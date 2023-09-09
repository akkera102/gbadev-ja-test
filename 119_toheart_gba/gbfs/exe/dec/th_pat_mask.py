# coding: Shift_JIS
# パレット48 or 96番を使用したアルファブレンド用ファイル作成

import os
import sys
from PIL import Image

fname = sys.argv[1]
print ("masking " + fname)

img = Image.open(fname)
iw, ih = img.size

msk = Image.new("RGB", (iw, ih))
col = 48

if(fname == "TITLE2.BMP"):
  col = 96


for y in range(0, ih):
  for x in range(0, iw):
    if(img.getpixel((x, y)) == col):
      msk.putpixel((x, y), (0, 0, 0))
    else:
      msk.putpixel((x, y), (255, 255, 255))


sname = os.path.splitext(fname)[0] + "_M.BMP"
msk.save(sname)

