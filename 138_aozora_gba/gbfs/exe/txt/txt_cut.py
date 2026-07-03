# coding: Shift_JIS
# スクリプトファイルをラベル単位で切り出し。コメント、全角空白などを削除
import re
import sys


fname = sys.argv[1]

print("txt_cut... " + fname)

with open(fname, "r") as f:
	lines = f.readlines()

blk = []
cur = ""

for line in lines:
	line = re.sub(r"\s*//\*.*$", "", line)
	line = re.sub(r"\s*/\*.*$", "", line)
	line = re.sub(r"\s*//*.*$", "", line)
	line = re.sub(r"@LF", "", line)
	line = re.sub(r"^\n", "", line)
	line = re.sub(r"　", "", line)

	if line.startswith("SC"):
		if cur != "":
			blk.append(cur)
		cur = line
	else:
		cur += line

blk.append(cur)


for i, sc in enumerate(blk):
	with open(f"tmp{fname[3]}{i:03d}.txt", "w") as out:
		out.write(sc)
