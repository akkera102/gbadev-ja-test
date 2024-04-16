# coding: Shift_JIS
# �A���t�@�u�����h�摜���o�C�i���ɕύX
# �o�C�i����1�h�b�g1�o�C�g�`��

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

