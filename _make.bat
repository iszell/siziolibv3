del *.d64
del *.prg

for %%i in ("loader_plus4_serial1bit" "loader_plus4_serial2bit" "loader_plus4_parallel" "loader_plus4_tcbm" "loader_drive_1bit1541" "loader_drive_2bit1541" "loader_drive_1bit1581" "loader_drive_parallel1541" "loader_drive_tcbm" "loader_drive_gijoe" "decrunch" "IOLibV3Test" "IOLibV3ExoTest" "createtestpattern" "demo") do (
	bin\64tass --ascii -o %%i.prg %%i.asm
)

for %%i in ("loader_plus4_serial1bit" "loader_plus4_serial2bit" "loader_plus4_parallel" "loader_plus4_tcbm" "loader_drive_1bit1541" "loader_drive_2bit1541" "loader_drive_1bit1581" "loader_drive_parallel1541" "loader_drive_tcbm" "loader_drive_gijoe" "decrunch") do (
	del %%i.prg
)

bin\64tass --ascii -o bitmap1exo.tmp bitmap1exo.asm
exomizer\3.0.1\exomizer.exe mem -f -o bitmap1exo.prg bitmap1exo.tmp
del bitmap1exo.tmp

bin\makedisk iolibv3test.d64 iolibv3test.mdc
start iolibv3test.d64
