# coding: Shift_JIS
# 320x224画像を120x80にカットし、256色に減色します
import os
import sys
from PIL import Image


fname = sys.argv[1]
img   = Image.open(fname)

print("img_cut... " + fname)

assert(img.size == (320, 224))


# クロップ
# 左右1px、上下6px削ります（中央寄せ）
left   = 1
top    = 6
right  = left + 318
bottom = top  + 212

cropped = img.crop((left, top, right, bottom))
resized = cropped.resize((180, 120), Image.Resampling.LANCZOS)
final   = resized.quantize(colors=256, kmeans=3)

base, ext = os.path.splitext(fname)
final.save(base + ".png")
# final.show()
