rm *.d64
rm *.prg

for i in "loader_plus4_serial1bit" "loader_plus4_serial2bit" "loader_plus4_parallel" "loader_plus4_tcbm" "loader_drive_1bit1541" "loader_drive_2bit1541" "loader_drive_1bit1581" "loader_drive_parallel1541" "loader_drive_tcbm" "loader_drive_gijoe" "decrunch" "IOLibV3Test" "IOLibV3ExoTest" "createtestpattern" ; do \
        64tass --ascii -l $i.lst -o $i.prg $i.asm \
; done

64tass --ascii -l demo.lst -o demo.tmp demo.asm
exomizer3.0.2 sfx basic -t 4 -o demo.prg demo.tmp
64tass --ascii -o bitmap1exo.tmp bitmap1exo.asm
exomizer3.0.2 mem -f -o bitmap1exo.prg bitmap1exo.tmp
rm bitmap1exo.tmp

for i in "loader_plus4_serial1bit" "loader_plus4_serial2bit" "loader_plus4_parallel" "loader_plus4_tcbm" "loader_drive_1bit1541" "loader_drive_2bit1541" "loader_drive_1bit1581" "loader_drive_parallel1541" "loader_drive_tcbm" "loader_drive_gijoe" "decrunch" ; do \
        rm $i.prg $i.tmp \
; done

echo "Buldling disk"

cc1541 -f demo -w demo.prg -f iolibv3test -w IOLibV3Test.prg -f iolibv3exotest -w IOLibV3ExoTest.prg -f b1 -w bitmap1.bin -f e1 -w bitmap1exo.prg -f testpattern -w testpattern.bin -n iolibv3test -i io32a iolibv3test.d64
cc1541 -f demo -w demo.prg -f iolibv3test -w IOLibV3Test.prg -f iolibv3exotest -w IOLibV3ExoTest.prg -f b1 -w bitmap1.bin -f e1 -w bitmap1exo.prg -f testpattern -w testpattern.bin -n iolibv3test -i io32a iolibv3test.d71
cc1541 -f demo -w demo.prg -f iolibv3test -w IOLibV3Test.prg -f iolibv3exotest -w IOLibV3ExoTest.prg -f b1 -w bitmap1.bin -f e1 -w bitmap1exo.prg -f testpattern -w testpattern.bin -n iolibv3test -i io32d iolibv3test.d81
