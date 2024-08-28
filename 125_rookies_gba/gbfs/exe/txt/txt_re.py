# coding: Shift_JIS

import re
import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
# �W�����v���߂̃A�h���X�\�L��ύX���܂�
def Label(text):
	lines = text.splitlines()
	loc = []

	for line in lines:
		list = line.split()
		elem = [l for l in list if 'loc_' in l]

		if elem:
			adr = elem[0].replace('loc_', '')

			if not adr in loc:
				loc.append(adr)

	loc = sorted(loc)

	i = 0
	for adr in loc:
		# �W�����v���́uloc_�A�h���X�v���u�C���f�b�N�X�ԍ��v�ɒu������
		text = re.sub('loc_' + adr, str(i), text)
		# �W�����v��̓A�h���X��LBL���߂�ǉ�
		text = re.sub(adr, adr + ' LBL ' + str(i) + '\n' + adr, text)
		i = i + 1

	return text

# ---------------------------------------------------------------------------
# ���K�\��
def Regex(text, file):

	# �A�h���X�\�L����
	text = re.sub('[0-9A-F]{4}\\s\n', '', text)
	text = re.sub('[0-9A-F]{4}\\s', '', text)

	# �f�B���N�g���\�L�ύX
	text = re.sub('BG\\\\\\\\', '', text)
	text = re.sub('BGM\\\\\\\\', '', text)
	text = re.sub('BGM\\\\', '', text)
	text = re.sub('CHR\\\\\\\\', '', text)
	text = re.sub('ED\\\\\\\\', '', text)
	text = re.sub('ETC\\\\\\\\', '', text)
	text = re.sub('EV\\\\\\\\', '', text)
	text = re.sub('H\\\\\\\\', '', text)
	text = re.sub('H\\\\', '', text)
	text = re.sub('OP\\\\\\\\', '', text)

	# �g���q�ύX
	text = re.sub('\\.SCP', '', text)
	text = re.sub('\\.MIG', '', text)
	text = re.sub('\\.IDX', '', text)
	text = re.sub('\\.M', '', text)

	# WIN, KABE�\���̏���
	text = re.sub('BGL KABE\n', '', text)
	text = re.sub('BGL WIN\n', '', text)

	# �t�@�C�����ύX
	text = re.sub('BGL YBG_02ITA', 'BGL YBG_02IT', text)

	# �G�t�F�N�g�ύX
	text = re.sub('EFF 2\nEFF 7\nEFF 1\n', 'EFF 2\nEFF 16\nEFF 1\n', text)
	text = re.sub('EFF 7\nEFF 5\n', 'EFF 5\n', text)
	text = re.sub('EFF 9\nEFF 9\n', 'EFF 9\n', text)
	text = re.sub('EFF 10\nEFF 10\n', 'EFF 10\n', text)

	# IPL2�ɖ߂�Ƃ��̓u���b�N�C���G�t�F�N�g���g��Ȃ�
	text = re.sub('EFF 2\nLDS IPL2\n', 'LDS IPL2\n', text)

	# �X�N���[���摜�̃R�}���h�ύX�i�����͏ォ�����̕\���j
	text = re.sub('BGL E_15A', 'SCR 0 E_15A', text)
	text = re.sub('BGL E_15B', 'SCR 0 E_15B', text)
	text = re.sub('BGL E_49C', 'SCR 0 E_49C', text)
	text = re.sub('BGL OP_08A', 'SCR 0 OP_08A', text)
	text = re.sub('BGL OP_01A', 'SCR 0 OP_01A', text)
	text = re.sub('BGL OP_02A', 'SCR 0 OP_02A', text)

	# �ꕔ�̃L�����\���������ς݃L�����w�i�ɕύX
	text = re.sub('BGL BG_12\nBGL ASA_07\n', 'BGL ASA_07\n', text)
	text = re.sub('BGL BG_12\nBGL ASA_08\n', 'BGL ASA_08\n', text)
	text = re.sub('BGL BG_11\nBGL HAZU_02\n', 'BGL HAZU_02\n', text)
	text = re.sub('BGL BG_11\nBGL HAZU_03\n', 'BGL HAZU_03\n', text)
	text = re.sub('BGL BG_11\nBGL HAZU_04\n', 'BGL HAZU_04\n', text)
	text = re.sub('BGL BG_11\nBGL HAZU_05\n', 'BGL HAZU_05\n', text)
	text = re.sub('BGL BG_34\nBGL HIRO_07\n', 'BGL HIRO_07\n', text)
	text = re.sub('BGL BG_34\nBGL HIRO_08\n', 'BGL HIRO_08\n', text)
	text = re.sub('BGL BG_34\nBGL HIRO_09\n', 'BGL HIRO_09\n', text)
	text = re.sub('BGL BG_13\nBGL KYO_03\n', 'BGL KYO_03\n', text)
	text = re.sub('BGL BG_13\nBGL KYO_04\n', 'BGL KYO_04\n', text)

	# �L�����\���̓R�}���h��ύX
	text = re.sub('BGL AIHA_00', 'CHR 1 AIHA_00', text)
	text = re.sub('BGL AIHA_02', 'CHR 1 AIHA_02', text)
	text = re.sub('BGL AIHA_03', 'CHR 1 AIHA_03', text)
	text = re.sub('BGL ARI_00', 'CHR 1 ARI_00', text)
	text = re.sub('BGL ASA_00', 'CHR 1 ASA_00', text)
	text = re.sub('BGL ASA_02', 'CHR 1 ASA_02', text)
	text = re.sub('BGL ASA_03', 'CHR 1 ASA_03', text)
	text = re.sub('BGL ASA_04', 'CHR 1 ASA_04', text)
	text = re.sub('BGL ASA_06', 'CHR 1 ASA_06', text)
	text = re.sub('BGL CHUNE_00', 'CHR 1 CHUNE_00', text)
	text = re.sub('BGL CHUNE_01', 'CHR 1 CHUNE_01', text)
	text = re.sub('BGL CHUNE_02', 'CHR 1 CHUNE_02', text)
	text = re.sub('BGL CHUNE_03', 'CHR 1 CHUNE_03', text)
	text = re.sub('BGL HATA_00', 'CHR 1 HATA_00', text)
	text = re.sub('BGL HAZU_00', 'CHR 1 HAZU_00', text)
	text = re.sub('BGL HAZU_01', 'CHR 1 HAZU_01', text)
	text = re.sub('BGL HAZU_06', 'CHR 1 HAZU_06', text)
	text = re.sub('BGL HIRO_00', 'CHR 1 HIRO_00', text)
	text = re.sub('BGL HIRO_01', 'CHR 1 HIRO_01', text)
	text = re.sub('BGL HIRO_02', 'CHR 1 HIRO_02', text)
	text = re.sub('BGL HIRO_03', 'CHR 1 HIRO_03', text)
	text = re.sub('BGL HIRO_04', 'CHR 1 HIRO_04', text)
	text = re.sub('BGL HIRO_05', 'CHR 1 HIRO_05', text)
	text = re.sub('BGL HIRO_06', 'CHR 1 HIRO_06', text)
	text = re.sub('BGL KYO_00', 'CHR 1 KYO_00', text)
	text = re.sub('BGL KYO_01', 'CHR 1 KYO_01', text)
	text = re.sub('BGL KYO_02', 'CHR 1 KYO_02', text)
	text = re.sub('BGL OUME_00', 'CHR 1 OUME_00', text)
	text = re.sub('BGL RISA_00', 'CHR 1 RISA_00', text)
	text = re.sub('BGL RISA_01', 'CHR 1 RISA_01', text)
	text = re.sub('BGL RISA_02', 'CHR 1 RISA_02', text)
	text = re.sub('BGL RISA_03', 'CHR 1 RISA_03', text)
	text = re.sub('BGL RISA_04', 'CHR 1 RISA_04', text)
	text = re.sub('BGL RISA_05', 'CHR 1 RISA_05', text)
	text = re.sub('BGL RISA_06', 'CHR 1 RISA_06', text)
	text = re.sub('BGL RISA_07', 'CHR 1 RISA_07', text)
	text = re.sub('BGL RISA_07A', 'CHR 1 RISA_07A', text)
	text = re.sub('BGL RISA_08', 'CHR 1 RISA_08', text)
	text = re.sub('BGL RISA_08A', 'CHR 1 RISA_08A', text)
	text = re.sub('BGL RISA_08B', 'CHR 1 RISA_08B', text)
	text = re.sub('BGL RISA_09', 'CHR 1 RISA_09', text)
	text = re.sub('BGL RISA_10', 'CHR 1 RISA_10', text)
	text = re.sub('BGL RISA_12', 'CHR 1 RISA_12', text)
	text = re.sub('BGL RISA_13', 'CHR 1 RISA_13', text)
	text = re.sub('BGL RISA_14', 'CHR 1 RISA_14', text)
	text = re.sub('BGL SAKI_00', 'CHR 1 SAKI_00', text)
	text = re.sub('BGL SAKI_01', 'CHR 1 SAKI_01', text)
	text = re.sub('BGL SAKI_02', 'CHR 1 SAKI_02', text)
	text = re.sub('BGL SAKI_03', 'CHR 1 SAKI_03', text)
	text = re.sub('BGL SAKI_04', 'CHR 1 SAKI_04', text)
	text = re.sub('BGL SATO_00', 'CHR 1 SATO_00', text)
	text = re.sub('BGL SATO_02', 'CHR 1 SATO_02', text)
	text = re.sub('BGL SATO_03', 'CHR 1 SATO_03', text)
	text = re.sub('BGL SATO_04', 'CHR 1 SATO_04', text)
	text = re.sub('BGL SEITO_00', 'CHR 1 SEITO_00', text)
	text = re.sub('BGL SUYA_00', 'CHR 1 SUYA_00', text)
	text = re.sub('BGL SUYA_01', 'CHR 1 SUYA_01', text)
	text = re.sub('BGL TOMO_00', 'CHR 1 TOMO_00', text)
	text = re.sub('BGL YUMI_00', 'CHR 1 YUMI_00', text)
	text = re.sub('BGL YUMI_02', 'CHR 1 YUMI_02', text)
	text = re.sub('BGL YUMI_04', 'CHR 1 YUMI_04', text)
	text = re.sub('BGL YUMI_05', 'CHR 1 YUMI_05', text)
	text = re.sub('BGL YUMI_06', 'CHR 1 YUMI_06', text)

	# �L�����\���̏d���̓��C���[��ύX
	text = re.sub('CHR 1 CHUNE_03\nCHR 1 CHUNE_01', 'CHR 1 CHUNE_03\nCHR 2 CHUNE_01', text)
	text = re.sub('CHR 1 KYO_01\nCHR 1 AIHA_03', 'CHR 1 KYO_01\nCHR 2 AIHA_03', text)
	text = re.sub('CHR 1 KYO_01\nCHR 1 HATA_00', 'CHR 1 KYO_01\nCHR 2 HATA_00', text)
	text = re.sub('CHR 1 HATA_00\nCHR 1 ARI_00', 'CHR 1 HATA_00\nCHR 2 ARI_00', text)
	text = re.sub('CHR 1 HAZU_00\nCHR 1 SAKI_00', 'CHR 1 HAZU_00\nCHR 2 SAKI_00', text)
	text = re.sub('CHR 1 HAZU_00\nCHR 1 SAKI_01', 'CHR 1 HAZU_00\nCHR 2 SAKI_01', text)
	text = re.sub('CHR 1 HAZU_00\nCHR 1 SAKI_02', 'CHR 1 HAZU_00\nCHR 2 SAKI_02', text)
	text = re.sub('CHR 1 HIRO_00\nCHR 1 RISA_00', 'CHR 1 HIRO_00\nCHR 2 RISA_00', text)
	text = re.sub('CHR 1 HIRO_03\nCHR 1 RISA_00', 'CHR 1 HIRO_03\nCHR 2 RISA_00', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 HIRO_00', 'CHR 1 RISA_00\nCHR 2 HIRO_00', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 HIRO_01', 'CHR 1 RISA_00\nCHR 2 HIRO_01', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 HIRO_02', 'CHR 1 RISA_00\nCHR 2 HIRO_02', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 HIRO_03', 'CHR 1 RISA_00\nCHR 2 HIRO_03', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 HIRO_04', 'CHR 1 RISA_00\nCHR 2 HIRO_04', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 HIRO_06', 'CHR 1 RISA_00\nCHR 2 HIRO_06', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 KYO_00', 'CHR 1 RISA_00\nCHR 2 KYO_00', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 KYO_01', 'CHR 1 RISA_00\nCHR 2 KYO_01', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 KYO_02', 'CHR 1 RISA_00\nCHR 2 KYO_02', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 KYO_05', 'CHR 1 RISA_00\nCHR 2 KYO_05', text)
	text = re.sub('CHR 1 RISA_00\nCHR 1 HIRO_00', 'CHR 1 RISA_00\nCHR 2 HIRO_00', text)
	text = re.sub('CHR 1 RISA_01\nCHR 1 HIRO_00', 'CHR 1 RISA_01\nCHR 2 HIRO_00', text)
	text = re.sub('CHR 1 RISA_02\nCHR 1 HIRO_00', 'CHR 1 RISA_02\nCHR 2 HIRO_00', text)
	text = re.sub('CHR 1 RISA_03\nCHR 1 HIRO_00', 'CHR 1 RISA_03\nCHR 2 HIRO_00', text)
	text = re.sub('CHR 1 RISA_04\nCHR 1 KYO_00', 'CHR 1 RISA_04\nCHR 2 KYO_00', text)
	text = re.sub('CHR 1 RISA_05\nCHR 1 KYO_00', 'CHR 1 RISA_05\nCHR 2 KYO_00', text)
	text = re.sub('CHR 1 RISA_05\nCHR 1 KYO_01', 'CHR 1 RISA_05\nCHR 2 KYO_01', text)
	text = re.sub('CHR 1 RISA_06\nCHR 1 KYO_00', 'CHR 1 RISA_06\nCHR 2 KYO_00', text)
	text = re.sub('CHR 1 RISA_08\nCHR 1 KYO_00', 'CHR 1 RISA_08\nCHR 2 KYO_00', text)
	text = re.sub('CHR 1 RISA_08A\nCHR 1 SAKI_03', 'CHR 1 RISA_08A\nCHR 2 SAKI_03', text)
	text = re.sub('CHR 1 RISA_09\nCHR 1 YUMI_04', 'CHR 1 RISA_09\nCHR 2 YUMI_04', text)
	text = re.sub('CHR 1 RISA_10\nCHR 1 HIRO_05', 'CHR 1 RISA_10\nCHR 2 HIRO_05', text)
	text = re.sub('CHR 1 RISA_12\nCHR 1 HIRO_03', 'CHR 1 RISA_12\nCHR 2 HIRO_03', text)

	# ���y�̈ꕔ���P��Đ��֕ύX
	text = re.sub('BGM 1 F1A', 'BGM 0 F1A', text)
	text = re.sub('BGM 1 UMI', 'BGM 0 UMI', text)
	text = re.sub('BGM 1 BGM M78_2', 'BGM 0 BGM M78_2', text)
	text = re.sub('BGM 1 H1', 'BGM 0 H1', text)
	text = re.sub('BGM 1 GAAN\n', 'BGM 0 GAAN\n', text)

	# �ʏC��
	if(file == 'IPL.txt'):
		text = re.sub('EFF 2\nBGL MENULOGO\n', 'WAT 225\nBGS\nLDS IPL2\n', text)

	if(file == 'IPL2.txt'):
		text = re.sub('BGL MENUMAIN\n', 'BGS\nFMS\nEFF 2\nBGL MENULOGO\nEFF 15\nEFF 1\nSTA\n', text)

	if(file == 'TAI.txt'):
		text = re.sub('BGL TAI_00\nEFF 7\nEFF 1\n', 'TAI 0 0 ���@�C�����쏊\nEFF 17\n', text)
		text = re.sub('BGL TAI_01\nEFF 7\n', 'TAI 0 0 �L�����N�^�[�f�U�C��\nTAI 0 1 �����ܕ���\nEFF 17\n', text)
		text = re.sub('BGL TAI_02\nEFF 7\n', 'TAI 0 0 �r�{\nTAI 0 1 ���u�ޖ���\nEFF 17\n', text)
		text = re.sub('BGL TAI_03\nEFF 7\n', 'TAI 0 0 �b�f�ďC\nTAI 0 1 �s�n�l�`\nEFF 17\n', text)
		text = re.sub('BGL TAI_04\nEFF 7\n', 'TAI 0 0 �v���O���}�[\nTAI 0 1 ���쌒��\nEFF 17\n', text)
		text = re.sub('BGL TAI_05\nEFF 7\n', 'TAI 0 0 ���y�E����\nTAI 0 1 �w�������E�ΐ�\nEFF 17\n', text)
		text = re.sub('BGL TAI_06\nEFF 7\n', 'TAI 0 0 �v���f���[�T�[\nTAI 0 1 �s�[�`�E�X�p�C�_�[\nEFF 17\n', text)
		text = re.sub('BGL TAI_07\nEFF 7\n', 'TAI 0 0 �ē�\nTAI 0 1 �������\nEFF 17\n', text)
		text = re.sub('EFF 2\nBGL UMI\n', 'TAI 0 0 �@\nEFF 2\nBGL UMI\n', text)
		text = re.sub('EFF 7\n', 'EFF 15\n', text)

	if(file == 'END.txt'):
		text = re.sub('WAT 160\n', 'WAT 480\n', text)
		text = re.sub('WAT 255\n', 'WAT 765\n', text)

	if(file == '2DAY_A.txt'):
		# �ύX�@�G�t�F�N�g
		text = re.sub('EFF 7\nEFF 1\n', 'EFF 16\nEFF 1\n', text)

	if(file == '4BAD.txt'):
		# �����@�d���G�t�F�N�g
		text = re.sub('BGL BG_30\nEFF 5\n', 'BGL BG_30\nEFF 15\n', text)

	if(file == '5DAY_B.txt'):
		# �ύX�@�G�t�F�N�g�@�w�Z����P��
		text = re.sub('BGL WIN00\nEFF 7\n', 'EFF 16\n', text)
		# �ύX�@�G�t�F�N�g�@����
		text = re.sub('EFF 6\nBGL WIN00\n', '', text)
		# �ǉ��@�G�t�F�N�g�@������z
		text = re.sub('MSG �E�E�E���́E�E�E\nKEY\nBGL BG_03\n', 'MSG �E�E�E���́E�E�E\nKEY\nEFF 6\nBGL BG_03\n', text)

	if(file == '5DAY_D.txt'):
		# �����@�d���G�t�F�N�g�@���ƑΌ�
		text = re.sub('SCR 0 E_49C\nEFF 10\n', 'SCR 0 E_49C\n', text)

	if(file == '5BAD_B.txt'):
		# �����@�d���G�t�F�N�g
		text = re.sub('BGL YBG_08\nEFF 7\n', 'EFF 2\nBGL YBG_08\nEFF 15\n', text)

	# �ꕔ���y�����ʉ��Đ��ɕύX�A��~�R�}���h��ǉ�
	# AME    -> 66
	# JIRIRI -> 67
	# MIZU   -> 68

	# AME
	text = re.sub('BGM 1 AME\n', 'BGS\nFMX 66\n', text)
	if(file == '4DAY_D.txt'):
		text = re.sub('EFF 6\nBGL BG_36\nCHR 1 RISA_00\n', 'EFF 6\nFMS\nBGL BG_36\nCHR 1 RISA_00\n', text)
	if(file == '4DAY_D.txt'):
		text = re.sub('EFF 2\nBGL H_35A\n', 'EFF 2\nFMS\nBGL H_35A\n', text)

	# JIRIRI
	text = re.sub('BGM 1 JIRIRI\n', 'BGS\nFMX 67\n', text)
	if(file == '4DAY_C.txt'):
		text = re.sub('BGM 1 G1\n', 'FMS\nBGM 1 G1\n', text)
	if(file == '5DAY_C.txt'):
		text = re.sub('MSG �E�E�E���͍Z��', 'FMS\nMSG �E�E�E���͍Z��', text)

	# MIZU
	text = re.sub('BGM 1 MIZU\n', 'BGS\nFMX 68\n', text)
	if(file == '1DAY_A.txt'):
		text = re.sub('BGS\nEFF 6\nBGM 1 SUZUME\n', 'FMS\nEFF 6\nBGM 1 SUZUME\n', text)

	# �U������t�^
	if(file == '1DAY_A.txt'): text = re.sub('SEL 10', 'SEL 1', text) # 2 10 �J���Ă݂悤 ���̂܂܂ɂ��Ă�����
	if(file == '1DAY_B.txt'): text = re.sub('SEL 10', 'SEL 1', text) # 2 10 ���������Ă݂悤 ��肷������
	if(file == '1DAY_B.txt'): text = re.sub('SEL 11', 'SEL 0', text) # 3 10 ���ނ��D������ �ؐH��`�҂Ȃ� ����ނ���
	if(file == '1DAY_B.txt'): text = re.sub('SEL 12', 'SEL 0', text) # 2 10 �H���Ă��܂��� ���Ƃ����܂���
	if(file == '1DAY_B.txt'): text = re.sub('SEL 13', 'SEL 3', text) # 4 12 ���p�� �ƒ�Ȏ� ���y�� �Ȋw������
	if(file == '2DAY_A.txt'): text = re.sub('SEL 10', 'SEL 1', text) # 2  0 �C�ɂ����|������ �����`���Ă݂�
	if(file == '2DAY_A.txt'): text = re.sub('SEL 11', 'SEL 1', text) # 2  0 �|���𑱂��� �����`���Ă݂�
	if(file == '2DAY_B.txt'): text = re.sub('SEL 10', 'SEL 0', text) # 2  0 �Ō�܂ŐH���Ă�� �d���Ȃ����^�C�A��
	if(file == '3DAY_A.txt'): text = re.sub('SEL 10', 'SEL 2', text) # 2 13 �Z�ɂɍs�� �Z�O�ɍs��
	if(file == '3DAY_A.txt'): text = re.sub('SEL 11', 'SEL 3', text) # 3 14 �z���Ă�񂾂�H �m��Ȃ��񂾂ȁH �����Ă�񂾂�H
	if(file == '3DAY_B.txt'): text = re.sub('SEL 10', 'SEL 1', text) # 2  0 ��C�ɍU�߂� �l�q������
	if(file == '3DAY_B.txt'): text = re.sub('SEL 11', 'SEL 2', text) # 2  0 ��C�ɍU�߂� �l�q������
	if(file == '3DAY_B.txt'): text = re.sub('SEL 12', 'SEL 1', text) # 2  0 ��C�ɍU�ߗ��Ƃ� �����炸�l�q������
	if(file == '4DAY_A.txt'): text = re.sub('SEL 10', 'SEL 2', text) # 2  0 �Z�ɓ���{���� �Z�ɊO��{����
	if(file == '4DAY_A.txt'): text = re.sub('SEL 11', 'SEL 2', text) # 2  0 ������񌩉߂����Ȃ��A�������Ă��I�I ����A���������l�q�����悤
	if(file == '4DAY_A.txt'): text = re.sub('SEL 12', 'SEL 1', text) # 2  0 �͂� ������
	if(file == '4DAY_A.txt'): text = re.sub('SEL 13', 'SEL 1', text) # 2  0 �͂� ������
	if(file == '4DAY_A.txt'): text = re.sub('SEL 14', 'SEL 1', text) # 2  0 �͂� ������
	if(file == '4DAY_A.txt'): text = re.sub('SEL 15', 'SEL 1', text) # 2  0 �͂� ������
	if(file == '4DAY_A.txt'): text = re.sub('SEL 16', 'SEL 1', text) # 2  0 ������܂��� �����Ă���
	if(file == '4DAY_A.txt'): text = re.sub('SEL 17', 'SEL 1', text) # 2  0 ������܂��� �E�E�E�͂�
	if(file == '4DAY_A.txt'): text = re.sub('SEL 18', 'SEL 1', text) # 2  0 ������܂��� �E�E�E������
	if(file == '4DAY_B.txt'): text = re.sub('SEL 10', 'SEL 1', text) # 2  0 �{�ق�{���� ���ق�{����
	if(file == '4DAY_C.txt'): text = re.sub('SEL 10', 'SEL 3', text) # 3 15 �����Ɠ������ꗬ�̗����l�ɂȂ鎖���B �G�̍˔\�𐶂����Č|�p�ƂɂȂ鎖���B �ق��ċ߂��ɎU��΂��Ă���}���K�G������n��
	if(file == '5DAY_A.txt'): text = re.sub('SEL 10', 'SEL 2', text) # 2  0 �}���ł�񂾁B�܂��V��ł�邩��A���Ⴀ�ȁB �E�E�E���傤���Ȃ��ȁB���������t�������Ă���B
	if(file == '5DAY_A.txt'): text = re.sub('SEL 11', 'SEL 2', text) # 2 16 �E�E�E�N���A�΂������񂾂ȁH �E�E�E������Ɨ��Ă���B
	if(file == '5DAY_C.txt'): text = re.sub('SEL 10', 'SEL 2', text) # 2 17 ������߂ė����̑҂w���Ɍ����� �Ђ�q�ɓd�b��������
	if(file == '5DAY_C.txt'): text = re.sub('SEL 11', 'SEL 2', text) # 2  0 �����E�E�E�l��҂����Ă�񂾁E�E�E ���������E�E�E�����������ɂ��Ă���
	if(file == '5DAY_D.txt'): text = re.sub('SEL 10', 'SEL 1', text) # 3  0 ��i�������I�I �E�������I�I ���������I�I

	return text
# ---------------------------------------------------------------------------
file = sys.argv[1]

print("txt_re... " + file)

f = open(file, 'r')
text = f.read()
f.close()


text = Label(text)
text = Regex(text, file)


f = open(file, "w")
f.write(text)
