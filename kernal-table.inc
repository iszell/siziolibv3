st	= $90

defkey	= $ff49
print	= $ff4c
primm	= $ff4f
monitor	= $ff52

vidinit	= $ff81
ioinit	= $ff84
ramtest	= $ff87
restorio	= $ff8a
; X/Y: user table address, C=0: copy user table to vectors, C=1: copy vectors to user table
vector	= $ff8d
setmsg	= $ff90
second	= $ff93
tksa	= $ff96
memtop	= $ff99
membot	= $ff9c
scnkey	= $ff9f
settmo	= $ffa2
iecin	= $ffa5
iecout	= $ffa8
untalk	= $ffab
unlisten	= $ffae
listen	= $ffb1
talk	= $ffb4
readst	= $ffb7
; A: logical file number, X: device number, Y: secondary address
setlfs	= $ffba
; A: length, X/Y: pointer to filename
setnam	= $ffbd
; must follow setlfs and setnam
open	= $ffc0
; A: logical file number to close
close	= $ffc3
; X: logical file number for input
chkin	= $ffc6
; X: logical file number for output
chkout	= $ffc9
; clear input/output channels and set them back to defaults
clrchans	= $ffcc
chrin	= $ffcf
chrout	= $ffd2
; A=0: load, A=1-255: verify, X/Y load address (if secondary address=0, otherwise file first two bytes)
load	= $ffd5
; A: zero page pointer number for start address, X/Y: end address+1
save	= $ffd8
settime	= $ffdb
readtim	= $ffde
stop	= $ffe1
getchar	= $ffe4
closeall	= $ffe7
udtime	= $ffea
scrnsize	= $ffed
plot	= $fff0
iobase	= $fff3
reset	= $fff6
