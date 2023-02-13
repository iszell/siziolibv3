	#import	"plus4_basic_header.inc"
	#import	"plus4_kernal_table.inc"
	#import	"ted.inc"

	jsr	iolib.detect
	lda	iolib.drivedetect.io_drivetyp
	bne	!+
	beq quit
!:	jsr	iolib.init
	bcc !+
quit:
	jmp $fff6
!:  jmp $5555

.namespace iolib {
	.label	io_tcbmoffs	= $0700
	.label	io_base		= $0701
	.label  io_bitbuff	= $b7
	.label  io_loadptr  = $9e
	#define need_loader
}
#define skip_default_definitions
#import "iolib.inc"

