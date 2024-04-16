@echo off

cd img


rem ---------------------------------
rem 差分データを合成


python ..\..\exe\img\png_over.py 01n.png 001.png
python ..\..\exe\img\png_over.py 2c1.png 2a1.png
python ..\..\exe\img\png_over.py 2c2.png 2a2.png
python ..\..\exe\img\png_over.py 2d1.png 2a1.png
python ..\..\exe\img\png_over.py 2d2.png 2a2.png
python ..\..\exe\img\png_over.py 03n.png 003.png
python ..\..\exe\img\png_over.py 06n.png 006.png
python ..\..\exe\img\png_over.py 07b.png 07a.png
python ..\..\exe\img\png_over.py 6c2.png 16c.png
python ..\..\exe\img\png_over.py 6d2.png 16d.png
python ..\..\exe\img\png_over.py 7b2.png 7a2.png
python ..\..\exe\img\png_over.py 7c2.png 7a2.png
python ..\..\exe\img\png_over.py 08n.png 008.png
python ..\..\exe\img\png_over.py 09n.png 009.png
python ..\..\exe\img\png_over.py 10b.png 10a.png
python ..\..\exe\img\png_over.py 12b.png 012.png
python ..\..\exe\img\png_over.py 16b.png 16a.png
python ..\..\exe\img\png_over.py 17b.png 17c.png
python ..\..\exe\img\png_over.py 17a.png 17b.png
python ..\..\exe\img\png_over.py 25b.png 25a.png
python ..\..\exe\img\png_over.py 25c.png 25a.png
python ..\..\exe\img\png_over.py 25e.png 25a.png
python ..\..\exe\img\png_over.py 25g.png 25a.png
python ..\..\exe\img\png_over.py 30c.png 30b.png
python ..\..\exe\img\png_over.py 30d.png 30c.png
python ..\..\exe\img\png_over.py 37b.png 37a.png
python ..\..\exe\img\png_over.py 37c.png 37a.png
python ..\..\exe\img\png_over.py 43b.png 43a.png
python ..\..\exe\img\png_over.py 43c.png 43a.png
python ..\..\exe\img\png_over.py 43e.png 43d.png
python ..\..\exe\img\png_over.py 52b.png 52a.png
python ..\..\exe\img\png_over.py 52c.png 52a.png
python ..\..\exe\img\png_over.py 52d.png 52a.png
python ..\..\exe\img\png_over.py 52e.png 52a.png
python ..\..\exe\img\png_over.py 54b.png 54a.png
python ..\..\exe\img\png_over.py 58b.png 58a.png
python ..\..\exe\img\png_over.py 60a.png 60b.png
python ..\..\exe\img\png_over.py 60c.png 60a.png
python ..\..\exe\img\png_over.py 67b.png 67a.png
python ..\..\exe\img\png_over.py 67c.png 67b.png
python ..\..\exe\img\png_over.py 79b.png 79a.png
python ..\..\exe\img\png_over.py 79c.png 79a.png
python ..\..\exe\img\png_over.py 79d.png 79a.png
python ..\..\exe\img\png_over.py 84b.png 84a.png
python ..\..\exe\img\png_over.py 84d.png 84a.png
python ..\..\exe\img\png_over.py 86b.png 86a.png
python ..\..\exe\img\png_over.py 86c.png 86b.png
python ..\..\exe\img\png_over.py 86d.png 86c.png
python ..\..\exe\img\png_over.py 90a.png 90z.png
python ..\..\exe\img\png_over.py 90b.png 90z.png
python ..\..\exe\img\png_over.py 90c.png 90z.png
python ..\..\exe\img\png_over.py 90d.png 90z.png
python ..\..\exe\img\png_over.py 96b.png 96a.png
python ..\..\exe\img\png_over.py 4bd.png 64b.png


rem ---------------------------------
rem マスクファイル作成

