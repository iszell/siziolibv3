
	.include	"basic_header.inc"
	.include	"kernal-table.inc"
	.include	"iolib_def.inc"

	jsr	primm
	.text	"IOLibV3 Exomizer test by Siz"
	.byte	13
	.text	"(c) 2016.04.02"
	.byte	14, 13, 0

	jsr	io_detect
;	lda	io_drivetyp
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
	lda	#%00000010
	sta	ted_irqmask
	lda	#220
	sta	ted_rasterirqline
	sta	ted_ramen
	cli
	ldx	#"e"
	ldy	#"x"
	jsr	io_decrunch
	sta	ted_romen
	bcs	error
	jsr	primm
	.text	"done"
	.byte	13, 0
	lda	#$3b
	sta	$ff06
	lda	#$18
	sta	$ff07
	lda	#$18
	sta	$ff12
	lda	#$58
	sta	$ff14
	lda	$5bfe
	sta	$ff15
	lda	$5bff
	sta	$ff16
	lda	#0
	sta	$ff19
	jmp	*
	
error	jsr	primm
	.text	"load error"
	.byte	13, 0
	rts
	
irq	inc	ted_border
	pha
	lda	ted_irqsource
	sta	ted_irqsource
	pla
	dec	ted_border
	rti

io_prtstatus = 1
io_needmemdetect = 1
io_needvideodetect = 1
io_needsounddetect = 1
io_needloader = 1
io_needdecrunch = 1
	.include	"iolib.inc"

