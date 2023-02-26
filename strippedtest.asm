	#import "stripped.asm"
	
	* = $5555
	
	dec $ff19
	lda #0
	sta iolib.io_loadflag
	ldx #'b'
	ldy #'1'
	jsr iolib.load
	bcc !++
!:	dec $ff19
	jmp !-
!:	dec $ff19
	jmp *
