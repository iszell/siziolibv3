
	.include	"basic_header.inc"
	
	jsr	io_det_drive
	lda	#$65
	bcc	+
	lda	#$32
+	sta	$ff19
	jsr	io_init_ldr
	lda	#$6e
	bcc	+
	lda	#$32
+	sta	$ff19

	ldx	#"d"
	ldy	#"e"
	jsr	$0200
	bcs	+
	stx	$0c00
	sty	$0c01
	lda	#$67
	sta	$ff19
	jmp	*
+	lda	#$32
	sta	$ff19
	jmp	*

	.include	"io_sd2iec.inc"
