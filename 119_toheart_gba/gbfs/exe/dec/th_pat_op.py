# coding: Shift_JIS
# �I�[�v�j���O�\���Ŏg���ʐ^�摜�Ɣw�i���������܂��i�e�ʑ����͋C�ɂ��Ȃ�

import os
import sys
import struct
from PIL import Image


file = sys.argv[1]

print ("patching " + file)

img1 = Image.open(file)
img2 = Image.open("S49D.BMP")

iw1, ih1 = img1.size
iw2, ih2 = img2.size

img1 = img1.convert('RGB')
img2 = img2.convert('RGB')

img2.paste(img1, (int(iw2/2 - iw1/2), int(ih2/2 - ih1/2)))

img2.save(file)
