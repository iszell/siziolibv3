; Standard CBM 264 series I/O ports 
; ---------------------------------

cpu_dir		= $0
;  Bit Dir Expl.
;  7   In  Serial Data In (and PLUS/4: Cas Sense) (0=Low, 1=High)
;  6   In  Serial Clock In                        (0=Low, 1=High)
;  5   -   Not used (no pin-out on 7501/8501)     (N/A)
;  4   In  Cassette Read                          (0=Low, 1=High)
;  3   Out Cassette Motor                         (0=9VDC, 1=Off) (Inverted)
;  2   Out Serial ATN Out (and PLUS/4: User Port) (0=High, 1=Low) (Inverted)
;  1   Out Serial Clock Out, Cassette Write       (0=High, 1=Low) (Inverted)
;  0   Out Serial Data Out                        (0=High, 1=Low) (Inverted)
cpu_port		= $1

acia		= $fd00
acia_data		= acia + 0
; Read: status, Write: programmed reset (for any data)

;  Bit7    IRq (1: was)
;  Bit6    DSR
;  Bit5    DCD
;  Bit4    Transmit data register empty
;  Bit3    Receive data register full
;  Bit2    Overrun error
;  Bit1    Framing error
;  Bit0    Parity error
acia_status	= acia + 1
;  Bit7-5  Parity mode
;  Bit4    Echo on/off
;  Bit3-2  Transmitter controls
;  Bit1    Interrupt disable (1: disabled)
;  Bit0    Negated DTR
acia_command	= acia + 2
;  Bit7    Number of stop bits (0: 1, 1: depends on data length)
;  Bit6-5  Data length (0: 8bit, 1: 7bit, 2: 6bit, 3: 5bit)
;  Bit4    Receive clock source (0: external, 1: internal)
;  Bit3-0  Baud rate
acia_control	= acia + 3

pio_parport 	= $fd10
pio_keyboard 	= $fd30
rom_bank_latch 	= $fdd0
	
ted		= $ff00

; Expansions
; ----------

tcbm_8		= $fef0
tcbm_9		= $fec0
tcbm_data		= tcbm_9 + 0
;  Bit1    status 1
;  Bit0    status 0
tcbm_status	= tcbm_9 + 1
;  Bit7    DAV
;  Bit6    ACK
tcbm_handshake	= tcbm_9 + 2
; 1=out; 0=in
tcbm_data_dir	= tcbm_9 + 3
tcbm_status_dir	= tcbm_9 + 4
tcbm_handshake_dir	= tcbm_9 + 5
	
; Custom expansions
; -----------------

; Csory RAM expansion control 
; Bit 7-6: main memory window select (00: $0000, 01: $4000, 10: $8000, 11: $c000)
;     5-4: unused (avaliable for 1M RAM expansion) 
;     3-0: 16k memory bank select to display in main memory window (16x16k = 256k)
; See also Hannes control register bit 6 
; Default value: $00
ramexpctrl_csory	= $fd15
; Hannes RAM expansion control
; Bit   7: expansion memory switch bound: 0:$1000, 1:$4000
;       6: expansion disable for TED: 0: access only default bank (11), 
;                                     1: access like CPU
;          affects Csory expansion too 
;     5-4: activate Csory expansion with 01, other values switch it off
;          address bits 21-20 for 4M Hannes RAM expansion
;     3-2: unused
;          address bits 19-18 for 1M Hannes RAM expansion 
;     1-0: 64k memory bank select 
; Caution! Bits 1&0 are inverted!
; Default value: $ff
ramexpctrl_hannes	= $fd16

sid_solder	= $fd40
nae_control	= $fd80
sid_csory		= $fe80
