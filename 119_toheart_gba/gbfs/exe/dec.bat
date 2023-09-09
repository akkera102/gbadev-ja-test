@echo off

rem ---------------------------------
rem LFG, LF2ファイルをBMPに変換

for %%i in (*.LFG) do (
    ..\exe\dec\th_bmp %%i
)

for %%i in (*.LF2) do (
    ..\exe\dec\th_bmp %%i
)

del *.LFG 2> nul
del *.LF2 2> nul

rem ---------------------------------
rem アルファブレンド用マスクファイル作成

python ..\exe\dec\th_pat_mask.py C0101.BMP
python ..\exe\dec\th_pat_mask.py C0102.BMP
python ..\exe\dec\th_pat_mask.py C0103.BMP
python ..\exe\dec\th_pat_mask.py C0104.BMP
python ..\exe\dec\th_pat_mask.py C0105.BMP
python ..\exe\dec\th_pat_mask.py C0106.BMP
python ..\exe\dec\th_pat_mask.py C0107.BMP
python ..\exe\dec\th_pat_mask.py C0108.BMP
python ..\exe\dec\th_pat_mask.py C0109.BMP
python ..\exe\dec\th_pat_mask.py C010A.BMP
python ..\exe\dec\th_pat_mask.py C010B.BMP
python ..\exe\dec\th_pat_mask.py C010C.BMP
python ..\exe\dec\th_pat_mask.py C010D.BMP
python ..\exe\dec\th_pat_mask.py C010E.BMP
python ..\exe\dec\th_pat_mask.py C0181.BMP
python ..\exe\dec\th_pat_mask.py C0182.BMP
python ..\exe\dec\th_pat_mask.py C0183.BMP
python ..\exe\dec\th_pat_mask.py C0184.BMP
python ..\exe\dec\th_pat_mask.py C0185.BMP
python ..\exe\dec\th_pat_mask.py C0186.BMP
python ..\exe\dec\th_pat_mask.py C0187.BMP
python ..\exe\dec\th_pat_mask.py C0188.BMP
python ..\exe\dec\th_pat_mask.py C0189.BMP
python ..\exe\dec\th_pat_mask.py C018A.BMP
python ..\exe\dec\th_pat_mask.py C018B.BMP
python ..\exe\dec\th_pat_mask.py C018C.BMP
python ..\exe\dec\th_pat_mask.py C018D.BMP
python ..\exe\dec\th_pat_mask.py C0201.BMP
python ..\exe\dec\th_pat_mask.py C0202.BMP
python ..\exe\dec\th_pat_mask.py C0203.BMP
python ..\exe\dec\th_pat_mask.py C0204.BMP
python ..\exe\dec\th_pat_mask.py C0205.BMP
python ..\exe\dec\th_pat_mask.py C0206.BMP
python ..\exe\dec\th_pat_mask.py C0207.BMP
python ..\exe\dec\th_pat_mask.py C0208.BMP
python ..\exe\dec\th_pat_mask.py C0209.BMP
python ..\exe\dec\th_pat_mask.py C020A.BMP
python ..\exe\dec\th_pat_mask.py C0301.BMP
python ..\exe\dec\th_pat_mask.py C0302.BMP
python ..\exe\dec\th_pat_mask.py C0303.BMP
python ..\exe\dec\th_pat_mask.py C0304.BMP
python ..\exe\dec\th_pat_mask.py C0305.BMP
python ..\exe\dec\th_pat_mask.py C0306.BMP
python ..\exe\dec\th_pat_mask.py C0307.BMP
python ..\exe\dec\th_pat_mask.py C0308.BMP
python ..\exe\dec\th_pat_mask.py C0309.BMP
python ..\exe\dec\th_pat_mask.py C030A.BMP
python ..\exe\dec\th_pat_mask.py C030B.BMP
python ..\exe\dec\th_pat_mask.py C030C.BMP
python ..\exe\dec\th_pat_mask.py C030D.BMP
python ..\exe\dec\th_pat_mask.py C030E.BMP
python ..\exe\dec\th_pat_mask.py C030F.BMP
python ..\exe\dec\th_pat_mask.py C0310.BMP
python ..\exe\dec\th_pat_mask.py C0311.BMP
python ..\exe\dec\th_pat_mask.py C0312.BMP
python ..\exe\dec\th_pat_mask.py C0313.BMP
python ..\exe\dec\th_pat_mask.py C0314.BMP
python ..\exe\dec\th_pat_mask.py C0401.BMP
python ..\exe\dec\th_pat_mask.py C0402.BMP
python ..\exe\dec\th_pat_mask.py C0403.BMP
python ..\exe\dec\th_pat_mask.py C0404.BMP
python ..\exe\dec\th_pat_mask.py C0405.BMP
python ..\exe\dec\th_pat_mask.py C0406.BMP
python ..\exe\dec\th_pat_mask.py C0407.BMP
python ..\exe\dec\th_pat_mask.py C0408.BMP
python ..\exe\dec\th_pat_mask.py C0409.BMP
python ..\exe\dec\th_pat_mask.py C040A.BMP
python ..\exe\dec\th_pat_mask.py C040B.BMP
python ..\exe\dec\th_pat_mask.py C040C.BMP
python ..\exe\dec\th_pat_mask.py C040D.BMP
python ..\exe\dec\th_pat_mask.py C040E.BMP
python ..\exe\dec\th_pat_mask.py C040F.BMP
python ..\exe\dec\th_pat_mask.py C0410.BMP
python ..\exe\dec\th_pat_mask.py C0411.BMP
python ..\exe\dec\th_pat_mask.py C0412.BMP
python ..\exe\dec\th_pat_mask.py C0413.BMP
python ..\exe\dec\th_pat_mask.py C0414.BMP
python ..\exe\dec\th_pat_mask.py C0415.BMP
python ..\exe\dec\th_pat_mask.py C0416.BMP
python ..\exe\dec\th_pat_mask.py C0417.BMP
python ..\exe\dec\th_pat_mask.py C0418.BMP
python ..\exe\dec\th_pat_mask.py C0501.BMP
python ..\exe\dec\th_pat_mask.py C0502.BMP
python ..\exe\dec\th_pat_mask.py C0503.BMP
python ..\exe\dec\th_pat_mask.py C0504.BMP
python ..\exe\dec\th_pat_mask.py C0505.BMP
python ..\exe\dec\th_pat_mask.py C0506.BMP
python ..\exe\dec\th_pat_mask.py C0507.BMP
python ..\exe\dec\th_pat_mask.py C0508.BMP
python ..\exe\dec\th_pat_mask.py C0509.BMP
python ..\exe\dec\th_pat_mask.py C050A.BMP
python ..\exe\dec\th_pat_mask.py C050B.BMP
python ..\exe\dec\th_pat_mask.py C050C.BMP
python ..\exe\dec\th_pat_mask.py C050D.BMP
python ..\exe\dec\th_pat_mask.py C050E.BMP
python ..\exe\dec\th_pat_mask.py C050F.BMP
python ..\exe\dec\th_pat_mask.py C0510.BMP
python ..\exe\dec\th_pat_mask.py C0511.BMP
python ..\exe\dec\th_pat_mask.py C0512.BMP
python ..\exe\dec\th_pat_mask.py C0513.BMP
python ..\exe\dec\th_pat_mask.py C0514.BMP
python ..\exe\dec\th_pat_mask.py C0515.BMP
python ..\exe\dec\th_pat_mask.py C0516.BMP
python ..\exe\dec\th_pat_mask.py C0517.BMP
python ..\exe\dec\th_pat_mask.py C0518.BMP
python ..\exe\dec\th_pat_mask.py C0601.BMP
python ..\exe\dec\th_pat_mask.py C0602.BMP
python ..\exe\dec\th_pat_mask.py C0603.BMP
python ..\exe\dec\th_pat_mask.py C0604.BMP
python ..\exe\dec\th_pat_mask.py C0605.BMP
python ..\exe\dec\th_pat_mask.py C0606.BMP
python ..\exe\dec\th_pat_mask.py C0607.BMP
python ..\exe\dec\th_pat_mask.py C0608.BMP
python ..\exe\dec\th_pat_mask.py C0609.BMP
python ..\exe\dec\th_pat_mask.py C060A.BMP
python ..\exe\dec\th_pat_mask.py C060B.BMP
python ..\exe\dec\th_pat_mask.py C060C.BMP
python ..\exe\dec\th_pat_mask.py C060D.BMP
python ..\exe\dec\th_pat_mask.py C060E.BMP
python ..\exe\dec\th_pat_mask.py C060F.BMP
python ..\exe\dec\th_pat_mask.py C0610.BMP
python ..\exe\dec\th_pat_mask.py C0611.BMP
python ..\exe\dec\th_pat_mask.py C0612.BMP
python ..\exe\dec\th_pat_mask.py C0613.BMP
python ..\exe\dec\th_pat_mask.py C0614.BMP
python ..\exe\dec\th_pat_mask.py C0615.BMP
python ..\exe\dec\th_pat_mask.py C0616.BMP
python ..\exe\dec\th_pat_mask.py C0617.BMP
python ..\exe\dec\th_pat_mask.py C0618.BMP
python ..\exe\dec\th_pat_mask.py C0619.BMP
python ..\exe\dec\th_pat_mask.py C0701.BMP
python ..\exe\dec\th_pat_mask.py C0702.BMP
python ..\exe\dec\th_pat_mask.py C0703.BMP
python ..\exe\dec\th_pat_mask.py C0704.BMP
python ..\exe\dec\th_pat_mask.py C0705.BMP
python ..\exe\dec\th_pat_mask.py C0706.BMP
python ..\exe\dec\th_pat_mask.py C0707.BMP
python ..\exe\dec\th_pat_mask.py C0708.BMP
python ..\exe\dec\th_pat_mask.py C0709.BMP
python ..\exe\dec\th_pat_mask.py C070A.BMP
python ..\exe\dec\th_pat_mask.py C070B.BMP
python ..\exe\dec\th_pat_mask.py C070C.BMP
python ..\exe\dec\th_pat_mask.py C070D.BMP
python ..\exe\dec\th_pat_mask.py C070E.BMP
python ..\exe\dec\th_pat_mask.py C070F.BMP
python ..\exe\dec\th_pat_mask.py C0710.BMP
python ..\exe\dec\th_pat_mask.py C0711.BMP
python ..\exe\dec\th_pat_mask.py C0801.BMP
python ..\exe\dec\th_pat_mask.py C0802.BMP
python ..\exe\dec\th_pat_mask.py C0803.BMP
python ..\exe\dec\th_pat_mask.py C0804.BMP
python ..\exe\dec\th_pat_mask.py C0805.BMP
python ..\exe\dec\th_pat_mask.py C0806.BMP
python ..\exe\dec\th_pat_mask.py C0807.BMP
python ..\exe\dec\th_pat_mask.py C0808.BMP
python ..\exe\dec\th_pat_mask.py C0809.BMP
python ..\exe\dec\th_pat_mask.py C080A.BMP
python ..\exe\dec\th_pat_mask.py C080B.BMP
python ..\exe\dec\th_pat_mask.py C080C.BMP
python ..\exe\dec\th_pat_mask.py C080D.BMP
python ..\exe\dec\th_pat_mask.py C080E.BMP
python ..\exe\dec\th_pat_mask.py C0901.BMP
python ..\exe\dec\th_pat_mask.py C0902.BMP
python ..\exe\dec\th_pat_mask.py C0903.BMP
python ..\exe\dec\th_pat_mask.py C0904.BMP
python ..\exe\dec\th_pat_mask.py C0A01.BMP
python ..\exe\dec\th_pat_mask.py C0A02.BMP
python ..\exe\dec\th_pat_mask.py C0A03.BMP
python ..\exe\dec\th_pat_mask.py C0A04.BMP
python ..\exe\dec\th_pat_mask.py C0A05.BMP
python ..\exe\dec\th_pat_mask.py C0A06.BMP
python ..\exe\dec\th_pat_mask.py C0B01.BMP
python ..\exe\dec\th_pat_mask.py C0C01.BMP
python ..\exe\dec\th_pat_mask.py C0C02.BMP
python ..\exe\dec\th_pat_mask.py C0C03.BMP
python ..\exe\dec\th_pat_mask.py C0D01.BMP
python ..\exe\dec\th_pat_mask.py C0D02.BMP
python ..\exe\dec\th_pat_mask.py C0E01.BMP
python ..\exe\dec\th_pat_mask.py C0E02.BMP
python ..\exe\dec\th_pat_mask.py C0E03.BMP
python ..\exe\dec\th_pat_mask.py C0E04.BMP
python ..\exe\dec\th_pat_mask.py C0F01.BMP
python ..\exe\dec\th_pat_mask.py C0F02.BMP
python ..\exe\dec\th_pat_mask.py C0F03.BMP
python ..\exe\dec\th_pat_mask.py C1001.BMP
python ..\exe\dec\th_pat_mask.py C1002.BMP
python ..\exe\dec\th_pat_mask.py C1101.BMP
python ..\exe\dec\th_pat_mask.py C1201.BMP
python ..\exe\dec\th_pat_mask.py C1202.BMP
python ..\exe\dec\th_pat_mask.py C1203.BMP
python ..\exe\dec\th_pat_mask.py C1204.BMP
python ..\exe\dec\th_pat_mask.py C1205.BMP
python ..\exe\dec\th_pat_mask.py C1206.BMP
python ..\exe\dec\th_pat_mask.py C1207.BMP
python ..\exe\dec\th_pat_mask.py C1208.BMP
python ..\exe\dec\th_pat_mask.py C1209.BMP
python ..\exe\dec\th_pat_mask.py C120A.BMP
python ..\exe\dec\th_pat_mask.py C120B.BMP
python ..\exe\dec\th_pat_mask.py C120C.BMP
python ..\exe\dec\th_pat_mask.py C120D.BMP
python ..\exe\dec\th_pat_mask.py C1301.BMP
python ..\exe\dec\th_pat_mask.py C1401.BMP
python ..\exe\dec\th_pat_mask.py C1402.BMP
python ..\exe\dec\th_pat_mask.py C1501.BMP
python ..\exe\dec\th_pat_mask.py C1601.BMP
python ..\exe\dec\th_pat_mask.py C1602.BMP
python ..\exe\dec\th_pat_mask.py C1603.BMP
python ..\exe\dec\th_pat_mask.py C160B.BMP
python ..\exe\dec\th_pat_mask.py C160C.BMP
python ..\exe\dec\th_pat_mask.py C1801.BMP
python ..\exe\dec\th_pat_mask.py C1901.BMP
python ..\exe\dec\th_pat_mask.py C1A01.BMP
python ..\exe\dec\th_pat_mask.py C1B01.BMP
python ..\exe\dec\th_pat_mask.py C1D01.BMP
python ..\exe\dec\th_pat_mask.py C1D02.BMP
python ..\exe\dec\th_pat_mask.py C1D03.BMP
python ..\exe\dec\th_pat_mask.py C1D04.BMP
python ..\exe\dec\th_pat_mask.py C1E01.BMP
python ..\exe\dec\th_pat_mask.py C1E02.BMP
python ..\exe\dec\th_pat_mask.py C1E03.BMP
python ..\exe\dec\th_pat_mask.py C1E04.BMP
python ..\exe\dec\th_pat_mask.py C1E05.BMP
python ..\exe\dec\th_pat_mask.py C1E06.BMP
python ..\exe\dec\th_pat_mask.py C1E07.BMP
python ..\exe\dec\th_pat_mask.py C1E08.BMP
python ..\exe\dec\th_pat_mask.py C1E09.BMP
python ..\exe\dec\th_pat_mask.py C1E0A.BMP
python ..\exe\dec\th_pat_mask.py C1E0B.BMP
python ..\exe\dec\th_pat_mask.py C1E0C.BMP
python ..\exe\dec\th_pat_mask.py C1E0D.BMP
python ..\exe\dec\th_pat_mask.py C1E0E.BMP
python ..\exe\dec\th_pat_mask.py C1E0F.BMP
python ..\exe\dec\th_pat_mask.py C1E10.BMP
python ..\exe\dec\th_pat_mask.py C1E11.BMP
python ..\exe\dec\th_pat_mask.py C1E12.BMP
python ..\exe\dec\th_pat_mask.py C1E13.BMP
python ..\exe\dec\th_pat_mask.py C1E14.BMP
python ..\exe\dec\th_pat_mask.py C1E15.BMP
python ..\exe\dec\th_pat_mask.py C1E16.BMP
python ..\exe\dec\th_pat_mask.py C1E17.BMP
python ..\exe\dec\th_pat_mask.py C1E18.BMP
python ..\exe\dec\th_pat_mask.py C1E19.BMP
python ..\exe\dec\th_pat_mask.py C1E1A.BMP
python ..\exe\dec\th_pat_mask.py C1E1B.BMP
python ..\exe\dec\th_pat_mask.py C1E1C.BMP
python ..\exe\dec\th_pat_mask.py C1E1D.BMP
python ..\exe\dec\th_pat_mask.py C1E1E.BMP
python ..\exe\dec\th_pat_mask.py C1E1F.BMP
python ..\exe\dec\th_pat_mask.py C1E20.BMP
python ..\exe\dec\th_pat_mask.py C1E21.BMP
python ..\exe\dec\th_pat_mask.py C1E22.BMP
python ..\exe\dec\th_pat_mask.py C1F01.BMP
python ..\exe\dec\th_pat_mask.py C1F02.BMP
python ..\exe\dec\th_pat_mask.py C1F03.BMP
python ..\exe\dec\th_pat_mask.py C1F04.BMP
python ..\exe\dec\th_pat_mask.py C1F05.BMP
python ..\exe\dec\th_pat_mask.py C1F06.BMP

