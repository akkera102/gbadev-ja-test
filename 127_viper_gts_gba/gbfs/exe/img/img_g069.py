# coding: Shift_JIS
# G069_01�AG069_02��p�i�J�����ƓV�g�X�N���[���̍����j

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
# from�p���b�g�ԍ���to�p���b�g�ԍ��ɕύX
def Col(img, f, t):
	iw, ih = img.size

	for y in range(0, ih):
		for x in range(0, iw):

			if(img.getpixel((x, y)) == f):
				img.putpixel((x, y), t)

# ---------------------------------------------------------------------------
# img1 -> img2
def Copy(img1, img2):
	iw, ih = img1.size

	for y in range(0, ih):
		for x in range(0, iw):

			pal = img1.getpixel((x, y))

			if(pal != 25):
				img2.putpixel((x, y), pal)

# ---------------------------------------------------------------------------
img1 = Image.open("G069_01.bmp")	# �V�g
img2 = Image.open("G069_02.bmp")	# �J����

print("img_g069...")


# �Δw�i�����ɕύX
Col(img2, 40, 25)

# �V�g���R�s�[���܂�
Copy(img1, img2)


sav = img2.copy()
img1.close()
img2.close()

# sav.show()
sav.save("G069_02.bmp")
