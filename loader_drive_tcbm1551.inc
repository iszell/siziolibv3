cpuport  = $01

blk4job  = $06
blk4trk  = $10
blk4sec  = $11
drv0id1  = $14
drv0id2  = $15
retrycnt = $16
hdrid1   = $18
hdrid2   = $19

blk4buf  = $0700

tia      = $4000
padta    = tia
pbdta    = tia+1
pcdta    = tia+2
padir    = tia+3
pbdir    = tia+4
pcdir    = tia+5

ledport	= cpuport
ledvalue	= %00001000
ledinverted = 1

dirsect	= 1
serialdata = 0

	.include	"loader_drive_core.inc"
init	sei
	cld
        	lda #%11111111	;dir=output
        	sta padir
	lda pcdta
	and #%11110100	;ACK=0
	sta pcdta
-	bit pcdta		;DAV=1
	bmi -			;yes
	rts
writebyte  
-	bit pcdta      ;DAV=1?
	bpl -          ;no
	stx padta      ;put byte
	lda pcdta
	ora #%00001000
	sta pcdta      ;ACK=1
-	bit pcdta      ;DAV=1?
	bmi -          ;yes
	lda pcdta
	and #%11110111
	sta pcdta      ;ACK=0
	rts
readbyte
	inc padir
-	bit pcdta      ;DAV=1?
	bpl -          ;no
	lda padta      ;get byte
	pha
	lda pcdta
	ora #%00001000
	sta pcdta      ;ACK=1
-	bit pcdta      ;DAV=0?
	bmi -          ;yes
	lda pcdta
	and #%11110111
	sta pcdta      ;ACK=0
	dec padir
	pla
	rts
dirtrack	.byte	18
