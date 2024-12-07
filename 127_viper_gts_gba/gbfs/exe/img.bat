@echo off

cd tmp


rem ---------------------------------
rem ANMをBMPに変換

for %%i in (*.ANM) do ..\..\exe\img\anm2bmp %%i

del *.ANM


rem ---------------------------------
rem 差分ファイルの合成

python ..\..\exe\img\img_dif2.py 245 G002.dat G002_04.bmp G002_09.bmp
python ..\..\exe\img\img_dif1.py 245 G002_05.bmp G002_04.bmp
python ..\..\exe\img\img_dif1.py 245 G002_06.bmp G002_05.bmp
python ..\..\exe\img\img_dif1.py 245 G002_07.bmp G002_06.bmp
python ..\..\exe\img\img_dif1.py 245 G002_08.bmp G002_07.bmp

python ..\..\exe\img\img_dif2.py 12 G003.dat G003_04.bmp G003_10.bmp
python ..\..\exe\img\img_dif1.py 12 G003_05.bmp G003_04.bmp
python ..\..\exe\img\img_dif1.py 12 G003_06.bmp G003_05.bmp
python ..\..\exe\img\img_dif1.py 12 G003_07.bmp G003_06.bmp
python ..\..\exe\img\img_dif1.py 12 G003_08.bmp G003_07.bmp
python ..\..\exe\img\img_dif1.py 12 G003_09.bmp G003_08.bmp

python ..\..\exe\img\img_dif1.py 245 G004_08.bmp G004_07.bmp
python ..\..\exe\img\img_dif1.py 245 G004_09.bmp G004_08.bmp
python ..\..\exe\img\img_dif1.py 245 G004_10.bmp G004_09.bmp
python ..\..\exe\img\img_dif1.py 245 G004_11.bmp G004_10.bmp
python ..\..\exe\img\img_dif1.py 245 G004_12.bmp G004_11.bmp
python ..\..\exe\img\img_dif1.py 245 G004_13.bmp G004_12.bmp
python ..\..\exe\img\img_dif1.py 245 G004_14.bmp G004_13.bmp
python ..\..\exe\img\img_dif1.py 245 G004_15.bmp G004_14.bmp
python ..\..\exe\img\img_dif1.py 245 G004_16.bmp G004_15.bmp
python ..\..\exe\img\img_dif1.py 245 G004_17.bmp G004_16.bmp
python ..\..\exe\img\img_dif1.py 245 G004_18.bmp G004_17.bmp
python ..\..\exe\img\img_dif1.py 245 G004_19.bmp G004_18.bmp
python ..\..\exe\img\img_dif1.py 245 G004_20.bmp G004_19.bmp
python ..\..\exe\img\img_dif1.py 245 G004_21.bmp G004_20.bmp
python ..\..\exe\img\img_dif1.py 245 G004_22.bmp G004_21.bmp
python ..\..\exe\img\img_dif1.py 245 G004_23.bmp G004_22.bmp
python ..\..\exe\img\img_dif1.py 245 G004_24.bmp G004_23.bmp
python ..\..\exe\img\img_dif1.py 245 G004_25.bmp G004_24.bmp
python ..\..\exe\img\img_dif1.py 245 G004_26.bmp G004_25.bmp
python ..\..\exe\img\img_dif1.py 245 G004_27.bmp G004_26.bmp
python ..\..\exe\img\img_dif1.py 245 G004_28.bmp G004_27.bmp
python ..\..\exe\img\img_dif1.py 245 G004_29.bmp G004_28.bmp
python ..\..\exe\img\img_dif1.py 245 G004_30.bmp G004_29.bmp

python ..\..\exe\img\img_dif2.py 245 G010.dat G010_07.bmp G010_09.bmp
python ..\..\exe\img\img_dif1.py 245 G010_08.bmp G010_07.bmp

python ..\..\exe\img\img_dif3.py 12 G011_07.bmp G011_41.bmp
python ..\..\exe\img\img_dif3.py 12 G011_08.bmp G011_41.bmp
python ..\..\exe\img\img_dif3.py 12 G011_09.bmp G011_41.bmp
python ..\..\exe\img\img_dif3.py 12 G011_10.bmp G011_41.bmp
python ..\..\exe\img\img_dif3.py 12 G011_11.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_12.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_13.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_14.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_15.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_16.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_17.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_18.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_19.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_20.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_21.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_22.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_23.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_24.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_25.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_26.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_27.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_28.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_29.bmp G011_41.bmp
python ..\..\exe\img\img_dif1.py 12 G011_30.bmp G011_29.bmp
python ..\..\exe\img\img_dif1.py 12 G011_31.bmp G011_30.bmp
python ..\..\exe\img\img_dif1.py 12 G011_32.bmp G011_31.bmp
python ..\..\exe\img\img_dif1.py 12 G011_33.bmp G011_32.bmp
python ..\..\exe\img\img_dif1.py 12 G011_34.bmp G011_33.bmp
python ..\..\exe\img\img_dif1.py 12 G011_35.bmp G011_34.bmp
python ..\..\exe\img\img_dif1.py 12 G011_36.bmp G011_35.bmp
python ..\..\exe\img\img_dif1.py 12 G011_37.bmp G011_36.bmp
python ..\..\exe\img\img_dif1.py 12 G011_38.bmp G011_37.bmp
python ..\..\exe\img\img_dif1.py 12 G011_39.bmp G011_38.bmp
python ..\..\exe\img\img_dif1.py 12 G011_40.bmp G011_39.bmp

python ..\..\exe\img\img_dif1.py 245 G012_02.bmp G012_01.bmp
python ..\..\exe\img\img_dif1.py 245 G012_03.bmp G012_02.bmp
python ..\..\exe\img\img_dif1.py 245 G012_04.bmp G012_03.bmp
python ..\..\exe\img\img_dif1.py 245 G012_05.bmp G012_04.bmp
python ..\..\exe\img\img_dif1.py 245 G012_06.bmp G012_05.bmp
python ..\..\exe\img\img_dif1.py 245 G012_07.bmp G012_06.bmp
python ..\..\exe\img\img_dif1.py 245 G012_08.bmp G012_07.bmp
python ..\..\exe\img\img_dif1.py 245 G012_09.bmp G012_08.bmp
python ..\..\exe\img\img_dif1.py 245 G012_10.bmp G012_09.bmp
python ..\..\exe\img\img_dif1.py 245 G012_11.bmp G012_10.bmp
python ..\..\exe\img\img_dif1.py 245 G012_12.bmp G012_11.bmp
python ..\..\exe\img\img_dif1.py 245 G012_13.bmp G012_12.bmp
python ..\..\exe\img\img_dif1.py 245 G012_14.bmp G012_13.bmp
python ..\..\exe\img\img_dif1.py 245 G012_15.bmp G012_14.bmp
python ..\..\exe\img\img_dif1.py 245 G012_16.bmp G012_15.bmp
python ..\..\exe\img\img_dif1.py 245 G012_17.bmp G012_16.bmp
python ..\..\exe\img\img_dif1.py 245 G012_18.bmp G012_17.bmp
python ..\..\exe\img\img_dif1.py 245 G012_19.bmp G012_18.bmp

python ..\..\exe\img\img_dif1.py 245 G013_07.bmp G013_12.bmp
python ..\..\exe\img\img_dif1.py 245 G013_08.bmp G013_07.bmp
python ..\..\exe\img\img_dif1.py 245 G013_09.bmp G013_08.bmp
python ..\..\exe\img\img_dif1.py 245 G013_10.bmp G013_09.bmp
python ..\..\exe\img\img_dif1.py 245 G013_11.bmp G013_10.bmp
python ..\..\exe\img\img_dif1.py 245 G013_12.bmp G013_11.bmp

python ..\..\exe\img\img_dif1.py 245 G014_02.bmp G014_01.bmp
python ..\..\exe\img\img_dif1.py 245 G014_03.bmp G014_02.bmp
python ..\..\exe\img\img_dif1.py 245 G014_04.bmp G014_03.bmp
python ..\..\exe\img\img_dif1.py 245 G014_05.bmp G014_04.bmp
python ..\..\exe\img\img_dif1.py 245 G014_06.bmp G014_05.bmp
python ..\..\exe\img\img_dif1.py 245 G014_07.bmp G014_06.bmp
python ..\..\exe\img\img_dif1.py 245 G014_08.bmp G014_07.bmp
python ..\..\exe\img\img_dif1.py 245 G014_09.bmp G014_08.bmp
python ..\..\exe\img\img_dif1.py 245 G014_10.bmp G014_09.bmp
python ..\..\exe\img\img_dif1.py 245 G014_11.bmp G014_10.bmp
python ..\..\exe\img\img_dif1.py 245 G014_12.bmp G014_11.bmp
python ..\..\exe\img\img_dif1.py 245 G014_13.bmp G014_12.bmp
python ..\..\exe\img\img_dif1.py 245 G014_14.bmp G014_13.bmp
python ..\..\exe\img\img_dif1.py 245 G014_15.bmp G014_14.bmp
python ..\..\exe\img\img_dif1.py 245 G014_16.bmp G014_15.bmp
python ..\..\exe\img\img_dif1.py 245 G014_17.bmp G014_16.bmp
python ..\..\exe\img\img_dif1.py 245 G014_18.bmp G014_17.bmp
python ..\..\exe\img\img_dif1.py 245 G014_19.bmp G014_18.bmp
python ..\..\exe\img\img_dif1.py 245 G014_20.bmp G014_19.bmp
python ..\..\exe\img\img_dif1.py 245 G014_21.bmp G014_20.bmp
python ..\..\exe\img\img_dif1.py 245 G014_22.bmp G014_21.bmp
python ..\..\exe\img\img_dif1.py 245 G014_23.bmp G014_22.bmp
python ..\..\exe\img\img_dif1.py 245 G014_24.bmp G014_23.bmp
python ..\..\exe\img\img_dif1.py 245 G014_25.bmp G014_24.bmp
python ..\..\exe\img\img_dif1.py 245 G014_26.bmp G014_25.bmp
python ..\..\exe\img\img_dif1.py 245 G014_27.bmp G014_26.bmp
python ..\..\exe\img\img_dif1.py 245 G014_28.bmp G014_27.bmp
python ..\..\exe\img\img_dif1.py 245 G014_29.bmp G014_28.bmp
python ..\..\exe\img\img_dif1.py 245 G014_30.bmp G014_18.bmp

