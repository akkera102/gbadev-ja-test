# coding: Shift_JIS
# G069_01、G069_02専用（カルラと天使スクロールの合成）

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
# img2 -> img1
def Copy(img1, img2):
	iw2, ih2 = img2.size

	for y in range(0, ih2):
		for x in range(0, iw2):

			pal = img2.getpixel((x, y))

			if(pal != 40):
				img1.putpixel((x, 16 + y), pal)

# ---------------------------------------------------------------------------
img1 = Image.open("G069_01.bmp")	# 天使
img2 = Image.open("G069_02.bmp")	# カルラ

print("img_g069...")


Copy(img1, img2)


sav = img1.copy()
img1.close()
img2.close()

# sav.show()
# sav.save("xxx.bmp")
sav.save("G069_02.bmp")
