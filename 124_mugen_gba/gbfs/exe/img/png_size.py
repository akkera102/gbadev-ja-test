# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Resize(file):
  p = Image.open(file)
  iw, ih = p.size

  if iw == 480 and ih == 304:
    # 背景、キャラクタ（本来のアスペで考えると240x152）
    iw =  240
    ih =  160
  elif iw == 640 and ih == 400:
    # Hシーン、イベントなど
    iw = 240
    ih = 160
  elif iw == 224 and ih == 128:
    # 見取り図
    iw = 224
    ih = 128
  else:
    print("Error Size : %s %d %d" % (file, iw, ih))
    return

  p = p.convert("RGB")
  p = p.resize((iw, ih), Image.LANCZOS)
  p.save(file)
  p.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_size... " + file)
Resize(file)
