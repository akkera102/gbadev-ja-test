@echo off

cd tmp

rem ---------------------------------
rem EFFをBMPに変換

for %%i in (*.EFF) do ..\..\exe\eff\eff2bmp %%i

del *.EFF


rem ---------------------------------
rem リサイズとバイナリ化

for %%i in (*.bmp) do python ..\..\exe\eff\eff_bin.py %%i

del *.bmp


rem ---------------------------------
rem 重複、何もしないフレームは消去

del CLS91_30.e01
del CLS93_09.e01
del CLS96_08.e01

del CLS01_00.e01
del CLS10_00.e01
del CLS93_00.e01
del CLS97_00.e01
del CLS99_00.e01


rem ---------------------------------
rem バイナリを再結合

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


