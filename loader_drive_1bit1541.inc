blk4job	= $04
blk4trk	= $0e
blk4sec	= $0f
drv0id1	= $12
drv0id2	= $13
bitbuff	= $14
hdrid1	= $16
hdrid2	= $17
retrycnt	= $8b

; serial bus bits are inverted!
; default value %00000000
;Bit  7   ATN IN
;Bits 6-5 Device address preset switches:
;           00 = #8, 01 = #9, 10 = #10, 11 = #11
;Bit  4   ATN acknowledge OUT
;Bit  3   CLOCK OUT
;Bit  2   CLOCK IN
;Bit  1   DATA OUT
;Bit  0   DATA IN
serialdata = $1800

ledport	= $1c00
ledvalue	= %00001000
ledinverted = 0

dirsect	= 1

blk4buf	= $0700

	.include	"loader_drive_core.inc"
	.include	"loader_drive_1bitserial.inc"

dirtrack	.byte	18