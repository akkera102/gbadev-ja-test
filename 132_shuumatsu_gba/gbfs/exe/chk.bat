@echo off

rem ---------------------------------
rem ファイル有無の確認


echo check DSK files...

if not exist GRAPHIC.DSK goto err
if not exist scene.DSK goto err
if not exist WIPE.DSK goto err

echo check PFT files...

if not exist GRAPHIC.PFT goto err
if not exist scene.PFT goto err
if not exist WIPE.PFT goto err

echo check adp files...

if not exist DOM.adp goto err
if not exist ido.adp goto err
if not exist od_m.adp goto err
if not exist OD_MO.adp goto err
if not exist od_p.adp goto err
if not exist OD_WC.adp goto err
if not exist OD_WO.adp goto err
if not exist paper.adp goto err
if not exist paperbag.adp goto err
if not exist sd_m.adp goto err
if not exist sd_p.adp goto err
if not exist TIMEBELL.adp goto err
if not exist radio.adp goto err
if not exist radionz.adp goto err


rem ---------------------------------
exit /b 0

rem ---------------------------------
:err
exit /b 1
