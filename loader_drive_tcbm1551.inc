	.print	". 1551 TCBM loader"
	.namespace iolib {
	.namespace tcbm1551 {
	.pseudopc $0500 {

.var	drive_serial	= false
.var	ledinverted	= true

	#import	"loader_drive_core.inc"
.label	cpuport  = $01

.label	blk4job  = $06
.label	blk4trk  = $10
.label	blk4sec  = $11
.label	drv0id1  = $14
.label	drv0id2  = $15
.label	retrycnt = $16
.label	hdrid1   = $18
.label	hdrid2   = $19

.label	blk4buf  = $0700

.label	tia      = $4000
.label	padta    = tia
.label	pbdta    = tia+1
.label	pcdta    = tia+2
.label	padir    = tia+3
.label	pbdir    = tia+4
.label	pcdir    = tia+5

.label	ledport	= cpuport
.const	ledvalue = %00001000

.const	dirsect	= 1

	driveload(init, dirtrack, dirsect, blk4trk, blk4sec, blk4job, blk4buf, retrycnt, hdrid1, hdrid2, drv0id1, drv0id2, readbyte, writebyte, ledport, ledvalue, 0, drive_serial, ledinverted)

init:	sei
	cld
        lda #%11111111	//dir=output
        sta padir
	lda pcdta
	and #%11110100	//ACK=0
	sta pcdta
!:	bit pcdta	//DAV=1
	bmi !-		//yes
	rts
writebyte:
!:	bit pcdta	//DAV=1?
	bpl !-		//no
	stx padta	//put byte
	lda pcdta
	ora #%00001000
	sta pcdta	//ACK=1
!:	bit pcdta	//DAV=1?
	bmi !-		//yes
	lda pcdta
	and #%11110111
	sta pcdta	//ACK=0
	rts
readbyte:
	inc padir
!:	bit pcdta	//DAV=1?
	bpl !-		//no
	lda padta	//get byte
	pha
	lda pcdta
	ora #%00001000
	sta pcdta	//ACK=1
!:	bit pcdta	//DAV=0?
	bmi !-		//yes
	lda pcdta
	and #%11110111
	sta pcdta	//ACK=0
	dec padir
	pla
	rts

dirtrack:
	.byte	18

}
}
}
