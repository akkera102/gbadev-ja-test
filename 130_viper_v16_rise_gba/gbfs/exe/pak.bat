@echo off

cd tmp

rem ---------------------------------
..\..\exe\pak\sgspak SGS.DAT

move ANM\*.ANM .  > nul
move PCM\*.PCM .  > nul
move PCMSE\*.PCM . > nul

rmdir /s /q ANM 2> nul
rmdir /s /q PCM 2> nul
rmdir /s /q PCMSE 2> nul

del SGS.DAT  > nul

cd ..
