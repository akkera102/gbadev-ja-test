# coding: shift_jis
import os
from PIL import Image

# mode3 -> spr font

#------------------------------------
cnt = 6962
sx  = 0
sy  = 0
dx  = 0
dy  = 0
x   = 0
y   = 0
# �p���b�g�ԍ������L����ׁA�㏑������ǂݍ���
bmp = Image.open('fnt_m8x8.bmp')
new = Image.open('fnt_m8x8.bmp')


for i in range(cnt):
	for y in range(8):
		for x in range(8):
			val = bmp.getpixel((sx + x, sy + y))
			new.putpixel((dx, dy), val)

			dx += 1
			if(dx == 8*32):
				dx  = 0
				dy += 1

	sx += 8
	if(sx == 8*32):
		sx  = 0
		sy += 8


new.save('fnt_m8x8.png')
