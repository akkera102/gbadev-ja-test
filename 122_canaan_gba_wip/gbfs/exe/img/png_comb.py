# coding: Shift_JIS
# スクロール画像の結合

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Comb(file):
  dst  = Image.new("P", (480, 768))
  src1 = Image.open(file + "h.png")
  src2 = Image.open(file + "l.png")

  dst.putpalette(src1.getpalette())

  dst.paste(src1, (0, 0))
  dst.paste(src2, (0, 533))

  src1.close()
  src2.close()

  dst.save(file + ".png")
  dst.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_comb... " + file)
Comb(file)

