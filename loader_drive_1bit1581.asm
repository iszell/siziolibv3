blk4job	= $06
blk4trk	= $13
blk4sec	= $14
drv0id1	= $1d
drv0id2	= $1e
bitbuff	= $5e
hdrid1	= $1d
hdrid2	= $1e
retrycnt	= $5f

; serial bus bits are inverted!
; default value %01010000
; Bit 7 ATN IN
; Bit 6 0 = Write protect active
; Bit 5 Data Direction of the Bus Driver (FSM)
;         0 = Input, 1 = Output
; Bit 4 automatic ATN-Response
; Bit 3 CLOCK OUT
; Bit 2 CLOCK IN
; Bit 1 DATA OUT
; Bit 0 DATA IN

serialdata = $4001

ledport	= $4000
ledvalue	= %00100000
ledinverted = 0

blk4buf	= $0700

dirsect	= 3
dirtrack	= $022b

	.include	"loader_drive_core.inc"
	.include	"loader_drive_1bitserial.inc"
