# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Param(file):
  # 元画像のサイズだけ取得
  p = Image.open(file[:-4] + ".png")
  iw, ih = p.size
  p.close()

  f = open(file, "rb")
  x = f.read()
  f.close()

  # サイズ情報をファイル先頭に付与
  f = open(file, 'wb')
  f.write(struct.pack('HH', iw, ih))
  f.write(x)
  f.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_para... " + file)
Param(file)


