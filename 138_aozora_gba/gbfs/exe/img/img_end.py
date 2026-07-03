# coding: Shift_JIS
# スタッフクレジット画像を480x320にします
import os
import sys
from PIL import Image


f_bg = sys.argv[1]
f_pa = sys.argv[2]
x_offset = int(sys.argv[3])
y_offset = int(sys.argv[4])

bg = Image.open(f_bg)
pa = Image.open(f_pa)

print("img_end... " + f_pa)

bg.paste(pa, (x_offset, y_offset))

# END_10は右下cropします
if(f_pa != "END_10.bmp"):
	crop = bg.crop((160, 140, 160+480, 140+320))
else:
	crop = bg.crop((800-480, 600-320, 800, 600))

base, ext = os.path.splitext(f_pa)
crop.save(base + ".png")

# crop.show()
