	.print	". sound source detection"
	.namespace iolib {

detect_sound:
{
.label	sidptr	=	2

	lda	sidptr
	pha
	lda	sidptr+1
	pha
// Detect SID address
#if	HAS_TED
	sei
	sta ted.ramen
#endif
	lda #0
	sta io_soundtype
	ldx #<sid_solder
	ldy #>sid_solder
	jsr io_detsidaddr
	cmp #$ff
	beq soldersid
	ldx #<sid_csory
	ldy #>sid_csory
	jsr io_detsidaddr
	cmp #$ff
	bne nosiddet
soldersid:
	inc io_soundtype
// Detect SID type
	jsr detsidtp
// Detect NAE
#if	HAS_TED
	jsr detnae
#endif
	ldx sidptr
	ldy sidptr+1
	stx io_sidbase
	sty io_sidbase+1
nosiddet:
// Detect AY (DIGIMUZ)
#if	HAS_TED
	jsr detay
#endif
// Detect FM
	jsr detfm

// Print result
#if	HAS_TED
	sta ted.romen
	cli
#endif
	#if	prtstatus
	jsr	primm
	.text	" Sound: "
	.byte	0
#if	HAS_TED
	jsr	primm
	.text	"TED "
	.byte	0
#endif
// Print SID
#if	HAS_TED
	sei
	sta	ted.ramen
#endif
	lda	io_soundtype
	and	#%111
#if	HAS_TED
	sta	ted.romen
	cli
#endif
	beq	nosid
	pha
	and	#%100
	bne	!+
	jsr	primm
	      // NAE 1.2
	.text	"SIDCard"
	.byte	0
	jmp	!++
!:	jsr	primm
	.text	"NAE "
	.byte	0
	lda	nae_control+15
	pha
	lsr
	lsr
	lsr
	lsr
	ora	#'0'
	jsr	chrout
	lda	#'.'
	jsr	chrout
	pla
	and	#%00001111
	ora	#'0'
	jsr	chrout
!:	lda	#'/'
	jsr	chrout
	pla
	and	#%10
	asl
	tax
	ldy	#4
!:	lda	io_sidtypes,x
	jsr	chrout
	inx
	dey
	bne	!-
	jsr	prtspc
nosid:	
// Print AY
#if	HAS_TED
	sei
	sta	ted.ramen
#endif
	lda	#%1000
	bit	io_soundtype
#if	HAS_TED
	sta	ted.romen
	cli
#endif
	beq	noay
	jsr	primm
	.text	"AY "
	.byte	0
noay:
// Print FM
#if	HAS_TED
	sei
	sta	ted.ramen
#endif
	lda	#%10000
	bit	io_soundtype
#if	HAS_TED
	sta	ted.romen
	cli
#endif
	beq	nofm
	jsr	primm
	.text	"FM"
	.byte	0
nofm:
	jsr	prtcr
	#endif
	pla
	sta	sidptr+1
	pla
	sta	sidptr
	rts
	
// Detect SID address
//=======================================
//  In: XR: SID address low
//      YR: SID address high
// Out: AC: 0: not found $ff: found
//=======================================

io_detsidaddr:
	lda #0
	sta io_sidbase
	sta io_sidbase+1
	
	stx sidptr
	sty sidptr+1
	
	ldy #24
!:	sta (sidptr),y
	dey
	bpl !-
	
	ldy #25
	lda (sidptr),y
	iny
	and (sidptr),y
	rts
	
//=======================================
// Detect NST SIDCard
//=======================================

#if	HAS_TED
detnae:	lda #%11100000
	sta nae_control+13
	ldx #0
!:	lda nae_control+15
	cmp nae_control+15
	bne !+
	dex
	bne !-
	and #%11100000
	cmp #%11100000
	beq !+		// Legacy SID-Card
	lda nae_control+15
	beq !+		// VICE :)
	lda io_soundtype
	ora #%100
	sta io_soundtype
!:	rts
#endif
	
// Detect SID chip type
// original version from Reflex Math demo
//=======================================
	
detsidtp:
//Set a low frequency for Oscillator
// (Voice 3) #$0200 which is somewhere
// between B-0 and C-1, according to demo
	
	ldy #15
	lda #$02
	sta (sidptr),y
	
//Set Sawtooth and Triangle waveforms for
//voice 3 and start release of ADSR
	
	ldy #18
	lda #%00110000
	sta (sidptr),y
	
//Check if output of voice 3 ever goes
//higher than $80. It's only possible on
//new SID chip (8580) and never on the
//old one (6581)
	
	ldy #0
	ldx #0
	sty ystore
loop2:	ldy #27
	lda (sidptr),y
	bmi newsid
	dex
	bne loop2
	ldy ystore
	dey
	sty ystore
	bne loop2
	beq oldsid
newsid:	lda #%10
	ora io_soundtype
	sta io_soundtype
oldsid:	rts

#if	HAS_TED
setsidc64:
	#if	prtstatus
	jsr	primm
	.text	" Switching NAE to C64 clock"
	.byte	13, 0
	#endif
	lda #$d1
	sta nae_control+13
	rts
#endif

#if	HAS_TED
detay:  rts
	lda #%1000
	ora io_soundtype
	sta io_soundtype
	rts
#endif

detfm:  rts
	lda #%10000
	ora io_soundtype
	sta io_soundtype
	rts

ystore:	.byte	0

	#if	prtstatus
io_sidtypes:
	.text	"6581"
	.text	"8580"
	#endif
}
}
