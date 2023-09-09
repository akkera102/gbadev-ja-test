# coding: Shift_JIS
# タイトルと背景の合成（容量増加は気にしない

import os
import sys
import struct
from PIL import Image

img1 = Image.open("TITLE2.BMP")
img2 = Image.open("S17D.BMP")

print ("patching TITLE2.BMP")

iw1, ih1 = img1.size
iw2, ih2 = img2.size

pal = img1.getpalette()
sx  = int(iw2/2 - iw1/2)
sy  = int(ih2/2 - ih1/2) - 69

for y in range(0, ih1):
  for x in range(0, iw1):

    dot = img1.getpixel((x, y))

    if(dot != 96):
      img2.putpixel((sx + x, sy + y), (pal[dot*3+0], pal[dot*3+1], pal[dot*3+2]))

img1.close()
img2.save("TITLE2.BMP")
