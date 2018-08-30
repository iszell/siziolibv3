
	.include	"basic_header.inc"
	.include	"kernal-table.inc"

	jsr	primm
	.text	"IOLibV3 demo by Siz (c) 2017.05.10"
	.byte	14, 13, 0
	
	jsr	io_detect
	lda	io_drivetyp
	bne	+
	rts
+	jsr	io_init

	sei
	sta	ted_ramen
	lda	#<irq
	ldx	#>irq
	sta	$fffe
	stx	$ffff
	lda	#2
	sta	ted_rasterirqline
	cli
	
	ldx	#0
	lda	#$70
-	.for	i=0, i<4, i=i+1
	sta	$1800+$100*i,x
	.next
	inx
	bne	-
	lda	#$01
-	.for	i=0, i<4, i=i+1
	sta	$1c00+$100*i,x
	.next
	inx
	bne	-
	
	lda	#$3b
	sta	ted_ctrl1
	lda	#$18
	sta	ted_screenaddr
	lda	#$08
	sta	ted_bitmapctrl
	
loadloop	ldx	#"b"
	ldy	#"1"
	jsr	io_load
	
	jsr	clr

	ldx	#"e"
	ldy	#"1"
	jsr	io_decrunch
	jsr	clr
	jmp	loadloop
	
clr	ldx	#0
	lda	#$00
-	.for	i=0, i<32, i=i+1
	sta	$2000+$100*i,x
	.next
	inx
	bne	-
	rts

irq	pha
	txa
	pha
	tya
	pha

bordercolor = *+1
	lda	#$71
	ldx	#160
-	cpx	ted_rastercolumn
	bcs	-
	sta	ted_border

irqline	= *+1
	lda	#203
	sta	ted_rasterirqline
	
	lda	bordercolor
	eor	#$50
	sta	bordercolor
	
	lda	irqline
	eor	#(203 ^ 2)
	sta	irqline
	
	lda	ted_irqsource
	sta	ted_irqsource
	
	pla
	tay
	pla
	tax
	pla
	rti

io_prtstatus = 1
io_needmemdetect = 1
io_needvideodetect = 1
io_needsounddetect = 1
io_needloader = 1
io_needdecrunch = 1
	.include	"iolib_def.inc"
	.include	"iolib.inc"
; Eclipse Assembly Editor custom preferences
;#$postProcessor=exomizer\3.0.1\exomizer.exe
;#$postProcessorOptions=sfx basic -t4 -o &o &i
