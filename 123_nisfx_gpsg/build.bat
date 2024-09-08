@echo off

cd tool/vgm2gba/
call _make_gpsg.bat
cd ../../

make quick

rem tool\\NanoBoyAdvance\\NanoBoyAdvance.exe _bin/test.gba
tool\\mGBA\\mGBA.exe _bin/test.gba