@echo off

rem SGS.DAT���m�F

echo check file... SGS.DAT
if not exist SGS.DAT goto err


rem ---------------------------------
exit /b 0

rem ---------------------------------
:err
exit /b 1

