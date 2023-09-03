# coding: Shift_JIS
# C1C01 校舎屋上の背景と虹を合成

import os
import sys
from PIL import Image


fname1 = "C1C01.BMP"
fname2 = "S15D.BMP"

print ("patching " + fname1)

img1 = Image.open(fname1)
img2 = Image.open(fname2).convert("RGB")

iw, ih = img1.size
pal = img1.getpalette()


for y in range(0, ih):
  for x in range(0, iw):

    dot = img1.getpixel((x, y))

    if(dot != 48):
      img2.putpixel((x, y), (pal[dot*3+0], pal[dot*3+1], pal[dot*3+2]))

img1.close()
img2.save("C1C01.BMP")
