# coding: cp932
# スクリプトログを正規表現にて置換
import sys
import os
import re


# ---------------------------------------------------------------------------
if len(sys.argv) < 3:
	print("Usage: {} input.log output.txt".format(sys.argv[0]))
	sys.exit(1)

print("log2txt... " + os.path.basename(sys.argv[1]))

with open(sys.argv[1], "r", encoding='cp932') as f:
	txt = f.read()


# ---------------------------------------------------------------------------
# 拡張子
txt = re.sub('\\.g', '', txt)
txt = re.sub('\\.s', '', txt)

# 不要ウェイト
txt = re.sub('WAT 0\n', '', txt)
# 演奏重複コマンド
txt = re.sub('BST\nBST\n', 'BST\n', txt)
# 効果音再生時の不要コマンド
txt = re.sub('MSG \n', '', txt)


# ---------------------------------------------------------------------------
# エフェクト

# 何もしない
txt = re.sub('PFA 0 1\nIMG bk0\nPBW 0 3\n', '', txt)
txt = re.sub('IMG bk0\n', '', txt)
# ブラックイン
txt = re.sub('PFA 0 3\nPFA 0 3\n', 'EFF 1 3\n', txt)
txt = re.sub('PFA 0', 'EFF 1', txt)
# ブラックアウト
txt = re.sub('PBW 0', 'EFF 2', txt)
# ホワイトイン
txt = re.sub('PFA 1', 'EFF 3', txt)
# ホワイトアウト
txt = re.sub('PBW 1', 'EFF 4', txt)
# 黒に塗りつぶし
txt = re.sub('DRW 0', 'EFF 5 0', txt)
# ざらざら黒エフェクト
txt = re.sub('DRW 1', 'EFF 6 0', txt)
# キャラ消去
txt = re.sub('DLC', 'EFF 7 0', txt)


# ---------------------------------------------------------------------------
# 差分背景
txt = re.sub('IMG 003\nIMG 03n\n', 'BGL 03n\n', txt)
txt = re.sub('IMG 006\nIMG 06n\n', 'BGL 06n\n', txt)
txt = re.sub('IMG 07a\nIMG 07b\n', 'BGL 07b\n', txt)
txt = re.sub('IMG 008\nIMG 08n\n', 'BGL 08n\n', txt)
txt = re.sub('IMG 10a\nIMG 10b\n', 'BGL 10b\n', txt)
txt = re.sub('IMG 012\nIMG 12b\n', 'BGL 12b\n', txt)

# 背景
txt = re.sub('IMG ttl', 'BGL ttl', txt)
txt = re.sub('IMG 001', 'BGL 001', txt)
txt = re.sub('IMG 002', 'BGL 002', txt)
txt = re.sub('IMG 003', 'BGL 003', txt)
txt = re.sub('IMG 004', 'BGL 004', txt)
txt = re.sub('IMG 005', 'BGL 005', txt)
txt = re.sub('IMG 05b', 'BGL 05b', txt)
txt = re.sub('IMG 006', 'BGL 006', txt)
txt = re.sub('IMG 07a', 'BGL 07a', txt)
txt = re.sub('IMG 008', 'BGL 008', txt)
txt = re.sub('IMG 009', 'BGL 009', txt)
txt = re.sub('IMG 10a', 'BGL 10a', txt)
txt = re.sub('IMG 011', 'BGL 011', txt)
txt = re.sub('IMG 012', 'BGL 012', txt)
txt = re.sub('IMG 013', 'BGL 013', txt)
txt = re.sub('IMG 014', 'BGL 014', txt)
txt = re.sub('IMG 015', 'BGL 015', txt)
txt = re.sub('IMG 048', 'BGL 048', txt)
txt = re.sub('IMG 48n', 'BGL 48n', txt)
txt = re.sub('IMG 049', 'BGL 049', txt)
txt = re.sub('IMG 089', 'BGL 089', txt)

# 不明背景
txt = re.sub('IMG 02n\n', '', txt)
txt = re.sub('IMG 04n\n', '', txt)
txt = re.sub('IMG 05n\n', '', txt)
txt = re.sub('IMG 07n\n', '', txt)
txt = re.sub('IMG 09n\n', '', txt)
txt = re.sub('IMG 10n\n', '', txt)
txt = re.sub('IMG 11n\n', '', txt)
txt = re.sub('IMG 12n\n', '', txt)
txt = re.sub('IMG 13n\n', '', txt)
txt = re.sub('IMG 14n\n', '', txt)
txt = re.sub('IMG 15n\n', '', txt)
txt = re.sub('IMG 49n\n', '', txt)

# 7_40 鬼消滅エフェクト
txt = re.sub('IMG write\n', 'SET write 1\nEFF 34 0\nEFF 7 0\nWAT 120\n', txt)


# ---------------------------------------------------------------------------
# キャラクタ

# 亜璃沙
txt = re.sub('IMG 2a1\nIMG 2c1\n', 'CHR 2c1\n', txt)
txt = re.sub('IMG 2a2\nIMG 2c2\n', 'CHR 2c2\n', txt)
txt = re.sub('IMG 2a1\nIMG 2d1\n', 'CHR 2d1\n', txt)
txt = re.sub('IMG 2a2\nIMG 2d2\n', 'CHR 2d2\n', txt)
txt = re.sub('IMG 2a1', 'CHR 2a1', txt)
txt = re.sub('IMG 2a2', 'CHR 2a2', txt)
txt = re.sub('IMG 2b1', 'CHR 2b1', txt)
txt = re.sub('IMG 2b2', 'CHR 2b2', txt)

# 深紗緒
txt = re.sub('IMG 7a2\nIMG 7b2\n', 'CHR 7b2\n', txt)
txt = re.sub('IMG 7a2\nIMG 7c2\n', 'CHR 7c2\n', txt)
txt = re.sub('IMG 7a2', 'CHR 7a2', txt)
txt = re.sub('IMG 7d2', 'CHR 7d2', txt)
txt = re.sub('IMG 7e2', 'CHR 7e2', txt)

# 雪菜
txt = re.sub('IMG 16a\nIMG 16b\n', 'CHR 16b\n', txt)
txt = re.sub('IMG 16c\nIMG 6c2\n', 'CHR 6c2\n', txt)
txt = re.sub('IMG 16d\nIMG 6d2\n', 'CHR 6d2\n', txt)
txt = re.sub('IMG 16a', 'CHR 16a', txt)
txt = re.sub('IMG 16c', 'CHR 16c', txt)
txt = re.sub('IMG 16d', 'CHR 16d', txt)

# 摩耶
txt = re.sub('IMG 25a\nIMG 25b\n', 'CHR 25b\n', txt)
txt = re.sub('IMG 25a\nIMG 25c\n', 'CHR 25c\n', txt)
txt = re.sub('IMG 25a\nIMG 25e\n', 'CHR 25e\n', txt)
txt = re.sub('IMG 25a\nIMG 25g\n', 'CHR 25g\n', txt)
txt = re.sub('IMG 25a', 'CHR 25a', txt)
txt = re.sub('IMG 25d', 'CHR 25d', txt)
txt = re.sub('IMG 25f', 'CHR 25f', txt)
txt = re.sub('IMG 25h', 'CHR 25h', txt)

# 深紗緒
txt = re.sub('IMG 37a\nIMG 37b\n', 'CHR 37b\n', txt)
txt = re.sub('IMG 37a\nIMG 37c\n', 'CHR 37c\n', txt)
txt = re.sub('IMG 37a', 'CHR 37a', txt)
txt = re.sub('IMG 37d', 'CHR 37d', txt)
txt = re.sub('IMG 37e', 'CHR 37e', txt)
txt = re.sub('IMG 039', 'CHR 039', txt)

# 女主人
txt = re.sub('IMG 43a\nIMG 43b\n', 'CHR 43b\n', txt)
txt = re.sub('IMG 43a\nIMG 43c\n', 'CHR 43c\n', txt)
txt = re.sub('IMG 43d\nIMG 43e\n', 'CHR 43e\n', txt)
txt = re.sub('IMG 43a', 'CHR 43a', txt)
txt = re.sub('IMG 43d', 'CHR 43d', txt)

# 由羅
txt = re.sub('IMG 52a\nIMG 52b\n', 'CHR 52b\n', txt)
txt = re.sub('IMG 52a\nIMG 52c\n', 'CHR 52c\n', txt)
txt = re.sub('IMG 52a\nIMG 52d\n', 'CHR 52d\n', txt)
txt = re.sub('IMG 52a\nIMG 52e\n', 'CHR 52e\n', txt)
txt = re.sub('IMG 52a', 'CHR 52a', txt)

