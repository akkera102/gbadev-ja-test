@echo off

cd tmp

rem ---------------------------------
rem アーカイブファイルを展開

..\..\exe\pak\tcdpak DATA.TCD

del DATA.TCD


cd ..
