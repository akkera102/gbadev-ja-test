# coding: Shift_JIS

import re
import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Regex(text, file):

	# �ǉ��@�e�L�X�g��
	text = re.sub('�b������������������', '�b���������@�����@������', text)
	text = re.sub('�f�����������������t', '�f�����@�������������@�t', text)
	text = re.sub('�g�`�q�c�c�`�x���j����������', '�g�`�q�c�@�c�`�x���@�j����������', text)
	text = re.sub('�g�`�q�c�c�`�x��', '�g�`�q�c�@�c�`�x��', text)
	text = re.sub('�g�����i�`�l', '�g�����@�i�`�l', text)
	text = re.sub('����������������������', '���������@�����@����������', text)
	text = re.sub('���������j�`�v�k', '���������@�j�`�v�k', text)
	text = re.sub('�m�������v������', '�m�������@�v������', text)

	# �ύX�@�摜�ԍ��̃_�u��w��
	text = re.sub('!g 136', '!g 17', text)
	text = re.sub('!g 140', '!g 15', text)

	# �ύX�@���s(_n)�̐�
	text = re.sub('_n_n_n', '_n_n', text)
	text = re.sub('_n_n', '_n', text)

	# �ύX�@���s(_n)�Ǝw�A�C�R��(_t)�̓���ւ�
	text = re.sub('_n_t', '_t_n', text)

	# �폜�@��R�}���h
	text = re.sub('_w', '', text)
	text = re.sub('_s', '', text)
	text = re.sub('[0-9A-F]{4} !s [0-9]+ [0-9]+\n', '', text)
	text = re.sub('[0-9A-F]{4} !p\n', '', text)
	text = re.sub('[0-9A-F]{4} !c\n', '', text)
	text = re.sub('[0-9A-F]{4} #b\n', '', text)

	# �ʑΉ�
	if(file == 'SCN008.txt'):
		# �ǉ��@���y�[�W�i���b�Z�[�W�E�B���h�E�ɓ���Ȃ��j
		text = re.sub('���k�ƁA�P�O�l', '���k�ƁA_r�P�O�l', text)

	if(file == 'SCN010.txt'):
		# �ύX�@���y�[�W�i���b�Z�[�W�E�B���h�E�ɓ���Ȃ��j
		text = re.sub('���Ђ�v_t_n', '���Ђ�v_r', text)

	if(file == 'SCN013.txt'):
		# �ύX�@���y�[�W�i���b�Z�[�W�E�B���h�E�ɓ���Ȃ��j
		text = re.sub('���Ђ�v_t_n', '���Ђ�v_r', text)

	if(file == 'SCN014.txt'):
		# �ύX�@�X�N���v�g�~�X
		text = re.sub('0B14 !x 49 0', '0B14 !x 51 0', text)

	if(file == 'SCN020.txt'):
		# �ύX�@�I�����A�h���X���폜���ꂽ��
		text = re.sub('0074', '006E', text)
		text = re.sub('01F9', '01F3', text)

	if(file == 'SCN032.txt'):
		# �ύX�@�I�����A�h���X���폜���ꂽ��
		text = re.sub('044F', '044B', text)

	if(file == 'SCN037.txt'):
		# �ύX�@�X�N���v�g�~�X
		text = re.sub('05F1 !x 38 0', '05F1 !x 38 1', text)

	if(file == 'SCN051.txt'):
		# �ύX�@���y�[�W�i���b�Z�[�W�E�B���h�E�ɓ���Ȃ��j
		text = re.sub('�邽�߁A�ނ��', '�邽�߁A_r�ނ��', text)

	if(file == 'SCN053.txt'):
		# �ύX�@���y�[�W�i���b�Z�[�W�E�B���h�E�ɓ���Ȃ��j
		text = re.sub('�����ǁA���̕�', '�����ǁA_r���̕�', text)

	if(file == 'SCN077.txt'):
		# �ύX�@���y�[�W�i���b�Z�[�W�E�B���h�E�ɓ���Ȃ��j
		text = re.sub('�鎖�B_t_n', '�鎖�B_r', text)


	return text

# ---------------------------------------------------------------------------
file = sys.argv[1]

print("scn_re... " + file)

f = open(file, 'r')
text = f.read()
f.close()


text = Regex(text, file)


f = open(file, "w")
f.write(text)
f.close()
