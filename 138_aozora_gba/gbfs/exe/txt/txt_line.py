# coding: Shift_JIS
import sys
import re

# ---------------------------------------------------------------------------
# 禁則文字処理
def kinsoku(input):
	ret = []
	buf = ""

	for line in input:

		# 行頭全角？
		if re.search(r'^[^\x01-\x7E]', line):
			buf += line.strip()
		else:
			if buf:
				ret.extend(kinsoku_sub(buf))
				buf = ""

			ret.append(line)

	if buf:
		ret.extend(kinsoku_sub(buf))

	return ret
# ---------------------------------------------------------------------------
def kinsoku_sub(buf, line_length=17):
	# 行頭禁則
	line_start_prohibition = (
	"、。，．・？！゛゜ー―‐／）］｝〉》」』】〕"
	"ぁぃぅぇぉっゃゅょゎァィゥェォッャュョヮヵヶ"
	"°′″"
	)
	# 行末禁則
	line_end_prohibition = (
	"（［｛〈《「『【〔"
	)

	ret = []
	str = buf

	while len(str) > 0:

		if len(str) <= line_length:
			ret.append(str)
			break

		split_pos = line_length

		# 行末チェック（行の末尾が該当文字の場合、その文字を次の行へ送り出す）
		while split_pos > 0 and str[split_pos - 1] in line_end_prohibition:
			split_pos -= 1

		# 行頭チェック（行の先頭が該当文字の場合、行の末尾を次の行へ送り出す）
		if split_pos < len(str):
			while split_pos > 0 and str[split_pos] in line_start_prohibition:
				split_pos -= 1

		# セーフティ（禁則文字が続きすぎて1行が空になる場合）
		if split_pos == 0:
			split_pos = line_length

		ret.append(str[:split_pos])
		str = str[split_pos:]

	return ret
# ---------------------------------------------------------------------------
# 最大行に合わせて改ページ命令を印字
def page_break(input, max_lines=6):
	ret = []
	cnt = 0
	max = max_lines

	for i, line in enumerate(input):
		ret.append(line)

		if re.search(r'^MES', line):
			if re.search(r'^MES 0', line):
				# システムメッセージ最大行
				max = max_lines
			else:
				# キャラのセリフは１行少ない
				max = max_lines - 1

		# 行頭全角？
		if re.search(r'^[^\x01-\x7E]', line):
			cnt += 1

			if cnt == max:
				if (i + 1) < len(input) and re.search(r'^[^\x01-\x7E]', input[i + 1]):
					ret.append('MLF')
					cnt = 0
		else:
			cnt = 0

	return ret
# ---------------------------------------------------------------------------
# IF文の条件式を逆ポーランドに変更
def rpn(input):
	pre = {
		'!': 4,
		'>': 3, '<': 3, '=': 3, '@': 3,		# @ not equal
		'&': 2,
		'|': 1,
	}
	ret = []

	for line in input:
		if not re.search(r'^IF0', line):
			ret.append(line)
			continue

		out = []
		stack = []
		tokens = re.findall(r'[a-zA-Z0-9]+|!|[><=@&|]+', line)

		for token in tokens:
			if re.match(r'[a-zA-Z0-9]+', token):
				out.append(token)
			else:
				while (stack and pre.get(token, 0) <= pre.get(stack[-1], 0)):
					out.append(stack.pop())

				stack.append(token)

		while stack:
			out.append(stack.pop())

		# パラメータ数を挿入
		out.insert(1, str(len(out) - 1))
		ret.append(" ".join(out))

	return ret
# ---------------------------------------------------------------------------
file = sys.argv[1]

print("txt_line... " + file)

f = open(file, 'r')
data = f.read()
f.close()


data = data.splitlines()

data = kinsoku(data)
data = page_break(data)
data = rpn(data)
data = "\n".join(data) + "\n"


f = open(file, "w")
f.write(data)
f.close()
