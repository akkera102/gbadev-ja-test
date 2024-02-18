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
# 拡張子消去
txt = re.sub('\\.g', '', txt)
txt = re.sub('\\.lsp', '', txt)

# 演奏コマンド重複
txt = re.sub('BST\nBST\nBST\n', 'BST\n', txt)
txt = re.sub('BST\nBST\n', 'BST\n', txt)

# 演奏コマンド24（パタパタアニメ曲）
txt = re.sub('BPL 24\n', '', txt)

# 効果音再生時の不要テキスト
txt = re.sub('MSG \n', '', txt)

# ---------------------------------------------------------------------------
# パタパタアニメ
# 1:ウルフィ→カイト
# 2:カイト　→ウルフィ
# 3:ウルフィ→ウルフィ
# 4:カイト　→カイト
# 5:ウルフィ→ラビィ
# 6:ラビィ　→ウルフィ

txt = re.sub('IMG pata\n', '', txt)
txt = re.sub('IMG pata2\n', '', txt)
txt = re.sub('IMG pat001', 'PAT 1 1', txt)		# Falling Angel
txt = re.sub('IMG pat002', 'PAT 2 2', txt)		# Seeker
txt = re.sub('IMG pat003', 'PAT 3 3', txt)		# Twin Angel
txt = re.sub('IMG pat004', 'PAT 4 3', txt)		# In the Dark...
txt = re.sub('IMG pat005', 'PAT 5 1', txt)		# Miracle
txt = re.sub('IMG pat006', 'PAT 6 2', txt)		# Resolution
txt = re.sub('IMG pat007', 'PAT 7 1', txt)		# The Clue
txt = re.sub('IMG pat008', 'PAT 8 2', txt)		# Foresight
txt = re.sub('IMG pat009', 'PAT 9 3', txt)		# Loss of Hope
txt = re.sub('IMG pat010', 'PAT 10 1', txt)		# Prayer
txt = re.sub('IMG pat011', 'PAT 11 2', txt)		# Stream
txt = re.sub('IMG pat012', 'PAT 12 1', txt)		# Mermaid
txt = re.sub('IMG pat013', 'PAT 13 2', txt)		# Drifter
txt = re.sub('IMG pat014', 'PAT 14 1', txt)		# Flashback
txt = re.sub('IMG pat015', 'PAT 15 2', txt)		# Confusion
txt = re.sub('IMG pat016', 'PAT 16 1', txt)		# Join a Party
txt = re.sub('IMG pat017', 'PAT 17 2', txt)		# Rebirth
txt = re.sub('IMG pat018', 'PAT 18 5', txt)		# Doomcity
txt = re.sub('IMG pat019', 'PAT 19 6', txt)		# Underground
txt = re.sub('IMG pat020', 'PAT 20 1', txt)		# Cavern
txt = re.sub('IMG pat021', 'PAT 21 4', txt)		# Fork
txt = re.sub('IMG pat022', 'PAT 22 2', txt)		# Slough
txt = re.sub('IMG pat023', 'PAT 23 3', txt)		# Hope
txt = re.sub('IMG pat024', 'PAT 24 1', txt)		# Meet Again
txt = re.sub('IMG pat025', 'PAT 25 2', txt)		# Forbidden Place
txt = re.sub('IMG pat026', 'PAT 26 3', txt)		# Final Fight
txt = re.sub('IMG pat027', 'PAT 27 3', txt)		# Relieve
txt = re.sub('IMG pat028', 'PAT 28 1', txt)		# And...


# ---------------------------------------------------------------------------
# パーティ
txt = re.sub('IMG pty000\n', '', txt)
txt = re.sub('IMG pty', 'PTY pty', txt)


# ---------------------------------------------------------------------------
# エフェクト
txt = re.sub('IMG blackf\nIMG win3\nIMG waku06b\n', 'EFF 15\n', txt)
txt = re.sub('IMG win3\nIMG waku06b\nIMG black\n', 'EFF 14\n', txt)
txt = re.sub('IMG winf\nIMG blackf\nIMG blackf\n', 'EFF 13\n', txt)
txt = re.sub('IMG black\nIMG blacke\nIMG black\n', 'EFF 12\n', txt)
txt = re.sub('IMG win3\nIMG waku06b\n', 'EFF 11\n', txt)
txt = re.sub('IMG black\nIMG blacke\n', 'EFF 10\n', txt)
txt = re.sub('IMG winf\nIMG blackf\n', 'EFF 9\n', txt)
txt = re.sub('IMG black\nIMG black\n', 'EFF 8\n', txt)
txt = re.sub('IMG waku06b', 'EFF 7', txt)
txt = re.sub('IMG blackf', 'EFF 6', txt)
txt = re.sub('IMG blacke', 'EFF 5', txt)
txt = re.sub('IMG black', 'EFF 4', txt)
txt = re.sub('IMG light', 'EFF 3', txt)
txt = re.sub('IMG winf', 'EFF 2', txt)
txt = re.sub('IMG win3', 'EFF 1', txt)


# ---------------------------------------------------------------------------
# キャラアイコン
txt = re.sub('IMG kait', 'ICO kait', txt)
txt = re.sub('IMG iria', 'ICO iria', txt)
txt = re.sub('IMG wolf', 'ICO wolf', txt)
txt = re.sub('IMG raby', 'ICO raby', txt)
txt = re.sub('IMG nees', 'ICO nees', txt)
txt = re.sub('IMG angl', 'ICO angl', txt)
txt = re.sub('IMG xtra', 'ICO xtra', txt)
txt = re.sub('IMG dian', 'ICO dian', txt)
txt = re.sub('IMG far_', 'ICO far_', txt)
txt = re.sub('IMG blue', 'ICO blue', txt)
txt = re.sub('IMG kine', 'ICO kine', txt)
txt = re.sub('IMG leon', 'ICO leon', txt)
txt = re.sub('IMG dora', 'ICO dora', txt)
txt = re.sub('IMG mira', 'ICO mira', txt)
txt = re.sub('IMG kyas', 'ICO kyas', txt)
txt = re.sub('IMG biat', 'ICO biat', txt)
txt = re.sub('IMG nukiff', 'ICO nukiff', txt)
txt = re.sub('IMG mina', 'ICO mina', txt)
txt = re.sub('IMG dira', 'ICO dira', txt)
txt = re.sub('IMG resi', 'ICO resi', txt)
txt = re.sub('IMG bee_', 'ICO bee_', txt)
txt = re.sub('IMG ruri', 'ICO ruri', txt)
txt = re.sub('IMG lili', 'ICO lili', txt)
txt = re.sub('IMG elza', 'ICO elza', txt)
txt = re.sub('IMG titi', 'ICO titi', txt)
txt = re.sub('IMG rose', 'ICO rose', txt)
txt = re.sub('IMG harp', 'ICO harp', txt)
txt = re.sub('IMG vian', 'ICO vian', txt)
txt = re.sub('IMG mie_', 'ICO mie_', txt)
txt = re.sub('IMG alph', 'ICO alph', txt)
txt = re.sub('IMG mirh', 'ICO mirh', txt)
txt = re.sub('IMG irih', 'ICO irih', txt)
txt = re.sub('IMG leoh', 'ICO leoh', txt)
txt = re.sub('IMG dorh', 'ICO dorh', txt)
txt = re.sub('IMG rabh', 'ICO rabh', txt)


# ---------------------------------------------------------------------------
# キャラ立ち絵（アルファあり）
txt = re.sub('IMG ca002a2\nIMG ca002d2\n', 'CHR ca002d2\n', txt)
txt = re.sub('IMG ca007a2\nIMG ca007c2\n', 'CHR ca007c2\n', txt)
txt = re.sub('IMG ca007a2\nIMG ca007d2\n', 'CHR ca007d2\n', txt)
txt = re.sub('IMG ca007b\nIMG ca007b2\n', 'CHR ca007b2\n', txt)
txt = re.sub('IMG ca008a\nIMG ca008b\n', 'CHR ca008b\n', txt)
txt = re.sub('IMG ca008a\nIMG ca008c\n', 'CHR ca008c\n', txt)
txt = re.sub('IMG ca009a\nIMG ca009b\n', 'CHR ca009b\n', txt)
txt = re.sub('IMG ca010a\nIMG ca010b\n', 'CHR ca010b\n', txt)
txt = re.sub('IMG ca010a\nIMG ca010c\n', 'CHR ca010c\n', txt)
txt = re.sub('IMG ca011a\nIMG ca011f2\n', 'CHR ca011f2\n', txt)
txt = re.sub('IMG ca012a\nIMG ca012d\n', 'CHR ca012d\n', txt)
txt = re.sub('IMG ca013a\nIMG ca013f\n', 'CHR ca013f\n', txt)
txt = re.sub('IMG ca014a\nIMG ca014b\n', 'CHR ca014b\n', txt)
txt = re.sub('IMG ca014a\nIMG ca014c\n', 'CHR ca014c\n', txt)
txt = re.sub('IMG ca014a\nIMG ca014d\n', 'CHR ca014d\n', txt)
txt = re.sub('IMG ca015a\nIMG ca015c\n', 'CHR ca015c\n', txt)
txt = re.sub('IMG ca018a\nIMG ca018b\n', 'CHR ca018b\n', txt)
txt = re.sub('IMG ca019a\nIMG ca019c\n', 'CHR ca019c\n', txt)
txt = re.sub('IMG ca019a\nIMG ca019d\n', 'CHR ca019d\n', txt)
txt = re.sub('IMG ca020a\nIMG ca020b\n', 'CHR ca020b\n', txt)
txt = re.sub('IMG ca020a\nIMG ca020c\n', 'CHR ca020c\n', txt)
txt = re.sub('IMG ca020a\nIMG ca020d\n', 'CHR ca020d\n', txt)
txt = re.sub('IMG ca021a\nIMG ca021c\n', 'CHR ca021c\n', txt)
txt = re.sub('IMG ca021a\nIMG ca021b\n', 'CHR ca021b\n', txt)
txt = re.sub('IMG ca021a\nIMG ca021d\n', 'CHR ca021d\n', txt)


