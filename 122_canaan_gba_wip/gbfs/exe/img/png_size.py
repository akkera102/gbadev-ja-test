# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Resize(file):
  p = Image.open(file)
  iw, ih = p.size

  if iw == 96 and ih == 96:
    # ��
    iw =  56
    ih =  56
  elif iw == 480 and ih == 176:
    # ���w�i
    iw = 240
    ih =  88
  elif iw == 480 and ih == 768:
    # �X�N���[���w�i
    iw = 240
    ih = 384
  elif iw == 480 and ih == 288:
    # ��w�i
    iw = 240
    ih = 144
  elif iw == 640 and ih == 400:
    # �t���T�C�Y
    iw = 240
    ih = 160
  elif iw == 96 and ih == 128:
    # �p�^�p�^�A�j��
    iw =  64
    ih =  84
  elif iw == 96 and ih == 160:
    # �p�[�e�B�Ґ��\
    return
  elif iw == 320 and ih == 112:
    # �G���f�B���O��Ж��istl�j
    iw = 240
    ih =  76
  elif iw == 480 and ih == 304:
    # �e�B�e�B�����G�ica020a�j
    iw = 240
    ih = 152
  elif iw == 536 and ih == 256:
    # �G���f�B���O�w�i�ien00�j
    iw = 240
    ih = 114
  elif iw == 536 and ih == 400:
    # �G���f�B���O�w�i�ien4�j
    iw = 240
    ih = 160
  elif iw == 480 and ih == 320:
    # �ŏI�{�X�ό`�w�i�ibg15b,c�j
    iw = 240
    ih = 160
  elif iw == 240 and ih == 160:
    # GBA�g�p�iwaku06b�j
    return
  elif iw == 240 and ih == 288:
    # �������摜�̉��H��
    iw = 120
    ih = 144
  elif iw == 480 and ih == 432:
    # ���i(e050)
    iw = 240
    ih = 216
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