python ..\..\exe\img\img_dif1.py 245 G016_04.bmp G016_10.bmp
python ..\..\exe\img\img_dif1.py 245 G016_05.bmp G016_10.bmp
python ..\..\exe\img\img_dif1.py 245 G016_06.bmp G016_10.bmp
python ..\..\exe\img\img_dif1.py 245 G016_07.bmp G016_10.bmp
python ..\..\exe\img\img_dif1.py 245 G016_08.bmp G016_10.bmp
python ..\..\exe\img\img_dif1.py 245 G016_09.bmp G016_10.bmp

python ..\..\exe\img\img_dif1.py 245 G017_05.bmp G017_04.bmp
python ..\..\exe\img\img_dif1.py 245 G017_06.bmp G017_05.bmp
python ..\..\exe\img\img_dif1.py 245 G017_07.bmp G017_06.bmp
python ..\..\exe\img\img_dif1.py 245 G017_08.bmp G017_07.bmp
python ..\..\exe\img\img_dif1.py 245 G017_09.bmp G017_08.bmp
python ..\..\exe\img\img_dif1.py 245 G017_10.bmp G017_09.bmp
python ..\..\exe\img\img_dif1.py 245 G017_11.bmp G017_10.bmp
python ..\..\exe\img\img_dif1.py 245 G017_12.bmp G017_11.bmp
python ..\..\exe\img\img_dif1.py 245 G017_13.bmp G017_12.bmp
python ..\..\exe\img\img_dif1.py 245 G017_14.bmp G017_13.bmp
python ..\..\exe\img\img_dif1.py 245 G017_15.bmp G017_14.bmp

python ..\..\exe\img\img_dif1.py 245 G019_04.bmp G019_07.bmp
python ..\..\exe\img\img_dif1.py 245 G019_05.bmp G019_04.bmp
python ..\..\exe\img\img_dif1.py 245 G019_06.bmp G019_05.bmp

python ..\..\exe\img\img_dif1.py 245 G020_02.bmp G020_01.bmp
python ..\..\exe\img\img_dif1.py 245 G020_03.bmp G020_02.bmp
python ..\..\exe\img\img_dif1.py 245 G020_04.bmp G020_03.bmp
python ..\..\exe\img\img_dif1.py 245 G020_05.bmp G020_04.bmp
python ..\..\exe\img\img_dif1.py 245 G020_06.bmp G020_05.bmp
python ..\..\exe\img\img_dif1.py 245 G020_07.bmp G020_06.bmp
python ..\..\exe\img\img_dif1.py 245 G020_08.bmp G020_07.bmp
python ..\..\exe\img\img_dif1.py 245 G020_09.bmp G020_08.bmp
python ..\..\exe\img\img_dif1.py 245 G020_10.bmp G020_09.bmp
python ..\..\exe\img\img_dif1.py 245 G020_11.bmp G020_10.bmp
python ..\..\exe\img\img_dif1.py 245 G020_12.bmp G020_11.bmp
python ..\..\exe\img\img_dif1.py 245 G020_13.bmp G020_12.bmp
python ..\..\exe\img\img_dif1.py 245 G020_14.bmp G020_13.bmp
python ..\..\exe\img\img_dif1.py 245 G020_15.bmp G020_14.bmp

python ..\..\exe\img\img_dif1.py 245 G021_02.bmp G021_01.bmp
python ..\..\exe\img\img_dif1.py 245 G021_03.bmp G021_02.bmp
python ..\..\exe\img\img_dif1.py 245 G021_04.bmp G021_03.bmp
python ..\..\exe\img\img_dif1.py 245 G021_05.bmp G021_04.bmp
python ..\..\exe\img\img_dif1.py 245 G021_06.bmp G021_05.bmp
python ..\..\exe\img\img_dif1.py 245 G021_07.bmp G021_06.bmp
python ..\..\exe\img\img_dif1.py 245 G021_08.bmp G021_07.bmp

python ..\..\exe\img\img_dif1.py 245 G022_01.bmp G022_06.bmp
python ..\..\exe\img\img_dif1.py 245 G022_02.bmp G022_06.bmp
python ..\..\exe\img\img_dif1.py 245 G022_03.bmp G022_06.bmp
python ..\..\exe\img\img_dif1.py 245 G022_04.bmp G022_06.bmp
python ..\..\exe\img\img_dif1.py 245 G022_05.bmp G022_06.bmp

python ..\..\exe\img\img_dif1.py 245 G026_02.bmp G026_01.bmp
python ..\..\exe\img\img_dif1.py 245 G026_03.bmp G026_02.bmp
python ..\..\exe\img\img_dif1.py 245 G026_04.bmp G026_03.bmp
python ..\..\exe\img\img_dif1.py 245 G026_05.bmp G026_04.bmp
python ..\..\exe\img\img_dif1.py 245 G026_06.bmp G026_05.bmp
python ..\..\exe\img\img_dif1.py 245 G026_07.bmp G026_06.bmp
python ..\..\exe\img\img_dif1.py 245 G026_08.bmp G026_07.bmp
python ..\..\exe\img\img_dif1.py 245 G026_09.bmp G026_08.bmp
python ..\..\exe\img\img_dif1.py 245 G026_10.bmp G026_09.bmp
python ..\..\exe\img\img_dif1.py 245 G026_11.bmp G026_10.bmp
python ..\..\exe\img\img_dif1.py 245 G026_12.bmp G026_11.bmp
python ..\..\exe\img\img_dif1.py 245 G026_13.bmp G026_12.bmp
python ..\..\exe\img\img_dif1.py 245 G026_14.bmp G026_13.bmp
python ..\..\exe\img\img_dif1.py 245 G026_15.bmp G026_14.bmp
python ..\..\exe\img\img_dif1.py 245 G026_16.bmp G026_15.bmp
python ..\..\exe\img\img_dif1.py 245 G026_17.bmp G026_16.bmp
python ..\..\exe\img\img_dif1.py 245 G026_18.bmp G026_17.bmp
python ..\..\exe\img\img_dif1.py 245 G026_19.bmp G026_18.bmp
python ..\..\exe\img\img_dif1.py 245 G026_20.bmp G026_19.bmp
python ..\..\exe\img\img_dif1.py 245 G026_21.bmp G026_20.bmp
python ..\..\exe\img\img_dif1.py 245 G026_22.bmp G026_21.bmp
python ..\..\exe\img\img_dif1.py 245 G026_23.bmp G026_22.bmp
python ..\..\exe\img\img_dif1.py 245 G026_24.bmp G026_23.bmp
python ..\..\exe\img\img_dif1.py 245 G026_25.bmp G026_24.bmp
python ..\..\exe\img\img_dif1.py 245 G026_26.bmp G026_25.bmp
python ..\..\exe\img\img_dif1.py 245 G026_27.bmp G026_26.bmp
python ..\..\exe\img\img_dif1.py 245 G026_28.bmp G026_27.bmp
python ..\..\exe\img\img_dif1.py 245 G026_29.bmp G026_28.bmp
python ..\..\exe\img\img_dif1.py 245 G026_30.bmp G026_29.bmp
python ..\..\exe\img\img_dif1.py 245 G026_31.bmp G026_30.bmp
python ..\..\exe\img\img_dif1.py 245 G026_32.bmp G026_01.bmp
python ..\..\exe\img\img_dif1.py 245 G026_33.bmp G026_01.bmp
python ..\..\exe\img\img_dif1.py 245 G026_34.bmp G026_01.bmp

python ..\..\exe\img\img_dif1.py 245 G029_17.bmp G029_16.bmp
python ..\..\exe\img\img_dif1.py 245 G029_18.bmp G029_17.bmp
python ..\..\exe\img\img_dif1.py 245 G029_19.bmp G029_18.bmp
python ..\..\exe\img\img_dif1.py 245 G029_20.bmp G029_19.bmp
python ..\..\exe\img\img_dif1.py 245 G029_21.bmp G029_20.bmp
python ..\..\exe\img\img_dif1.py 245 G029_22.bmp G029_21.bmp
python ..\..\exe\img\img_dif1.py 245 G029_23.bmp G029_22.bmp
python ..\..\exe\img\img_dif1.py 245 G029_24.bmp G029_23.bmp
python ..\..\exe\img\img_dif1.py 245 G029_25.bmp G029_24.bmp
python ..\..\exe\img\img_dif1.py 245 G029_26.bmp G029_25.bmp
python ..\..\exe\img\img_dif1.py 245 G029_27.bmp G029_26.bmp
python ..\..\exe\img\img_dif1.py 245 G029_28.bmp G029_27.bmp

python ..\..\exe\img\img_dif1.py 245 G031_05.bmp G031_10.bmp
python ..\..\exe\img\img_dif1.py 245 G031_06.bmp G031_05.bmp
python ..\..\exe\img\img_dif1.py 245 G031_07.bmp G031_06.bmp
python ..\..\exe\img\img_dif1.py 245 G031_08.bmp G031_07.bmp
python ..\..\exe\img\img_dif1.py 245 G031_09.bmp G031_08.bmp
python ..\..\exe\img\img_dif1.py 245 G031_04.bmp G031_09.bmp

python ..\..\exe\img\img_dif1.py 245 G035_02.bmp G035_07.bmp
python ..\..\exe\img\img_dif1.py 245 G035_03.bmp G035_02.bmp
python ..\..\exe\img\img_dif1.py 245 G035_04.bmp G035_03.bmp
python ..\..\exe\img\img_dif1.py 245 G035_05.bmp G035_04.bmp
python ..\..\exe\img\img_dif1.py 245 G035_06.bmp G035_05.bmp
python ..\..\exe\img\img_dif1.py 245 G035_01.bmp G035_06.bmp

python ..\..\exe\img\img_dif1.py 245 G037_06.bmp G037_19.bmp
python ..\..\exe\img\img_dif1.py 245 G037_07.bmp G037_06.bmp
python ..\..\exe\img\img_dif1.py 245 G037_08.bmp G037_07.bmp
python ..\..\exe\img\img_dif1.py 245 G037_09.bmp G037_08.bmp
python ..\..\exe\img\img_dif1.py 245 G037_10.bmp G037_09.bmp
python ..\..\exe\img\img_dif1.py 245 G037_11.bmp G037_10.bmp
python ..\..\exe\img\img_dif1.py 245 G037_12.bmp G037_11.bmp
python ..\..\exe\img\img_dif1.py 245 G037_13.bmp G037_12.bmp
python ..\..\exe\img\img_dif1.py 245 G037_14.bmp G037_13.bmp
python ..\..\exe\img\img_dif1.py 245 G037_15.bmp G037_14.bmp
python ..\..\exe\img\img_dif1.py 245 G037_16.bmp G037_15.bmp
python ..\..\exe\img\img_dif1.py 245 G037_17.bmp G037_16.bmp
python ..\..\exe\img\img_dif1.py 245 G037_18.bmp G037_19.bmp

