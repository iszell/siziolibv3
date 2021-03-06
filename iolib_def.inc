#importonce
.print("Siz IOLibV3 definitions")
.namespace iolib {
// IOLibV3 definitions to be included in programs where you use it

#if HAS_TED
.label	io_base		= $fc00
#else
.label	io_base		= $cf00
#endif
.label	io_data		= io_base-5
// Compress data to be loaded with "exomizer mem -f" command
// parameters: X: file name first byte, Y: file name second byte
.label	decrunch	= io_base - $190

// parameters: X: file name first byte, Y: file name second byte
.label	load		= io_base
.label	io_readbyte	= io_base + 3
.label	io_writebyte	= io_base + 6
.label	io_hardsync	= io_base + 9
.label	io_sync		= io_base + 12
.label	io_initloader	= io_base + 15

// Detected RAM size
// -----------------
// bit 0-4
//  0: 16k
//  1: 32k
//  2: 64k
//  3: 256k
//  4: 512k
//  5: 1024k
//  6: 2048k
//  7: 4096k
// bit 5
//  SideKick NeoRAM present
// bit 6
//  Hannes expansion present
// bit 7
// Csory expansion present
.label	io_ramsize	= io_data

// Type of sound source detected 
// -----------------------------
// bit 0: SID present
// bit 1: SID type (0: 6581, 1: 8580)
// bit 2: NAE controls present
// bit 3: AY (DIGIMUZ) present at $fd20
// bit 4: FM present at $fde2
// bit 5
// bit 6
// bit 7
.label	io_soundtype	= io_ramsize + 1

// Base address of detected SID
// ----------------------------
.label	io_sidbase	= io_soundtype + 1

.label	io_tcbmoffs	= io_sidbase + 2
}
