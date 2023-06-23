import os
import Image

# mode3 -> spr font

#------------------------------------
cnt  = 6962
x    = 0
y    = 0
x2   = 0
y2   = 0
pNew = Image.new('RGB', (384, 2180))
pBmp = Image.open('fnt_k12x10w.bmp')


for i in range(cnt):
	
	for j in range(10):
		box = (1+x, 1+y+j, 1+x+12, 1+y+j+1)
		im  = pBmp.crop(box)
		
		pNew.paste(im, (x2, y2))
		
		x2 += 12
		if(x2 == 384):
			x2  = 0
			y2 += 1
	
	x += 13
	if(x == 416):
		x = 0
		y += 11


pNew.save('new.bmp')
