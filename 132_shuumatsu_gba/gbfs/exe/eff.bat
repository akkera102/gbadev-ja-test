@echo off

cd tmp

rem ---------------------------------
rem EFF��BMP�ɕϊ�

for %%i in (*.EFF) do ..\..\exe\eff\eff2bmp %%i

del *.EFF


rem ---------------------------------
rem ���T�C�Y�ƃo�C�i����

for %%i in (*.bmp) do python ..\..\exe\eff\eff_bin.py %%i

del *.bmp


rem ---------------------------------
rem �o�C�i�����Č���

python ..\..\exe\eff\eff_cat.py CLS01
python ..\..\exe\eff\eff_cat.py CLS02
python ..\..\exe\eff\eff_cat.py CLS03
python ..\..\exe\eff\eff_cat.py CLS10
python ..\..\exe\eff\eff_cat.py CLS90
python ..\..\exe\eff\eff_cat.py CLS91
python ..\..\exe\eff\eff_cat.py CLS92
python ..\..\exe\eff\eff_cat.py CLS93
python ..\..\exe\eff\eff_cat.py CLS94
python ..\..\exe\eff\eff_cat.py CLS95
python ..\..\exe\eff\eff_cat.py CLS96
python ..\..\exe\eff\eff_cat.py CLS97
python ..\..\exe\eff\eff_cat.py CLS98
python ..\..\exe\eff\eff_cat.py CLS99

del *.e01

cd ..


