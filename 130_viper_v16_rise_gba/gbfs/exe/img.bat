@echo off

cd tmp

rem ---------------------------------
rem 重複、不要ANMを削除

del B4B.ANM
del B4C.ANM
del INFO.ANM
del RIFRM.ANM
del SELREP.ANM

rem ---------------------------------
rem ANMをBMPに変換

for %%i in (*.ANM) do ..\..\exe\img\anm2bmp %%i

del *.ANM

rem ---------------------------------
rem 差分ファイルの合成

python ..\..\exe\img\img_dif1.py A1.dat A1_26.bmp A1_25.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_27.bmp A1_26.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_28.bmp A1_27.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_29.bmp A1_28.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_30.bmp A1_29.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_31.bmp A1_30.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_32.bmp A1_31.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_33.bmp A1_32.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_34.bmp A1_33.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_35.bmp A1_34.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_36.bmp A1_35.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_37.bmp A1_36.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_38.bmp A1_37.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_39.bmp A1_38.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_40.bmp A1_39.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_41.bmp A1_40.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_42.bmp A1_41.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_43.bmp A1_42.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_44.bmp A1_43.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_45.bmp A1_44.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_46.bmp A1_45.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_47.bmp A1_46.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_48.bmp A1_47.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_49.bmp A1_48.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_50.bmp A1_49.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_51.bmp A1_50.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_52.bmp A1_51.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_53.bmp A1_52.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_54.bmp A1_53.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_55.bmp A1_54.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_56.bmp A1_55.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_57.bmp A1_56.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_58.bmp A1_57.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_59.bmp A1_58.bmp
python ..\..\exe\img\img_dif1.py A1.dat A1_60.bmp A1_59.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_26.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_27.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_28.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_29.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_30.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_31.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_32.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_33.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_34.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_35.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_36.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_37.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_38.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_39.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_40.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_41.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_42.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_43.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_44.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_45.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_46.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_47.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_48.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_49.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_50.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_51.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_52.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_53.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_54.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_55.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_56.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_57.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_58.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_59.bmp
python ..\..\exe\img\img_cut1.py A1.dat A1_60.bmp

python ..\..\exe\img\img_dif1.py B4.dat B4_06.bmp B4_07.bmp
python ..\..\exe\img\img_dif1.py B4.dat B4_05.bmp B4_06.bmp
python ..\..\exe\img\img_cut1.py B4.dat B4_06.bmp
python ..\..\exe\img\img_cut1.py B4.dat B4_05.bmp

rem ---------------------------------
rem 戦闘関連

python ..\..\exe\img\img_dif2.py BATA.dat BATA_27.bmp BATA_01.bmp
python ..\..\exe\img\img_dif2.py BATA.dat BATA_28.bmp BATA_01.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_01.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_02.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_03.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_04.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_05.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_06.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_07.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_08.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_09.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_10.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_11.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_12.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_13.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_14.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_15.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_16.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_17.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_18.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_19.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_20.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_21.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_22.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_23.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_24.bmp BATA_26.bmp
python ..\..\exe\img\img_dif1.py BATA.dat BATA_25.bmp BATA_26.bmp
ren BATA_27.bmp BATA_32.bmp
ren BATA_28.bmp BATA_33.bmp
python ..\..\exe\img\dat_add.py 0 0 448 320 BATA.dat
python ..\..\exe\img\dat_add.py 0 0 448 320 BATA.dat
del BATA_26.bmp

python ..\..\exe\img\img_dif2.py BATB.dat BATB_27.bmp BATB_01.bmp
python ..\..\exe\img\img_dif2.py BATB.dat BATB_28.bmp BATB_01.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_01.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_02.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_03.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_04.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_05.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_06.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_07.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_08.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_09.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_10.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_11.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_12.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_13.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_14.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_15.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_16.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_17.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_18.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_19.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_20.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_21.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_22.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_23.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_24.bmp BATB_26.bmp
python ..\..\exe\img\img_dif1.py BATB.dat BATB_25.bmp BATB_26.bmp
ren BATB_27.bmp BATB_32.bmp
ren BATB_28.bmp BATB_33.bmp
python ..\..\exe\img\dat_add.py 0 0 448 320 BATB.dat
python ..\..\exe\img\dat_add.py 0 0 448 320 BATB.dat
del BATB_26.bmp

python ..\..\exe\img\img_dif2.py BOSS.dat BOSS_25.bmp BOSS_01.bmp
python ..\..\exe\img\img_dif2.py BOSS.dat BOSS_26.bmp BOSS_01.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_01.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_02.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_03.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_04.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_05.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_06.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_07.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_08.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_09.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_10.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_11.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_12.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_13.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_14.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_15.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_16.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_17.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_18.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_19.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_20.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_21.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_22.bmp BOSS_24.bmp
python ..\..\exe\img\img_dif1.py BOSS.dat BOSS_23.bmp BOSS_24.bmp
python ..\..\exe\img\dat_edit.py 1 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 2 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 3 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 7 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 8 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 9 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 10 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 12 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 14 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 15 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 16 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 17 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 21 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 22 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_edit.py 23 0 0 448 320 BOSS.dat
ren BOSS_25.bmp BOSS_32.bmp
ren BOSS_26.bmp BOSS_33.bmp
python ..\..\exe\img\dat_add.py 0 0 448 320 BOSS.dat
python ..\..\exe\img\dat_add.py 0 0 448 320 BOSS.dat
del BOSS_24.bmp

rem ---------------------------------

python ..\..\exe\img\img_dif1.py C3.dat C3_01.bmp C3_07.bmp
python ..\..\exe\img\img_dif1.py C3.dat C3_02.bmp C3_07.bmp
python ..\..\exe\img\img_dif1.py C3.dat C3_03.bmp C3_07.bmp
python ..\..\exe\img\img_dif1.py C3.dat C3_04.bmp C3_07.bmp
python ..\..\exe\img\img_dif1.py C3.dat C3_05.bmp C3_07.bmp
python ..\..\exe\img\img_dif1.py C3.dat C3_06.bmp C3_07.bmp
del C3_07.bmp

python ..\..\exe\img\img_dif1.py C4.dat C4_01.bmp C4_13.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_02.bmp C4_13.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_03.bmp C4_13.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_04.bmp C4_13.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_05.bmp C4_13.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_06.bmp C4_13.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_07.bmp C4_13.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_08.bmp C4_13.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_09.bmp C4_13.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_10.bmp C4_09.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_11.bmp C4_10.bmp
python ..\..\exe\img\img_dif1.py C4.dat C4_12.bmp C4_11.bmp
python ..\..\exe\img\dat_edit.py 1 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 2 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 3 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 4 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 5 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 6 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 7 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 8 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 9 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 10 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 11 0 0 448 320 C4.dat
python ..\..\exe\img\dat_edit.py 12 0 0 448 320 C4.dat
del C4_13.bmp

python ..\..\exe\img\img_dif1.py ED22.dat ED22_01.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_02.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_03.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_04.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_05.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_06.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_07.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_08.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_09.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_10.bmp ED22_12.bmp
python ..\..\exe\img\img_dif1.py ED22.dat ED22_11.bmp ED22_12.bmp
python ..\..\exe\img\dat_edit.py 1 0 0 448 320 ED22.dat
del ED22_12.bmp

python ..\..\exe\img\img_dif1.py ED23.dat ED23_01.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_02.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_03.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_04.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_05.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_06.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_07.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_08.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_09.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_10.bmp ED23_12.bmp
python ..\..\exe\img\img_dif1.py ED23.dat ED23_11.bmp ED23_12.bmp
del ED23_12.bmp

python ..\..\exe\img\img_dif1.py ED32.dat ED32_01.bmp ED32_10.bmp
python ..\..\exe\img\img_dif1.py ED32.dat ED32_02.bmp ED32_10.bmp
python ..\..\exe\img\img_dif1.py ED32.dat ED32_03.bmp ED32_10.bmp
python ..\..\exe\img\img_dif1.py ED32.dat ED32_04.bmp ED32_10.bmp
python ..\..\exe\img\img_dif1.py ED32.dat ED32_05.bmp ED32_10.bmp
python ..\..\exe\img\img_dif1.py ED32.dat ED32_06.bmp ED32_10.bmp
python ..\..\exe\img\img_dif1.py ED32.dat ED32_07.bmp ED32_10.bmp
python ..\..\exe\img\img_dif1.py ED32.dat ED32_08.bmp ED32_10.bmp
python ..\..\exe\img\img_dif1.py ED32.dat ED32_09.bmp ED32_10.bmp
del ED32_10.bmp

