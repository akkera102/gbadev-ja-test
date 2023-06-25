@echo off
set PATH=C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%

for %%f in (*.gbs) do (
	gbs2gba.exe %%f
) 

gbfs ..\..\test.gbfs *.bin


echo done!
pause
