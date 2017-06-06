# siziolibv3: Siz's I/O library v3

1. Introduction
---------------
The IOLibV3 is a modular hardware detection and IRq loader framework for the
Commodore 264 series of computers.
Main goal of development was to create a totally asynchronous loader system
that can be used together with any IRq handlers and is compatible with as many
drive types as possible.

Loader features:
----------------
- file name based (first two characters of name are checked)
  * you can load files in any order
  * you can load files from an SD2IEC directory natively
- IRq loader
  * you can interrupt loading any time
- uses serial protocol based on number of serial drives detected
  * TODO: currently only the multi-drive protocol is implemented
  * for parallel and TCBM interfaces the number of drives is not important
- DOS compatible, sector based (NOT A TRACKLOADER)
  * this ensures compatiblity with non-GCR drives
  * not so fast

2. Modules
----------
All functionality of the library is divided into modules. All modules can be
included/excluded using compilation options.
List of modules:
1. Hardware detection (mandatory)
2. Detailed status report of detected hardware (for debugging purposes)
3. Video standard detection
4. Memory size detection
5. Sound source detection
6. Loader (includes drive type detection)
7. On-the-fly Exomizer decruncher

2.1 Hardware detection
----------------------
Executes all included detection modules.

2.2 Detection status report
---------------------------
All hardware detection modules can report what they found via standard chrout
printing to screen (lower case characters). This can be totally switched off
to avoid printing the obvious and to save memory and disk space.

2.3 memory size detection
-------------------------
Detects available RAM size:
- 16k
- 32k
- 64k
- 128k  (Hannes)
- 256k  (Hannes/Csory)
- 512k  (Hannes)
- 1024k (Hannes)
- 2048k (Hannes)
- 4096k (Hannes)
 
2.4 Video standard detection
----------------------------
Based on TED control register #2 ($ff07) bit 6.
(Yeah, it's simple, mostly for reporting)
 
2.5 Sound source detection
--------------------------
Detects if a SID card is plugged in, the SID chip type (6581/8580) and if the
card is an NST Audio Extension (BSz SID Card).

2.6 Loader
----------
Detects devices connected to the computer from #4 to #31.
First executes a drive ROM read and tries to identify the drive type. If that
fails it will execute a UI command to get the initialization status message
from the drive and uses that to look up drive type.

Drive types supported:
- Commodore 1540
- Commodore 1541
- Commodore 1541C
- Commodore 1541-II
- Commodore 1551
- Commodore 1570
- Commodore 1571
- Commodore 1581
- RF501C
- SD2IEC

After the drive type is identified it will detected the interface used to
connect the drive to the computer in the following order
- TCBM (1551)
- parallel (154*)
- serial (154*, 157*, 158*, RF501C, SD2IEC)

2.7 Exomizer decruncher
-----------------------
There is a module for unpacking Exomizer packed files on-the-fly. To use this
feature you have to start exomizer with "mem -f" options.

3. Usage
--------
In the included IOLibV3Test.asm source you can see an example how to use the
library.
Basically you have to create an initialization part that detects hardware and
installs loader. In this init part you have to include two sources:
- iolib_def.inc: definitions for the library. This is required for all programs
  where you want to use the library
- iolib.inc: the library itself. It can be compiled to any memory location
You also have to define which modules needed. For example:
io_prtstatus = 1
io_needmemdetect = 1
io_needvideodetect = 1
io_needsounddetect = 1
io_needloader = 1
io_needdecrunch = 0

You have to call two functions:
- io_detect to do hardware detection
- io_init to initialize the loader. This will install the loader from $fc00-$fcff
  with some variables from $fbfb-fbff.
  If you use exomizer decruncher it will occupy $fa80-$bfa.

After that you only have to do the following in your parts:
- include iolib_def.inc
- call io_load or io_decrunch with first character of file name in XR and second
  one in YR

For variables set by detection check the contents of iolib_def.inc.

Memory used:
- $02/$03 (init only)
- $9e/$9f (during non-exomizer load)
- $a7, $ae/$af, $fc-$ff (exomizer decruncher)
- $b7 (during serial load)
- $ff40-$ffdc (exomizer decruncher)
