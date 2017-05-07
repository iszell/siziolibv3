	.include "basic_header.inc"

ptr	=	2

	ldy	#0
	lda	#$30
	sty	ptr
	sta	ptr+1
-	tya
	sta	(ptr),y
	iny
	bne	-
	inc	ptr+1
	lda	ptr+1
	cmp	#$f0
	bne	-
	rts