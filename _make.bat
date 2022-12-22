@rem Cleanup
del *.prg
del *.lst
del *.d??
del *.tmp

@rem Make programs
call bin\ka -bytedumpfile iolibv3test.lst iolibv3test.asm
call bin\ka -bytedumpfile iolibv3exotest.lst iolibv3exotest.asm
call bin\ka -bytedumpfile demo.lst demo.asm
call bin\ka -bytedumpfile      init.lst -define prtstatus -o init.tmp init.asm
exomizer\3.1.1\exomizer sfx basic -t 4 -n -s "lda $ae pha" -f "pla sta $ae" -o      init.prg init.tmp
call bin\ka -bytedumpfile initquiet.lst                   -o init.tmp init.asm
exomizer\3.1.1\exomizer sfx basic -t 4 -n -s "lda $ae pha" -f "pla sta $ae" -o initquiet.prg init.tmp
call bin\ka -bytedumpfile hwdetectplus4.lst hwdetectplus4.asm
call bin\ka -bytedumpfile hwdetect64.lst hwdetect64.asm
call bin\ka testdata.asm
exomizer\3.1.1\exomizer mem -f -o bitmapexodata.prg bitmap1.bin
exomizer\3.1.1\exomizer mem -f -o exotestdata.prg dotctitle.bin

@rem make disks
call bin\ka testdisk.asm
for %%i in (d64 d71 d81) do (
bin\cc1541 -n "iolibv3test"^
 -f demo -w demo.prg^
 -f iolibv3test -w iolibv3test.prg^
 -f iolibv3exotest -w iolibv3exotest.prg^
 -f b1 -w bitmap1.bin^
 -f e1 -w bitmapexodata.prg^
 -f testdata -w testdata.prg^
 -f exotestdata -w exotestdata.prg^
 -f "hwdetect plus/4" -w hwdetectplus4.prg^
 -f "hwdetect 64" -w hwdetect64.prg^
 testdisk.%%i
)

@rem start test disk
start testdisk.d64
