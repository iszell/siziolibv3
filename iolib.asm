	.encoding	"petscii_mixed"

	.disk [filename="iolibv3test.d64", name="IOLIBV3TEST", id="2021!" ]
	{
		[name="IOLIBV3TEST", type="prg", segments="iolibv3test" ],
		[name="TESTPATTERN", type="prg", segments="testdata" ]
	}

	.segment iolibv3test []
	#import "IOLibV3Test.asm"

	.segment testdata []
	.import binary "testpattern.bin"
