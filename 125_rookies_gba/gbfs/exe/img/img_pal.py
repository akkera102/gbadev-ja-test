# coding: Shift_JIS
# パレット番号14を黒色に変える
import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Palette(f):
	img = Image.open(f)
	cop = img.copy()
	img.close()

	pal = cop.getpalette()

	pal[14*3+0] = 0
	pal[14*3+1] = 0
	pal[14*3+2] = 0

	cop.putpalette(pal)
	cop.save(f)

# ---------------------------------------------------------------------------
f = sys.argv[1]

print("img_pal... " + f)
Palette(f)
