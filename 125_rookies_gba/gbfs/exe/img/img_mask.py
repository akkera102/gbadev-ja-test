# coding: Shift_JIS
# アルファブレンド用ファイルの作成

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Mask(f):
	s = Image.open(f)
	iw, ih = s.size

	m = Image.new("RGB", (iw, ih))


	for y in range(0, ih):
		for x in range(0, iw):

			if s.getpixel((x, y)) == 14:
				m.putpixel((x, y), (0, 0, 0))
			else:
				m.putpixel((x, y), (255, 255, 255))

	s.close()

	m.save(f[:-4] + "_m.bmp")
	m.close()

# ---------------------------------------------------------------------------
f = sys.argv[1]

print("img_mask... " + f)
Mask(f)
