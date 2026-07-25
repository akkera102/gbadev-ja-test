@echo off

rem ---------------------------------
rem ファイル有無の確認


echo check DIN_OP.DBL

if not exist DIN_OP.DBL goto err

echo check DIN_OP00.ST2

if not exist DIN_OP00.ST2 goto err

echo check SPRING.GI

if not exist SPRING.GI goto err


rem ---------------------------------
exit /b 0

rem ---------------------------------
:err
exit /b 1
