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
def Regex(text, file):

	if(file == 'GTS0.txt'):
		# ���6  �G���W�����̃E�F�C�g����
		text = re.sub('0CE5: PCM ENGINE 2', '0CE5: PCM ENGINE 4', text)
		# ���6  �Q�[���{�҂Ɉړ�
		text = re.sub('0E3E: WIN MAIN\n', '0E3E: WIN GTS1\n', text)

	if(file == 'GTS1.txt'):
		# ���8 �J�����o��X�N���[���̃X�s�[�h�ύX
		text = re.sub('1\n034A:', '2\n034A:', text)
		# ���11 �X�N���[���w��ύX�A�E�F�C�g�l�ύX
		text = re.sub('0B15: BUF 0', '0B15: BUF 1', text)
		text = re.sub('0B38: BUF 1', '0B38: BUF 0', text)
		text = re.sub('90\n0B38:', '50\n0B38:', text)
		text = re.sub('0C2A: WAY 0', '0C2A: WAY 1', text)
		text = re.sub('0C2C: BUF 0\n', '', text)
		text = re.sub('0C39: BUF 1', '0C39: BUF 0', text)
		text = re.sub('0F59: BUF 0', '0F59: BUF 1', text)
		text = re.sub('0F70: BUF 1', '0F70: BUF 0', text)
		# ���16 ���d�X�N���[���폜
		text = re.sub('19F3:.*\n', '', text)
		text = re.sub('1A00: BUF 1', '1A00: BUF 0', text)
 		# ���19 ���d�X�N���[���폜
		text = re.sub('25FD:.*\n', '', text)
		text = re.sub('260A: BUF 1', '260A: BUF 0', text)
 		# ���19 �X���[�v����
		text = re.sub('263F: SLP 100', '263F: SLP 10', text)
		# ���22 ���d�X�N���[���폜
		text = re.sub('2BE0:.*\n', '', text)
		text = re.sub('2BED: BUF 1', '260A: BUF 0', text)

	if(file == 'GTS2.txt'):
		# ���27 �����̉�������
		text = re.sub('074A: PCM BIRIDON2 2', '074A: PCM BIRIDON2 4', text)
		# ���27 ������ʂ̃t���[���E�F�C�g�ύX
		text = re.sub('0770: SLP 180', '0770: SLP 100', text)
		# ���31 �o�b�t�@�l��ύX
		text = re.sub('28B9: BUF 3', '28B9: BUF 0', text)
		# ���35 ��ʂ��c��@�h��Ԃ��{�t�F�[�h�A�E�g
		text = re.sub('3784:.*\n', '3784: EFF 5 0\n', text)
		text = re.sub('3791:.*\n', '', text)
		text = re.sub('3804:.*\n', '3804: EFF 5 0\n', text)
		text = re.sub('3811:.*\n', '3811: EFF 1 255\n', text)
		# ���35 ��ʂ��c��@�h��Ԃ�
		text = re.sub('3A45:.*\n', '3A45: EFF 5 0\n', text)
		# ���36 ��ʂ��c��@�h��Ԃ�
		text = re.sub('2DA4:.*\n', '2DA4: EFF 5 0\n', text)
		text = re.sub('2DB1:.*\n', '', text)
		text = re.sub('2DEB: EFF 2 1\n', '2DEB: EFF 1 255\n2DEB: EFF 2 1\n', text)
		# ���36 �X�N���[���摜�R�}���h���g�p���̒��߂Ɉړ�
		text = re.sub('30BA:.*\n', '', text)
		text = re.sub('31E0:', '31E0: BUI 0 19\n31E0:', text)
		# ���37 �t���b�V����̃E�F�C�g����
		text = re.sub('31C3: SLP 50', '31C3: SLP 25', text)
		text = re.sub('31CA: SLP 100', '31CA: SLP 50', text)
		text = re.sub('31D1: SLP 100', '31D1: SLP 50', text)
		text = re.sub('31D8: SLP 200', '31D8: SLP 100', text)
		# ���37 �d���X�N���[���폜
		text = re.sub('3221:.*\n', '', text)
		text = re.sub('3246: BUF 1', '3246: BUF 0', text)
		text = re.sub('328E:.*\n', '', text)
		text = re.sub('329B: BUF 1', '329B: BUF 0', text)
		# ���39 ��ʂ��c��@�h��Ԃ��{�z���C�g�C��
		text = re.sub('48F6:.*\n', '48F6: EFF 5 0\n', text)
		text = re.sub('4903:.*\n', '4903: EFF 4 2\n', text)
		# ���132 ��ʂ��c��@�h��Ԃ�
		text = re.sub('32D9:.*\n', '32D9: EFF 5 0\n', text)
		text = re.sub('32E6:.*\n', '', text)
		text = re.sub('3368: EFF 2 1\n', '3368: EFF 1 255\n3368: EFF 2 1\n', text)
		# ���137 �t���b�V����̃E�F�C�g����
		text = re.sub('3CDA: SLP 50', '3CDA: SLP 25', text)
		text = re.sub('3CE1: SLP 100', '3CE1: SLP 50', text)
		text = re.sub('3CE8: SLP 100', '3CE8: SLP 50', text)
		text = re.sub('3CEF: SLP 200', '3CE8: SLP 100', text)
		# ���137 �d���X�N���[���폜
		text = re.sub('3D38:.*\n', '', text)
		text = re.sub('3D5D: BUF 1', '329B: BUF 0', text)
		text = re.sub('3DA5:.*\n', '', text)
		text = re.sub('3DB2: BUF 1', '3DB2: BUF 0', text)

	if(file == 'GTS3.txt'):
		# ���40 ����ANM��ύX
		text = re.sub('02F1: ANM G040', '02F1: ANM G026', text)
		# ���40 �����̉�������
		text = re.sub('058E: PCM BIRIDON2 2', '058E: PCM BIRIDON2 4', text)
		# ���40 �����̃E�F�C�g�ύX
		text = re.sub('05B4: SLP 180', '05B4: SLP 100', text)
		# ���51 ���b�Z�[�W�t�F�[�h�Ɖ�ʃt�F�[�h�����ׁA�h��Ԃ��Ή�
		text = re.sub('1C33:.*\n', '1C33: EFF 5 0\n', text)
		text = re.sub('1C40:.*\n', '', text)
		# ���56 ��ʂ��c��@�h��Ԃ��{�t�F�[�h�A�E�g
		text = re.sub('24DE:.*\n', '24DE: EFF 5 0\n', text)
		text = re.sub('24EB:.*\n', '', text)
		text = re.sub('2551: EFF 2 2\n', '2551: EFF 1 255\n2551: EFF 2 2\n', text)
		# ���64 ��ʂ��c��@�h��Ԃ��{�z���C�g�C��
		text = re.sub('3557:.*\n', '3557: EFF 5 0\n', text)
		text = re.sub('3564:.*\n', '3564: EFF 4 2\n', text)
		# ���70 �V�g�o��@�d���X�N���[���폜
		text = re.sub('3F15:.*\n', '', text)
		text = re.sub('3F22: BUF 1', '3F22: BUF 0', text)
		text = re.sub('3F51:.*\n', '', text)
		# ���71 ��ʂ��c��@�h��Ԃ��{�t�F�[�h�A�E�g
		text = re.sub('432E:', '432E: EFF 5 0\n432E: EFF 1 255\n432E:', text)
		# ���155 ��ʂ��c��@�h��Ԃ�
		text = re.sub('2A87:.*\n', '2A87: EFF 5 0\n', text)
		text = re.sub('2A94:.*\n', '', text)

	if(file == 'GTS4.txt'):
		# ���73 ��ʂ��c��@�h��Ԃ�
		text = re.sub('0D59:.*\n', '0D59: EFF 5 0\n', text)
		text = re.sub('0D66:.*\n', '', text)
		# ���74 ��ʂ��c��@�h��Ԃ�
		text = re.sub('0E52:.*\n', '0E52: EFF 5 0\n', text)
		text = re.sub('0E5F:.*\n', '', text)
		text = re.sub('0EF0:', '0EF0: EFF 1 255\n0EF0:', text)
		# ���78 �E�F�C�g����
		text = re.sub('1857: SLP 400', '1857: SLP 200', text)
		# ���78 PCM�Đ��폜
		text = re.sub('1863:.*\n', '', text)
		# ���78 ��ʂ��c��@�h��Ԃ�
		text = re.sub('1873:.*\n', '1873: EFF 5 0\n', text)
		text = re.sub('1880:.*\n', '', text)
		# ���79 ��ʂ��c��@�h��Ԃ�
		text = re.sub('191F:.*\n', '191F: EFF 5 0\n', text)
		# ���80 ��ʂ��c��@�h��Ԃ�
		text = re.sub('1B2F:.*\n', '1B2F: EFF 5 0\n', text)
		# ���81 �t�F�[�h�A�E�g�ǉ�
		text = re.sub('1B38:', '1B38: EFF 1 255\n1B38:', text)
		# ���81 �d���X�N���[���폜
		text = re.sub('1B70:.*\n', '', text)
		text = re.sub('1B7D: BUF 1', '1B7D: BUF 0', text)
		# ���82 ��ʂ��c��@�h��Ԃ�
		text = re.sub('1C14:', '1C14: EFF 5 0\n1C14:', text)
		# ���82 �d���`��
		text = re.sub('1C2D:.*\n', '', text)
		# ���83 �d���X�N���[���폜
		text = re.sub('1D9E:.*\n', '', text)
		text = re.sub('1DAB: BUF 1', '1DAB: BUF 0', text)
		# ���84 �d���X�N���[���폜
		text = re.sub('2083: BUF 1', '2083: BUF 0', text)
		# ���91 ���b�Z�[�W�t�F�[�h�Ɖ�ʃt�F�[�h�����ׁA�h��Ԃ��Ή�
		text = re.sub('25E8:.*\n', '25E8: EFF 5 0\n', text)
		# ���92 �t�F�[�h�A�E�g�ǉ�
		text = re.sub('2620:', '2620: EFF 1 255\n2620:', text)
		# ���92 �d���X�N���[���폜
		text = re.sub('2668:.*\n', '', text)
		text = re.sub('2675: BUF 1', '2675: BUF 0', text)
		# ���99 ��ʂ��c��@�h��Ԃ�
		text = re.sub('38D4:.*\n', '1873: EFF 5 0\n', text)
		text = re.sub('38E1:.*\n', '', text)
		# ���99 �t�F�[�h�A�E�g�ǉ�
		text = re.sub('38FC:', '38FC: EFF 1 255\n38FC:', text)
		# ���100 �t���b�V���t���[���ƃG�t�F�N�g�폜
		text = re.sub('392B:.*\n', '', text)
		text = re.sub('3955:.*\n', '', text)
		# ���100 �E�F�C�g����
		text = re.sub('395E: SLP 400', '1857: SLP 200', text)
		# ���100 PCM�Đ��폜
		text = re.sub('3966:.*\n', '', text)
		# ���100 ��ʂ��c��@�h��Ԃ�
		text = re.sub('3976:.*\n', '1873: EFF 5 0\n', text)
		text = re.sub('3983:.*\n', '', text)


	# �Q�[���^�C�g���ƃ��j���[�\���AGTS0�ւ̑J�ڒǉ�
	if(file == 'MAIN.txt'):
		text = re.sub('^', 'EFF 1 255\nANM GTS_TIT\nPAL\nBUF 0 0 1 3 1\nWAB 0\nEFF 2 2\nWAI\nTXC\nEFF 1 2\nEFF 5 0\nSLP 50\nWIN GTS0\n', text)

	# ���S�\����̓��j���[��ʕ\��
	if(file == 'START.txt'):
		text = re.sub('00C3: WIN GTS0\n', '0E3E: WIN MAIN\n', text)

	# �L�[���͌�̃E�F�C�g�𒲐�
	if(file == 'GTS0.txt'):
		text = re.sub('0E4B: SLP 50', '0E4B: SLP 25', text)
	if(file == 'GTS1.txt'):
		text = re.sub('3A38: SLP 30', '3A38: SLP 5', text)
	if(file == 'GTS2.txt'):
		text = re.sub('4926: SLP 30', '4926: SLP 5', text)
	if(file == 'GTS3.txt'):
		text = re.sub('462E: SLP 30', '462E: SLP 5', text)
	if(file == 'GTS4.txt'):
		text = re.sub('4080: SLP 30', '4080: SLP 5', text)

	# ���g�p��WINDOW�i�g�j�����������A�G�t�F�N�g������
	if(file == 'GTS1.txt'):
		text = re.sub('009A:.*\n', '', text)
		text = re.sub('009C:.*\n', '', text)
		text = re.sub('00A9:.*\n', '', text)
		text = re.sub('00AB: EFF 2 2', '00AB: EFF 2 255', text)
	if(file == 'GTS2.txt'):
		text = re.sub('00AB:.*\n', '', text)
		text = re.sub('00AD:.*\n', '', text)
		text = re.sub('00BA:.*\n', '', text)
		text = re.sub('00BC: EFF 2 2', '00BC: EFF 2 255', text)
	if(file == 'GTS3.txt'):
		text = re.sub('00A9:.*\n', '', text)
		text = re.sub('00AB:.*\n', '', text)
		text = re.sub('00B8:.*\n', '', text)
		text = re.sub('00BA: EFF 2 2', '00BA: EFF 2 255', text)
	if(file == 'GTS4.txt'):
		text = re.sub('009A:.*\n', '', text)
		text = re.sub('009C:.*\n', '', text)
		text = re.sub('00A9:.*\n', '', text)
		text = re.sub('00AB: EFF 2 2', '00AB: EFF 2 255', text)
	if(file == 'START.txt'):
		text = re.sub('006E:.*\n', '', text)

	# �A�h���X�\�L�͍폜
	text = re.sub('[0-9A-F]{4}: \n', '', text)
	text = re.sub('[0-9A-F]{4}: ', '', text)

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
