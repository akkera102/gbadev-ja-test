# coding: shift_jis
import os
from PIL import Image

# mode3 -> spr font

#------------------------------------
cnt = 6962 + 14 + 64
sx  = 0
sy  = 0
dx  = 0
dy  = 0
x   = 0
y   = 0
# �p���b�g�ԍ������L����ׁA�㏑������ǂݍ���
bmp = Image.open('k12x10.bmp')
new = Image.open('k12x10.bmp')


for i in range(cnt):
	for y in range(10):
		for x in range(12):
			val = bmp.getpixel((sx + x, sy + y))
			new.putpixel((dx, dy), val)

			dx += 1
			if(dx == 384):
				dx  = 0
				dy += 1

	sx += 12
	if(sx == 384):
		sx  = 0
		sy += 10


new.save('fnt_k12x10.png')
