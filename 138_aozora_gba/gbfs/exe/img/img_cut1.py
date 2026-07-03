# coding: Shift_JIS
# 背景、イベント画像(800x600サイズ)を798x532にカットします
import os
import sys
from PIL import Image


fname  = sys.argv[1]
offset = int(sys.argv[2])

width  = 798
height = 532
assert(0 <= offset <= 600 - height)		# 0-68

img = Image.open(fname)

# HGRP28のみ800x602
assert(img.size == (800, 600) or img.size == (800, 602))

print("img_cut1... " + fname)

crop = img.crop((1, offset, width+1, offset + height))

base, ext = os.path.splitext(fname)
crop.save(base + ".png")

# crop.show()
# img.show()
