# coding: Shift_JIS
# 元画像に対して差分画像を合成。保存先は差分ではなく、元画像（file2）で保存します

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
	sav.save(file2)


# ---------------------------------------------------------------------------
file1 = sys.argv[1]			# 座標情報（DAT）
file2 = sys.argv[3]			# 差分画像（注意！引数3を使用）
file3 = sys.argv[2]			# 元画像　（注意！引数2を使用）

print("img_dif2... " + file1 + " " + file3 + " " + file2)

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


