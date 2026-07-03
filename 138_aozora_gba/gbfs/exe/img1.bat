@echo off

cd tmp

rem ---------------------------------
rem GBAで使用しないファイルを削除

del COCKPIT_DIAG_NEXT.SPD
del COCKPIT_EVENT_BASE.SPD
del COCKPIT_EVENT_FUTUU.SPD
del COCKPIT_EVENT_FUTUU_ON.SPD
del COCKPIT_EVENT_HAYAI.SPD
del COCKPIT_EVENT_HAYAI_ON.SPD
del COCKPIT_EVENT_LOAD.SPD
del COCKPIT_EVENT_LOAD_ON.SPD
del COCKPIT_EVENT_MESBG.SPD
del COCKPIT_EVENT_OKURI.SPD
del COCKPIT_EVENT_OKURI_ON.SPD
del COCKPIT_EVENT_OSOI.SPD
del COCKPIT_EVENT_OSOI_ON.SPD
del COCKPIT_EVENT_PAGE.SPD
del COCKPIT_EVENT_PAGE_ON.SPD
del COCKPIT_EVENT_SAVE.SPD
del COCKPIT_EVENT_SAVE_ON.SPD
del COCKPIT_EVENT_SYSTEM.SPD
del COCKPIT_EVENT_SYSTEM_ON.SPD
del COCKPIT_EVENT_TUGINO.SPD
del COCKPIT_EVENT_TUGINO_ON.SPD
del COCKPIT_MES_BG.SPD
del COCKPIT_TR00.SPD
del COCKPIT_TR01.SPD
del COCKPIT_YOKO_BASE.SPD
del COCKPIT_YOKO_FUTUU.SPD
del COCKPIT_YOKO_FUTUU_ON.SPD
del COCKPIT_YOKO_HAYAI.SPD
del COCKPIT_YOKO_HAYAI_ON.SPD
del COCKPIT_YOKO_LOAD.SPD
del COCKPIT_YOKO_LOAD_ON.SPD
del COCKPIT_YOKO_OKURI.SPD
del COCKPIT_YOKO_OKURI_ON.SPD
del COCKPIT_YOKO_OSOI.SPD
del COCKPIT_YOKO_OSOI_ON.SPD
del COCKPIT_YOKO_PAGE.SPD
del COCKPIT_YOKO_PAGE_ON.SPD
del COCKPIT_YOKO_SAVE.SPD
del COCKPIT_YOKO_SAVE_ON.SPD
del COCKPIT_YOKO_SYSTEM.SPD
del COCKPIT_YOKO_SYSTEM2.SPD
del COCKPIT_YOKO_SYSTEM_ON.SPD
del COCKPIT_YOKO_TATE.SPD
del COCKPIT_YOKO_TATE_ON.SPD
del COCKPIT_YOKO_TUGINO.SPD
del COCKPIT_YOKO_TUGINO_ON.SPD
del COCKPIT_YOKO_YOKO.SPD
del COCKPIT_YOKO_YOKO_ON.SPD
del CONF_1_OFF.SPD
del CONF_1_ON.SPD
del CONF_2_OFF.SPD
del CONF_2_ON.SPD
del CONF_3_OFF.SPD
del CONF_3_ON.SPD
del CONF_4_OFF.SPD
del CONF_4_ON.SPD
del CONF_5_OFF.SPD
del CONF_5_ON.SPD
del CONF_ARI_OFF.SPD
del CONF_ARI_ON.SPD
del CONF_MODORU_OFF.SPD
del CONF_MODORU_ON.SPD
del CONF_NAME_OFF.SPD
del CONF_NAME_ON.SPD
del CONF_NASHI_OFF.SPD
del CONF_NASHI_ON.SPD
del CONF_NASI_OFF.SPD
del CONF_NASI_ON.SPD
del CONF_SAIDAI_OFF.SPD
del CONF_SAIDAI_ON.SPD
del CONF_SCRN_0.SPD
del CONF_SCRN_1.SPD
del CONF_SHIORI_OFF.SPD
del CONF_SHIORI_ON.SPD
del CONF_SHURYOU_OFF.SPD
del CONF_SHURYOU_ON.SPD
del CONF_TIT_OFF.SPD
del CONF_TIT_ON.SPD
del CONF_TUUJOU_OFF.SPD
del CONF_TUUJOU_ON.SPD
del CONF_WIN_0.SPD
del CONF_WIN_1.SPD
del CONFIG_BASE.SPD
del ETURAN_AKI1.SPD
del ETURAN_AKI2.SPD
del ETURAN_FUYU1.SPD
del ETURAN_FUYU2.SPD
del ETURAN_FUYU3.SPD
del ETURAN_HARU.SPD
del ETURAN_MODORU.SPD
del ETURAN_NATU1.SPD
del ETURAN_NATU2.SPD
del ETURAN_NATU3.SPD
del ETURAN_SHIGYOU.SPD
del KAKUNIN_EXIT_BASE.SPD
del KAKUNIN_LOAD_BASE.SPD
del KAKUNIN_NO_ON.SPD
del KAKUNIN_SAVE_BASE.SPD
del KAKUNIN_SHIORI_BASE.SPD
del KAKUNIN_SHOKIKA_BASE.SPD
del KAKUNIN_YES_ON.SPD
del KISETU_AKI_0.SPD
del KISETU_AKI_1.SPD
del KISETU_BASE.SPD
del KISETU_FUYU_0.SPD
del KISETU_FUYU_1.SPD
del KISETU_HARU_0.SPD
del KISETU_HARU_1.SPD
del KISETU_LINE.SPD
del KISETU_MODORU_1.SPD
del KISETU_NATU_0.SPD
del KISETU_NATU_1.SPD
del KISETU_OMAKE_0.SPD
del KISETU_OMAKE_1.SPD
del KISETU_SAISHO_0.SPD
del KISETU_SAISHO_1.SPD
del KNIGHTS.SPD
del LOAD_BLUE.SPD
del LOAD_RED.SPD
del LOAD_WHITE.SPD
del NAME_AIUEO.SPD
del NAME_BAK.SPD
del NAME_BASE.SPD
del NAME_CAPS.SPD
del NAME_CUR_DOWN.SPD
del NAME_CUR_LINE.SPD
del NAME_CUR_UP.SPD
del NAME_DEL.SPD
del NAME_DOWN.SPD
del NAME_HIRAGANA.SPD
del NAME_KANA.SPD
del NAME_KANJI.SPD
del NAME_KATAKANA.SPD
del NAME_LINE.SPD
del NAME_OK.SPD
del NAME_UP.SPD
del SAVE_BLUE.SPD
del SAVE_RED.SPD
del SAVE_WHITE.SPD
del SHIORI_ANK_0.SPD
del SHIORI_ANK_0_R.SPD
del SHIORI_ANK_1.SPD
del SHIORI_ANK_1_R.SPD
del SHIORI_ANK_2.SPD
del SHIORI_ANK_2_R.SPD
del SHIORI_ANK_3.SPD
del SHIORI_ANK_3_R.SPD
del SHIORI_ANK_4.SPD
del SHIORI_ANK_4_R.SPD
del SHIORI_ANK_5.SPD
del SHIORI_ANK_5_R.SPD
del SHIORI_ANK_6.SPD
del SHIORI_ANK_6_R.SPD
del SHIORI_ANK_7.SPD
del SHIORI_ANK_7_R.SPD
del SHIORI_ANK_8.SPD
del SHIORI_ANK_8_R.SPD
del SHIORI_ANK_9.SPD
del SHIORI_ANK_9_R.SPD
del SHIORI_ANK_CORON.SPD
del SHIORI_ANK_CORON_R.SPD
del SHIORI_ANK_NO.SPD
del SHIORI_ANK_NO_R.SPD
del SHIORI_ANK_SLASH.SPD
del SHIORI_ANK_SLASH_R.SPD
del SHIORI_BASE.SPD
del SHIORI_BLUE01.SPD
del SHIORI_BLUE01_.SPD
del SHIORI_BLUE02.SPD
del SHIORI_BLUE02_.SPD
del SHIORI_BLUE03.SPD
del SHIORI_BLUE03_.SPD
del SHIORI_CUR_DOWN_1.SPD
del SHIORI_CUR_UP_1.SPD
del SHIORI_DEGIT00.SPD
del SHIORI_DEGIT00_R.SPD
del SHIORI_DEGIT01.SPD
del SHIORI_DEGIT01_R.SPD
del SHIORI_DEGIT02.SPD
del SHIORI_DEGIT02_R.SPD
del SHIORI_DEGIT03.SPD
del SHIORI_DEGIT03_R.SPD
del SHIORI_DEGIT04.SPD
del SHIORI_DEGIT04_R.SPD
del SHIORI_DEGIT05.SPD
del SHIORI_DEGIT05_R.SPD
del SHIORI_DEGIT06.SPD
del SHIORI_DEGIT06_R.SPD
del SHIORI_DEGIT07.SPD
del SHIORI_DEGIT07_R.SPD
del SHIORI_DEGIT08.SPD
del SHIORI_DEGIT08_R.SPD
del SHIORI_DEGIT09.SPD
del SHIORI_DEGIT09_R.SPD
del SHIORI_ETURAN.SPD
del SHIORI_HH.SPD
del SHIORI_HH_R.SPD
del SHIORI_KAN_AKI.SPD
del SHIORI_KAN_AKI_R.SPD
del SHIORI_KAN_FUYU.SPD
del SHIORI_KAN_FUYU_R.SPD
del SHIORI_KAN_HAJI.SPD
del SHIORI_KAN_HAJI_R.SPD
del SHIORI_KAN_HARU.SPD
del SHIORI_KAN_HARU_R.SPD
del SHIORI_KAN_NATU.SPD
del SHIORI_KAN_NATU_R.SPD
del SHIORI_KAN_OWARI.SPD
del SHIORI_KAN_OWARI_R.SPD
del SHIORI_MM.SPD
del SHIORI_MM_R.SPD
del SHIORI_PINK01.SPD
del SHIORI_PINK01_.SPD
del SHIORI_PINK02.SPD
del SHIORI_PINK02_.SPD
del SHIORI_PINK03.SPD
del SHIORI_PINK03_.SPD
del SHIORI_SAISHO.SPD
del SHIORI_SEL_BAR.SPD
del SHIORI_SHOKIKA.SPD
del SHIORI_TUDUKI.SPD
del SHIORI_WHITE01.SPD
del SHIORI_WHITE01_.SPD
del SHIORI_WHITE02.SPD
del SHIORI_WHITE02_.SPD
del SHIORI_WHITE03.SPD
del SHIORI_WHITE03_.SPD
del SUJI_01.SPD
del SUJI_02.SPD
del SUJI_03.SPD
del SUJI_04.SPD
del SUJI_05.SPD
del SUJI_06.SPD
del SUJI_07.SPD
del SUJI_08.SPD
del SUJI_09.SPD
del SUJI_10.SPD
del SUJI_11.SPD
del SUJI_12.SPD
del SUJI_13.SPD
del SUJI_14.SPD
del SUJI_15.SPD
del SUJI_16.SPD
del TH_GRP01.SPD
del TH_GRP01B.SPD
del TH_GRP02.SPD
del TH_GRP03.SPD
del TH_GRP03B.SPD
del TH_GRP04.SPD
del TH_GRP04B.SPD
del TH_GRP04C.SPD
del TH_GRP05.SPD
del TH_GRP06.SPD
del TH_GRP07.SPD
del TH_GRP08.SPD
del TH_GRP09.SPD
del TH_GRP10.SPD
del TH_GRP11.SPD
del TH_GRP11B.SPD
del TH_GRP11C.SPD
del TH_GRP12.SPD
del TH_GRP13.SPD
del TH_GRP14.SPD
del TH_GRP15.SPD
del TH_GRP16.SPD
del TH_GRP16B.SPD
del TH_GRP16C.SPD
del TH_GRP17.SPD
del TH_GRP18.SPD
del TH_GRP19.SPD
del TH_GRP19B.SPD
del TH_GRP19B2.SPD
del TH_GRP19C.SPD
del TH_GRP19D.SPD
del TH_GRP19E.SPD
del TH_GRP19F.SPD
del TH_GRP19G.SPD
del TH_GRP19H.SPD
del TH_GRP20.SPD
del TH_GRP20B.SPD
del TH_GRP21.SPD
del TH_GRP22.SPD
del TH_GRP22B.SPD
del TH_GRP23.SPD
del TH_GRP25.SPD
del TH_GRP26.SPD
del TH_GRP27.SPD
del TH_GRP27B.SPD
del TH_GRP28.SPD
del TH_GRP29.SPD
del TH_GRP30B.SPD
del TH_GRP30D.SPD
del TH_GRP30E.SPD
del TH_GRP31.SPD
del TH_GRP32.SPD
del TH_GRP33.SPD
del TH_GRP33B.SPD
del TH_GRP34.SPD
del TH_GRP34B.SPD
del TH_GRP35.SPD
del TH_GRP35B.SPD
del TH_GRP36.SPD
del TH_GRP37.SPD
del TH_GRP38.SPD
del TH_GRP39.SPD
del TH_GRP40.SPD
del TH_GRP41.SPD
del TH_GRP42B.SPD
del TH_GRP42C.SPD
del TH_GRP42D.SPD
del TH_GRP42E.SPD
del TH_GRP43.SPD
del TH_GRP45.SPD
del TH_GRP47.SPD
del TH_GRP48.SPD
del TH_GRP51.SPD
del TH_GRP53.SPD
del TH_GRP54.SPD
del TH_GRP55.SPD
del TH_GRP58.SPD
del TH_GRP59.SPD
del TH_GRP60.SPD
del TH_GRP60B.SPD
del TH_HGRP01.SPD
del TH_HGRP01B.SPD
del TH_HGRP02.SPD
del TH_HGRP03.SPD
del TH_HGRP04.SPD
del TH_HGRP05.SPD
del TH_HGRP06.SPD
del TH_HGRP06B.SPD
del TH_HGRP07.SPD
del TH_HGRP08.SPD
del TH_HGRP09.SPD
del TH_HGRP10.SPD
del TH_HGRP11.SPD
del TH_HGRP12.SPD
del TH_HGRP12B.SPD
del TH_HGRP13.SPD
del TH_HGRP14.SPD
del TH_HGRP15.SPD
del TH_HGRP15B.SPD
del TH_HGRP16.SPD
del TH_HGRP17.SPD
del TH_HGRP18.SPD
del TH_HGRP19.SPD
del TH_HGRP20.SPD
del TH_HGRP21.SPD
del TH_HGRP22.SPD
del TH_HGRP23.SPD
del TH_HGRP24.SPD
del TH_HGRP25.SPD
del TH_HGRP26.SPD
del TH_HGRP27.SPD
del TH_HGRP28.SPD
del TH_HGRP29.SPD
del TH_HGRP30B.SPD
del TH_HGRP30C.SPD
del TH_HGRP31.SPD
del TH_HGRP31B.SPD
del TH_HGRP31C.SPD
del TH_HGRP31E.SPD
del TH_HGRP32.SPD
del TH_HGRP32B.SPD
del TH_HGRP33.SPD
del TH_HGRP34.SPD
del TH_HGRP35.SPD
del TH_HGRP36.SPD
del TH_HGRP37.SPD
del TH_HGRP38.SPD
del TH_HGRP39.SPD

