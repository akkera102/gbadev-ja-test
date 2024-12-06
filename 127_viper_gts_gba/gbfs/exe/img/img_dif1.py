# coding: Shift_JIS
# 差分画像にオリジナル画像を合成します。開始座標指定なし

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Diff(pal, file1, file2):
	img1 = Image.open(file1)
	img2 = Image.open(file2)

	iw, ih = img1.size

	for y in range(0, ih):
		for x in range(0, iw):

			if(img1.getpixel((x, y)) == pal):
				img1.putpixel((x, y), img2.getpixel((x, y)))

	sav = img1.copy()
	img1.close()
	img2.close()

#	sav.show()
	sav.save(file1)

# ---------------------------------------------------------------------------
pal   = sys.argv[1]			# 透明色
file1 = sys.argv[2]			# 差分画像
file2 = sys.argv[3]			# 元画像

print("img_dif1... " + pal + " " + file1 + " " + file2)

Diff(int(pal), file1, file2)

