@echo off

cd tmp

rem ---------------------------------
rem BMPに変換

..\..\exe\img\gi2bmp SPRING.GI

echo dbl2bmp... Cropping images, this may take 1 to 2 minutes.

..\..\exe\img\dbl2bmp DIN_OP.DBL > log.txt

del log.txt
del SPRING.GI
del DIN_OP.DBL


rem ---------------------------------
rem GBAで使用していないファイルを削除

del f00158.bmp
del f00176.bmp
del f00184.bmp
del f00210.bmp
del f00228.bmp
del f00254.bmp
del f00280.bmp
del f00298.bmp
del f00306.bmp
del f00324.bmp
del f00350.bmp
del f00376.bmp
del f00428.bmp
del f00446.bmp
del f00454.bmp
del f00480.bmp
del f00498.bmp
del f00524.bmp
del f01204.bmp
del f01686.bmp
del f02434.bmp
del f02442.bmp
del f02464.bmp
del f02472.bmp
del f02984.bmp
del f03624.bmp
del f03634.bmp
del f03730.bmp
del f03740.bmp
del f03762.bmp
del f03846.bmp
del f03868.bmp
del f03984.bmp
del f04044.bmp
del f04141.bmp
del f04434.bmp
del f04674.bmp
del f04684.bmp
del f04694.bmp
del f04704.bmp
del f04714.bmp
del f04724.bmp
del f04734.bmp
del f04744.bmp
del f04754.bmp
del f04764.bmp
del f04774.bmp
del f04784.bmp
del f04794.bmp
del f04804.bmp
del f04814.bmp
del f04824.bmp
del f04834.bmp
del f04906.bmp
del f05060.bmp
del f05072.bmp
del f05102.bmp
del f05110.bmp
del f05120.bmp
del f05128.bmp
del f05138.bmp
del f05256.bmp
del f05330.bmp
del f05668.bmp
del f05690.bmp
del f05766.bmp
del f05856.bmp
del f05866.bmp
del f05876.bmp
del f05888.bmp
del f05898.bmp
del f06262.bmp
del f06322.bmp
del f06388.bmp
del f06444.bmp
del f06736.bmp
del f07314.bmp
del f07320.bmp
del f07328.bmp
del f07334.bmp
del f07340.bmp
del f07346.bmp
del f07354.bmp
del f07360.bmp
del f07366.bmp
del f07372.bmp
del f07380.bmp
del f07386.bmp
del f07392.bmp
del f07398.bmp
del f07404.bmp
del f07412.bmp
del f07418.bmp
del f07424.bmp
del f07438.bmp
del f07444.bmp
del f07456.bmp
del f07464.bmp
del f07476.bmp
del f07488.bmp
del f07496.bmp
del f07508.bmp
del f07514.bmp
del f07528.bmp
del f07534.bmp
del f07546.bmp
del f07554.bmp
del f07566.bmp
del f07572.bmp
del f07578.bmp
del f07586.bmp
del f07598.bmp
del f07606.bmp
del f07618.bmp
del f07624.bmp
del f07638.bmp
del f07644.bmp
del f07670.bmp
del f07682.bmp
del f07692.bmp
del f07706.bmp
del f07712.bmp
del f07722.bmp
del f07742.bmp
del f07752.bmp
del f07784.bmp
del f07790.bmp
del f07866.bmp
del f07870.bmp
del f08180.bmp


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

ren SPRING.img f20000.img
ren SPRING.pal f20000.pal


cd ..
