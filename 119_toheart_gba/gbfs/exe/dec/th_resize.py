# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Resize(file):
  p = Image.open(file)
  iw, ih = p.size

  iw = int(iw * 0.375)
  ih = int(ih * 0.334)
  if(iw % 2 != 0): iw -= 1
  if(ih % 2 != 0): ih -= 1

  p = p.convert("RGB")
  p = p.resize((iw,ih), Image.LANCZOS)

  p.save(file)
  p.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("th_resize " + file)
Resize(file)
