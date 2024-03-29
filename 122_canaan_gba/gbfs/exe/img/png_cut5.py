# coding: Shift_JIS
# 画像の下をカット

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Cut(file):
  p = Image.open(file)
  p.crop((0, 0, 480, 664)).save(file)
  p.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_cut5... " + file)
Cut(file)