# ---------------------------------------------------------------------------
# 背景差分
txt = re.sub('IMG bg01\nIMG bg01b', 'BGL bg01b', txt)
txt = re.sub('IMG bg19\nIMG bg19c\n', 'BGL bg19c\n', txt)
txt = re.sub('IMG bg00\nIMG bg00b\n', 'BGL bg00b\n', txt)
txt = re.sub('IMG bg01\nIMG bg01c\n', 'BGL bg01c\n', txt)
txt = re.sub('IMG bg01\nIMG bg01d\n', 'BGL bg01d\n', txt)
txt = re.sub('IMG bg07\nIMG bg07\nIMG bg07b\n', 'BGL bg07b\n', txt)
txt = re.sub('IMG bg07\nIMG bg07c\n', 'BGL bg07c\n', txt)
txt = re.sub('IMG bg06\nIMG bg06b\n', 'BGL bg06b\n', txt)
txt = re.sub('IMG bg10\nIMG bg10d\n', 'BGL bg10d\n', txt)
txt = re.sub('IMG bg13\nIMG bg13c\n', 'BGL bg13c\n', txt)
txt = re.sub('IMG bg15\nIMG bg15b\n', 'BGL bg15b\n', txt)
txt = re.sub('IMG bg15\nIMG bg15c\n', 'BGL bg15c\n', txt)
txt = re.sub('IMG bg16\nIMG bg16b\n', 'BGL bg16b\n', txt)


# ---------------------------------------------------------------------------
# Hシーン差分
txt = re.sub('IMG ca031b\nIMG ca031a\n', 'HSC ca031a\n', txt)
txt = re.sub('IMG ca032b\nIMG ca032a\n', 'HSC ca032a\n', txt)
# Hシーン（１枚絵）
txt = re.sub('IMG ca026', 'HSC ca026', txt)
txt = re.sub('IMG ca027c\nIMG ca027b\nIMG ca027a\n', 'HSC ca027a\n', txt)
txt = re.sub('IMG ca027c\nIMG ca027b\n', 'HSC ca027b\n', txt)
txt = re.sub('IMG ca027c', 'HSC ca027c', txt)
txt = re.sub('IMG ca028', 'HSC ca028', txt)
txt = re.sub('IMG ca029', 'HSC ca029', txt)
txt = re.sub('IMG ca030', 'HSC ca030', txt)
txt = re.sub('IMG ca031a', 'HSC ca031a', txt)
txt = re.sub('IMG ca031b', 'HSC ca031b', txt)
txt = re.sub('IMG ca032a', 'HSC ca032a', txt)
txt = re.sub('IMG ca032b', 'HSC ca032b', txt)
txt = re.sub('IMG ca033', 'HSC ca033', txt)
txt = re.sub('IMG ca034', 'HSC ca034', txt)
txt = re.sub('IMG ca035a', 'HSC ca035a', txt)
txt = re.sub('IMG ca035b', 'HSC ca035b', txt)
txt = re.sub('IMG ca035c', 'HSC ca035c', txt)
txt = re.sub('IMG ca035d', 'HSC ca035d', txt)
txt = re.sub('IMG ca036', 'HSC ca036', txt)
txt = re.sub('IMG ca037', 'HSC ca037', txt)
txt = re.sub('IMG ca038a', 'HSC ca038a', txt)
txt = re.sub('IMG ca038b', 'HSC ca038b', txt)
txt = re.sub('IMG ca039', 'HSC ca039', txt)
txt = re.sub('IMG ca040', 'HSC ca040', txt)
txt = re.sub('IMG ca041', 'HSC ca041', txt)
txt = re.sub('IMG ca042', 'HSC ca042', txt)
txt = re.sub('IMG ca043', 'HSC ca043', txt)
txt = re.sub('IMG ca044', 'HSC ca044', txt)
txt = re.sub('IMG ca045a', 'HSC ca045a', txt)
txt = re.sub('IMG ca045b', 'HSC ca045b', txt)
txt = re.sub('IMG ca045c', 'HSC ca045c', txt)
txt = re.sub('IMG ca046', 'HSC ca046', txt)
txt = re.sub('IMG ca047', 'HSC ca047', txt)
txt = re.sub('IMG ca048', 'HSC ca048', txt)
txt = re.sub('IMG ca049', 'HSC ca049', txt)
txt = re.sub('IMG ca050', 'HSC ca050', txt)
txt = re.sub('IMG ca051a', 'HSC ca051a', txt)
txt = re.sub('IMG ca051b', 'HSC ca051b', txt)
txt = re.sub('IMG ca052a', 'HSC ca052a', txt)
txt = re.sub('IMG ca052b', 'HSC ca052b', txt)
txt = re.sub('IMG ca053', 'HSC ca053', txt)
txt = re.sub('IMG ca054', 'HSC ca054', txt)
txt = re.sub('IMG ca055', 'HSC ca055', txt)
txt = re.sub('IMG ca056', 'HSC ca056', txt)
txt = re.sub('IMG ca057', 'HSC ca057', txt)
txt = re.sub('IMG ca058', 'HSC ca058', txt)
txt = re.sub('IMG ca059', 'HSC ca059', txt)
txt = re.sub('IMG ca060', 'HSC ca060', txt)
txt = re.sub('IMG ca061', 'HSC ca061', txt)
txt = re.sub('IMG ca062', 'HSC ca062', txt)
txt = re.sub('IMG ca063', 'HSC ca063', txt)
txt = re.sub('IMG ca064', 'HSC ca064', txt)
txt = re.sub('IMG ca065', 'HSC ca065', txt)
txt = re.sub('IMG ca066', 'HSC ca066', txt)
txt = re.sub('IMG ca067', 'HSC ca067', txt)
txt = re.sub('IMG ca068', 'HSC ca068', txt)
txt = re.sub('IMG ca069', 'HSC ca069', txt)
txt = re.sub('IMG ca070', 'HSC ca070', txt)
txt = re.sub('IMG ca071', 'HSC ca071', txt)
txt = re.sub('IMG ca072', 'HSC ca072', txt)
txt = re.sub('IMG ca073', 'HSC ca073', txt)
txt = re.sub('IMG ca074', 'HSC ca074', txt)
txt = re.sub('IMG ca075', 'HSC ca075', txt)
txt = re.sub('IMG ca076', 'HSC ca076', txt)
txt = re.sub('IMG ca077', 'HSC ca077', txt)
txt = re.sub('IMG ca078a', 'HSC ca078a', txt)
txt = re.sub('IMG ca078b', 'HSC ca078b', txt)
txt = re.sub('IMG ca079', 'HSC ca079', txt)
txt = re.sub('IMG ca080', 'HSC ca080', txt)
txt = re.sub('IMG ca081', 'HSC ca081', txt)
txt = re.sub('IMG ca082', 'HSC ca082', txt)
txt = re.sub('IMG ca083a', 'HSC ca083a', txt)
txt = re.sub('IMG ca083b', 'HSC ca083b', txt)
txt = re.sub('IMG ca084', 'HSC ca084', txt)
txt = re.sub('IMG ca085', 'HSC ca085', txt)
txt = re.sub('IMG ca086', 'HSC ca086', txt)


# ---------------------------------------------------------------------------
# スクロール
txt = re.sub('IMG e020l\nIMG e020h\n', 'SCR e020 1\n', txt)
txt = re.sub('IMG e29bl\nIMG e29bh\n', 'SCR e29b 1\n', txt)
txt = re.sub('IMG bg12l\nIMG bg12h\n', 'SCR bg12 1\n', txt)
txt = re.sub('IMG e033l\nIMG e033h\nIMG e033l\nIMG e033h\n', 'SCR e033 1\nSCR e033 2\n', txt)
txt = re.sub('IMG e050l\nIMG e050h\n', 'SCR e050 1\n', txt)


# ---------------------------------------------------------------------------
# エンディング背景
txt = re.sub('IMG en00',   'CLR 7\nSET en00 3\nEFF 33', txt)
txt = re.sub('IMG en01',   'EFF 9\nSET en01 3\nEFF 33', txt)
txt = re.sub('IMG en02',   'EFF 9\nSET en02 3\nEFF 33', txt)
txt = re.sub('IMG en03',   'EFF 9\nSET en03 3\nEFF 33', txt)
txt = re.sub('IMG en4',    'EFF 9\nSET en4 3\nEFF 33', txt)
txt = re.sub('IMG en05a',  'EFF 9\nSET en05a 3\nEFF 33', txt)
txt = re.sub('IMG en05b',  'CLR 7\nSET en05b 3\nEFF 33', txt)
txt = re.sub('IMG en06',   'EFF 9\nSET en06 3\nEFF 33', txt)
txt = re.sub('IMG en07a1', 'EFF 9\nSET en07a1 3\nEFF 33', txt)
txt = re.sub('IMG en07a2', 'CLR 7\nSET en07a2 3\nEFF 33', txt)
txt = re.sub('IMG en07b',  'CLR 7\nSET en07b 3\nEFF 33', txt)
txt = re.sub('IMG en08',   'EFF 9\nSET en08 3\nEFF 33', txt)


# ---------------------------------------------------------------------------
# アイコン重複
txt = re.sub('IMG mini05\nIMG mini05\n', 'MIN mini05\n', txt)
# アイコン
txt = re.sub('IMG mini', 'MIN mini', txt)


# ---------------------------------------------------------------------------
# 一括返還
txt = re.sub('IMG ca', 'CHR ca', txt)
txt = re.sub('IMG bg', 'BGL bg', txt)
txt = re.sub('IMG s', 'BGL s', txt)
txt = re.sub('IMG e', 'BGL e', txt)


