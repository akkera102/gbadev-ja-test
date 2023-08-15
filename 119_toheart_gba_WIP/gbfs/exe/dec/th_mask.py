# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Bin2msk(file):
  f = open(file[:-4] + ".img.bin", "rb")
  x = f.read()
  f.close()

  f = open(file[:-4] + ".img.bin", 'wb')
  for i in range(len(x)):
    if((i % 2) == 0):
      f.write(struct.pack('B', x[i] & 0x1f))

  f.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

if (file[-5] == 'M'):
	print ("th_mask " + file[:-4] + ".img.bin")
	Bin2msk(file)

