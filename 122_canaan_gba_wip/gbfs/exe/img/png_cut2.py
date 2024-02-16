# coding: Shift_JIS
# waku06bをGBA背景用にします

import os
import sys
import struct
from PIL import Image

file = "waku06b.png"
print("png_cut2... " + file)

p = Image.open(file)
p.crop((0, 0, 240, 160)).save(file)
p.close()