rem ゲーム内で未使用のファイルを削除
del BG02D.SPD
del BG02F.SPD
del BG07D.SPD
del BG11C.SPD
del AI03DZ.SPD
del AI03Z.SPD
del ASU09B.SPD
del ASU09D.SPD
del ASU10.SPD
del KAED01DZ.SPD
del KAED04D.SPD
del YUKA02E.SPD
del YUKA03EZ.SPD
del YUKA05D.SPD
del YUKA05E.SPD
del YUKA07E.SPD
del YUKA08.SPD
del YUKA08C.SPD
del YUKA08D.SPD
del YUKA08E.SPD


rem ---------------------------------
rem SPDをBMPに変換

for %%i in (*.SPD) do ..\..\exe\img\spd2bmp %%i

del *.SPD


rem ---------------------------------
rem キャラクタのマスクファイルを作成

..\..\exe\img\bmp2msk ACT00.bmp
..\..\exe\img\bmp2msk ACT01.bmp
..\..\exe\img\bmp2msk ACT02.bmp
..\..\exe\img\bmp2msk ACT03.bmp
..\..\exe\img\bmp2msk ACT03B.bmp
..\..\exe\img\bmp2msk ACT04.bmp
..\..\exe\img\bmp2msk ACT05.bmp
..\..\exe\img\bmp2msk AI01.bmp
..\..\exe\img\bmp2msk AI01B.bmp
..\..\exe\img\bmp2msk AI01C.bmp
..\..\exe\img\bmp2msk AI01D.bmp
..\..\exe\img\bmp2msk AI02.bmp
..\..\exe\img\bmp2msk AI02B.bmp
..\..\exe\img\bmp2msk AI02C.bmp
..\..\exe\img\bmp2msk AI02D.bmp
..\..\exe\img\bmp2msk AI03.bmp
..\..\exe\img\bmp2msk AI03B.bmp
..\..\exe\img\bmp2msk AI03BZ.bmp
..\..\exe\img\bmp2msk AI03C.bmp
..\..\exe\img\bmp2msk AI03CZ.bmp
..\..\exe\img\bmp2msk AI03D.bmp
..\..\exe\img\bmp2msk AI04.bmp
..\..\exe\img\bmp2msk AI04B.bmp
..\..\exe\img\bmp2msk AI04C.bmp
..\..\exe\img\bmp2msk AI04D.bmp
..\..\exe\img\bmp2msk AI05.bmp
..\..\exe\img\bmp2msk AI05B.bmp
..\..\exe\img\bmp2msk AI05C.bmp
..\..\exe\img\bmp2msk AI05D.bmp
..\..\exe\img\bmp2msk AI06.bmp
..\..\exe\img\bmp2msk AI06B.bmp
..\..\exe\img\bmp2msk AI06C.bmp
..\..\exe\img\bmp2msk AI06D.bmp
..\..\exe\img\bmp2msk ASU01.bmp
..\..\exe\img\bmp2msk ASU01B.bmp
..\..\exe\img\bmp2msk ASU01C.bmp
..\..\exe\img\bmp2msk ASU02.bmp
..\..\exe\img\bmp2msk ASU02B.bmp
..\..\exe\img\bmp2msk ASU02C.bmp
..\..\exe\img\bmp2msk ASU03.bmp
..\..\exe\img\bmp2msk ASU03B.bmp
..\..\exe\img\bmp2msk ASU03C.bmp
..\..\exe\img\bmp2msk ASU04.bmp
..\..\exe\img\bmp2msk ASU04B.bmp
..\..\exe\img\bmp2msk ASU04C.bmp
..\..\exe\img\bmp2msk ASU05.bmp
..\..\exe\img\bmp2msk ASU05B.bmp
..\..\exe\img\bmp2msk ASU05C.bmp
..\..\exe\img\bmp2msk ASU06.bmp
..\..\exe\img\bmp2msk ASU06B.bmp
..\..\exe\img\bmp2msk ASU06C.bmp
..\..\exe\img\bmp2msk ASU09C.bmp
..\..\exe\img\bmp2msk ASU10B.bmp
..\..\exe\img\bmp2msk ASU10C.bmp
..\..\exe\img\bmp2msk DOU01.bmp
..\..\exe\img\bmp2msk DOU02.bmp
..\..\exe\img\bmp2msk DOU03.bmp
..\..\exe\img\bmp2msk DOU04.bmp
..\..\exe\img\bmp2msk ERIK01.bmp
..\..\exe\img\bmp2msk ERIK02.bmp
..\..\exe\img\bmp2msk ERIK04.bmp
..\..\exe\img\bmp2msk ERIK05.bmp
..\..\exe\img\bmp2msk ERIK06.bmp
..\..\exe\img\bmp2msk FUMI01.bmp
..\..\exe\img\bmp2msk FUMI01C.bmp
..\..\exe\img\bmp2msk FUMI02.bmp
..\..\exe\img\bmp2msk FUMI02B.bmp
..\..\exe\img\bmp2msk FUMI02C.bmp
..\..\exe\img\bmp2msk FUMI03.bmp
..\..\exe\img\bmp2msk FUMI03C.bmp
..\..\exe\img\bmp2msk FUMI04.bmp
..\..\exe\img\bmp2msk FUMI04C.bmp
..\..\exe\img\bmp2msk FUMI05.bmp
..\..\exe\img\bmp2msk FUMI05C.bmp
..\..\exe\img\bmp2msk FUMI07.bmp
..\..\exe\img\bmp2msk FUMI07C.bmp
..\..\exe\img\bmp2msk FUMI08.bmp
..\..\exe\img\bmp2msk FUMI08C.bmp
..\..\exe\img\bmp2msk KAED01.bmp
..\..\exe\img\bmp2msk KAED01B.bmp
..\..\exe\img\bmp2msk KAED01BZ.bmp
..\..\exe\img\bmp2msk KAED01C.bmp
..\..\exe\img\bmp2msk KAED01CZ.bmp
..\..\exe\img\bmp2msk KAED01D.bmp
..\..\exe\img\bmp2msk KAED01E.bmp
..\..\exe\img\bmp2msk KAED01EZ.bmp
..\..\exe\img\bmp2msk KAED01Z.bmp
..\..\exe\img\bmp2msk KAED02.bmp
..\..\exe\img\bmp2msk KAED02B.bmp
..\..\exe\img\bmp2msk KAED02C.bmp
..\..\exe\img\bmp2msk KAED02D.bmp
..\..\exe\img\bmp2msk KAED02E.bmp
..\..\exe\img\bmp2msk KAED03.bmp
..\..\exe\img\bmp2msk KAED03B.bmp
..\..\exe\img\bmp2msk KAED03C.bmp
..\..\exe\img\bmp2msk KAED03D.bmp
..\..\exe\img\bmp2msk KAED03E.bmp
..\..\exe\img\bmp2msk KAED04.bmp
..\..\exe\img\bmp2msk KAED04B.bmp
..\..\exe\img\bmp2msk KAED04C.bmp
..\..\exe\img\bmp2msk KAED04E.bmp
..\..\exe\img\bmp2msk SAIG01.bmp
..\..\exe\img\bmp2msk SAIG02.bmp
..\..\exe\img\bmp2msk SAIG03.bmp
..\..\exe\img\bmp2msk SAIG04.bmp
..\..\exe\img\bmp2msk SOUS01.bmp
..\..\exe\img\bmp2msk SOUS02.bmp
..\..\exe\img\bmp2msk SOUS03.bmp
..\..\exe\img\bmp2msk SOUS04.bmp
..\..\exe\img\bmp2msk TUJI01.bmp
..\..\exe\img\bmp2msk TUJI02.bmp
..\..\exe\img\bmp2msk TUJI03.bmp
..\..\exe\img\bmp2msk TUJI04.bmp
..\..\exe\img\bmp2msk YUKA01.bmp
..\..\exe\img\bmp2msk YUKA01B.bmp
..\..\exe\img\bmp2msk YUKA01C.bmp
..\..\exe\img\bmp2msk YUKA01D.bmp
..\..\exe\img\bmp2msk YUKA01E.bmp
..\..\exe\img\bmp2msk YUKA01Z.bmp
..\..\exe\img\bmp2msk YUKA02.bmp
..\..\exe\img\bmp2msk YUKA02B.bmp
..\..\exe\img\bmp2msk YUKA02C.bmp
..\..\exe\img\bmp2msk YUKA02D.bmp
..\..\exe\img\bmp2msk YUKA03.bmp
..\..\exe\img\bmp2msk YUKA03B.bmp
..\..\exe\img\bmp2msk YUKA03BZ.bmp
..\..\exe\img\bmp2msk YUKA03C.bmp
..\..\exe\img\bmp2msk YUKA03CZ.bmp
..\..\exe\img\bmp2msk YUKA03D.bmp
..\..\exe\img\bmp2msk YUKA03E.bmp
..\..\exe\img\bmp2msk YUKA03Z.bmp
..\..\exe\img\bmp2msk YUKA04.bmp
..\..\exe\img\bmp2msk YUKA04B.bmp
..\..\exe\img\bmp2msk YUKA04C.bmp
..\..\exe\img\bmp2msk YUKA04D.bmp
..\..\exe\img\bmp2msk YUKA04E.bmp
..\..\exe\img\bmp2msk YUKA05.bmp
..\..\exe\img\bmp2msk YUKA05B.bmp
..\..\exe\img\bmp2msk YUKA05C.bmp
..\..\exe\img\bmp2msk YUKA06.bmp
..\..\exe\img\bmp2msk YUKA06B.bmp
..\..\exe\img\bmp2msk YUKA06C.bmp
..\..\exe\img\bmp2msk YUKA06D.bmp
..\..\exe\img\bmp2msk YUKA06E.bmp
..\..\exe\img\bmp2msk YUKA07.bmp
..\..\exe\img\bmp2msk YUKA07B.bmp
..\..\exe\img\bmp2msk YUKA07C.bmp
..\..\exe\img\bmp2msk YUKA07D.bmp

