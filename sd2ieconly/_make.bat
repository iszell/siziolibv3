del *.d64
del *.prg

for %%i in ("loader_plus4_serial1bit" "loader_drive_gijoe" "demo") do (
	..\bin\64tass --ascii -o %%i.prg %%i.asm	
)

for %%i in ("loader_plus4_serial1bit" "loader_drive_gijoe") do (
	del %%i.prg
)

..\bin\makedisk sd2iectest.d64 sd2iectest.mdc
start sd2iectest.d64
