@echo off

echo ---------------------------------
echo 　- 「終末の過ごし方」 for GBA -
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
call ..\exe\eff.bat
call ..\exe\img.bat
call ..\exe\snd.bat
call ..\exe\scn.bat
call ..\exe\rom.bat

rem ---------------------------------
echo 終了しました。
pause

rem ---------------------------------
:end
cd ..
cd ..
