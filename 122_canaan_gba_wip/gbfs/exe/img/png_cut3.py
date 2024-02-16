# coding: Shift_JIS
# 画像の右半分をカット

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Cut(file):
  p = Image.open(file)
  p.crop((0, 0, 240, 288)).save(file)
  p.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_cut3... " + file)
Cut(file)