python ..\..\exe\img\img_dif1.py 245 G044_02.bmp G044_01.bmp
python ..\..\exe\img\img_dif1.py 245 G044_03.bmp G044_02.bmp
python ..\..\exe\img\img_dif1.py 245 G044_04.bmp G044_03.bmp
python ..\..\exe\img\img_dif1.py 245 G044_05.bmp G044_04.bmp
python ..\..\exe\img\img_dif1.py 245 G044_06.bmp G044_05.bmp
python ..\..\exe\img\img_dif1.py 245 G044_07.bmp G044_06.bmp
python ..\..\exe\img\img_dif1.py 245 G044_08.bmp G044_07.bmp
python ..\..\exe\img\img_dif1.py 245 G044_09.bmp G044_08.bmp
python ..\..\exe\img\img_dif1.py 245 G044_10.bmp G044_09.bmp
python ..\..\exe\img\img_dif1.py 245 G044_11.bmp G044_10.bmp
python ..\..\exe\img\img_dif1.py 245 G044_12.bmp G044_11.bmp
python ..\..\exe\img\img_dif1.py 245 G044_13.bmp G044_12.bmp
python ..\..\exe\img\img_dif1.py 245 G044_14.bmp G044_13.bmp
python ..\..\exe\img\img_dif1.py 245 G044_15.bmp G044_14.bmp
python ..\..\exe\img\img_dif1.py 245 G044_16.bmp G044_15.bmp
python ..\..\exe\img\img_dif1.py 245 G044_17.bmp G044_16.bmp
python ..\..\exe\img\img_dif1.py 245 G044_18.bmp G044_17.bmp
python ..\..\exe\img\img_dif1.py 245 G044_19.bmp G044_18.bmp
python ..\..\exe\img\img_dif1.py 245 G044_20.bmp G044_19.bmp
python ..\..\exe\img\img_dif1.py 245 G044_21.bmp G044_20.bmp
python ..\..\exe\img\img_dif1.py 245 G044_22.bmp G044_21.bmp
python ..\..\exe\img\img_dif1.py 245 G044_23.bmp G044_22.bmp
python ..\..\exe\img\img_dif1.py 245 G044_24.bmp G044_23.bmp
python ..\..\exe\img\img_dif1.py 245 G044_25.bmp G044_24.bmp
python ..\..\exe\img\img_dif1.py 245 G044_26.bmp G044_25.bmp
python ..\..\exe\img\img_dif1.py 245 G044_27.bmp G044_26.bmp

python ..\..\exe\img\img_dif1.py 245 G044B_02.bmp G044B_07.bmp
python ..\..\exe\img\img_dif1.py 245 G044B_03.bmp G044B_02.bmp
python ..\..\exe\img\img_dif1.py 245 G044B_04.bmp G044B_03.bmp
python ..\..\exe\img\img_dif1.py 245 G044B_05.bmp G044B_04.bmp
python ..\..\exe\img\img_dif1.py 245 G044B_06.bmp G044B_05.bmp
python ..\..\exe\img\img_dif1.py 245 G044B_01.bmp G044B_06.bmp

python ..\..\exe\img\img_dif1.py 245 G045_05.bmp G045_04.bmp
python ..\..\exe\img\img_dif1.py 245 G045_06.bmp G045_05.bmp
python ..\..\exe\img\img_dif1.py 245 G045_07.bmp G045_06.bmp
python ..\..\exe\img\img_dif1.py 245 G045_08.bmp G045_07.bmp
python ..\..\exe\img\img_dif1.py 245 G045_09.bmp G045_08.bmp
python ..\..\exe\img\img_dif1.py 245 G045_10.bmp G045_09.bmp
python ..\..\exe\img\img_dif1.py 245 G045_11.bmp G045_10.bmp
python ..\..\exe\img\img_dif1.py 245 G045_12.bmp G045_11.bmp
python ..\..\exe\img\img_dif1.py 245 G045_13.bmp G045_12.bmp
python ..\..\exe\img\img_dif1.py 245 G045_14.bmp G045_13.bmp
python ..\..\exe\img\img_dif1.py 245 G045_15.bmp G045_14.bmp
python ..\..\exe\img\img_dif1.py 245 G045_16.bmp G045_15.bmp
python ..\..\exe\img\img_dif1.py 245 G045_17.bmp G045_16.bmp
python ..\..\exe\img\img_dif1.py 245 G045_18.bmp G045_17.bmp
python ..\..\exe\img\img_dif1.py 245 G045_19.bmp G045_18.bmp

python ..\..\exe\img\img_dif1.py 245 G047_02.bmp G047_01.bmp
python ..\..\exe\img\img_dif1.py 245 G047_03.bmp G047_02.bmp
python ..\..\exe\img\img_dif1.py 245 G047_04.bmp G047_03.bmp
python ..\..\exe\img\img_dif1.py 245 G047_05.bmp G047_04.bmp
python ..\..\exe\img\img_dif1.py 245 G047_06.bmp G047_05.bmp
python ..\..\exe\img\img_dif1.py 245 G047_07.bmp G047_06.bmp
python ..\..\exe\img\img_dif1.py 245 G047_08.bmp G047_07.bmp
python ..\..\exe\img\img_dif1.py 245 G047_09.bmp G047_08.bmp
python ..\..\exe\img\img_dif1.py 245 G047_10.bmp G047_09.bmp
python ..\..\exe\img\img_dif1.py 245 G047_11.bmp G047_10.bmp
python ..\..\exe\img\img_dif1.py 245 G047_12.bmp G047_11.bmp
python ..\..\exe\img\img_dif1.py 245 G047_13.bmp G047_12.bmp
python ..\..\exe\img\img_dif1.py 245 G047_14.bmp G047_13.bmp
python ..\..\exe\img\img_dif1.py 245 G047_15.bmp G047_14.bmp
python ..\..\exe\img\img_dif1.py 245 G047_16.bmp G047_15.bmp
python ..\..\exe\img\img_dif1.py 245 G047_17.bmp G047_16.bmp
python ..\..\exe\img\img_dif1.py 245 G047_18.bmp G047_17.bmp
python ..\..\exe\img\img_dif1.py 245 G047_19.bmp G047_18.bmp
python ..\..\exe\img\img_dif1.py 245 G047_20.bmp G047_19.bmp

python ..\..\exe\img\img_dif1.py 245 G048_05.bmp G048_08.bmp
python ..\..\exe\img\img_dif1.py 245 G048_06.bmp G048_05.bmp
python ..\..\exe\img\img_dif1.py 245 G048_07.bmp G048_06.bmp
python ..\..\exe\img\img_dif1.py 245 G048_04.bmp G048_07.bmp

python ..\..\exe\img\img_dif1.py 245 G051_05.bmp G051_01.bmp
python ..\..\exe\img\img_dif1.py 245 G051_06.bmp G051_05.bmp
python ..\..\exe\img\img_dif1.py 245 G051_07.bmp G051_06.bmp
python ..\..\exe\img\img_dif1.py 245 G051_08.bmp G051_07.bmp
python ..\..\exe\img\img_dif1.py 245 G051_09.bmp G051_08.bmp
python ..\..\exe\img\img_dif1.py 245 G051_10.bmp G051_09.bmp
python ..\..\exe\img\img_dif1.py 245 G051_11.bmp G051_10.bmp
python ..\..\exe\img\img_dif1.py 245 G051_12.bmp G051_11.bmp
python ..\..\exe\img\img_dif1.py 245 G051_13.bmp G051_12.bmp
python ..\..\exe\img\img_dif1.py 245 G051_14.bmp G051_13.bmp
python ..\..\exe\img\img_dif1.py 245 G051_15.bmp G051_14.bmp
python ..\..\exe\img\img_dif1.py 245 G051_16.bmp G051_15.bmp
python ..\..\exe\img\img_dif1.py 245 G051_17.bmp G051_16.bmp
python ..\..\exe\img\img_dif1.py 245 G051_18.bmp G051_17.bmp
python ..\..\exe\img\img_dif1.py 245 G051_19.bmp G051_18.bmp
python ..\..\exe\img\img_dif1.py 245 G051_20.bmp G051_19.bmp
python ..\..\exe\img\img_dif1.py 245 G051_21.bmp G051_20.bmp

python ..\..\exe\img\img_dif2.py 245 G052.dat G052_05.bmp G052_26.bmp
python ..\..\exe\img\img_dif1.py 245 G052_06.bmp G052_05.bmp
python ..\..\exe\img\img_dif1.py 245 G052_07.bmp G052_06.bmp
python ..\..\exe\img\img_dif1.py 245 G052_04.bmp G052_07.bmp
python ..\..\exe\img\img_dif1.py 245 G052_21.bmp G052_19.bmp
python ..\..\exe\img\img_dif1.py 245 G052_22.bmp G052_21.bmp
python ..\..\exe\img\img_dif1.py 245 G052_23.bmp G052_22.bmp
python ..\..\exe\img\img_dif1.py 245 G052_24.bmp G052_23.bmp
python ..\..\exe\img\img_dif1.py 245 G052_25.bmp G052_24.bmp
python ..\..\exe\img\img_dif1.py 245 G052_20.bmp G052_25.bmp