rem 時計
python ..\exe\dec\th_pat_mask.py OC_00.BMP


rem ---------------------------------
rem タイトルと背景を合成

python ..\exe\dec\th_pat_title.py


rem ---------------------------------
rem リーフロゴを背景付きに変更

python ..\exe\dec\th_pat_leaf.py


rem ---------------------------------
rem オープニングの写真を背景付きに変更

python ..\exe\dec\th_pat_op.py OP00.BMP
python ..\exe\dec\th_pat_op.py OP01.BMP
python ..\exe\dec\th_pat_op.py OP02.BMP
python ..\exe\dec\th_pat_op.py OP03.BMP


rem ---------------------------------
rem 校舎屋上の背景と虹を合成

python ..\exe\dec\th_pat_C1C01.py

del VF6.BMP 2> nul
ren C1C01.BMP VF6.BMP


rem ---------------------------------
rem マスクファイル修正

python ..\exe\dec\th_pat_C1205.py


rem ---------------------------------
rem 一部画像を背景画像としてリネーム

del VF0.BMP 2> nul
del VF1.BMP 2> nul
del VF2.BMP 2> nul
del VF3.BMP 2> nul
del VF4.BMP 2> nul
del VF5.BMP 2> nul

ren OP00.BMP VF0.BMP
ren OP01.BMP VF1.BMP
ren OP02.BMP VF2.BMP
ren OP03.BMP VF3.BMP
ren LEAF.BMP VF4.BMP
ren TITLE2.BMP VF5.BMP


rem ---------------------------------
rem リサイズ

for %%i in (*.BMP) do (
    python ..\exe\dec\th_resize.py %%i
)

rem ---------------------------------
rem GBAに画像変換

for %%i in (*.BMP) do (
    echo grit %%i
    ..\exe\dec\grit.exe %%i -gb -gB16 -ftb -gu16 -fh!
)

rem ---------------------------------
rem マスクファイルを更にリサイズ

for %%i in (*_M.BMP) do (
    python ..\exe\dec\th_mask.py %%i
)

rem ---------------------------------
rem lz77圧縮

for %%i in (*.img.bin) do (
    echo gbalzss %%i
    ..\\exe\\dec\\gbalzss.exe e %%i %%~ni
)

rem ---------------------------------
rem imgファイルパラメータ付与

for %%i in (*.BMP) do (
    python ..\exe\dec\th_param.py %%i
)


del *.img.bin 2> nul
del *.BMP 2> nul

