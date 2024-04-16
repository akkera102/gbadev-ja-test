# coding: Shift_JIS
# アルファブレンド画像をバイナリに変更
# バイナリは1ドット1バイト形式

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Png2msk(file):
  src = Image.open(file)
  iw, ih = src.size

  list = []

  for y in range(0, ih):
    for x in range(0, iw):

      dot = src.getpixel((x, y))
      r, g, b = dot
      hex = (int)(r / 8)
      list.append(hex)

  src.close()

  name, ext = os.path.splitext(file)

  f = open(name[:-2] + ".msk", "wb")
  f.write(bytearray(list))
  f.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print("png_msk... " + file)
Png2msk(file)

