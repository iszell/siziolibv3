// IOLibV3 by Siz of ~TBC~ Absence
// (c) Siz, 2014.06.03
//
// Change log:
// 	2014.06.03: first touch
//	2015.04.27: implemented sound and memory size detection
//	2015.04.28: implemented drive type detection
//	2015.04.29: implemented drive interface type detection (except parallel)
//	2015.05.01: implemented parallel drive interface detection
//	2015.05.03: implemented loader selection
//	2015.05.06: added G.I. Joe loader definition for SD2IEC
//	2015.05.11: implemented G.I. Joe loader drive part (used for SD2IEC only!)
//	2015.05.15: serial 1 bit plus/4 loader (G.I. Joe) is done
//	2015.05.20: serial 1 bit 1581 loader is finally done (G.I. Joe loader is missing a SEI for read error condition)
//	2015.05.20: serial 1 bit 1541 loader basically G.I. Joe with the SEI fix
//	2015.05.23: implemented 1541 parallel and 1551 TCBM loader, drive code download fix
//	2015.08.14: bugfix in SID type detection when no SIDCard present
//	2016.04.02: exomizer decruncher during load
//	2016.09.06: modular architecture
//	2017.05.08: first public release (no code changes, added readme)
//	2017.05.10: dual 1551 fix
//	2020.05.30: change copyright message
//	2021.06.17: migrate sources to KickAss

	#import "iolib_def.inc"

	.print	"Siz IOLibV3 startup code"

	.namespace iolib {
	.encoding	"petscii_mixed"

detect:
	#if	prtstatus
	jsr	primm
	.byte	14
	.text	"IOLibV3 by Siz of Absence (c) 2021"
	.byte	13
	.text	"Detecting hardware configuration..."
	.byte	13, 0
	#endif

	#if	need_video_detect
	jsr	detect_video
	#endif
	#if	need_memory_detect
	jsr	detect_memsize
	#endif
	#if	need_sound_detect
	jsr	detect_sound
	#endif
	jsr	detect_drive
	rts

#if	need_video_detect
	.print	". video standard detection"
detect_video:
{
#if	HAS_TED
	#if	prtstatus
	jsr	primm
	.text	" Video standard: "
	.byte	0
	lda	ted.ctrl2
	and	#%01000000
	lsr
	lsr
	lsr
	lsr
	tax
	ldy	#4
!:	lda	vidnames,x
	jsr	chrout
	inx
	dey
	bne	!-
	jsr	prtcr
	#endif
#endif
	rts

	#if	prtstatus
vidnames:
	.text	"PAL NTSC"
	#endif
}
#endif
	#if	prtstatus
prtspc:	lda	#' '
	jmp	chrout
prtcr:	lda	#13
	jmp	chrout
	#endif

#if	need_memory_detect
	#import	"detect_memory.inc"
#endif
#if	need_sound_detect
	#import	"detect_sound.inc"
#endif
	#import	"detect_drive.inc"
 	#import	"iolib_init.inc"
}
