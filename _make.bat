del *.d64
del *.prg

for %%i in ("loader_plus4_serial1bit" "loader_plus4_serial2bit" "loader_plus4_parallel" "loader_plus4_tcbm" "loader_drive_1bit1541" "loader_drive_2bit1541" "loader_drive_1bit1581" "loader_drive_parallel1541" "loader_drive_tcbm" "loader_drive_gijoe" "decrunch" "IOLibV3Test" "IOLibV3ExoTest" "createtestpattern") do (
	bin\64tass --ascii -o %%i.prg %%i.asm
)

bin\64tass --ascii -o demo.tmp demo.asm
exomizer\3.0.1\exomizer.exe sfx $100d -t 4 -o demo.prg demo.tmp
rem del demo.tmp
bin\64tass --ascii -o bitmap1exo.tmp bitmap1exo.asm
exomizer\3.0.1\exomizer.exe mem -f -o bitmap1exo.prg bitmap1exo.tmp
del bitmap1exo.tmp

for %%i in ("loader_plus4_serial1bit" "loader_plus4_serial2bit" "loader_plus4_parallel" "loader_plus4_tcbm" "loader_drive_1bit1541" "loader_drive_2bit1541" "loader_drive_1bit1581" "loader_drive_parallel1541" "loader_drive_tcbm" "loader_drive_gijoe" "decrunch") do (
	del %%i.prg %%.tmp
)

bin\cc1541 -f DEMO -w demo.prg -f IOLIBV3TEST -w IOLibV3Test.prg -f IOLIBV3EXOTEST -w IOLibV3ExoTest.prg -f B1 -w bitmap1.bin -f E1 -w bitmap1exo.prg -n IOLIBV3TEST -i IO32A iolibv3test.d64
bin\cc1541 -f DEMO -w demo.prg -f IOLIBV3TEST -w IOLibV3Test.prg -f IOLIBV3EXOTEST -w IOLibV3ExoTest.prg -f B1 -w bitmap1.bin -f E1 -w bitmap1exo.prg -n IOLIBV3TEST -i IO32A iolibv3test.d71
bin\cc1541 -f DEMO -w demo.prg -f IOLIBV3TEST -w IOLibV3Test.prg -f IOLIBV3EXOTEST -w IOLibV3ExoTest.prg -f B1 -w bitmap1.bin -f E1 -w bitmap1exo.prg -n IOLIBV3TEST -i IO32D iolibv3test.d81

start iolibv3test.d64
