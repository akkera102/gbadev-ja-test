# coding: Shift_JIS
# 元画像に対して差分画像を合成。元画像サイズで保存します

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Diff(pal, sx, sy, file1, file2):
	img1 = Image.open(file1)
	img2 = Image.open(file2)

	iw, ih = img1.size

	for y in range(0, ih):
		for x in range(0, iw):

			if(img1.getpixel((x, y)) != pal):
				img2.putpixel((sx + x, sy + y), img1.getpixel((x, y)))

	sav = img2.copy()
	img1.close()
	img2.close()

#	sav.show()
	sav.save(file1)


# ---------------------------------------------------------------------------
file1 = sys.argv[1]			# 座標情報（DAT）
file2 = sys.argv[2]			# 差分画像
file3 = sys.argv[3]			# 元画像

print("img_dif1... " + file1 + " " + file2 + " " + file3)

# 開始座標をDAT情報より取得
f = open(file1, "rb")
d = f.read()
f.close()

num = int(re.findall(r'\d+', file2)[-1]) - 1
pos = 16 + 256*2 + num*8
sx  = d[pos + 0] + (d[pos + 1] << 8)
sy  = d[pos + 2] + (d[pos + 3] << 8)

# 差分合成
Diff(12, sx, sy, file2, file3)


