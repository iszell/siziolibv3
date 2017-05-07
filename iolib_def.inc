; IOLibV3 definitions to be included in programs where you use it

io_base		= $fc00
io_data		= io_base-5
; Compress data to be loaded with "exomizer mem -f" command
; parameters: X: file name first byte, Y: file name second byte
io_decrunch	= io_base - $180

; parameters: X: file name first byte, Y: file name second byte
io_load		= io_base
io_readbyte	= io_base + 3
io_writebyte	= io_base + 6
io_hardsync	= io_base + 9
io_sync		= io_base + 12
io_initloader	= io_base + 15

; Detected RAM size
; -----------------
; bit 0-5
;  0: 16k
;  1: 32k
;  2: 64k
;  3: 256k
;  4: 512k
;  5: 1024k
;  6: 2048k
;  7: 4096k
; bit 6
;  Hannes expansion present
; bit 7
; Csory expansion present

io_ramsize	= io_data

; Type of sound source detected 
; -----------------------------
; $00: TED only
; $01: Legacy SIDCard SID 6581
; $02: Legacy SIDCard SID 8580
; $81: NAE SID 6581
; $82: NAE SID 8580
io_soundtype	= io_ramsize + 1
; Base address of detected SID
; ----------------------------
io_sidbase	= io_soundtype + 1
io_tcbmoffs	= io_sidbase + 2
