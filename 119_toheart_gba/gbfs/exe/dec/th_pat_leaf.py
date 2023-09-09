# coding: Shift_JIS
# ホワイト画像を作成して中央にロゴ表示

import os
import sys
from PIL import Image


file = "LEAF.BMP"

print ("patching " + file)

img1 = Image.open(file)
img2 = Image.new("RGB", (640, 480), (255, 255, 255))
iw1, ih1 = img1.size
iw2, ih2 = img2.size


img2.paste(img1, (int(iw2/2 - iw1/2), int(ih2/2 - ih1/2)))

img1.close()
img2.save("LEAF.BMP")

