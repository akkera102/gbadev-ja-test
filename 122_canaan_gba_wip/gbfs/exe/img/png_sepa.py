# coding: Shift_JIS
# ２画面用画像の乱れ表示を修正

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Separate(file):
  src = Image.open(file)
  sw, sh = src.size

  dw = 480
  dh = 534
  dst = Image.new("P", (dw, dh))
  dst.putpalette(src.getpalette())
  dx = 0
  dy = 0

  for sy in range(0, sh):
    for sx in range(0, sw):

      dot = src.getpixel((sx, sy))
      dst.putpixel((dx, dy), dot)

      dx = dx + 1
      if dx >= dw:
          dx = 0
          dy = dy + 1

  src.close()

  name, ext = os.path.splitext(file)

  dst.save(name + ".png")
  dst.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_intr... " + file)
Separate(file)

