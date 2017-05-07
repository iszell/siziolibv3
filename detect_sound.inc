sidptr	=	2

io_det_sound
.if	ted_romen
	sei
	sta ted_ramen
.endif
	lda #0
	sta io_soundtype
	ldx #<sid_solder
	ldy #>sid_solder
	jsr io_detsidaddr
	cmp #$ff
	beq +
	ldx #<sid_csory
	ldy #>sid_csory
	jsr io_detsidaddr
	cmp #$ff
	bne ++
+	inc io_soundtype
	jsr detsidtp
.if	nae_control
	jsr detnae
.endif
	ldx sidptr
	ldy sidptr+1
	stx io_sidbase
	sty io_sidbase+1
+
.if	ted_romen
	sta ted_romen
	cli
.endif
	.if	io_prtstatus
	jsr	primm
	.null	" Sound: "
	sei
	sta	ted_ramen
	lda	io_soundtype
	sta	ted_romen
	cli
.if	nae_control
	bmi	++
	sei
	sta	ted_ramen
	lda	io_soundtype
	sta	ted_romen
.endif
	bne	+
	jsr	primm
	.null	"TED"
	jmp	++++
+	jsr	primm
	.null	"SIDCard"
.if	nae_control
	jmp	++
+	jsr	primm
	.null	"NAE v"
	lda	nae_control+15
	pha
	lsr
	lsr
	lsr
	lsr
	ora	#"0"
	jsr	chrout
	lda	#"."
	jsr	chrout
	pla
	and	#%00001111
	ora	#"0"
	jsr	chrout
.endif
+	jsr	primm
	.null	" with "
	sei
	sta	ted_ramen
	lda	io_soundtype
	sta	ted_romen
	cli
	asl
	asl
	tax
	ldy	#4
-	lda	io_sidtypes-4,x
	jsr	chrout
	inx
	dey
	bne	-
+	lda	#13
	jsr	chrout
	.endif
	rts
	
; Detect SID address
;=======================================
;  In: XR: SID address low
;      YR: SID address high
; Out: AC: 0: not found $ff: found
;=======================================

io_detsidaddr	
	lda #0
	sta io_sidbase
	sta io_sidbase+1
	
	stx sidptr
	sty sidptr+1
	
	ldy #24
-	sta (sidptr),y
	dey
	bpl -
	
	ldy #25
	lda (sidptr),y
	iny
	and (sidptr),y
	rts
	
;=======================================
; Detect NST SIDCard
;=======================================

.if	nae_control
detnae	lda #%11100000
	sta nae_control+13
	ldx #0
-	lda nae_control+15
	cmp nae_control+15
	bne +
	dex
	bne -
	and #%11100000
	cmp #%11100000
	beq +		; Legacy SID-Card
	lda nae_control+15
	beq +		; VICE :)
	lda io_soundtype
	ora #%10000000
-	sta io_soundtype
+	rts
.endif
	
; Detect SID chip type
; original version from Reflex Math demo
;=======================================
	
detsidtp	lda #1
	sta io_soundtype
	
;Set a low frequency for Oscillator
; (Voice 3) #$0200 which is somewhere
; between B-0 and C-1, according to demo
	
	ldy #15
	lda #$02
	sta (sidptr),y
	
;Set Sawtooth and Triangle waveforms for
;voice 3 and start release of ADSR
	
	ldy #18
	lda #%00110000
	sta (sidptr),y
	
;Check if output of voice 3 ever goes
;higher than $80. It's only possible on
;new SID chip (8580) and never on the
;old one (6581)
	
	ldy #0
	ldx #0
	sty ystore
loop2	ldy #27
	lda (sidptr),y
	bmi newsid
	dex
	bne loop2
	ldy ystore
	dey
	sty ystore
	bne loop2
	beq oldsid
newsid	inc io_soundtype
oldsid	rts

.if	nae_control
setsidc64
	.if	io_prtstatus
	jsr	primm
	.text	" Switching NAE to C64 clock"
	.byte	13, 0
	.endif
	lda #$d1
	sta nae_control+13
	rts
.endif

ystore	.byte	0

	.if	io_prtstatus
io_sidtypes
	.text	"6581"
	.text	"8580"
	.endif