# coding: Shift_JIS
# しおりアイコンを１ファイルに統合
import os
import sys
import struct
from PIL import Image


print("img_ico... ")

tbl = ["SHIORI_AMANE", "SHIORI_YUKA", "SHIORI_AI", "SHIORI_ASUNA", "SHIORI_FUMINO"]
dst = Image.new("RGB", (40*5, 40*2))
alp = Image.new("RGB", (40*5, 40*2))

for i, f in enumerate(tbl):
	im0 = Image.open(f + "_0.bmp")
	im1 = Image.open(f + "_1.bmp")
	im2 = Image.open(f + "_0_m.bmp")
	im3 = Image.open(f + "_1_m.bmp")

	dst.paste(im0, (40*i,  0))
	dst.paste(im1, (40*i, 40))
	alp.paste(im2, (40*i,  0))
	alp.paste(im3, (40*i, 40))

dst.save("SIORI.png")
alp.save("SIORI_m.png")
