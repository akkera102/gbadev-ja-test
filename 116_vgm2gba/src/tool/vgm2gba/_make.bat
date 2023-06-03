@echo off

for %%f in (*.vgm) do (
	vgm2gba.exe %%f
) 

pause