python ..\..\exe\img\img_dif1.py ED42.dat ED42_08.bmp ED42_07.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_09.bmp ED42_08.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_10.bmp ED42_09.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_11.bmp ED42_10.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_12.bmp ED42_11.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_13.bmp ED42_12.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_14.bmp ED42_13.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_15.bmp ED42_14.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_16.bmp ED42_15.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_17.bmp ED42_16.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_18.bmp ED42_17.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_19.bmp ED42_18.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_20.bmp ED42_19.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_21.bmp ED42_20.bmp
python ..\..\exe\img\img_dif1.py ED42.dat ED42_22.bmp ED42_21.bmp
python ..\..\exe\img\dat_edit.py 8 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 9 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 10 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 11 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 12 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 13 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 14 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 15 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 16 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 17 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 18 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 19 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 20 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 21 0 0 448 320 ED42.dat
python ..\..\exe\img\dat_edit.py 22 0 0 448 320 ED42.dat

copy ED43_26.bmp tmp01.bmp > nul
copy ED43_26.bmp tmp02.bmp > nul
copy ED43_26.bmp tmp03.bmp > nul
copy ED43_26.bmp tmp04.bmp > nul
copy ED43_26.bmp tmp05.bmp > nul
copy ED43_26.bmp tmp06.bmp > nul
copy ED43_26.bmp tmp07.bmp > nul
copy ED43_26.bmp tmp08.bmp > nul
copy ED43_26.bmp tmp09.bmp > nul
copy ED43_26.bmp tmp10.bmp > nul
python ..\..\exe\img\img_dif2.py ED43.dat tmp01.bmp ED43_15.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp01.bmp ED43_19.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp02.bmp ED43_15.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp02.bmp ED43_20.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp03.bmp ED43_15.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp03.bmp ED43_21.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp04.bmp ED43_15.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp04.bmp ED43_22.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp05.bmp ED43_15.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp05.bmp ED43_14.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp05.bmp ED43_23.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp06.bmp ED43_15.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp06.bmp ED43_14.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp06.bmp ED43_24.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp07.bmp ED43_15.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp07.bmp ED43_14.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp07.bmp ED43_25.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp08.bmp ED43_16.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp08.bmp ED43_25.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp09.bmp ED43_17.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp09.bmp ED43_25.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp10.bmp ED43_18.bmp
python ..\..\exe\img\img_dif2.py ED43.dat tmp10.bmp ED43_25.bmp
del ED43_15.bmp
del ED43_16.bmp
del ED43_17.bmp
del ED43_18.bmp
del ED43_19.bmp
del ED43_20.bmp
del ED43_21.bmp
del ED43_22.bmp
del ED43_23.bmp
del ED43_24.bmp
del ED43_25.bmp
del ED43_26.bmp
ren tmp01.bmp ED43_19.bmp
ren tmp02.bmp ED43_20.bmp
ren tmp03.bmp ED43_21.bmp
ren tmp04.bmp ED43_22.bmp
ren tmp05.bmp ED43_23.bmp
ren tmp06.bmp ED43_24.bmp
ren tmp07.bmp ED43_25.bmp
ren tmp08.bmp ED43_26.bmp
ren tmp09.bmp ED43_27.bmp
ren tmp10.bmp ED43_28.bmp

python ..\..\exe\img\dat_edit.py 19 0 0 448 320 ED43.dat
python ..\..\exe\img\dat_edit.py 20 0 0 448 320 ED43.dat
python ..\..\exe\img\dat_edit.py 21 0 0 448 320 ED43.dat
python ..\..\exe\img\dat_edit.py 22 0 0 448 320 ED43.dat
python ..\..\exe\img\dat_edit.py 23 0 0 448 320 ED43.dat
python ..\..\exe\img\dat_edit.py 24 0 0 448 320 ED43.dat
python ..\..\exe\img\dat_edit.py 25 0 0 448 320 ED43.dat
python ..\..\exe\img\dat_edit.py 26 0 0 448 320 ED43.dat
python ..\..\exe\img\dat_add.py 0 0 448 320 ED43.dat
python ..\..\exe\img\dat_add.py 0 0 448 320 ED43.dat

python ..\..\exe\img\img_dif1.py ED43.dat ED43_10.bmp ED43_19.bmp
python ..\..\exe\img\img_dif1.py ED43.dat ED43_11.bmp ED43_19.bmp
python ..\..\exe\img\img_dif1.py ED43.dat ED43_12.bmp ED43_19.bmp
python ..\..\exe\img\img_dif1.py ED43.dat ED43_13.bmp ED43_19.bmp
python ..\..\exe\img\img_dif1.py ED43.dat ED43_14.bmp ED43_19.bmp
python ..\..\exe\img\img_cut1.py ED43.dat ED43_10.bmp
python ..\..\exe\img\img_cut1.py ED43.dat ED43_11.bmp
python ..\..\exe\img\img_cut1.py ED43.dat ED43_12.bmp
python ..\..\exe\img\img_cut1.py ED43.dat ED43_13.bmp
python ..\..\exe\img\img_cut1.py ED43.dat ED43_14.bmp

python ..\..\exe\img\img_dif1.py ED51.dat ED51_01.bmp ED51_14.bmp
python ..\..\exe\img\img_dif1.py ED51.dat ED51_02.bmp ED51_01.bmp
python ..\..\exe\img\dat_edit.py 1 0 0 448 664 ED51.dat
python ..\..\exe\img\dat_edit.py 2 0 0 448 664 ED51.dat

python ..\..\exe\img\img_dif1.py ED52.dat ED52_49.bmp ED52_11.bmp
python ..\..\exe\img\img_dif1.py ED52.dat ED52_50.bmp ED52_49.bmp
python ..\..\exe\img\img_dif1.py ED52.dat ED52_51.bmp ED52_50.bmp
python ..\..\exe\img\img_dif1.py ED52.dat ED52_52.bmp ED52_51.bmp
python ..\..\exe\img\img_dif1.py ED52.dat ED52_53.bmp ED52_52.bmp
python ..\..\exe\img\img_dif1.py ED52.dat ED52_54.bmp ED52_53.bmp
python ..\..\exe\img\img_dif1.py ED52.dat ED52_55.bmp ED52_54.bmp
python ..\..\exe\img\dat_edit.py 49 0 0 448 320 ED52.dat
python ..\..\exe\img\dat_edit.py 50 0 0 448 320 ED52.dat
python ..\..\exe\img\dat_edit.py 51 0 0 448 320 ED52.dat
python ..\..\exe\img\dat_edit.py 52 0 0 448 320 ED52.dat
python ..\..\exe\img\dat_edit.py 53 0 0 448 320 ED52.dat
python ..\..\exe\img\dat_edit.py 54 0 0 448 320 ED52.dat
python ..\..\exe\img\dat_edit.py 55 0 0 448 320 ED52.dat

python ..\..\exe\img\img_dif1.py ED53.dat ED53_01.bmp ED53_16.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_02.bmp ED53_16.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_03.bmp ED53_16.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_04.bmp ED53_16.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_05.bmp ED53_16.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_07.bmp ED53_01.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_06.bmp ED53_07.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_12.bmp ED53_06.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_13.bmp ED53_12.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_14.bmp ED53_13.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_15.bmp ED53_14.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_09.bmp ED53_15.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_08.bmp ED53_09.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_11.bmp ED53_05.bmp
python ..\..\exe\img\img_dif1.py ED53.dat ED53_10.bmp ED53_11.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_06.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_07.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_08.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_09.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_10.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_11.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_12.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_13.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_14.bmp
python ..\..\exe\img\img_cut1.py ED53.dat ED53_15.bmp
python ..\..\exe\img\dat_edit.py 1 0 0 448 320 ED53.dat
python ..\..\exe\img\dat_edit.py 2 0 0 448 320 ED53.dat
python ..\..\exe\img\dat_edit.py 3 0 0 448 320 ED53.dat
python ..\..\exe\img\dat_edit.py 4 0 0 448 320 ED53.dat
python ..\..\exe\img\dat_edit.py 5 0 0 448 320 ED53.dat
del ED53_16.bmp

