# coding: Shift_JIS
# 240x160画像以外を無圧縮に変換（Mode4）

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Bin(file):
	bin = []
	img = Image.open(file)
	iw, ih = img.size

	if(iw % 2 == 1):
		print("[warning] odd number iw")

	for y in range(0, ih):
		for x in range(0, iw):
			bin.append(img.getpixel((x, y)))

	img.close()

	f = open(file[:-4] + ".img.bin", 'wb')
	for d in bin:
	    f.write(struct.pack("B", d))
	f.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print("img_bin... " + file)

Bin(file)


