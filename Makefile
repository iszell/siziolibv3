CC1541			= cc1541
EXOMIZER		= exomizer
EXOMIZERSFXOPTS	= sfx basic -t 4 -n -s "lda 174 pha" -f "pla sta 174"
EXOMIZERMEMOPTS	= mem -f
KICKASS			= java -jar $(KICKASSPATH)/KickAss.jar
KICKASSOPTS		= -showmem -symbolfile

SRCS = $(wildcard *.asm)
PRGS = $(SRCS:.asm=.prg)

all: testdisk.d64 testdisk.d71 testdisk.d81 init.prg initquiet.prg stripped.prg

clean:
	$(RM) *.prg *.lst *.d?? *.tmp *.sym

%.prg: %.asm *.inc
	$(KICKASS) $(KICKASSOPTS) -o $@.tmp $<
	$(EXOMIZER) $(EXOMIZERSFXOPTS) -o $@ $@.tmp

bitmapexodata.prg: bitmap1.bin
	$(EXOMIZER) $(EXOMIZERMEMOPTS) -o $@ $<

demo.prg: demo.asm *.inc
	$(KICKASS) $(KICKASSOPTS) -o $@ demo.asm

hwdetect64.prg: hwdetect64.asm *.inc
	$(KICKASS) $(KICKASSOPTS) -define prtstatus -o $@.tmp hwdetect64.asm
	$(EXOMIZER) sfx basic -t 64 -n -o $@ $@.tmp

init.prg: init.asm *.inc
	$(KICKASS) $(KICKASSOPTS) -define prtstatus -o $@.tmp init.asm
	$(EXOMIZER) $(EXOMIZERSFXOPTS) -o $@ $@.tmp

initquiet.prg: init.asm *.inc
	$(KICKASS) $(KICKASSOPTS) -o $@.tmp init.asm
	$(EXOMIZER) $(EXOMIZERSFXOPTS) -o $@ $@.tmp

exotestdata.prg: dotctitle.bin
	$(EXOMIZER) $(EXOMIZERMEMOPTS) -o $@ $<

stripped.prg: stripped.asm
	$(KICKASS) $(KICKASSOPTS) -o $@ stripped.asm

strippedtest.prg: strippedtest.asm stripped.asm
	$(KICKASS) $(KICKASSOPTS) -o $@ strippedtest.asm

testfile.prg: testfile.asm
	$(KICKASS) $(KICKASSOPTS) -o $@ testfile.asm

testdata.prg: testdata.asm
	$(KICKASS) $(KICKASSOPTS) -o $@ testdata.asm

testdisk.d64 testdisk.d71 testdisk.d81: $(PRGS) exotestdata.prg bitmapexodata.prg
	$(CC1541) \
		-n "iolibv3test" \
		-f demo -w demo.prg \
		-f iolibv3test -w iolibv3test.prg \
		-f iolibv3exotest -w iolibv3exotest.prg \
		-f b1 -w bitmap1.bin \
		-f e1 -w bitmapexodata.prg \
		-f testdata -w testdata.prg \
		-f exotestdata -w exotestdata.prg \
		-f "hwdetect plus/4" -w hwdetectplus4.prg \
		-f "hwdetect 64" -w hwdetect64.prg \
		-f "stripped loader" -w strippedtest.prg \
		$@