python ..\..\exe\img\img_dif1.py ED54.dat ED54_05.bmp ED54_04.bmp
python ..\..\exe\img\img_dif1.py ED54.dat ED54_06.bmp ED54_05.bmp
python ..\..\exe\img\img_dif1.py ED54.dat ED54_07.bmp ED54_06.bmp
python ..\..\exe\img\img_dif1.py ED54.dat ED54_08.bmp ED54_07.bmp
python ..\..\exe\img\img_dif1.py ED54.dat ED54_09.bmp ED54_08.bmp
python ..\..\exe\img\img_dif1.py ED54.dat ED54_10.bmp ED54_09.bmp
python ..\..\exe\img\img_dif1.py ED54.dat ED54_11.bmp ED54_10.bmp
python ..\..\exe\img\img_dif1.py ED54.dat ED54_12.bmp ED54_11.bmp
python ..\..\exe\img\img_dif1.py ED54.dat ED54_13.bmp ED54_12.bmp
python ..\..\exe\img\img_dif1.py ED54.dat ED54_14.bmp ED54_13.bmp
python ..\..\exe\img\dat_edit.py 5 0 0 448 320 ED54.dat
python ..\..\exe\img\dat_edit.py 6 0 0 448 320 ED54.dat
python ..\..\exe\img\dat_edit.py 7 0 0 448 320 ED54.dat
python ..\..\exe\img\dat_edit.py 8 0 0 448 320 ED54.dat
python ..\..\exe\img\dat_edit.py 9 0 0 448 320 ED54.dat
python ..\..\exe\img\dat_edit.py 10 0 0 448 320 ED54.dat
python ..\..\exe\img\dat_edit.py 11 0 0 448 320 ED54.dat
python ..\..\exe\img\dat_edit.py 12 0 0 448 320 ED54.dat
python ..\..\exe\img\dat_edit.py 13 0 0 448 320 ED54.dat
python ..\..\exe\img\dat_edit.py 14 0 0 448 320 ED54.dat

python ..\..\exe\img\img_dif1.py ED61.dat ED61_04.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_05.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_06.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_07.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_08.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_09.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_10.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_11.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_12.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_13.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_14.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_15.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_16.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_17.bmp ED61_04.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_18.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_19.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_20.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_21.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_22.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_23.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_24.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_25.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_26.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_27.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_28.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_29.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_30.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_31.bmp ED61_33.bmp
python ..\..\exe\img\img_dif1.py ED61.dat ED61_32.bmp ED61_33.bmp
python ..\..\exe\img\dat_edit.py 5 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 6 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 7 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 8 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 9 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 10 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 11 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 12 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 13 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 14 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 15 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 16 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 17 0 0 448 320 ED61.dat
python ..\..\exe\img\dat_edit.py 32 0 0 448 320 ED61.dat
del ED61_04.bmp
del ED61_33.bmp

python ..\..\exe\img\img_dif1.py ED62.dat ED62_17.bmp ED62_16.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_18.bmp ED62_17.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_19.bmp ED62_18.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_20.bmp ED62_19.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_21.bmp ED62_20.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_22.bmp ED62_21.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_23.bmp ED62_22.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_03.bmp ED62_23.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_04.bmp ED62_03.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_05.bmp ED62_04.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_06.bmp ED62_05.bmp
python ..\..\exe\img\img_dif1.py ED62.dat ED62_07.bmp ED62_06.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_03.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_04.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_05.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_06.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_07.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_17.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_18.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_19.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_20.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_21.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_22.bmp
python ..\..\exe\img\img_cut1.py ED62.dat ED62_23.bmp

