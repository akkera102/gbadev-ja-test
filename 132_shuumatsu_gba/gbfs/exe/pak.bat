@echo off

cd tmp

rem ---------------------------------
..\..\exe\pak\dskpak scene.DSK scene.PFT SCF
..\..\exe\pak\dskpak GRAPHIC.DSK GRAPHIC.PFT KG
..\..\exe\pak\dskpak WIPE.DSK WIPE.PFT EFF

del scene.DSK > nul
del scene.PFT > nul
del GRAPHIC.DSK > nul
del GRAPHIC.PFT > nul
del WIPE.DSK > nul
del WIPE.PFT > nul


cd ..
