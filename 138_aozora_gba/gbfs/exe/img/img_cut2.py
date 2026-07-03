# coding: Shift_JIS
# 立ち絵（???x600サイズ）を???x532にカットします。下半身の削除
import os
import sys
from PIL import Image


fname  = sys.argv[1]
img = Image.open(fname)
iw, ih = img.size

assert(ih == 600)

print("img_cut2... " + fname)

crop = img.crop((0, 0, iw, ih-68))

base, ext = os.path.splitext(fname)
crop.save(base + ".png")

# crop.show()
# img.show()
