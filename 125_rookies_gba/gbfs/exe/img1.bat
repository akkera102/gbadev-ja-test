@echo off

cd tmp

rem ---------------------------------
rem MIGをbmpに変換

for %%i in (*.MIG) do ..\..\exe\img\mig2bmp %%i

del *.MIG


rem ---------------------------------
rem IDX, PIXをbmpに変換

for %%i in (*.IDX) do ..\..\exe\img\anim2bmp %%i %%~ni.PIX

del *.IDX
del *.PIX


rem ---------------------------------
rem 差分画像を合成

python ..\..\exe\img\img_diff.py ASA_07.bmp BG_12.bmp
python ..\..\exe\img\img_diff.py ASA_08.bmp BG_12.bmp
python ..\..\exe\img\img_diff.py HAZU_02.bmp BG_11.bmp
python ..\..\exe\img\img_diff.py HAZU_03.bmp BG_11.bmp
python ..\..\exe\img\img_diff.py HAZU_04.bmp BG_11.bmp
python ..\..\exe\img\img_diff.py HAZU_05.bmp BG_11.bmp
python ..\..\exe\img\img_diff.py HIRO_07.bmp BG_34.bmp
python ..\..\exe\img\img_diff.py HIRO_08.bmp BG_34.bmp
python ..\..\exe\img\img_diff.py HIRO_09.bmp BG_34.bmp
python ..\..\exe\img\img_diff.py KYO_03.bmp BG_13.bmp
python ..\..\exe\img\img_diff.py KYO_04.bmp BG_13.bmp


rem ---------------------------------
rem 一部の画像カット

python ..\..\exe\img\img_cut.py ED_10.bmp 56 24 529 273
python ..\..\exe\img\img_cut.py ED_11.bmp 56 24 529 273
python ..\..\exe\img\img_cut.py TAI_08.bmp 72 24 496 288


rem ---------------------------------
rem キャラクタのマスクデータ作成

python ..\..\exe\img\img_mask.py AIHA_00.bmp
python ..\..\exe\img\img_mask.py AIHA_02.bmp
python ..\..\exe\img\img_mask.py AIHA_03.bmp
python ..\..\exe\img\img_mask.py ARI_00.bmp
python ..\..\exe\img\img_mask.py ASA_00.bmp
python ..\..\exe\img\img_mask.py ASA_02.bmp
python ..\..\exe\img\img_mask.py ASA_03.bmp
python ..\..\exe\img\img_mask.py ASA_04.bmp
python ..\..\exe\img\img_mask.py ASA_06.bmp
python ..\..\exe\img\img_mask.py CHUNE_00.bmp
python ..\..\exe\img\img_mask.py CHUNE_01.bmp
python ..\..\exe\img\img_mask.py CHUNE_02.bmp
python ..\..\exe\img\img_mask.py CHUNE_03.bmp
python ..\..\exe\img\img_mask.py HATA_00.bmp
python ..\..\exe\img\img_mask.py HAZU_00.bmp
python ..\..\exe\img\img_mask.py HAZU_01.bmp
python ..\..\exe\img\img_mask.py HAZU_06.bmp
python ..\..\exe\img\img_mask.py HIRO_00.bmp
python ..\..\exe\img\img_mask.py HIRO_01.bmp
python ..\..\exe\img\img_mask.py HIRO_02.bmp
python ..\..\exe\img\img_mask.py HIRO_03.bmp
python ..\..\exe\img\img_mask.py HIRO_04.bmp
python ..\..\exe\img\img_mask.py HIRO_05.bmp
python ..\..\exe\img\img_mask.py HIRO_06.bmp
python ..\..\exe\img\img_mask.py KYO_00.bmp
python ..\..\exe\img\img_mask.py KYO_01.bmp
python ..\..\exe\img\img_mask.py KYO_02.bmp
python ..\..\exe\img\img_mask.py OUME_00.bmp
python ..\..\exe\img\img_mask.py RISA_00.bmp
python ..\..\exe\img\img_mask.py RISA_01.bmp
python ..\..\exe\img\img_mask.py RISA_02.bmp
python ..\..\exe\img\img_mask.py RISA_03.bmp
python ..\..\exe\img\img_mask.py RISA_04.bmp
python ..\..\exe\img\img_mask.py RISA_05.bmp
python ..\..\exe\img\img_mask.py RISA_06.bmp
python ..\..\exe\img\img_mask.py RISA_07.bmp
python ..\..\exe\img\img_mask.py RISA_07A.bmp
python ..\..\exe\img\img_mask.py RISA_08.bmp
python ..\..\exe\img\img_mask.py RISA_08A.bmp
python ..\..\exe\img\img_mask.py RISA_08B.bmp
python ..\..\exe\img\img_mask.py RISA_09.bmp
python ..\..\exe\img\img_mask.py RISA_10.bmp
python ..\..\exe\img\img_mask.py RISA_12.bmp
python ..\..\exe\img\img_mask.py RISA_13.bmp
python ..\..\exe\img\img_mask.py RISA_14.bmp
python ..\..\exe\img\img_mask.py SAKI_00.bmp
python ..\..\exe\img\img_mask.py SAKI_01.bmp
python ..\..\exe\img\img_mask.py SAKI_02.bmp
python ..\..\exe\img\img_mask.py SAKI_03.bmp
python ..\..\exe\img\img_mask.py SAKI_04.bmp
python ..\..\exe\img\img_mask.py SATO_00.bmp
python ..\..\exe\img\img_mask.py SATO_02.bmp
python ..\..\exe\img\img_mask.py SATO_03.bmp
python ..\..\exe\img\img_mask.py SATO_04.bmp
python ..\..\exe\img\img_mask.py SEITO_00.bmp
python ..\..\exe\img\img_mask.py SUYA_00.bmp
python ..\..\exe\img\img_mask.py SUYA_01.bmp
python ..\..\exe\img\img_mask.py TOMO_00.bmp
python ..\..\exe\img\img_mask.py YUMI_00.bmp
python ..\..\exe\img\img_mask.py YUMI_02.bmp
python ..\..\exe\img\img_mask.py YUMI_04.bmp
python ..\..\exe\img\img_mask.py YUMI_05.bmp
python ..\..\exe\img\img_mask.py YUMI_06.bmp


