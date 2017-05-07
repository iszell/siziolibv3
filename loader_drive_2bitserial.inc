writebyte	stx bitbuff
	lda #%00000100
	jsr write2bit
	jsr write2bit
	jsr write2bit
write2bit	lsr bitbuff
	ldx #%00000010
	bcc +
	ldx #%00000000
+
-	bit serialdata
	bne -
	stx serialdata
	lsr bitbuff
	ldx #%00000010
	bcc +
	ldx #%00000000
+
-	bit serialdata
	beq -
	stx serialdata
	rts
readbyte	ldy #4
	lda #%00000100
-	bit serialdata
	beq -
	lda serialdata
	lsr
	ror bitbuff
	lda #%00000100
-	bit serialdata
	bne -
	lda serialdata
	lsr
	ror bitbuff
	dey
	bne readbyte+2
	lda bitbuff
	rts
init	sei
	cld
	ldy #8
initloop	lda #%00010000
	sta serialdata
-	dex
	bne -
	lda #%00000000
	sta serialdata
-	dex
	bne -
	dey
	bne initloop
-	lda serialdata
	and #%00000101
	bne -
	lda serialdata
	and #%00000101
	bne -
	rts
	
	.end
; Send byte code from Siz fastloader (works with screen off and interrupts disabled)
	
	sta bitbuff
-	bit serialdata
	bpl -
	lda #%10000
	sta serialdata
	ldx #4
-	lda #0
	asl bitbuf
	rol
	asl
	asl bitbuff
	rol
	asl
	sta serialdata
	dex
	bne -
	ldx #1
	bne +
+	nop
	nop
	lda #%01111
	sta serialdata
	rts
