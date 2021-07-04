	.plugin "se.booze.kickass.CruncherPlugins"

	.encoding	"petscii_mixed"

	.disk [filename="testdisk.d64", name="IOLIBV3TEST", id="2021!" ]
	{
		[name="IOLIBV3TEST", type="prg", segments="iolibv3test" ],
		[name="IOLIBV3EXOTEST", type="prg", segments="iolibv3exotest" ],
		[name="TESTPATTERN", type="prg", segments="testdata" ],
		[name="E1", type="prg", segments="exotestdata" ]
	}

	.segment iolibv3test []
	* = $1001
	.import c64 "IOLibV3Test.prg"

	.segment iolibv3exotest []
	* = $1001
	.import c64 "IOLibV3ExoTest.prg"

	.segment testdata []
	* = $3000
	.for(var h=$30 ; h<$f0 ; h++) {
		.for(var l=0 ; l<256 ; l++) .byte l
	}

	.segment exotestdata []
	.modify ForwardMemExomizer($5800) {
		* = $5800
		.import c64 "dotctitle.bin"
	}
