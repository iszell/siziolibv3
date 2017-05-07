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
