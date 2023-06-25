# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Bmp2img(file):
  p = Image.open(file)
  iw, ih = p.size
  p.close()

  f = open(file[:-4] + ".img", "rb")
  x = f.read()
  f.close()

  f = open(file[:-4] + ".img", 'wb')
  f.write(struct.pack('HH', iw, ih))
  f.write(x)

  f.close()

# ---------------------------------------------------------------------------
def Bmp2msk(file):
  p = Image.open(file)
  iw, ih = p.size
  p.close()

  f = open(file[:-4] + ".img", "rb")
  x = f.read()
  f.close()

  f = open(file[:-4] + ".img", 'wb')
  for i in range(len(x)):
    if((i % 2) == 0):
      f.write(struct.pack('B', x[i] & 0x1f))

  f.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

if (file[-5] == 'M'):
	print ("param " + file)
	Bmp2msk(file)
else:
	print ("param " + file)
	Bmp2img(file)