python ..\..\exe\img\img_dif1.py 245 G055_05.bmp G055_34.bmp
python ..\..\exe\img\img_dif1.py 245 G055_06.bmp G055_05.bmp
python ..\..\exe\img\img_dif1.py 245 G055_07.bmp G055_06.bmp
python ..\..\exe\img\img_dif1.py 245 G055_08.bmp G055_07.bmp
python ..\..\exe\img\img_dif1.py 245 G055_09.bmp G055_08.bmp
python ..\..\exe\img\img_dif1.py 245 G055_10.bmp G055_09.bmp
python ..\..\exe\img\img_dif1.py 245 G055_11.bmp G055_10.bmp
python ..\..\exe\img\img_dif1.py 245 G055_12.bmp G055_11.bmp
python ..\..\exe\img\img_dif1.py 245 G055_13.bmp G055_12.bmp
python ..\..\exe\img\img_dif1.py 245 G055_14.bmp G055_13.bmp
python ..\..\exe\img\img_dif1.py 245 G055_15.bmp G055_14.bmp
python ..\..\exe\img\img_dif1.py 245 G055_16.bmp G055_15.bmp
python ..\..\exe\img\img_dif1.py 245 G055_17.bmp G055_16.bmp
python ..\..\exe\img\img_dif1.py 245 G055_18.bmp G055_17.bmp
python ..\..\exe\img\img_dif1.py 245 G055_19.bmp G055_18.bmp
python ..\..\exe\img\img_dif1.py 245 G055_20.bmp G055_19.bmp
python ..\..\exe\img\img_dif1.py 245 G055_21.bmp G055_20.bmp
python ..\..\exe\img\img_dif1.py 245 G055_22.bmp G055_21.bmp
python ..\..\exe\img\img_dif1.py 245 G055_23.bmp G055_22.bmp
python ..\..\exe\img\img_dif1.py 245 G055_24.bmp G055_23.bmp
python ..\..\exe\img\img_dif1.py 245 G055_25.bmp G055_24.bmp
python ..\..\exe\img\img_dif1.py 245 G055_26.bmp G055_25.bmp
python ..\..\exe\img\img_dif1.py 245 G055_27.bmp G055_26.bmp
python ..\..\exe\img\img_dif1.py 245 G055_28.bmp G055_27.bmp

python ..\..\exe\img\img_dif1.py 245 G059_02.bmp G059_06.bmp
python ..\..\exe\img\img_dif1.py 245 G059_03.bmp G059_02.bmp
python ..\..\exe\img\img_dif1.py 245 G059_04.bmp G059_03.bmp
python ..\..\exe\img\img_dif1.py 245 G059_05.bmp G059_04.bmp
python ..\..\exe\img\img_dif1.py 245 G059_01.bmp G059_05.bmp

python ..\..\exe\img\img_dif1.py 245 G062_02.bmp G062_01.bmp
python ..\..\exe\img\img_dif1.py 245 G062_03.bmp G062_01.bmp
python ..\..\exe\img\img_dif1.py 245 G062_04.bmp G062_01.bmp
python ..\..\exe\img\img_dif1.py 245 G062_05.bmp G062_01.bmp
python ..\..\exe\img\img_dif1.py 245 G062_06.bmp G062_05.bmp
python ..\..\exe\img\img_dif1.py 245 G062_07.bmp G062_06.bmp
python ..\..\exe\img\img_dif1.py 245 G062_08.bmp G062_07.bmp
python ..\..\exe\img\img_dif1.py 245 G062_09.bmp G062_08.bmp
python ..\..\exe\img\img_dif1.py 245 G062_10.bmp G062_09.bmp
python ..\..\exe\img\img_dif1.py 245 G062_11.bmp G062_10.bmp
python ..\..\exe\img\img_dif1.py 245 G062_12.bmp G062_11.bmp
python ..\..\exe\img\img_dif1.py 245 G062_13.bmp G062_12.bmp
python ..\..\exe\img\img_dif1.py 245 G062_14.bmp G062_13.bmp
python ..\..\exe\img\img_dif1.py 245 G062_15.bmp G062_14.bmp
python ..\..\exe\img\img_dif1.py 245 G062_16.bmp G062_15.bmp
python ..\..\exe\img\img_dif1.py 245 G062_17.bmp G062_16.bmp
python ..\..\exe\img\img_dif1.py 245 G062_18.bmp G062_17.bmp
python ..\..\exe\img\img_dif1.py 245 G062_19.bmp G062_18.bmp

python ..\..\exe\img\img_dif1.py 12 G064A_02.bmp G064A_01.bmp

python ..\..\exe\img\img_dif2.py 245 G065.dat G065_05.bmp G065_26.bmp
python ..\..\exe\img\img_dif1.py 245 G065_06.bmp G065_05.bmp
python ..\..\exe\img\img_dif1.py 245 G065_07.bmp G065_06.bmp
python ..\..\exe\img\img_dif1.py 245 G065_04.bmp G065_07.bmp
python ..\..\exe\img\img_dif1.py 245 G065_21.bmp G065_19.bmp
python ..\..\exe\img\img_dif1.py 245 G065_22.bmp G065_21.bmp
python ..\..\exe\img\img_dif1.py 245 G065_23.bmp G065_22.bmp
python ..\..\exe\img\img_dif1.py 245 G065_24.bmp G065_23.bmp
python ..\..\exe\img\img_dif1.py 245 G065_25.bmp G065_24.bmp
python ..\..\exe\img\img_dif1.py 245 G065_20.bmp G065_25.bmp

python ..\..\exe\img\img_dif1.py 245 G068_08.bmp G068_07.bmp
python ..\..\exe\img\img_dif1.py 245 G068_09.bmp G068_08.bmp
python ..\..\exe\img\img_dif1.py 245 G068_10.bmp G068_09.bmp
python ..\..\exe\img\img_dif1.py 245 G068_11.bmp G068_10.bmp

python ..\..\exe\img\img_dif1.py 245 G070_09.bmp G070_15.bmp
python ..\..\exe\img\img_dif1.py 245 G070_10.bmp G070_15.bmp
python ..\..\exe\img\img_dif1.py 245 G070_11.bmp G070_15.bmp
python ..\..\exe\img\img_dif1.py 245 G070_12.bmp G070_15.bmp
python ..\..\exe\img\img_dif1.py 245 G070_13.bmp G070_15.bmp
python ..\..\exe\img\img_dif1.py 245 G070_14.bmp G070_15.bmp

python ..\..\exe\img\img_dif1.py 245 G079_05.bmp G079_04.bmp
python ..\..\exe\img\img_dif1.py 245 G079_06.bmp G079_05.bmp
python ..\..\exe\img\img_dif1.py 245 G079_07.bmp G079_06.bmp
python ..\..\exe\img\img_dif1.py 245 G079_08.bmp G079_07.bmp
python ..\..\exe\img\img_dif1.py 245 G079_09.bmp G079_08.bmp
python ..\..\exe\img\img_dif1.py 245 G079_10.bmp G079_09.bmp
python ..\..\exe\img\img_dif1.py 245 G079_11.bmp G079_10.bmp
python ..\..\exe\img\img_dif1.py 245 G079_12.bmp G079_11.bmp
python ..\..\exe\img\img_dif1.py 245 G079_13.bmp G079_12.bmp
python ..\..\exe\img\img_dif3.py 245 G079_15.bmp G079_14.bmp
python ..\..\exe\img\img_dif3.py 245 G079_16.bmp G079_15.bmp
python ..\..\exe\img\img_dif3.py 245 G079_17.bmp G079_16.bmp
python ..\..\exe\img\img_dif3.py 245 G079_18.bmp G079_17.bmp
python ..\..\exe\img\img_dif3.py 245 G079_19.bmp G079_18.bmp
python ..\..\exe\img\img_dif3.py 245 G079_20.bmp G079_19.bmp

python ..\..\exe\img\img_dif2.py 12 G080.dat G080_01.bmp G080_05.bmp
python ..\..\exe\img\img_dif1.py 12 G080_02.bmp G080_01.bmp
python ..\..\exe\img\img_dif1.py 12 G080_03.bmp G080_02.bmp
python ..\..\exe\img\img_dif1.py 12 G080_04.bmp G080_03.bmp

python ..\..\exe\img\img_dif1.py 245 G081_01.bmp G081_05.bmp
python ..\..\exe\img\img_dif1.py 245 G081_02.bmp G081_05.bmp
python ..\..\exe\img\img_dif1.py 245 G081_03.bmp G081_05.bmp
python ..\..\exe\img\img_dif1.py 245 G081_04.bmp G081_05.bmp

python ..\..\exe\img\img_dif1.py 12 G082_01.bmp G082_16.bmp
python ..\..\exe\img\img_dif1.py 12 G082_02.bmp G082_16.bmp
python ..\..\exe\img\img_dif1.py 12 G082_03.bmp G082_16.bmp
python ..\..\exe\img\img_dif1.py 12 G082_04.bmp G082_16.bmp
python ..\..\exe\img\img_dif1.py 12 G082_05.bmp G082_04.bmp
python ..\..\exe\img\img_dif1.py 12 G082_11.bmp G082_10.bmp
python ..\..\exe\img\img_dif1.py 12 G082_12.bmp G082_10.bmp
python ..\..\exe\img\img_dif1.py 12 G082_13.bmp G082_10.bmp
python ..\..\exe\img\img_dif1.py 12 G082_14.bmp G082_10.bmp
python ..\..\exe\img\img_dif1.py 12 G082_15.bmp G082_10.bmp

python ..\..\exe\img\img_dif1.py 245 G083_01.bmp G083_05.bmp
python ..\..\exe\img\img_dif1.py 245 G083_02.bmp G083_05.bmp
python ..\..\exe\img\img_dif1.py 245 G083_03.bmp G083_05.bmp
python ..\..\exe\img\img_dif1.py 245 G083_04.bmp G083_05.bmp

python ..\..\exe\img\img_dif3.py 10 G084_01.bmp G084_15.bmp
python ..\..\exe\img\img_dif3.py 10 G084_02.bmp G084_01.bmp
python ..\..\exe\img\img_dif3.py 10 G084_03.bmp G084_02.bmp
python ..\..\exe\img\img_dif3.py 10 G084_04.bmp G084_03.bmp
python ..\..\exe\img\img_dif3.py 10 G084_05.bmp G084_04.bmp
python ..\..\exe\img\img_dif3.py 10 G084_06.bmp G084_05.bmp
python ..\..\exe\img\img_dif3.py 10 G084_07.bmp G084_06.bmp
python ..\..\exe\img\img_dif3.py 10 G084_08.bmp G084_07.bmp
python ..\..\exe\img\img_dif3.py 10 G084_09.bmp G084_08.bmp
python ..\..\exe\img\img_dif3.py 10 G084_10.bmp G084_09.bmp
python ..\..\exe\img\img_dif3.py 10 G084_11.bmp G084_10.bmp
python ..\..\exe\img\img_dif3.py 10 G084_12.bmp G084_11.bmp
python ..\..\exe\img\img_dif3.py 10 G084_13.bmp G084_12.bmp
python ..\..\exe\img\img_dif3.py 10 G084_14.bmp G084_13.bmp