python ..\..\exe\img\png_mask.py 2a1.png
python ..\..\exe\img\png_mask.py 2a2.png
python ..\..\exe\img\png_mask.py 2b1.png
python ..\..\exe\img\png_mask.py 2b2.png
python ..\..\exe\img\png_mask.py 2c1.png
python ..\..\exe\img\png_mask.py 2c2.png
python ..\..\exe\img\png_mask.py 2d1.png
python ..\..\exe\img\png_mask.py 2d2.png
python ..\..\exe\img\png_mask.py 6c2.png
python ..\..\exe\img\png_mask.py 6d2.png
python ..\..\exe\img\png_mask.py 7a2.png
python ..\..\exe\img\png_mask.py 7b2.png
python ..\..\exe\img\png_mask.py 7c2.png
python ..\..\exe\img\png_mask.py 7d2.png
python ..\..\exe\img\png_mask.py 7e2.png
python ..\..\exe\img\png_mask.py 16a.png
python ..\..\exe\img\png_mask.py 16b.png
python ..\..\exe\img\png_mask.py 16c.png
python ..\..\exe\img\png_mask.py 16d.png
python ..\..\exe\img\png_mask.py 25a.png
python ..\..\exe\img\png_mask.py 25b.png
python ..\..\exe\img\png_mask.py 25c.png
python ..\..\exe\img\png_mask.py 25d.png
python ..\..\exe\img\png_mask.py 25e.png
python ..\..\exe\img\png_mask.py 25f.png
python ..\..\exe\img\png_mask.py 25g.png
python ..\..\exe\img\png_mask.py 25h.png
python ..\..\exe\img\png_mask.py 37a.png
python ..\..\exe\img\png_mask.py 37b.png
python ..\..\exe\img\png_mask.py 37c.png
python ..\..\exe\img\png_mask.py 37d.png
python ..\..\exe\img\png_mask.py 37e.png
python ..\..\exe\img\png_mask.py 039.png
python ..\..\exe\img\png_mask.py 43a.png
python ..\..\exe\img\png_mask.py 43b.png
python ..\..\exe\img\png_mask.py 43c.png
python ..\..\exe\img\png_mask.py 43d.png
python ..\..\exe\img\png_mask.py 43e.png
python ..\..\exe\img\png_mask.py 52a.png
python ..\..\exe\img\png_mask.py 52b.png
python ..\..\exe\img\png_mask.py 52c.png
python ..\..\exe\img\png_mask.py 52d.png
python ..\..\exe\img\png_mask.py 52e.png
python ..\..\exe\img\png_mask.py 58a.png
python ..\..\exe\img\png_mask.py 58b.png
python ..\..\exe\img\png_mask.py 58c.png
python ..\..\exe\img\png_mask.py 64a.png
python ..\..\exe\img\png_mask.py 64b.png
python ..\..\exe\img\png_mask.py 64c.png
python ..\..\exe\img\png_mask.py 083.png
python ..\..\exe\img\png_mask.py 84a.png
python ..\..\exe\img\png_mask.py 84b.png
python ..\..\exe\img\png_mask.py 84c.png
python ..\..\exe\img\png_mask.py 84d.png
python ..\..\exe\img\png_mask.py 90a.png
python ..\..\exe\img\png_mask.py 90b.png
python ..\..\exe\img\png_mask.py 90c.png
python ..\..\exe\img\png_mask.py 90d.png
python ..\..\exe\img\png_mask.py 90e.png
python ..\..\exe\img\png_mask.py 4bd.png


rem ---------------------------------
rem mitori.pngカット
python ..\..\exe\img\png_map.py mitori.png


rem ---------------------------------
rem 不要ファイルを消去

del 02n.png
del 04n.png
del 05n.png
del 07n.png
del 10n.png
del 11n.png
del 12n.png
del 13n.png
del 14n.png
del 15n.png
del 49n.png
del 90z.png
del backtmp2.png
del bk0.png
del half.png
del oyapat.png
del win.png
del winopn.png
del mitori.png


cd ..
