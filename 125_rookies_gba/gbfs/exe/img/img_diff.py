# coding: Shift_JIS
# 差分ファイルに画像を合成します

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Diff(file1, file2):
	img1 = Image.open(file1)
	img2 = Image.open(file2)
	iw1, ih1 = img1.size
	iw2, ih2 = img2.size

	for y in range(0, ih1):
		for x in range(0, iw1):

			pal = img1.getpixel((x, y))

			if(pal != 14):
				img2.putpixel((x, y), pal)

	img1.close()
	img2.save(file1)
	img2.close()

# ---------------------------------------------------------------------------
file1 = sys.argv[1] # 差分
file2 = sys.argv[2] # 画像

print("img_diff... " + file1 + " " + file2)
Diff(file1, file2)

