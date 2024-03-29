@echo off

cd img

rem ---------------------------------
rem 背景差分の合成
python ..\..\exe\img\png_over.py bg00b.png bg00.png
python ..\..\exe\img\png_over.py bg01b.png bg01.png
python ..\..\exe\img\png_over.py bg01c.png bg01.png
python ..\..\exe\img\png_over.py bg01d.png bg01.png
python ..\..\exe\img\png_over.py bg06b.png bg06.png
python ..\..\exe\img\png_over.py bg07b.png bg07.png
python ..\..\exe\img\png_over.py bg07c.png bg07.png
python ..\..\exe\img\png_over.py bg10d.png bg10.png
python ..\..\exe\img\png_over.py bg13b.png bg13.png
python ..\..\exe\img\png_over.py bg13c.png bg13.png
python ..\..\exe\img\png_over.py bg15b.png bg15.png
python ..\..\exe\img\png_over.py bg15c.png bg15.png
python ..\..\exe\img\png_over.py bg16b.png bg16.png
python ..\..\exe\img\png_over.py bg17p1.png bg17.png
python ..\..\exe\img\png_over.py bg19c.png bg19.png
python ..\..\exe\img\png_over.py bg30n.png bg30.png

python ..\..\exe\img\png_over.py e030a2.png e030a1.png


rem ---------------------------------
rem 立ち絵差分の合成
python ..\..\exe\img\png_over.py ca002d1.png ca002a2.png
python ..\..\exe\img\png_over.py ca002d2.png ca002a2.png
python ..\..\exe\img\png_over.py ca007b2.png ca007b.png
python ..\..\exe\img\png_over.py ca007c.png ca007a2.png
python ..\..\exe\img\png_over.py ca007c2.png ca007a2.png
python ..\..\exe\img\png_over.py ca007d.png ca007a2.png
python ..\..\exe\img\png_over.py ca007d2.png ca007a2.png
python ..\..\exe\img\png_over.py ca008b.png ca008a.png
python ..\..\exe\img\png_over.py ca008c.png ca008a.png
python ..\..\exe\img\png_over.py ca009b.png ca009a.png
python ..\..\exe\img\png_over.py ca010b.png ca010a.png
python ..\..\exe\img\png_over.py ca010c.png ca010a.png
python ..\..\exe\img\png_over.py ca011a2.png ca011a.png
python ..\..\exe\img\png_over.py ca011e.png ca011a.png
python ..\..\exe\img\png_over.py ca011f2.png ca011a.png
python ..\..\exe\img\png_over.py ca012d.png ca012a.png
python ..\..\exe\img\png_over.py ca013f.png ca013a.png
python ..\..\exe\img\png_over.py ca014b.png ca014a.png
python ..\..\exe\img\png_over.py ca014c.png ca014a.png
python ..\..\exe\img\png_over.py ca014d.png ca014a.png
python ..\..\exe\img\png_over.py ca015c.png ca015a.png
python ..\..\exe\img\png_over.py ca018b.png ca018a.png
python ..\..\exe\img\png_over.py ca019c.png ca019a.png
python ..\..\exe\img\png_over.py ca019d.png ca019a.png
python ..\..\exe\img\png_over.py ca019e.png ca019a.png
python ..\..\exe\img\png_over.py ca020b.png ca020a.png
python ..\..\exe\img\png_over.py ca020c.png ca020a.png
python ..\..\exe\img\png_over.py ca020d.png ca020a.png
python ..\..\exe\img\png_over.py ca021b.png ca021a.png
python ..\..\exe\img\png_over.py ca021c.png ca021a.png
python ..\..\exe\img\png_over.py ca021d.png ca021a.png


rem ---------------------------------
rem ビジュアル差分の合成（使い方注意：正しい上書き順あり）
python ..\..\exe\img\png_over.py ca027b.png ca027c.png
python ..\..\exe\img\png_over.py ca027a.png ca027b.png
python ..\..\exe\img\png_over.py ca031a.png ca031b.png
python ..\..\exe\img\png_over.py ca032a.png ca032b.png
python ..\..\exe\img\png_over.py ca035b.png ca035c.png
python ..\..\exe\img\png_over.py ca035a.png ca035b.png
python ..\..\exe\img\png_over.py ca035d.png ca035a.png
python ..\..\exe\img\png_over.py ca038b.png ca038a.png
python ..\..\exe\img\png_over.py ca045c.png ca045b.png
python ..\..\exe\img\png_over.py ca045a.png ca045c.png
python ..\..\exe\img\png_over.py ca051b.png ca051a.png
python ..\..\exe\img\png_over.py ca052b.png ca052a.png
python ..\..\exe\img\png_over.py ca078a.png ca078b.png


