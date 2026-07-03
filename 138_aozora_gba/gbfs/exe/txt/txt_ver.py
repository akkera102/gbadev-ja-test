# coding: Shift_JIS
# 初回版をメモリアル版にアップデートします。既にメモリアル版だった場合、変更はありません
import re
import sys


fname = sys.argv[1]

print("txt_ver... " + fname)

f = open(fname, 'r')
txt = f.read()
f.close()

if(fname == 'SC00.txt'):
	txt = re.sub(r'明日菜ちゃんは誰よりも遙かに', r'明日菜ちゃんは誰よりもずっと', txt)
	txt = re.sub(r'それが俺にできる唯一のことだったから', r'それが俺に出来る唯一の事だったから', txt)
	txt = re.sub(r'景色が色あせていくと共に', r'景色が色褪せていくと共に', txt)

if(fname == 'SC01.txt'):
	txt = re.sub(r'双子の姉妹のうち一人', r'双子の姉妹の一人、　', txt)
	txt = re.sub(r'\n\n\/\*▽俺もそう思うよ', r'\n/*CHK TONO dd\n/*▽俺もそう思うよ', txt)

if(fname == 'SC05.txt'):
	txt = re.sub(r'ここで彼女を抱いた時だった', r'ここだった', txt)
	txt = re.sub(r'藍ちゃんと文乃ちゃんは自分から身体を起こして、　', r'藍ちゃんと明日菜ちゃんは自分から身体を起こして、', txt)

f = open(fname, "w")
f.write(txt)
f.close()
