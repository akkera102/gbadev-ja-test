# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def paramAdd(file):
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
file = sys.argv[1]

if (file[-5] != 'M'):
	print ("th_param " + file[:-4] + ".img")
	paramAdd(file)


