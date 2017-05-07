; TED registers 

ted_timer1lo	= ted + $00
ted_timer1hi	= ted + $01
ted_timer2lo	= ted + $02
ted_timer2hi	= ted + $03
ted_timer3lo	= ted + $04
ted_timer3hi	= ted + $05

;  Bit7    TEST Internal TED Test    (Should be always 0)
;  Bit6    ECM  Enhanced color mode  (0=Normal, 1=Extended)
;  Bit5    BMM  Bitmap mode          (0=Text, 1=Bitmap)
;  Bit4    DEN  Display Enable       (0=Blank/Border Color, 1=Display Enable)
;  Bit3    RSEL 24/25 rows screen    (0=24 Rows, 1=25 Rows)
;  Bit2-0  Y2-0 Vertical smooth-scrolling
ted_ctrl1		= ted + $06

;  Bit7         Reverse Mode  (0=Reverse/128 Chars, 1=No Reverse/256 Chars)
;               If 0, higmost char-bit tells if char should appear in inverse.
;  Bit6    NTSC Select Video Format  (0=PAL, 1=NTSC) (Don't change!)
;  Bit5    RES  TED stop. If set, the TED stops it's counters and
;               screen-generating, only single clock and refresh
;               cycles remain.  PROJECT 64: Flashing (0=Yes, 1=No)
;  Bit4    MCM  Multicolor mode      (0=Normal, 1=Multicolor)
;  Bit3    CSEL 40/38 columns screen (0=38 Columns, 1=40 Columns)
;  Bit2-0  X2-0 Horizontal smooth-scrolling
ted_ctrl2		= ted + $07
ted_keyblatch	= ted + $08

;  Bit7  Set on Any-Enabled-IRQ Condition  (0=None, 1=IRQ)
;  Bit6  Timer 3 Interrupt Request         (0=None, 1=IRQ / Acknowledge)
;  Bit5  Unused
;  Bit4  Timer 2 Interrupt Request         (0=None, 1=IRQ / Acknowledge)
;  Bit3  Timer 1 Interrupt Request         (0=None, 1=IRQ / Acknowledge)
;  Bit2  Lightpen Interrupt Request        (Not implemented?)
;  Bit1  Raster Interrupt Request          (0=None, 1=IRQ / Acknowledge)
;  Bit0  Unused
ted_irqsource	= ted + $09

;  Bit7  Unused
;  Bit6  Timer 3 Interrupt        (0=Disable, 1=Enable)
;  Bit5  Unused
;  Bit4  Timer 2 Interrupt        (0=Disable, 1=Enable)
;  Bit3  Timer 1 Interrupt        (0=Disable, 1=Enable)
;  Bit2  Lightpen Interrupt       (Not implemented?)
;  Bit1  Raster Interrupt         (0=Disable, 1=Enable)
;  Bit0  High bit of Raster FF0Bh (see there)
ted_irqmask	= ted + $0a
ted_rasterirqline	= ted + $0b
ted_cursorhi	= ted + $0c
ted_cursorlo	= ted + $0d
ted_voice1lo	= ted + $0e
ted_voice2lo	= ted + $0f
ted_voice1hi	= ted + $10

;  Bit7    D/A mode.
;  Bit6    Sound #2 noise on/off. If You set both, the square will sound.
;  Bit5    Sound #2 squarewave on/off.
;  Bit4    Sound #1 squarewave on/off.
;  Bit0-3  Volume. Maximum value is 8.
ted_soundctrl	= ted + $11

;  Bit7-6  Unused
;  Bit5-3  Bitmap Base Address      (in 8K steps) (ROM/RAM see FF12h.Bit2)
;  Bit2    Character/Bitmap ROM/RAM (0=RAM, 1=ROM) (Address see FF13h.Bit7-2)
;  Bit1-0  Sound 2 Frequency MSB    (see Sound chapter)
ted_bitmapctrl	= ted + $12

;  Bit7-2  Character Base Address (in 1K steps) (ROM/RAM see FF12h.Bit2)
;  Bit1    Force single clock mode (0=double, 1=single)
;  Bit0    Memory State READ ONLY (0=RAM, 1=ROM) (change via FF3Eh/FF3Fh)
ted_charsetaddr	= ted + $13

;  Bit7-3  Video-ram Base Address (in 2K steps) (ROM/RAM see FF3Eh/FF3Fh)
;  Bit2-0  Unused
ted_screenaddr	= ted + $14
ted_background	= ted + $15
ted_color1	= ted + $16
ted_color2	= ted + $17
ted_color3	= ted + $18
ted_border	= ted + $19

; Bit7-3   Unused
; Bit1-0   Current character position MSB
ted_currcharhi	= ted + $1a
; Bit7-0   Current character position LSB
ted_currcharlo	= ted + $1b

; Bit7-1   Unused
; Bit0     MSB of register $1d
ted_rasterlinehi	= ted + $1c
ted_rasterline	= ted + $1d
ted_rastercolumn	= ted + $1e

;  Bit7    Unused
;  Bit6-3  Flashing counter. It's value increases with every
;             frame, and TED fits it's flashing feature to this
;             register's reaching to 15.
;  Bit2-0  Actual vertical scanning-line in a character-row (R/W!)
ted_chrscanline	= ted + $1f

ted_romen		= ted + $3e
ted_ramen		= ted + $3f