# 沙里
txt = re.sub('IMG 58a\nIMG 58b\n', 'CHR 58b\n', txt)
txt = re.sub('IMG 58a', 'CHR 58a', txt)
txt = re.sub('IMG 58c', 'CHR 58c', txt)

# 美和子
txt = re.sub('IMG 64b\nIMG 4bd\n', 'CHR 4bd\n', txt) # 赤面差分
txt = re.sub('IMG 64a', 'CHR 64a', txt)
txt = re.sub('IMG 64b', 'CHR 64b', txt)
txt = re.sub('IMG 64c', 'CHR 64c', txt)

# 犬
txt = re.sub('IMG 083', 'CHR 083', txt)

# 赤ずきん
txt = re.sub('IMG 84a\nIMG 84b\n', 'CHR 84b\n', txt)
txt = re.sub('IMG 84a\nIMG 84d\n', 'CHR 84d\n', txt)
txt = re.sub('IMG 84a', 'CHR 84a', txt)
txt = re.sub('IMG 84c', 'CHR 84c', txt)

# 草山
txt = re.sub('IMG 90z\nIMG 90a\n', 'CHR 90a\n', txt)
txt = re.sub('IMG 90z\nIMG 90b\n', 'CHR 90b\n', txt)
txt = re.sub('IMG 90z\nIMG 90c\n', 'CHR 90c\n', txt)
txt = re.sub('IMG 90z\nIMG 90d\n', 'CHR 90d\n', txt)
txt = re.sub('IMG 90e', 'CHR 90e', txt)


# ---------------------------------------------------------------------------
# Hシーン、イベントシーン
txt = re.sub('IMG 17a', 'HSC 17a', txt)
txt = re.sub('IMG 17b', 'HSC 17b', txt)
txt = re.sub('IMG 17c', 'HSC 17c', txt)
txt = re.sub('IMG 018', 'HSC 018', txt)
txt = re.sub('IMG 019', 'HSC 019', txt)
txt = re.sub('IMG 020', 'HSC 020', txt)
txt = re.sub('IMG 021', 'HSC 021', txt)
txt = re.sub('IMG 022', 'HSC 022', txt)
txt = re.sub('IMG 023', 'HSC 023', txt)
txt = re.sub('IMG 024', 'HSC 024', txt)
txt = re.sub('IMG 026', 'HSC 026', txt)
txt = re.sub('IMG 027', 'HSC 027', txt)
txt = re.sub('IMG 028', 'HSC 028', txt)
txt = re.sub('IMG 029', 'HSC 029', txt)
txt = re.sub('IMG 30a', 'HSC 30a', txt)
txt = re.sub('IMG 30b', 'HSC 30b', txt)
txt = re.sub('IMG 30c', 'HSC 30c', txt)
txt = re.sub('IMG 30d', 'HSC 30d', txt)
txt = re.sub('IMG 031', 'HSC 031', txt)
txt = re.sub('IMG 032', 'HSC 032', txt)
txt = re.sub('IMG 033', 'HSC 033', txt)
txt = re.sub('IMG 034', 'HSC 034', txt)
txt = re.sub('IMG 035', 'HSC 035', txt)
txt = re.sub('IMG 036', 'HSC 036', txt)
txt = re.sub('IMG 038', 'HSC 038', txt)
txt = re.sub('IMG 040', 'HSC 040', txt)
txt = re.sub('IMG 041', 'HSC 041', txt)
txt = re.sub('IMG 042', 'HSC 042', txt)
txt = re.sub('IMG 044', 'HSC 044', txt)
txt = re.sub('IMG 045', 'HSC 045', txt)
txt = re.sub('IMG 046', 'HSC 046', txt)
txt = re.sub('IMG 047', 'HSC 047', txt)
txt = re.sub('IMG 050', 'HSC 050', txt)
txt = re.sub('IMG 051', 'HSC 051', txt)
txt = re.sub('IMG 053', 'HSC 053', txt)
txt = re.sub('IMG 54a\nIMG 54b', 'HSC 54b', txt)
txt = re.sub('IMG 54a', 'HSC 54a', txt)
txt = re.sub('IMG 055', 'HSC 055', txt)
txt = re.sub('IMG 056', 'HSC 056', txt)
txt = re.sub('IMG 057', 'HSC 057', txt)
txt = re.sub('IMG 059', 'HSC 059', txt)
txt = re.sub('IMG 60a', 'HSC 60a', txt)
txt = re.sub('IMG 60b', 'HSC 60b', txt)
txt = re.sub('IMG 60c', 'HSC 60c', txt)
txt = re.sub('IMG 061', 'HSC 061', txt)
txt = re.sub('IMG 062', 'HSC 062', txt)
txt = re.sub('IMG 063', 'HSC 063', txt)
txt = re.sub('IMG 065', 'HSC 065', txt)
txt = re.sub('IMG 066', 'HSC 066', txt)
txt = re.sub('IMG 67a', 'HSC 67a', txt)
txt = re.sub('IMG 67b', 'HSC 67b', txt)
txt = re.sub('IMG 67c', 'HSC 67c', txt)
txt = re.sub('IMG 068', 'HSC 068', txt)
txt = re.sub('IMG 069', 'HSC 069', txt)
txt = re.sub('IMG 070', 'HSC 070', txt)
txt = re.sub('IMG 071', 'HSC 071', txt)
txt = re.sub('IMG 073', 'HSC 073', txt)
txt = re.sub('IMG 074', 'HSC 074', txt)
txt = re.sub('IMG 075', 'HSC 075', txt)
txt = re.sub('IMG 076', 'HSC 076', txt)
txt = re.sub('IMG 077', 'HSC 077', txt)
txt = re.sub('IMG 078', 'HSC 078', txt)
txt = re.sub('IMG 79a', 'HSC 79a', txt)
txt = re.sub('IMG 79b\n', 'SET 79b 1\nEFF 7 0\n', txt)
txt = re.sub('IMG 79c\n', 'SET 79c 1\nEFF 7 0\n', txt)
txt = re.sub('IMG 79d\n', 'SET 79d 1\nEFF 7 0\n', txt)
txt = re.sub('IMG 080', 'HSC 080', txt)
txt = re.sub('IMG 081', 'HSC 081', txt)
txt = re.sub('IMG 082', 'HSC 082', txt)
txt = re.sub('IMG 085', 'HSC 085', txt)
txt = re.sub('IMG 86a', 'HSC 86a', txt)
txt = re.sub('IMG 86b', 'HSC 86b', txt)
txt = re.sub('IMG 86c', 'HSC 86c', txt)
txt = re.sub('IMG 86d', 'HSC 86d', txt)
txt = re.sub('IMG 087', 'HSC 087', txt)
txt = re.sub('IMG 088', 'HSC 088', txt)
txt = re.sub('IMG 091', 'HSC 091', txt)
txt = re.sub('IMG 092', 'HSC 092', txt)
txt = re.sub('IMG 093', 'HSC 093', txt)
txt = re.sub('IMG 095', 'HSC 095', txt)
txt = re.sub('IMG 097', 'HSC 097', txt)
txt = re.sub('IMG 97b', 'HSC 97b', txt)
txt = re.sub('IMG 098', 'HSC 098', txt)
txt = re.sub('IMG 099', 'HSC 099', txt)
txt = re.sub('IMG 100', 'HSC 100', txt)
txt = re.sub('IMG 101', 'HSC 101', txt)
txt = re.sub('IMG mu058d', 'HSC mu058d', txt)
txt = re.sub('IMG mu094a', 'HSC mu094a', txt)
txt = re.sub('IMG mu094b', 'HSC mu094b', txt)


# ---------------------------------------------------------------------------
# ジャンプ命令変更

txt = re.sub('SEL 移動\n', '', txt)

