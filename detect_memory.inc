testaddr	=	$fcff
io_det_memsize
	sei
	ldy	#0
	sty	io_ramsize
	sty	ted_ramen

; Reset Csory expansion control
; -- commented out because most probably VICE Csory emulation is wrong - inverted default value!
;	sty	ramexpctrl_csory
; Reset detection address contents
	lda	testaddr
	pha
	sty	testaddr
	lda	testaddr & $7fff
	pha
	sty	testaddr & $7fff
	lda	testaddr & $3fff
	pha
	sty	testaddr & $3fff
; Reset address contents in all memory banks				
	ldx	#%11000000
	stx	ramexpctrl_hannes
	sty	testaddr
	ldx	#%11100000 ; this one turns on Csory expansion!
	stx	ramexpctrl_hannes
	sty	testaddr
	ldx	#%11110000
	stx	ramexpctrl_hannes
	sty	testaddr
	ldx	#%11111000
	stx	ramexpctrl_hannes
	sty	testaddr
	ldx	#%11111100
	stx	ramexpctrl_hannes
	sty	testaddr
	ldx	#%11111110
	stx	ramexpctrl_hannes
	sty	testaddr
	ldx	#%11111111
	stx	ramexpctrl_hannes
	sty	testaddr
	
; Set test byte at 64k RAM end
	lda	#$55
	sta	testaddr
; Detect 16k				
	cmp	testaddr & $3fff
	beq	+
	iny
; Detect 32k				
	cmp	testaddr & $7fff
	beq	+
; We have at least 64k				
	iny
	jsr	io_detmem_hannes
+	ldx	#%11111111
	stx	ramexpctrl_hannes
	inx
; -- commented out because most probably VICE Csory emulation is wrong - inverted default value!
;	stx	ramexpctrl_csory
	tya
	cpy	#3
	bcc	+
	ora	#%10000000 ; Signal Hannes expansion
+	sta	io_ramsize
	jsr	io_detmem_csory
	sty	io_detmemtemp
	lda	io_ramsize
	and	#%00111111
	cmp	io_detmemtemp
	bcs	+
	lda	io_detmemtemp
	ora	#%01000000
	sta	io_ramsize
+	pla
	sta	testaddr & $3fff
	pla
	sta	testaddr & $7fff
	pla
	sta	testaddr
	sta	ted_romen
	cli

	.if	io_prtstatus
	jsr	primm
	.null	" RAM size: "
	sei
	sta	ted_ramen
	lda	io_ramsize
	sta	ted_romen
	pha
	cli
	and	#%00111111
	asl
	tay
	ldx	io_ramsizes,y
	lda	io_ramsizes+1,y
	jsr	lnprt
	jsr	primm
	.null	"k"
	pla
	bpl	+
	jsr	primm
	.null	" (Hannes)"
;	bit	io_ramsize
;	bvc	+++
;	lda	#"+"
;	jsr	chrout
;+	bit	io_ramsize
	;bvc	+
;	jsr	primm
;	.null	"Csory"
;	jmp	++
;+	jsr	primm
;	.null	"stock"
+
;	lda	#")"
;	jsr	chrout
	lda	#13
	jsr	chrout
	.endif
	rts
	
; Detect Hannes expansion
; -----------------------
; Method: 
; 1) set a test pattern in highest possible memory bank 
; 2) test from lowest bank, increasing used address bits one by one
; 3) we are at highest bank present when we found our test pattern
; Attention! Address bits are inverted (control register defaults to $ff)  
 
io_detmem_hannes
; Set test byte in highest bank
	ldx	#%11000000
	stx	ramexpctrl_hannes
	lda	#$aa
	sta	testaddr
; Start search from first (default) bank
	ldx	#%11111111
	stx	ramexpctrl_hannes
	
	ldx	#6	; Number of available memory configurations (address bits)
-	cmp	testaddr
	beq	+
	asl	ramexpctrl_hannes
	iny
	dex
	bne	-
+	rts	

; Detect Csory expansion
; -----------------------
; Method: 
; 1) 
io_detmem_csory
	ldy	#0
	rts
io_detmemtemp
	.byte	0
	.if	io_prtstatus
io_ramsizes
	.word 16, 32, 64, 128, 256, 512, 1024, 2048, 4096
	.endif
