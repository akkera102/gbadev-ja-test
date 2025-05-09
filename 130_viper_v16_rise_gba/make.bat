@echo off

echo ---------------------------------
echo 　- 「Viper V16 RISE」 for GBA -
echo 　インストール　バッチ処理
echo ---------------------------------

cd gbfs
cd data

rem ---------------------------------
call ..\exe\chk.bat
if %ERRORLEVEL% == 0 goto next

echo ※　指定されたファイルまたはフォルダが違います。再度確認をお願いします。
pause
goto end

rem ---------------------------------
:next

echo ゲームデータの確認ができました。インストールを続行します。
pause

call ..\exe\cpy.bat
call ..\exe\pak.bat
call ..\exe\img.bat
call ..\exe\snd.bat
call ..\exe\txt.bat
call ..\exe\rom.bat

rem ---------------------------------
echo 終了しました。
pause

rem ---------------------------------
:end
cd ..
cd ..