..\..\exe\img\bmp2msk SHIORI_AI_0.bmp
..\..\exe\img\bmp2msk SHIORI_AI_1.bmp
..\..\exe\img\bmp2msk SHIORI_AMANE_0.bmp
..\..\exe\img\bmp2msk SHIORI_AMANE_1.bmp
..\..\exe\img\bmp2msk SHIORI_ASUNA_0.bmp
..\..\exe\img\bmp2msk SHIORI_ASUNA_1.bmp
..\..\exe\img\bmp2msk SHIORI_FUMINO_0.bmp
..\..\exe\img\bmp2msk SHIORI_FUMINO_1.bmp
..\..\exe\img\bmp2msk SHIORI_YUKA_0.bmp
..\..\exe\img\bmp2msk SHIORI_YUKA_1.bmp


rem ---------------------------------
rem トリミング

python ..\..\exe\img\img_cut1.py BG01B.bmp 34
python ..\..\exe\img\img_cut1.py BG01C.bmp 34
python ..\..\exe\img\img_cut1.py BG01D.bmp 34
python ..\..\exe\img\img_cut1.py BG01E.bmp 34
python ..\..\exe\img\img_cut1.py BG01.bmp 34
python ..\..\exe\img\img_cut1.py BG02.bmp 0
python ..\..\exe\img\img_cut1.py BG02B.bmp 0
python ..\..\exe\img\img_cut1.py BG02C.bmp 0
python ..\..\exe\img\img_cut1.py BG02E.bmp 0
python ..\..\exe\img\img_cut1.py BG02G.bmp 0
python ..\..\exe\img\img_cut1.py BG02H.bmp 0
python ..\..\exe\img\img_cut1.py BG03.bmp 34
python ..\..\exe\img\img_cut1.py BG03C.bmp 34
python ..\..\exe\img\img_cut1.py BG04.bmp 34
python ..\..\exe\img\img_cut1.py BG04B.bmp 34
python ..\..\exe\img\img_cut1.py BG04C.bmp 34
python ..\..\exe\img\img_cut1.py BG05.bmp 0
python ..\..\exe\img\img_cut1.py BG05B.bmp 0
python ..\..\exe\img\img_cut1.py BG06.bmp 34
python ..\..\exe\img\img_cut1.py BG06B.bmp 34
python ..\..\exe\img\img_cut1.py BG06C.bmp 34
python ..\..\exe\img\img_cut1.py BG07.bmp 0
python ..\..\exe\img\img_cut1.py BG07C.bmp 0
python ..\..\exe\img\img_cut1.py BG07E.bmp 0
python ..\..\exe\img\img_cut1.py BG08.bmp 0
python ..\..\exe\img\img_cut1.py BG09.bmp 34
python ..\..\exe\img\img_cut1.py BG09C.bmp 34
python ..\..\exe\img\img_cut1.py BG09D.bmp 34
python ..\..\exe\img\img_cut1.py BG09E.bmp 34
python ..\..\exe\img\img_cut1.py BG10.bmp 34
python ..\..\exe\img\img_cut1.py BG11.bmp 34
python ..\..\exe\img\img_cut1.py BG11B.bmp 34
python ..\..\exe\img\img_cut1.py BG11D.bmp 34
python ..\..\exe\img\img_cut1.py BG12.bmp 0
python ..\..\exe\img\img_cut1.py BG13.bmp 34
python ..\..\exe\img\img_cut1.py BG13B.bmp 34
python ..\..\exe\img\img_cut1.py BG13C.bmp 34
python ..\..\exe\img\img_cut1.py BG13D.bmp 34
python ..\..\exe\img\img_cut1.py BG14.bmp 34
python ..\..\exe\img\img_cut1.py BG14B.bmp 34
python ..\..\exe\img\img_cut1.py BG14C.bmp 34
python ..\..\exe\img\img_cut1.py BG15.bmp 0
python ..\..\exe\img\img_cut1.py BG15B.bmp 0
python ..\..\exe\img\img_cut1.py BG16.bmp 34
python ..\..\exe\img\img_cut1.py BG17.bmp 34
python ..\..\exe\img\img_cut1.py BG17B.bmp 34
python ..\..\exe\img\img_cut1.py BG18.bmp 0
python ..\..\exe\img\img_cut1.py BG19.bmp 34
python ..\..\exe\img\img_cut1.py BG20.bmp 34
python ..\..\exe\img\img_cut1.py BG20B.bmp 34
python ..\..\exe\img\img_cut1.py BG21.bmp 34
python ..\..\exe\img\img_cut1.py BG22.bmp 34
python ..\..\exe\img\img_cut1.py BG23.bmp 0
python ..\..\exe\img\img_cut1.py BG24.bmp 34
python ..\..\exe\img\img_cut1.py BG25.bmp 51
python ..\..\exe\img\img_cut1.py BG25B.bmp 51
python ..\..\exe\img\img_cut1.py BG27.bmp 34
python ..\..\exe\img\img_cut1.py BG28.bmp 34
python ..\..\exe\img\img_cut1.py BG29.bmp 0
python ..\..\exe\img\img_cut1.py BG30.bmp 34
python ..\..\exe\img\img_cut1.py BG31.bmp 34
python ..\..\exe\img\img_cut1.py BG31B.bmp 34
python ..\..\exe\img\img_cut1.py BG32.bmp 34
python ..\..\exe\img\img_cut1.py BG32B.bmp 34
python ..\..\exe\img\img_cut1.py BG33.bmp 34
python ..\..\exe\img\img_cut1.py BG34.bmp 34
python ..\..\exe\img\img_cut1.py BG34B.bmp 34
python ..\..\exe\img\img_cut1.py BG34C.bmp 34
python ..\..\exe\img\img_cut1.py BG35.bmp 68
python ..\..\exe\img\img_cut1.py BG35B.bmp 68
python ..\..\exe\img\img_cut1.py BG35B2.bmp 68
python ..\..\exe\img\img_cut1.py BG35D.bmp 68
python ..\..\exe\img\img_cut1.py BG36.bmp 34
python ..\..\exe\img\img_cut1.py BG36B.bmp 34
python ..\..\exe\img\img_cut1.py BG36C.bmp 34
python ..\..\exe\img\img_cut1.py BG37.bmp 34
python ..\..\exe\img\img_cut1.py BG37B.bmp 34
python ..\..\exe\img\img_cut1.py BG37C.bmp 34
python ..\..\exe\img\img_cut1.py BG38.bmp 34
python ..\..\exe\img\img_cut1.py BG39.bmp 34
python ..\..\exe\img\img_cut1.py BG40.bmp 34
python ..\..\exe\img\img_cut1.py BG41.bmp 34
python ..\..\exe\img\img_cut1.py BG42.bmp 34
python ..\..\exe\img\img_cut1.py BG43.bmp 34
python ..\..\exe\img\img_cut1.py BG44.bmp 34
python ..\..\exe\img\img_cut1.py BG45.bmp 34
python ..\..\exe\img\img_cut1.py BGT_AKI.bmp 23
python ..\..\exe\img\img_cut1.py BGT_FUYU.bmp 23
python ..\..\exe\img\img_cut1.py BGT_HARU.bmp 23
python ..\..\exe\img\img_cut1.py BGT_NATU.bmp 23
python ..\..\exe\img\img_cut1.py BGT_SIGYOU.bmp 23

