; IOLibV3 by Siz of TBC
; (c) Siz, 2014.06.03
;
; Change log:
; 	2014.06.03: first touch
;	2015.04.27: implemented sound and memory size detection
;	2015.04.28: implemented drive type detection
;	2015.04.29: implemented drive interface type detection (except parallel)
;	2015.05.01: implemented parallel drive interface detection
;	2015.05.03: implemented loader selection
;	2015.05.06: added G.I. Joe loader definition for SD2IEC
;	2015.05.11: implemented G.I. Joe loader drive part (used for SD2IEC only!)
;	2015.05.15: serial 1 bit plus/4 loader (G.I. Joe) is done
;	2015.05.20: serial 1 bit 1581 loader is finally done (G.I. Joe loader is missing a SEI for read error condition)
;	2015.05.20: serial 1 bit 1541 loader basically G.I. Joe with the SEI fix
;	2015.05.23: implemented 1541 parallel and 1551 TCBM loader, drive code download fix
;	2015.08.14: bugfix in SID type detection when no SIDCard present
;	2016.04.02: exomizer decruncher during load
;	2016.09.06: modular architecture
;	2017.05.08: first public release (no code changes, added readme)
;	2017.05.10: dual 1551 fix

	.include	"plus4_io_map.inc"
	.include	"plus4kernal-table.inc"
	.include	"ted.inc"

io_detect
	.if	io_prtstatus
	jsr	primm
	.byte	14
	.text	"IOLibV3 by Siz of TBC (c) 2015"
	.byte	13
	.text	"Detecting hardware configuration..."
	.byte	13, 0
	.endif

	.if	io_needvideodetect
	jsr	io_det_video
	.endif
	.if	io_needmemdetect
	jsr	io_det_memsize
	.endif
	.if	io_needsounddetect
	jsr	io_det_sound
	.endif
	.if	io_needloader
	jsr	io_det_drive
	.endif
	rts

.if	io_needvideodetect
io_det_video
	.if	io_prtstatus
	jsr	primm
	.null	" Video standard: "
	lda	ted_ctrl2
	and	#%01000000
	lsr
	lsr
	lsr
	lsr
	tax
	ldy	#4
-	lda	io_vidnames,x
	jsr	chrout
	inx
	dey
	bne	-
	jsr	io_prtcr
	.endif
	rts

	.if	io_prtstatus
io_prtspc	lda	#" "
	jmp	chrout
io_prtcr	lda	#13
	jmp	chrout
	.endif

	.if	io_prtstatus
io_vidnames
	.text	"PAL NTSC"
	.endif
.endif
.if	io_needmemdetect
	.include	"detect_memory.inc"
.endif
.if	io_needsounddetect
	.include	"detect_sound.inc"
.endif
.if	io_needloader
	.include	"detect_drive.inc"
.endif
	.include	"iolib_init.inc"