copy ED64_89.bmp tmp01.bmp > nul
copy ED64_89.bmp tmp02.bmp > nul
copy ED64_89.bmp tmp03.bmp > nul
copy ED64_89.bmp tmp04.bmp > nul
copy ED64_89.bmp tmp05.bmp > nul
copy ED64_89.bmp tmp06.bmp > nul
copy ED64_89.bmp tmp07.bmp > nul
copy ED64_89.bmp tmp08.bmp > nul
copy ED64_89.bmp tmp09.bmp > nul
copy ED64_89.bmp tmp10.bmp > nul
copy ED64_89.bmp tmp11.bmp > nul
copy ED64_89.bmp tmp12.bmp > nul
copy ED64_89.bmp tmp13.bmp > nul
copy ED64_89.bmp tmp14.bmp > nul
copy ED64_89.bmp tmp15.bmp > nul
copy ED64_89.bmp tmp16.bmp > nul
copy ED64_89.bmp tmp17.bmp > nul
copy ED64_89.bmp tmp18.bmp > nul
copy ED64_89.bmp tmp19.bmp > nul
copy ED64_89.bmp tmp20.bmp > nul
copy ED64_89.bmp tmp21.bmp > nul
copy ED64_89.bmp tmp22.bmp > nul
copy ED64_89.bmp tmp23.bmp > nul
copy ED64_89.bmp tmp24.bmp > nul
copy ED64_89.bmp tmp25.bmp > nul
copy ED64_89.bmp tmp26.bmp > nul
copy ED64_89.bmp tmp27.bmp > nul
copy ED64_89.bmp tmp28.bmp > nul
copy ED64_89.bmp tmp29.bmp > nul
copy ED64_89.bmp tmp30.bmp > nul
copy ED64_89.bmp tmp31.bmp > nul
copy ED64_89.bmp tmp32.bmp > nul
copy ED64_89.bmp tmp33.bmp > nul
copy ED64_89.bmp tmp34.bmp > nul
copy ED64_89.bmp tmp35.bmp > nul
copy ED64_89.bmp tmp36.bmp > nul
copy ED64_89.bmp tmp37.bmp > nul
copy ED64_89.bmp tmp38.bmp > nul
copy ED64_89.bmp tmp39.bmp > nul
copy ED64_89.bmp tmp40.bmp > nul
copy ED64_89.bmp tmp41.bmp > nul
copy ED64_89.bmp tmp42.bmp > nul
copy ED64_89.bmp tmp43.bmp > nul
copy ED64_89.bmp tmp44.bmp > nul
copy ED64_89.bmp tmp45.bmp > nul
copy ED64_89.bmp tmp46.bmp > nul
copy ED64_89.bmp tmp47.bmp > nul
copy ED64_89.bmp tmp48.bmp > nul
copy ED64_89.bmp tmp49.bmp > nul
copy ED64_89.bmp tmp50.bmp > nul
copy ED64_89.bmp tmp51.bmp > nul
copy ED64_89.bmp tmp52.bmp > nul
copy ED64_89.bmp tmp53.bmp > nul
copy ED64_89.bmp tmp54.bmp > nul
copy ED64_89.bmp tmp55.bmp > nul
copy ED64_89.bmp tmp56.bmp > nul
copy ED64_89.bmp tmp57.bmp > nul
copy ED64_89.bmp tmp58.bmp > nul
copy ED64_89.bmp tmp59.bmp > nul
copy ED64_89.bmp tmp60.bmp > nul
copy ED64_89.bmp tmp61.bmp > nul
copy ED64_89.bmp tmp62.bmp > nul
copy ED64_89.bmp tmp63.bmp > nul
copy ED64_89.bmp tmp64.bmp > nul
copy ED64_89.bmp tmp65.bmp > nul
copy ED64_89.bmp tmp66.bmp > nul
copy ED64_89.bmp tmp67.bmp > nul
copy ED64_89.bmp tmp68.bmp > nul
python ..\..\exe\img\img_dif2.py ED64.dat tmp01.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp01.bmp ED64_01.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp01.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp01.bmp ED64_35.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp02.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp02.bmp ED64_02.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp02.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp02.bmp ED64_36.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp03.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp03.bmp ED64_03.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp03.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp03.bmp ED64_37.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp04.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp04.bmp ED64_04.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp04.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp04.bmp ED64_38.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp05.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp05.bmp ED64_05.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp05.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp05.bmp ED64_39.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp06.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp06.bmp ED64_06.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp06.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp06.bmp ED64_40.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp07.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp07.bmp ED64_07.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp07.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp07.bmp ED64_41.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp08.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp08.bmp ED64_08.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp08.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp08.bmp ED64_42.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp09.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp09.bmp ED64_09.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp09.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp09.bmp ED64_42.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp10.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp10.bmp ED64_10.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp10.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp10.bmp ED64_43.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp11.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp11.bmp ED64_11.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp11.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp11.bmp ED64_44.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp12.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp12.bmp ED64_11.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp12.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp12.bmp ED64_45.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp13.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp13.bmp ED64_11.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp13.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp13.bmp ED64_46.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp14.bmp ED64_83.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp14.bmp ED64_11.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp14.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp14.bmp ED64_47.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp15.bmp ED64_12.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp15.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp15.bmp ED64_48.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp16.bmp ED64_13.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp16.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp16.bmp ED64_48.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp17.bmp ED64_14.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp17.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp17.bmp ED64_48.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp18.bmp ED64_15.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp18.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp18.bmp ED64_48.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp19.bmp ED64_16.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp19.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp19.bmp ED64_48.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp20.bmp ED64_17.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp20.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp20.bmp ED64_48.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp21.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp21.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp21.bmp ED64_48.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp22.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp22.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp22.bmp ED64_38.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp23.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp23.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp23.bmp ED64_39.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp24.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp24.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp24.bmp ED64_40.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp25.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp25.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp25.bmp ED64_41.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp26.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp26.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp26.bmp ED64_42.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp27.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp27.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp27.bmp ED64_42.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp28.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp28.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp28.bmp ED64_43.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp29.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp29.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp29.bmp ED64_44.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp30.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp30.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp30.bmp ED64_45.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp31.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp31.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp31.bmp ED64_46.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp32.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp32.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp32.bmp ED64_47.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp33.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp33.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp33.bmp ED64_49.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp34.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp34.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp34.bmp ED64_50.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp35.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp35.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp35.bmp ED64_51.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp36.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp36.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp36.bmp ED64_52.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp37.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp37.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp37.bmp ED64_53.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp38.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp38.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp38.bmp ED64_54.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp39.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp39.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp39.bmp ED64_55.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp40.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp40.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp40.bmp ED64_56.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp41.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp41.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp41.bmp ED64_57.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp42.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp42.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp42.bmp ED64_58.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp43.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp43.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp43.bmp ED64_59.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp44.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp44.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp44.bmp ED64_60.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp45.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp45.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp45.bmp ED64_61.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp46.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp46.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp46.bmp ED64_62.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp47.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp47.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp47.bmp ED64_63.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp48.bmp ED64_18.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp48.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp48.bmp ED64_64.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp49.bmp ED64_19.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp49.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp49.bmp ED64_64.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp50.bmp ED64_20.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp50.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp50.bmp ED64_64.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp51.bmp ED64_21.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp51.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp51.bmp ED64_64.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp52.bmp ED64_22.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp52.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp52.bmp ED64_64.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp53.bmp ED64_23.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp53.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp53.bmp ED64_64.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp54.bmp ED64_24.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp54.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp54.bmp ED64_65.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp55.bmp ED64_25.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp55.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp55.bmp ED64_66.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp56.bmp ED64_26.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp56.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp56.bmp ED64_67.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp57.bmp ED64_27.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp57.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp57.bmp ED64_68.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp58.bmp ED64_28.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp58.bmp ED64_84.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp58.bmp ED64_68.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp59.bmp ED64_29.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp59.bmp ED64_69.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp60.bmp ED64_30.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp60.bmp ED64_70.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp61.bmp ED64_31.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp61.bmp ED64_85.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp61.bmp ED64_71.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp61.bmp ED64_81.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp62.bmp ED64_31.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp62.bmp ED64_85.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp62.bmp ED64_71.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp62.bmp ED64_82.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp63.bmp ED64_33.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp63.bmp ED64_85.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp63.bmp ED64_73.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp64.bmp ED64_34.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp64.bmp ED64_85.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp64.bmp ED64_74.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp65.bmp ED64_33.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp65.bmp ED64_85.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp65.bmp ED64_75.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp66.bmp ED64_32.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp66.bmp ED64_85.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp66.bmp ED64_76.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp67.bmp ED64_32.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp67.bmp ED64_85.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp67.bmp ED64_77.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp68.bmp ED64_32.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp68.bmp ED64_85.bmp
python ..\..\exe\img\img_dif2.py ED64.dat tmp68.bmp ED64_78.bmp
python ..\..\exe\img\img_dif1.py ED64.dat ED64_79.bmp tmp01.bmp
python ..\..\exe\img\img_dif1.py ED64.dat ED64_80.bmp ED64_79.bmp
python ..\..\exe\img\img_dif1.py ED64.dat ED64_81.bmp tmp61.bmp
python ..\..\exe\img\img_dif1.py ED64.dat ED64_82.bmp ED64_81.bmp
python ..\..\exe\img\img_cut1.py ED64.dat ED64_79.bmp
python ..\..\exe\img\img_cut1.py ED64.dat ED64_80.bmp
python ..\..\exe\img\img_cut1.py ED64.dat ED64_81.bmp
python ..\..\exe\img\img_cut1.py ED64.dat ED64_82.bmp
del ED64_01.bmp
del ED64_02.bmp
del ED64_03.bmp
del ED64_04.bmp
del ED64_05.bmp
del ED64_06.bmp
del ED64_07.bmp
del ED64_08.bmp
del ED64_09.bmp
del ED64_10.bmp
del ED64_11.bmp
del ED64_12.bmp
del ED64_13.bmp
del ED64_14.bmp
del ED64_15.bmp
del ED64_16.bmp
del ED64_17.bmp
del ED64_18.bmp
del ED64_19.bmp
del ED64_20.bmp
del ED64_21.bmp
del ED64_22.bmp
del ED64_23.bmp
del ED64_24.bmp
del ED64_25.bmp
del ED64_26.bmp
del ED64_27.bmp
del ED64_28.bmp
del ED64_29.bmp
del ED64_30.bmp
del ED64_31.bmp
del ED64_32.bmp
del ED64_33.bmp
del ED64_34.bmp
del ED64_35.bmp
del ED64_36.bmp
del ED64_37.bmp
del ED64_38.bmp
del ED64_39.bmp
del ED64_40.bmp
del ED64_41.bmp
del ED64_42.bmp
del ED64_43.bmp
del ED64_44.bmp
del ED64_45.bmp
del ED64_46.bmp
del ED64_47.bmp
del ED64_48.bmp
del ED64_49.bmp
del ED64_50.bmp
del ED64_51.bmp
del ED64_52.bmp
del ED64_53.bmp
del ED64_54.bmp
del ED64_55.bmp
del ED64_56.bmp
del ED64_57.bmp
del ED64_58.bmp
del ED64_59.bmp
del ED64_60.bmp
del ED64_61.bmp
del ED64_62.bmp
del ED64_63.bmp
del ED64_64.bmp
del ED64_65.bmp
del ED64_66.bmp
del ED64_67.bmp
del ED64_68.bmp
del ED64_69.bmp
del ED64_70.bmp
del ED64_71.bmp
del ED64_72.bmp
del ED64_73.bmp
del ED64_74.bmp
del ED64_75.bmp
del ED64_76.bmp
del ED64_77.bmp
del ED64_78.bmp
del ED64_83.bmp
del ED64_84.bmp
del ED64_85.bmp
del ED64_89.bmp
ren tmp01.bmp ED64_01.bmp
ren tmp02.bmp ED64_02.bmp
ren tmp03.bmp ED64_03.bmp
ren tmp04.bmp ED64_04.bmp
ren tmp05.bmp ED64_05.bmp
ren tmp06.bmp ED64_06.bmp
ren tmp07.bmp ED64_07.bmp
ren tmp08.bmp ED64_08.bmp
ren tmp09.bmp ED64_09.bmp
ren tmp10.bmp ED64_10.bmp
ren tmp11.bmp ED64_11.bmp
ren tmp12.bmp ED64_12.bmp
ren tmp13.bmp ED64_13.bmp
ren tmp14.bmp ED64_14.bmp
ren tmp15.bmp ED64_15.bmp
ren tmp16.bmp ED64_16.bmp
ren tmp17.bmp ED64_17.bmp
ren tmp18.bmp ED64_18.bmp
ren tmp19.bmp ED64_19.bmp
ren tmp20.bmp ED64_20.bmp
ren tmp21.bmp ED64_21.bmp
ren tmp22.bmp ED64_22.bmp
ren tmp23.bmp ED64_23.bmp
ren tmp24.bmp ED64_24.bmp
ren tmp25.bmp ED64_25.bmp
ren tmp26.bmp ED64_26.bmp
ren tmp27.bmp ED64_27.bmp
ren tmp28.bmp ED64_28.bmp
ren tmp29.bmp ED64_29.bmp
ren tmp30.bmp ED64_30.bmp
ren tmp31.bmp ED64_31.bmp
ren tmp32.bmp ED64_32.bmp
ren tmp33.bmp ED64_33.bmp
ren tmp34.bmp ED64_34.bmp
ren tmp35.bmp ED64_35.bmp
ren tmp36.bmp ED64_36.bmp
ren tmp37.bmp ED64_37.bmp
ren tmp38.bmp ED64_38.bmp
ren tmp39.bmp ED64_39.bmp
ren tmp40.bmp ED64_40.bmp
ren tmp41.bmp ED64_41.bmp
ren tmp42.bmp ED64_42.bmp
ren tmp43.bmp ED64_43.bmp
ren tmp44.bmp ED64_44.bmp
ren tmp45.bmp ED64_45.bmp
ren tmp46.bmp ED64_46.bmp
ren tmp47.bmp ED64_47.bmp
ren tmp48.bmp ED64_48.bmp
ren tmp49.bmp ED64_49.bmp
ren tmp50.bmp ED64_50.bmp
ren tmp51.bmp ED64_51.bmp
ren tmp52.bmp ED64_52.bmp
ren tmp53.bmp ED64_53.bmp
ren tmp54.bmp ED64_54.bmp
ren tmp55.bmp ED64_55.bmp
ren tmp56.bmp ED64_56.bmp
ren tmp57.bmp ED64_57.bmp
ren tmp58.bmp ED64_58.bmp
ren tmp59.bmp ED64_59.bmp
ren tmp60.bmp ED64_60.bmp
ren tmp61.bmp ED64_61.bmp
ren tmp62.bmp ED64_62.bmp
ren tmp63.bmp ED64_63.bmp
ren tmp64.bmp ED64_64.bmp
ren tmp65.bmp ED64_65.bmp
ren tmp66.bmp ED64_66.bmp
ren tmp67.bmp ED64_67.bmp
ren tmp68.bmp ED64_68.bmp
python ..\..\exe\img\dat_edit.py 1 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 2 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 3 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 4 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 5 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 6 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 7 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 8 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 9 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 10 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 11 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 12 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 13 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 14 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 15 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 16 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 17 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 18 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 19 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 20 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 21 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 22 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 23 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 24 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 25 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 26 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 27 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 28 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 29 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 30 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 31 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 32 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 33 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 34 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 35 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 36 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 37 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 38 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 39 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 40 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 41 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 42 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 43 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 44 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 45 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 46 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 47 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 48 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 49 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 50 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 51 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 52 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 53 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 54 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 55 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 56 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 57 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 58 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 59 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 60 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 61 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 62 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 63 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 64 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 65 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 66 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 67 0 0 448 320 ED64.dat
python ..\..\exe\img\dat_edit.py 68 0 0 448 320 ED64.dat