python ..\..\exe\img\img_cut1.py GRP01.bmp 34
python ..\..\exe\img\img_cut1.py GRP01B.bmp 34
python ..\..\exe\img\img_cut1.py GRP02.bmp 34
python ..\..\exe\img\img_cut1.py GRP03.bmp 34
python ..\..\exe\img\img_cut1.py GRP03B.bmp 34
python ..\..\exe\img\img_cut1.py GRP04.bmp 34
python ..\..\exe\img\img_cut1.py GRP04B.bmp 34
python ..\..\exe\img\img_cut1.py GRP04C.bmp 34
python ..\..\exe\img\img_cut1.py GRP05.bmp 34
python ..\..\exe\img\img_cut1.py GRP06.bmp 0
python ..\..\exe\img\img_cut1.py GRP07.bmp 34
python ..\..\exe\img\img_cut1.py GRP08.bmp 34
python ..\..\exe\img\img_cut1.py GRP09.bmp 34
python ..\..\exe\img\img_cut1.py GRP10.bmp 34
python ..\..\exe\img\img_cut1.py GRP11.bmp 34
python ..\..\exe\img\img_cut1.py GRP11B.bmp 34
python ..\..\exe\img\img_cut1.py GRP11C.bmp 34
python ..\..\exe\img\img_cut1.py GRP12.bmp 34
python ..\..\exe\img\img_cut1.py GRP13.bmp 34
python ..\..\exe\img\img_cut1.py GRP14.bmp 0
python ..\..\exe\img\img_cut1.py GRP15.bmp 51
python ..\..\exe\img\img_cut1.py GRP16.bmp 34
python ..\..\exe\img\img_cut1.py GRP16B.bmp 34
python ..\..\exe\img\img_cut1.py GRP16C.bmp 34
python ..\..\exe\img\img_cut1.py GRP17.bmp 34
python ..\..\exe\img\img_cut1.py GRP18.bmp 0
python ..\..\exe\img\img_cut1.py GRP19.bmp 34
python ..\..\exe\img\img_cut1.py GRP19B.bmp 34
python ..\..\exe\img\img_cut1.py GRP19B2.bmp 34
python ..\..\exe\img\img_cut1.py GRP19C.bmp 34
python ..\..\exe\img\img_cut1.py GRP19D.bmp 34
python ..\..\exe\img\img_cut1.py GRP19E.bmp 34
python ..\..\exe\img\img_cut1.py GRP19F.bmp 34
python ..\..\exe\img\img_cut1.py GRP19G.bmp 34
python ..\..\exe\img\img_cut1.py GRP19H.bmp 34
python ..\..\exe\img\img_cut1.py GRP20.bmp 34
python ..\..\exe\img\img_cut1.py GRP20B.bmp 34
python ..\..\exe\img\img_cut1.py GRP21.bmp 0
python ..\..\exe\img\img_cut1.py GRP22.bmp 0
python ..\..\exe\img\img_cut1.py GRP22B.bmp 0
python ..\..\exe\img\img_cut1.py GRP23.bmp 34
python ..\..\exe\img\img_cut1.py GRP25.bmp 34
python ..\..\exe\img\img_cut1.py GRP26.bmp 34
python ..\..\exe\img\img_cut1.py GRP27.bmp 34
python ..\..\exe\img\img_cut1.py GRP27B.bmp 34
python ..\..\exe\img\img_cut1.py GRP28.bmp 51
python ..\..\exe\img\img_cut1.py GRP29.bmp 34
python ..\..\exe\img\img_cut1.py GRP30.bmp 34
python ..\..\exe\img\img_cut1.py GRP30B.bmp 0
python ..\..\exe\img\img_cut1.py GRP30C.bmp 34
python ..\..\exe\img\img_cut1.py GRP30D.bmp 0
python ..\..\exe\img\img_cut1.py GRP30E.bmp 0
python ..\..\exe\img\img_cut1.py GRP31.bmp 34
python ..\..\exe\img\img_cut1.py GRP32.bmp 0
python ..\..\exe\img\img_cut1.py GRP33.bmp 34
python ..\..\exe\img\img_cut1.py GRP33B.bmp 34
python ..\..\exe\img\img_cut1.py GRP34.bmp 34
python ..\..\exe\img\img_cut1.py GRP34B.bmp 34
python ..\..\exe\img\img_cut1.py GRP35.bmp 0
python ..\..\exe\img\img_cut1.py GRP35B.bmp 0
python ..\..\exe\img\img_cut1.py GRP36.bmp 0
python ..\..\exe\img\img_cut1.py GRP37.bmp 0
python ..\..\exe\img\img_cut1.py GRP38.bmp 34
python ..\..\exe\img\img_cut1.py GRP39.bmp 34
python ..\..\exe\img\img_cut1.py GRP39B.bmp 34
python ..\..\exe\img\img_cut1.py GRP40.bmp 0
python ..\..\exe\img\img_cut1.py GRP41.bmp 0
python ..\..\exe\img\img_cut1.py GRP42B.bmp 0
python ..\..\exe\img\img_cut1.py GRP42C.bmp 68
python ..\..\exe\img\img_cut1.py GRP42D.bmp 68
python ..\..\exe\img\img_cut1.py GRP42E.bmp 68
python ..\..\exe\img\img_cut1.py GRP43.bmp 34
python ..\..\exe\img\img_cut1.py GRP45.bmp 0
python ..\..\exe\img\img_cut1.py GRP47.bmp 34
python ..\..\exe\img\img_cut1.py GRP48.bmp 34
python ..\..\exe\img\img_cut1.py GRP51.bmp 34
python ..\..\exe\img\img_cut1.py GRP53.bmp 34
python ..\..\exe\img\img_cut1.py GRP54.bmp 34
python ..\..\exe\img\img_cut1.py GRP55.bmp 0
python ..\..\exe\img\img_cut1.py GRP58.bmp 0
python ..\..\exe\img\img_cut1.py GRP59.bmp 34
python ..\..\exe\img\img_cut1.py GRP60.bmp 0
python ..\..\exe\img\img_cut1.py GRP60B.bmp 0

