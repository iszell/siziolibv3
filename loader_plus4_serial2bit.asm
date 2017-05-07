	* = io_base

bitbuff	= $b7
;C64 (serial bus output is inverted!)
; default value %10010111 (at least with JiffyDOS)
;  Bit  Dir. Expl.
;  7         Serial Bus Data Input
;  6         Serial Bus Clock Pulse Input
;  5         Serial Bus Data Output
;  4         Serial Bus Clock Pulse Output
;  3         Serial Bus ATN Signal Output
;  2         User / RS-232 Data Output / CNTR "/Strobe"
;  1-0  Out  VIC Memory Bank XOR 3  (Default=3, see VIC Port D018h)
;plus/4
; default value %11001000
;  Bit Dir Expl.
;  7   In  Serial Data In (and PLUS/4: Cas Sense) (0=Low, 1=High)
;  6   In  Serial Clock In                        (0=Low, 1=High)
;  5   -   Not used (no pin-out on 7501/8501)     (N/A)
;  4   In  Cassette Read                          (0=Low, 1=High)
;  3   Out Cassette Motor                         (0=9VDC, 1=Off) (Inverted)
;  2   Out Serial ATN Out (and PLUS/4: User Port) (0=High, 1=Low) (Inverted)
;  1   Out Serial Clock Out, Cassette Write       (0=High, 1=Low) (Inverted)
;  0   Out Serial Data Out                        (0=High, 1=Low) (Inverted)
serialport	= cpu_port

	jmp	startload
	jmp	readbyte
	jmp	writebyte
	jmp	hardsync
	jmp	sync
	lda	#%00001000	; 11000111
	sta	serialport
	ldx	#0
-	dey
	bne	-
	dex
	bne	-
	rts
readbyte	jsr read2bit
	jsr read2bit
	jsr read2bit
	jsr read2bit
	jsr dummyrts
	lda bitbuff
dummyrts	rts
read2bit	ldx #%00001010 ;10010111 clock hi data lo
	lda serialport
	stx serialport
	asl
	ror bitbuff
	ldx #7
-	dex
	bne -
	ldx #%00001000 ;11000111 clock lo, data lo
	lda serialport
	stx serialport
	asl
	ror bitbuff
	ldx #3
-	dex
	bne -
	rts
writebyte	sta bitbuff
	jsr write2bit
	jsr write2bit
	jsr write2bit
	jsr write2bit
	rts
write2bit	lda #%00001010 ;00010111 ; clock hi, data hi
	lsr bitbuff
	bcc +
	ora #%00000001 ; set data lo
+	sta serialport
	ldx #8
-	dex
	bne -
	lda #%00001000 ;00000111 ; clock lo, data hi 
	lsr bitbuff
	bcc +
	ora #%00000001 ; set data lo
+	sta serialport
	jmp dummyrts
hardsync	lda #%00001001 ;00100111 - clock lo, data hi
	sta serialport
sync	ldx #100
-	dex
	bne -
-	lda serialport
	and #%01000000 ;01000000 check clock
	beq -
	lda #%00001000 ;11000111 clock lo, data lo
	sta serialport
	ldx #10
-	dex
	bne -
	rts
	.include	"loader_plus4_core.inc"

	.end

; Read byte code from Siz fastloader (works with screen off and interrupts disabled)
	lda #%100
	sta serialport
-	bit serialport
	bpl -
	lda #%000
	sta serialport
	ldx #6
-	dex
	nop
	bne -
	ldx #4
-	lda serialport
	bit ted_border
	bit ted_border
	bit ted_border
	asl
	php
	asl
	rol bitbuff
	plp
	rol bitbuff
	rol ted_border
	dex
	bne -
	lda bitbuff
	eor #$ff
	rts
