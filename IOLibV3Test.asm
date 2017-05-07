
	.include	"basic_header.inc"
	.include	"kernal-table.inc"

	jsr	primm
	.text	"IOLibV3 test by Siz (c) 2014.06.03"
	.byte	14, 13, 0

	jsr	io_detect
	lda	io_drivetyp
	bne	+
	rts
+	jsr	io_init
	jsr	primm
	.byte	13
	.null	"Testing loader: "
	sei
	lda	#<irq
	ldx	#>irq
	sta	$fffe
	stx	$ffff
	lda	#%00001010
	sta	ted_irqmask
	lda	#220
	sta	ted_rasterirqline
	sta	ted_ramen
	lda	#0
	sta	counter
	sta	counter+1
	sta	counter+2
	sta	counter+3
	cli
	ldx	#"t"
	ldy	#"e"
	jsr	io_load
;	lda	$efff
;	pha
;	dec	ted_border
;	ldx	#"t"
;	ldy	#"e"
;	jsr	io_load
	lda	#%00000010
	sta	ted_irqmask
;	pla
;	tax
	php
	lda	$efff
;	pha
	sta	ted_romen
	tax
	lda	#0
	jsr	lnprt
;	lda	#" "
;	jsr	chrout
;	pla
;	tax
;	lda	#0
;	jsr	lnprt
	lda	#" "
	jsr	chrout
	plp
	bcs	+
	jsr	primm
	.null	"no "
+	jsr	primm
	.text	"error"
	.byte	13
	.null	"load took "
	ldx	counter
	lda	counter+1
	jsr	lnprt
	lda	#":"
	jsr	chrout
	ldx	counter+2
	lda	counter+3
	jsr	lnprt
	jsr	primm
	.text	" frames"
	.byte	13, 0
;	inc	ted_border
	rts
	
irq	inc	ted_border
	pha
	lda	ted_irqsource
	sta	ted_irqsource
	and	#%00000010
	beq	+
	inc	counter+3
	bcc	+
	inc	counter+2
	bcc	+
	inc	counter+1
	bcc	+
	inc	counter
+	lda	ted_timer3lo
	eor	ted_timer2lo
	sta	ted_timer1lo
	sta	ted_timer1hi
	pla
	dec	ted_border
	rti

io_prtstatus = 1
io_needmemdetect = 1
io_needvideodetect = 1
io_needsounddetect = 1
io_needloader = 1
io_needdecrunch = 0
	.include	"iolib_def.inc"
	.include	"iolib.inc"

counter	.word	0
	.word	0