python ..\..\exe\img\img_dif1.py ED66.dat ED66_11.bmp ED66_01.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_12.bmp ED66_01.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_13.bmp ED66_12.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_14.bmp ED66_13.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_15.bmp ED66_14.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_16.bmp ED66_15.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_17.bmp ED66_16.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_18.bmp ED66_17.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_19.bmp ED66_18.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_20.bmp ED66_19.bmp
python ..\..\exe\img\img_dif1.py ED66.dat ED66_21.bmp ED66_20.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_11.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_12.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_13.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_14.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_15.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_16.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_17.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_18.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_19.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_20.bmp
python ..\..\exe\img\img_cut1.py ED66.dat ED66_21.bmp

python ..\..\exe\img\img_dif1.py ED67.dat ED67_01.bmp ED67_20.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_02.bmp ED67_01.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_05.bmp ED67_02.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_06.bmp ED67_05.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_07.bmp ED67_06.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_08.bmp ED67_07.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_21.bmp ED67_08.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_22.bmp ED67_21.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_23.bmp ED67_22.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_24.bmp ED67_23.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_04.bmp ED67_24.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_03.bmp ED67_04.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_13.bmp ED67_03.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_14.bmp ED67_13.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_15.bmp ED67_14.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_16.bmp ED67_15.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_17.bmp ED67_16.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_18.bmp ED67_17.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_19.bmp ED67_18.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_09.bmp ED67_19.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_10.bmp ED67_09.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_11.bmp ED67_10.bmp
python ..\..\exe\img\img_dif1.py ED67.dat ED67_12.bmp ED67_11.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_01.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_02.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_03.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_04.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_05.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_06.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_07.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_08.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_09.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_10.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_11.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_12.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_13.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_14.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_15.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_16.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_17.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_18.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_19.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_21.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_22.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_23.bmp
python ..\..\exe\img\img_cut1.py ED67.dat ED67_24.bmp

python ..\..\exe\img\img_dif1.py ED68.dat ED68_01.bmp ED68_47.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_02.bmp ED68_47.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_03.bmp ED68_47.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_04.bmp ED68_47.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_05.bmp ED68_47.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_06.bmp ED68_47.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_07.bmp ED68_47.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_08.bmp ED68_47.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_09.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_10.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_44.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_11.bmp ED68_44.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_12.bmp ED68_44.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_13.bmp ED68_44.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_14.bmp ED68_44.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_15.bmp ED68_44.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_16.bmp ED68_44.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_17.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_18.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_19.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_20.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_21.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_22.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_23.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_24.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_25.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_45.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_26.bmp ED68_45.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_27.bmp ED68_45.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_28.bmp ED68_45.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_29.bmp ED68_45.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_30.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_31.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_32.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_33.bmp ED68_46.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_34.bmp ED68_33.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_35.bmp ED68_34.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_36.bmp ED68_35.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_37.bmp ED68_36.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_38.bmp ED68_37.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_39.bmp ED68_38.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_40.bmp ED68_39.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_42.bmp ED68_41.bmp
python ..\..\exe\img\img_dif1.py ED68.dat ED68_43.bmp ED68_41.bmp
python ..\..\exe\img\dat_edit.py 11 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 12 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 13 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 14 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 15 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 16 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 17 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 18 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 26 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 27 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 28 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 29 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 34 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 35 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 36 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 37 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 38 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 39 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 40 0 0 448 320 ED68.dat
python ..\..\exe\img\dat_edit.py 42 0 0 448 640 ED68.dat
python ..\..\exe\img\dat_edit.py 43 0 0 448 640 ED68.dat
del ED68_41.bmp
del ED68_44.bmp
del ED68_45.bmp
del ED68_46.bmp
del ED68_47.bmp

python ..\..\exe\img\img_dif1.py ED71.dat ED71_29.bmp ED71_28.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_30.bmp ED71_29.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_31.bmp ED71_30.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_32.bmp ED71_31.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_33.bmp ED71_32.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_34.bmp ED71_33.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_35.bmp ED71_34.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_36.bmp ED71_35.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_37.bmp ED71_36.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_38.bmp ED71_37.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_39.bmp ED71_38.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_40.bmp ED71_39.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_41.bmp ED71_40.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_42.bmp ED71_41.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_43.bmp ED71_42.bmp
python ..\..\exe\img\img_dif1.py ED71.dat ED71_44.bmp ED71_43.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_29.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_30.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_31.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_32.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_33.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_34.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_35.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_36.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_37.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_38.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_39.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_40.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_41.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_42.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_43.bmp
python ..\..\exe\img\img_cut1.py ED71.dat ED71_44.bmp

