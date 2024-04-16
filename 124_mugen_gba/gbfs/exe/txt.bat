@echo off

rmdir /s /q txt 2> nul
mkdir txt
move tmp\*.s txt > nul


rem ---------------------------------
cd txt

del n*.s 2> nul
del u*.s 2> nul
del ss*.s 2>nul
del open.s 2>nul
del run.s 2>nul


rem ---------------------------------
rem sファイルをデコード
python ..\..\exe\txt\s2scn.py 0_00.s 0_00.scn
python ..\..\exe\txt\s2scn.py 1_00.s 1_00.scn
python ..\..\exe\txt\s2scn.py 1_01.s 1_01.scn
python ..\..\exe\txt\s2scn.py 1_02.s 1_02.scn
python ..\..\exe\txt\s2scn.py 1_26.s 1_26.scn
python ..\..\exe\txt\s2scn.py 1_03.s 1_03.scn
python ..\..\exe\txt\s2scn.py 1_24.s 1_24.scn
python ..\..\exe\txt\s2scn.py 1_13.s 1_13.scn
python ..\..\exe\txt\s2scn.py 1_19.s 1_19.scn
python ..\..\exe\txt\s2scn.py 1_18.s 1_18.scn
python ..\..\exe\txt\s2scn.py 1_33.s 1_33.scn
python ..\..\exe\txt\s2scn.py 1_28.s 1_28.scn
python ..\..\exe\txt\s2scn.py 1_29.s 1_29.scn
python ..\..\exe\txt\s2scn.py 1_30.s 1_30.scn
python ..\..\exe\txt\s2scn.py 1_17.s 1_17.scn
python ..\..\exe\txt\s2scn.py 1_27.s 1_27.scn
python ..\..\exe\txt\s2scn.py 1_06.s 1_06.scn
python ..\..\exe\txt\s2scn.py 1_07.s 1_07.scn
python ..\..\exe\txt\s2scn.py 1_05.s 1_05.scn
python ..\..\exe\txt\s2scn.py 1_10.s 1_10.scn
python ..\..\exe\txt\s2scn.py 1_12.s 1_12.scn
python ..\..\exe\txt\s2scn.py 1_34.s 1_34.scn
python ..\..\exe\txt\s2scn.py 1_35.s 1_35.scn
python ..\..\exe\txt\s2scn.py 1_36.s 1_36.scn
python ..\..\exe\txt\s2scn.py 1_58.s 1_58.scn
python ..\..\exe\txt\s2scn.py 1_49.s 1_49.scn
python ..\..\exe\txt\s2scn.py 1_54.s 1_54.scn
python ..\..\exe\txt\s2scn.py 1_61.s 1_61.scn
python ..\..\exe\txt\s2scn.py 1_64.s 1_64.scn
python ..\..\exe\txt\s2scn.py 2_00.s 2_00.scn
python ..\..\exe\txt\s2scn.py 2_20.s 2_20.scn
python ..\..\exe\txt\s2scn.py 2_24.s 2_24.scn
python ..\..\exe\txt\s2scn.py 2_18.s 2_18.scn
python ..\..\exe\txt\s2scn.py 2_01.s 2_01.scn
python ..\..\exe\txt\s2scn.py 2_33.s 2_33.scn
python ..\..\exe\txt\s2scn.py 2_29.s 2_29.scn
python ..\..\exe\txt\s2scn.py 2_34.s 2_34.scn
python ..\..\exe\txt\s2scn.py 2_02.s 2_02.scn
python ..\..\exe\txt\s2scn.py 2_03.s 2_03.scn
python ..\..\exe\txt\s2scn.py 2_30.s 2_30.scn
python ..\..\exe\txt\s2scn.py 2_08.s 2_08.scn
python ..\..\exe\txt\s2scn.py 2_31.s 2_31.scn
python ..\..\exe\txt\s2scn.py 2_27.s 2_27.scn
python ..\..\exe\txt\s2scn.py 2_28.s 2_28.scn
python ..\..\exe\txt\s2scn.py 2_35.s 2_35.scn
python ..\..\exe\txt\s2scn.py 2_55.s 2_55.scn
python ..\..\exe\txt\s2scn.py 2_41.s 2_41.scn
python ..\..\exe\txt\s2scn.py 2_46.s 2_46.scn
python ..\..\exe\txt\s2scn.py 2_61.s 2_61.scn
python ..\..\exe\txt\s2scn.py 2_64.s 2_64.scn
python ..\..\exe\txt\s2scn.py 2_68.s 2_68.scn
python ..\..\exe\txt\s2scn.py 2_71.s 2_71.scn
python ..\..\exe\txt\s2scn.py 2_62.s 2_62.scn
python ..\..\exe\txt\s2scn.py 3_00.s 3_00.scn
python ..\..\exe\txt\s2scn.py 3_01.s 3_01.scn
python ..\..\exe\txt\s2scn.py 3_02.s 3_02.scn
python ..\..\exe\txt\s2scn.py 3_03.s 3_03.scn
python ..\..\exe\txt\s2scn.py 3_04.s 3_04.scn
python ..\..\exe\txt\s2scn.py 3_05.s 3_05.scn
python ..\..\exe\txt\s2scn.py 3_06.s 3_06.scn
python ..\..\exe\txt\s2scn.py 3_07.s 3_07.scn
python ..\..\exe\txt\s2scn.py 3_08.s 3_08.scn
python ..\..\exe\txt\s2scn.py 3_09.s 3_09.scn
python ..\..\exe\txt\s2scn.py 3_10.s 3_10.scn
python ..\..\exe\txt\s2scn.py 4_00.s 4_00.scn
python ..\..\exe\txt\s2scn.py 4_24.s 4_24.scn
python ..\..\exe\txt\s2scn.py 4_14.s 4_14.scn
python ..\..\exe\txt\s2scn.py 4_26.s 4_26.scn
python ..\..\exe\txt\s2scn.py 4_29.s 4_29.scn
python ..\..\exe\txt\s2scn.py 4_30.s 4_30.scn
python ..\..\exe\txt\s2scn.py 4_31.s 4_31.scn
python ..\..\exe\txt\s2scn.py 4_32.s 4_32.scn
python ..\..\exe\txt\s2scn.py 5_00.s 5_00.scn
python ..\..\exe\txt\s2scn.py 5_01.s 5_01.scn
python ..\..\exe\txt\s2scn.py 5_16.s 5_16.scn
python ..\..\exe\txt\s2scn.py 5_28.s 5_28.scn
python ..\..\exe\txt\s2scn.py 5_26.s 5_26.scn
python ..\..\exe\txt\s2scn.py 5_31.s 5_31.scn
python ..\..\exe\txt\s2scn.py 5_23.s 5_23.scn
python ..\..\exe\txt\s2scn.py 5_32.s 5_32.scn
python ..\..\exe\txt\s2scn.py 5_33.s 5_33.scn
python ..\..\exe\txt\s2scn.py 5_34.s 5_34.scn
python ..\..\exe\txt\s2scn.py 5_35.s 5_35.scn
python ..\..\exe\txt\s2scn.py 5_36.s 5_36.scn
python ..\..\exe\txt\s2scn.py 5_37.s 5_37.scn
python ..\..\exe\txt\s2scn.py 5_38.s 5_38.scn
python ..\..\exe\txt\s2scn.py 5_62.s 5_62.scn
python ..\..\exe\txt\s2scn.py 5_63.s 5_63.scn
python ..\..\exe\txt\s2scn.py 5_64.s 5_64.scn
python ..\..\exe\txt\s2scn.py 5_65.s 5_65.scn
python ..\..\exe\txt\s2scn.py 5_66.s 5_66.scn
python ..\..\exe\txt\s2scn.py 6_00.s 6_00.scn
python ..\..\exe\txt\s2scn.py 6_01.s 6_01.scn
python ..\..\exe\txt\s2scn.py 6_02.s 6_02.scn
python ..\..\exe\txt\s2scn.py 6_03.s 6_03.scn
python ..\..\exe\txt\s2scn.py 6_04.s 6_04.scn
python ..\..\exe\txt\s2scn.py 6_05.s 6_05.scn
python ..\..\exe\txt\s2scn.py 6_06.s 6_06.scn
python ..\..\exe\txt\s2scn.py 6_26.s 6_26.scn
python ..\..\exe\txt\s2scn.py 6_27.s 6_27.scn
python ..\..\exe\txt\s2scn.py 6_28.s 6_28.scn
python ..\..\exe\txt\s2scn.py 6_30.s 6_30.scn
python ..\..\exe\txt\s2scn.py 6_29.s 6_29.scn
python ..\..\exe\txt\s2scn.py 6_16.s 6_16.scn
python ..\..\exe\txt\s2scn.py 6_12.s 6_12.scn
python ..\..\exe\txt\s2scn.py 6_13.s 6_13.scn
python ..\..\exe\txt\s2scn.py 6_14.s 6_14.scn
python ..\..\exe\txt\s2scn.py 6_15.s 6_15.scn
python ..\..\exe\txt\s2scn.py 6_11.s 6_11.scn
python ..\..\exe\txt\s2scn.py 6_25.s 6_25.scn
python ..\..\exe\txt\s2scn.py 6_20.s 6_20.scn
python ..\..\exe\txt\s2scn.py 6_21.s 6_21.scn
python ..\..\exe\txt\s2scn.py 6_17.s 6_17.scn
python ..\..\exe\txt\s2scn.py 6_19.s 6_19.scn
python ..\..\exe\txt\s2scn.py 6_31.s 6_31.scn
python ..\..\exe\txt\s2scn.py 6_32.s 6_32.scn
python ..\..\exe\txt\s2scn.py 6_33.s 6_33.scn
python ..\..\exe\txt\s2scn.py 6_34.s 6_34.scn
python ..\..\exe\txt\s2scn.py 6_35.s 6_35.scn
python ..\..\exe\txt\s2scn.py 7_00.s 7_00.scn
python ..\..\exe\txt\s2scn.py 7_02.s 7_02.scn
python ..\..\exe\txt\s2scn.py 7_01.s 7_01.scn
python ..\..\exe\txt\s2scn.py 7_03.s 7_03.scn
python ..\..\exe\txt\s2scn.py 7_04.s 7_04.scn
python ..\..\exe\txt\s2scn.py 7_05.s 7_05.scn
python ..\..\exe\txt\s2scn.py 7_06.s 7_06.scn
python ..\..\exe\txt\s2scn.py 7_07.s 7_07.scn
python ..\..\exe\txt\s2scn.py 7_34.s 7_34.scn
python ..\..\exe\txt\s2scn.py 7_37.s 7_37.scn
python ..\..\exe\txt\s2scn.py 7_35.s 7_35.scn
python ..\..\exe\txt\s2scn.py 7_19.s 7_19.scn
python ..\..\exe\txt\s2scn.py 7_23.s 7_23.scn
python ..\..\exe\txt\s2scn.py 7_25.s 7_25.scn
python ..\..\exe\txt\s2scn.py 7_08.s 7_08.scn
python ..\..\exe\txt\s2scn.py 7_12.s 7_12.scn
python ..\..\exe\txt\s2scn.py 7_22.s 7_22.scn
python ..\..\exe\txt\s2scn.py 7_33.s 7_33.scn
python ..\..\exe\txt\s2scn.py 7_38.s 7_38.scn
python ..\..\exe\txt\s2scn.py 7_39.s 7_39.scn
python ..\..\exe\txt\s2scn.py 7_40.s 7_40.scn
python ..\..\exe\txt\s2scn.py 7_41.s 7_41.scn
python ..\..\exe\txt\s2scn.py 7_42.s 7_42.scn
python ..\..\exe\txt\s2scn.py 8_00.s 8_00.scn
python ..\..\exe\txt\s2scn.py 8_01.s 8_01.scn
python ..\..\exe\txt\s2scn.py 8_02.s 8_02.scn
python ..\..\exe\txt\s2scn.py 8_19.s 8_19.scn
python ..\..\exe\txt\s2scn.py 8_13.s 8_13.scn
python ..\..\exe\txt\s2scn.py 8_16.s 8_16.scn
python ..\..\exe\txt\s2scn.py 8_28.s 8_28.scn
python ..\..\exe\txt\s2scn.py 8_25.s 8_25.scn
python ..\..\exe\txt\s2scn.py 8_29.s 8_29.scn
python ..\..\exe\txt\s2scn.py 8_30.s 8_30.scn
python ..\..\exe\txt\s2scn.py 8_32.s 8_32.scn
python ..\..\exe\txt\s2scn.py 8_33.s 8_33.scn
python ..\..\exe\txt\s2scn.py 8_34.s 8_34.scn
python ..\..\exe\txt\s2scn.py 8_35.s 8_35.scn
python ..\..\exe\txt\s2scn.py 9_00.s 9_00.scn
python ..\..\exe\txt\s2scn.py 9_01.s 9_01.scn
python ..\..\exe\txt\s2scn.py 9_24.s 9_24.scn
python ..\..\exe\txt\s2scn.py 9_26.s 9_26.scn
python ..\..\exe\txt\s2scn.py 9_31.s 9_31.scn
python ..\..\exe\txt\s2scn.py 9_08.s 9_08.scn
python ..\..\exe\txt\s2scn.py 9_13.s 9_13.scn
python ..\..\exe\txt\s2scn.py 9_28.s 9_28.scn
python ..\..\exe\txt\s2scn.py 9_29.s 9_29.scn
python ..\..\exe\txt\s2scn.py 9_32.s 9_32.scn
python ..\..\exe\txt\s2scn.py 9_33.s 9_33.scn
python ..\..\exe\txt\s2scn.py 9_34.s 9_34.scn
python ..\..\exe\txt\s2scn.py 9_36.s 9_36.scn
python ..\..\exe\txt\s2scn.py 9_37.s 9_37.scn
python ..\..\exe\txt\s2scn.py 9_38.s 9_38.scn
python ..\..\exe\txt\s2scn.py 9_39.s 9_39.scn
python ..\..\exe\txt\s2scn.py 9_40.s 9_40.scn
python ..\..\exe\txt\s2scn.py 9_41.s 9_41.scn
python ..\..\exe\txt\s2scn.py 9_42.s 9_42.scn
python ..\..\exe\txt\s2scn.py a_00.s a_00.scn
python ..\..\exe\txt\s2scn.py a_01.s a_01.scn
python ..\..\exe\txt\s2scn.py a_01b.s a_01b.scn
python ..\..\exe\txt\s2scn.py a_02.s a_02.scn
python ..\..\exe\txt\s2scn.py a_03.s a_03.scn
python ..\..\exe\txt\s2scn.py a_04.s a_04.scn
python ..\..\exe\txt\s2scn.py a_05.s a_05.scn
python ..\..\exe\txt\s2scn.py a_06.s a_06.scn
python ..\..\exe\txt\s2scn.py b_00.s b_00.scn
python ..\..\exe\txt\s2scn.py b_03.s b_03.scn
python ..\..\exe\txt\s2scn.py b_02.s b_02.scn
python ..\..\exe\txt\s2scn.py b_04.s b_04.scn
python ..\..\exe\txt\s2scn.py b_01.s b_01.scn
python ..\..\exe\txt\s2scn.py b_05.s b_05.scn
python ..\..\exe\txt\s2scn.py b_06.s b_06.scn
python ..\..\exe\txt\s2scn.py b_07.s b_07.scn
python ..\..\exe\txt\s2scn.py b_08.s b_08.scn
python ..\..\exe\txt\s2scn.py b_14.s b_14.scn
python ..\..\exe\txt\s2scn.py b_09.s b_09.scn
python ..\..\exe\txt\s2scn.py b_11.s b_11.scn
python ..\..\exe\txt\s2scn.py b_10.s b_10.scn
python ..\..\exe\txt\s2scn.py b_13.s b_13.scn
python ..\..\exe\txt\s2scn.py b_15.s b_15.scn
python ..\..\exe\txt\s2scn.py b_16.s b_16.scn
python ..\..\exe\txt\s2scn.py b_17.s b_17.scn
python ..\..\exe\txt\s2scn.py c_00.s c_00.scn
python ..\..\exe\txt\s2scn.py c_03.s c_03.scn
python ..\..\exe\txt\s2scn.py c_07.s c_07.scn
python ..\..\exe\txt\s2scn.py c_04.s c_04.scn
python ..\..\exe\txt\s2scn.py c_05.s c_05.scn
python ..\..\exe\txt\s2scn.py c_06.s c_06.scn
python ..\..\exe\txt\s2scn.py c_02.s c_02.scn
python ..\..\exe\txt\s2scn.py c_08.s c_08.scn
python ..\..\exe\txt\s2scn.py c_01.s c_01.scn
python ..\..\exe\txt\s2scn.py mug_sub.s mug_sub.scn


rem ---------------------------------
rem 一部スクリプトのコピー作成。別分岐の為
copy 1_36.scn 1_66.scn > nul
copy c_07.scn c_17.scn > nul
copy c_06.scn c_16.scn > nul
copy c_08.scn c_18.scn > nul
copy c_01.scn c_11.scn > nul


rem ---------------------------------
rem scnファイルをログ出力
for %%f in (0_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (1_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (2_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (3_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (4_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (5_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (6_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (7_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (8_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (9_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (a_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (b_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (c_*.scn) do ..\..\exe\txt\scn2log %%f


rem ---------------------------------
rem ファイル名を変更
move a_01b.log a_07.log > nul


rem ---------------------------------
rem ログを正規表現テキスト出力
for %%f in (*.log) do python ..\..\exe\txt\log2txt.py %%f %%~nf.txt


rem ---------------------------------
rem 一部特殊フォントをバイナリ化
for %%f in (*.txt) do python ..\..\exe\txt\txt2txt.py %%f


del *.s 2> nul
del *.scn 2>nul
del *.log 2>nul

cd ..