rem ---------------------------------
rem パーティ背景の合成
python ..\..\exe\img\png_over.py pty001.png pty000.png
python ..\..\exe\img\png_over.py pty002.png pty000.png
python ..\..\exe\img\png_over.py pty003.png pty000.png
python ..\..\exe\img\png_over.py pty004.png pty000.png
python ..\..\exe\img\png_over.py pty005.png pty000.png
python ..\..\exe\img\png_over.py pty006.png pty000.png
python ..\..\exe\img\png_over.py pty007.png pty000.png
python ..\..\exe\img\png_over.py pty008.png pty000.png
python ..\..\exe\img\png_over.py pty009.png pty000.png
python ..\..\exe\img\png_over.py pty010.png pty000.png
python ..\..\exe\img\png_over.py pty011.png pty000.png
python ..\..\exe\img\png_over.py pty012.png pty000.png
python ..\..\exe\img\png_over.py pty013.png pty000.png
python ..\..\exe\img\png_over.py pty014.png pty000.png
python ..\..\exe\img\png_over.py pty015.png pty000.png
python ..\..\exe\img\png_over.py pty016.png pty000.png
python ..\..\exe\img\png_over.py pty017.png pty000.png
python ..\..\exe\img\png_over.py pty018.png pty000.png
python ..\..\exe\img\png_over.py pty019.png pty000.png
python ..\..\exe\img\png_over.py pty020.png pty000.png
python ..\..\exe\img\png_over.py pty021.png pty000.png
python ..\..\exe\img\png_over.py pty022.png pty000.png
python ..\..\exe\img\png_over.py pty023.png pty000.png
python ..\..\exe\img\png_over.py pty024.png pty000.png
python ..\..\exe\img\png_over.py pty025.png pty000.png
python ..\..\exe\img\png_over.py pty026.png pty000.png
python ..\..\exe\img\png_over.py pty027.png pty000.png
python ..\..\exe\img\png_over.py pty028.png pty000.png
python ..\..\exe\img\png_over.py pty029.png pty000.png
python ..\..\exe\img\png_over.py pty030.png pty000.png
python ..\..\exe\img\png_over.py pty031.png pty000.png
python ..\..\exe\img\png_over.py pty032.png pty000.png
python ..\..\exe\img\png_over.py pty033.png pty000.png
python ..\..\exe\img\png_over.py pty034.png pty000.png
python ..\..\exe\img\png_over.py pty035.png pty000.png
python ..\..\exe\img\png_over.py pty036.png pty000.png
python ..\..\exe\img\png_over.py pty037.png pty000.png
python ..\..\exe\img\png_over.py pty038.png pty000.png
python ..\..\exe\img\png_over.py pty039.png pty000.png
python ..\..\exe\img\png_over.py pty040.png pty000.png
python ..\..\exe\img\png_over.py pty041.png pty000.png
python ..\..\exe\img\png_over.py pty042.png pty000.png
python ..\..\exe\img\png_over.py pty043.png pty000.png
python ..\..\exe\img\png_over.py pty044.png pty000.png
python ..\..\exe\img\png_over.py pty045.png pty000.png
python ..\..\exe\img\png_over.py pty046.png pty000.png
python ..\..\exe\img\png_over.py pty047.png pty000.png
python ..\..\exe\img\png_over.py pty048.png pty000.png
python ..\..\exe\img\png_over.py pty049.png pty000.png
python ..\..\exe\img\png_over.py pty050.png pty000.png
python ..\..\exe\img\png_over.py pty051.png pty000.png
python ..\..\exe\img\png_over.py pty052.png pty000.png
python ..\..\exe\img\png_over.py pty053.png pty000.png
python ..\..\exe\img\png_over.py pty054.png pty000.png
del pty000.png
del pty999.png


rem ---------------------------------
rem フリップの分解
python ..\..\exe\img\png_cut1.py
rem 元の画像は削除
del pata.png
del pata2.png
del pata04.png
del pata12.png


rem ---------------------------------
rem waku06b専用カット
python ..\..\exe\img\png_cut2.py


rem ---------------------------------
rem e018xx専用カット
python ..\..\exe\img\png_cut3.py e018a1.png
python ..\..\exe\img\png_cut3.py e018a2.png
python ..\..\exe\img\png_cut3.py e018b1.png
python ..\..\exe\img\png_cut3.py e018b2.png
python ..\..\exe\img\png_cut3.py e018c1.png
python ..\..\exe\img\png_cut3.py e018c2.png
python ..\..\exe\img\png_cut3.py e018d1.png
python ..\..\exe\img\png_cut3.py e018d2.png
python ..\..\exe\img\png_cut3.py e018e.png
python ..\..\exe\img\png_cut3.py e018f.png