python ..\..\exe\img\img_cut1.py HGRP01.bmp 34
python ..\..\exe\img\img_cut1.py HGRP01B.bmp 34
python ..\..\exe\img\img_cut1.py HGRP02.bmp 34
python ..\..\exe\img\img_cut1.py HGRP03.bmp 34
python ..\..\exe\img\img_cut1.py HGRP04.bmp 34
python ..\..\exe\img\img_cut1.py HGRP05.bmp 34
python ..\..\exe\img\img_cut1.py HGRP06.bmp 17
python ..\..\exe\img\img_cut1.py HGRP06B.bmp 34
python ..\..\exe\img\img_cut1.py HGRP07.bmp 34
python ..\..\exe\img\img_cut1.py HGRP08.bmp 0
python ..\..\exe\img\img_cut1.py HGRP09.bmp 34
python ..\..\exe\img\img_cut1.py HGRP10.bmp 0
python ..\..\exe\img\img_cut1.py HGRP11.bmp 0
python ..\..\exe\img\img_cut1.py HGRP12.bmp 34
python ..\..\exe\img\img_cut1.py HGRP12B.bmp 34
python ..\..\exe\img\img_cut1.py HGRP13.bmp 34
python ..\..\exe\img\img_cut1.py HGRP14.bmp 0
python ..\..\exe\img\img_cut1.py HGRP15.bmp 0
python ..\..\exe\img\img_cut1.py HGRP15B.bmp 0
python ..\..\exe\img\img_cut1.py HGRP16.bmp 68
python ..\..\exe\img\img_cut1.py HGRP17.bmp 0
python ..\..\exe\img\img_cut1.py HGRP18.bmp 0
python ..\..\exe\img\img_cut1.py HGRP19.bmp 17
python ..\..\exe\img\img_cut1.py HGRP20.bmp 34
python ..\..\exe\img\img_cut1.py HGRP21.bmp 34
python ..\..\exe\img\img_cut1.py HGRP22.bmp 34
python ..\..\exe\img\img_cut1.py HGRP23.bmp 34
python ..\..\exe\img\img_cut1.py HGRP24.bmp 34
python ..\..\exe\img\img_cut1.py HGRP25.bmp 34
python ..\..\exe\img\img_cut1.py HGRP26.bmp 34
python ..\..\exe\img\img_cut1.py HGRP27.bmp 0
python ..\..\exe\img\img_cut1.py HGRP28.bmp 34
python ..\..\exe\img\img_cut1.py HGRP29.bmp 34
python ..\..\exe\img\img_cut1.py HGRP30B.bmp 34
python ..\..\exe\img\img_cut1.py HGRP30C.bmp 34
python ..\..\exe\img\img_cut1.py HGRP31.bmp 17
python ..\..\exe\img\img_cut1.py HGRP31B.bmp 17
python ..\..\exe\img\img_cut1.py HGRP31C.bmp 17
python ..\..\exe\img\img_cut1.py HGRP31E.bmp 17
python ..\..\exe\img\img_cut1.py HGRP32.bmp 34
python ..\..\exe\img\img_cut1.py HGRP32B.bmp 34
python ..\..\exe\img\img_cut1.py HGRP33.bmp 34
python ..\..\exe\img\img_cut1.py HGRP34.bmp 0
python ..\..\exe\img\img_cut1.py HGRP35.bmp 17
python ..\..\exe\img\img_cut1.py HGRP36.bmp 34
python ..\..\exe\img\img_cut1.py HGRP37.bmp 0
python ..\..\exe\img\img_cut1.py HGRP38.bmp 34
python ..\..\exe\img\img_cut1.py HGRP39.bmp 34

