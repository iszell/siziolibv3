call bin\ka iolibv3test.asm
call bin\ka iolibv3exotest.asm
call bin\ka demo.asm
call bin\ka -define prtstatus -o init.tmp init.asm
exomizer\3.1.1\exomizer sfx basic -t 4 -n -s "lda $ae pha" -f "pla sta $ae" -o init.prg init.tmp
call bin\ka -o init.tmp init.asm
exomizer\3.1.1\exomizer sfx basic -t 4 -n -s "lda $ae pha" -f "pla sta $ae" -o initquiet.prg init.tmp
call bin\ka hwdetectplus4.asm
call bin\ka hwdetect64.asm
call bin\ka testdisk.asm

start testdisk.d64
