@echo off

cd tmp

rem ---------------------------------
rem トリミングと256色に変換

for %%i in (*.bmp) do (
    python ..\..\exe\img\img_cut.py %%i
)

del *.bmp


rem ---------------------------------
rem GBA(mode4)に変換

for %%i in (*.png) do (
    echo grit... %%i
    ..\..\exe\img\grit %%i -g -gB8 -gb -ftb -fh!
)

del *.png


rem ---------------------------------
rem lz圧縮

for %%i in (*.img.bin) do (
    echo gbalzss... %%i
    ..\..\exe\img\gbalzss e %%i %%~ni
)

for %%i in (*.pal.bin) do (
    echo gbalzss... %%i
    ..\..\exe\img\gbalzss e %%i %%~ni
)

del *.img.bin
del *.pal.bin


rem ---------------------------------
rem リネーム

ren SPRING.img f8400.img
ren SPRING.pal f8400.pal


cd ..