python ..\..\exe\img\img_dif1.py 245 G086_02.bmp G086_07.bmp
python ..\..\exe\img\img_dif1.py 245 G086_03.bmp G086_02.bmp
python ..\..\exe\img\img_dif1.py 245 G086_04.bmp G086_03.bmp
python ..\..\exe\img\img_dif1.py 245 G086_05.bmp G086_04.bmp
python ..\..\exe\img\img_dif1.py 245 G086_06.bmp G086_05.bmp
python ..\..\exe\img\img_dif1.py 245 G086_01.bmp G086_06.bmp

python ..\..\exe\img\img_dif1.py 245 G088_01.bmp G088_06.bmp
python ..\..\exe\img\img_dif1.py 245 G088_02.bmp G088_06.bmp
python ..\..\exe\img\img_dif1.py 245 G088_03.bmp G088_06.bmp
python ..\..\exe\img\img_dif1.py 245 G088_04.bmp G088_06.bmp
python ..\..\exe\img\img_dif1.py 245 G088_05.bmp G088_06.bmp

python ..\..\exe\img\img_dif4.py 245 G090.dat G090_29.bmp G090_10.bmp
python ..\..\exe\img\img_dif1.py 245 G090_10.bmp G090_09.bmp
python ..\..\exe\img\img_dif1.py 245 G090_11.bmp G090_10.bmp
python ..\..\exe\img\img_dif1.py 245 G090_12.bmp G090_11.bmp
python ..\..\exe\img\img_dif1.py 245 G090_13.bmp G090_12.bmp
python ..\..\exe\img\img_dif1.py 245 G090_14.bmp G090_13.bmp
python ..\..\exe\img\img_dif1.py 245 G090_15.bmp G090_14.bmp
python ..\..\exe\img\img_dif1.py 245 G090_16.bmp G090_15.bmp
python ..\..\exe\img\img_dif1.py 245 G090_17.bmp G090_16.bmp
python ..\..\exe\img\img_dif1.py 245 G090_18.bmp G090_17.bmp
python ..\..\exe\img\img_dif1.py 245 G090_19.bmp G090_18.bmp
python ..\..\exe\img\img_dif1.py 245 G090_20.bmp G090_19.bmp
python ..\..\exe\img\img_dif1.py 245 G090_21.bmp G090_20.bmp
python ..\..\exe\img\img_dif1.py 245 G090_22.bmp G090_21.bmp
python ..\..\exe\img\img_dif1.py 245 G090_23.bmp G090_22.bmp
python ..\..\exe\img\img_dif1.py 245 G090_24.bmp G090_23.bmp

python ..\..\exe\img\img_dif1.py 12 G092_04.bmp G092_10.bmp
python ..\..\exe\img\img_dif1.py 12 G092_05.bmp G092_10.bmp
python ..\..\exe\img\img_dif1.py 12 G092_06.bmp G092_10.bmp
python ..\..\exe\img\img_dif1.py 12 G092_07.bmp G092_10.bmp
python ..\..\exe\img\img_dif1.py 12 G092_08.bmp G092_10.bmp
python ..\..\exe\img\img_dif1.py 12 G092_09.bmp G092_10.bmp

python ..\..\exe\img\img_dif1.py 245 GRSB_13.bmp GRSA_10.bmp
python ..\..\exe\img\img_dif1.py 245 GRSB_14.bmp GRSA_10.bmp
python ..\..\exe\img\img_dif1.py 245 GRSB_15.bmp GRSA_10.bmp
python ..\..\exe\img\img_dif1.py 245 GRSB_16.bmp GRSA_10.bmp
python ..\..\exe\img\img_dif1.py 245 GRSB_17.bmp GRSA_10.bmp
python ..\..\exe\img\img_dif1.py 245 GRSB_18.bmp GRSA_10.bmp


rem ---------------------------------
rem 口パク画像などの透明色をカットし、座標データを変更

python ..\..\exe\img\img_cut1.py 12 0 G011.dat G011_01.bmp
python ..\..\exe\img\img_cut1.py 12 0 G011.dat G011_02.bmp
python ..\..\exe\img\img_cut1.py 12 0 G011.dat G011_03.bmp
python ..\..\exe\img\img_cut1.py 12 0 G011.dat G011_04.bmp
python ..\..\exe\img\img_cut1.py 12 0 G011.dat G011_05.bmp
python ..\..\exe\img\img_cut1.py 12 0 G011.dat G011_06.bmp

python ..\..\exe\img\img_cut1.py 245 1 G016.dat G016_02.bmp
python ..\..\exe\img\img_cut1.py 245 0 G016.dat G016_03.bmp
python ..\..\exe\img\img_dif2.py 245 G016.dat G016_02.bmp G016_10.bmp
python ..\..\exe\img\img_dif2.py 245 G016.dat G016_03.bmp G016_10.bmp

python ..\..\exe\img\img_cut1.py 245 4 G019.dat G019_02.bmp
python ..\..\exe\img\img_cut1.py 245 0 G019.dat G019_03.bmp
python ..\..\exe\img\img_dif2.py 245 G019.dat G019_02.bmp G019_07.bmp
python ..\..\exe\img\img_dif2.py 245 G019.dat G019_03.bmp G019_07.bmp

python ..\..\exe\img\img_cut1.py 245 1 G025.dat G025_02.bmp
python ..\..\exe\img\img_cut1.py 245 0 G025.dat G025_03.bmp
python ..\..\exe\img\img_cut1.py 245 2 G025.dat G025_05.bmp
python ..\..\exe\img\img_cut1.py 245 0 G025.dat G025_06.bmp
python ..\..\exe\img\img_dif2.py 245 G025.dat G025_02.bmp G025_07.bmp
python ..\..\exe\img\img_dif2.py 245 G025.dat G025_03.bmp G025_07.bmp
python ..\..\exe\img\img_dif2.py 245 G025.dat G025_05.bmp G025_07.bmp
python ..\..\exe\img\img_dif2.py 245 G025.dat G025_06.bmp G025_07.bmp

python ..\..\exe\img\img_cut1.py 245 4 G027.dat G027_02.bmp
python ..\..\exe\img\img_cut1.py 245 0 G027.dat G027_03.bmp
python ..\..\exe\img\img_dif2.py 245 G027.dat G027_02.bmp G027_04.bmp
python ..\..\exe\img\img_dif2.py 245 G027.dat G027_03.bmp G027_04.bmp

python ..\..\exe\img\img_cut1.py 245 4 G030.dat G030_02.bmp
python ..\..\exe\img\img_cut1.py 245 0 G030.dat G030_03.bmp
python ..\..\exe\img\img_dif2.py 245 G030.dat G030_02.bmp G030_04.bmp
python ..\..\exe\img\img_dif2.py 245 G030.dat G030_03.bmp G030_04.bmp

python ..\..\exe\img\img_cut1.py 245 0 G034.dat G034_02.bmp
python ..\..\exe\img\img_cut1.py 245 0 G034.dat G034_03.bmp
python ..\..\exe\img\img_dif2.py 245 G034.dat G034_02.bmp G034_04.bmp
python ..\..\exe\img\img_dif2.py 245 G034.dat G034_03.bmp G034_04.bmp

python ..\..\exe\img\img_cut1.py 245 4 G041.dat G041_02.bmp
python ..\..\exe\img\img_cut1.py 245 0 G041.dat G041_03.bmp
python ..\..\exe\img\img_dif2.py 245 G041.dat G041_02.bmp G041_04.bmp
python ..\..\exe\img\img_dif2.py 245 G041.dat G041_03.bmp G041_04.bmp

python ..\..\exe\img\img_cut1.py 245 12 G070.dat G070_05.bmp
python ..\..\exe\img\img_cut1.py 245 0 G070.dat G070_06.bmp
python ..\..\exe\img\img_dif2.py 245 G070.dat G070_05.bmp G070_15.bmp
python ..\..\exe\img\img_dif2.py 245 G070.dat G070_06.bmp G070_15.bmp

python ..\..\exe\img\img_dif2.py 12 G078.dat G078_02.bmp G078_06.bmp
python ..\..\exe\img\img_dif2.py 12 G078.dat G078_03.bmp G078_06.bmp

python ..\..\exe\img\img_cut1.py 12 5 G092.dat G092_02.bmp
python ..\..\exe\img\img_cut1.py 12 0 G092.dat G092_03.bmp
python ..\..\exe\img\img_dif2.py 12 G092.dat G092_02.bmp G092_10.bmp
python ..\..\exe\img\img_dif2.py 12 G092.dat G092_03.bmp G092_10.bmp

python ..\..\exe\img\img_dif2.py 252 G104.dat G104_04.bmp G104_09.bmp
python ..\..\exe\img\img_dif2.py 252 G104.dat G104_05.bmp G104_09.bmp
python ..\..\exe\img\img_dif2.py 252 G104.dat G104_06.bmp G104_09.bmp
python ..\..\exe\img\img_dif2.py 252 G104.dat G104_07.bmp G104_09.bmp
python ..\..\exe\img\img_dif2.py 252 G104.dat G104_08.bmp G104_09.bmp


rem ---------------------------------
rem 透明色だけの口パク画像を削除し、実体をスクロール画像から取得
rem 座標は他の口パクデータを取得し変更

del G016_01.bmp
python ..\..\exe\img\img_cut3.py 3 G016.dat G016_01.bmp G016_10.bmp

del G019_01.bmp
python ..\..\exe\img\img_cut3.py 3 G019.dat G019_01.bmp G019_07.bmp

del G025_01.bmp
python ..\..\exe\img\img_cut3.py 3 G025.dat G025_01.bmp G025_07.bmp

del G025_04.bmp
python ..\..\exe\img\img_cut3.py 6 G025.dat G025_04.bmp G025_07.bmp

del G027_01.bmp
python ..\..\exe\img\img_cut3.py 3 G027.dat G027_01.bmp G027_04.bmp

del G030_01.bmp
python ..\..\exe\img\img_cut3.py 3 G030.dat G030_01.bmp G030_04.bmp

del G034_01.bmp
python ..\..\exe\img\img_cut3.py 2 G034.dat G034_01.bmp G034_04.bmp

del G041_01.bmp
python ..\..\exe\img\img_cut3.py 3 G041.dat G041_01.bmp G041_04.bmp

del G070_04.bmp
python ..\..\exe\img\img_cut3.py 6 G070.dat G070_04.bmp G070_15.bmp

del G078_01.bmp
python ..\..\exe\img\img_cut3.py 2 G078.dat G078_01.bmp G078_06.bmp

del G092_01.bmp
python ..\..\exe\img\img_cut3.py 3 G092.dat G092_01.bmp G092_10.bmp


