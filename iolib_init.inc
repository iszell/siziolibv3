ptr	=	2

io_init
.if	io_needloader
	jsr	initloader
.endif
	rts

.if	io_needloader
initloader
	lda	io_driveiftyp
	asl
	asl
	asl
	asl
	ora	io_drivetyp
	asl
	tax
	stx	xtmp
	lda	io_loadertab,x
	bne	+
	jmp	io_noloader
+	pha
	.if	io_prtstatus
	jsr	primm
	.text	"Initializing I/O library"
	.byte	13,0
	.endif	
	.if	io_needdecrunch = 1
	.if	io_prtstatus
	jsr	primm
	.text	" Exomizer decruncher"
	.byte	13, 0
	.endif
	ldx	#0
-	lda	io_decrunchdata,x
	sta	io_decrunch,x
	inx
	bne	-
	ldx	#io_decrunchdatasize-$100
-	lda	io_decrunchdata+$100,x
	sta	io_decrunch+$100,x
	dex
	bpl	-
	.endif
	.if	io_prtstatus
	jsr	primm
	.null	" Computer loader: "
	asl
	asl
	asl
	asl
	tay
	ldx	#16
-	lda	io_cmploadernames,y
	jsr	chrout
	iny
	dex
	bne	-
	.endif
	pla
	asl
	tax
	lda	io_plus4loaders,x
	sta	ptr
	lda	io_plus4loaders+1,x
	sta	ptr+1
; Copy computer loader code
	ldy	#0
-	lda	(ptr),y
	sta	io_base,y
	iny
	bne	-
	ldx	xtmp
	inx
	lda	io_loadertab,x
	.if	io_prtstatus
	pha
	jsr	primm
	.byte	13
	.null	" Drive loader: "
	asl
	asl
	asl
	asl
	tay
	ldx	#16
-	lda	io_drvloadernames,y
	jsr	chrout
	iny
	dex
	bne	-
	lda	#13
	jsr	chrout
	pla
	.endif
	asl
	asl
	tax
	; loader start address
	lda	io_driveloaders,x
	sta	ptr
	lda	io_driveloaders+1,x
	sta	ptr+1
	lda	io_driveloaders+2,x
	; loader end address
	sta	ptr+2
	lda	io_driveloaders+3,x
	sta	ptr+3
	; loader drive side address
	lda	#<$0500
	sta	ptr+4
	lda	#>$0500
	sta	ptr+5
	.if	io_prtstatus
	jsr	primm
	.null	"  Downloading drive code... "
	.endif
; Download drive code
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
	lda	ptr+4
	jsr	sendbyte
	lda	ptr+5
	jsr	sendbyte
	lda	#16
	jsr	sendbyte
	ldy	#0
-	lda	(ptr),y
	jsr	sendbyte
	iny
	cpy	#16
	bne	-
	jsr	clrchans
	tya
	clc
	adc	ptr+4
	sta	ptr+4
	bcc	+
	inc	ptr+5
+	tya
	clc
	adc	ptr
	sta	ptr
	bcc	+
	inc	ptr+1
+	lda	ptr+1
	cmp	ptr+3
	bcc	--
	bne	+
	lda	ptr
	cmp	ptr+2
	bcc	--
+	.if	io_prtstatus
	jsr	primm
	.text	"done"
	.byte	13
	.text	"  Starting drive code" 
	.byte	13, 0
	.endif
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
	.if	io_base > $8000
	sei
	sta	ted_ramen
	.endif
	jsr	io_initloader
	.if	io_base > $8000
	sta	ted_romen
	cli
	.endif
	.if	io_prtstatus
	jsr	primm
	.text	"Initialization complete" 
	.byte	13, 0
	.endif
	clc
	.byte	$24
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

