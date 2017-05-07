	* = io_base

tia	= tcbm_9
padta	= tia
pbdta	= tia+1
pcdta	= tia+2
padir	= tia+3
pbdir	= tia+4
pcdir	= tia+5

	jmp	startload
	jmp	readbyte
	jmp	writebyte
	jmp	hardsync
	jmp	sync
	ldx	io_tcbmoffs
	lda pcdta,x
	and #%10111111
	sta pcdta,x
-	lda pcdta,x
	bmi -
hardsync
sync	rts

readbyte	ldx	io_tcbmoffs
-	lda pcdta,x	;ACK=1?
	bmi -		;yes
	lda pcdta,x
	ora #%01000000
	sta pcdta,x	;DAV=1
-	lda pcdta,x	;ACK=1?
	bpl -		;no
	lda padta,x	;get byte
	pha
	lda pcdta,x
	and #%10111111
	sta pcdta,x	;DAV=0
	pla
	rts

writebyte
	ldx	io_tcbmoffs
	pha
	lda #$ff
	sta padir,x	;dir=out
-	lda pcdta,x	;ACK=1?
	bmi -		;yes
	pla
	sta padta,x	;put byte
	lda pcdta,x
	ora #%01000000
	sta pcdta,x	;DAV=1
-	lda pcdta,x	;ACK=1?
	bpl -		;no
	lda pcdta,x
	and #%10111111
	sta pcdta,x	;DAV=0
	inc padir,x	;dir=in
	rts
	.include	"loader_plus4_core.inc"
