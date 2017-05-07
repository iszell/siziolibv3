	* = $cf00

ptr	= $9e
bitbuff	= $b7
;  Bit  Dir. Expl.
;  7         Serial Bus Data Input
;  6         Serial Bus Clock Pulse Input
;  5         Serial Bus Data Output
;  4         Serial Bus Clock Pulse Output
;  3         Serial Bus ATN Signal Output
;  2         User / RS-232 Data Output / CNTR "/Strobe"
;  1-0  Out  VIC Memory Bank XOR 3  (Default=3, see VIC Port D018h)
serialport	= $dd00

	lda serialport
	and #%00001111	; 0000 0111
	sta V_CFCE + 1
	eor #%00010000	; 0001 0111
	sta write2bit + 1
	eor #%00110000	; 0010 0111
	sta V_CF6A + 1
	eor #%10110000	; 1001 0111
	sta read2bit + 1
	eor #%01010000	; 1100 0111
	sta V_CFA4 + 1
	sta V_CFE8 + 1
	lda #2
	jsr sendfnam
	jsr S_CFDC
	jsr readbyte
	sta ptr
	jsr readbyte
	sta ptr+1
	ldy #0
loadloop	jsr readbyte
	cmp #$ac
	bne storebyte
	jsr readbyte
	cmp #$ac
	beq storebyte
	cmp #$ff
	beq eof
	cmp #$f7
	beq loaderror
	jsr S_CFDC
	jmp loadloop
	;
storebyte	sta (ptr),Y
	iny
	bne +
	inc ptr+1
+	jmp loadloop
eof	clc
loaderror	ldx filename
	ldy filename+1
	lda #0
	rts
sendfnam	pha
	stx filename
	sty filename+1
V_CF6A	lda #%00100111
	sta serialport
	jsr S_CFDC
	pla
	jsr writebyte
	lda filename
	jsr writebyte
	lda filename+1
	jsr writebyte
	rts
readbyte	jsr read2bit
	jsr read2bit
	jsr read2bit
	jsr read2bit
	jsr S_CF94
	lda bitbuff
S_CF94	rts
read2bit	ldx #%10010111
	lda serialport
	stx serialport
	asl
	ror bitbuff
	pha
	pla
	pha
	pla
V_CFA4	ldx #%11000111
	lda serialport
	stx serialport
	asl
	ror bitbuff
	rts
writebyte	sta bitbuff
	jsr write2bit
	jsr write2bit
	jsr write2bit
	jsr write2bit
	rts
write2bit	lda #%00010111
	lsr bitbuff
	bcc +
	ora #%00100000
+	sta serialport
	nop
	nop
	nop
	nop
V_CFCE	lda #%00000111
	lsr bitbuff
	bcc +
	ora #%00100000
+	sta serialport
	nop
	nop
	rts
S_CFDC	ldx #50
-	dex
	bne -
-	lda serialport
	and #%01000000
	beq -
V_CFE8	lda #%11000111
	sta serialport
	lda #$fe
	sta V_CFFB
	ldx #5
-	dex
	bne -
	rts

	.byte 5
filename	.text "f0"
V_CFFB	.byte $fe
	.text "10"
	.byte $fe, $ff
	.byte 0
