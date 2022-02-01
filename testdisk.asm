	.plugin "se.booze.kickass.CruncherPlugins"

	.encoding	"petscii_mixed"

	.disk [filename="testdisk.d64", name="IOLIBV3TEST", id="2022!" ]
	{
		[name="DEMO", type="prg", segments="demo" ],
		[name="IOLIBV3TEST", type="prg", segments="iolibv3test" ],
		[name="IOLIBV3EXOTEST", type="prg", segments="iolibv3exotest" ],
		[name="TESTPATTERN", type="prg", segments="testdata" ],
		[name="B1", type="prg", segments="bitmapdata" ],
		[name="E1", type="prg", segments="bitmapexodata" ],
		[name="EXOTESTDATA", type="prg", segments="exotestdata" ],
		[name="HWDETECT PLUS/4", type="prg", segments="hwdetplus4" ],
		[name="HWDETECT C64", type="prg", segments="hwdetc64" ]
	}

	.segment demo []
.print "Demo"
	* = $1001
	.import c64 "demo.prg"

	.segment iolibv3test []
.print "IOLibV3 test"
	* = $1001
	.import c64 "iolibv3test.prg"

	.segment iolibv3exotest []
.print "IOLibV3 exomizer test"
	* = $1001
	.import c64 "iolibv3exotest.prg"

	.segment testdata []
.print "Test data"
	* = $3000
	.for(var h=$30 ; h<$f0 ; h++) {
		.for(var l=0 ; l<256 ; l++) .byte l
	}

	.segment bitmapdata []
.print "Test bitmap"
		* = $2000
		.import c64 "bitmap1.bin"

	.segment bitmapexodata []
.print "Test bitmap exomized"
	.modify ForwardMemExomizer($2000) {
		* = $2000
		.import c64 "bitmap1.bin"
	}

	.segment exotestdata []
.print "Test data exomized"
	.modify ForwardMemExomizer($5800) {
		* = $5800
		.import c64 "dotctitle.bin"
	}

	.segment hwdetplus4 []
.print "Hardware detect plus/4"
	* = $1001
	.import c64 "hwdetectplus4.prg"

	.segment hwdetc64 []
.print "Hardware detect C64"
	* = $1001
	.import c64 "hwdetect64.prg"