# ---------------------------------------------------------------------------
# 分岐操作
# シェルター探索
if(sys.argv[1] == "cs05_13.log"): txt = re.sub('LDS 5 39', 'LDS 5 16', txt)
if(sys.argv[1] == "cs05_16.log"): txt = re.sub('LDS 5 13', 'LDS 5 17', txt)
if(sys.argv[1] == "cs05_17.log"): txt = re.sub('LDS 5 13', 'LDS 5 18', txt)
if(sys.argv[1] == "cs05_18.log"): txt = re.sub('LDS 5 13', 'LDS 5 19', txt)
if(sys.argv[1] == "cs05_19.log"): txt = re.sub('LDS 5 14', 'LDS 5 21', txt)
if(sys.argv[1] == "cs05_21.log"): txt = re.sub('LDS 5 13', 'LDS 5 22', txt)
if(sys.argv[1] == "cs05_22.log"): txt = re.sub('LDS 5 23', 'LDS 5 24', txt)
if(sys.argv[1] == "cs05_24.log"): txt = re.sub('LDS 5 23', 'LDS 5 25', txt)
if(sys.argv[1] == "cs05_25.log"): txt = re.sub('LDS 5 23', 'LDS 5 26', txt)
if(sys.argv[1] == "cs05_26.log"): txt = re.sub('LDS 5 23', 'LDS 5 27', txt)
if(sys.argv[1] == "cs05_27.log"): txt = re.sub('LDS 5 23', 'LDS 5 28', txt)
if(sys.argv[1] == "cs05_28.log"): txt = re.sub('LDS 5 23', 'LDS 5 40', txt)
# レオナドーラ救出
if(sys.argv[1] == "cs22_13.log"): txt = re.sub('LDS 22 14', 'LDS 22 20', txt)
if(sys.argv[1] == "cs22_15.log"): txt = re.sub('LDS 22 10', 'LDS 22 19', txt)
if(sys.argv[1] == "cs22_18.log"): txt = re.sub('LDS 22 10', 'LDS 22 21', txt)
#エンディング
txt = re.sub('LDS 28 7', 'END', txt)


# ---------------------------------------------------------------------------
# ログで拾えず、不自然な演出を個別修正・・・


# 避ける演出のアイコン消去
txt = re.sub('ICO xtra0a\n', '', txt)


# 背景をキャラ表示に変更
# 商隊
txt = re.sub('BGL e004\n', 'CHR e004\n', txt)
# モンスター
txt = re.sub('BGL e019\n', 'CHR e019\n', txt)
# モンスター集団
txt = re.sub('BGL e019f\n', 'CHR e019f\n', txt)
# ガードロボ
txt = re.sub('BGL bg18\n', 'CHR bg18\n', txt)
# ハーパー博士
txt = re.sub('BGL e032\n', 'CHR e032\n', txt)
# ミィ
txt = re.sub('BGL e060a\n', 'CHR e060a\n', txt)
# ミィ
txt = re.sub('BGL e060a\n', 'CHR e060a\n', txt)
# アルファ
txt = re.sub('BGL e060b\n', 'CHR e060b\n', txt)


# 中央表示　ラビィとアンジェラハッキング
txt = re.sub('BGL e018a1\n', 'CLR 2\nSET e018a1 2\nEFF 33\n', txt)
txt = re.sub('BGL e018a2\n', 'CLR 2\nSET e018a2 2\nEFF 33\n', txt)
txt = re.sub('BGL e018b1\n', 'CLR 2\nSET e018b1 2\nEFF 33\n', txt)
txt = re.sub('BGL e018b2\n', 'CLR 2\nSET e018b2 2\nEFF 33\n', txt)
txt = re.sub('BGL e018c1\n', 'CLR 2\nSET e018c1 2\nEFF 33\n', txt)
txt = re.sub('BGL e018d1\n', 'CLR 2\nSET e018d1 2\nEFF 33\n', txt)
txt = re.sub('BGL e018e\n', 'CLR 2\nSET e018e 2\nEFF 33\n', txt)
txt = re.sub('BGL e018f\n', 'CLR 2\nSET e018f 2\nEFF 33\n', txt)


# レオナドーラ２人表示
txt = re.sub('CHR ca005a\nCHR ca006a\n', 'SET ca005a 4\nSET ca006a 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005a\nCHR ca006b\n', 'SET ca005a 4\nSET ca006b 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005a\nCHR ca006c\n', 'SET ca005a 4\nSET ca006c 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005b\nCHR ca006b\n', 'SET ca005b 4\nSET ca006b 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005c\nCHR ca006c\n', 'SET ca005c 4\nSET ca006c 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005c\nCHR ca006d\n', 'SET ca005c 4\nSET ca006d 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005d\nCHR ca006d\n', 'SET ca005d 4\nSET ca006d 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005e\nCHR ca006a\n', 'SET ca005e 4\nSET ca006a 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005e\nCHR ca006b\n', 'SET ca005e 4\nSET ca006b 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005e\nCHR ca006e\n', 'SET ca005e 4\nSET ca006e 5\nEFF 33\n', txt)
txt = re.sub('CHR ca005f\nCHR ca006f\n', 'SET ca005f 4\nSET ca006f 5\nEFF 33\n', txt)
# ミィとアルファ２人表示
txt = re.sub('CHR e060a\nCHR e060b\n', 'SET e060a 4\nSET e060b 5\nEFF 33\n', txt)


# 消去　プロローグコマンド
if(sys.argv[1] == "cs01_01.log"): txt = re.sub('BST\nBPL 10\nCHR can01z\nIMG mojibg\nIMG mojibg\nCHR can02z\nIMG mojibg\nCHR can03z\nIMG mojibg\nCHR can04z\nIMG mojibg\nCHR can05z\nIMG mojibg\nCHR can06z\nIMG mojibg\n', '', txt)
# インアウト枠　シェルター入口へ
if(sys.argv[1] == "cs01_03.log"): txt = re.sub('KEY\nEFF 4\n', 'KEY\nEFF 36\nEFF 11\n', txt)
# イリア消去　残りつづける為
if(sys.argv[1] == "cs01_06.log"): txt = re.sub('ICO kait0a\nMSG （げげげ', 'CLR 2\nEFF 33\nICO kait0a\nMSG （げげげ', txt)
# インアウト　カイト寝る
if(sys.argv[1] == "cs01_07.log"): txt = re.sub('BPL 19\n', 'EFF 36\nEFF 37\nBPL 19\n', txt)
# インアウト　アンジェラヘリから助ける
if(sys.argv[1] == "cs01_10.log"): txt = re.sub('ICO kait07\n', 'EFF 36\nEFF 37\nICO kait07\n', txt)
# イン　２人でカナンを探しに行く
if(sys.argv[1] == "cs01_11.log"): txt = re.sub('EFF 4', 'EFF 36', txt)
# アウト枠　２人でカナンを探しに行く
if(sys.argv[1] == "cs01_12.log"): txt = re.sub('EFF 4', 'EFF 11', txt)
# イン　シェルター入口へ
if(sys.argv[1] == "cs01_14.log"): txt = re.sub('KEY\nEFF 4\n', 'KEY\nEFF 36\n', txt)
# アウト枠　シェルター廊下内
if(sys.argv[1] == "cs01_15.log"): txt = re.sub('EFF 4', 'EFF 11', txt)
# 倉庫背景追加　コンピュータ壊れた
if(sys.argv[1] == "cs01_19.log"): txt = re.sub('CHR ca009b\n', 'BGL bg67c\nCHR ca009b\n', txt)
# インアウト　カイト悪夢
if(sys.argv[1] == "cs01_19.log"): txt = re.sub('EFF 4\n', 'EFF 4\nEFF 36\nEFF 37\n', txt)
# UD黒　アンジェラ水浴び復帰１
if(sys.argv[1] == "cs01_21.log"): txt = re.sub('EFF 6\nBST\n', 'EFF 9\nBST\n', txt)
# アウト枠　アンジェラ水浴び復帰２
if(sys.argv[1] == "cs01_21.log"): txt = re.sub('EFF 14', 'EFF 11', txt)
# イン黒＋消去
if(sys.argv[1] == "cs01_21.log"): txt = re.sub('EFF 4\nLDS', 'EFF 6\nLDS', txt)