python ..\..\exe\img\img_cut2.py ACT00.bmp
python ..\..\exe\img\img_cut2.py ACT00_m.bmp
python ..\..\exe\img\img_cut2.py ACT01.bmp
python ..\..\exe\img\img_cut2.py ACT01_m.bmp
python ..\..\exe\img\img_cut2.py ACT02.bmp
python ..\..\exe\img\img_cut2.py ACT02_m.bmp
python ..\..\exe\img\img_cut2.py ACT03.bmp
python ..\..\exe\img\img_cut2.py ACT03_m.bmp
python ..\..\exe\img\img_cut2.py ACT03B.bmp
python ..\..\exe\img\img_cut2.py ACT03B_m.bmp
python ..\..\exe\img\img_cut2.py ACT04.bmp
python ..\..\exe\img\img_cut2.py ACT04_m.bmp
python ..\..\exe\img\img_cut2.py ACT05.bmp
python ..\..\exe\img\img_cut2.py ACT05_m.bmp
python ..\..\exe\img\img_cut2.py AI01.bmp
python ..\..\exe\img\img_cut2.py AI01_m.bmp
python ..\..\exe\img\img_cut2.py AI01B.bmp
python ..\..\exe\img\img_cut2.py AI01B_m.bmp
python ..\..\exe\img\img_cut2.py AI01C.bmp
python ..\..\exe\img\img_cut2.py AI01C_m.bmp
python ..\..\exe\img\img_cut2.py AI01D.bmp
python ..\..\exe\img\img_cut2.py AI01D_m.bmp
python ..\..\exe\img\img_cut2.py AI02.bmp
python ..\..\exe\img\img_cut2.py AI02_m.bmp
python ..\..\exe\img\img_cut2.py AI02B.bmp
python ..\..\exe\img\img_cut2.py AI02B_m.bmp
python ..\..\exe\img\img_cut2.py AI02C.bmp
python ..\..\exe\img\img_cut2.py AI02C_m.bmp
python ..\..\exe\img\img_cut2.py AI02D.bmp
python ..\..\exe\img\img_cut2.py AI02D_m.bmp
python ..\..\exe\img\img_cut2.py AI03.bmp
python ..\..\exe\img\img_cut2.py AI03_m.bmp
python ..\..\exe\img\img_cut2.py AI03B.bmp
python ..\..\exe\img\img_cut2.py AI03B_m.bmp
python ..\..\exe\img\img_cut2.py AI03BZ.bmp
python ..\..\exe\img\img_cut2.py AI03BZ_m.bmp
python ..\..\exe\img\img_cut2.py AI03C.bmp
python ..\..\exe\img\img_cut2.py AI03C_m.bmp
python ..\..\exe\img\img_cut2.py AI03CZ.bmp
python ..\..\exe\img\img_cut2.py AI03CZ_m.bmp
python ..\..\exe\img\img_cut2.py AI03D.bmp
python ..\..\exe\img\img_cut2.py AI03D_m.bmp
python ..\..\exe\img\img_cut2.py AI04.bmp
python ..\..\exe\img\img_cut2.py AI04_m.bmp
python ..\..\exe\img\img_cut2.py AI04B.bmp
python ..\..\exe\img\img_cut2.py AI04B_m.bmp
python ..\..\exe\img\img_cut2.py AI04C.bmp
python ..\..\exe\img\img_cut2.py AI04C_m.bmp
python ..\..\exe\img\img_cut2.py AI04D.bmp
python ..\..\exe\img\img_cut2.py AI04D_m.bmp
python ..\..\exe\img\img_cut2.py AI05.bmp
python ..\..\exe\img\img_cut2.py AI05_m.bmp
python ..\..\exe\img\img_cut2.py AI05B.bmp
python ..\..\exe\img\img_cut2.py AI05B_m.bmp
python ..\..\exe\img\img_cut2.py AI05C.bmp
python ..\..\exe\img\img_cut2.py AI05C_m.bmp
python ..\..\exe\img\img_cut2.py AI05D.bmp
python ..\..\exe\img\img_cut2.py AI05D_m.bmp
python ..\..\exe\img\img_cut2.py AI06.bmp
python ..\..\exe\img\img_cut2.py AI06_m.bmp
python ..\..\exe\img\img_cut2.py AI06B.bmp
python ..\..\exe\img\img_cut2.py AI06B_m.bmp
python ..\..\exe\img\img_cut2.py AI06C.bmp
python ..\..\exe\img\img_cut2.py AI06C_m.bmp
python ..\..\exe\img\img_cut2.py AI06D.bmp
python ..\..\exe\img\img_cut2.py AI06D_m.bmp
python ..\..\exe\img\img_cut2.py ASU01.bmp
python ..\..\exe\img\img_cut2.py ASU01_m.bmp
python ..\..\exe\img\img_cut2.py ASU01B.bmp
python ..\..\exe\img\img_cut2.py ASU01B_m.bmp
python ..\..\exe\img\img_cut2.py ASU01C.bmp
python ..\..\exe\img\img_cut2.py ASU01C_m.bmp
python ..\..\exe\img\img_cut2.py ASU02.bmp
python ..\..\exe\img\img_cut2.py ASU02_m.bmp
python ..\..\exe\img\img_cut2.py ASU02B.bmp
python ..\..\exe\img\img_cut2.py ASU02B_m.bmp
python ..\..\exe\img\img_cut2.py ASU02C.bmp
python ..\..\exe\img\img_cut2.py ASU02C_m.bmp
python ..\..\exe\img\img_cut2.py ASU03.bmp
python ..\..\exe\img\img_cut2.py ASU03_m.bmp
python ..\..\exe\img\img_cut2.py ASU03B.bmp
python ..\..\exe\img\img_cut2.py ASU03B_m.bmp
python ..\..\exe\img\img_cut2.py ASU03C.bmp
python ..\..\exe\img\img_cut2.py ASU03C_m.bmp
python ..\..\exe\img\img_cut2.py ASU04.bmp
python ..\..\exe\img\img_cut2.py ASU04_m.bmp
python ..\..\exe\img\img_cut2.py ASU04B.bmp
python ..\..\exe\img\img_cut2.py ASU04B_m.bmp
python ..\..\exe\img\img_cut2.py ASU04C.bmp
python ..\..\exe\img\img_cut2.py ASU04C_m.bmp
python ..\..\exe\img\img_cut2.py ASU05.bmp
python ..\..\exe\img\img_cut2.py ASU05_m.bmp
python ..\..\exe\img\img_cut2.py ASU05B.bmp
python ..\..\exe\img\img_cut2.py ASU05B_m.bmp
python ..\..\exe\img\img_cut2.py ASU05C.bmp
python ..\..\exe\img\img_cut2.py ASU05C_m.bmp
python ..\..\exe\img\img_cut2.py ASU06.bmp
python ..\..\exe\img\img_cut2.py ASU06_m.bmp
python ..\..\exe\img\img_cut2.py ASU06B.bmp
python ..\..\exe\img\img_cut2.py ASU06B_m.bmp
python ..\..\exe\img\img_cut2.py ASU06C.bmp
python ..\..\exe\img\img_cut2.py ASU06C_m.bmp
python ..\..\exe\img\img_cut2.py ASU09C.bmp
python ..\..\exe\img\img_cut2.py ASU09C_m.bmp
python ..\..\exe\img\img_cut2.py ASU10B.bmp
python ..\..\exe\img\img_cut2.py ASU10B_m.bmp
python ..\..\exe\img\img_cut2.py ASU10C.bmp
python ..\..\exe\img\img_cut2.py ASU10C_m.bmp
python ..\..\exe\img\img_cut2.py DOU01.bmp
python ..\..\exe\img\img_cut2.py DOU01_m.bmp
python ..\..\exe\img\img_cut2.py DOU02.bmp
python ..\..\exe\img\img_cut2.py DOU02_m.bmp
python ..\..\exe\img\img_cut2.py DOU03.bmp
python ..\..\exe\img\img_cut2.py DOU03_m.bmp
python ..\..\exe\img\img_cut2.py DOU04.bmp
python ..\..\exe\img\img_cut2.py DOU04_m.bmp
python ..\..\exe\img\img_cut2.py ERIK01.bmp
python ..\..\exe\img\img_cut2.py ERIK01_m.bmp
python ..\..\exe\img\img_cut2.py ERIK02.bmp
python ..\..\exe\img\img_cut2.py ERIK02_m.bmp
python ..\..\exe\img\img_cut2.py ERIK04.bmp
python ..\..\exe\img\img_cut2.py ERIK04_m.bmp
python ..\..\exe\img\img_cut2.py ERIK05.bmp
python ..\..\exe\img\img_cut2.py ERIK05_m.bmp
python ..\..\exe\img\img_cut2.py ERIK06.bmp
python ..\..\exe\img\img_cut2.py ERIK06_m.bmp
python ..\..\exe\img\img_cut2.py FUMI01.bmp
python ..\..\exe\img\img_cut2.py FUMI01_m.bmp
python ..\..\exe\img\img_cut2.py FUMI01C.bmp
python ..\..\exe\img\img_cut2.py FUMI01C_m.bmp
python ..\..\exe\img\img_cut2.py FUMI02.bmp
python ..\..\exe\img\img_cut2.py FUMI02_m.bmp
python ..\..\exe\img\img_cut2.py FUMI02B.bmp
python ..\..\exe\img\img_cut2.py FUMI02B_m.bmp
python ..\..\exe\img\img_cut2.py FUMI02C.bmp
python ..\..\exe\img\img_cut2.py FUMI02C_m.bmp
python ..\..\exe\img\img_cut2.py FUMI03.bmp
python ..\..\exe\img\img_cut2.py FUMI03_m.bmp
python ..\..\exe\img\img_cut2.py FUMI03C.bmp
python ..\..\exe\img\img_cut2.py FUMI03C_m.bmp
python ..\..\exe\img\img_cut2.py FUMI04.bmp
python ..\..\exe\img\img_cut2.py FUMI04_m.bmp
python ..\..\exe\img\img_cut2.py FUMI04C.bmp
python ..\..\exe\img\img_cut2.py FUMI04C_m.bmp
python ..\..\exe\img\img_cut2.py FUMI05.bmp
python ..\..\exe\img\img_cut2.py FUMI05_m.bmp
python ..\..\exe\img\img_cut2.py FUMI05C.bmp
python ..\..\exe\img\img_cut2.py FUMI05C_m.bmp
python ..\..\exe\img\img_cut2.py FUMI07.bmp
python ..\..\exe\img\img_cut2.py FUMI07_m.bmp
python ..\..\exe\img\img_cut2.py FUMI07C.bmp
python ..\..\exe\img\img_cut2.py FUMI07C_m.bmp
python ..\..\exe\img\img_cut2.py FUMI08.bmp
python ..\..\exe\img\img_cut2.py FUMI08_m.bmp
python ..\..\exe\img\img_cut2.py FUMI08C.bmp
python ..\..\exe\img\img_cut2.py FUMI08C_m.bmp
python ..\..\exe\img\img_cut2.py KAED01.bmp
python ..\..\exe\img\img_cut2.py KAED01_m.bmp
python ..\..\exe\img\img_cut2.py KAED01B.bmp
python ..\..\exe\img\img_cut2.py KAED01B_m.bmp
python ..\..\exe\img\img_cut2.py KAED01BZ.bmp
python ..\..\exe\img\img_cut2.py KAED01BZ_m.bmp
python ..\..\exe\img\img_cut2.py KAED01C.bmp
python ..\..\exe\img\img_cut2.py KAED01C_m.bmp
python ..\..\exe\img\img_cut2.py KAED01CZ.bmp
python ..\..\exe\img\img_cut2.py KAED01CZ_m.bmp
python ..\..\exe\img\img_cut2.py KAED01D.bmp
python ..\..\exe\img\img_cut2.py KAED01D_m.bmp
python ..\..\exe\img\img_cut2.py KAED01E.bmp
python ..\..\exe\img\img_cut2.py KAED01E_m.bmp
python ..\..\exe\img\img_cut2.py KAED01EZ.bmp
python ..\..\exe\img\img_cut2.py KAED01EZ_m.bmp
python ..\..\exe\img\img_cut2.py KAED01Z.bmp
python ..\..\exe\img\img_cut2.py KAED01Z_m.bmp
python ..\..\exe\img\img_cut2.py KAED02.bmp
python ..\..\exe\img\img_cut2.py KAED02_m.bmp
python ..\..\exe\img\img_cut2.py KAED02B.bmp
python ..\..\exe\img\img_cut2.py KAED02B_m.bmp
python ..\..\exe\img\img_cut2.py KAED02C.bmp
python ..\..\exe\img\img_cut2.py KAED02C_m.bmp
python ..\..\exe\img\img_cut2.py KAED02D.bmp
python ..\..\exe\img\img_cut2.py KAED02D_m.bmp
python ..\..\exe\img\img_cut2.py KAED02E.bmp
python ..\..\exe\img\img_cut2.py KAED02E_m.bmp
python ..\..\exe\img\img_cut2.py KAED03.bmp
python ..\..\exe\img\img_cut2.py KAED03_m.bmp
python ..\..\exe\img\img_cut2.py KAED03B.bmp
python ..\..\exe\img\img_cut2.py KAED03B_m.bmp
python ..\..\exe\img\img_cut2.py KAED03C.bmp
python ..\..\exe\img\img_cut2.py KAED03C_m.bmp
python ..\..\exe\img\img_cut2.py KAED03D.bmp
python ..\..\exe\img\img_cut2.py KAED03D_m.bmp
python ..\..\exe\img\img_cut2.py KAED03E.bmp
python ..\..\exe\img\img_cut2.py KAED03E_m.bmp
python ..\..\exe\img\img_cut2.py KAED04.bmp
python ..\..\exe\img\img_cut2.py KAED04_m.bmp
python ..\..\exe\img\img_cut2.py KAED04B.bmp
python ..\..\exe\img\img_cut2.py KAED04B_m.bmp
python ..\..\exe\img\img_cut2.py KAED04C.bmp
python ..\..\exe\img\img_cut2.py KAED04C_m.bmp
python ..\..\exe\img\img_cut2.py KAED04E.bmp
python ..\..\exe\img\img_cut2.py KAED04E_m.bmp
python ..\..\exe\img\img_cut2.py SAIG01.bmp
python ..\..\exe\img\img_cut2.py SAIG01_m.bmp
python ..\..\exe\img\img_cut2.py SAIG02.bmp
python ..\..\exe\img\img_cut2.py SAIG02_m.bmp
python ..\..\exe\img\img_cut2.py SAIG03.bmp
python ..\..\exe\img\img_cut2.py SAIG03_m.bmp
python ..\..\exe\img\img_cut2.py SAIG04.bmp
python ..\..\exe\img\img_cut2.py SAIG04_m.bmp
python ..\..\exe\img\img_cut2.py SOUS01.bmp
python ..\..\exe\img\img_cut2.py SOUS01_m.bmp
python ..\..\exe\img\img_cut2.py SOUS02.bmp
python ..\..\exe\img\img_cut2.py SOUS02_m.bmp
python ..\..\exe\img\img_cut2.py SOUS03.bmp
python ..\..\exe\img\img_cut2.py SOUS03_m.bmp
python ..\..\exe\img\img_cut2.py SOUS04.bmp
python ..\..\exe\img\img_cut2.py SOUS04_m.bmp
python ..\..\exe\img\img_cut2.py TUJI01.bmp
python ..\..\exe\img\img_cut2.py TUJI01_m.bmp
python ..\..\exe\img\img_cut2.py TUJI02.bmp
python ..\..\exe\img\img_cut2.py TUJI02_m.bmp
python ..\..\exe\img\img_cut2.py TUJI03.bmp
python ..\..\exe\img\img_cut2.py TUJI03_m.bmp
python ..\..\exe\img\img_cut2.py TUJI04.bmp
python ..\..\exe\img\img_cut2.py TUJI04_m.bmp
python ..\..\exe\img\img_cut2.py YUKA01.bmp
python ..\..\exe\img\img_cut2.py YUKA01_m.bmp
python ..\..\exe\img\img_cut2.py YUKA01B.bmp
python ..\..\exe\img\img_cut2.py YUKA01B_m.bmp
python ..\..\exe\img\img_cut2.py YUKA01C.bmp
python ..\..\exe\img\img_cut2.py YUKA01C_m.bmp
python ..\..\exe\img\img_cut2.py YUKA01D.bmp
python ..\..\exe\img\img_cut2.py YUKA01D_m.bmp
python ..\..\exe\img\img_cut2.py YUKA01E.bmp
python ..\..\exe\img\img_cut2.py YUKA01E_m.bmp
python ..\..\exe\img\img_cut2.py YUKA01Z.bmp
python ..\..\exe\img\img_cut2.py YUKA01Z_m.bmp
python ..\..\exe\img\img_cut2.py YUKA02.bmp
python ..\..\exe\img\img_cut2.py YUKA02_m.bmp
python ..\..\exe\img\img_cut2.py YUKA02B.bmp
python ..\..\exe\img\img_cut2.py YUKA02B_m.bmp
python ..\..\exe\img\img_cut2.py YUKA02C.bmp
python ..\..\exe\img\img_cut2.py YUKA02C_m.bmp
python ..\..\exe\img\img_cut2.py YUKA02D.bmp
python ..\..\exe\img\img_cut2.py YUKA02D_m.bmp
python ..\..\exe\img\img_cut2.py YUKA03.bmp
python ..\..\exe\img\img_cut2.py YUKA03_m.bmp
python ..\..\exe\img\img_cut2.py YUKA03B.bmp
python ..\..\exe\img\img_cut2.py YUKA03B_m.bmp
python ..\..\exe\img\img_cut2.py YUKA03BZ.bmp
python ..\..\exe\img\img_cut2.py YUKA03BZ_m.bmp
python ..\..\exe\img\img_cut2.py YUKA03C.bmp
python ..\..\exe\img\img_cut2.py YUKA03C_m.bmp
python ..\..\exe\img\img_cut2.py YUKA03CZ.bmp
python ..\..\exe\img\img_cut2.py YUKA03CZ_m.bmp
python ..\..\exe\img\img_cut2.py YUKA03D.bmp
python ..\..\exe\img\img_cut2.py YUKA03D_m.bmp
python ..\..\exe\img\img_cut2.py YUKA03E.bmp
python ..\..\exe\img\img_cut2.py YUKA03E_m.bmp
python ..\..\exe\img\img_cut2.py YUKA03Z.bmp
python ..\..\exe\img\img_cut2.py YUKA03Z_m.bmp
python ..\..\exe\img\img_cut2.py YUKA04.bmp
python ..\..\exe\img\img_cut2.py YUKA04_m.bmp
python ..\..\exe\img\img_cut2.py YUKA04B.bmp
python ..\..\exe\img\img_cut2.py YUKA04B_m.bmp
python ..\..\exe\img\img_cut2.py YUKA04C.bmp
python ..\..\exe\img\img_cut2.py YUKA04C_m.bmp
python ..\..\exe\img\img_cut2.py YUKA04D.bmp
python ..\..\exe\img\img_cut2.py YUKA04D_m.bmp
python ..\..\exe\img\img_cut2.py YUKA04E.bmp
python ..\..\exe\img\img_cut2.py YUKA04E_m.bmp
python ..\..\exe\img\img_cut2.py YUKA05.bmp
python ..\..\exe\img\img_cut2.py YUKA05_m.bmp
python ..\..\exe\img\img_cut2.py YUKA05B.bmp
python ..\..\exe\img\img_cut2.py YUKA05B_m.bmp
python ..\..\exe\img\img_cut2.py YUKA05C.bmp
python ..\..\exe\img\img_cut2.py YUKA05C_m.bmp
python ..\..\exe\img\img_cut2.py YUKA06.bmp
python ..\..\exe\img\img_cut2.py YUKA06_m.bmp
python ..\..\exe\img\img_cut2.py YUKA06B.bmp
python ..\..\exe\img\img_cut2.py YUKA06B_m.bmp
python ..\..\exe\img\img_cut2.py YUKA06C.bmp
python ..\..\exe\img\img_cut2.py YUKA06C_m.bmp
python ..\..\exe\img\img_cut2.py YUKA06D.bmp
python ..\..\exe\img\img_cut2.py YUKA06D_m.bmp
python ..\..\exe\img\img_cut2.py YUKA06E.bmp
python ..\..\exe\img\img_cut2.py YUKA06E_m.bmp
python ..\..\exe\img\img_cut2.py YUKA07.bmp
python ..\..\exe\img\img_cut2.py YUKA07_m.bmp
python ..\..\exe\img\img_cut2.py YUKA07B.bmp
python ..\..\exe\img\img_cut2.py YUKA07B_m.bmp
python ..\..\exe\img\img_cut2.py YUKA07C.bmp
python ..\..\exe\img\img_cut2.py YUKA07C_m.bmp
python ..\..\exe\img\img_cut2.py YUKA07D.bmp
python ..\..\exe\img\img_cut2.py YUKA07D_m.bmp


rem ---------------------------------
rem エンドクレジットを480x320サイズに変更

python ..\..\exe\img\img_end.py ED_WH.bmp END_00.bmp 150 196
python ..\..\exe\img\img_end.py ED_WH.bmp END_01.bmp 150 204
python ..\..\exe\img\img_end.py ED_WH.bmp END_02.bmp 174 220
python ..\..\exe\img\img_end.py ED_WH.bmp END_03.bmp 172 162
python ..\..\exe\img\img_end.py ED_WH.bmp END_04.bmp 291 162
python ..\..\exe\img\img_end.py ED_WH.bmp END_05.bmp 289 152
python ..\..\exe\img\img_end.py ED_WH.bmp END_06.bmp 289 152
python ..\..\exe\img\img_end.py ED_WH.bmp END_07.bmp 278 152
python ..\..\exe\img\img_end.py ED_WH.bmp END_08.bmp 182 210
python ..\..\exe\img\img_end.py ED_WH.bmp END_09.bmp 365 241
python ..\..\exe\img\img_end.py ED_WH.bmp END_10.bmp 544 532


rem ---------------------------------
rem しおりアイコンを１ファイルに統合

python ..\..\exe\img\img_ico.py


del *.bmp
cd ..
