# coding: Shift_JIS
# メッセージにユニーク番号を付与
import os
import sys
import glob
import re

def func(match):
	global bit, idx

	num = match.group(1)
	ret = f"{word} {num} {idx} {bit}"

	bit += 1
	if bit == 8:
		bit = 0
		idx += 1

	return ret


word = "MES"
list = glob.glob(os.path.join("*.txt"))

idx = 1		# idxの0番地は空（ブランク）書き込み用
bit = 0

for fname in list:
	new = []

	print(f"txt_mes... {fname}")

	with open(fname, "r") as f:
		lines = f.readlines()

	for line in lines:
		tmp = re.sub(r'\b' + word + r"\b (\d+)\b", func, line)
		new.append(tmp)

	with open(fname, "w") as f:
		f.writelines(new)


# print(f"done! idx:{idx} bit:{bit}")
# 
# 調査済み　idx:2979 bit:5
# 2979 + 1 = 2980 Byte
