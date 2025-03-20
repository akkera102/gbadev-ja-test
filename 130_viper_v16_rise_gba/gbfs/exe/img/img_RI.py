# coding: Shift_JIS
# RI_SEL_06専用。448x320リサイズ、メーカーロゴを右下にコピペします


import os
import re
import sys
import struct
from PIL import Image, ImageDraw

# ---------------------------------------------------------------------------
file = sys.argv[1]			# 画像

print("img_RI... " + file)

img = Image.open(file)
cpy = img.copy()
img.close()

cre = cpy.crop((514, 457, 626, 473))
dst = cpy.crop((96, 40, 544, 360))

iw1, ih1 = cre.size
iw2, ih2 = dst.size

dst.paste(cre, (iw2 - iw1, ih2 - ih1))

# cre.show()
# dst.show()
# dst.save("TEST.bmp")
dst.save(file)
