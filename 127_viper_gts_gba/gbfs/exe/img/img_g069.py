# coding: Shift_JIS
# G069_01、G069_02専用（カルラと天使スクロールの合成）

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
# fromパレット番号をtoパレット番号に変更
def Col(img, f, t):
	iw, ih = img.size

	for y in range(0, ih):
		for x in range(0, iw):

			if(img.getpixel((x, y)) == f):
				img.putpixel((x, y), t)

# ---------------------------------------------------------------------------
# img1 -> img2
def Copy(img1, img2):
	iw, ih = img1.size

	for y in range(0, ih):
		for x in range(0, iw):

			pal = img1.getpixel((x, y))

			if(pal != 25):
				img2.putpixel((x, y), pal)

# ---------------------------------------------------------------------------
img1 = Image.open("G069_01.bmp")	# 天使
img2 = Image.open("G069_02.bmp")	# カルラ

print("img_g069...")


# 緑背景を黄に変更
Col(img2, 40, 25)

# 天使をコピーします
Copy(img1, img2)


sav = img2.copy()
img1.close()
img2.close()

# sav.show()
sav.save("G069_02.bmp")
