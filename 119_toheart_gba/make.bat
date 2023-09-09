@echo off

echo ---------------------------------
echo 　- 「To Heart」 Advance -
echo 　インストール　バッチ処理
echo ---------------------------------
pause

cd gbfs
cd data

rem ---------------------------------
call ..\exe\chk.bat
if %ERRORLEVEL% == 0 goto next

echo ※　指定されたファイルが違います。
echo 　　再度確認をお願いします。
pause
goto end

rem ---------------------------------
:next
call ..\exe\pak.bat
call ..\exe\dec.bat
call ..\exe\scn.bat
call ..\exe\snd.bat
call ..\exe\rom.bat

rem ---------------------------------
echo 　　終了しました。
pause

rem ---------------------------------
:end
cd ..