rem ---------------------------------
rem e050専用カット
python ..\..\exe\img\png_cut4.py e050.png


rem ---------------------------------
rem s034専用カット
python ..\..\exe\img\png_cut5.py s034.png


rem ---------------------------------
rem pngパレットの変更
for %%f in (*.png) do python ..\..\exe\img\png_pal.py "%%f"


rem ---------------------------------
rem アルファブレンド画像を作成

python ..\..\exe\img\png_mask.py ca001a.png
python ..\..\exe\img\png_mask.py ca001b.png
python ..\..\exe\img\png_mask.py ca001c.png
python ..\..\exe\img\png_mask.py ca001d.png
python ..\..\exe\img\png_mask.py ca001e.png
python ..\..\exe\img\png_mask.py ca001f.png
python ..\..\exe\img\png_mask.py ca001g.png
python ..\..\exe\img\png_mask.py ca002a1.png
python ..\..\exe\img\png_mask.py ca002a2.png
python ..\..\exe\img\png_mask.py ca002b1.png
python ..\..\exe\img\png_mask.py ca002b2.png
python ..\..\exe\img\png_mask.py ca002c1.png
python ..\..\exe\img\png_mask.py ca002c2.png
python ..\..\exe\img\png_mask.py ca002d1.png
python ..\..\exe\img\png_mask.py ca002d2.png
python ..\..\exe\img\png_mask.py ca002e1.png
python ..\..\exe\img\png_mask.py ca002e2.png
python ..\..\exe\img\png_mask.py ca002f.png
python ..\..\exe\img\png_mask.py ca002g.png
python ..\..\exe\img\png_mask.py ca002h1.png
python ..\..\exe\img\png_mask.py ca002h2.png
python ..\..\exe\img\png_mask.py ca003a.png
python ..\..\exe\img\png_mask.py ca003b.png
python ..\..\exe\img\png_mask.py ca003c.png
python ..\..\exe\img\png_mask.py ca004a.png
python ..\..\exe\img\png_mask.py ca004b.png
python ..\..\exe\img\png_mask.py ca004c.png
python ..\..\exe\img\png_mask.py ca004d.png
python ..\..\exe\img\png_mask.py ca004e.png
python ..\..\exe\img\png_mask.py ca004f.png
python ..\..\exe\img\png_mask.py ca004g.png
python ..\..\exe\img\png_mask.py ca004h.png
python ..\..\exe\img\png_mask.py ca004i.png
python ..\..\exe\img\png_mask.py ca004j.png
python ..\..\exe\img\png_mask.py ca004k.png
python ..\..\exe\img\png_mask.py ca005a.png
python ..\..\exe\img\png_mask.py ca005b.png
python ..\..\exe\img\png_mask.py ca005c.png
python ..\..\exe\img\png_mask.py ca005d.png
python ..\..\exe\img\png_mask.py ca005e.png
python ..\..\exe\img\png_mask.py ca005f.png
python ..\..\exe\img\png_mask.py ca006a.png
python ..\..\exe\img\png_mask.py ca006b.png
python ..\..\exe\img\png_mask.py ca006c.png
python ..\..\exe\img\png_mask.py ca006d.png
python ..\..\exe\img\png_mask.py ca006e.png
python ..\..\exe\img\png_mask.py ca006f.png
python ..\..\exe\img\png_mask.py ca007a.png
python ..\..\exe\img\png_mask.py ca007a2.png
python ..\..\exe\img\png_mask.py ca007a3.png
python ..\..\exe\img\png_mask.py ca007b.png
python ..\..\exe\img\png_mask.py ca007b2.png
python ..\..\exe\img\png_mask.py ca007c.png
python ..\..\exe\img\png_mask.py ca007c2.png
python ..\..\exe\img\png_mask.py ca007d.png
python ..\..\exe\img\png_mask.py ca007d2.png
python ..\..\exe\img\png_mask.py ca007e.png
python ..\..\exe\img\png_mask.py ca008a.png
python ..\..\exe\img\png_mask.py ca008b.png
python ..\..\exe\img\png_mask.py ca008c.png
python ..\..\exe\img\png_mask.py ca008d.png
python ..\..\exe\img\png_mask.py ca008e.png
python ..\..\exe\img\png_mask.py ca008f.png
python ..\..\exe\img\png_mask.py ca008h.png
python ..\..\exe\img\png_mask.py ca009a.png
python ..\..\exe\img\png_mask.py ca009b.png
python ..\..\exe\img\png_mask.py ca009c.png
python ..\..\exe\img\png_mask.py ca009d.png
python ..\..\exe\img\png_mask.py ca009e.png
python ..\..\exe\img\png_mask.py ca010a.png
python ..\..\exe\img\png_mask.py ca010b.png
python ..\..\exe\img\png_mask.py ca010c.png
python ..\..\exe\img\png_mask.py ca011a.png
python ..\..\exe\img\png_mask.py ca011a2.png
python ..\..\exe\img\png_mask.py ca011b.png
python ..\..\exe\img\png_mask.py ca011c.png
python ..\..\exe\img\png_mask.py ca011d.png
python ..\..\exe\img\png_mask.py ca011e.png
python ..\..\exe\img\png_mask.py ca011f.png
python ..\..\exe\img\png_mask.py ca011f2.png
python ..\..\exe\img\png_mask.py ca011g.png
python ..\..\exe\img\png_mask.py ca011h.png
python ..\..\exe\img\png_mask.py ca012a.png
python ..\..\exe\img\png_mask.py ca012b.png
python ..\..\exe\img\png_mask.py ca012c.png
python ..\..\exe\img\png_mask.py ca012d.png
python ..\..\exe\img\png_mask.py ca012e.png
python ..\..\exe\img\png_mask.py ca013a.png
python ..\..\exe\img\png_mask.py ca013b.png
python ..\..\exe\img\png_mask.py ca013c.png
python ..\..\exe\img\png_mask.py ca013d.png
python ..\..\exe\img\png_mask.py ca013e.png
python ..\..\exe\img\png_mask.py ca013f.png
python ..\..\exe\img\png_mask.py ca014a.png
python ..\..\exe\img\png_mask.py ca014b.png
python ..\..\exe\img\png_mask.py ca014c.png
python ..\..\exe\img\png_mask.py ca014d.png
python ..\..\exe\img\png_mask.py ca015a.png
python ..\..\exe\img\png_mask.py ca015b.png
python ..\..\exe\img\png_mask.py ca015c.png
python ..\..\exe\img\png_mask.py ca016a.png
python ..\..\exe\img\png_mask.py ca016b.png
python ..\..\exe\img\png_mask.py ca016c.png
python ..\..\exe\img\png_mask.py ca017a.png
python ..\..\exe\img\png_mask.py ca017b.png
python ..\..\exe\img\png_mask.py ca017c.png
python ..\..\exe\img\png_mask.py ca018a.png
python ..\..\exe\img\png_mask.py ca018b.png
python ..\..\exe\img\png_mask.py ca018c.png
python ..\..\exe\img\png_mask.py ca018d.png
python ..\..\exe\img\png_mask.py ca018e.png
python ..\..\exe\img\png_mask.py ca019a.png
python ..\..\exe\img\png_mask.py ca019b.png
python ..\..\exe\img\png_mask.py ca019c.png
python ..\..\exe\img\png_mask.py ca019d.png
python ..\..\exe\img\png_mask.py ca019e.png
python ..\..\exe\img\png_mask.py ca020a.png
python ..\..\exe\img\png_mask.py ca020b.png
python ..\..\exe\img\png_mask.py ca020c.png
python ..\..\exe\img\png_mask.py ca020d.png
python ..\..\exe\img\png_mask.py ca020e.png
python ..\..\exe\img\png_mask.py ca020f.png
python ..\..\exe\img\png_mask.py ca021a.png
python ..\..\exe\img\png_mask.py ca021b.png
python ..\..\exe\img\png_mask.py ca021c.png
python ..\..\exe\img\png_mask.py ca021d.png
python ..\..\exe\img\png_mask.py ca022a.png
python ..\..\exe\img\png_mask.py ca022b.png
python ..\..\exe\img\png_mask.py ca023a.png
python ..\..\exe\img\png_mask.py ca023b.png
python ..\..\exe\img\png_mask.py ca024a.png
python ..\..\exe\img\png_mask.py ca024b.png
python ..\..\exe\img\png_mask.py ca025a.png
python ..\..\exe\img\png_mask.py ca025b.png
python ..\..\exe\img\png_mask.py ca025c.png

python ..\..\exe\img\png_mask.py e004.png
python ..\..\exe\img\png_mask.py e019.png
python ..\..\exe\img\png_mask.py e019f.png
python ..\..\exe\img\png_mask.py e032.png
python ..\..\exe\img\png_mask.py e060a.png
python ..\..\exe\img\png_mask.py e060b.png
python ..\..\exe\img\png_mask.py bg18.png


cd ..
