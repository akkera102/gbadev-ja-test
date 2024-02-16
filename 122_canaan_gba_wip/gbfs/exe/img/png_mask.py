# coding: Shift_JIS
# パレット48 or 96番を使用したアルファブレンド用ファイル作成

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Mask(file):
  src = Image.open(file)
  iw, ih = src.size

  msk = Image.new("RGB", (iw, ih))

  if file == "ca002g.png" or file == "nukiff.png":
    tra = 3
  else:
    tra = 0

  for y in range(0, ih):
    for x in range(0, iw):

      col = src.getpixel((x, y))

      if col == tra:
        msk.putpixel((x, y), (0, 0, 0))
      else:
        msk.putpixel((x, y), (255, 255, 255))

  src.close()

  name, ext = os.path.splitext(file)

  msk.save(name + "_m.png")
  msk.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_mask... " + file)
Mask(file)
