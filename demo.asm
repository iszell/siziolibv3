
	.include	"basic_header.inc"
	.include	"kernal-table.inc"

charset	=	$4000
bmp	=	$2000

	jsr	primm
	.text	"IOLibV3 demo by Siz (c) 2017.05.10"
	.byte	14, 13, 0
	
	jsr	io_detect
	lda	io_drivetyp
	bne	+
	rts
+	jsr	io_init

	ldx	#0
-	.for	i=0, i<4, i=i+1
	lda	$d400+i*$100,x
	sta	charset+i*$100,x
	.next
	inx
	bne	-

	lda	#0
	sta	loopcnt
	sta	loopcnt+1
	sta	loopcnt+2
	sta	loopcnt+3
	sta	loopcnt+4

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
	
loadloop
	jsr	rstframe
	ldx	#"b"
	ldy	#"1"
	jsr	io_load
	inc	framerun
	
	jsr	clr
	
	jsr	incloop
	
	lda	#"R"
	ldx	#"a"
	ldy	#"w"
	sta	modestr
	stx	modestr+1
	sty	modestr+2
	jsr	prtstr

	jsr	rstframe
	ldx	#"e"
	ldy	#"1"
	jsr	io_decrunch
	inc	framerun
	jsr	clr
	lda	#"E"
	ldx	#"x"
	ldy	#"o"
	sta	modestr
	stx	modestr+1
	sty	modestr+2
	jsr	prtstr
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
	
	bpl	+
	jsr	incframe
+
	
	lda	ted_irqsource
	sta	ted_irqsource
	
	pla
	tay
	pla
	tax
	pla
	rti

rstframe
	ldx	#0
	stx	framecnt
	stx	framecnt+1
	stx	framecnt+2
	stx	framecnt+3
	stx	framecnt+4
	inx
	stx	framerun
	rts

incframe
	ldy	#4
-	ldx	framecnt,y
	inx
	cpx	#10
	bne	+
	lda	#0
	sta	framecnt,y
	dey
	bpl	-
+	txa
	sta	framecnt,y
	rts
	

incloop	ldy	#4
-	ldx	loopcnt,y
	inx
	cpx	#10
	bne	+
	lda	#0
	sta	loopcnt,y
	dey
	bpl	-
+	txa
	sta	loopcnt,y
	ldx	#4
-	lda	loopcnt,x
	ora	#"0"
	sta	loopstr,x
	dex
	bpl	-
	rts

prtstr	
	ldx	#4
-	lda	framecnt,x
	ora	#"0"
	sta	framestr,x
	dex
	bpl	-

	lda	#0
	sta	prtchar.dstaddr
	lda	#(>bmp+24*320)
	sta	prtchar.dstaddr+1
	ldx	#0
-	lda	string,x
	bmi	+
	cmp	#$40
	bcc	++
	and	#$1f
+	and	#$7f
+	jsr	prtchar
	inx
	cpx	#32
	bne	-
	rts

prtchar	.block
	sta	savea
	stx	savex
	lda	#0
	sta	srcaddr+1
	lda	savea
	asl
	rol	srcaddr+1
	asl
	rol	srcaddr+1
	asl
	rol	srcaddr+1
	sta	srcaddr
	lda	srcaddr+1
	ora	#>charset
	sta	srcaddr+1
	ldx	#7
srcaddr=*+1
-	lda	charset,x
dstaddr=*+1
	sta	bmp+24*320,x
	dex
	bpl	-
	lda	#8
	clc
	adc	dstaddr
	sta	dstaddr
	bcc	+
	inc	dstaddr+1
+
savex=*+1
	ldx	#0
savea=*+1
	lda	#0
	.bend
	rts

loopcnt	.fill	5
		;012345
framecnt
	.fill	5
framerun
	.byte	0

		;012345
string	.text	"Loop: "
		;6789abcdef0123
loopstr	.text	"01234 Frames: "
		;456789
framestr
	.text	"01234 "
		;abc
modestr	.text	"Raw"
		;def
	.text	"   "

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