python ..\..\exe\img\img_cut2.py 96 40 544 360 GAMEOVER_01.bmp
python ..\..\exe\img\dat_edit.py 1 0 0 448 320 GAMEOVER.dat

python ..\..\exe\img\dat_edit.py 1 0 0 448 320 OP1.dat

python ..\..\exe\img\img_dif1.py OP2.dat OP2_04.bmp OP2_14.bmp
python ..\..\exe\img\img_OP2.py OP2_05.bmp OP2_14.bmp
python ..\..\exe\img\img_OP2.py OP2_06.bmp OP2_14.bmp
python ..\..\exe\img\img_OP2.py OP2_07.bmp OP2_14.bmp
python ..\..\exe\img\img_OP2.py OP2_08.bmp OP2_14.bmp
python ..\..\exe\img\img_OP2.py OP2_09.bmp OP2_14.bmp
python ..\..\exe\img\img_OP2.py OP2_10.bmp OP2_14.bmp
python ..\..\exe\img\img_OP2.py OP2_11.bmp OP2_10.bmp
python ..\..\exe\img\img_OP2.py OP2_12.bmp OP2_11.bmp
python ..\..\exe\img\img_OP2.py OP2_13.bmp OP2_12.bmp
python ..\..\exe\img\img_cut2.py 280 0 728 320 OP2_05.bmp
python ..\..\exe\img\img_cut2.py 280 0 728 320 OP2_06.bmp
python ..\..\exe\img\img_cut2.py 280 0 728 320 OP2_07.bmp
python ..\..\exe\img\img_cut2.py 280 0 728 320 OP2_08.bmp
python ..\..\exe\img\img_cut2.py 280 0 728 320 OP2_09.bmp
python ..\..\exe\img\img_cut2.py 280 0 728 320 OP2_10.bmp
python ..\..\exe\img\img_cut2.py 280 0 728 320 OP2_11.bmp
python ..\..\exe\img\img_cut2.py 280 0 728 320 OP2_12.bmp
python ..\..\exe\img\img_cut2.py 280 0 728 320 OP2_13.bmp
python ..\..\exe\img\dat_edit.py 5 0 0 448 320 OP2.dat
python ..\..\exe\img\dat_edit.py 6 0 0 448 320 OP2.dat
python ..\..\exe\img\dat_edit.py 7 0 0 448 320 OP2.dat
python ..\..\exe\img\dat_edit.py 8 0 0 448 320 OP2.dat
python ..\..\exe\img\dat_edit.py 9 0 0 448 320 OP2.dat
python ..\..\exe\img\dat_edit.py 10 0 0 448 320 OP2.dat
python ..\..\exe\img\dat_edit.py 11 0 0 448 320 OP2.dat
python ..\..\exe\img\dat_edit.py 12 0 0 448 320 OP2.dat
python ..\..\exe\img\dat_edit.py 13 0 0 448 320 OP2.dat
del OP2_14.bmp

del OP2B.dat
del OP2B_01.bmp
del OP2B_02.bmp
del OP2B_03.bmp
del OP2B_04.bmp
del OP2B_05.bmp
del OP2B_06.bmp
del OP2B_07.bmp
del OP2B_08.bmp
del OP2B_09.bmp
del OP2B_10.bmp
del OP2B_11.bmp
del OP2B_12.bmp
del OP2B_13.bmp
del OP2B_14.bmp

python ..\..\exe\img\img_RI.py RI_SEL_06.bmp
python ..\..\exe\img\dat_edit.py 6 0 0 448 320 RI_SEL.dat
del RI_SEL_01.bmp
del RI_SEL_02.bmp
del RI_SEL_03.bmp
del RI_SEL_04.bmp
del RI_SEL_05.bmp

python ..\..\exe\img\img_cut2.py 96 40 544 360 SOGNA98_01.bmp
python ..\..\exe\img\dat_edit.py 1 0 0 448 320 SOGNA98.dat

rem ---------------------------------
rem リサイズ
for %%i in (*.bmp) do python ..\..\exe\img\img_size.py %%i

rem ---------------------------------
rem 自前画像に差し替え
del OP1_01.bmp
copy ..\..\exe\img\OP1_01\OP1_01.bmp . > nul

rem ---------------------------------
rem 画像をLz77圧縮（240x160）、無圧縮（240x160以外）にMode4変換

