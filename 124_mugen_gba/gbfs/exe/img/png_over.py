# coding: Shift_JIS
# �����t�@�C���Ɍ��摜���������܂�

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Over(file1, file2):
  img1 = Image.open(file1)
  img2 = Image.open(file2)
  iw1, ih1 = img1.size
  iw2, ih2 = img2.size

  for y in range(0, ih1):
    for x in range(0, iw1):

      # ������ƌ��ŉ�ʃT�C�Y���قȂ�ꍇ
      if y < ih2:
        dot1 = img1.getpixel((x, y))
        dot2 = img2.getpixel((x, y))

        if(dot1 != 0):
          img1.putpixel((x, y), dot1)
        else:
          img1.putpixel((x, y), dot2)

      else:
        dot1 = img1.getpixel((x, y))

        if(dot1 != 0):
          img1.putpixel((x, y), dot1)
        else:
          img1.putpixel((x, y), 0)

  # �������T�C�Y�Ƀ��T�C�Y
  img1 = img1.crop((0, 0, iw2, ih2))

  img1.save(file1)
  img1.close()
  img2.close()

# ---------------------------------------------------------------------------
file1 = sys.argv[1]
file2 = sys.argv[2]

print ("png_over... " + file1 + " " + file2)
Over(file1, file2)

