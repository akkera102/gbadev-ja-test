# coding: Shift_JIS
# OP2専用

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Diff(pal, file1, file2):
	img1 = Image.open(file1)
	img2 = Image.open(file2)

	iw1, ih1 = img1.size
	iw2, ih2 = img2.size
	sx = iw2 - iw1
	sy = 0

	for y in range(0, ih1):
		for x in range(0, iw1):

			if(img1.getpixel((x, y)) != pal):
				img2.putpixel((sx + x, sy + y), img1.getpixel((x, y)))

	sav = img2.copy()
	img1.close()
	img2.close()

#	sav.show()
	sav.save(file1)


# ---------------------------------------------------------------------------
file1 = sys.argv[1]			# 差分画像
file2 = sys.argv[2]			# 元画像

print("img_OP2... " + file1 + " " + file2)

# 差分合成
Diff(12, file1, file2)


