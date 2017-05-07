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
serialport = $1800
parport	= $1801
pardir	= $1803
serialdata = 0

ledport	= $1c00
ledvalue	= %00001000
ledinverted = 0

dirsect	= 1

blk4buf	= $0700

	.include	"loader_drive_core.inc"

init     sei
         cld
         lda #%11111111
         sta pardir
         lda #%00000100 ;CLK=0?
-        bit serialport
         beq -          ;yes
         ldx #%00000010
         stx serialport
-        bit serialport
         bne -          ;no
         rts

writebyte  lda #%00000100        ;CLK=0?
-        bit serialport
         beq -          ;yes
         stx parport      ;put byte
         lda #%00000000 ;CLK=0,DATA=0
         sta serialport
         lda #%00000100 ;CLK=1?
-        bit serialport
         bne -          ;no
         lda #%00000010 ;CLK=0,DATA=1
         sta serialport
         rts

readbyte inc pardir
         lda #%00000100 ;CLK=0?
-        bit serialport
         beq -          ;yes
         lda parport      ;get byte
         pha
         lda #%00000000 ;CLK=0,DATA=0
         sta serialport
         lda #%00000100 ;CLK=0?
-        bit serialport
         bne -          ;no
         lda #%00000010
         sta serialport      ;CLK=0,DATA=1
         dec pardir
         pla
         rts

dirtrack	.byte	18