rem ---------------------------------
rem G069専用（カルラと天使スクロール）
python ..\..\exe\img\img_g069.py


rem ---------------------------------
rem G100のカルラのビリビリ合成とリネーム
python ..\..\exe\img\img_dif1.py 11 G100_04.bmp G100_01.bmp
python ..\..\exe\img\img_dif1.py 11 G100_05.bmp G100_02.bmp
python ..\..\exe\img\img_dif1.py 11 G100_06.bmp G100_03.bmp

del G100_01.bmp
del G100_02.bmp
del G100_03.bmp
rename G100_04.bmp G100_01.bmp
rename G100_05.bmp G100_02.bmp
rename G100_06.bmp G100_03.bmp


rem ---------------------------------
rem タイトルの画像をカット、加工
python ..\..\exe\img\img_cut2.py 96 32 544 352 GTS_TIT_03.bmp
python ..\..\exe\img\img_dif5.py 12 48 0 GTS_TIT.dat GTS_TIT_01.bmp GTS_TIT_03.bmp
python ..\..\exe\img\img_dif5.py 12 48 0 GTS_TIT.dat GTS_TIT_02.bmp GTS_TIT_03.bmp
python ..\..\exe\img\dat_edit.py 3 0 0 448 320 GTS_TIT.dat


rem ---------------------------------
rem ロゴの一部カット
python ..\..\exe\img\img_cut2.py 96 40 544 360 SOGNA_01.bmp
python ..\..\exe\img\dat_edit.py 1 0 0 448 320 SOGNA.dat


rem ---------------------------------
rem ゴミ除去
python ..\..\exe\img\img_cut2.py 0 0 448 755 G009_04.bmp
python ..\..\exe\img\dat_edit.py 4 0 0 448 755 G009.dat


rem ---------------------------------
rem 不要ファイルを削除（合成用の素材、重複素材、フレーム画像）
del G011_41.bmp
del G016_10.bmp
del G022_06.bmp
del G035_07.bmp
del G069_01.bmp
del G081_05.bmp
del G082_16.bmp
del G083_05.bmp
del G088_06.bmp
del G092_10.bmp

del G040.dat
del G040_01.bmp
del G040_02.bmp
del G040_03.bmp
del G040_04.bmp
del G040_05.bmp
del G040_06.bmp
del G040_07.bmp
del G040_08.bmp
del G040_09.bmp
del G040_10.bmp
del G040_11.bmp
del G040_12.bmp
del G040_13.bmp
del G040_14.bmp
del G040_15.bmp
del G040_16.bmp
del G040_17.bmp
del G040_18.bmp
del G040_19.bmp
del G040_20.bmp
del G040_21.bmp
del G040_22.bmp
del G040_23.bmp
del G040_24.bmp
del G040_25.bmp
del G040_26.bmp
del G040_27.bmp
del G040_28.bmp
del G040_29.bmp
del G040_30.bmp
del G040_31.bmp
del G040_32.bmp
del G040_33.bmp
del G040_34.bmp

del WINDOW.dat
del WINDOW_01.bmp
del WINDOW_02.bmp
del WINDOW_03.bmp


rem ---------------------------------
rem リサイズ

for %%i in (*.bmp) do python ..\..\exe\img\img_size.py %%i


rem ---------------------------------
echo BMPファイルをGBA用に変換中です・・・。

rem 240x160画像をLz77圧縮(mode4)
..\..\exe\img\grit G001_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G002_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G003_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G004_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G005_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G007_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G007_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G007_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G007_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G007_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G007_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G007_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G007_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G007_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G008_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_33.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_34.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_35.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_36.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_37.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_38.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_39.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G011_40.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G012_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G013_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G013_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G013_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G013_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G013_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G013_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G014_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G015_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G017_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G018_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G020_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G021_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G021_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G021_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G021_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G021_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G021_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G021_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G021_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G023_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G024_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G024_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G024_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G024_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G024_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G024_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G024_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G024_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_33.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G026_34.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G028_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G029_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G031_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G031_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G031_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G031_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G031_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G031_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G031_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G032_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G032_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G032_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G032_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G032_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G032_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G033_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G035_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G035_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G035_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G035_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G035_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G035_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G036_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G036_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G036_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G036_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G036_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G036_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G036_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G037_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G039_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G042_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G043_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044B_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044B_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044B_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044B_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044B_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044B_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044B_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G044_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G045_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G046_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G046_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G046_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G046_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G046_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G047_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G048_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G048_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G048_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G048_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G048_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G050_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G050_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G050_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G050_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G050_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G050_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G051_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G052_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G054_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G054_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G054_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G054_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G054_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G054_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_33.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G055_34.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G056_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G058_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G058_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G058_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G058_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G058_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G058_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G058_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G058_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G059_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G059_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G059_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G059_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G059_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G059_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G060_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G061_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G061_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G061_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G061_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G062_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G063_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G064A_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G064A_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G065_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G066_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G067_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G068_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G068_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G068_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G068_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G068_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G068_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G068_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G068_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G071_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G071_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G071_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G071_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G071_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G071_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G071_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G071_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G072_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G073_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G074_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G075B_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G076A_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G076B_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G077_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G077_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G078_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G078_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G078_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G079_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G080_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G081_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G081_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G081_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G081_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G082_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G084_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G085_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G086_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G086_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G086_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G086_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G086_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G086_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G086_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G087_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G087_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G087_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G087_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G087_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G087_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G087_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G087_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G087_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G088_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G088_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G088_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G088_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G088_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G089_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G089_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G089_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G089_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G089_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G089_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G090_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G091_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G093_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G093_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G093_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G093_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G093_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G093_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G094_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G095_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G096_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G096_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G096_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G096_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G096_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G097_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G098_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G099_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G100_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G100_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G100_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G101_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G102_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G102_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G102_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G102_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G102_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G103_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G103_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G103_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G103_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G103_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit G104_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit GRSA_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit GRSB_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit GRSB_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit GRSB_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit GRSB_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit GRSB_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit GRSB_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit GTS_TIT_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit SOGNA_01.bmp -g -gb -ftb -gzl -p! -fh!

rem ---------------------------------
rem 240x160画像以外を無圧縮に変換（Mode4）

