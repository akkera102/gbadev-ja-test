@echo off
set PATH=C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%

cd data

gbfs ..\test.gbfs *.bin


echo done!
pause
