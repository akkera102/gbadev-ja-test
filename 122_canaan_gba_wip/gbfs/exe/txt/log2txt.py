# coding: cp932
# �X�N���v�g���O�𐳋K�\���ɂĒu��
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
# �g���q����
txt = re.sub('\\.g', '', txt)
txt = re.sub('\\.lsp', '', txt)

# ���t�R�}���h�d��
txt = re.sub('BST\nBST\nBST\n', 'BST\n', txt)
txt = re.sub('BST\nBST\n', 'BST\n', txt)

# ���t�R�}���h24�i�p�^�p�^�A�j���ȁj
txt = re.sub('BPL 24\n', '', txt)

# ���ʉ��Đ����̕s�v�e�L�X�g
txt = re.sub('MSG \n', '', txt)

# ---------------------------------------------------------------------------
# �p�^�p�^�A�j��
# 1:�E���t�B���J�C�g
# 2:�J�C�g�@���E���t�B
# 3:�E���t�B���E���t�B
# 4:�J�C�g�@���J�C�g
# 5:�E���t�B�����r�B
# 6:���r�B�@���E���t�B

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
# �p�[�e�B
txt = re.sub('IMG pty000\n', '', txt)
txt = re.sub('IMG pty', 'PTY pty', txt)


# ---------------------------------------------------------------------------
# �G�t�F�N�g
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
# �L�����A�C�R��
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
# �L���������G�i�A���t�@����j
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
# �w�i����
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
# H�V�[������
txt = re.sub('IMG ca031b\nIMG ca031a\n', 'HSC ca031a\n', txt)
txt = re.sub('IMG ca032b\nIMG ca032a\n', 'HSC ca032a\n', txt)
# H�V�[���i�P���G�j
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
# �X�N���[��
txt = re.sub('IMG e020l\nIMG e020h\n', 'SCR e020 1\n', txt)
txt = re.sub('IMG e29bl\nIMG e29bh\n', 'SCR e29b 1\n', txt)
txt = re.sub('IMG bg12l\nIMG bg12h\n', 'SCR bg12 1\n', txt)
txt = re.sub('IMG e033l\nIMG e033h\nIMG e033l\nIMG e033h\n', 'SCR e033 1\nSCR e033 2\n', txt)
txt = re.sub('IMG e050l\nIMG e050h\n', 'SCR e050 1\n', txt)


# ---------------------------------------------------------------------------
# �G���f�B���O�w�i
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
# �A�C�R���d��
txt = re.sub('IMG mini05\nIMG mini05\n', 'MIN mini05\n', txt)
# �A�C�R��
txt = re.sub('IMG mini', 'MIN mini', txt)


# ---------------------------------------------------------------------------
# �ꊇ�Ԋ�
txt = re.sub('IMG ca', 'CHR ca', txt)
txt = re.sub('IMG bg', 'BGL bg', txt)
txt = re.sub('IMG s', 'BGL s', txt)
txt = re.sub('IMG e', 'BGL e', txt)


# ---------------------------------------------------------------------------
# ���򑀍�
# �V�F���^�[�T��
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
# ���I�i�h�[���~�o
if(sys.argv[1] == "cs22_13.log"): txt = re.sub('LDS 22 14', 'LDS 22 20', txt)
if(sys.argv[1] == "cs22_15.log"): txt = re.sub('LDS 22 10', 'LDS 22 19', txt)
if(sys.argv[1] == "cs22_18.log"): txt = re.sub('LDS 22 10', 'LDS 22 21', txt)
#�G���f�B���O
txt = re.sub('LDS 28 7', 'END', txt)


# ---------------------------------------------------------------------------
# ���O�ŏE�����A�s���R�ȉ��o���ʏC���E�E�E


# �����鉉�o�̃A�C�R������
txt = re.sub('ICO xtra0a\n', '', txt)


# �w�i���L�����\���ɕύX
# ����
txt = re.sub('BGL e004\n', 'CHR e004\n', txt)
# �����X�^�[
txt = re.sub('BGL e019\n', 'CHR e019\n', txt)
# �����X�^�[�W�c
txt = re.sub('BGL e019f\n', 'CHR e019f\n', txt)
# �K�[�h���{
txt = re.sub('BGL bg18\n', 'CHR bg18\n', txt)
# �n�[�p�[���m
txt = re.sub('BGL e032\n', 'CHR e032\n', txt)
# �~�B
txt = re.sub('BGL e060a\n', 'CHR e060a\n', txt)
# �~�B
txt = re.sub('BGL e060a\n', 'CHR e060a\n', txt)
# �A���t�@
txt = re.sub('BGL e060b\n', 'CHR e060b\n', txt)


# �����\���@���r�B�ƃA���W�F���n�b�L���O
txt = re.sub('BGL e018a1\n', 'CLR 2\nSET e018a1 2\nEFF 33\n', txt)
txt = re.sub('BGL e018a2\n', 'CLR 2\nSET e018a2 2\nEFF 33\n', txt)
txt = re.sub('BGL e018b1\n', 'CLR 2\nSET e018b1 2\nEFF 33\n', txt)
txt = re.sub('BGL e018b2\n', 'CLR 2\nSET e018b2 2\nEFF 33\n', txt)
txt = re.sub('BGL e018c1\n', 'CLR 2\nSET e018c1 2\nEFF 33\n', txt)
txt = re.sub('BGL e018d1\n', 'CLR 2\nSET e018d1 2\nEFF 33\n', txt)
txt = re.sub('BGL e018e\n', 'CLR 2\nSET e018e 2\nEFF 33\n', txt)
txt = re.sub('BGL e018f\n', 'CLR 2\nSET e018f 2\nEFF 33\n', txt)


# ���I�i�h�[���Q�l�\��
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
# �~�B�ƃA���t�@�Q�l�\��
txt = re.sub('CHR e060a\nCHR e060b\n', 'SET e060a 4\nSET e060b 5\nEFF 33\n', txt)


# �����@�v�����[�O�R�}���h
if(sys.argv[1] == "cs01_01.log"): txt = re.sub('BST\nBPL 10\nCHR can01z\nIMG mojibg\nIMG mojibg\nCHR can02z\nIMG mojibg\nCHR can03z\nIMG mojibg\nCHR can04z\nIMG mojibg\nCHR can05z\nIMG mojibg\nCHR can06z\nIMG mojibg\n', '', txt)
# �C���A�E�g�g�@�V�F���^�[������
if(sys.argv[1] == "cs01_03.log"): txt = re.sub('KEY\nEFF 4\n', 'KEY\nEFF 36\nEFF 11\n', txt)
# �C���A�����@�c��Â����
if(sys.argv[1] == "cs01_06.log"): txt = re.sub('ICO kait0a\nMSG �i������', 'CLR 2\nEFF 33\nICO kait0a\nMSG �i������', txt)
# �C���A�E�g�@�J�C�g�Q��
if(sys.argv[1] == "cs01_07.log"): txt = re.sub('BPL 19\n', 'EFF 36\nEFF 37\nBPL 19\n', txt)
# �C���A�E�g�@�A���W�F���w�����珕����
if(sys.argv[1] == "cs01_10.log"): txt = re.sub('ICO kait07\n', 'EFF 36\nEFF 37\nICO kait07\n', txt)
# �C���@�Q�l�ŃJ�i����T���ɍs��
if(sys.argv[1] == "cs01_11.log"): txt = re.sub('EFF 4', 'EFF 36', txt)
# �A�E�g�g�@�Q�l�ŃJ�i����T���ɍs��
if(sys.argv[1] == "cs01_12.log"): txt = re.sub('EFF 4', 'EFF 11', txt)
# �C���@�V�F���^�[������
if(sys.argv[1] == "cs01_14.log"): txt = re.sub('KEY\nEFF 4\n', 'KEY\nEFF 36\n', txt)
# �A�E�g�g�@�V�F���^�[�L����
if(sys.argv[1] == "cs01_15.log"): txt = re.sub('EFF 4', 'EFF 11', txt)
# �q�ɔw�i�ǉ��@�R���s���[�^��ꂽ
if(sys.argv[1] == "cs01_19.log"): txt = re.sub('CHR ca009b\n', 'BGL bg67c\nCHR ca009b\n', txt)
# �C���A�E�g�@�J�C�g����
if(sys.argv[1] == "cs01_19.log"): txt = re.sub('EFF 4\n', 'EFF 4\nEFF 36\nEFF 37\n', txt)
# UD���@�A���W�F�������ѕ��A�P
if(sys.argv[1] == "cs01_21.log"): txt = re.sub('EFF 6\nBST\n', 'EFF 9\nBST\n', txt)
# �A�E�g�g�@�A���W�F�������ѕ��A�Q
if(sys.argv[1] == "cs01_21.log"): txt = re.sub('EFF 14', 'EFF 11', txt)
# �C�����{����
if(sys.argv[1] == "cs01_21.log"): txt = re.sub('EFF 4\nLDS', 'EFF 6\nLDS', txt)