python ..\..\exe\img\img_bin.py G001_01.bmp
python ..\..\exe\img\img_bin.py G001_02.bmp
python ..\..\exe\img\img_bin.py G001_03.bmp
python ..\..\exe\img\img_bin.py G002_01.bmp
python ..\..\exe\img\img_bin.py G002_02.bmp
python ..\..\exe\img\img_bin.py G002_03.bmp
python ..\..\exe\img\img_bin.py G002_04.bmp
python ..\..\exe\img\img_bin.py G002_05.bmp
python ..\..\exe\img\img_bin.py G002_06.bmp
python ..\..\exe\img\img_bin.py G002_07.bmp
python ..\..\exe\img\img_bin.py G002_08.bmp
python ..\..\exe\img\img_bin.py G003_01.bmp
python ..\..\exe\img\img_bin.py G003_02.bmp
python ..\..\exe\img\img_bin.py G003_03.bmp
python ..\..\exe\img\img_bin.py G003_04.bmp
python ..\..\exe\img\img_bin.py G003_05.bmp
python ..\..\exe\img\img_bin.py G003_06.bmp
python ..\..\exe\img\img_bin.py G003_07.bmp
python ..\..\exe\img\img_bin.py G003_08.bmp
python ..\..\exe\img\img_bin.py G003_09.bmp
python ..\..\exe\img\img_bin.py G005_01.bmp
python ..\..\exe\img\img_bin.py G005_02.bmp
python ..\..\exe\img\img_bin.py G006_01.bmp
python ..\..\exe\img\img_bin.py G008_02.bmp
python ..\..\exe\img\img_bin.py G008_03.bmp
python ..\..\exe\img\img_bin.py G008_04.bmp
python ..\..\exe\img\img_bin.py G008_05.bmp
python ..\..\exe\img\img_bin.py G008_06.bmp
python ..\..\exe\img\img_bin.py G008_07.bmp
python ..\..\exe\img\img_bin.py G009_01.bmp
python ..\..\exe\img\img_bin.py G009_02.bmp
python ..\..\exe\img\img_bin.py G009_03.bmp
python ..\..\exe\img\img_bin.py G009_04.bmp
python ..\..\exe\img\img_bin.py G010_01.bmp
python ..\..\exe\img\img_bin.py G010_02.bmp
python ..\..\exe\img\img_bin.py G010_03.bmp
python ..\..\exe\img\img_bin.py G010_04.bmp
python ..\..\exe\img\img_bin.py G010_05.bmp
python ..\..\exe\img\img_bin.py G010_06.bmp
python ..\..\exe\img\img_bin.py G010_07.bmp
python ..\..\exe\img\img_bin.py G010_08.bmp
python ..\..\exe\img\img_bin.py G010_09.bmp
python ..\..\exe\img\img_bin.py G011_01.bmp
python ..\..\exe\img\img_bin.py G011_02.bmp
python ..\..\exe\img\img_bin.py G011_03.bmp
python ..\..\exe\img\img_bin.py G011_04.bmp
python ..\..\exe\img\img_bin.py G011_05.bmp
python ..\..\exe\img\img_bin.py G011_06.bmp
python ..\..\exe\img\img_bin.py G011_12.bmp
python ..\..\exe\img\img_bin.py G011_13.bmp
python ..\..\exe\img\img_bin.py G011_14.bmp
python ..\..\exe\img\img_bin.py G011_15.bmp
python ..\..\exe\img\img_bin.py G011_16.bmp
python ..\..\exe\img\img_bin.py G011_17.bmp
python ..\..\exe\img\img_bin.py G011_18.bmp
python ..\..\exe\img\img_bin.py G011_19.bmp
python ..\..\exe\img\img_bin.py G011_20.bmp
python ..\..\exe\img\img_bin.py G011_21.bmp
python ..\..\exe\img\img_bin.py G011_22.bmp
python ..\..\exe\img\img_bin.py G011_23.bmp
python ..\..\exe\img\img_bin.py G011_24.bmp
python ..\..\exe\img\img_bin.py G011_25.bmp
python ..\..\exe\img\img_bin.py G011_26.bmp
python ..\..\exe\img\img_bin.py G011_27.bmp
python ..\..\exe\img\img_bin.py G011_28.bmp
python ..\..\exe\img\img_bin.py G011_29.bmp
python ..\..\exe\img\img_bin.py G013_01.bmp
python ..\..\exe\img\img_bin.py G013_02.bmp
python ..\..\exe\img\img_bin.py G013_03.bmp
python ..\..\exe\img\img_bin.py G013_04.bmp
python ..\..\exe\img\img_bin.py G013_05.bmp
python ..\..\exe\img\img_bin.py G013_06.bmp
python ..\..\exe\img\img_bin.py G015_01.bmp
python ..\..\exe\img\img_bin.py G015_02.bmp
python ..\..\exe\img\img_bin.py G015_03.bmp
python ..\..\exe\img\img_bin.py G016_01.bmp
python ..\..\exe\img\img_bin.py G016_02.bmp
python ..\..\exe\img\img_bin.py G016_03.bmp
python ..\..\exe\img\img_bin.py G016_04.bmp
python ..\..\exe\img\img_bin.py G016_05.bmp
python ..\..\exe\img\img_bin.py G016_06.bmp
python ..\..\exe\img\img_bin.py G016_07.bmp
python ..\..\exe\img\img_bin.py G016_08.bmp
python ..\..\exe\img\img_bin.py G016_09.bmp
python ..\..\exe\img\img_bin.py G017_01.bmp
python ..\..\exe\img\img_bin.py G017_02.bmp
python ..\..\exe\img\img_bin.py G017_03.bmp
python ..\..\exe\img\img_bin.py G018_01.bmp
python ..\..\exe\img\img_bin.py G018_02.bmp
python ..\..\exe\img\img_bin.py G018_03.bmp
python ..\..\exe\img\img_bin.py G019_01.bmp
python ..\..\exe\img\img_bin.py G019_02.bmp
python ..\..\exe\img\img_bin.py G019_03.bmp
python ..\..\exe\img\img_bin.py G019_04.bmp
python ..\..\exe\img\img_bin.py G019_05.bmp
python ..\..\exe\img\img_bin.py G019_06.bmp
python ..\..\exe\img\img_bin.py G019_07.bmp
python ..\..\exe\img\img_bin.py G022_01.bmp
python ..\..\exe\img\img_bin.py G022_02.bmp
python ..\..\exe\img\img_bin.py G022_03.bmp
python ..\..\exe\img\img_bin.py G022_04.bmp
python ..\..\exe\img\img_bin.py G022_05.bmp
python ..\..\exe\img\img_bin.py G025_01.bmp
python ..\..\exe\img\img_bin.py G025_02.bmp
python ..\..\exe\img\img_bin.py G025_03.bmp
python ..\..\exe\img\img_bin.py G025_04.bmp
python ..\..\exe\img\img_bin.py G025_05.bmp
python ..\..\exe\img\img_bin.py G025_06.bmp
python ..\..\exe\img\img_bin.py G025_07.bmp
python ..\..\exe\img\img_bin.py G027_01.bmp
python ..\..\exe\img\img_bin.py G027_02.bmp
python ..\..\exe\img\img_bin.py G027_03.bmp
python ..\..\exe\img\img_bin.py G027_04.bmp
python ..\..\exe\img\img_bin.py G029_01.bmp
python ..\..\exe\img\img_bin.py G029_02.bmp
python ..\..\exe\img\img_bin.py G029_03.bmp
python ..\..\exe\img\img_bin.py G029_04.bmp
python ..\..\exe\img\img_bin.py G029_05.bmp
python ..\..\exe\img\img_bin.py G029_06.bmp
python ..\..\exe\img\img_bin.py G029_07.bmp
python ..\..\exe\img\img_bin.py G029_08.bmp
python ..\..\exe\img\img_bin.py G029_09.bmp
python ..\..\exe\img\img_bin.py G029_10.bmp
python ..\..\exe\img\img_bin.py G029_11.bmp
python ..\..\exe\img\img_bin.py G029_12.bmp
python ..\..\exe\img\img_bin.py G029_13.bmp
python ..\..\exe\img\img_bin.py G029_14.bmp
python ..\..\exe\img\img_bin.py G029_15.bmp
python ..\..\exe\img\img_bin.py G030_01.bmp
python ..\..\exe\img\img_bin.py G030_02.bmp
python ..\..\exe\img\img_bin.py G030_03.bmp
python ..\..\exe\img\img_bin.py G030_04.bmp
python ..\..\exe\img\img_bin.py G031_01.bmp
python ..\..\exe\img\img_bin.py G031_02.bmp
python ..\..\exe\img\img_bin.py G031_03.bmp
python ..\..\exe\img\img_bin.py G033_01.bmp
python ..\..\exe\img\img_bin.py G033_02.bmp
python ..\..\exe\img\img_bin.py G033_03.bmp
python ..\..\exe\img\img_bin.py G033_11.bmp
python ..\..\exe\img\img_bin.py G033_12.bmp
python ..\..\exe\img\img_bin.py G033_13.bmp
python ..\..\exe\img\img_bin.py G034_01.bmp
python ..\..\exe\img\img_bin.py G034_02.bmp
python ..\..\exe\img\img_bin.py G034_03.bmp
python ..\..\exe\img\img_bin.py G034_04.bmp
python ..\..\exe\img\img_bin.py G037_18.bmp
python ..\..\exe\img\img_bin.py G037_19.bmp
python ..\..\exe\img\img_bin.py G039_01.bmp
python ..\..\exe\img\img_bin.py G039_02.bmp
python ..\..\exe\img\img_bin.py G039_03.bmp
python ..\..\exe\img\img_bin.py G041_01.bmp
python ..\..\exe\img\img_bin.py G041_02.bmp
python ..\..\exe\img\img_bin.py G041_03.bmp
python ..\..\exe\img\img_bin.py G041_04.bmp
python ..\..\exe\img\img_bin.py G042_01.bmp
python ..\..\exe\img\img_bin.py G042_02.bmp
python ..\..\exe\img\img_bin.py G042_03.bmp
python ..\..\exe\img\img_bin.py G043_01.bmp
python ..\..\exe\img\img_bin.py G043_02.bmp
python ..\..\exe\img\img_bin.py G043_03.bmp
python ..\..\exe\img\img_bin.py G045_01.bmp
python ..\..\exe\img\img_bin.py G045_02.bmp
python ..\..\exe\img\img_bin.py G045_03.bmp
python ..\..\exe\img\img_bin.py G045_20.bmp
python ..\..\exe\img\img_bin.py G045_21.bmp
python ..\..\exe\img\img_bin.py G045_22.bmp
python ..\..\exe\img\img_bin.py G045_23.bmp
python ..\..\exe\img\img_bin.py G045_24.bmp
python ..\..\exe\img\img_bin.py G048_01.bmp
python ..\..\exe\img\img_bin.py G048_02.bmp
python ..\..\exe\img\img_bin.py G048_03.bmp
python ..\..\exe\img\img_bin.py G049_01.bmp
python ..\..\exe\img\img_bin.py G049_02.bmp
python ..\..\exe\img\img_bin.py G049_03.bmp
python ..\..\exe\img\img_bin.py G049_04.bmp
python ..\..\exe\img\img_bin.py G049_05.bmp
python ..\..\exe\img\img_bin.py G049_06.bmp
python ..\..\exe\img\img_bin.py G052_01.bmp
python ..\..\exe\img\img_bin.py G052_02.bmp
python ..\..\exe\img\img_bin.py G052_03.bmp
python ..\..\exe\img\img_bin.py G052_04.bmp
python ..\..\exe\img\img_bin.py G052_05.bmp
python ..\..\exe\img\img_bin.py G052_06.bmp
python ..\..\exe\img\img_bin.py G052_07.bmp
python ..\..\exe\img\img_bin.py G053_01.bmp
python ..\..\exe\img\img_bin.py G053_02.bmp
python ..\..\exe\img\img_bin.py G053_03.bmp
python ..\..\exe\img\img_bin.py G053_04.bmp
python ..\..\exe\img\img_bin.py G053_05.bmp
python ..\..\exe\img\img_bin.py G053_06.bmp
python ..\..\exe\img\img_bin.py G055_01.bmp
python ..\..\exe\img\img_bin.py G055_02.bmp
python ..\..\exe\img\img_bin.py G055_03.bmp
python ..\..\exe\img\img_bin.py G055_04.bmp
python ..\..\exe\img\img_bin.py G057_01.bmp
python ..\..\exe\img\img_bin.py G057_02.bmp
python ..\..\exe\img\img_bin.py G057_03.bmp
python ..\..\exe\img\img_bin.py G057_04.bmp
python ..\..\exe\img\img_bin.py G057_05.bmp
python ..\..\exe\img\img_bin.py G057_06.bmp
python ..\..\exe\img\img_bin.py G057_07.bmp
python ..\..\exe\img\img_bin.py G060_01.bmp
python ..\..\exe\img\img_bin.py G060_02.bmp
python ..\..\exe\img\img_bin.py G060_03.bmp
python ..\..\exe\img\img_bin.py G060_04.bmp
python ..\..\exe\img\img_bin.py G060_05.bmp
python ..\..\exe\img\img_bin.py G060_06.bmp
python ..\..\exe\img\img_bin.py G063_01.bmp
python ..\..\exe\img\img_bin.py G063_02.bmp
python ..\..\exe\img\img_bin.py G063_03.bmp
python ..\..\exe\img\img_bin.py G063_04.bmp
python ..\..\exe\img\img_bin.py G063_05.bmp
python ..\..\exe\img\img_bin.py G063_06.bmp
python ..\..\exe\img\img_bin.py G065_01.bmp
python ..\..\exe\img\img_bin.py G065_02.bmp
python ..\..\exe\img\img_bin.py G065_03.bmp
python ..\..\exe\img\img_bin.py G065_04.bmp
python ..\..\exe\img\img_bin.py G065_05.bmp
python ..\..\exe\img\img_bin.py G065_06.bmp
python ..\..\exe\img\img_bin.py G065_07.bmp
python ..\..\exe\img\img_bin.py G067_01.bmp
python ..\..\exe\img\img_bin.py G067_02.bmp
python ..\..\exe\img\img_bin.py G067_03.bmp
python ..\..\exe\img\img_bin.py G068_01.bmp
python ..\..\exe\img\img_bin.py G068_02.bmp
python ..\..\exe\img\img_bin.py G068_03.bmp
python ..\..\exe\img\img_bin.py G069_02.bmp
python ..\..\exe\img\img_bin.py G070_01.bmp
python ..\..\exe\img\img_bin.py G070_02.bmp
python ..\..\exe\img\img_bin.py G070_03.bmp
python ..\..\exe\img\img_bin.py G070_04.bmp
python ..\..\exe\img\img_bin.py G070_05.bmp
python ..\..\exe\img\img_bin.py G070_06.bmp
python ..\..\exe\img\img_bin.py G070_07.bmp
python ..\..\exe\img\img_bin.py G070_08.bmp
python ..\..\exe\img\img_bin.py G070_09.bmp
python ..\..\exe\img\img_bin.py G070_10.bmp
python ..\..\exe\img\img_bin.py G070_11.bmp
python ..\..\exe\img\img_bin.py G070_12.bmp
python ..\..\exe\img\img_bin.py G070_13.bmp
python ..\..\exe\img\img_bin.py G070_14.bmp
python ..\..\exe\img\img_bin.py G070_15.bmp
python ..\..\exe\img\img_bin.py G071_01.bmp
python ..\..\exe\img\img_bin.py G071_02.bmp
python ..\..\exe\img\img_bin.py G071_03.bmp
python ..\..\exe\img\img_bin.py G073_01.bmp
python ..\..\exe\img\img_bin.py G073_02.bmp
python ..\..\exe\img\img_bin.py G073_03.bmp
python ..\..\exe\img\img_bin.py G073_04.bmp
python ..\..\exe\img\img_bin.py G073_05.bmp
python ..\..\exe\img\img_bin.py G073_06.bmp
python ..\..\exe\img\img_bin.py G073_08.bmp
python ..\..\exe\img\img_bin.py G073_09.bmp
python ..\..\exe\img\img_bin.py G073_10.bmp
python ..\..\exe\img\img_bin.py G075_01.bmp
python ..\..\exe\img\img_bin.py G075_02.bmp
python ..\..\exe\img\img_bin.py G075_03.bmp
python ..\..\exe\img\img_bin.py G075_04.bmp
python ..\..\exe\img\img_bin.py G075_05.bmp
python ..\..\exe\img\img_bin.py G075_06.bmp
python ..\..\exe\img\img_bin.py G075_07.bmp
python ..\..\exe\img\img_bin.py G075_08.bmp
python ..\..\exe\img\img_bin.py G075_09.bmp
python ..\..\exe\img\img_bin.py G075_10.bmp
python ..\..\exe\img\img_bin.py G077_01.bmp
python ..\..\exe\img\img_bin.py G077_02.bmp
python ..\..\exe\img\img_bin.py G077_03.bmp
python ..\..\exe\img\img_bin.py G078_01.bmp
python ..\..\exe\img\img_bin.py G078_02.bmp
python ..\..\exe\img\img_bin.py G078_03.bmp
python ..\..\exe\img\img_bin.py G079_01.bmp
python ..\..\exe\img\img_bin.py G079_02.bmp
python ..\..\exe\img\img_bin.py G079_03.bmp
python ..\..\exe\img\img_bin.py G079_14.bmp
python ..\..\exe\img\img_bin.py G080_01.bmp
python ..\..\exe\img\img_bin.py G080_02.bmp
python ..\..\exe\img\img_bin.py G080_03.bmp
python ..\..\exe\img\img_bin.py G080_04.bmp
python ..\..\exe\img\img_bin.py G083_01.bmp
python ..\..\exe\img\img_bin.py G083_02.bmp
python ..\..\exe\img\img_bin.py G083_03.bmp
python ..\..\exe\img\img_bin.py G083_04.bmp
python ..\..\exe\img\img_bin.py G084_15.bmp
python ..\..\exe\img\img_bin.py G090_25.bmp
python ..\..\exe\img\img_bin.py G090_26.bmp
python ..\..\exe\img\img_bin.py G090_27.bmp
python ..\..\exe\img\img_bin.py G090_28.bmp
python ..\..\exe\img\img_bin.py G090_29.bmp
python ..\..\exe\img\img_bin.py G091_01.bmp
python ..\..\exe\img\img_bin.py G091_02.bmp
python ..\..\exe\img\img_bin.py G091_03.bmp
python ..\..\exe\img\img_bin.py G091_04.bmp
python ..\..\exe\img\img_bin.py G091_05.bmp
python ..\..\exe\img\img_bin.py G091_06.bmp
python ..\..\exe\img\img_bin.py G092_01.bmp
python ..\..\exe\img\img_bin.py G092_02.bmp
python ..\..\exe\img\img_bin.py G092_03.bmp
python ..\..\exe\img\img_bin.py G092_04.bmp
python ..\..\exe\img\img_bin.py G092_05.bmp
python ..\..\exe\img\img_bin.py G092_06.bmp
python ..\..\exe\img\img_bin.py G092_07.bmp
python ..\..\exe\img\img_bin.py G092_08.bmp
python ..\..\exe\img\img_bin.py G092_09.bmp
python ..\..\exe\img\img_bin.py G094_01.bmp
python ..\..\exe\img\img_bin.py G094_02.bmp
python ..\..\exe\img\img_bin.py G095_01.bmp
python ..\..\exe\img\img_bin.py G095_02.bmp
python ..\..\exe\img\img_bin.py G095_03.bmp
python ..\..\exe\img\img_bin.py G097_01.bmp
python ..\..\exe\img\img_bin.py G097_02.bmp
python ..\..\exe\img\img_bin.py G097_03.bmp
python ..\..\exe\img\img_bin.py G097_04.bmp
python ..\..\exe\img\img_bin.py G097_05.bmp
python ..\..\exe\img\img_bin.py G097_06.bmp
python ..\..\exe\img\img_bin.py G098_01.bmp
python ..\..\exe\img\img_bin.py G098_02.bmp
python ..\..\exe\img\img_bin.py G099_01.bmp
python ..\..\exe\img\img_bin.py G099_02.bmp
python ..\..\exe\img\img_bin.py G099_03.bmp
python ..\..\exe\img\img_bin.py G099_04.bmp
python ..\..\exe\img\img_bin.py G099_05.bmp
python ..\..\exe\img\img_bin.py G099_06.bmp
python ..\..\exe\img\img_bin.py G101_01.bmp
python ..\..\exe\img\img_bin.py G101_02.bmp
python ..\..\exe\img\img_bin.py G101_03.bmp
python ..\..\exe\img\img_bin.py G104_01.bmp
python ..\..\exe\img\img_bin.py G104_02.bmp
python ..\..\exe\img\img_bin.py G104_03.bmp
python ..\..\exe\img\img_bin.py G104_04.bmp
python ..\..\exe\img\img_bin.py G104_05.bmp
python ..\..\exe\img\img_bin.py G104_06.bmp
python ..\..\exe\img\img_bin.py G104_07.bmp
python ..\..\exe\img\img_bin.py G104_08.bmp
python ..\..\exe\img\img_bin.py G105_01.bmp
python ..\..\exe\img\img_bin.py G105_02.bmp
python ..\..\exe\img\img_bin.py G105_03.bmp
python ..\..\exe\img\img_bin.py G105_04.bmp
python ..\..\exe\img\img_bin.py GRSA_01.bmp
python ..\..\exe\img\img_bin.py GRSA_02.bmp
python ..\..\exe\img\img_bin.py GRSA_03.bmp
python ..\..\exe\img\img_bin.py GRSA_04.bmp
python ..\..\exe\img\img_bin.py GRSA_05.bmp
python ..\..\exe\img\img_bin.py GRSA_06.bmp
python ..\..\exe\img\img_bin.py GRSA_07.bmp
python ..\..\exe\img\img_bin.py GRSA_08.bmp
python ..\..\exe\img\img_bin.py GRSA_09.bmp
python ..\..\exe\img\img_bin.py GRSA_11.bmp
python ..\..\exe\img\img_bin.py GRSA_12.bmp
python ..\..\exe\img\img_bin.py GRSA_13.bmp
python ..\..\exe\img\img_bin.py GRSA_14.bmp
python ..\..\exe\img\img_bin.py GRSA_15.bmp
python ..\..\exe\img\img_bin.py GRSA_16.bmp
python ..\..\exe\img\img_bin.py GRSA_17.bmp
python ..\..\exe\img\img_bin.py GRSA_18.bmp
python ..\..\exe\img\img_bin.py GRSA_19.bmp
python ..\..\exe\img\img_bin.py GRSA_20.bmp
python ..\..\exe\img\img_bin.py GRSA_21.bmp
python ..\..\exe\img\img_bin.py GRSA_22.bmp
python ..\..\exe\img\img_bin.py GRSA_23.bmp
python ..\..\exe\img\img_bin.py GRSA_24.bmp
python ..\..\exe\img\img_bin.py GRSA_25.bmp
python ..\..\exe\img\img_bin.py GRSA_26.bmp
python ..\..\exe\img\img_bin.py GRSB_01.bmp
python ..\..\exe\img\img_bin.py GRSB_02.bmp
python ..\..\exe\img\img_bin.py GRSB_03.bmp
python ..\..\exe\img\img_bin.py GRSB_04.bmp
python ..\..\exe\img\img_bin.py GRSB_05.bmp
python ..\..\exe\img\img_bin.py GRSB_06.bmp
python ..\..\exe\img\img_bin.py GRSB_07.bmp
python ..\..\exe\img\img_bin.py GRSB_08.bmp
python ..\..\exe\img\img_bin.py GRSB_09.bmp
python ..\..\exe\img\img_bin.py GRSB_10.bmp
python ..\..\exe\img\img_bin.py GRSB_11.bmp
python ..\..\exe\img\img_bin.py GRSB_12.bmp
python ..\..\exe\img\img_bin.py GRSB_19.bmp
python ..\..\exe\img\img_bin.py GRSB_20.bmp
python ..\..\exe\img\img_bin.py GRSB_21.bmp
python ..\..\exe\img\img_bin.py GRSB_22.bmp
python ..\..\exe\img\img_bin.py GRSB_23.bmp
python ..\..\exe\img\img_bin.py GRSB_24.bmp
python ..\..\exe\img\img_bin.py GRSB_25.bmp
python ..\..\exe\img\img_bin.py GRSB_26.bmp
python ..\..\exe\img\img_bin.py GRSB_27.bmp
python ..\..\exe\img\img_bin.py GRSB_28.bmp
python ..\..\exe\img\img_bin.py GTS_TIT_01.bmp
python ..\..\exe\img\img_bin.py GTS_TIT_02.bmp

ren *.img.bin *.
del *.bmp


rem ---------------------------------
rem DATファイルをGBAに変更（座標と画像サイズを２分の１）

for %%i in (*.dat) do python ..\..\exe\img\dat_half.py %%i


cd ..
