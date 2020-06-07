
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
	sta	jiffy

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
	jsr	inctimer
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
	stx	timecnt
	stx	timecnt+1
	stx	timecnt+2
	stx	timecnt+3
	stx	timecnt+4
	inx
	stx	framerun
-	rts

incframe
	lda	framerun
	beq	-
	ldy	#4
	inc	timecnt+4
-	ldx	timecnt,y
	inx
	cpx	#10
	bne	+
	lda	#0
	sta	timecnt,y
	dey
	bpl	-
+	txa
	sta	timecnt,y
-	rts

inctimer
	inc	jiffy
	lda	jiffy
	cmp	#50
	bne	-
	lda	#0
	sta	jiffy
	
	inc	runsec+1
	lda	runsec+1
	cmp	#"9"+1
	bne	-
	lda	#"0"
	sta	runsec+1
	
	inc	runsec
	lda	runsec
	cmp	#"6"
	bne	-
	lda	#"0"
	sta	runsec

	inc	runmin+1
	lda	runmin+1
	cmp	#"9"+1
	bne	-
	lda	#"0"
	sta	runmin+1
	
	inc	runmin
	lda	runmin
	cmp	#"6"
	bne	-
	lda	#"0"
	sta	runmin

	inc	runhour+1
	lda	runhour+1
	cmp	#"9"+1
	bne	-
	lda	#"0"
	sta	runhour+1
	
	inc	runhour
	lda	runhour
	cmp	#"9"+1
	bne	-
	lda	#"0"
	sta	runhour

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
	ldx	#0
	ldy	#0
-	lda	timecnt,x
	ora	#"0"
	sta	timestr,y
	inx
	iny
	cpy	#3
	bne	+
	iny
+	cpx	#5
	bne	-

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
timecnt	.fill	5
framerun
	.byte	0
jiffy	.byte	0

string	.text	"L: "
loopstr	.text	"01234 T: "
timestr
	.text	"012.34s "
modestr	.text	"Raw"
	.text	" "
runhour	.text	"00:"
runmin	.text	"00:"
runsec	.text	"00"
	.fill	32, " "

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