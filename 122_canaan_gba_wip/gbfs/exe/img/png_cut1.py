# coding: Shift_JIS
# pataとpata2.pngフリップのカット

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
p = Image.open("pata.png")
i = 0

for y in range(0, 3):
  for x in range(0, 6):
    if i == 16:
      continue

    file = "pata%02d.png" % (i)
    i = i + 1

    print("png_cut1... " + file)
    p.crop((x*96, y*128, x*96+96, y*128+128)).save(file)

p.close()

# ---------------------------------------------------------------------------
p = Image.open("pata2.png")

for x in range(0, 5):
  file = "pata%02d.png" % (i)
  i = i + 1
  print("png_cut1... " + file)
  p.crop((x*96, 0, x*96+96, 128)).save(file)


p.close()
