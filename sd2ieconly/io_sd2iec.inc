	.include	"kernal-table.inc"
io_det_drive
; default to drive 8 if last used # is less than that
	lda	#8
	cmp	$ae
	bcc	+
	sta	$ae
+	ldx	#statustxte-statustxt-1
	lda	#0
-	sta	statustxt,x
	dex
	bpl	-
	ldx	$ae
	lda	#15
	tay
	jsr	setlfs
	lda	#0
	jsr	setnam
	jsr	open
	lda	st
	beq	+
	jmp	enderr
+	ldx	#15
	jsr	chkout
	lda	st
	bne	enderr
	lda	#"u"
	jsr	chrout
	lda	st
	bne	enderr
	lda	#"i"
	jsr	chrout
	lda	st
	bne	enderr
	lda	#0
	sta	statuslen
	jsr	open
	lda	st
	bne	enderr
	ldx	#15
	jsr	chkin
	lda	st
	bne	enderr
-	jsr	chrin
	ldx	statuslen
	sta	statustxt,x
	inc	statuslen
+	bit	st
	bvs	+
	lda	st
	bne	enderr
	beq	-
+
; analyze result status string
	ldx	#8
-	lda	statustxt,x
	cmp	io_drivestsstr,x
	bne	enderr
	dex
	bpl	-
	clc
	.byte $24  ; bit $xx
enderr	sec
	php
	jsr	clrchans
	lda	#15
	jsr	close
	plp
	rts

; Init loader
io_init_ldr
	ldx	#0
-	lda	io_plus4serial1bit,x
	sta	$0200,x
	inx
	bne	-

	ldx	$ae
	lda	#15
	tay
	jsr	setlfs
	lda	#0
	jsr	setnam
	jsr	open
	lda	st
	beq	+
	jmp	io_noloader
+
-	ldx	#15
	jsr	chkout
	lda	st
	beq	+
	jmp	io_noloader
+	lda	#"m"
	jsr	sendbyte
	lda	#"-"
	jsr	sendbyte
	lda	#"w"
	jsr	sendbyte
drvaddrlo=*+1
	lda	#$00
	jsr	sendbyte
drvaddrhi=*+1
	lda	#$05
	jsr	sendbyte
	lda	#16
	jsr	sendbyte
	ldy	#0
cmpaddr=*+1
-	lda	io_drvgijoe,y
	jsr	sendbyte
	iny
	cpy	#16
	bne	-
	jsr	clrchans
	tya
	clc
	adc	drvaddrlo
	sta	drvaddrlo
	bcc	+
	inc	drvaddrhi
+	tya
	clc
	adc	cmpaddr
	sta	cmpaddr
	bcc	+
	inc	cmpaddr+1
+	lda	cmpaddr+1
	cmp	#(>io_loaderend)+1
	bcc	--
	bne	+
	ldx	#15
	jsr	chkout
	lda	#"m"
	jsr	sendbyte
	lda	#"-"
	jsr	sendbyte
	lda	#"e"
	jsr	sendbyte
	lda	#<$0500
	jsr	sendbyte
	lda	#>$0500
	jsr	sendbyte
	jsr	clrchans
	lda	#15
	jsr	close
	jsr	$0203
	clc
	rts
io_noloader
	sec
	rts

sendbyte	jsr	chrout
	lda	st
	beq	+
	pla
	pla
	jmp	io_noloader
+	rts

; format: null terminated string up to 6 characters or 7 characters without null termination
; 	byte 8 is drive type number  
io_drivestsstr	;0123456
;	.text	"73,sd2iec"
	.text	"73,cbm do"

statuslen .byte	0
statustxt	.fill	64, 0
statustxte

io_plus4serial1bit
	.binary	"loader_plus4_serial1bit.prg",2
io_drvgijoe
	.binary	"loader_drive_gijoe.prg",2
io_loaderend
