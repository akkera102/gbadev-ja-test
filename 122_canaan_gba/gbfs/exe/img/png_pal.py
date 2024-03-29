# coding: Shift_JIS
# �p���b�g�ԍ�0�����F�ɕς���B�ꕔ�͑S�̓I�ɕύX

import os
import sys
import struct
from PIL import Image

# �G���f�B���O�@�X�^�b�t�N���W�b�g
listStaff = [
  "stl01.png", "stl02.png", "stl03.png", "stl04.png", "stl05.png",
  "stl06.png", "stl07.png", "stl08.png", "stl09.png", "stl10.png",
  "stl11.png",
]

# �������X�g�@�p���b�g�O���g�p
listIgnore = [
  "e10.png", "e16.png", "e001.png", "e002a.png", "e002b.png",
  "e006.png", "e013.png", "e015a.png", "e015a2.png", "e015b.png",
  "e015c.png", "e015d.png", "e021a.png", "e021b.png", "e021c.png",
  "e022a.png", "e022b.png", "e022b2.png", "e022c.png", "e022d.png",
  "e025.png", "e026.png", "e028.png", "e030a1.png", "e030b.png",
  "e031a.png", "e031b.png", "e034a1.png", "e034a2.png", "e034a3.png",
  "e034b.png", "e036.png", "e039a.png", "e039b.png", "e040.png",
  "e043.png", "e045a.png", "e045b.png", "e45b.png", "e046a.png",
  "e046b.png", "e051.png", "e056a.png", "e056b.png", "e056c.png",
  "e061.png", "e062a.png", "e062b.png", "e063a.png", "e063b.png",
  "en01.png", "en02.png", "en03.png", "en04.png", "en06.png",
  "en07a1.png", "en07a2.png", "en07b.png",
]

# ---------------------------------------------------------------------------
def Palette(file):

  # �w�i�摜�@�ꕔ�������ĕύX���Ȃ�
  if file[0] == 'b' and file[1] == 'g':
    if file != "bg15b.png" and file != "bg15c.png" and file != "bg18.png":
      return

  # �������X�g
  if file in listIgnore:
    return

  img = Image.open(file)
  pal = img.getpalette()
  iw, ih = img.size


  # �ő�摜�@�G���f�B���O�̃j�[�X�G(s005)�͗�O
  if iw == 640 and ih == 400 and file != "s005.png":
    return

  # �X�N���[���摜
  if iw == 480 and ih == 768:
    return

  # ���X�g�ɂ���ꍇ�̓p���b�g1-6�ύX
  if file in listStaff:
    for i in range(0, 16):
      if i >= 1 and i <= 6:
        pal[i*3+0] = 255
        pal[i*3+1] = 255
        pal[i*3+2] = 255
      else:
        pal[i*3+0] = 0
        pal[i*3+1] = 0
        pal[i*3+2] = 0
  else:
  # ���X�g�ɂȂ��ꍇ�̓p���b�g0�ύX
    pal[0] = 0
    pal[1] = 0
    pal[2] = 0

  img.putpalette(pal)
  img.save(file)
  img.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_pal... " + file)
Palette(file)
