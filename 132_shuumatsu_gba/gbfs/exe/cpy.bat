@echo off

rem ---------------------------------
rem ファイルを作業フォルダにコピー中

rmdir /s /q tmp 2> nul
mkdir tmp

copy GRAPHIC.DSK tmp > nul
copy scene.DSK tmp > nul
copy WIPE.DSK tmp > nul

copy GRAPHIC.PFT tmp > nul
copy scene.PFT tmp > nul
copy WIPE.PFT tmp > nul

copy DOM.adp tmp > nul
copy ido.adp tmp > nul
copy od_m.adp tmp > nul
copy OD_MO.adp tmp > nul
copy od_p.adp tmp > nul
copy OD_WC.adp tmp > nul
copy OD_WO.adp tmp > nul
copy paper.adp tmp > nul
copy paperbag.adp tmp > nul
copy sd_m.adp tmp > nul
copy sd_p.adp tmp > nul
copy TIMEBELL.adp tmp > nul
copy radio.adp tmp > nul
copy radionz.adp tmp > nul


