	#import	"plus4_basic_header.inc"
	#import	"plus4_io_map.inc"
	#import	"ted.inc"
	#import	"plus4_kernal_table.inc"

	.encoding	"petscii_mixed"
	
	jsr	iolib.detect
	lda	iolib.drivedetect.io_drivetyp
	bne	!+
	rts
!:	jsr	iolib.init
	jsr	primm
	.byte	13
	.text	"Loading..."
	.byte	13, 0

	sei
	sta	ted.ramen
	ldx	#23
!:	lda	bootcode,x
	sta	$fe8,x
	dex
	bpl	!-
	ldx	#'i'
	ldy	#'i'
	jmp	$fe8

bootcode: .pseudopc $fe8 {
	jsr	iolib.decrunch
	sta	ted.romen
	cli
	bcs	error
	jmp	$100d
	
error:	lda	#$32
	sta	ted.border
	rts
}

.namespace iolib {
	#define	prtstatus
	#define need_video_detect
	#define need_memory_detect
	#define need_sound_detect
	#define need_loader
	#define need_exodecrunch
}
#import "iolib.inc"