rem ---------------------------------
rem キャラクタの透明色パレットを変更

python ..\..\exe\img\img_pal.py AIHA_00.bmp
python ..\..\exe\img\img_pal.py AIHA_02.bmp
python ..\..\exe\img\img_pal.py AIHA_03.bmp
python ..\..\exe\img\img_pal.py ARI_00.bmp
python ..\..\exe\img\img_pal.py ASA_00.bmp
python ..\..\exe\img\img_pal.py ASA_02.bmp
python ..\..\exe\img\img_pal.py ASA_03.bmp
python ..\..\exe\img\img_pal.py ASA_04.bmp
python ..\..\exe\img\img_pal.py ASA_06.bmp
python ..\..\exe\img\img_pal.py CHUNE_00.bmp
python ..\..\exe\img\img_pal.py CHUNE_01.bmp
python ..\..\exe\img\img_pal.py CHUNE_02.bmp
python ..\..\exe\img\img_pal.py CHUNE_03.bmp
python ..\..\exe\img\img_pal.py HATA_00.bmp
python ..\..\exe\img\img_pal.py HAZU_00.bmp
python ..\..\exe\img\img_pal.py HAZU_01.bmp
python ..\..\exe\img\img_pal.py HAZU_06.bmp
python ..\..\exe\img\img_pal.py HIRO_00.bmp
python ..\..\exe\img\img_pal.py HIRO_01.bmp
python ..\..\exe\img\img_pal.py HIRO_02.bmp
python ..\..\exe\img\img_pal.py HIRO_03.bmp
python ..\..\exe\img\img_pal.py HIRO_04.bmp
python ..\..\exe\img\img_pal.py HIRO_05.bmp
python ..\..\exe\img\img_pal.py HIRO_06.bmp
python ..\..\exe\img\img_pal.py KYO_00.bmp
python ..\..\exe\img\img_pal.py KYO_01.bmp
python ..\..\exe\img\img_pal.py KYO_02.bmp
python ..\..\exe\img\img_pal.py OUME_00.bmp
python ..\..\exe\img\img_pal.py RISA_00.bmp
python ..\..\exe\img\img_pal.py RISA_01.bmp
python ..\..\exe\img\img_pal.py RISA_02.bmp
python ..\..\exe\img\img_pal.py RISA_03.bmp
python ..\..\exe\img\img_pal.py RISA_04.bmp
python ..\..\exe\img\img_pal.py RISA_05.bmp
python ..\..\exe\img\img_pal.py RISA_06.bmp
python ..\..\exe\img\img_pal.py RISA_07.bmp
python ..\..\exe\img\img_pal.py RISA_07A.bmp
python ..\..\exe\img\img_pal.py RISA_08.bmp
python ..\..\exe\img\img_pal.py RISA_08A.bmp
python ..\..\exe\img\img_pal.py RISA_08B.bmp
python ..\..\exe\img\img_pal.py RISA_09.bmp
python ..\..\exe\img\img_pal.py RISA_10.bmp
python ..\..\exe\img\img_pal.py RISA_12.bmp
python ..\..\exe\img\img_pal.py RISA_13.bmp
python ..\..\exe\img\img_pal.py RISA_14.bmp
python ..\..\exe\img\img_pal.py SAKI_00.bmp
python ..\..\exe\img\img_pal.py SAKI_01.bmp
python ..\..\exe\img\img_pal.py SAKI_02.bmp
python ..\..\exe\img\img_pal.py SAKI_03.bmp
python ..\..\exe\img\img_pal.py SAKI_04.bmp
python ..\..\exe\img\img_pal.py SATO_00.bmp
python ..\..\exe\img\img_pal.py SATO_02.bmp
python ..\..\exe\img\img_pal.py SATO_03.bmp
python ..\..\exe\img\img_pal.py SATO_04.bmp
python ..\..\exe\img\img_pal.py SEITO_00.bmp
python ..\..\exe\img\img_pal.py SUYA_00.bmp
python ..\..\exe\img\img_pal.py SUYA_01.bmp
python ..\..\exe\img\img_pal.py TOMO_00.bmp
python ..\..\exe\img\img_pal.py YUMI_00.bmp
python ..\..\exe\img\img_pal.py YUMI_02.bmp
python ..\..\exe\img\img_pal.py YUMI_04.bmp
python ..\..\exe\img\img_pal.py YUMI_05.bmp
python ..\..\exe\img\img_pal.py YUMI_06.bmp


rem ---------------------------------
rem 全ての画像のリサイズ

for %%i in (*.bmp) do ..\..\exe\img\img_size.py %%i

del *.bmp


rem ---------------------------------
rem キャラクタの余白をカットして保存、さらにマスクファイルを生成

for %%i in (*_m.png) do python ..\..\exe\img\img_chr.py %%i

del *_m.png


rem ---------------------------------
rem GBA(mode3)に変換

for %%i in (*.png) do (
    echo grit... %%i
    ..\..\exe\img\grit %%i -gb -gB16 -ftb -gu16 -fh!
)

ren *.img.bin *.


rem ---------------------------------

cd ..
