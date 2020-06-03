del *.d64
del *.prg

for %%i in ("loader_plus4_serial1bit" "loader_plus4_serial2bit" "loader_plus4_parallel" "loader_plus4_tcbm" "loader_drive_1bit1541" "loader_drive_2bit1541" "loader_drive_1bit1581" "loader_drive_parallel1541" "loader_drive_tcbm" "loader_drive_gijoe" "decrunch" "IOLibV3Test" "IOLibV3ExoTest" "createtestpattern") do (
	bin\64tass --ascii -l %%i.lst -o %%i.prg %%i.asm
)

bin\64tass --ascii -l demo.lst -o demo.tmp demo.asm
exomizer\3.0.1\exomizer.exe sfx basic -t 4 -o demo.prg demo.tmp
rem del demo.tmp
bin\64tass --ascii -o bitmap1exo.tmp bitmap1exo.asm
exomizer\3.0.1\exomizer.exe mem -f -o bitmap1exo.prg bitmap1exo.tmp
del bitmap1exo.tmp

for %%i in ("loader_plus4_serial1bit" "loader_plus4_serial2bit" "loader_plus4_parallel" "loader_plus4_tcbm" "loader_drive_1bit1541" "loader_drive_2bit1541" "loader_drive_1bit1581" "loader_drive_parallel1541" "loader_drive_tcbm" "loader_drive_gijoe" "decrunch") do (
	del %%i.prg %%i.tmp
)

bin\cc1541 -f demo -w demo.prg -f iolibv3test -w iolibv3test.prg -f iolibv3exotest -w iolibv3exotest.prg -f b1 -w bitmap1.bin -f e1 -w bitmap1exo.prg -f testpattern -w testpattern.bin -n iolibv3test -i io32a iolibv3test.d64
bin\cc1541 -f demo -w demo.prg -f iolibv3test -w iolibv3test.prg -f iolibv3exotest -w iolibv3exotest.prg -f b1 -w bitmap1.bin -f e1 -w bitmap1exo.prg -f testpattern -w testpattern.bin -n iolibv3test -i io32a iolibv3test.d71
bin\cc1541 -f demo -w demo.prg -f iolibv3test -w iolibv3test.prg -f iolibv3exotest -w iolibv3exotest.prg -f b1 -w bitmap1.bin -f e1 -w bitmap1exo.prg -f testpattern -w testpattern.bin -n iolibv3test -i io32d iolibv3test.d81

start iolibv3test.d64