# 残りつづけるニース消去
if(sys.argv[1] == "cs02_01.log"): txt = re.sub('LDS', 'CLR 2\nEFF 33\nLDS', txt)
# インアウト　ダイアナ登場
if(sys.argv[1] == "cs02_06.log"): txt = re.sub('CHR ca025a\n', 'EFF 36\nEFF 37\nCHR ca025a\n', txt)
# インアウト　商談中
if(sys.argv[1] == "cs02_07.log"): txt = re.sub('ICO xtra01\nMSG 「それじ', 'EFF 36\nEFF 37\nICO xtra01\nMSG 「それじ', txt)
# イン　商隊と別れる１
if(sys.argv[1] == "cs02_07.log"): txt = re.sub('EFF 4', 'EFF 36', txt)
# アウト枠　商隊と別れる２
if(sys.argv[1] == "cs02_08.log"): txt = re.sub('EFF 4', 'EFF 11', txt)
# イン　ラビィH導入
if(sys.argv[1] == "cs02_09.log"): txt = re.sub('EFF 9\n', 'EFF 36\nWAT 30\n', txt)
# 消去
if(sys.argv[1] == "cs02_10.log"): txt = re.sub('EFF 9\n', '', txt)
# 消去
if(sys.argv[1] == "cs02_11.log"): txt = re.sub('EFF 9\n', '', txt)
# 消去
if(sys.argv[1] == "cs02_12.log"): txt = re.sub('EFF 6\n', '', txt)
# UD黒＋アウト枠　ラビィH終了
if(sys.argv[1] == "cs02_13.log"): txt = re.sub('EFF 15\n', 'EFF 9\nWAT 30\nEFF 11\n', txt)
# インアウト枠　おばけ捜索１
if(sys.argv[1] == "cs02_14.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　おばけ捜索２
if(sys.argv[1] == "cs02_14.log"): txt = re.sub('EFF 9\n', 'EFF 36\nEFF 11\n', txt)
# ホワイトイン＋セット＋アウト　イリア攻撃おばけ
if(sys.argv[1] == "cs02_15.log"): txt = re.sub('BGL e005_\n', 'EFF 34\nSET e005_ 1\nEFF 35\n', txt)
# インアウト枠　シェルター探索
if(sys.argv[1] == "cs02_18.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　シェルター食糧庫
if(sys.argv[1] == "cs02_22.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　カイトの部屋へ
if(sys.argv[1] == "cs02_23.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# ホワイトインアウト　ヘリ落下エフェクト
if(sys.argv[1] == "cs03_03.log"): txt = re.sub('SSG 15\n', 'SSG 15\nEFF 34\nEFF 35\n', txt)
# インアウト枠　ヘリに移動
if(sys.argv[1] == "cs03_03.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# MIN消去　飛行機の死体
if(sys.argv[1] == "cs03_04.log"): txt = re.sub('SEL 怪物\nICO wolf09\n', 'SEL 怪物\nICO wolf09\nEFF 60\n', txt)
# インアウト枠　ファーと会話
if(sys.argv[1] == "cs03_04.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# イン　ファーと合流１
if(sys.argv[1] == "cs03_05.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nLDS', txt)
# アウト枠　ファーと合流２
if(sys.argv[1] == "cs03_06.log"): txt = re.sub('BPL 4\nEFF 4\n', 'BPL 4\nEFF 11\n', txt)
# インアウト枠　ファー歓迎会終了
if(sys.argv[1] == "cs03_06.log"): txt = re.sub('BFA\nEFF 4\n', 'BFA\nEFF 36\nEFF 11\n', txt)
# ニース消す　酔っぱいニース
if(sys.argv[1] == "cs03_07.log"): txt = re.sub('MSG ニースは大', 'CLR 2\nEFF 33\nMSG ニースは大', txt)
# UD黒　ニースとH
if(sys.argv[1] == "cs03_08.log"): txt = re.sub('EFF 6', 'EFF 9', txt)
# 消去
if(sys.argv[1] == "cs03_09.log"): txt = re.sub('EFF 9\n', '', txt)
# UD黒　ニースとH中
if(sys.argv[1] == "cs03_09.log"): txt = re.sub('EFF 6', 'EFF 9', txt)
# 消去
if(sys.argv[1] == "cs03_10.log"): txt = re.sub('EFF 9\n', '', txt)
# UD黒　ニースとH本番
if(sys.argv[1] == "cs03_10.log"): txt = re.sub('EFF 6', 'EFF 9', txt)
# 消去
if(sys.argv[1] == "cs03_11.log"): txt = re.sub('EFF 9\n', '', txt)
# UD黒　ニースとH終了
if(sys.argv[1] == "cs03_11.log"): txt = re.sub('EFF 6', 'EFF 9', txt)
# レオナドーラ退場
if(sys.argv[1] == "cs03_14.log"): txt = re.sub('ICO iria0c\nMSG 「ウルフィ、お', 'CLR 2\nCLR 3\nEFF 33\nICO iria0c\nMSG 「ウルフィ、お', txt)
# インアウト　レオナドーラ退場後
if(sys.argv[1] == "cs03_14.log"): txt = re.sub('LDS', 'EFF 36\nEFF 37\nLDS', txt)
# UD黒　ファーと夜空を見た後
if(sys.argv[1] == "cs03_16.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)


# 消去ラビィ　ファー迷子
if(sys.argv[1] == "cs04_01.log"): txt = re.sub('まかしとけ」\nKEY\n', 'まかしとけ」\nKEY\nCLR 2\nEFF 33\n', txt)
# 消去ファー　ファー洞窟へ
if(sys.argv[1] == "cs04_04.log"): txt = re.sub('SSG 21\nPTY pty003\n', 'CLR 2\nEFF 33\nSSG 21\nPTY pty003\n', txt)
# インアウト枠　全員洞窟へ
if(sys.argv[1] == "cs04_04.log"): txt = re.sub('EFF 4\nMSG', 'EFF 36\nEFF 11\nMSG', txt)
# 消去
if(sys.argv[1] == "cs04_04.log"): txt = re.sub('EFF 4\nBGL', 'BGL', txt)
# 落下エフェクト　ウルフィとブルー
if(sys.argv[1] == "cs04_08.log"): txt = re.sub('EFF 4', 'EFF 40', txt)
# ホワイトイン＋ウェイト＋消去＋アウト　カイン博士のライト
if(sys.argv[1] == "cs04_25.log"): txt = re.sub('EFF 3', 'EFF 34\nWAT 60\nCLR 7\nEFF 35', txt)
# UD＋フラッシュ　スタンガン
if(sys.argv[1] == "cs04_26.log"): txt = re.sub('MSG ばしい', 'CLR 2\nEFF 33\nEFF 41\nMSG ばしい', txt)
# インアウト枠　ウルフィ意識を失う
if(sys.argv[1] == "cs04_26.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ウルフィ仲間を探す
if(sys.argv[1] == "cs04_27.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# UDに変更　レオナ、カイトに攻撃
if(sys.argv[1] == "cs05_03.log"): txt = re.sub('BGL e003a2\n', 'SET e003a2 1\nEFF 33\n', txt)
# UDに変更　ドーラ、カイトに攻撃
if(sys.argv[1] == "cs05_03.log"): txt = re.sub('BGL e003b2\n', 'SET e003b2 1\nEFF 33\n', txt)
# UDに変更　ドーラ、カイトに攻撃
if(sys.argv[1] == "cs05_03.log"): txt = re.sub('BGL e003b\n', 'SET e003b 1\nEFF 33\n', txt)
# 消去矢
if(sys.argv[1] == "cs05_03.log"): txt = re.sub('胸に走り続けた。\nKEY\n', '胸に走り続けた。\nKEY\nEFF 60\n', txt)
# ２重文章消去　レオナドーラ銃を撃つ
if(sys.argv[1] == "cs05_08.log"): txt = re.sub('SSG 24\nKEY\nMSG ばーーーーーーーん\\\\eb\\\\b8\n', '', txt)
# インアウト枠　カイトとアンジェラ逃走
if(sys.argv[1] == "cs05_09.log"): txt = re.sub('EFF 4\nBGL', 'EFF 36\nEFF 11\nBGL', txt)
# MINを消去しない　カイトとアンジェラ手を繋ぐ
if(sys.argv[1] == "cs05_09.log"): txt = re.sub('CHR ca009a\nMIN', 'SET ca009a 4\nEFF 33\nMIN', txt)
# インアウト枠　アンジェラ洞窟発見
if(sys.argv[1] == "cs05_12.log"): txt = re.sub('BPL 19\nEFF 4\n', 'BPL 19\nEFF 36\nEFF 11\n', txt)
# 全角３個消去　ミラのミラはミラクルのミラ
if(sys.argv[1] == "cs05_21.log"): txt = re.sub('MSG 　　　', 'MSG ', txt)
# アイコン消去　カイト図書室で本を閲覧
if(sys.argv[1] == "cs05_26.log"): txt = re.sub('MSG 『Ｈｉ', 'EFF 60\nMSG 『Ｈｉ', txt)
# アイコン消去　医務室
if(sys.argv[1] == "cs05_27.log"): txt = re.sub('MSG 妻が', 'EFF 60\nMSG 妻が', txt)
# インアウト枠　ミラの部屋を出る
if(sys.argv[1] == "cs05_31.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# 消去　ミラH
if(sys.argv[1] == "cs05_33.log"): txt = re.sub('EFF 6\n', '', txt)
# UD黒＋アウト枠　ミラH終了
if(sys.argv[1] == "cs05_34.log"): txt = re.sub('EFF 15\n', 'EFF 9\nWAT 30\nEFF 11\n', txt)


# MIN消去　イリア、レオナ、ドーラ飲んべ中
if(sys.argv[1] == "cs06_03.log"): txt = re.sub('EFF 4\nBGL bg02\n', 'EFF 60\n', txt)
# キャラとアイコン消去　飲み会終了
if(sys.argv[1] == "cs06_04.log"): txt = re.sub('BST\nMSG い', 'BST\nCLR 2\nCLR 3\nEFF 33\nMSG い', txt)
# フラッシュ　キャシーの爪攻撃
if(sys.argv[1] == "cs06_06.log"): txt = re.sub('KEY\nMSG が、', 'KEY\nEFF 41\nMSG が、', txt)
# フラッシュ　キャシーの爪攻撃（正規表現２回）
if(sys.argv[1] == "cs06_06.log"): txt = re.sub('MSG バシッ', 'EFF 41\nMSG バシッ', txt)
# BGM消去　重複している。戦闘終了
if(sys.argv[1] == "cs06_07.log"): txt = re.sub('BST\nBPL 13\n', '', txt)
# インアウト枠　ファー誘拐される
if(sys.argv[1] == "cs06_07.log"): txt = re.sub('EFF 4\nLDS', 'EFF 4\nEFF 36\nEFF 11\nLDS', txt)
# インアウト枠　次の日
if(sys.argv[1] == "cs06_08.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# MIN消去　監視カメラ
if(sys.argv[1] == "cs07_07.log"): txt = re.sub('ん・・・」\nKEY\n', 'ん・・・」\nKEY\nEFF 60\n', txt)
# MIN消去　犬の死体
if(sys.argv[1] == "cs07_09.log"): txt = re.sub('ーっ」\nKEY\n', 'ーっ」\nKEY\nEFF 60\n', txt)
# MIN消去　羽の標本
if(sys.argv[1] == "cs07_10.log"): txt = re.sub('っている。\nKEY\n', 'っている。\nKEY\nEFF 60\n', txt)
# ホワイトインアウト、ホワイトインアウト　一瞬の羽の記憶
if(sys.argv[1] == "cs07_11.log"): txt = re.sub('BGL e028\nICO kait06\n', 'EFF 34\nCLR 7\nSET e028 1\nEFF 35\nWAT 60\nEFF 34\nSET bg44 1\nSET ca009b 4\nSET kait06 7\nSET mini12 8\nEFF 35\nICO kait06\n', txt)
# アンジェラ消去　混乱している
if(sys.argv[1] == "cs07_11.log"): txt = re.sub('SEL 話す\nICO angl0d\n', 'CLR 2\nEFF 33\nSEL 話す\nICO angl0d\n', txt)
# MIN消去　手とICO
if(sys.argv[1] == "cs07_11.log"): txt = re.sub('MSG 「・・・・・・\\\\eb\\\\c1」\nKEY\nMSG ・・', 'MSG 「・・・・・・\\\\eb\\\\c1」\nKEY\nEFF 60\nMSG ・・', txt)
# インアウト枠　カイト音の正体を調べる
if(sys.argv[1] == "cs07_11.log"): txt = re.sub('EFF 4\nSSG 21\n', 'EFF 36\nEFF 11\nSSG 21\n', txt)
# エルザ消去　カイトたちより逃走
if(sys.argv[1] == "cs07_12.log"): txt = re.sub('EFF 4\nBST\n', 'CLR 2\nEFF 33\nBST\n', txt)
# MIN消去　ベットの血
if(sys.argv[1] == "cs07_13.log"): txt = re.sub('ラ・・・」\nKEY\n', 'ラ・・・」\nKEY\nEFF 60\n', txt)


# MIN消去　野菜の話を商人と
if(sys.argv[1] == "cs08_02.log"): txt = re.sub('ICO xtra04\nMSG 「すまない', 'EFF 60\nICO xtra04\nMSG 「すまない', txt)
# インアウト枠　酒場の後のセイラム村
if(sys.argv[1] == "cs08_06.log"): txt = re.sub('BPL 17\nEFF 4\n', 'BPL 17\nEFF 36\nEFF 11\n', txt)
# インキャラアイコン消去アウト　ローズマリーに診てもらう
if(sys.argv[1] == "cs08_06.log"): txt = re.sub('LDS', 'EFF 36\nCLR 2\nEFF 37\nLDS', txt)
# 消去
if(sys.argv[1] == "cs08_10.log"): txt = re.sub('EFF 9\n', '', txt)
# 消去
if(sys.argv[1] == "cs08_10.log"): txt = re.sub('EFF 6\n', '', txt)
# UD黒＋アウト枠　ローズマリーH終了
if(sys.argv[1] == "cs08_12.log"): txt = re.sub('EFF 15\n', 'EFF 9\nWAT 30\nEFF 11\n', txt)
# インアウト枠　次の日
if(sys.argv[1] == "cs08_15.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# ミナ消去　酒場で情報収集
if(sys.argv[1] == "cs08_17.log"): txt = re.sub('SEL 見る\n', 'CLR 2\nEFF 33\nSEL 見る\n', txt)
# レジーナ消去　やっぱりいいんです
if(sys.argv[1] == "cs08_18.log"): txt = re.sub('ICO raby0d\n', 'CLR 2\nEFF 33\nICO raby0d\n', txt)
# インアウト枠　ドームへ出発
if(sys.argv[1] == "cs08_18.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ドーム付近
if(sys.argv[1] == "cs08_20.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# ディライア消去　ラビィと密談
if(sys.argv[1] == "cs08_22.log"): txt = re.sub('SSG 21\nPTY pty013\n', 'CLR 2\nEFF 33\nSSG 21\nPTY pty013\n', txt)
# インアウト枠　セイラム村に帰る
if(sys.argv[1] == "cs08_22.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# ダイアナ消去　ダンス後
if(sys.argv[1] == "cs08_24.log"): txt = re.sub('LDS', 'CLR 2\nEFF 33\nLDS', txt)
# インアウト枠　酒場会話後
if(sys.argv[1] == "cs08_25.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　夜中目を覚ます
if(sys.argv[1] == "cs08_26.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# UD黒　レジーナH
if(sys.argv[1] == "cs08_35.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# 消去
if(sys.argv[1] == "cs08_31.log"): txt = re.sub('EFF 9\n', '', txt)
# UD黒　レジーナH
if(sys.argv[1] == "cs08_31.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# アイコン消去＋フラッシュ＋ウェイト＋インアウト枠　レジーナH終了
if(sys.argv[1] == "cs08_31.log"): txt = re.sub('EFF 11\n', 'EFF 41\nWAT 30\nEFF 36\nEFF 11\n', txt)
# インアウト枠　ラビーと喧嘩
if(sys.argv[1] == "cs08_31.log"): txt = re.sub('LDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　部屋で夜ごはん
if(sys.argv[1] == "cs08_33.log"): txt = re.sub('EFF 4\nMSG', 'EFF 36\nEFF 11\nMSG', txt)
# インアウト枠　ラビィこっそり部屋出る
if(sys.argv[1] == "cs08_34.log"): txt = re.sub('EFF 4\nMSG', 'EFF 36\nEFF 11\nMSG', txt)
# インアウト枠　ラビィこっそり部屋出る
if(sys.argv[1] == "cs08_34.log"): txt = re.sub('EFF 4\nBGL bg05\n', 'EFF 36\nEFF 11\nBGL bg05\n', txt)


# インアウト枠　ドームに移動
if(sys.argv[1] == "cs09_04.log"): txt = re.sub('BPL 16\nEFF 4\n', 'BPL 16\nEFF 36\nEFF 11\n', txt)
# モンスター消去　倒される
if(sys.argv[1] == "cs09_06.log"): txt = re.sub('MSG 獣は自', 'CLR 2\nEFF 33\nMSG 獣は自', txt)
# インアウト枠　ラビィを探す
if(sys.argv[1] == "cs09_07.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　ビィの案内
if(sys.argv[1] == "cs09_08.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ビィの案内で医務室を目指す
if(sys.argv[1] == "cs09_09.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　地図を見て医務室を目指す
if(sys.argv[1] == "cs09_10.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　地図を見て医務室を目指す（ウルフィが）
if(sys.argv[1] == "cs09_13.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ウルフィ、モンスターを攻撃
if(sys.argv[1] == "cs09_14.log"): txt = re.sub('EFF 4\nBST\n', 'EFF 36\nEFF 11\nBST\n', txt)
# インアイコン消去アウト　廊下を駆け出す
if(sys.argv[1] == "cs09_14.log"): txt = re.sub('ICO nees05\n', 'EFF 36\nEFF 37\nICO nees05\n', txt)
# モンスター消去　倒される
if(sys.argv[1] == "cs09_17.log"): txt = re.sub('MSG ・・・・・・ずずん', 'CLR 2\nEFF 33\nMSG ・・・・・・ずずん', txt)
# ブルー消去　立ち去る
if(sys.argv[1] == "cs09_24.log"): txt = re.sub('MSG その背中', 'CLR 2\nEFF 33\nMSG その背中', txt)
# インアウト枠　ラビィを抱えて撤退中
if(sys.argv[1] == "cs09_24.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# ホワイトイン背景アウト　ドーム炎上
if(sys.argv[1] == "cs09_25.log"): txt = re.sub('BGL bg07b\n', 'EFF 34\nCLR 7\nSET bg07 1\nEFF 35\nBGL bg07b\n', txt)
# インアウト枠　村まで撤退
if(sys.argv[1] == "cs09_25.log"): txt = re.sub('EFF 4\nBGL bg05\nCHR ca001b\n', 'EFF 36\nEFF 11\nBGL bg05\nCHR ca001b\n', txt)
# インキャラ消去アウト　ニースと寝る
if(sys.argv[1] == "cs09_25.log"): txt = re.sub('MSG 翌朝、', 'EFF 36\nCLR 2\nEFF 37\nMSG 翌朝、', txt)
# UD表示　アンジェラ祈り１
if(sys.argv[1] == "cs09_27.log"): txt = re.sub('BGL e022b\n', 'SET e022b 1\nEFF 33\n', txt)
# UD表示　アンジェラ祈り２
if(sys.argv[1] == "cs09_27.log"): txt = re.sub('BGL e022b2\n', 'SET e022b2 1\nEFF 33\n', txt)
# UD表示　ウルフィ、アンジェラに近づく
if(sys.argv[1] == "cs09_27.log"): txt = re.sub('BGL e022c\n', 'SET e022c 1\nEFF 33\n', txt)
# UD表示　アンジェラ逃げる
if(sys.argv[1] == "cs09_27.log"): txt = re.sub('BGL e022d\n', 'SET e022d 1\nEFF 33\n', txt)


# インアウト枠　村から遠ざかる
if(sys.argv[1] == "cs10_04.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ウルフィから逃げる
if(sys.argv[1] == "cs10_09.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　祠に戻る
if(sys.argv[1] == "cs10_10.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ケガ人へ行く
if(sys.argv[1] == "cs10_13.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# インアウト枠　墓に移動
if(sys.argv[1] == "cs11_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ドームに移動
if(sys.argv[1] == "cs11_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# UD背景　ドーム探索で手をついだ後
if(sys.argv[1] == "cs12_02.log"): txt = re.sub('BGL bg07c\nLDS', 'CLR 2\nSET bg07c 1\nEFF 33\nLDS', txt)
# インアウト枠　青く光る方へ
if(sys.argv[1] == "cs12_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　洪水脱出
if(sys.argv[1] == "cs12_05.log"): txt = re.sub('EFF 4\nBST\n', 'EFF 36\nEFF 11\nBST\n', txt)


# インアウト枠　岸辺の夜
if(sys.argv[1] == "cs13_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　岸辺の朝
if(sys.argv[1] == "cs13_04.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# 消去　エルザH
if(sys.argv[1] == "cs13_07.log"): txt = re.sub('EFF 9\n', '', txt)
# 消去　エルザH
if(sys.argv[1] == "cs13_08.log"): txt = re.sub('EFF 9\n', '', txt)
# アイコン消去＋フラッシュ＋ウェイト＋インアウト枠　エルザH終了
if(sys.argv[1] == "cs13_10.log"): txt = re.sub('EFF 11\n', 'EFF 41\nWAT 30\nEFF 36\nEFF 11\n', txt)
# フラッシュ　スタンガン
if(sys.argv[1] == "cs13_12.log"): txt = re.sub('MSG ばしい', 'CLR 2\nEFF 33\nEFF 41\nMSG ばしい', txt)
# ティティ消去　ルゥリィ湖に墜落
if(sys.argv[1] == "cs13_14.log"): txt = re.sub('MSG ティティが慌', 'CLR 2\nEFF 33\nMSG ティティが慌', txt)
# インアウト枠　ルゥリィティティ泣いた後
if(sys.argv[1] == "cs13_15.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# 消去　ティティH
if(sys.argv[1] == "cs13_18.log"): txt = re.sub('EFF 9\n', '', txt)
# UD黒　ティティH（正規表現２回）
if(sys.argv[1] == "cs13_18.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# アイコン消去＋フラッシュ＋ウェイト＋インアウト枠　ティティH終了
if(sys.argv[1] == "cs13_18.log"): txt = re.sub('EFF 15\n', 'EFF 34\nCLR 7\nWAT 30\nEFF 35\nEFF 11\n', txt)
# インアウト枠　ルゥリィとティティ別れ
if(sys.argv[1] == "cs13_20.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ルゥリィとティティ別れ
if(sys.argv[1] == "cs13_21.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# 消去　ルゥリィH
if(sys.argv[1] == "cs13_27.log"): txt = re.sub('EFF 9\n', '', txt)
# 消去　ルゥリィH
if(sys.argv[1] == "cs13_29.log"): txt = re.sub('EFF 9\n', '', txt)
# インアウト枠　ルゥリィH終了
if(sys.argv[1] == "cs13_30.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　ディライアのテントへ
if(sys.argv[1] == "cs13_33.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　お茶飲む
if(sys.argv[1] == "cs13_34.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# BGM消去　ディライアH
if(sys.argv[1] == "cs13_38.log"): txt = re.sub('BST\nBPL 14\n', '', txt)
# アイコン消去＋フラッシュ＋ウェイト＋インアウト枠　ディライアH終了
if(sys.argv[1] == "cs13_39.log"): txt = re.sub('EFF 6\n', 'EFF 41\nWAT 30\nEFF 36\nEFF 11\n', txt)
# インアイコン消去アウト枠　いきさつを話す
if(sys.argv[1] == "cs13_40.log"): txt = re.sub('はじめた。\nKEY\n', 'はじめた。\nKEY\nEFF 36\nEFF 37\n', txt)
# インアウト枠　セイラム村へ
if(sys.argv[1] == "cs13_40.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# MIN消去　手を放す
if(sys.argv[1] == "cs14_01.log"): txt = re.sub('ICO angl22\n', 'EFF 60\nICO angl22\n', txt)
# インアウト枠　社の外
if(sys.argv[1] == "cs14_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　薬を手に入れる決意
if(sys.argv[1] == "cs14_02.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　セイラム村へ出発（正規表現２回）
if(sys.argv[1] == "cs14_03.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　セイラム村へ出発
if(sys.argv[1] == "cs14_03.log"): txt = re.sub('EFF 4\nSSG 21\n', 'EFF 36\nEFF 11\nSSG 21\n', txt)
# インアウト枠　セイラム村へ出発
if(sys.argv[1] == "cs14_03.log"): txt = re.sub('BST\nEFF 4\nBST\n', 'BST\nEFF 36\nEFF 11\nBST\n', txt)
# 商隊消去＋UD＋インアウト　ローズマリーの家へ
if(sys.argv[1] == "cs14_04.log"): txt = re.sub('MSG 僕は変異体に', 'CLR 2\nEFF 33\nEFF 36\nEFF 37\nMSG 僕は変異体に', txt)
# キャラ消去＋UD＋インアウト　酒場へ
if(sys.argv[1] == "cs14_04.log"): txt = re.sub('MSG 酒場に', 'CLR 2\nEFF 33\nEFF 36\nEFF 37\nMSG 酒場に', txt)
# アイコン消去＋インアウト　酒場へ
if(sys.argv[1] == "cs14_04.log"): txt = re.sub('LDS', 'EFF 36\nEFF 37\nLDS', txt)
# キャラ消去＋UD　ダイアナがミナ呼ぶ
if(sys.argv[1] == "cs14_05.log"): txt = re.sub('あげるわ」\nKEY\n', 'あげるわ」\nKEY\nCLR 2\nEFF 33\n', txt)
# キャラ消去＋UD　ミナの野菜スープ
if(sys.argv[1] == "cs14_05.log"): txt = re.sub('込んだ。\nKEY\n', '込んだ。\nKEY\nCLR 2\nEFF 33\n', txt)
# キャラ消去＋UD　酒場の外に出る
if(sys.argv[1] == "cs14_06.log"): txt = re.sub('EFF 4\n', 'CLR 2\nEFF 33\nEFF 4\n', txt)
# キャラ消去　アンジェラ混乱
if(sys.argv[1] == "cs14_09.log"): txt = re.sub('MSG アンジェラは跳', 'CLR 2\nEFF 33\nMSG アンジェラは跳', txt)
# フラッシュ１回　アンジェラの記憶導入
if(sys.argv[1] == "cs14_11.log"): txt = re.sub('ば・・・\\\\eb\\\\c3」\nKEY\n', 'ば・・・\\\\eb\\\\c3」\nKEY\nEFF 41\n', txt)
# フラッシュ３回　アンジェラの記憶導入
if(sys.argv[1] == "cs14_11.log"): txt = re.sub('ICO wolf07\nMSG 「・・', 'EFF 41\nEFF 41\nEFF 41\nICO wolf07\nMSG 「・・', txt)
# ホワイトイン＋ウェイト＋アウト枠　アンジェラの記憶
if(sys.argv[1] == "cs14_11.log"): txt = re.sub('EFF 4\nBST\n', 'EFF 34\nCLR 7\nSET waku06b 1\nWAT 60\nEFF 35\nBST\n', txt)
# フラッシュ３回　アンジェラの記憶戻る
if(sys.argv[1] == "cs14_11.log"): txt = re.sub('BPL 9\n', 'CLR 2\nEFF 41\nEFF 41\nEFF 41\nBPL 9\n', txt)


# キャラ消去＋UD　イリア先に行く
if(sys.argv[1] == "cs15_01.log"): txt = re.sub('SSG 21\n', 'CLR 2\nEFF 33\nSSG 21\n', txt)
# フラッシュ１回　アンジェラの記憶導入
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('ば・・・\\\\eb\\\\c3」\nKEY\n', 'ば・・・\\\\eb\\\\c3」\nKEY\nEFF 41\n', txt)
# フラッシュ３回　アンジェラの記憶導入
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('ICO wolf07\nMSG 「・・', 'EFF 41\nEFF 41\nEFF 41\nICO wolf07\nMSG 「・・', txt)
# ホワイトイン＋ウェイト＋アウト枠　アンジェラの記憶
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('EFF 4\nBST\n', 'EFF 34\nCLR 7\nSET waku06b 1\nWAT 60\nEFF 35\nBST\n', txt)
# 通常表示　ラビィの幻影
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('CHR ca002a1\n', 'SET ca002a1 4\nEFF 60\n', txt)
# ホワイトイン＋アウト枠　ウルフィの記憶戻る
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('ICO wolf0e\nMSG 「・・・・・・ラビィ」\n', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\nICO wolf0e\nMSG 「・・・・・・ラビィ」\n', txt)
# フラッシュ　キャシーにダメージ
if(sys.argv[1] == "cs15_09.log"): txt = re.sub('ICO kyas0e\n', 'CLR 2\nEFF 41\nICO kyas0e\n', txt)
# 姉妹キャラ表示　キャラ２人で乾杯
if(sys.argv[1] == "cs15_05.log"): txt = re.sub('CHR ca006b\n', 'SET ca006b 5\nEFF 33\n', txt)
# インキャラ消去アウト　イリア酔いがさめるまで待つ
if(sys.argv[1] == "cs15_05.log"): txt = re.sub('BPL 17\n', 'EFF 36\nCLR 2\nEFF 37\n', txt)
# キャラ消去　リリー立ち去る
if(sys.argv[1] == "cs15_07.log"): txt = re.sub('ICO wolf0a\nMSG 「・・・・・・」\nKEY\n', 'ICO wolf0a\nMSG 「・・・・・・」\nKEY\nCLR 2\nEFF 33\n', txt)
# キャラICO消去　キャシー退却
if(sys.argv[1] == "cs15_09.log"): txt = re.sub('BPL 10\n', 'CLR 2\nEFF 33\nBPL 10\n', txt)


# インアウト枠　セイラム村へ
if(sys.argv[1] == "cs16_02.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　セイラム村へ道中
if(sys.argv[1] == "cs16_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# キャラ消去　レジーナ
if(sys.argv[1] == "cs16_04.log"): txt = re.sub('ICO kait18\n', 'CLR 2\nEFF 33\nICO kait18\n', txt)
# キャラ消去　ウルフィ
if(sys.argv[1] == "cs16_05.log"): txt = re.sub('SSG 21\n', 'CLR 2\nEFF 33\nSSG 21\n', txt)
# インアウト枠　カイト寝る
if(sys.argv[1] == "cs16_06.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# キャラ消去　イリア酔っ払い１
if(sys.argv[1] == "cs16_07.log"): txt = re.sub('ICO iria42\n', 'CLR 2\nEFF 33\nICO iria42\n', txt)
# キャラ消去　イリア酔っ払い２
if(sys.argv[1] == "cs16_07.log"): txt = re.sub('倒れた。\nKEY\n', '倒れた。\nKEY\nCLR 2\nEFF 33\n', txt)
# インアウト枠　カイト治療
if(sys.argv[1] == "cs16_11.log"): txt = re.sub('して」\nKEY\n', 'して」\nKEY\nEFF 36\nCLR 2\nEFF 37\n', txt)
# インアウト枠　セイラム村で仲間紹介
if(sys.argv[1] == "cs16_11.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# イン　リリーH終了
if(sys.argv[1] == "cs16_17.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)
# BGM消去　リリーH後
if(sys.argv[1] == "cs16_18.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# キャラ消去　ミナ
if(sys.argv[1] == "cs16_18.log"): txt = re.sub('いいわ」\nKEY\n', 'いいわ」\nKEY\nCLR 2\nEFF 33\n', txt)
# キャラ消去　ミナ
if(sys.argv[1] == "cs16_18.log"): txt = re.sub('LDS', 'CLR 2\nEFF 33\nLDS', txt)
# キャラ消去　イリア
if(sys.argv[1] == "cs16_20.log"): txt = re.sub('ICO kait25', 'CLR 2\nEFF 33\nICO kait25', txt)


# 消去　イリアH
if(sys.argv[1] == "cs17_05.log"): txt = re.sub('EFF 9\n', '', txt)
# UD黒　イリアH
if(sys.argv[1] == "cs17_05.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# アイコン消去＋ホワイトイン＋ウェイト＋ホワイトアウト＋アウト枠　イリアH
if(sys.argv[1] == "cs17_05.log"): txt = re.sub('EFF 15\n', 'EFF 34\nCLR 7\nWAT 30\nEFF 35\nEFF 11\n', txt)
# アイコン消去＋インアウト　イリアH後寝る
if(sys.argv[1] == "cs17_05.log"): txt = re.sub('LDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　酒場へ
if(sys.argv[1] == "cs17_06.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# イン＋キャラ消去＋アウト　アンジェラのパーティ挨拶
if(sys.argv[1] == "cs17_07.log"): txt = re.sub('SSG 21\nPTY pty026\n', 'SSG 21\nPTY pty026\nEFF 36\nCLR 2\nEFF 37\n', txt)
# インアウト枠　宿屋の一室
if(sys.argv[1] == "cs17_07.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　アンジェラの状況説明
if(sys.argv[1] == "cs17_10.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# 消去　ダイアナH
if(sys.argv[1] == "cs17_16.log"): txt = re.sub('EFF 9\n', '', txt)
# UD黒　ダイアナH
if(sys.argv[1] == "cs17_16.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# UD黒　ダイアナH終了
if(sys.argv[1] == "cs17_16.log"): txt = re.sub('EFF 15\n', 'EFF 9\n', txt)
# UD黒　ダイアナとローズマリーH
if(sys.argv[1] == "cs17_17.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# 消去　ダイアナとローズマリーH
if(sys.argv[1] == "cs17_19.log"): txt = re.sub('EFF 9\n', '', txt)
# UD黒＋アウト枠　ダイアナとローズマリーH終了
if(sys.argv[1] == "cs17_20.log"): txt = re.sub('EFF 15\n', 'EFF 9\nEFF 11\n', txt)
# UD黒　ミナH
if(sys.argv[1] == "cs17_22.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# 消去　ミナH
if(sys.argv[1] == "cs17_23.log"): txt = re.sub('EFF 6\n', '', txt)
# UD黒＋アウト枠　ミナH終了
if(sys.argv[1] == "cs17_24.log"): txt = re.sub('EFF 15\n', 'EFF 9\nEFF 11\n', txt)
# 消去　ダイアナとミナH
if(sys.argv[1] == "cs17_25.log"): txt = re.sub('EFF 6\n', '', txt)
# 消去　ダイアナとミナH
if(sys.argv[1] == "cs17_26.log"): txt = re.sub('EFF 6\n', '', txt)
# UD黒＋アウト枠　ダイアナとミナH終了
if(sys.argv[1] == "cs17_27.log"): txt = re.sub('EFF 6\n', 'EFF 9\nEFF 11\n', txt)
# UD黒＋アウト枠　研究所に移動
if(sys.argv[1] == "cs17_30.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# MIN消去　犬の死体
if(sys.argv[1] == "cs17_33.log"): txt = re.sub('SEL 話す\nICO angl08\n', 'EFF 60\nSEL 話す\nICO angl08\n', txt)
# MIN消去　コンピュータ
if(sys.argv[1] == "cs17_35.log"): txt = re.sub('SEL 話す\nMSG 壁の', 'EFF 60\nSEL 話す\nMSG 壁の', txt)
# MIN消去　ラビィの宝石
if(sys.argv[1] == "cs17_37.log"): txt = re.sub('・・・）\nKEY\n', '・・・）\nKEY\nEFF 60\n', txt)
# インアウト枠　ディライアにイジュウインシティを案内してもらう
if(sys.argv[1] == "cs17_42.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ラビィを気長に待つ
if(sys.argv[1] == "cs17_45.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# フラッシュ３回　ラビィに
if(sys.argv[1] == "cs17_47.log"): txt = re.sub('MSG ばしいっ', 'EFF 41\nEFF 41\nEFF 41\nMSG ばしいっ', txt)
# 背景消去
if(sys.argv[1] == "cs17_47.log"): txt = re.sub('BGL bg47\nCHR ca007c2\nICO blue0a', 'CHR ca007c2\nICO blue0a', txt)
# アニメーション指定　ジャンプ命令を後編ROM指定
if(sys.argv[1] == "cs17_49.log"): txt = re.sub('LDS 18 1', 'END', txt)


# 消去　３箇所
if(sys.argv[1] == "cs18_01.log"): txt = re.sub('EFF 5\n', '', txt)
# インアウト枠　ラビィ一人でドームへ
if(sys.argv[1] == "cs18_01.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　ドームの中へ
if(sys.argv[1] == "cs18_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# UD黒　ビアトリスとキャシーH
if(sys.argv[1] == "cs18_03.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# 消去
if(sys.argv[1] == "cs18_04.log"): txt = re.sub('BST\nBPL 9\n', '', txt)
# 消去とHSC変更　ラビィさん問い詰め中
if(sys.argv[1] == "cs18_04.log"): txt = re.sub('EFF 9\nBGL e016\n', 'HSC e016\n', txt)
# インアウト枠　カイン止める
if(sys.argv[1] == "cs18_04.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　ラビィさん問い詰め終了
if(sys.argv[1] == "cs18_04.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　ラビィ寝る
if(sys.argv[1] == "cs18_05.log"): txt = re.sub('LDS', 'EFF 36\nEFF 11\nLDS', txt)
# カイン消去　ラビィと会話終了
if(sys.argv[1] == "cs18_07.log"): txt = re.sub('ねえー」\nKEY\n', 'ねえー」\nKEY\nCLR 2\nEFF 33\n', txt)
# 全角消去
if(sys.argv[1] == "cs18_08.log"): txt = re.sub('　　　　　　　　　レポート', '　レポート', txt)
# 全角消去
if(sys.argv[1] == "cs18_08.log"): txt = re.sub('　　　　渋滞時の抜け道ご案内　　　　』', '　渋滞時の抜け道ご案内』', txt)
# 背景変更　扉のラビィのハッキング１（衣装間違いの為。原作修正
if(sys.argv[1] == "cs18_08.log"): txt = re.sub('e018b2', 'e018b1', txt)
# 背景変更　扉のラビィのハッキング２（衣装間違いの為。原作修正
if(sys.argv[1] == "cs18_08.log"): txt = re.sub('e018a2', 'e018a1', txt)
# 背景モンスター変更　ラビィハッキング中の背後に
if(sys.argv[1] == "cs18_09.log"): txt = re.sub('MSG あたしはこの', 'SET bg45 2\nEFF 33\nMSG あたしはこの', txt)


# インアウト枠　ディライアの案内
if(sys.argv[1] == "cs19_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# 消去　ディライア負傷
if(sys.argv[1] == "cs19_02.log"): txt = re.sub('EFF 5\n', '', txt)
# インアウト枠　ディライアの案内
if(sys.argv[1] == "cs19_02.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　広大な台地
if(sys.argv[1] == "cs19_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　入口
if(sys.argv[1] == "cs19_04.log"): txt = re.sub('EFF 4\nSSG 21', 'EFF 36\nEFF 11\nSSG 21', txt)
# MIN消去　アメーバ
if(sys.argv[1] == "cs19_06.log"): txt = re.sub('MSG 我に返った', 'EFF 60\nMSG 我に返った', txt)
# MIN消去　鉄格子
if(sys.argv[1] == "cs19_08.log"): txt = re.sub('ICO kait17\nMSG 「すっ', 'EFF 60\nICO kait17\nMSG 「すっ', txt)


# インアウト枠　部屋に入る
if(sys.argv[1] == "cs20_05.log"): txt = re.sub('EFF 4\nBST', 'EFF 36\nEFF 11\nBST', txt)
# インアウト枠　風呂
if(sys.argv[1] == "cs20_05.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# MIN消去　クラゲ
if(sys.argv[1] == "cs20_07.log"): txt = re.sub('MSG 僕は意', 'EFF 60\nMSG 僕は意', txt)


# インアウト枠　Ａ級市民居住区の扉を開ける
if(sys.argv[1] == "cs21_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# 消去
if(sys.argv[1] == "cs21_02.log"): txt = re.sub('EFF 8\nBGL bg13\n', '', txt)
# MIN消去　カイト背中
if(sys.argv[1] == "cs21_05.log"): txt = re.sub('SEL 話す\nICO irih16\n', 'EFF 60\nSEL 話す\nICO irih16\n', txt)
# インアウト枠　ビィの会話終了
if(sys.argv[1] == "cs21_08.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　エルザの部屋扉前、地図を見て
if(sys.argv[1] == "cs21_09.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# MIN消去　イリアが扉の錠を壊す
if(sys.argv[1] == "cs21_10.log"): txt = re.sub('SSG 26\n', 'EFF 60\nSSG 26\n', txt)
# イン＋キャラ消去＋アウト枠　エルザに事情説明
if(sys.argv[1] == "cs21_10.log"): txt = re.sub('LDS', 'EFF 36\nCLR 2\nEFF 37\nLDS', txt)
# MIN消去　アンジェラとカイト手をつなぐ
if(sys.argv[1] == "cs21_12.log"): txt = re.sub('MSG アンジェラは僕', 'EFF 60\nMSG アンジェラは僕', txt)
# MIN消去　アンジェラ、エルザにキス
if(sys.argv[1] == "cs21_12.log"): txt = re.sub('ICO angl0f\nMSG 「それじゃ', 'EFF 60\nICO angl0f\nMSG 「それじゃ', txt)
# インアウト枠　エルザの部屋から出る
if(sys.argv[1] == "cs21_12.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# インアウト枠　誘導されてる（正規表現２回）
if(sys.argv[1] == "cs21_13.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　待ち受けている
if(sys.argv[1] == "cs21_13.log"): txt = re.sub('BST\nEFF 4\n', 'BST\nEFF 36\nEFF 11\n', txt)


# インアウト枠　コンピュータを探そう
if(sys.argv[1] == "cs22_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# MIN消去　アンジェラキス
if(sys.argv[1] == "cs22_04.log"): txt = re.sub('ICO angl05\nMSG 「これで', 'EFF 60\nICO angl05\nMSG 「これで', txt)
# インアウト枠　ハーパー博士の部屋を出る
if(sys.argv[1] == "cs22_09.log"): txt = re.sub('BST\nEFF 4\n', 'BST\nEFF 36\nEFF 11\n', txt)
# 消去　レオナH
if(sys.argv[1] == "cs22_13.log"): txt = re.sub('EFF 9\n', '', txt)
# 消去　レオナH
if(sys.argv[1] == "cs22_13.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# インアウト枠　レオナH終了
if(sys.argv[1] == "cs22_13.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)
# 消去　ドーラH
if(sys.argv[1] == "cs22_16.log"): txt = re.sub('EFF 6\n', '', txt)
# 消去　ドーラH
if(sys.argv[1] == "cs22_17.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# 消去　ドーラH
if(sys.argv[1] == "cs22_18.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)


# 消去　高い建物
if(sys.argv[1] == "cs23_01.log"): txt = re.sub('EFF 4\n', '', txt)
# UD表示　ファー（正規表現２回）
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('CHR ca010a\n', 'SET waku06b 1\nSET ca010a 2\nEFF 33\n', txt)
# UD表示　微笑みファー（正規表現３回）
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('CHR ca010c\n', 'SET waku06b 1\nSET ca010c 2\nEFF 33\n', txt)
# LR枠　ファー消去
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('EFF 12\n', 'EFF 4\n', txt)
# ウェイト　ウルフィ照準
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('MIN mini2f\nMIN mini2e\n', 'MIN mini2e\nWAT 60\nMIN mini2f\nWAT 60\n', txt)
# UD表示　ヴィアンカ（正規表現３回）
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('BGL e034a1\n', 'CLR 2\nSET e034a1 1\nEFF 33\n', txt)
# インアウト　ファー撃たれる
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('BPL 6\n', 'EFF 36\nCLR 7\nEFF 37\nBPL 6\n', txt)
# キー追加　ファー撃たれた後
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO wolf16', 'KEY\nICO wolf16', txt)
# キー追加　ファー撃たれた後
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO kait0a', 'KEY\nICO kait0a', txt)
# キー追加　ファー撃たれた後
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO iria19', 'KEY\nICO iria19', txt)
# キー追加　ファー撃たれた後
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO mira03', 'KEY\nICO mira03', txt)
# キー追加　ファー撃たれた後
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO nees1b', 'KEY\nICO nees1b', txt)
# キー追加　ファー撃たれた後
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO leon03', 'KEY\nICO leon03', txt)
# キー追加　ファー撃たれた後
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO dora0f', 'KEY\nICO dora0f', txt)
# キー追加＋ホワイトイン＋ウェイト＋アウト枠
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('EFF 4\nMSG ヴィアンカの銃', 'KEY\nEFF 34\nCLR 7\nWAT 30\nSET waku06b 1\nEFF 35\nMSG ヴィアンカの銃', txt)
# 消去（正規表現３回）
if(sys.argv[1] == "cs23_03.log"): txt = re.sub('EFF 5\n', '', txt)
# ホワイトイン＋ウェイト＋アウト枠　ラビィ光に包まれる
if(sys.argv[1] == "cs23_05.log"): txt = re.sub('CHR ca002g\n', 'EFF 34\nCLR 7\nWAT 30\nSET ca002g 1\nEFF 35\n', txt)
# キャラ消去　ラビィ融合
if(sys.argv[1] == "cs23_05.log"): txt = re.sub('BST\nMSG と、', 'CLR 2\nEFF 33\nBST\nMSG と、', txt)
# キャラ消去　ロボット兵
if(sys.argv[1] == "cs23_06.log"): txt = re.sub('ICO iria07\nMSG 「今のうち', 'CLR 2\nEFF 33\nICO iria07\nMSG 「今のうち', txt)
# フラッシュ　ウルフィにダメージ
if(sys.argv[1] == "cs23_06.log"): txt = re.sub('MSG ほっとした', 'EFF 41\nMSG ほっとした', txt)
# インアウト枠　ディライアの案内
if(sys.argv[1] == "cs23_06.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# キャラ消去　牢屋から脱出
if(sys.argv[1] == "cs23_11.log"): txt = re.sub('BST\nBPL 9', 'CLR 2\nEFF 33\nBST\nBPL 9', txt)
# フラッシュ　ウルフィにレーザー
if(sys.argv[1] == "cs23_11.log"): txt = re.sub('BST\nMSG', 'EFF 41\nBST\nMSG', txt)
# ホワイトインアウト枠
if(sys.argv[1] == "cs23_11.log"): txt = re.sub('EFF 4\nLDS', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\nLDS', txt)
# キャラ消去　ミィ
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('締めた・・・。\nKEY\n', '締めた・・・。\nKEY\nCLR 2\nEFF 33\n', txt)
# フラッシュ　キーワード
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('SSG 45\nMSG', 'SSG 45\nEFF 41\nMSG', txt)
# ホワイトインアウト枠　頭の中が真っ白
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 4\nEFF 12\n', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\n', txt)
# インアウト枠　ケガ治る
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('なんでもないよ・・・」\nKEY\n', 'なんでもないよ・・・」\nKEY\nEFF 36\nEFF 11\n', txt)
# インアウト枠　またね
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('またね、ウルフィ・・・」\nKEY\n', 'またね、ウルフィ・・・」\nKEY\nEFF 36\nEFF 11\n', txt)
# インアウト枠　力の増幅器説明
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　パンドラの森
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 4\nICO xtra49\n', 'EFF 36\nEFF 11\nICO xtra49\n', txt)
# インアウト枠　ビィ過去
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 12\nCHR ca010c\n', 'EFF 36\nEFF 11\nCHR ca010c\n', txt)
# ホワイトインアウト枠　地球
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 4\nLDS', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\nLDS', txt)
# MIN消去　ミズクラゲの代わり
if(sys.argv[1] == "cs23_14.log"): txt = re.sub('というわけや」\nKEY\n', 'というわけや」\nKEY\nEFF 60\n', txt)


# インアウト枠　アンジェラを救出に行く
if(sys.argv[1] == "cs24_02.log"): txt = re.sub('ね\\\\eb\\\\b4）\nKEY\nEFF 4\n', 'ね\\\\eb\\\\b4）\nKEY\nEFF 36\nEFF 11\n', txt)
# フラッシュ　アンジェラ思念
if(sys.argv[1] == "cs24_02.log"): txt = re.sub('ICO angl17\nMSG 「カイト', 'EFF 41\nICO angl17\nMSG 「カイト', txt)
# インアウト　アンジェラの呼び声
if(sys.argv[1] == "cs24_02.log"): txt = re.sub('響いていた。\nKEY\n', '響いていた。\nKEY\nEFF 36\nEFF 37\n', txt)
# 消去
if(sys.argv[1] == "cs24_03.log"): txt = re.sub('EFF 5\n', '', txt)
# インアウト枠　扉前
if(sys.argv[1] == "cs24_03.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)


# 消去
if(sys.argv[1] == "cs25_06.log"): txt = re.sub('EFF 5\n', '', txt)
# キャラ消去
if(sys.argv[1] == "cs25_08.log"): txt = re.sub('BPL 21\n', 'BPL 21\nCLR 2\nEFF 33\n', txt)


# インアウト枠　スザクの部屋へ
if(sys.argv[1] == "cs26_01.log"): txt = re.sub('EFF 4\nBST', 'EFF 36\nEFF 11\nBST', txt)
# フラッシュ　イリアの攻撃（正規表現３回）
if(sys.argv[1] == "cs26_02.log"): txt = re.sub('SSG 30\n', 'SSG 30\nEFF 41\n', txt)
# 消去
if(sys.argv[1] == "cs26_03.log"): txt = re.sub('EFF 5\n', '', txt)


# ホワイトインアウト枠　回想
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('EFF 4\nMSG 数時間前', 'EFF 34\nWAT 15\nCLR 7\nSET waku06b 1\nEFF 35\nMSG 数時間前', txt)
# ホワイトインアウト枠　回想終了（泣
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('EFF 4\nPTY pty048', 'EFF 34\nWAT 60\nCLR 7\nSET waku06b 1\nEFF 35\nPTY pty048', txt)
# アイコン変更　ウルフィ
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('BGL e049b\nICO wolf0e\n', 'ICO e049b\n', txt)
# アイコン変更　カイト
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('BGL e049a\nICO kait18\n', 'ICO e049a\n', txt)
# ホワイトインアウト枠　ファー降臨
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('EFF 7\n', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\n', txt)
# とどめ
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('BGL e007_\nBGL e012b2\n', 'BGL e007_\nWAT 100\nSET e012b2 1\nEFF 60\nWAT 20\nSET e007_ 1\nEFF 60\nWAT 20\nSET e012b2 1\nEFF 60\nWAT 20\nSET e007_ 1\nEFF 42\n', txt)
# フラッシュ３回　爆発（本来は５回だが眩しすぎる為）
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('MSG 同時に', 'EFF 41\nEFF 41\nEFF 41\nMSG 同時に', txt)
# ホワイトインアウト枠　戦闘終了
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('EFF 4\nPTY pty050\n', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\nPTY pty050\n', txt)


# キャラ消去　脱出するだけ
if(sys.argv[1] == "cs27_01.log"): txt = re.sub('SSG 21\nPTY pty048\n', 'CLR 2\nEFF 33\nSSG 21\nPTY pty048\n', txt)
# 消去（正規表現３回）
if(sys.argv[1] == "cs27_02.log"): txt = re.sub('EFF 5\n', '', txt)
# インアウト枠　イリアとブルー
if(sys.argv[1] == "cs27_02.log"): txt = re.sub('EFF 4\nEFF 10\n', 'EFF 36\nEFF 11\n', txt)
# インアウト枠　ブルーとカイン
if(sys.argv[1] == "cs27_02.log"): txt = re.sub('BST\nEFF 4\n', 'BST\nEFF 36\nEFF 11\n', txt)
# ホワイトインアウト　出口
if(sys.argv[1] == "cs27_02.log"): txt = re.sub('BGL bg37\n', 'EFF 34\nCLR 7\nSET bg37 1\nEFF 35\n', txt)


# インアウト枠　次の夜
if(sys.argv[1] == "cs28_01.log"): txt = re.sub('EFF 4\nSSG 21\n', 'EFF 36\nEFF 11\nSSG 21\n', txt)
# UD黒　ラビィH１
if(sys.argv[1] == "cs28_02.log"): txt = re.sub('EFF 6\nHSC ca082\n', 'EFF 9\nHSC ca082\n', txt)
# UD黒　ラビィH２
if(sys.argv[1] == "cs28_02.log"): txt = re.sub('EFF 6\nMSG 俺は', 'EFF 9\nMSG 俺は', txt)
# UD黒　ラビィH３
if(sys.argv[1] == "cs28_02.log"): txt = re.sub('EFF 6\nHSC ca083a\n', 'EFF 9\nHSC ca083a\n', txt)
# ホワイトインアウト　ラビィH終了
if(sys.argv[1] == "cs28_02.log"): txt = re.sub('EFF 6\nLDS', 'EFF 34\nCLR 7\nWAT 30\nEFF 35\nLDS', txt)
# UD黒　アンジェラH１
if(sys.argv[1] == "cs28_04.log"): txt = re.sub('EFF 6\nHSC ca085\n', 'EFF 9\nHSC ca085\n', txt)
# UD黒　アンジェラH２
if(sys.argv[1] == "cs28_04.log"): txt = re.sub('EFF 6\nHSC ca086\n', 'EFF 9\nHSC ca086\n', txt)
# ホワイトインアウト　アンジェラH終了
if(sys.argv[1] == "cs28_04.log"): txt = re.sub('EFF 6\nLDS', 'EFF 34\nCLR 7\nSET waku06b 1\nWAT 30\nEFF 35\nLDS', txt)
# 消去
if(sys.argv[1] == "cs28_06.log"): txt = re.sub('EFF 6\n', '', txt)


# ---------------------------------------------------------------------------

with open(sys.argv[2], "w") as f:
	f.write(txt)

