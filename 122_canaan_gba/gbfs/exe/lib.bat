@echo off

rmdir /s /q tmp 2> nul

for %%f in (*.CAT) do python ..\exe\lib\lib_unpak.py %%f %%~nf.LIB tmp