; Index: bit 7-5: interface
;        bit 4-1: drive type
;        bit   0: 0: computer, 1: drive
; Value:	byte 0: computer loader
;	byte 1: drive loader
io_loadertab
	; unsupported interface
	.byte	0, 0 ; 0
	.byte	0, 0 ; 1
	.byte	0, 0 ; 2
	.byte	0, 0 ; 3
	.byte	0, 0 ; 4
	.byte	0, 0 ; 5
	.byte	0, 0 ; 6
	.byte	0, 0 ; 7
	.byte	0, 0 ; 8
	.byte	0, 0 ; 9
	.byte	0, 0 ; a
	.byte	0, 0 ; b
	.byte	0, 0 ; c
	.byte	0, 0 ; d
	.byte	0, 0 ; e
	.byte	0, 0 ; f
	; serial with single drive on the bus
	.byte	0, 0 ; 0 unknown
	.byte	1, 1 ; 1 1540
	.byte	1, 1 ; 2 1541
	.byte	1, 1 ; 3 1541C
	.byte	1, 1 ; 4 1541-II
	.byte	0, 0 ; 5 1551
	.byte	1, 1 ; 6 1570
	.byte	1, 1 ; 7 1571
	.byte	1, 3 ; 8 1581
	.byte	1, 1 ; 9 RF-501C
	.byte	2, 7 ; a SD2IEC
	.byte	0, 0 ; b
	.byte	0, 0 ; c
	.byte	0, 0 ; d
	.byte	0, 0 ; e
	.byte	0, 0 ; f
	; serial with multiple drives on the bus
	.byte	0, 0 ; 0 unknown
	.byte	2, 2 ; 1 1540
	.byte	2, 2 ; 2 1541
	.byte	2, 2 ; 3 1541C
	.byte	2, 2 ; 4 1541-II
	.byte	0, 0 ; 5 1551
	.byte	2, 2 ; 6 1570
	.byte	2, 2 ; 7 1571
	.byte	2, 4 ; 8 1581
	.byte	2, 2 ; 9 RF-501C
	.byte	2, 7 ; a SD2IEC
	.byte	0, 0 ; b
	.byte	0, 0 ; c
	.byte	0, 0 ; d
	.byte	0, 0 ; e
	.byte	0, 0 ; f
	; TCBM
	.byte	0, 0 ; 0 unknown
	.byte	0, 0 ; 1 1540
	.byte	0, 0 ; 2 1541
	.byte	0, 0 ; 3 1541C
	.byte	0, 0 ; 4 1541-II
	.byte	4, 6 ; 5 1551
	.byte	0, 0 ; 6 1570
	.byte	0, 0 ; 7 1571
	.byte	0, 0 ; 8 1581
	.byte	0, 0 ; 9 RF-501C
	.byte	0, 0 ; a SD2IEC
	.byte	0, 0 ; b
	.byte	0, 0 ; c
	.byte	0, 0 ; d
	.byte	0, 0 ; e
	.byte	0, 0 ; f
	; parallel
	.byte	0, 0 ; 0 unknown
	.byte	0, 0 ; 1 1540
	.byte	3, 5 ; 2 1541
	.byte	3, 5 ; 3 1541C
	.byte	3, 5 ; 4 1541-II
	.byte	0, 0 ; 5 1551
	.byte	0, 0 ; 6 1570
	.byte	0, 0 ; 7 1571
	.byte	0, 0 ; 8 1581
	.byte	0, 0 ; 9 RF-501C
	.byte	0, 0 ; a SD2IEC
	.byte	0, 0 ; b
	.byte	0, 0 ; c
	.byte	0, 0 ; d
	.byte	0, 0 ; e
	.byte	0, 0 ; f

	.if	io_prtstatus
io_cmploadernames
		;0123456789abcdef
	.text	"unsupported     " ; 0
	.text	"serial 2bit     " ; 1
	.text	"serial 1bit     " ; 2
	.text	"parallel        " ; 3
	.text	"TCBM            " ; 4
io_drvloadernames
		;0123456789abcdef
	.text	"unsupported     " ; 0
	.text	"1541 serial 2bit" ; 1
	.text	"1541 serial 1bit" ; 2
	.text	"1581 serial 2bit" ; 3
	.text	"1581 serial 1bit" ; 4
	.text	"1541 parallel   " ; 5
	.text	"1551 TCBM       " ; 6
 	.text	"SD2IEC G.I. Joe " ; 7
	.endif

; contains the start address of the selected loader with the end address on the next word
io_plus4loaders
	.word	0
	.word	io_plus4serial2bit
	.word	io_plus4serial1bit
	.word	io_plus4parallel
	.word	io_plus4tcbm
	
; contains the start address and end addresses of the selected loader
io_driveloaders
	.word	0, 0
	.word	io_drv1541ser2, io_drv1541ser1
	.word	io_drv1541ser1, io_drv1581ser2
	.word	io_drv1581ser2, io_drv1581ser1
	.word	io_drv1581ser1, io_drv1541par
	.word	io_drv1541par, io_drvtcbm
	.word	io_drvtcbm, io_drvgijoe
	.word	io_drvgijoe, io_loaderend

io_plus4serial2bit
	.binary	"loader_plus4_serial2bit.prg",2
io_plus4serial1bit
	.binary	"loader_plus4_serial1bit.prg",2
io_plus4parallel
	.binary	"loader_plus4_parallel.prg",2
io_plus4tcbm
	.binary	"loader_plus4_tcbm.prg",2
io_drv1541ser2
	.binary	"loader_drive_2bit1541.prg",2
io_drv1541ser1
	.binary	"loader_drive_1bit1541.prg",2
io_drv1581ser2
io_drv1581ser1
	.binary	"loader_drive_1bit1581.prg",2
io_drv1541par
	.binary	"loader_drive_parallel1541.prg",2
io_drvtcbm
	.binary	"loader_drive_tcbm.prg",2
io_drvgijoe
	.binary	"loader_drive_gijoe.prg",2
io_loaderend
.if io_needdecrunch = 1
io_decrunchdata
	.binary	"decrunch.prg", 2
io_decrunchdatasize=*-io_decrunchdata
.endif
.endif