if(sys.argv[1] == "0_00.log"): txt = re.sub('LDS 1_00\n', 'LDS 1 0\n', txt)
if(sys.argv[1] == "1_00.log"): txt = re.sub('LDS 1_01\n', 'LDS 1 1\n', txt)
if(sys.argv[1] == "1_01.log"): txt = re.sub('LDS 1_02\n', 'LDS 1 2\n', txt)
if(sys.argv[1] == "1_02.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 27 0\nLDS 1 26\n', txt)
if(sys.argv[1] == "1_26.log"): txt = re.sub('LDS 1_25\n', 'MAP 20 1\nLDS 1 3\n', txt)
if(sys.argv[1] == "1_03.log"): txt = re.sub('LDS 1_04\n', 'MAP 26 0\nLDS 1 24\n', txt)
if(sys.argv[1] == "1_24.log"): txt = re.sub('LDS 1_23\n', 'MAP 11 1\nLDS 1 13\n', txt)
if(sys.argv[1] == "1_13.log"): txt = re.sub('LDS 1_14\n', 'MAP 12 0\nLDS 1 19\n', txt)
if(sys.argv[1] == "1_19.log"): txt = re.sub('LDS ss\n', 'LDS 1 18\n', txt)
if(sys.argv[1] == "1_18.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 0 0\nLDS 1 33\n', txt)
if(sys.argv[1] == "1_33.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 3 0\nLDS 1 28\n', txt)
if(sys.argv[1] == "1_28.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 4 0\nLDS 1 29\n', txt)
if(sys.argv[1] == "1_29.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 5 0\nLDS 1 30\n', txt)
if(sys.argv[1] == "1_30.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 13 1\nLDS 1 17\n', txt)
if(sys.argv[1] == "1_17.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 14 0\nLDS 1 27\n', txt)
if(sys.argv[1] == "1_27.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 22 1\nLDS 1 6\n', txt)
if(sys.argv[1] == "1_06.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 24 1\nLDS 1 7\n', txt)
if(sys.argv[1] == "1_07.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 17 1\nLDS 1 5\n', txt)
if(sys.argv[1] == "1_05.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 16 1\nLDS 1 10\n', txt)
if(sys.argv[1] == "1_10.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 25 0\nLDS 1 12\n', txt)
if(sys.argv[1] == "1_12.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 27 0\nLDS 1 34\n', txt)
if(sys.argv[1] == "1_34.log"): txt = re.sub('LDS 1_35\n', 'LDS 1 35\n', txt)
if(sys.argv[1] == "1_35.log"): txt = re.sub('LDS 1_36\n', 'LDS 1 36\n', txt)
if(sys.argv[1] == "1_36.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 27 0\nLDS 1 58\n', txt)
if(sys.argv[1] == "1_58.log"): txt = re.sub('LDS 1_57\n', 'MAP 9 1\nLDS 1 49\n', txt)
if(sys.argv[1] == "1_49.log"): txt = re.sub('LDS 1_48\n', 'MAP 7 1\nLDS 1 54\n', txt)
if(sys.argv[1] == "1_54.log"): txt = re.sub('LDS 1_56\n', 'MAP 3 0\nLDS 1 61\n', txt)
if(sys.argv[1] == "1_61.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 1 0\nLDS 1 64\n', txt)
if(sys.argv[1] == "1_64.log"): txt = re.sub('MAP\nLDS ss\n', 'MAP 19 0\nLDS 1 66\n', txt)
if(sys.argv[1] == "1_66.log"): txt = re.sub('LDS 2_00\n', 'LDS 2 0\n', txt)

if(sys.argv[1] == "2_00.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 8 1\nLDS 2 20\n', txt)
if(sys.argv[1] == "2_20.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 26 0\nLDS 2 24\n', txt)
if(sys.argv[1] == "2_24.log"): txt = re.sub('MAP\nEFF 6 0\nLDS ss2\n', 'MAP 13 0\nLDS 2 18\n', txt)
if(sys.argv[1] == "2_18.log"): txt = re.sub('LDS 2_23\n', 'BGL 049\nMAP 12 0\nLDS 2 1\n', txt)
if(sys.argv[1] == "2_01.log"): txt = re.sub('LDS ss2\n', 'MAP 0 0\nLDS 2 33\n', txt)
if(sys.argv[1] == "2_33.log"): txt = re.sub('LDS 2_32\n', 'BGL 002\nMAP 5 0\nLDS 2 29\n', txt)
if(sys.argv[1] == "2_29.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 0 0\nLDS 2 34\n', txt)
if(sys.argv[1] == "2_34.log"): txt = re.sub('LDS 2_32\n', 'MAP 12 0\nLDS 2 2\n', txt)
if(sys.argv[1] == "2_02.log"): txt = re.sub('LDS ss2\n', 'MAP 5 0\nLDS 2 3\n', txt)
if(sys.argv[1] == "2_03.log"): txt = re.sub('LDS ss2\n', 'LDS 2 30\n', txt)
if(sys.argv[1] == "2_30.log"): txt = re.sub('LDS 2_29\n', 'MAP 24 0\nLDS 2 8\n', txt)
if(sys.argv[1] == "2_08.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 1 0\nLDS 2 31\n', txt)
if(sys.argv[1] == "2_31.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 3 0\nLDS 2 27\n', txt)
if(sys.argv[1] == "2_27.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 4 0\nLDS 2 28\n', txt)
if(sys.argv[1] == "2_28.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 12 0\nLDS 2 35\n', txt)
if(sys.argv[1] == "2_35.log"): txt = re.sub('MAP\nLDS ss2\n', 'LDS 2 55\n', txt)
if(sys.argv[1] == "2_55.log"): txt = re.sub('LDS 2_59\n', 'BGL 049\nMAP 18 0\nLDS 2 41\n', txt)
if(sys.argv[1] == "2_41.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 15 1\nLDS 2 46\n', txt)
if(sys.argv[1] == "2_46.log"): txt = re.sub('LDS 2_60\n', 'MAP 27 0\nLDS 2 61\n', txt)
if(sys.argv[1] == "2_61.log"): txt = re.sub('LDS 2_60\n', 'BGL 049\nMAP 3 0\nLDS 2 64\n', txt)
if(sys.argv[1] == "2_64.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 1 0\nLDS 2 68\n', txt)
if(sys.argv[1] == "2_68.log"): txt = re.sub('MAP\nLDS ss2\n', 'MAP 0 0\nLDS 2 71\n', txt)
if(sys.argv[1] == "2_71.log"): txt = re.sub('LDS 2_70\n', 'MAP 14 0\nLDS 2 62\n', txt)
if(sys.argv[1] == "2_62.log"): txt = re.sub('LDS 2_63\n', 'MAP 19 0\nLDS 3 0\n', txt)

if(sys.argv[1] == "3_00.log"): txt = re.sub('LDS u123\n', 'BGL 003\nMAP 0 0\nLDS 3 1\n', txt)
if(sys.argv[1] == "3_01.log"): txt = re.sub('LDS 3_02\n', 'LDS 3 2\n', txt)
if(sys.argv[1] == "3_02.log"): txt = re.sub('LDS 3_03\n', 'LDS 3 3\n', txt)
if(sys.argv[1] == "3_03.log"): txt = re.sub('LDS u200\n', 'BGL 011\nMAP 24 0\nLDS 3 4\n', txt)
if(sys.argv[1] == "3_04.log"): txt = re.sub('MAP\nLDS ss3\n', 'MAP 27 0\nLDS 3 5\n', txt)
if(sys.argv[1] == "3_05.log"): txt = re.sub('LDS n219\n', 'BGL 049\nMAP 12 0\nLDS 3 6\n', txt)
if(sys.argv[1] == "3_06.log"): txt = re.sub('LDS 3_07\n', 'LDS 3 7\n', txt)
if(sys.argv[1] == "3_07.log"): txt = re.sub('LDS u318\n', 'BGL 049\nMAP 13 0\nLDS 3 8\n', txt)
if(sys.argv[1] == "3_08.log"): txt = re.sub('LDS 3_09\n', 'LDS 3 9\n', txt)
if(sys.argv[1] == "3_09.log"): txt = re.sub('LDS 3_10\n', 'LDS 3 10\n', txt)
if(sys.argv[1] == "3_10.log"): txt = re.sub('LDS 4_00\n', 'LDS 4 0\n', txt)

if(sys.argv[1] == "4_00.log"): txt = re.sub('MAP\nLDS ss4\n', 'MAP 4 0\nLDS 4 24\n', txt)
if(sys.argv[1] == "4_24.log"): txt = re.sub('LDS 4_23\n', 'BGL 006\nMAP 13 0\nLDS 4 14\n', txt)
if(sys.argv[1] == "4_14.log"): txt = re.sub('MAP\nLDS ss4\n', 'MAP 5 0\nLDS 4 26\n', txt)
if(sys.argv[1] == "4_26.log"): txt = re.sub('LDS 4_25\n', 'MAP 1 0\nLDS 4 29\n', txt)
if(sys.argv[1] == "4_29.log"): txt = re.sub('LDS 4_30\n', 'LDS 4 30\n', txt)
if(sys.argv[1] == "4_30.log"): txt = re.sub('LDS 4_31\n', 'LDS 4 31\n', txt)
if(sys.argv[1] == "4_31.log"): txt = re.sub('LDS 4_32\n', 'LDS 4 32\n', txt)
if(sys.argv[1] == "4_32.log"): txt = re.sub('LDS 5_00\n', 'LDS 5 0\n', txt)

if(sys.argv[1] == "5_00.log"): txt = re.sub('LDS 5_01\n', 'LDS 5 1\n', txt)
if(sys.argv[1] == "5_01.log"): txt = re.sub('MAP\nLDS ss5\n', 'MAP 12 0\nLDS 5 16\n', txt)
if(sys.argv[1] == "5_16.log"): txt = re.sub('MAP\nLDS ss5\n', 'MAP 5 0\nLDS 5 28\n', txt)
if(sys.argv[1] == "5_28.log"): txt = re.sub('LDS 5_27\n', 'MAP 4 0\nLDS 5 26\n', txt)
if(sys.argv[1] == "5_26.log"): txt = re.sub('MAP\nLDS ss5\n', 'MAP 0 0\nLDS 5 31\n', txt)
if(sys.argv[1] == "5_31.log"): txt = re.sub('LDS 5_30\n', 'BGL 002\nMAP 14 0\nLDS 5 23\n', txt)
if(sys.argv[1] == "5_23.log"): txt = re.sub('LDS 5_32\n', 'LDS 5 32\n', txt)
if(sys.argv[1] == "5_32.log"): txt = re.sub('MAP\n', 'MAP 26 0\n', txt)
if(sys.argv[1] == "5_32.log"): txt = re.sub('LDS 5_33\n', 'LDS 5 33\n', txt)
if(sys.argv[1] == "5_33.log"): txt = re.sub('LDS 5_34\n', 'LDS 5 34\n', txt)
if(sys.argv[1] == "5_34.log"): txt = re.sub('LDS 5_35\n', 'LDS 5 35\n', txt)
if(sys.argv[1] == "5_35.log"): txt = re.sub('LDS 5_36\n', 'LDS 5 36\n', txt)
if(sys.argv[1] == "5_36.log"): txt = re.sub('LDS 5_37\n', 'LDS 5 37\n', txt)
if(sys.argv[1] == "5_37.log"): txt = re.sub('LDS 5_38\n', 'LDS 5 38\n', txt)
if(sys.argv[1] == "5_38.log"): txt = re.sub('MAP\nLDS ss5\n', 'MAP 13 0\nLDS 5 62\n', txt)
if(sys.argv[1] == "5_62.log"): txt = re.sub('LDS 5_63\n', 'LDS 5 63\n', txt)
if(sys.argv[1] == "5_63.log"): txt = re.sub('LDS 5_64\n', 'LDS 5 64\n', txt)
if(sys.argv[1] == "5_64.log"): txt = re.sub('LDS 5_65\n', 'LDS 5 65\n', txt)
if(sys.argv[1] == "5_65.log"): txt = re.sub('LDS 5_66\n', 'LDS 5 66\n', txt)
if(sys.argv[1] == "5_66.log"): txt = re.sub('LDS 6_00\n', 'LDS 6 0\n', txt)

if(sys.argv[1] == "6_00.log"): txt = re.sub('LDS u400\n', 'BGL 011\nMAP 24 0\nLDS 6 1\n', txt)
if(sys.argv[1] == "6_01.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 24 0\nLDS 6 2\n', txt)
if(sys.argv[1] == "6_02.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 5 0\nLDS 6 3\n', txt)
if(sys.argv[1] == "6_03.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 5 0\nLDS 6 4\n', txt)
if(sys.argv[1] == "6_04.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 5 0\nLDS 6 5\n', txt)
if(sys.argv[1] == "6_05.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 0 0\nLDS 6 6\n', txt)
if(sys.argv[1] == "6_06.log"): txt = re.sub('LDS 6_30\n', 'MAP 3 0\nLDS 6 26\n', txt)
if(sys.argv[1] == "6_26.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 4 0\nLDS 6 27\n', txt)
if(sys.argv[1] == "6_27.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 5 0\nLDS 6 28\n', txt)
if(sys.argv[1] == "6_28.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 0 0\nLDS 6 30\n', txt)
if(sys.argv[1] == "6_30.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 1 0\nLDS 6 29\n', txt)
if(sys.argv[1] == "6_29.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 25 0\nLDS 6 16\n', txt)
if(sys.argv[1] == "6_16.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 18 0\nLDS 6 12\n', txt)
if(sys.argv[1] == "6_12.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 17 0\nLDS 6 13\n', txt)
if(sys.argv[1] == "6_13.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 16 0\nLDS 6 14\n', txt)
if(sys.argv[1] == "6_14.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 15 0\nLDS 6 15\n', txt)
if(sys.argv[1] == "6_15.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 24 0\nLDS 6 11\n', txt)
if(sys.argv[1] == "6_11.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 14 0\nLDS 6 25\n', txt)
if(sys.argv[1] == "6_25.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 13 0\nLDS 6 20\n', txt)
if(sys.argv[1] == "6_20.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 12 0\nLDS 6 21\n', txt)
if(sys.argv[1] == "6_21.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 11 0\nLDS 6 17\n', txt)
if(sys.argv[1] == "6_17.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 9 0\nLDS 6 19\n', txt)
if(sys.argv[1] == "6_19.log"): txt = re.sub('MAP\nLDS ss6\n', 'MAP 26 0\nLDS 6 31\n', txt)
if(sys.argv[1] == "6_31.log"): txt = re.sub('LDS 6_32\n', 'LDS 6 32\n', txt)
if(sys.argv[1] == "6_32.log"): txt = re.sub('LDS 6_33\n', 'LDS 6 33\n', txt)
if(sys.argv[1] == "6_33.log"): txt = re.sub('LDS 6_34\n', 'LDS 6 34\n', txt)
if(sys.argv[1] == "6_34.log"): txt = re.sub('LDS 6_35\n', 'LDS 6 35\n', txt)
if(sys.argv[1] == "6_35.log"): txt = re.sub('LDS 7_00\n', 'LDS 7 0\n', txt)

if(sys.argv[1] == "7_00.log"): txt = re.sub('LDS u500\n', 'BGL 011\nMAP 18 0\nLDS 7 2\n', txt)
if(sys.argv[1] == "7_02.log"): txt = re.sub('MAP\nLDS ss7\n', 'MAP 5 0\nLDS 7 1\n', txt)
if(sys.argv[1] == "7_01.log"): txt = re.sub('LDS u521\n', 'MAP 0 0\nLDS 7 3\n', txt)
if(sys.argv[1] == "7_03.log"): txt = re.sub('LDS 7_04\n', 'LDS 7 4\n', txt)
if(sys.argv[1] == "7_04.log"): txt = re.sub('LDS 7_05\n', 'LDS 7 5\n', txt)
if(sys.argv[1] == "7_05.log"): txt = re.sub('LDS 7_06\n', 'LDS 7 6\n', txt)
if(sys.argv[1] == "7_06.log"): txt = re.sub('LDS 7_07\n', 'LDS 7 7\n', txt)
if(sys.argv[1] == "7_07.log"): txt = re.sub('LDS 7_34\n', 'LDS 7 34\n', txt)
if(sys.argv[1] == "7_34.log"): txt = re.sub('MAP\nLDS ss7\n', 'MAP 0 0\nLDS 7 37\n', txt)
if(sys.argv[1] == "7_37.log"): txt = re.sub('LDS 7_36\n', 'MAP 1 0\nLDS 7 35\n', txt)
if(sys.argv[1] == "7_35.log"): txt = re.sub('MAP\nLDS ss7\n', 'MAP 11 0\nLDS 7 19\n', txt)
if(sys.argv[1] == "7_19.log"): txt = re.sub('MAP\nLDS ss7\n', 'MAP 13 0\nLDS 7 23\n', txt)
if(sys.argv[1] == "7_23.log"): txt = re.sub('MAP\nLDS ss7\n', 'MAP 12 0\nLDS 7 25\n', txt)
if(sys.argv[1] == "7_25.log"): txt = re.sub('MAP\nLDS ss7\n', 'MAP 19 0\nLDS 7 8\n', txt)
if(sys.argv[1] == "7_08.log"): txt = re.sub('MAP\nLDS ss7\n', 'MAP 24 0\nLDS 7 12\n', txt)
if(sys.argv[1] == "7_12.log"): txt = re.sub('MAP\nLDS ss7\n', 'MAP 13 0\nLDS 7 22\n', txt)
if(sys.argv[1] == "7_22.log"): txt = re.sub('MAP\nLDS ss7\n', 'MAP 5 0\nLDS 7 33\n', txt)
if(sys.argv[1] == "7_33.log"): txt = re.sub('LDS 7_38\n', 'MAP 4 0\nLDS 7 38\n', txt)
if(sys.argv[1] == "7_38.log"): txt = re.sub('LDS 7_39\n', 'LDS 7 39\n', txt)
if(sys.argv[1] == "7_39.log"): txt = re.sub('LDS 7_40\n', 'LDS 7 40\n', txt)
if(sys.argv[1] == "7_40.log"): txt = re.sub('LDS 7_41\n', 'LDS 7 41\n', txt)
if(sys.argv[1] == "7_41.log"): txt = re.sub('LDS 7_42\n', 'LDS 7 42\n', txt)
if(sys.argv[1] == "7_42.log"): txt = re.sub('LDS 8_00\n', 'LDS 8 0\n', txt)

if(sys.argv[1] == "8_00.log"): txt = re.sub('LDS 8_01\n', 'LDS 8 1\n', txt)
if(sys.argv[1] == "8_01.log"): txt = re.sub('LDS 8_02\n', 'LDS 8 2\n', txt)
if(sys.argv[1] == "8_02.log"): txt = re.sub('MAP\nLDS ss8\n', 'MAP 12 0\nLDS 8 19\n', txt)
if(sys.argv[1] == "8_19.log"): txt = re.sub('LDS 8_18\n', 'MAP 11 0\nLDS 8 13\n', txt)
if(sys.argv[1] == "8_13.log"): txt = re.sub('LDS 8_12\n', 'MAP 9 0\nLDS 8 16\n', txt)
if(sys.argv[1] == "8_16.log"): txt = re.sub('MAP\nEFF 6 0\nLDS ss8\n', 'MAP 5 0\nLDS 8 28\n', txt)
if(sys.argv[1] == "8_28.log"): txt = re.sub('LDS 8_27\n', 'MAP 3 0\nLDS 8 25\n', txt)
if(sys.argv[1] == "8_25.log"): txt = re.sub('MAP\nLDS ss8\n', 'MAP 1 0\nLDS 8 29\n', txt)
if(sys.argv[1] == "8_29.log"): txt = re.sub('LDS 8_30\n', 'LDS 8 30\n', txt)
if(sys.argv[1] == "8_30.log"): txt = re.sub('MAP\nLDS ss8\n', 'MAP 3 0\nLDS 8 32\n', txt)
if(sys.argv[1] == "8_32.log"): txt = re.sub('LDS 8_33\n', 'LDS 8 33\n', txt)
if(sys.argv[1] == "8_33.log"): txt = re.sub('LDS 8_34\n', 'LDS 8 34\n', txt)
if(sys.argv[1] == "8_34.log"): txt = re.sub('LDS 8_35\n', 'LDS 8 35\n', txt)
if(sys.argv[1] == "8_35.log"): txt = re.sub('LDS 9_00\n', 'EFF 5 0\nWAT 180\nLDS 9 0\n', txt)

if(sys.argv[1] == "9_00.log"): txt = re.sub('LDS 9_18\n', 'BGL 011\nMAP 12 0\nLDS 9 1\n', txt)
if(sys.argv[1] == "9_01.log"): txt = re.sub('MAP\nLDS ss9\n', 'MAP 3 0\nLDS 9 24\n', txt)
if(sys.argv[1] == "9_24.log"): txt = re.sub('LDS 9_23\n', 'MAP 4 0\nLDS 9 26\n', txt)
if(sys.argv[1] == "9_26.log"): txt = re.sub('LDS 9_25\n', 'MAP 0 0\nLDS 9 31\n', txt)
if(sys.argv[1] == "9_31.log"): txt = re.sub('LDS 9_30\n', 'MAP 18 0\nLDS 9 8\n', txt)
if(sys.argv[1] == "9_08.log"): txt = re.sub('LDS 9_07\n', 'MAP 25 0\nLDS 9 13\n', txt)
if(sys.argv[1] == "9_13.log"): txt = re.sub('LDS 9_12\n', 'MAP 1 0\nLDS 9 28\n', txt)
if(sys.argv[1] == "9_28.log"): txt = re.sub('LDS 9_29\n', 'LDS 9 29\n', txt)
if(sys.argv[1] == "9_29.log"): txt = re.sub('MAP\nLDS ss9\n', 'MAP 3 0\nLDS 9 32\n', txt)
if(sys.argv[1] == "9_32.log"): txt = re.sub('LDS 9_33\n', 'LDS 9 33\n', txt)
if(sys.argv[1] == "9_33.log"): txt = re.sub('LDS 9_34\n', 'LDS 9 34\n', txt)
if(sys.argv[1] == "9_34.log"): txt = re.sub('MAP\nLDS ss9\n', 'MAP 19 0\nLDS 9 36\n', txt)
if(sys.argv[1] == "9_36.log"): txt = re.sub('MAP\nLDS ss9\n', 'MAP 19 0\nLDS 9 37\n', txt)
if(sys.argv[1] == "9_37.log"): txt = re.sub('MAP\nLDS ss9\n', 'MAP 19 0\nLDS 9 38\n', txt)
if(sys.argv[1] == "9_38.log"): txt = re.sub('MAP\nLDS ss9\n', 'MAP 19 0\nLDS 9 39\n', txt)
if(sys.argv[1] == "9_39.log"): txt = re.sub('LDS ss9\n', 'MAP 19 0\nLDS 9 40\n', txt)

# オオカミに追いかけ回される
if(sys.argv[1] == "9_40.log"): txt = re.sub('MAP\nEFF 6 0\nBGL 005\n', 'MAP 1 0\nEFF 6 0\nBGL 005\n', txt)
if(sys.argv[1] == "9_40.log"): txt = re.sub('MAP\nEFF 6 0\nBGL 004\n', 'MAP 3 0\nEFF 6 0\nBGL 004\n', txt)
if(sys.argv[1] == "9_40.log"): txt = re.sub('MAP\nEFF 6 0\nBGL 006\n', 'MAP 4 0\nEFF 6 0\nBGL 006\n', txt)
if(sys.argv[1] == "9_40.log"): txt = re.sub('MAP\nEFF 6 0\nBGL 003\n', 'MAP 5 0\nEFF 6 0\nBGL 003\n', txt)
if(sys.argv[1] == "9_40.log"): txt = re.sub('LDS 9_41\n', 'LDS 9 41\n', txt)

if(sys.argv[1] == "9_41.log"): txt = re.sub('MAP\nEFF 6 0\nBGL 013\n', 'MAP 0 0\nEFF 6 0\nBGL 002\n', txt)
if(sys.argv[1] == "9_41.log"): txt = re.sub('LDS 9_42\n', 'LDS 9 42\n', txt)
if(sys.argv[1] == "9_42.log"): txt = re.sub('LDS a_00\n', 'LDS 10 0\n', txt)

if(sys.argv[1] == "a_00.log"): txt = re.sub('LDS a_01\n', 'LDS 10 1\n', txt)
if(sys.argv[1] == "a_01.log"): txt = re.sub('LDS a_01b\n', 'LDS 10 7\n', txt)
if(sys.argv[1] == "a_07.log"): txt = re.sub('LDS u600\n', 'MAP 27 0\nLDS 10 2\n', txt)
if(sys.argv[1] == "a_02.log"): txt = re.sub('LDS ssa\n', 'MAP 27 0\nLDS 10 3\n', txt)
if(sys.argv[1] == "a_03.log"): txt = re.sub('LDS ssa\n', 'MAP 27 0\nLDS 10 4\n', txt)
if(sys.argv[1] == "a_04.log"): txt = re.sub('LDS ssa\n', 'MAP 27 0\nLDS 10 5\n', txt)
if(sys.argv[1] == "a_05.log"): txt = re.sub('MAP\n', 'MAP 25 0\n', txt)
if(sys.argv[1] == "a_05.log"): txt = re.sub('LDS a_06\n', 'LDS 10 6\n', txt)
if(sys.argv[1] == "a_06.log"): txt = re.sub('LDS b_00\n', 'LDS 11 0\n', txt)

if(sys.argv[1] == "b_00.log"): txt = re.sub('LDS u700\n', 'MAP 18 0\nLDS 11 3\n', txt)
if(sys.argv[1] == "b_03.log"): txt = re.sub('MAP\nLDS ssb\n', 'MAP 5 0\nLDS 11 2\n', txt)
if(sys.argv[1] == "b_02.log"): txt = re.sub('MAP\nLDS ssb\n', 'MAP 1 0\nLDS 11 4\n', txt)
if(sys.argv[1] == "b_04.log"): txt = re.sub('MAP\nLDS ssb\n', 'MAP 12 0\nLDS 11 1\n', txt)
if(sys.argv[1] == "b_01.log"): txt = re.sub('MAP\nLDS ssb\n', 'MAP 24 0\nLDS 11 5\n', txt)
if(sys.argv[1] == "b_05.log"): txt = re.sub('LDS b_06\n', 'LDS 11 6\n', txt)
if(sys.argv[1] == "b_06.log"): txt = re.sub('LDS b_07\n', 'LDS 11 7\n', txt)
if(sys.argv[1] == "b_07.log"): txt = re.sub('LDS b_08\n', 'LDS 11 8\n', txt)
if(sys.argv[1] == "b_08.log"): txt = re.sub('LDS u700\n', 'MAP 16 0\nLDS 11 14\n', txt)
if(sys.argv[1] == "b_14.log"): txt = re.sub('MAP\nLDS ssb\n', 'MAP 27 0\nLDS 11 9\n', txt)
if(sys.argv[1] == "b_09.log"): txt = re.sub('LDS u700\n', 'BGL 011\nMAP 5 0\nLDS 11 11\n', txt)
if(sys.argv[1] == "b_11.log"): txt = re.sub('LDS u700\n', 'MAP 0 0\nLDS 11 10\n', txt)
if(sys.argv[1] == "b_10.log"): txt = re.sub('LDS u700\n', 'MAP 1 0\nLDS 11 13\n', txt)
if(sys.argv[1] == "b_13.log"): txt = re.sub('MAP\nLDS ssb\n', 'MAP 14 0\nLDS 11 15\n', txt)
if(sys.argv[1] == "b_15.log"): txt = re.sub('LDS b_16\n', 'LDS 11 16\n', txt)
if(sys.argv[1] == "b_16.log"): txt = re.sub('LDS b_17\n', 'LDS 11 17\n', txt)
if(sys.argv[1] == "b_17.log"): txt = re.sub('LDS c_00\n', 'LDS 12 0\n', txt)

if(sys.argv[1] == "c_00.log"): txt = re.sub('SEL 女主人\nLDS c_01\n', 'MEU\n', txt)
if(sys.argv[1] == "c_03.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_07.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_04.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_05.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_06.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_02.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_08.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_01.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_17.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_16.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_18.log"): txt = re.sub('LDS open\n', 'END\n', txt)
if(sys.argv[1] == "c_11.log"): txt = re.sub('LDS open\n', 'END\n', txt)


# ---------------------------------------------------------------------------
# 表現の変更

# 余白追加　名言
if(sys.argv[1] == "0_00.log"): txt = re.sub('MSG ポ\n', 'MSG 　ポ\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "0_00.log"): txt = re.sub('WAT 160\n', 'KEY\n', txt)
# タイトル　表示ウェイト
if(sys.argv[1] == "0_00.log"): txt = re.sub('BPL 1\n', 'BPL 1\nWAT 360\n', txt)
# タイトル　フェードアウト後のウェイト
if(sys.argv[1] == "0_00.log"): txt = re.sub('EFF 6 0\n', 'EFF 6 0\nWAT 120\n', txt)

# 消去　エフェクト
if(sys.argv[1] == "1_00.log"): txt = re.sub('EFF 5 0\nEFF 6 0\nEFF 2 4\n', '', txt)
# 消去　エフェクト
if(sys.argv[1] == "1_00.log"): txt = re.sub('EFF 1 3\nEFF 6 0\nEFF 5 0\n', 'EFF 1 3\nEFF 5 0\n', txt)
# 消去　エフェクト
if(sys.argv[1] == "1_00.log"): txt = re.sub('EFF 6 0\nEFF 5 0\n', 'EFF 5 0\n', txt)
# 消去　ウェイト
if(sys.argv[1] == "1_00.log"): txt = re.sub('BST\nMSG', 'WAT 60\nBST\nMSG', txt)
# 消去　（微妙に違うけど）重複文章
if(sys.argv[1] == "1_01.log"): txt = re.sub('SEL 見る\nSEL 女主人\nMSG 館の女主人は微笑みながら僕を見つめている。\nKEY\n', '', txt)
# 消去　重複文章
if(sys.argv[1] == "1_01.log"): txt = re.sub('SEL 聞く\nSEL 美和子\nMSG 美和子：「・・・美和子と申します・・・。このお屋敷に御奉公させていただいております・・・」\nKEY\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_26.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 全角空白追加　摩耶の名前
if(sys.argv[1] == "1_26.log"): txt = re.sub('岡崎', '　岡崎',txt)
# 消去　重複音楽
if(sys.argv[1] == "1_03.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_24.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複文章
if(sys.argv[1] == "1_24.log"): txt = re.sub('SEL 話す\nMSG 男：「さっすが、俺ってさえてるう\\\\eb\\\\b3」\nKEY\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_18.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_33.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_29.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_30.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_17.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_27.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_06.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_07.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_05.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_10.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_34.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_36.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_58.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_49.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複文章
if(sys.argv[1] == "1_61.log"): txt = re.sub('SEL 聞く\nSEL 客\nMSG 沙里：「私の長くのびた髪を見てあの方は誉めてくださるかしら・・・」\nKEY\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "1_66.log"): txt = re.sub('BST\nBPL 2\n', '', txt)

# 消去　重複音楽
if(sys.argv[1] == "2_20.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "2_24.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 背景追加　玄関ホール
if(sys.argv[1] == "2_01.log"): txt = re.sub('BPL 4\n', 'BPL 4\nBGL 10a\n', txt)
# 消去　重複文章
if(sys.argv[1] == "2_33.log"): txt = re.sub('SEL 聞く\nSEL 深紗緒\nMSG 深紗緒：「もう何も教えないからね」\nKEY\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "2_29.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 背景追加　玄関ホール
if(sys.argv[1] == "2_02.log"): txt = re.sub('BPL 4\n', 'BPL 4\nBGL 10a\n', txt)
# 背景追加　テラス
if(sys.argv[1] == "2_03.log"): txt = re.sub('BPL 4\n', 'BPL 4\nBGL 003\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "2_08.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複文章
if(sys.argv[1] == "2_08.log"): txt = re.sub('SEL 調べる\nSEL 本\nMSG 慎一：（僕は白日夢でも見たっていうのか・・・？）\nKEY\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "2_31.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "2_27.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "2_28.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 処理順入れ替え
if(sys.argv[1] == "2_41.log"): txt = re.sub('SEL 話す\nMSG 山草：「遠慮なんかしなくていいんだぜ」\nCHR 90b\n', 'CHR 90b\nSEL 話す\nMSG 山草：「遠慮なんかしなくていいんだぜ」\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "2_46.log"): txt = re.sub('BST\nBPL 4\n', '', txt)

# 余白追加　名言
if(sys.argv[1] == "3_00.log"): txt = re.sub('MSG ア\n', 'MSG 　ア\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "3_00.log"): txt = re.sub('WAT 160\n', 'KEY\n', txt)
# 消去　重複文章
if(sys.argv[1] == "3_01.log"): txt = re.sub('SEL 見る\nMSG 天井に取り付けられた扉は太い鎖で開かないように固定され、さらに大きな南京錠までとりつけられている。\nKEY\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "3_03.log"): txt = re.sub('BST\nBPL 9\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "3_03.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 消去　エフェクト
if(sys.argv[1] == "3_03.log"): txt = re.sub('EFF 6 0\nEFF 2 0\nEFF 6 0\n', '', txt)
# 背景変更　書斎
if(sys.argv[1] == "3_04.log"): txt = re.sub('BGL 002\n', 'BGL 013\n', txt)
# 消去　重複文章１
if(sys.argv[1] == "3_05.log"): txt = re.sub('SEL 聞く\nMSG 摩耶：「嫌嫌嫌っ\\\\eb\\\\b4」山草：「こらっ、暴れるなっ」\nKEY\n', '', txt)
# 消去　重複文章２
if(sys.argv[1] == "3_05.log"): txt = re.sub('MSG 僕達は２階の廊下の隅にいる。\nKEY\n', '', txt)
# 消去　美和子消去
if(sys.argv[1] == "3_08.log"): txt = re.sub('SEL 話す\nCHR 64b\n', 'SEL 話す\nEFF 7 0\nCHR 64b\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "3_09.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)

# 余白追加　名言
if(sys.argv[1] == "4_00.log"): txt = re.sub('MSG グ\n', 'MSG 　グ\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "4_00.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 消去　エフェクト
if(sys.argv[1] == "4_29.log"): txt = re.sub('EFF 5 0\n', '', txt)
# 変更　ウェイトをキー入力へ
if(sys.argv[1] == "4_29.log"): txt = re.sub('WAT 60\n', 'KEY\n', txt)
# 消去　背景重複１
if(sys.argv[1] == "4_29.log"): txt = re.sub('SET 79c 1\nEFF 7 0\nMSG 人魚：「私・・・私は', 'MSG 人魚：「私・・・私は', txt)
# 消去　背景重複２
if(sys.argv[1] == "4_29.log"): txt = re.sub('SET 79c 1\nEFF 7 0\nMSG 人魚：「でも、嵐', 'MSG 人魚：「でも、嵐', txt)
# 消去　背景重複３
if(sys.argv[1] == "4_29.log"): txt = re.sub('SET 79c 1\nEFF 7 0\nMSG 人魚：「それから・・・', 'MSG 人魚：「それから・・・', txt)
# 変更　エフェクト
if(sys.argv[1] == "4_30.log"): txt = re.sub('EFF 2 4', 'EFF 2 0', txt)
# 追加　ウェイト
if(sys.argv[1] == "4_30.log"): txt = re.sub('LDS 4 31\n', 'WAT 60\nLDS 4 31\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "4_32.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　ウェイト
if(sys.argv[1] == "4_32.log"): txt = re.sub('WAT 240\n', 'WAT 120\n', txt)

# 余白追加　名言
if(sys.argv[1] == "5_00.log"): txt = re.sub('MSG エ\n', 'MSG 　エ\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "5_00.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "5_16.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複文章
if(sys.argv[1] == "5_32.log"): txt = re.sub('SEL 聞く\nMSG ぴしぃっ・・・ぴしぃっ・・・音は僕を誘っているかのように闇の中から響いている・・・。\nKEY\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "5_33.log"): txt = re.sub('EFF 2 4', 'EFF 2 0', txt)
# 変更　エフェクト
if(sys.argv[1] == "5_33.log"): txt = re.sub('EFF 3 5\nEFF 5 0\nEFF 4 5\n', 'EFF 3 5\nEFF 6 0\nEFF 4 5\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "5_35.log"): txt = re.sub('EFF 3 5\nEFF 5 0\nEFF 4 5\n', 'EFF 3 5\nEFF 6 0\nEFF 4 5\n', txt)
# 消去　エフェクト
if(sys.argv[1] == "5_35.log"): txt = re.sub('EFF 6 0\nEFF 4 3\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "5_37.log"): txt = re.sub('EFF 1 5\nEFF 1 3\nEFF 5 0\nEFF 6 0\nEFF 2 4\nEFF 5 0\n', 'EFF 1 5\nEFF 5 0\nEFF 6 0\nEFF 2 0\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "5_37.log"): txt = re.sub('EFF 3 5\nEFF 5 0\nEFF 6 0\nEFF 4 3\n', 'EFF 3 5\nEFF 6 0\nEFF 4 3\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "5_63.log"): txt = re.sub('BST\nBPL 9\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "5_63.log"): txt = re.sub('EFF 1 5\nEFF 1 3\n', 'EFF 1 5\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "5_63.log"): txt = re.sub('EFF 2 4\nEFF 5 0\n', 'EFF 2 0\n', txt)
# 消去　重複文章
if(sys.argv[1] == "5_64.log"): txt = re.sub('・」\nKEY\nSEL 言葉で苛める\nMSG 慎一：「そんなにお尻を振ってどうしたんだい？何かして欲しいの？」美和子：「い、いえ・・・別に・・・」\nKEY\nMSG 慎一：「ふぅ～～～ん」\nKEY\n', '・」\nKEY\n', txt)
# 消去　ウェイト
if(sys.argv[1] == "5_66.log"): txt = re.sub('HSC 069\n', 'WAT 60\nHSC 069\n', txt)

# 余白追加　名言
if(sys.argv[1] == "6_00.log"): txt = re.sub('MSG マ\n', 'MSG 　マ\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "6_00.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 追加　背景
if(sys.argv[1] == "6_01.log"): txt = re.sub('BPL 0\n', 'BPL 0\nBGL 013\n', txt)
# 追加　背景
if(sys.argv[1] == "6_02.log"): txt = re.sub('BPL 4\n', 'BPL 4\nBGL 013\n', txt)
# 変更　草山→摩耶　コンバータ側のバグ。ゲーム上では問題なし
if(sys.argv[1] == "6_02.log"): txt = re.sub('山草：', '摩耶：', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_03.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_04.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 追加　背景
if(sys.argv[1] == "6_04.log"): txt = re.sub('CHR 25h\n', 'BGL 003\nCHR 25h\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_05.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 追加　背景
if(sys.argv[1] == "6_05.log"): txt = re.sub('CHR 64b\n', 'BGL 003\nCHR 64b\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_26.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_27.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_28.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_30.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_29.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_16.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_12.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_13.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_14.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_15.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_11.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_25.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_20.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "6_21.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# 消去　エフェクト
if(sys.argv[1] == "6_31.log"): txt = re.sub('EFF 1 5\nEFF 2 4\n', '', txt)
# 消去　重複文章
if(sys.argv[1] == "6_31.log"): txt = re.sub('SEL 見る\nSEL 指の先\nMSG 巣の中には、ぎゅうぎゅうとひしめきあっている、まるまるとした愛らしい鳥のヒナ達の姿があった。\nKEY\n', '', txt)
# 消去　エフェクト
if(sys.argv[1] == "6_32.log"): txt = re.sub('EFF 1 5\nBST\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "6_33.log"): txt = re.sub('EFF 3 4\nEFF 4 4\n', 'EFF 3 4\nEFF 7 0\nEFF 4 4\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "6_34.log"): txt = re.sub('EFF 2 4\nEFF 1 3\n', 'EFF 2 0\n', txt)

# 余白追加　名言
if(sys.argv[1] == "7_00.log"): txt = re.sub('MSG カ\n', 'MSG 　カ\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "7_00.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　ウェイトをキー入力へ
if(sys.argv[1] == "7_00.log"): txt = re.sub('WAT 120\n', 'KEY\n', txt)
# 変更　重複文章
if(sys.argv[1] == "7_03.log"): txt = re.sub('MSG そこは四方を茂みと土蔵の壁と屋敷の塀に囲まれた小さな空き地になっていた。\nKEY\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "7_04.log"): txt = re.sub('EFF 2 4', 'EFF 2 0', txt)
# 消去　重複文章
if(sys.argv[1] == "7_07.log"): txt = re.sub('SEL 見る\nSEL 由羅\nMSG 無邪気に微笑む由羅の顔を見つめていると、女主人に見せられた過去の光景が重なって・・・暗鬱たる気分になってしまう。\nKEY\n', '', txt)
# 消去　重複文章
if(sys.argv[1] == "7_07.log"): txt = re.sub('SEL 説得する\nMSG 慎一：（だめか・・・鬼には・・・もう人の心なんて残っていないのかも・・・。妹を独占したいという欲望しか・・・残っていないみたいだ・・・）\nKEY\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "7_12.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "7_35.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "7_22.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "7_38.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "7_41.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 追加　エフェクトとウェイト
if(sys.argv[1] == "7_42.log"): txt = re.sub('EFF 3 4\n', 'EFF 3 4\nEFF 6 0\nEFF 4 2\nWAT 60\n', txt)
# 追加　改行１
if(sys.argv[1] == "7_42.log"): txt = re.sub('妹・・・。\n', '妹・・・。\nKEY\n', txt)
# 追加　改行２
if(sys.argv[1] == "7_42.log"): txt = re.sub('BST\n', 'KEY\nBST\n', txt)

# 余白追加　名言
if(sys.argv[1] == "8_00.log"): txt = re.sub('MSG キ\n', 'MSG 　キ\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "8_00.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "8_00.log"): txt = re.sub('EFF 1 4\nEFF 5 0\nEFF 6 0\n', '', txt)
# 消去　重複文章
if(sys.argv[1] == "8_25.log"): txt = re.sub('SEL 聞く\nSEL 恋人\nMSG 沙里：「戦争が終わったら・・・あの方は帰ってこれるはずなんです」\nKEY\n', '', txt)
# 変更　背景
if(sys.argv[1] == "8_30.log"): txt = re.sub('BGL 048\n', '', txt)

# 余白追加　名言１
if(sys.argv[1] == "9_00.log"): txt = re.sub('MSG カ\n', 'MSG 　カ\n', txt)
# 余白追加　名言２
if(sys.argv[1] == "9_00.log"): txt = re.sub('MSG 『\n', 'MSG 『　\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "9_00.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト（正規表現２回）
if(sys.argv[1] == "9_00.log"): txt = re.sub('EFF 1 4\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "9_01.log"): txt = re.sub('BST\nBPL 0\n', '', txt)
# 変更　背景
if(sys.argv[1] == "9_01.log"): txt = re.sub('BGL 002\n', 'BGL 10a\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "9_24.log"): txt = re.sub('BST\nBPL 0\n', '', txt)
# 消去　重複音楽
if(sys.argv[1] == "9_26.log"): txt = re.sub('BST\nBPL 0\n', '', txt)
# 余白追加　名言
if(sys.argv[1] == "9_34.log"): txt = re.sub('MSG ペ\n', 'MSG 　ペ\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "9_34.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト（正規表現２回）
if(sys.argv[1] == "9_34.log"): txt = re.sub('EFF 1 4\nEFF 5 0\n', 'EFF 1 4\nEFF 2 0\n', txt)
# 追加　背景
if(sys.argv[1] == "9_36.log"): txt = re.sub('CHR 37a\n', 'BGL 011\nCHR 37a\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "9_37.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 追加　背景
if(sys.argv[1] == "9_37.log"): txt = re.sub('CHR 16c\n', 'BGL 011\nCHR 16c\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "9_38.log"): txt = re.sub('BST\nBPL 2\n', '', txt)
# 追加　背景
if(sys.argv[1] == "9_38.log"): txt = re.sub('CHR 25h\n', 'BGL 011\nCHR 25h\n', txt)
# 追加　背景
if(sys.argv[1] == "9_39.log"): txt = re.sub('CHR 083\n', 'BGL 011\nCHR 083\n', txt)
# 追加　背景
if(sys.argv[1] == "9_40.log"): txt = re.sub('BST\nMSG', 'BGL 011\nBST\nMSG', txt)
# 変更　エフェクト（正規表現２回）
if(sys.argv[1] == "9_42.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "9_42.log"): txt = re.sub('EFF 6 0\nBGL 089\n', 'EFF 6 0\nEFF 4 0\nBGL 089\n', txt)

# 余白追加　名言
if(sys.argv[1] == "a_00.log"): txt = re.sub('WAT 4\nMSG ト\n', 'WAT 4\nMSG 　ト\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "a_00.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　キー入力
if(sys.argv[1] == "a_00.log"): txt = re.sub('WAT 120\n', 'KEY\n', txt)
# 変更　文章
if(sys.argv[1] == "a_00.log"): txt = re.sub('MSG 父さん父さん', 'KEY\nMSG 父さん　父さん　', txt)
# 消去　重複音楽
if(sys.argv[1] == "a_07.log"): txt = re.sub('BST\nBPL 8\n', '', txt)
# 変更　背景
if(sys.argv[1] == "a_02.log"): txt = re.sub('BGL 002\n', 'BGL 049\n', txt)
# 変更　背景
if(sys.argv[1] == "a_03.log"): txt = re.sub('BGL 002\n', 'BGL 049\n', txt)
# 変更　背景
if(sys.argv[1] == "a_04.log"): txt = re.sub('BGL 002\n', 'BGL 049\n', txt)
# 変更　背景
if(sys.argv[1] == "a_05.log"): txt = re.sub('BGL 002\n', 'BGL 049\n', txt)

# 余白追加　名言
if(sys.argv[1] == "b_00.log"): txt = re.sub('MSG サ\n', 'MSG 　サ\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "b_00.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 消去　重複音楽
if(sys.argv[1] == "b_02.log"): txt = re.sub('BST\nBPL 0\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "b_07.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　エフェクト（正規表現２回）
if(sys.argv[1] == "b_08.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　エフェクト（正規表現２回）
if(sys.argv[1] == "b_16.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 消去　重複文章
if(sys.argv[1] == "b_16.log"): txt = re.sub('SEL 調べる\nSEL 書棚\nMSG 書棚には数え切れないほどの本が詰め込まれている。\nKEY\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "b_17.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)

# 余白追加　名言１
if(sys.argv[1] == "c_00.log"): txt = re.sub('MSG エ\n', 'MSG 　エ\n', txt)
# 余白追加　名言２
if(sys.argv[1] == "c_00.log"): txt = re.sub('MSG あ\nFMX 4\nWAT 4\nMSG っ\n', 'MSG 　あ\nFMX 4\nWAT 4\nMSG っ\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "c_00.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "c_01.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト（正規表現２回）
if(sys.argv[1] == "c_01.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "c_02.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "c_02.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "c_03.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "c_03.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "c_04.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "c_04.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "c_05.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "c_05.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "c_06.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "c_06.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　沙里の鬼から人へエフェクト
if(sys.argv[1] == "c_06.log"): txt = re.sub('EFF 1 0\nIMG 96a\nIMG 96b\nEFF 2 2\nEFF 3 1\nEFF 4 1\nEFF 4 2\nEFF 4 3\nEFF 4 4\n', 'EFF 1 0\nBGL 96b\nEFF 2 0\nEFF 3 1\nBGL 96b\nEFF 4 1\nEFF 3 2\nBGL 96a\nEFF 4 2\nEFF 3 3\nBGL 96b\nEFF 4 3\nEFF 3 4\nBGL 96a\nEFF 4 4\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "c_07.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "c_07.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　名言キー入力
if(sys.argv[1] == "c_08.log"): txt = re.sub('WAT 128\n', 'KEY\n', txt)
# 変更　エフェクト（正規表現２回）
if(sys.argv[1] == "c_08.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 消去　背景
if(sys.argv[1] == "c_08.log"): txt = re.sub('IMG half\n', '', txt)
# 変更　エフェクト（正規表現２回）
if(sys.argv[1] == "c_11.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "c_16.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 消去　背景
if(sys.argv[1] == "c_16.log"): txt = re.sub('IMG 96a\nIMG 96b\n', '', txt)
# 変更　エフェクト
if(sys.argv[1] == "c_17.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)
# 変更　エフェクト
if(sys.argv[1] == "c_18.log"): txt = re.sub('EFF 2 4\n', 'EFF 2 0\n', txt)


# ---------------------------------------------------------------------------
# GBA用の改行コードを挿入 0xeb 0xff
txt = re.sub('小間使い：', '\\\\eb\\\\ff小間使い：', txt)
txt = re.sub('女主人：', '\\\\eb\\\\ff女主人：', txt)
txt = re.sub('美和子：', '\\\\eb\\\\ff美和子：', txt)
txt = re.sub('深紗緒：', '\\\\eb\\\\ff深紗緒：', txt)
txt = re.sub('赤頭巾：', '\\\\eb\\\\ff赤頭巾：', txt)
txt = re.sub('亜璃沙：', '\\\\eb\\\\ff亜璃沙：', txt)
txt = re.sub('ヨロイ：', '\\\\eb\\\\ffヨロイ：', txt)
txt = re.sub('？？？：', '\\\\eb\\\\ff？？？：', txt)
txt = re.sub('慎一：', '\\\\eb\\\\ff慎一：', txt)
txt = re.sub('沙里：', '\\\\eb\\\\ff沙里：', txt)
txt = re.sub('摩耶：', '\\\\eb\\\\ff摩耶：', txt)
txt = re.sub('雪菜：', '\\\\eb\\\\ff雪菜：', txt)
txt = re.sub('由羅：', '\\\\eb\\\\ff由羅：', txt)
txt = re.sub('草山：', '\\\\eb\\\\ff草山：', txt)
txt = re.sub('女性：', '\\\\eb\\\\ff女性：', txt)
txt = re.sub('人魚：', '\\\\eb\\\\ff人魚：', txt)
txt = re.sub('手紙：', '\\\\eb\\\\ff手紙：', txt)
txt = re.sub('日記：', '\\\\eb\\\\ff日記：', txt)
txt = re.sub('男：', '\\\\eb\\\\ff男：', txt)
txt = re.sub('兄：', '\\\\eb\\\\ff兄：', txt)
txt = re.sub('鬼：', '\\\\eb\\\\ff鬼：', txt)
txt = re.sub('狼：', '\\\\eb\\\\ff狼：', txt)
txt = re.sub('声：', '\\\\eb\\\\ff声：', txt)

# 女、別の女、少女は先に女を置換します
txt = re.sub('女：', '\\\\eb\\\\ff女：', txt)
txt = re.sub('別の\\\\eb\\\\ff女：', '\\\\eb\\\\ff別の女：', txt)
txt = re.sub('少\\\\eb\\\\ff女：', '\\\\eb\\\\ff少女：', txt)

# 先頭は改行を行わない
txt = re.sub('MSG \\\\eb\\\\ff', 'MSG ', txt)


# ---------------------------------------------------------------------------

with open(sys.argv[2], "w") as f:
	f.write(txt)