python ..\..\exe\img\img_bin.py A1_01.bmp
python ..\..\exe\img\img_bin.py A1_02.bmp
python ..\..\exe\img\img_bin.py A1_03.bmp
python ..\..\exe\img\img_bin.py A1_04.bmp
python ..\..\exe\img\img_bin.py A1_05.bmp
python ..\..\exe\img\img_bin.py A1_06.bmp
python ..\..\exe\img\img_bin.py A1_07.bmp
python ..\..\exe\img\img_bin.py A1_08.bmp
python ..\..\exe\img\img_bin.py A1_09.bmp
python ..\..\exe\img\img_bin.py A1_10.bmp
python ..\..\exe\img\img_bin.py A1_11.bmp
python ..\..\exe\img\img_bin.py A1_12.bmp
python ..\..\exe\img\img_bin.py A1_13.bmp
python ..\..\exe\img\img_bin.py A1_14.bmp
python ..\..\exe\img\img_bin.py A1_15.bmp
python ..\..\exe\img\img_bin.py A1_16.bmp
python ..\..\exe\img\img_bin.py A1_17.bmp
python ..\..\exe\img\img_bin.py A1_18.bmp
python ..\..\exe\img\img_bin.py A1_19.bmp
python ..\..\exe\img\img_bin.py A1_20.bmp
python ..\..\exe\img\img_bin.py A1_21.bmp
python ..\..\exe\img\img_bin.py A1_22.bmp
python ..\..\exe\img\img_bin.py A1_23.bmp
python ..\..\exe\img\img_bin.py A1_24.bmp
..\..\exe\img\grit A1_25.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py A1_26.bmp
python ..\..\exe\img\img_bin.py A1_27.bmp
python ..\..\exe\img\img_bin.py A1_28.bmp
python ..\..\exe\img\img_bin.py A1_29.bmp
python ..\..\exe\img\img_bin.py A1_30.bmp
python ..\..\exe\img\img_bin.py A1_31.bmp
python ..\..\exe\img\img_bin.py A1_32.bmp
python ..\..\exe\img\img_bin.py A1_33.bmp
python ..\..\exe\img\img_bin.py A1_34.bmp
python ..\..\exe\img\img_bin.py A1_35.bmp
python ..\..\exe\img\img_bin.py A1_36.bmp
python ..\..\exe\img\img_bin.py A1_37.bmp
python ..\..\exe\img\img_bin.py A1_38.bmp
python ..\..\exe\img\img_bin.py A1_39.bmp
python ..\..\exe\img\img_bin.py A1_40.bmp
python ..\..\exe\img\img_bin.py A1_41.bmp
python ..\..\exe\img\img_bin.py A1_42.bmp
python ..\..\exe\img\img_bin.py A1_43.bmp
python ..\..\exe\img\img_bin.py A1_44.bmp
python ..\..\exe\img\img_bin.py A1_45.bmp
python ..\..\exe\img\img_bin.py A1_46.bmp
python ..\..\exe\img\img_bin.py A1_47.bmp
python ..\..\exe\img\img_bin.py A1_48.bmp
python ..\..\exe\img\img_bin.py A1_49.bmp
python ..\..\exe\img\img_bin.py A1_50.bmp
python ..\..\exe\img\img_bin.py A1_51.bmp
python ..\..\exe\img\img_bin.py A1_52.bmp
python ..\..\exe\img\img_bin.py A1_53.bmp
python ..\..\exe\img\img_bin.py A1_54.bmp
python ..\..\exe\img\img_bin.py A1_55.bmp
python ..\..\exe\img\img_bin.py A1_56.bmp
python ..\..\exe\img\img_bin.py A1_57.bmp
python ..\..\exe\img\img_bin.py A1_58.bmp
python ..\..\exe\img\img_bin.py A1_59.bmp
python ..\..\exe\img\img_bin.py A1_60.bmp
..\..\exe\img\grit A2_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit A3_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit A3_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit A3_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit A3_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit A3_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit A3_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit A4_01.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py A5_01.bmp
python ..\..\exe\img\img_bin.py A5_02.bmp
python ..\..\exe\img\img_bin.py A5_03.bmp
python ..\..\exe\img\img_bin.py A5_04.bmp
..\..\exe\img\grit A5_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit B1_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit B2_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit B3_01.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py B4_01.bmp
python ..\..\exe\img\img_bin.py B4_02.bmp
python ..\..\exe\img\img_bin.py B4_03.bmp
python ..\..\exe\img\img_bin.py B4_04.bmp
python ..\..\exe\img\img_bin.py B4_05.bmp
python ..\..\exe\img\img_bin.py B4_06.bmp
..\..\exe\img\grit B4_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATA_33.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BATB_33.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit BOSS_33.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py C1_01.bmp
python ..\..\exe\img\img_bin.py C1_02.bmp
..\..\exe\img\grit C1_03.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py C2B_01.bmp
python ..\..\exe\img\img_bin.py C2B_02.bmp
python ..\..\exe\img\img_bin.py C2B_03.bmp
..\..\exe\img\grit C2B_04.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py C2_01.bmp
python ..\..\exe\img\img_bin.py C2_02.bmp
python ..\..\exe\img\img_bin.py C2_03.bmp
..\..\exe\img\grit C2_04.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py C3_01.bmp
python ..\..\exe\img\img_bin.py C3_02.bmp
python ..\..\exe\img\img_bin.py C3_03.bmp
python ..\..\exe\img\img_bin.py C3_04.bmp
python ..\..\exe\img\img_bin.py C3_05.bmp
python ..\..\exe\img\img_bin.py C3_06.bmp
..\..\exe\img\grit C4_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit C4_12.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED1_01.bmp
..\..\exe\img\grit ED21_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED21_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED21_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED21_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED21_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED21_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED21_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED21_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED21_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED21_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED22_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED23_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED31_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED31_02.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED32_01.bmp
python ..\..\exe\img\img_bin.py ED32_02.bmp
python ..\..\exe\img\img_bin.py ED32_03.bmp
python ..\..\exe\img\img_bin.py ED32_04.bmp
python ..\..\exe\img\img_bin.py ED32_05.bmp
python ..\..\exe\img\img_bin.py ED32_06.bmp
python ..\..\exe\img\img_bin.py ED32_07.bmp
python ..\..\exe\img\img_bin.py ED32_08.bmp
python ..\..\exe\img\img_bin.py ED32_09.bmp
python ..\..\exe\img\img_bin.py ED41_01.bmp
python ..\..\exe\img\img_bin.py ED41_02.bmp
python ..\..\exe\img\img_bin.py ED41_03.bmp
..\..\exe\img\grit ED41_04.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED42_01.bmp
python ..\..\exe\img\img_bin.py ED42_02.bmp
python ..\..\exe\img\img_bin.py ED42_03.bmp
python ..\..\exe\img\img_bin.py ED42_04.bmp
python ..\..\exe\img\img_bin.py ED42_05.bmp
python ..\..\exe\img\img_bin.py ED42_06.bmp
..\..\exe\img\grit ED42_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED42_22.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED43_01.bmp
python ..\..\exe\img\img_bin.py ED43_02.bmp
python ..\..\exe\img\img_bin.py ED43_03.bmp
python ..\..\exe\img\img_bin.py ED43_04.bmp
python ..\..\exe\img\img_bin.py ED43_05.bmp
python ..\..\exe\img\img_bin.py ED43_06.bmp
python ..\..\exe\img\img_bin.py ED43_07.bmp
python ..\..\exe\img\img_bin.py ED43_08.bmp
python ..\..\exe\img\img_bin.py ED43_09.bmp
python ..\..\exe\img\img_bin.py ED43_10.bmp
python ..\..\exe\img\img_bin.py ED43_11.bmp
python ..\..\exe\img\img_bin.py ED43_12.bmp
python ..\..\exe\img\img_bin.py ED43_13.bmp
python ..\..\exe\img\img_bin.py ED43_14.bmp
..\..\exe\img\grit ED43_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED43_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED43_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED43_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED43_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED43_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED43_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED43_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED43_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED43_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED44_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED45_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED45_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED45_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED45_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED45_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED45_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED45_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED45_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED45_09.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED46_01.bmp
python ..\..\exe\img\img_bin.py ED46_02.bmp
python ..\..\exe\img\img_bin.py ED46_03.bmp
python ..\..\exe\img\img_bin.py ED46_04.bmp
python ..\..\exe\img\img_bin.py ED46_05.bmp
python ..\..\exe\img\img_bin.py ED46_06.bmp
..\..\exe\img\grit ED46_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED46_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED46_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED46_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED46_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED46_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED46_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED46_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED46_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED46_16.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED46_17.bmp
python ..\..\exe\img\img_bin.py ED51_01.bmp
python ..\..\exe\img\img_bin.py ED51_02.bmp
python ..\..\exe\img\img_bin.py ED51_03.bmp
python ..\..\exe\img\img_bin.py ED51_04.bmp
..\..\exe\img\grit ED51_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_13.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED51_14.bmp
..\..\exe\img\grit ED51_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED51_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_33.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_34.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_35.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_36.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_37.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_38.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_39.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_40.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_41.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_42.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_43.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_44.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_45.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_46.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_47.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_48.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_49.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_50.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_51.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_52.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_53.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_54.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED52_55.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED53_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED53_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED53_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED53_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED53_05.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED53_06.bmp
python ..\..\exe\img\img_bin.py ED53_07.bmp
python ..\..\exe\img\img_bin.py ED53_08.bmp
python ..\..\exe\img\img_bin.py ED53_09.bmp
python ..\..\exe\img\img_bin.py ED53_10.bmp
python ..\..\exe\img\img_bin.py ED53_11.bmp
python ..\..\exe\img\img_bin.py ED53_12.bmp
python ..\..\exe\img\img_bin.py ED53_13.bmp
python ..\..\exe\img\img_bin.py ED53_14.bmp
python ..\..\exe\img\img_bin.py ED53_15.bmp
python ..\..\exe\img\img_bin.py ED54_01.bmp
python ..\..\exe\img\img_bin.py ED54_02.bmp
python ..\..\exe\img\img_bin.py ED54_03.bmp
..\..\exe\img\grit ED54_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED54_22.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED55_01.bmp
python ..\..\exe\img\img_bin.py ED55_02.bmp
python ..\..\exe\img\img_bin.py ED55_03.bmp
python ..\..\exe\img\img_bin.py ED55_04.bmp
python ..\..\exe\img\img_bin.py ED55_05.bmp
python ..\..\exe\img\img_bin.py ED55_06.bmp
python ..\..\exe\img\img_bin.py ED55_07.bmp
python ..\..\exe\img\img_bin.py ED55_08.bmp
python ..\..\exe\img\img_bin.py ED55_09.bmp
python ..\..\exe\img\img_bin.py ED55_10.bmp
python ..\..\exe\img\img_bin.py ED55_11.bmp
python ..\..\exe\img\img_bin.py ED55_12.bmp
python ..\..\exe\img\img_bin.py ED61_01.bmp
python ..\..\exe\img\img_bin.py ED61_02.bmp
python ..\..\exe\img\img_bin.py ED61_03.bmp
..\..\exe\img\grit ED61_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED61_32.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED62_01.bmp
python ..\..\exe\img\img_bin.py ED62_02.bmp
python ..\..\exe\img\img_bin.py ED62_03.bmp
python ..\..\exe\img\img_bin.py ED62_04.bmp
python ..\..\exe\img\img_bin.py ED62_05.bmp
python ..\..\exe\img\img_bin.py ED62_06.bmp
python ..\..\exe\img\img_bin.py ED62_07.bmp
..\..\exe\img\grit ED62_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED62_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED62_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED62_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED62_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED62_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED62_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED62_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED62_16.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED62_17.bmp
python ..\..\exe\img\img_bin.py ED62_18.bmp
python ..\..\exe\img\img_bin.py ED62_19.bmp
python ..\..\exe\img\img_bin.py ED62_20.bmp
python ..\..\exe\img\img_bin.py ED62_21.bmp
python ..\..\exe\img\img_bin.py ED62_22.bmp
python ..\..\exe\img\img_bin.py ED62_23.bmp
python ..\..\exe\img\img_bin.py ED62_24.bmp
python ..\..\exe\img\img_bin.py ED62_25.bmp
python ..\..\exe\img\img_bin.py ED62_26.bmp
..\..\exe\img\grit ED63_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_33.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_34.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_35.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_36.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED63_37.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED63_38.bmp
python ..\..\exe\img\img_bin.py ED63_39.bmp
python ..\..\exe\img\img_bin.py ED63_40.bmp
..\..\exe\img\grit ED64_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_33.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_34.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_35.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_36.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_37.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_38.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_39.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_40.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_41.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_42.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_43.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_44.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_45.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_46.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_47.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_48.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_49.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_50.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_51.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_52.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_53.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_54.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_55.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_56.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_57.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_58.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_59.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_60.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_61.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_62.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_63.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_64.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_65.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_66.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_67.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED64_68.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED64_79.bmp
python ..\..\exe\img\img_bin.py ED64_80.bmp
python ..\..\exe\img\img_bin.py ED64_81.bmp
python ..\..\exe\img\img_bin.py ED64_82.bmp
python ..\..\exe\img\img_bin.py ED64_86.bmp
python ..\..\exe\img\img_bin.py ED64_87.bmp
python ..\..\exe\img\img_bin.py ED64_88.bmp
python ..\..\exe\img\img_bin.py ED65_01.bmp
python ..\..\exe\img\img_bin.py ED65_02.bmp
python ..\..\exe\img\img_bin.py ED65_03.bmp
python ..\..\exe\img\img_bin.py ED65_04.bmp
..\..\exe\img\grit ED66_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED66_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED66_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED66_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED66_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED66_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED66_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED66_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED66_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED66_10.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED66_11.bmp
python ..\..\exe\img\img_bin.py ED66_12.bmp
python ..\..\exe\img\img_bin.py ED66_13.bmp
python ..\..\exe\img\img_bin.py ED66_14.bmp
python ..\..\exe\img\img_bin.py ED66_15.bmp
python ..\..\exe\img\img_bin.py ED66_16.bmp
python ..\..\exe\img\img_bin.py ED66_17.bmp
python ..\..\exe\img\img_bin.py ED66_18.bmp
python ..\..\exe\img\img_bin.py ED66_19.bmp
python ..\..\exe\img\img_bin.py ED66_20.bmp
python ..\..\exe\img\img_bin.py ED66_21.bmp
python ..\..\exe\img\img_bin.py ED66_22.bmp
python ..\..\exe\img\img_bin.py ED66_23.bmp
python ..\..\exe\img\img_bin.py ED66_24.bmp
python ..\..\exe\img\img_bin.py ED67_01.bmp
python ..\..\exe\img\img_bin.py ED67_02.bmp
python ..\..\exe\img\img_bin.py ED67_03.bmp
python ..\..\exe\img\img_bin.py ED67_04.bmp
python ..\..\exe\img\img_bin.py ED67_05.bmp
python ..\..\exe\img\img_bin.py ED67_06.bmp
python ..\..\exe\img\img_bin.py ED67_07.bmp
python ..\..\exe\img\img_bin.py ED67_08.bmp
python ..\..\exe\img\img_bin.py ED67_09.bmp
python ..\..\exe\img\img_bin.py ED67_10.bmp
python ..\..\exe\img\img_bin.py ED67_11.bmp
python ..\..\exe\img\img_bin.py ED67_12.bmp
python ..\..\exe\img\img_bin.py ED67_13.bmp
python ..\..\exe\img\img_bin.py ED67_14.bmp
python ..\..\exe\img\img_bin.py ED67_15.bmp
python ..\..\exe\img\img_bin.py ED67_16.bmp
python ..\..\exe\img\img_bin.py ED67_17.bmp
python ..\..\exe\img\img_bin.py ED67_18.bmp
python ..\..\exe\img\img_bin.py ED67_19.bmp
..\..\exe\img\grit ED67_20.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED67_21.bmp
python ..\..\exe\img\img_bin.py ED67_22.bmp
python ..\..\exe\img\img_bin.py ED67_23.bmp
python ..\..\exe\img\img_bin.py ED67_24.bmp
python ..\..\exe\img\img_bin.py ED68_01.bmp
python ..\..\exe\img\img_bin.py ED68_02.bmp
python ..\..\exe\img\img_bin.py ED68_03.bmp
python ..\..\exe\img\img_bin.py ED68_04.bmp
python ..\..\exe\img\img_bin.py ED68_05.bmp
python ..\..\exe\img\img_bin.py ED68_06.bmp
python ..\..\exe\img\img_bin.py ED68_07.bmp
python ..\..\exe\img\img_bin.py ED68_08.bmp
..\..\exe\img\grit ED68_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_28.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_29.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_30.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_31.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_32.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_33.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_34.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_35.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_36.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_37.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_38.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_39.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED68_40.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED68_42.bmp
python ..\..\exe\img\img_bin.py ED68_43.bmp
..\..\exe\img\grit ED71_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_16.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_17.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_18.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_19.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_20.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_21.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_22.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_23.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_24.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_25.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_26.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_27.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED71_28.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED71_29.bmp
python ..\..\exe\img\img_bin.py ED71_30.bmp
python ..\..\exe\img\img_bin.py ED71_31.bmp
python ..\..\exe\img\img_bin.py ED71_32.bmp
python ..\..\exe\img\img_bin.py ED71_33.bmp
python ..\..\exe\img\img_bin.py ED71_34.bmp
python ..\..\exe\img\img_bin.py ED71_35.bmp
python ..\..\exe\img\img_bin.py ED71_36.bmp
python ..\..\exe\img\img_bin.py ED71_37.bmp
python ..\..\exe\img\img_bin.py ED71_38.bmp
python ..\..\exe\img\img_bin.py ED71_39.bmp
python ..\..\exe\img\img_bin.py ED71_40.bmp
python ..\..\exe\img\img_bin.py ED71_41.bmp
python ..\..\exe\img\img_bin.py ED71_42.bmp
python ..\..\exe\img\img_bin.py ED71_43.bmp
python ..\..\exe\img\img_bin.py ED71_44.bmp
..\..\exe\img\grit ED72_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED72_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED72_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED72_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED72_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED72_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED72_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit ED72_08.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py ED73_01.bmp
..\..\exe\img\grit GAMEOVER_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_02.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_03.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_13.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_14.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit MAIZE_15.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP1_01.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py OP2_01.bmp
python ..\..\exe\img\img_bin.py OP2_02.bmp
python ..\..\exe\img\img_bin.py OP2_03.bmp
python ..\..\exe\img\img_bin.py OP2_04.bmp
..\..\exe\img\grit OP2_05.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP2_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP2_07.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP2_08.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP2_09.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP2_10.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP2_11.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP2_12.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP2_13.bmp -g -gb -ftb -gzl -p! -fh!
python ..\..\exe\img\img_bin.py OP3_01.bmp
python ..\..\exe\img\img_bin.py OP3_02.bmp
python ..\..\exe\img\img_bin.py OP3_03.bmp
..\..\exe\img\grit OP3_04.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit OP4_01.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit RI_SEL_06.bmp -g -gb -ftb -gzl -p! -fh!
..\..\exe\img\grit SOGNA98_01.bmp -g -gb -ftb -gzl -p! -fh!

ren *.img.bin *.
del *.bmp

rem ---------------------------------
rem DATファイルをGBAに変更（座標と画像サイズを２分の１）

for %%i in (*.dat) do python ..\..\exe\img\dat_half.py %%i


cd ..