# �c��Â���j�[�X����
if(sys.argv[1] == "cs02_01.log"): txt = re.sub('LDS', 'CLR 2\nEFF 33\nLDS', txt)
# �C���A�E�g�@�_�C�A�i�o��
if(sys.argv[1] == "cs02_06.log"): txt = re.sub('CHR ca025a\n', 'EFF 36\nEFF 37\nCHR ca025a\n', txt)
# �C���A�E�g�@���k��
if(sys.argv[1] == "cs02_07.log"): txt = re.sub('ICO xtra01\nMSG �u���ꂶ', 'EFF 36\nEFF 37\nICO xtra01\nMSG �u���ꂶ', txt)
# �C���@�����ƕʂ��P
if(sys.argv[1] == "cs02_07.log"): txt = re.sub('EFF 4', 'EFF 36', txt)
# �A�E�g�g�@�����ƕʂ��Q
if(sys.argv[1] == "cs02_08.log"): txt = re.sub('EFF 4', 'EFF 11', txt)
# �C���@���r�BH����
if(sys.argv[1] == "cs02_09.log"): txt = re.sub('EFF 9\n', 'EFF 36\nWAT 30\n', txt)
# ����
if(sys.argv[1] == "cs02_10.log"): txt = re.sub('EFF 9\n', '', txt)
# ����
if(sys.argv[1] == "cs02_11.log"): txt = re.sub('EFF 9\n', '', txt)
# ����
if(sys.argv[1] == "cs02_12.log"): txt = re.sub('EFF 6\n', '', txt)
# UD���{�A�E�g�g�@���r�BH�I��
if(sys.argv[1] == "cs02_13.log"): txt = re.sub('EFF 15\n', 'EFF 9\nWAT 30\nEFF 11\n', txt)
# �C���A�E�g�g�@���΂��{���P
if(sys.argv[1] == "cs02_14.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@���΂��{���Q
if(sys.argv[1] == "cs02_14.log"): txt = re.sub('EFF 9\n', 'EFF 36\nEFF 11\n', txt)
# �z���C�g�C���{�Z�b�g�{�A�E�g�@�C���A�U�����΂�
if(sys.argv[1] == "cs02_15.log"): txt = re.sub('BGL e005_\n', 'EFF 34\nSET e005_ 1\nEFF 35\n', txt)
# �C���A�E�g�g�@�V�F���^�[�T��
if(sys.argv[1] == "cs02_18.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�V�F���^�[�H�ƌ�
if(sys.argv[1] == "cs02_22.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�J�C�g�̕�����
if(sys.argv[1] == "cs02_23.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# �z���C�g�C���A�E�g�@�w�������G�t�F�N�g
if(sys.argv[1] == "cs03_03.log"): txt = re.sub('SSG 15\n', 'SSG 15\nEFF 34\nEFF 35\n', txt)
# �C���A�E�g�g�@�w���Ɉړ�
if(sys.argv[1] == "cs03_03.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# MIN�����@��s�@�̎���
if(sys.argv[1] == "cs03_04.log"): txt = re.sub('SEL ����\nICO wolf09\n', 'SEL ����\nICO wolf09\nEFF 60\n', txt)
# �C���A�E�g�g�@�t�@�[�Ɖ�b
if(sys.argv[1] == "cs03_04.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# �C���@�t�@�[�ƍ����P
if(sys.argv[1] == "cs03_05.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nLDS', txt)
# �A�E�g�g�@�t�@�[�ƍ����Q
if(sys.argv[1] == "cs03_06.log"): txt = re.sub('BPL 4\nEFF 4\n', 'BPL 4\nEFF 11\n', txt)
# �C���A�E�g�g�@�t�@�[���}��I��
if(sys.argv[1] == "cs03_06.log"): txt = re.sub('BFA\nEFF 4\n', 'BFA\nEFF 36\nEFF 11\n', txt)
# �j�[�X�����@�����ς��j�[�X
if(sys.argv[1] == "cs03_07.log"): txt = re.sub('MSG �j�[�X�͑�', 'CLR 2\nEFF 33\nMSG �j�[�X�͑�', txt)
# UD���@�j�[�X��H
if(sys.argv[1] == "cs03_08.log"): txt = re.sub('EFF 6', 'EFF 9', txt)
# ����
if(sys.argv[1] == "cs03_09.log"): txt = re.sub('EFF 9\n', '', txt)
# UD���@�j�[�X��H��
if(sys.argv[1] == "cs03_09.log"): txt = re.sub('EFF 6', 'EFF 9', txt)
# ����
if(sys.argv[1] == "cs03_10.log"): txt = re.sub('EFF 9\n', '', txt)
# UD���@�j�[�X��H�{��
if(sys.argv[1] == "cs03_10.log"): txt = re.sub('EFF 6', 'EFF 9', txt)
# ����
if(sys.argv[1] == "cs03_11.log"): txt = re.sub('EFF 9\n', '', txt)
# UD���@�j�[�X��H�I��
if(sys.argv[1] == "cs03_11.log"): txt = re.sub('EFF 6', 'EFF 9', txt)
# ���I�i�h�[���ޏ�
if(sys.argv[1] == "cs03_14.log"): txt = re.sub('ICO iria0c\nMSG �u�E���t�B�A��', 'CLR 2\nCLR 3\nEFF 33\nICO iria0c\nMSG �u�E���t�B�A��', txt)
# �C���A�E�g�@���I�i�h�[���ޏ��
if(sys.argv[1] == "cs03_14.log"): txt = re.sub('LDS', 'EFF 36\nEFF 37\nLDS', txt)
# UD���@�t�@�[�Ɩ���������
if(sys.argv[1] == "cs03_16.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)


# �������r�B�@�t�@�[���q
if(sys.argv[1] == "cs04_01.log"): txt = re.sub('�܂����Ƃ��v\nKEY\n', '�܂����Ƃ��v\nKEY\nCLR 2\nEFF 33\n', txt)
# �����t�@�[�@�t�@�[���A��
if(sys.argv[1] == "cs04_04.log"): txt = re.sub('SSG 21\nPTY pty003\n', 'CLR 2\nEFF 33\nSSG 21\nPTY pty003\n', txt)
# �C���A�E�g�g�@�S�����A��
if(sys.argv[1] == "cs04_04.log"): txt = re.sub('EFF 4\nMSG', 'EFF 36\nEFF 11\nMSG', txt)
# ����
if(sys.argv[1] == "cs04_04.log"): txt = re.sub('EFF 4\nBGL', 'BGL', txt)
# �����G�t�F�N�g�@�E���t�B�ƃu���[
if(sys.argv[1] == "cs04_08.log"): txt = re.sub('EFF 4', 'EFF 40', txt)
# �z���C�g�C���{�E�F�C�g�{�����{�A�E�g�@�J�C�����m�̃��C�g
if(sys.argv[1] == "cs04_25.log"): txt = re.sub('EFF 3', 'EFF 34\nWAT 60\nCLR 7\nEFF 35', txt)
# UD�{�t���b�V���@�X�^���K��
if(sys.argv[1] == "cs04_26.log"): txt = re.sub('MSG �΂���', 'CLR 2\nEFF 33\nEFF 41\nMSG �΂���', txt)
# �C���A�E�g�g�@�E���t�B�ӎ�������
if(sys.argv[1] == "cs04_26.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�E���t�B���Ԃ�T��
if(sys.argv[1] == "cs04_27.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# UD�ɕύX�@���I�i�A�J�C�g�ɍU��
if(sys.argv[1] == "cs05_03.log"): txt = re.sub('BGL e003a2\n', 'SET e003a2 1\nEFF 33\n', txt)
# UD�ɕύX�@�h�[���A�J�C�g�ɍU��
if(sys.argv[1] == "cs05_03.log"): txt = re.sub('BGL e003b2\n', 'SET e003b2 1\nEFF 33\n', txt)
# UD�ɕύX�@�h�[���A�J�C�g�ɍU��
if(sys.argv[1] == "cs05_03.log"): txt = re.sub('BGL e003b\n', 'SET e003b 1\nEFF 33\n', txt)
# ������
if(sys.argv[1] == "cs05_03.log"): txt = re.sub('���ɑ��葱�����B\nKEY\n', '���ɑ��葱�����B\nKEY\nEFF 60\n', txt)
# �Q�d���͏����@���I�i�h�[���e������
if(sys.argv[1] == "cs05_08.log"): txt = re.sub('SSG 24\nKEY\nMSG �΁[�[�[�[�[�[�[��\\\\eb\\\\b8\n', '', txt)
# �C���A�E�g�g�@�J�C�g�ƃA���W�F������
if(sys.argv[1] == "cs05_09.log"): txt = re.sub('EFF 4\nBGL', 'EFF 36\nEFF 11\nBGL', txt)
# MIN���������Ȃ��@�J�C�g�ƃA���W�F������q��
if(sys.argv[1] == "cs05_09.log"): txt = re.sub('CHR ca009a\nMIN', 'SET ca009a 4\nEFF 33\nMIN', txt)
# �C���A�E�g�g�@�A���W�F�����A����
if(sys.argv[1] == "cs05_12.log"): txt = re.sub('BPL 19\nEFF 4\n', 'BPL 19\nEFF 36\nEFF 11\n', txt)
# �S�p�R�����@�~���̃~���̓~���N���̃~��
if(sys.argv[1] == "cs05_21.log"): txt = re.sub('MSG �@�@�@', 'MSG ', txt)
# �A�C�R�������@�J�C�g�}�����Ŗ{���{��
if(sys.argv[1] == "cs05_26.log"): txt = re.sub('MSG �w�g��', 'EFF 60\nMSG �w�g��', txt)
# �A�C�R�������@�㖱��
if(sys.argv[1] == "cs05_27.log"): txt = re.sub('MSG �Ȃ�', 'EFF 60\nMSG �Ȃ�', txt)
# �C���A�E�g�g�@�~���̕������o��
if(sys.argv[1] == "cs05_31.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# �����@�~��H
if(sys.argv[1] == "cs05_33.log"): txt = re.sub('EFF 6\n', '', txt)
# UD���{�A�E�g�g�@�~��H�I��
if(sys.argv[1] == "cs05_34.log"): txt = re.sub('EFF 15\n', 'EFF 9\nWAT 30\nEFF 11\n', txt)


# MIN�����@�C���A�A���I�i�A�h�[������ג�
if(sys.argv[1] == "cs06_03.log"): txt = re.sub('EFF 4\nBGL bg02\n', 'EFF 60\n', txt)
# �L�����ƃA�C�R�������@���݉�I��
if(sys.argv[1] == "cs06_04.log"): txt = re.sub('BST\nMSG ��', 'BST\nCLR 2\nCLR 3\nEFF 33\nMSG ��', txt)
# �t���b�V���@�L���V�[�̒܍U��
if(sys.argv[1] == "cs06_06.log"): txt = re.sub('KEY\nMSG ���A', 'KEY\nEFF 41\nMSG ���A', txt)
# �t���b�V���@�L���V�[�̒܍U���i���K�\���Q��j
if(sys.argv[1] == "cs06_06.log"): txt = re.sub('MSG �o�V�b', 'EFF 41\nMSG �o�V�b', txt)
# BGM�����@�d�����Ă���B�퓬�I��
if(sys.argv[1] == "cs06_07.log"): txt = re.sub('BST\nBPL 13\n', '', txt)
# �C���A�E�g�g�@�t�@�[�U�������
if(sys.argv[1] == "cs06_07.log"): txt = re.sub('EFF 4\nLDS', 'EFF 4\nEFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@���̓�
if(sys.argv[1] == "cs06_08.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# MIN�����@�Ď��J����
if(sys.argv[1] == "cs07_07.log"): txt = re.sub('��E�E�E�v\nKEY\n', '��E�E�E�v\nKEY\nEFF 60\n', txt)
# MIN�����@���̎���
if(sys.argv[1] == "cs07_09.log"): txt = re.sub('�[���v\nKEY\n', '�[���v\nKEY\nEFF 60\n', txt)
# MIN�����@�H�̕W�{
if(sys.argv[1] == "cs07_10.log"): txt = re.sub('���Ă���B\nKEY\n', '���Ă���B\nKEY\nEFF 60\n', txt)
# �z���C�g�C���A�E�g�A�z���C�g�C���A�E�g�@��u�̉H�̋L��
if(sys.argv[1] == "cs07_11.log"): txt = re.sub('BGL e028\nICO kait06\n', 'EFF 34\nCLR 7\nSET e028 1\nEFF 35\nWAT 60\nEFF 34\nSET bg44 1\nSET ca009b 4\nSET kait06 7\nSET mini12 8\nEFF 35\nICO kait06\n', txt)
# �A���W�F�������@�������Ă���
if(sys.argv[1] == "cs07_11.log"): txt = re.sub('SEL �b��\nICO angl0d\n', 'CLR 2\nEFF 33\nSEL �b��\nICO angl0d\n', txt)
# MIN�����@���ICO
if(sys.argv[1] == "cs07_11.log"): txt = re.sub('MSG �u�E�E�E�E�E�E\\\\eb\\\\c1�v\nKEY\nMSG �E�E', 'MSG �u�E�E�E�E�E�E\\\\eb\\\\c1�v\nKEY\nEFF 60\nMSG �E�E', txt)
# �C���A�E�g�g�@�J�C�g���̐��̂𒲂ׂ�
if(sys.argv[1] == "cs07_11.log"): txt = re.sub('EFF 4\nSSG 21\n', 'EFF 36\nEFF 11\nSSG 21\n', txt)
# �G���U�����@�J�C�g������蓦��
if(sys.argv[1] == "cs07_12.log"): txt = re.sub('EFF 4\nBST\n', 'CLR 2\nEFF 33\nBST\n', txt)
# MIN�����@�x�b�g�̌�
if(sys.argv[1] == "cs07_13.log"): txt = re.sub('���E�E�E�v\nKEY\n', '���E�E�E�v\nKEY\nEFF 60\n', txt)


# MIN�����@��؂̘b�����l��
if(sys.argv[1] == "cs08_02.log"): txt = re.sub('ICO xtra04\nMSG �u���܂Ȃ�', 'EFF 60\nICO xtra04\nMSG �u���܂Ȃ�', txt)
# �C���A�E�g�g�@����̌�̃Z�C������
if(sys.argv[1] == "cs08_06.log"): txt = re.sub('BPL 17\nEFF 4\n', 'BPL 17\nEFF 36\nEFF 11\n', txt)
# �C���L�����A�C�R�������A�E�g�@���[�Y�}���[�ɐf�Ă��炤
if(sys.argv[1] == "cs08_06.log"): txt = re.sub('LDS', 'EFF 36\nCLR 2\nEFF 37\nLDS', txt)
# ����
if(sys.argv[1] == "cs08_10.log"): txt = re.sub('EFF 9\n', '', txt)
# ����
if(sys.argv[1] == "cs08_10.log"): txt = re.sub('EFF 6\n', '', txt)
# UD���{�A�E�g�g�@���[�Y�}���[H�I��
if(sys.argv[1] == "cs08_12.log"): txt = re.sub('EFF 15\n', 'EFF 9\nWAT 30\nEFF 11\n', txt)
# �C���A�E�g�g�@���̓�
if(sys.argv[1] == "cs08_15.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �~�i�����@����ŏ����W
if(sys.argv[1] == "cs08_17.log"): txt = re.sub('SEL ����\n', 'CLR 2\nEFF 33\nSEL ����\n', txt)
# ���W�[�i�����@����ς肢����ł�
if(sys.argv[1] == "cs08_18.log"): txt = re.sub('ICO raby0d\n', 'CLR 2\nEFF 33\nICO raby0d\n', txt)
# �C���A�E�g�g�@�h�[���֏o��
if(sys.argv[1] == "cs08_18.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�h�[���t��
if(sys.argv[1] == "cs08_20.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �f�B���C�A�����@���r�B�Ɩ��k
if(sys.argv[1] == "cs08_22.log"): txt = re.sub('SSG 21\nPTY pty013\n', 'CLR 2\nEFF 33\nSSG 21\nPTY pty013\n', txt)
# �C���A�E�g�g�@�Z�C�������ɋA��
if(sys.argv[1] == "cs08_22.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �_�C�A�i�����@�_���X��
if(sys.argv[1] == "cs08_24.log"): txt = re.sub('LDS', 'CLR 2\nEFF 33\nLDS', txt)
# �C���A�E�g�g�@�����b��
if(sys.argv[1] == "cs08_25.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�钆�ڂ��o�܂�
if(sys.argv[1] == "cs08_26.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# UD���@���W�[�iH
if(sys.argv[1] == "cs08_35.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# ����
if(sys.argv[1] == "cs08_31.log"): txt = re.sub('EFF 9\n', '', txt)
# UD���@���W�[�iH
if(sys.argv[1] == "cs08_31.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# �A�C�R�������{�t���b�V���{�E�F�C�g�{�C���A�E�g�g�@���W�[�iH�I��
if(sys.argv[1] == "cs08_31.log"): txt = re.sub('EFF 11\n', 'EFF 41\nWAT 30\nEFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@���r�[�ƌ���
if(sys.argv[1] == "cs08_31.log"): txt = re.sub('LDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�����Ŗ邲�͂�
if(sys.argv[1] == "cs08_33.log"): txt = re.sub('EFF 4\nMSG', 'EFF 36\nEFF 11\nMSG', txt)
# �C���A�E�g�g�@���r�B�������蕔���o��
if(sys.argv[1] == "cs08_34.log"): txt = re.sub('EFF 4\nMSG', 'EFF 36\nEFF 11\nMSG', txt)
# �C���A�E�g�g�@���r�B�������蕔���o��
if(sys.argv[1] == "cs08_34.log"): txt = re.sub('EFF 4\nBGL bg05\n', 'EFF 36\nEFF 11\nBGL bg05\n', txt)


# �C���A�E�g�g�@�h�[���Ɉړ�
if(sys.argv[1] == "cs09_04.log"): txt = re.sub('BPL 16\nEFF 4\n', 'BPL 16\nEFF 36\nEFF 11\n', txt)
# �����X�^�[�����@�|�����
if(sys.argv[1] == "cs09_06.log"): txt = re.sub('MSG �b�͎�', 'CLR 2\nEFF 33\nMSG �b�͎�', txt)
# �C���A�E�g�g�@���r�B��T��
if(sys.argv[1] == "cs09_07.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�r�B�̈ē�
if(sys.argv[1] == "cs09_08.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�r�B�̈ē��ň㖱����ڎw��
if(sys.argv[1] == "cs09_09.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�n�}�����Ĉ㖱����ڎw��
if(sys.argv[1] == "cs09_10.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�n�}�����Ĉ㖱����ڎw���i�E���t�B���j
if(sys.argv[1] == "cs09_13.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�E���t�B�A�����X�^�[���U��
if(sys.argv[1] == "cs09_14.log"): txt = re.sub('EFF 4\nBST\n', 'EFF 36\nEFF 11\nBST\n', txt)
# �C���A�C�R�������A�E�g�@�L�����삯�o��
if(sys.argv[1] == "cs09_14.log"): txt = re.sub('ICO nees05\n', 'EFF 36\nEFF 37\nICO nees05\n', txt)
# �����X�^�[�����@�|�����
if(sys.argv[1] == "cs09_17.log"): txt = re.sub('MSG �E�E�E�E�E�E������', 'CLR 2\nEFF 33\nMSG �E�E�E�E�E�E������', txt)
# �u���[�����@��������
if(sys.argv[1] == "cs09_24.log"): txt = re.sub('MSG ���̔w��', 'CLR 2\nEFF 33\nMSG ���̔w��', txt)
# �C���A�E�g�g�@���r�B������ēP�ޒ�
if(sys.argv[1] == "cs09_24.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �z���C�g�C���w�i�A�E�g�@�h�[������
if(sys.argv[1] == "cs09_25.log"): txt = re.sub('BGL bg07b\n', 'EFF 34\nCLR 7\nSET bg07 1\nEFF 35\nBGL bg07b\n', txt)
# �C���A�E�g�g�@���܂œP��
if(sys.argv[1] == "cs09_25.log"): txt = re.sub('EFF 4\nBGL bg05\nCHR ca001b\n', 'EFF 36\nEFF 11\nBGL bg05\nCHR ca001b\n', txt)
# �C���L���������A�E�g�@�j�[�X�ƐQ��
if(sys.argv[1] == "cs09_25.log"): txt = re.sub('MSG �����A', 'EFF 36\nCLR 2\nEFF 37\nMSG �����A', txt)
# UD�\���@�A���W�F���F��P
if(sys.argv[1] == "cs09_27.log"): txt = re.sub('BGL e022b\n', 'SET e022b 1\nEFF 33\n', txt)
# UD�\���@�A���W�F���F��Q
if(sys.argv[1] == "cs09_27.log"): txt = re.sub('BGL e022b2\n', 'SET e022b2 1\nEFF 33\n', txt)
# UD�\���@�E���t�B�A�A���W�F���ɋ߂Â�
if(sys.argv[1] == "cs09_27.log"): txt = re.sub('BGL e022c\n', 'SET e022c 1\nEFF 33\n', txt)
# UD�\���@�A���W�F��������
if(sys.argv[1] == "cs09_27.log"): txt = re.sub('BGL e022d\n', 'SET e022d 1\nEFF 33\n', txt)


# �C���A�E�g�g�@�����牓������
if(sys.argv[1] == "cs10_04.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�E���t�B���瓦����
if(sys.argv[1] == "cs10_09.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�K�ɖ߂�
if(sys.argv[1] == "cs10_10.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�P�K�l�֍s��
if(sys.argv[1] == "cs10_13.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# �C���A�E�g�g�@��Ɉړ�
if(sys.argv[1] == "cs11_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�h�[���Ɉړ�
if(sys.argv[1] == "cs11_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# UD�w�i�@�h�[���T���Ŏ��������
if(sys.argv[1] == "cs12_02.log"): txt = re.sub('BGL bg07c\nLDS', 'CLR 2\nSET bg07c 1\nEFF 33\nLDS', txt)
# �C���A�E�g�g�@���������
if(sys.argv[1] == "cs12_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�^���E�o
if(sys.argv[1] == "cs12_05.log"): txt = re.sub('EFF 4\nBST\n', 'EFF 36\nEFF 11\nBST\n', txt)


# �C���A�E�g�g�@�ݕӂ̖�
if(sys.argv[1] == "cs13_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�ݕӂ̒�
if(sys.argv[1] == "cs13_04.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �����@�G���UH
if(sys.argv[1] == "cs13_07.log"): txt = re.sub('EFF 9\n', '', txt)
# �����@�G���UH
if(sys.argv[1] == "cs13_08.log"): txt = re.sub('EFF 9\n', '', txt)
# �A�C�R�������{�t���b�V���{�E�F�C�g�{�C���A�E�g�g�@�G���UH�I��
if(sys.argv[1] == "cs13_10.log"): txt = re.sub('EFF 11\n', 'EFF 41\nWAT 30\nEFF 36\nEFF 11\n', txt)
# �t���b�V���@�X�^���K��
if(sys.argv[1] == "cs13_12.log"): txt = re.sub('MSG �΂���', 'CLR 2\nEFF 33\nEFF 41\nMSG �΂���', txt)
# �e�B�e�B�����@���D���B�΂ɒė�
if(sys.argv[1] == "cs13_14.log"): txt = re.sub('MSG �e�B�e�B���Q', 'CLR 2\nEFF 33\nMSG �e�B�e�B���Q', txt)
# �C���A�E�g�g�@���D���B�e�B�e�B��������
if(sys.argv[1] == "cs13_15.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# �����@�e�B�e�BH
if(sys.argv[1] == "cs13_18.log"): txt = re.sub('EFF 9\n', '', txt)
# UD���@�e�B�e�BH�i���K�\���Q��j
if(sys.argv[1] == "cs13_18.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# �A�C�R�������{�t���b�V���{�E�F�C�g�{�C���A�E�g�g�@�e�B�e�BH�I��
if(sys.argv[1] == "cs13_18.log"): txt = re.sub('EFF 15\n', 'EFF 34\nCLR 7\nWAT 30\nEFF 35\nEFF 11\n', txt)
# �C���A�E�g�g�@���D���B�ƃe�B�e�B�ʂ�
if(sys.argv[1] == "cs13_20.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@���D���B�ƃe�B�e�B�ʂ�
if(sys.argv[1] == "cs13_21.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �����@���D���BH
if(sys.argv[1] == "cs13_27.log"): txt = re.sub('EFF 9\n', '', txt)
# �����@���D���BH
if(sys.argv[1] == "cs13_29.log"): txt = re.sub('EFF 9\n', '', txt)
# �C���A�E�g�g�@���D���BH�I��
if(sys.argv[1] == "cs13_30.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�f�B���C�A�̃e���g��
if(sys.argv[1] == "cs13_33.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@��������
if(sys.argv[1] == "cs13_34.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# BGM�����@�f�B���C�AH
if(sys.argv[1] == "cs13_38.log"): txt = re.sub('BST\nBPL 14\n', '', txt)
# �A�C�R�������{�t���b�V���{�E�F�C�g�{�C���A�E�g�g�@�f�B���C�AH�I��
if(sys.argv[1] == "cs13_39.log"): txt = re.sub('EFF 6\n', 'EFF 41\nWAT 30\nEFF 36\nEFF 11\n', txt)
# �C���A�C�R�������A�E�g�g�@��������b��
if(sys.argv[1] == "cs13_40.log"): txt = re.sub('�͂��߂��B\nKEY\n', '�͂��߂��B\nKEY\nEFF 36\nEFF 37\n', txt)
# �C���A�E�g�g�@�Z�C��������
if(sys.argv[1] == "cs13_40.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)


# MIN�����@������
if(sys.argv[1] == "cs14_01.log"): txt = re.sub('ICO angl22\n', 'EFF 60\nICO angl22\n', txt)
# �C���A�E�g�g�@�Ђ̊O
if(sys.argv[1] == "cs14_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�����ɓ���錈��
if(sys.argv[1] == "cs14_02.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�Z�C�������֏o���i���K�\���Q��j
if(sys.argv[1] == "cs14_03.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�Z�C�������֏o��
if(sys.argv[1] == "cs14_03.log"): txt = re.sub('EFF 4\nSSG 21\n', 'EFF 36\nEFF 11\nSSG 21\n', txt)
# �C���A�E�g�g�@�Z�C�������֏o��
if(sys.argv[1] == "cs14_03.log"): txt = re.sub('BST\nEFF 4\nBST\n', 'BST\nEFF 36\nEFF 11\nBST\n', txt)
# ���������{UD�{�C���A�E�g�@���[�Y�}���[�̉Ƃ�
if(sys.argv[1] == "cs14_04.log"): txt = re.sub('MSG �l�͕ψّ̂�', 'CLR 2\nEFF 33\nEFF 36\nEFF 37\nMSG �l�͕ψّ̂�', txt)
# �L���������{UD�{�C���A�E�g�@�����
if(sys.argv[1] == "cs14_04.log"): txt = re.sub('MSG �����', 'CLR 2\nEFF 33\nEFF 36\nEFF 37\nMSG �����', txt)
# �A�C�R�������{�C���A�E�g�@�����
if(sys.argv[1] == "cs14_04.log"): txt = re.sub('LDS', 'EFF 36\nEFF 37\nLDS', txt)
# �L���������{UD�@�_�C�A�i���~�i�Ă�
if(sys.argv[1] == "cs14_05.log"): txt = re.sub('�������v\nKEY\n', '�������v\nKEY\nCLR 2\nEFF 33\n', txt)
# �L���������{UD�@�~�i�̖�؃X�[�v
if(sys.argv[1] == "cs14_05.log"): txt = re.sub('���񂾁B\nKEY\n', '���񂾁B\nKEY\nCLR 2\nEFF 33\n', txt)
# �L���������{UD�@����̊O�ɏo��
if(sys.argv[1] == "cs14_06.log"): txt = re.sub('EFF 4\n', 'CLR 2\nEFF 33\nEFF 4\n', txt)
# �L���������@�A���W�F������
if(sys.argv[1] == "cs14_09.log"): txt = re.sub('MSG �A���W�F���͒�', 'CLR 2\nEFF 33\nMSG �A���W�F���͒�', txt)
# �t���b�V���P��@�A���W�F���̋L������
if(sys.argv[1] == "cs14_11.log"): txt = re.sub('�΁E�E�E\\\\eb\\\\c3�v\nKEY\n', '�΁E�E�E\\\\eb\\\\c3�v\nKEY\nEFF 41\n', txt)
# �t���b�V���R��@�A���W�F���̋L������
if(sys.argv[1] == "cs14_11.log"): txt = re.sub('ICO wolf07\nMSG �u�E�E', 'EFF 41\nEFF 41\nEFF 41\nICO wolf07\nMSG �u�E�E', txt)
# �z���C�g�C���{�E�F�C�g�{�A�E�g�g�@�A���W�F���̋L��
if(sys.argv[1] == "cs14_11.log"): txt = re.sub('EFF 4\nBST\n', 'EFF 34\nCLR 7\nSET waku06b 1\nWAT 60\nEFF 35\nBST\n', txt)
# �t���b�V���R��@�A���W�F���̋L���߂�
if(sys.argv[1] == "cs14_11.log"): txt = re.sub('BPL 9\n', 'CLR 2\nEFF 41\nEFF 41\nEFF 41\nBPL 9\n', txt)


# �L���������{UD�@�C���A��ɍs��
if(sys.argv[1] == "cs15_01.log"): txt = re.sub('SSG 21\n', 'CLR 2\nEFF 33\nSSG 21\n', txt)
# �t���b�V���P��@�A���W�F���̋L������
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('�΁E�E�E\\\\eb\\\\c3�v\nKEY\n', '�΁E�E�E\\\\eb\\\\c3�v\nKEY\nEFF 41\n', txt)
# �t���b�V���R��@�A���W�F���̋L������
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('ICO wolf07\nMSG �u�E�E', 'EFF 41\nEFF 41\nEFF 41\nICO wolf07\nMSG �u�E�E', txt)
# �z���C�g�C���{�E�F�C�g�{�A�E�g�g�@�A���W�F���̋L��
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('EFF 4\nBST\n', 'EFF 34\nCLR 7\nSET waku06b 1\nWAT 60\nEFF 35\nBST\n', txt)
# �ʏ�\���@���r�B�̌��e
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('CHR ca002a1\n', 'SET ca002a1 4\nEFF 60\n', txt)
# �z���C�g�C���{�A�E�g�g�@�E���t�B�̋L���߂�
if(sys.argv[1] == "cs15_02.log"): txt = re.sub('ICO wolf0e\nMSG �u�E�E�E�E�E�E���r�B�v\n', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\nICO wolf0e\nMSG �u�E�E�E�E�E�E���r�B�v\n', txt)
# �t���b�V���@�L���V�[�Ƀ_���[�W
if(sys.argv[1] == "cs15_09.log"): txt = re.sub('ICO kyas0e\n', 'CLR 2\nEFF 41\nICO kyas0e\n', txt)
# �o���L�����\���@�L�����Q�l�Ŋ��t
if(sys.argv[1] == "cs15_05.log"): txt = re.sub('CHR ca006b\n', 'SET ca006b 5\nEFF 33\n', txt)
# �C���L���������A�E�g�@�C���A���������߂�܂ő҂�
if(sys.argv[1] == "cs15_05.log"): txt = re.sub('BPL 17\n', 'EFF 36\nCLR 2\nEFF 37\n', txt)
# �L���������@�����[��������
if(sys.argv[1] == "cs15_07.log"): txt = re.sub('ICO wolf0a\nMSG �u�E�E�E�E�E�E�v\nKEY\n', 'ICO wolf0a\nMSG �u�E�E�E�E�E�E�v\nKEY\nCLR 2\nEFF 33\n', txt)
# �L����ICO�����@�L���V�[�ދp
if(sys.argv[1] == "cs15_09.log"): txt = re.sub('BPL 10\n', 'CLR 2\nEFF 33\nBPL 10\n', txt)


# �C���A�E�g�g�@�Z�C��������
if(sys.argv[1] == "cs16_02.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�Z�C�������֓���
if(sys.argv[1] == "cs16_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �L���������@���W�[�i
if(sys.argv[1] == "cs16_04.log"): txt = re.sub('ICO kait18\n', 'CLR 2\nEFF 33\nICO kait18\n', txt)
# �L���������@�E���t�B
if(sys.argv[1] == "cs16_05.log"): txt = re.sub('SSG 21\n', 'CLR 2\nEFF 33\nSSG 21\n', txt)
# �C���A�E�g�g�@�J�C�g�Q��
if(sys.argv[1] == "cs16_06.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �L���������@�C���A���������P
if(sys.argv[1] == "cs16_07.log"): txt = re.sub('ICO iria42\n', 'CLR 2\nEFF 33\nICO iria42\n', txt)
# �L���������@�C���A���������Q
if(sys.argv[1] == "cs16_07.log"): txt = re.sub('�|�ꂽ�B\nKEY\n', '�|�ꂽ�B\nKEY\nCLR 2\nEFF 33\n', txt)
# �C���A�E�g�g�@�J�C�g����
if(sys.argv[1] == "cs16_11.log"): txt = re.sub('���āv\nKEY\n', '���āv\nKEY\nEFF 36\nCLR 2\nEFF 37\n', txt)
# �C���A�E�g�g�@�Z�C�������Œ��ԏЉ�
if(sys.argv[1] == "cs16_11.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���@�����[H�I��
if(sys.argv[1] == "cs16_17.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)
# BGM�����@�����[H��
if(sys.argv[1] == "cs16_18.log"): txt = re.sub('BST\nBPL 4\n', '', txt)
# �L���������@�~�i
if(sys.argv[1] == "cs16_18.log"): txt = re.sub('������v\nKEY\n', '������v\nKEY\nCLR 2\nEFF 33\n', txt)
# �L���������@�~�i
if(sys.argv[1] == "cs16_18.log"): txt = re.sub('LDS', 'CLR 2\nEFF 33\nLDS', txt)
# �L���������@�C���A
if(sys.argv[1] == "cs16_20.log"): txt = re.sub('ICO kait25', 'CLR 2\nEFF 33\nICO kait25', txt)


# �����@�C���AH
if(sys.argv[1] == "cs17_05.log"): txt = re.sub('EFF 9\n', '', txt)
# UD���@�C���AH
if(sys.argv[1] == "cs17_05.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# �A�C�R�������{�z���C�g�C���{�E�F�C�g�{�z���C�g�A�E�g�{�A�E�g�g�@�C���AH
if(sys.argv[1] == "cs17_05.log"): txt = re.sub('EFF 15\n', 'EFF 34\nCLR 7\nWAT 30\nEFF 35\nEFF 11\n', txt)
# �A�C�R�������{�C���A�E�g�@�C���AH��Q��
if(sys.argv[1] == "cs17_05.log"): txt = re.sub('LDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�����
if(sys.argv[1] == "cs17_06.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���{�L���������{�A�E�g�@�A���W�F���̃p�[�e�B���A
if(sys.argv[1] == "cs17_07.log"): txt = re.sub('SSG 21\nPTY pty026\n', 'SSG 21\nPTY pty026\nEFF 36\nCLR 2\nEFF 37\n', txt)
# �C���A�E�g�g�@�h���̈ꎺ
if(sys.argv[1] == "cs17_07.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�A���W�F���̏󋵐���
if(sys.argv[1] == "cs17_10.log"): txt = re.sub('EFF 4\n', 'EFF 36\nEFF 11\n', txt)
# �����@�_�C�A�iH
if(sys.argv[1] == "cs17_16.log"): txt = re.sub('EFF 9\n', '', txt)
# UD���@�_�C�A�iH
if(sys.argv[1] == "cs17_16.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# UD���@�_�C�A�iH�I��
if(sys.argv[1] == "cs17_16.log"): txt = re.sub('EFF 15\n', 'EFF 9\n', txt)
# UD���@�_�C�A�i�ƃ��[�Y�}���[H
if(sys.argv[1] == "cs17_17.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# �����@�_�C�A�i�ƃ��[�Y�}���[H
if(sys.argv[1] == "cs17_19.log"): txt = re.sub('EFF 9\n', '', txt)
# UD���{�A�E�g�g�@�_�C�A�i�ƃ��[�Y�}���[H�I��
if(sys.argv[1] == "cs17_20.log"): txt = re.sub('EFF 15\n', 'EFF 9\nEFF 11\n', txt)
# UD���@�~�iH
if(sys.argv[1] == "cs17_22.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# �����@�~�iH
if(sys.argv[1] == "cs17_23.log"): txt = re.sub('EFF 6\n', '', txt)
# UD���{�A�E�g�g�@�~�iH�I��
if(sys.argv[1] == "cs17_24.log"): txt = re.sub('EFF 15\n', 'EFF 9\nEFF 11\n', txt)
# �����@�_�C�A�i�ƃ~�iH
if(sys.argv[1] == "cs17_25.log"): txt = re.sub('EFF 6\n', '', txt)
# �����@�_�C�A�i�ƃ~�iH
if(sys.argv[1] == "cs17_26.log"): txt = re.sub('EFF 6\n', '', txt)
# UD���{�A�E�g�g�@�_�C�A�i�ƃ~�iH�I��
if(sys.argv[1] == "cs17_27.log"): txt = re.sub('EFF 6\n', 'EFF 9\nEFF 11\n', txt)
# UD���{�A�E�g�g�@�������Ɉړ�
if(sys.argv[1] == "cs17_30.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# MIN�����@���̎���
if(sys.argv[1] == "cs17_33.log"): txt = re.sub('SEL �b��\nICO angl08\n', 'EFF 60\nSEL �b��\nICO angl08\n', txt)
# MIN�����@�R���s���[�^
if(sys.argv[1] == "cs17_35.log"): txt = re.sub('SEL �b��\nMSG �ǂ�', 'EFF 60\nSEL �b��\nMSG �ǂ�', txt)
# MIN�����@���r�B�̕��
if(sys.argv[1] == "cs17_37.log"): txt = re.sub('�E�E�E�j\nKEY\n', '�E�E�E�j\nKEY\nEFF 60\n', txt)
# �C���A�E�g�g�@�f�B���C�A�ɃC�W���E�C���V�e�B���ē����Ă��炤
if(sys.argv[1] == "cs17_42.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@���r�B���C���ɑ҂�
if(sys.argv[1] == "cs17_45.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �t���b�V���R��@���r�B��
if(sys.argv[1] == "cs17_47.log"): txt = re.sub('MSG �΂�����', 'EFF 41\nEFF 41\nEFF 41\nMSG �΂�����', txt)
# �w�i����
if(sys.argv[1] == "cs17_47.log"): txt = re.sub('BGL bg47\nCHR ca007c2\nICO blue0a', 'CHR ca007c2\nICO blue0a', txt)
# �A�j���[�V�����w��@�W�����v���߂����ROM�w��
if(sys.argv[1] == "cs17_49.log"): txt = re.sub('LDS 18 1', 'END', txt)


# �����@�R�ӏ�
if(sys.argv[1] == "cs18_01.log"): txt = re.sub('EFF 5\n', '', txt)
# �C���A�E�g�g�@���r�B��l�Ńh�[����
if(sys.argv[1] == "cs18_01.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�h�[���̒���
if(sys.argv[1] == "cs18_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# UD���@�r�A�g���X�ƃL���V�[H
if(sys.argv[1] == "cs18_03.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# ����
if(sys.argv[1] == "cs18_04.log"): txt = re.sub('BST\nBPL 9\n', '', txt)
# ������HSC�ύX�@���r�B����₢�l�ߒ�
if(sys.argv[1] == "cs18_04.log"): txt = re.sub('EFF 9\nBGL e016\n', 'HSC e016\n', txt)
# �C���A�E�g�g�@�J�C���~�߂�
if(sys.argv[1] == "cs18_04.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@���r�B����₢�l�ߏI��
if(sys.argv[1] == "cs18_04.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@���r�B�Q��
if(sys.argv[1] == "cs18_05.log"): txt = re.sub('LDS', 'EFF 36\nEFF 11\nLDS', txt)
# �J�C�������@���r�B�Ɖ�b�I��
if(sys.argv[1] == "cs18_07.log"): txt = re.sub('�˂��[�v\nKEY\n', '�˂��[�v\nKEY\nCLR 2\nEFF 33\n', txt)
# �S�p����
if(sys.argv[1] == "cs18_08.log"): txt = re.sub('�@�@�@�@�@�@�@�@�@���|�[�g', '�@���|�[�g', txt)
# �S�p����
if(sys.argv[1] == "cs18_08.log"): txt = re.sub('�@�@�@�@�a�؎��̔��������ē��@�@�@�@�x', '�@�a�؎��̔��������ē��x', txt)
# �w�i�ύX�@���̃��r�B�̃n�b�L���O�P�i�ߑ��ԈႢ�ׁ̈B����C��
if(sys.argv[1] == "cs18_08.log"): txt = re.sub('e018b2', 'e018b1', txt)
# �w�i�ύX�@���̃��r�B�̃n�b�L���O�Q�i�ߑ��ԈႢ�ׁ̈B����C��
if(sys.argv[1] == "cs18_08.log"): txt = re.sub('e018a2', 'e018a1', txt)
# �w�i�����X�^�[�ύX�@���r�B�n�b�L���O���̔w���
if(sys.argv[1] == "cs18_09.log"): txt = re.sub('MSG �������͂���', 'SET bg45 2\nEFF 33\nMSG �������͂���', txt)


# �C���A�E�g�g�@�f�B���C�A�̈ē�
if(sys.argv[1] == "cs19_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �����@�f�B���C�A����
if(sys.argv[1] == "cs19_02.log"): txt = re.sub('EFF 5\n', '', txt)
# �C���A�E�g�g�@�f�B���C�A�̈ē�
if(sys.argv[1] == "cs19_02.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�L��ȑ�n
if(sys.argv[1] == "cs19_03.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@����
if(sys.argv[1] == "cs19_04.log"): txt = re.sub('EFF 4\nSSG 21', 'EFF 36\nEFF 11\nSSG 21', txt)
# MIN�����@�A���[�o
if(sys.argv[1] == "cs19_06.log"): txt = re.sub('MSG ��ɕԂ���', 'EFF 60\nMSG ��ɕԂ���', txt)
# MIN�����@�S�i�q
if(sys.argv[1] == "cs19_08.log"): txt = re.sub('ICO kait17\nMSG �u����', 'EFF 60\nICO kait17\nMSG �u����', txt)


# �C���A�E�g�g�@�����ɓ���
if(sys.argv[1] == "cs20_05.log"): txt = re.sub('EFF 4\nBST', 'EFF 36\nEFF 11\nBST', txt)
# �C���A�E�g�g�@���C
if(sys.argv[1] == "cs20_05.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# MIN�����@�N���Q
if(sys.argv[1] == "cs20_07.log"): txt = re.sub('MSG �l�͈�', 'EFF 60\nMSG �l�͈�', txt)


# �C���A�E�g�g�@�`���s�����Z��̔����J����
if(sys.argv[1] == "cs21_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# ����
if(sys.argv[1] == "cs21_02.log"): txt = re.sub('EFF 8\nBGL bg13\n', '', txt)
# MIN�����@�J�C�g�w��
if(sys.argv[1] == "cs21_05.log"): txt = re.sub('SEL �b��\nICO irih16\n', 'EFF 60\nSEL �b��\nICO irih16\n', txt)
# �C���A�E�g�g�@�r�B�̉�b�I��
if(sys.argv[1] == "cs21_08.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�G���U�̕������O�A�n�}������
if(sys.argv[1] == "cs21_09.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# MIN�����@�C���A�����̏�����
if(sys.argv[1] == "cs21_10.log"): txt = re.sub('SSG 26\n', 'EFF 60\nSSG 26\n', txt)
# �C���{�L���������{�A�E�g�g�@�G���U�Ɏ������
if(sys.argv[1] == "cs21_10.log"): txt = re.sub('LDS', 'EFF 36\nCLR 2\nEFF 37\nLDS', txt)
# MIN�����@�A���W�F���ƃJ�C�g����Ȃ�
if(sys.argv[1] == "cs21_12.log"): txt = re.sub('MSG �A���W�F���͖l', 'EFF 60\nMSG �A���W�F���͖l', txt)
# MIN�����@�A���W�F���A�G���U�ɃL�X
if(sys.argv[1] == "cs21_12.log"): txt = re.sub('ICO angl0f\nMSG �u���ꂶ��', 'EFF 60\nICO angl0f\nMSG �u���ꂶ��', txt)
# �C���A�E�g�g�@�G���U�̕�������o��
if(sys.argv[1] == "cs21_12.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �C���A�E�g�g�@�U������Ă�i���K�\���Q��j
if(sys.argv[1] == "cs21_13.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�҂��󂯂Ă���
if(sys.argv[1] == "cs21_13.log"): txt = re.sub('BST\nEFF 4\n', 'BST\nEFF 36\nEFF 11\n', txt)


# �C���A�E�g�g�@�R���s���[�^��T����
if(sys.argv[1] == "cs22_01.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# MIN�����@�A���W�F���L�X
if(sys.argv[1] == "cs22_04.log"): txt = re.sub('ICO angl05\nMSG �u�����', 'EFF 60\nICO angl05\nMSG �u�����', txt)
# �C���A�E�g�g�@�n�[�p�[���m�̕������o��
if(sys.argv[1] == "cs22_09.log"): txt = re.sub('BST\nEFF 4\n', 'BST\nEFF 36\nEFF 11\n', txt)
# �����@���I�iH
if(sys.argv[1] == "cs22_13.log"): txt = re.sub('EFF 9\n', '', txt)
# �����@���I�iH
if(sys.argv[1] == "cs22_13.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# �C���A�E�g�g�@���I�iH�I��
if(sys.argv[1] == "cs22_13.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)
# �����@�h�[��H
if(sys.argv[1] == "cs22_16.log"): txt = re.sub('EFF 6\n', '', txt)
# �����@�h�[��H
if(sys.argv[1] == "cs22_17.log"): txt = re.sub('EFF 6\n', 'EFF 9\n', txt)
# �����@�h�[��H
if(sys.argv[1] == "cs22_18.log"): txt = re.sub('EFF 11\n', 'EFF 36\nEFF 11\n', txt)


# �����@��������
if(sys.argv[1] == "cs23_01.log"): txt = re.sub('EFF 4\n', '', txt)
# UD�\���@�t�@�[�i���K�\���Q��j
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('CHR ca010a\n', 'SET waku06b 1\nSET ca010a 2\nEFF 33\n', txt)
# UD�\���@���΂݃t�@�[�i���K�\���R��j
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('CHR ca010c\n', 'SET waku06b 1\nSET ca010c 2\nEFF 33\n', txt)
# LR�g�@�t�@�[����
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('EFF 12\n', 'EFF 4\n', txt)
# �E�F�C�g�@�E���t�B�Ə�
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('MIN mini2f\nMIN mini2e\n', 'MIN mini2e\nWAT 60\nMIN mini2f\nWAT 60\n', txt)
# UD�\���@���B�A���J�i���K�\���R��j
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('BGL e034a1\n', 'CLR 2\nSET e034a1 1\nEFF 33\n', txt)
# �C���A�E�g�@�t�@�[�������
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('BPL 6\n', 'EFF 36\nCLR 7\nEFF 37\nBPL 6\n', txt)
# �L�[�ǉ��@�t�@�[�����ꂽ��
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO wolf16', 'KEY\nICO wolf16', txt)
# �L�[�ǉ��@�t�@�[�����ꂽ��
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO kait0a', 'KEY\nICO kait0a', txt)
# �L�[�ǉ��@�t�@�[�����ꂽ��
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO iria19', 'KEY\nICO iria19', txt)
# �L�[�ǉ��@�t�@�[�����ꂽ��
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO mira03', 'KEY\nICO mira03', txt)
# �L�[�ǉ��@�t�@�[�����ꂽ��
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO nees1b', 'KEY\nICO nees1b', txt)
# �L�[�ǉ��@�t�@�[�����ꂽ��
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO leon03', 'KEY\nICO leon03', txt)
# �L�[�ǉ��@�t�@�[�����ꂽ��
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('ICO dora0f', 'KEY\nICO dora0f', txt)
# �L�[�ǉ��{�z���C�g�C���{�E�F�C�g�{�A�E�g�g
if(sys.argv[1] == "cs23_02.log"): txt = re.sub('EFF 4\nMSG ���B�A���J�̏e', 'KEY\nEFF 34\nCLR 7\nWAT 30\nSET waku06b 1\nEFF 35\nMSG ���B�A���J�̏e', txt)
# �����i���K�\���R��j
if(sys.argv[1] == "cs23_03.log"): txt = re.sub('EFF 5\n', '', txt)
# �z���C�g�C���{�E�F�C�g�{�A�E�g�g�@���r�B���ɕ�܂��
if(sys.argv[1] == "cs23_05.log"): txt = re.sub('CHR ca002g\n', 'EFF 34\nCLR 7\nWAT 30\nSET ca002g 1\nEFF 35\n', txt)
# �L���������@���r�B�Z��
if(sys.argv[1] == "cs23_05.log"): txt = re.sub('BST\nMSG �ƁA', 'CLR 2\nEFF 33\nBST\nMSG �ƁA', txt)
# �L���������@���{�b�g��
if(sys.argv[1] == "cs23_06.log"): txt = re.sub('ICO iria07\nMSG �u���̂���', 'CLR 2\nEFF 33\nICO iria07\nMSG �u���̂���', txt)
# �t���b�V���@�E���t�B�Ƀ_���[�W
if(sys.argv[1] == "cs23_06.log"): txt = re.sub('MSG �ق��Ƃ���', 'EFF 41\nMSG �ق��Ƃ���', txt)
# �C���A�E�g�g�@�f�B���C�A�̈ē�
if(sys.argv[1] == "cs23_06.log"): txt = re.sub('EFF 4\nLDS', 'EFF 36\nEFF 11\nLDS', txt)
# �L���������@�S������E�o
if(sys.argv[1] == "cs23_11.log"): txt = re.sub('BST\nBPL 9', 'CLR 2\nEFF 33\nBST\nBPL 9', txt)
# �t���b�V���@�E���t�B�Ƀ��[�U�[
if(sys.argv[1] == "cs23_11.log"): txt = re.sub('BST\nMSG', 'EFF 41\nBST\nMSG', txt)
# �z���C�g�C���A�E�g�g
if(sys.argv[1] == "cs23_11.log"): txt = re.sub('EFF 4\nLDS', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\nLDS', txt)
# �L���������@�~�B
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('���߂��E�E�E�B\nKEY\n', '���߂��E�E�E�B\nKEY\nCLR 2\nEFF 33\n', txt)
# �t���b�V���@�L�[���[�h
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('SSG 45\nMSG', 'SSG 45\nEFF 41\nMSG', txt)
# �z���C�g�C���A�E�g�g�@���̒����^����
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 4\nEFF 12\n', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\n', txt)
# �C���A�E�g�g�@�P�K����
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('�Ȃ�ł��Ȃ���E�E�E�v\nKEY\n', '�Ȃ�ł��Ȃ���E�E�E�v\nKEY\nEFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�܂���
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('�܂��ˁA�E���t�B�E�E�E�v\nKEY\n', '�܂��ˁA�E���t�B�E�E�E�v\nKEY\nEFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�͂̑��������
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�p���h���̐X
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 4\nICO xtra49\n', 'EFF 36\nEFF 11\nICO xtra49\n', txt)
# �C���A�E�g�g�@�r�B�ߋ�
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 12\nCHR ca010c\n', 'EFF 36\nEFF 11\nCHR ca010c\n', txt)
# �z���C�g�C���A�E�g�g�@�n��
if(sys.argv[1] == "cs23_12.log"): txt = re.sub('EFF 4\nLDS', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\nLDS', txt)
# MIN�����@�~�Y�N���Q�̑���
if(sys.argv[1] == "cs23_14.log"): txt = re.sub('�Ƃ����킯��v\nKEY\n', '�Ƃ����킯��v\nKEY\nEFF 60\n', txt)


# �C���A�E�g�g�@�A���W�F�����~�o�ɍs��
if(sys.argv[1] == "cs24_02.log"): txt = re.sub('��\\\\eb\\\\b4�j\nKEY\nEFF 4\n', '��\\\\eb\\\\b4�j\nKEY\nEFF 36\nEFF 11\n', txt)
# �t���b�V���@�A���W�F���v�O
if(sys.argv[1] == "cs24_02.log"): txt = re.sub('ICO angl17\nMSG �u�J�C�g', 'EFF 41\nICO angl17\nMSG �u�J�C�g', txt)
# �C���A�E�g�@�A���W�F���̌Ăѐ�
if(sys.argv[1] == "cs24_02.log"): txt = re.sub('�����Ă����B\nKEY\n', '�����Ă����B\nKEY\nEFF 36\nEFF 37\n', txt)
# ����
if(sys.argv[1] == "cs24_03.log"): txt = re.sub('EFF 5\n', '', txt)
# �C���A�E�g�g�@���O
if(sys.argv[1] == "cs24_03.log"): txt = re.sub('EFF 8\n', 'EFF 36\nEFF 11\n', txt)


# ����
if(sys.argv[1] == "cs25_06.log"): txt = re.sub('EFF 5\n', '', txt)
# �L��������
if(sys.argv[1] == "cs25_08.log"): txt = re.sub('BPL 21\n', 'BPL 21\nCLR 2\nEFF 33\n', txt)


# �C���A�E�g�g�@�X�U�N�̕�����
if(sys.argv[1] == "cs26_01.log"): txt = re.sub('EFF 4\nBST', 'EFF 36\nEFF 11\nBST', txt)
# �t���b�V���@�C���A�̍U���i���K�\���R��j
if(sys.argv[1] == "cs26_02.log"): txt = re.sub('SSG 30\n', 'SSG 30\nEFF 41\n', txt)
# ����
if(sys.argv[1] == "cs26_03.log"): txt = re.sub('EFF 5\n', '', txt)


# �z���C�g�C���A�E�g�g�@��z
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('EFF 4\nMSG �����ԑO', 'EFF 34\nWAT 15\nCLR 7\nSET waku06b 1\nEFF 35\nMSG �����ԑO', txt)
# �z���C�g�C���A�E�g�g�@��z�I���i��
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('EFF 4\nPTY pty048', 'EFF 34\nWAT 60\nCLR 7\nSET waku06b 1\nEFF 35\nPTY pty048', txt)
# �A�C�R���ύX�@�E���t�B
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('BGL e049b\nICO wolf0e\n', 'ICO e049b\n', txt)
# �A�C�R���ύX�@�J�C�g
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('BGL e049a\nICO kait18\n', 'ICO e049a\n', txt)
# �z���C�g�C���A�E�g�g�@�t�@�[�~��
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('EFF 7\n', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\n', txt)
# �Ƃǂ�
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('BGL e007_\nBGL e012b2\n', 'BGL e007_\nWAT 100\nSET e012b2 1\nEFF 60\nWAT 20\nSET e007_ 1\nEFF 60\nWAT 20\nSET e012b2 1\nEFF 60\nWAT 20\nSET e007_ 1\nEFF 42\n', txt)
# �t���b�V���R��@�����i�{���͂T�񂾂�ῂ�������ׁj
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('MSG ������', 'EFF 41\nEFF 41\nEFF 41\nMSG ������', txt)
# �z���C�g�C���A�E�g�g�@�퓬�I��
if(sys.argv[1] == "cs26_04.log"): txt = re.sub('EFF 4\nPTY pty050\n', 'EFF 34\nCLR 7\nSET waku06b 1\nEFF 35\nPTY pty050\n', txt)


# �L���������@�E�o���邾��
if(sys.argv[1] == "cs27_01.log"): txt = re.sub('SSG 21\nPTY pty048\n', 'CLR 2\nEFF 33\nSSG 21\nPTY pty048\n', txt)
# �����i���K�\���R��j
if(sys.argv[1] == "cs27_02.log"): txt = re.sub('EFF 5\n', '', txt)
# �C���A�E�g�g�@�C���A�ƃu���[
if(sys.argv[1] == "cs27_02.log"): txt = re.sub('EFF 4\nEFF 10\n', 'EFF 36\nEFF 11\n', txt)
# �C���A�E�g�g�@�u���[�ƃJ�C��
if(sys.argv[1] == "cs27_02.log"): txt = re.sub('BST\nEFF 4\n', 'BST\nEFF 36\nEFF 11\n', txt)
# �z���C�g�C���A�E�g�@�o��
if(sys.argv[1] == "cs27_02.log"): txt = re.sub('BGL bg37\n', 'EFF 34\nCLR 7\nSET bg37 1\nEFF 35\n', txt)


# �C���A�E�g�g�@���̖�
if(sys.argv[1] == "cs28_01.log"): txt = re.sub('EFF 4\nSSG 21\n', 'EFF 36\nEFF 11\nSSG 21\n', txt)
# UD���@���r�BH�P
if(sys.argv[1] == "cs28_02.log"): txt = re.sub('EFF 6\nHSC ca082\n', 'EFF 9\nHSC ca082\n', txt)
# UD���@���r�BH�Q
if(sys.argv[1] == "cs28_02.log"): txt = re.sub('EFF 6\nMSG ����', 'EFF 9\nMSG ����', txt)
# UD���@���r�BH�R
if(sys.argv[1] == "cs28_02.log"): txt = re.sub('EFF 6\nHSC ca083a\n', 'EFF 9\nHSC ca083a\n', txt)
# �z���C�g�C���A�E�g�@���r�BH�I��
if(sys.argv[1] == "cs28_02.log"): txt = re.sub('EFF 6\nLDS', 'EFF 34\nCLR 7\nWAT 30\nEFF 35\nLDS', txt)
# UD���@�A���W�F��H�P
if(sys.argv[1] == "cs28_04.log"): txt = re.sub('EFF 6\nHSC ca085\n', 'EFF 9\nHSC ca085\n', txt)
# UD���@�A���W�F��H�Q
if(sys.argv[1] == "cs28_04.log"): txt = re.sub('EFF 6\nHSC ca086\n', 'EFF 9\nHSC ca086\n', txt)
# �z���C�g�C���A�E�g�@�A���W�F��H�I��
if(sys.argv[1] == "cs28_04.log"): txt = re.sub('EFF 6\nLDS', 'EFF 34\nCLR 7\nSET waku06b 1\nWAT 30\nEFF 35\nLDS', txt)
# ����
if(sys.argv[1] == "cs28_06.log"): txt = re.sub('EFF 6\n', '', txt)


# ---------------------------------------------------------------------------

with open(sys.argv[2], "w") as f:
	f.write(txt)

