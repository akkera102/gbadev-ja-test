
# ������z�� for GBA

## ���ē�

���̃\�t�g��PC98�u������z�ȁv��GBA�ֈڐA�������̂ł��B�Q�[���f�[�^�͕t�����Ă��Ȃ��ׁA���i�������Ă�����̂ݗV�ׂ܂��BWindows�ł͐\����Ȃ��̂ł������Ή��ł��B

![README](README.png)

## �C���X�g�[�����@

���L�̃t�@�C�����ugbfs\data�v���ɒu���Ă��������B

```
DISK_A.CAT
DISK_A.LIB
DISK_B.CAT
DISK_B.LIB
DISK_C.CAT
DISK_C.LIB
DISK_D.CAT
DISK_D.LIB
------------
�v8�t�@�C��
```

�ϊ���Ƃɂ�Python3��Pillow���g�p���܂��B�ʓr�C���X�g�[�����s���A�v�����v�g�̃p�X���ʂ��Ă��邱�Ƃ��m�F���Ă��������BMicrosoft Visual C++ Redistributable(Visual Studio 2015, 2017, 2019, and 2022)���C���X�g�[�������肢���܂��B

�umake.bat�v�����s�����ROM�t�@�C���������I�ɍ���܂��Bi5+SSD���ŕϊ����Ԃ�10���قǁB��27MB��ROM�������ΐ����ł��B���Ȃ݂ɃR���o�[�g���ɃG���[���������Ă��~�܂�܂���B��蒼�������ꍇ��DOS�v�����v�g��ʂ���āugbfs\data�v�����ɂ����������ƃt�H���_���폜���Ă��������B�Ȃ��C���X�g�[���[��32bit���p�\�R���ɖ��Ή��ł��B

## ����

- �u������z�ȁv�̓A�v���R�b�g�̒��앨�ł��B
- ���̃\�t�g�Ɋւ���₢���킹���A�v���R�b�g�ɂ��Ȃ��ł��������B
- ���̃\�t�g���g�p���Ĕ����������ȂǁA�����͈�ؐӔC�𕉂��܂���B
- ���p�͌l�Ŏg�p����͈͂ɗ��߂Ă��������B

## �ӎ�

[Four�Nine System-98 ADV/Visual Novel engine](https://github.com/ValleyBell/PC98VNResearch/tree/master/four-nine_system98)

��������Valley Bell����̉�̓c�[�����g�p�����Ă��������܂����B������z�Ȃ̓T�u���[�`���X�N���v�g���p�ӂ���Ă��āA�G�t�F�N�g�A���y�A�ق̌����}�\���Ȃǂ̖�����S�����Ă��܂��B�V�i���I�X�N���v�g�̓T�u���[�`����ʂ��đ�����s���̂ŁACALL�������t�b�N����ΊȒP�ɈڐA��i�߂��܂��B�K�w�\�����肪�����ł��B���[��E�E�E�J�i�����������肾�����烉�N�������̂ɂƎv���܂������ǁA�N��I�ɂ��傤���Ȃ������̂�������܂���B

���ʉ�

��������[hoshi����](https://twitter.com/hoshi903)�ɂ��肢���Ă��܂��B�����Ŏg���Ă�����ʉ��̖����Ԃ肷�݂܂���ł����B���e�C�N�̂������œ������͌��z�I�ȕ��͋C�ɂȂ����Ǝv���܂��B���肪�Ƃ��������܂��B


## ������^�C���i�܂����Ă��E�E�E�j

- GBA�ł͑I�����@�\���G���f�B���O���O�܂Ŏg�p���Ȃ��ł��B���ׁ̈A�T���ŃE���E������K�v������܂���B
- �G���f�B���O�̓I���W�i���Ɠ������I�Ղ܂ŌŒ�ł��B�e�q���C���̃G���f�B���O���[�g��I�����ꗗ���Ă��܂��B
- �كQ�[���̕��͋C���o������1�͂����͓����H�킹�Ă��܂��B�����̖��̂Ȃǂ��m�F���Ă��炦��΂Ǝv���Ă��܂��B
- �����͂Q�K���Ăŕ~�n���ɂ��ړ��G���A������������܂��B
- �̓W�����v�i0-12�j�̓f�o�b�N�p�ł��B�G���f�B���O�����Ă���g�p���Ă��������B
- �v���C���Ԃ�6�`8���Ԓ��x�Ǝv���܂��B
- �T����[���g��PC�������Q�[���U�� @ wiki](https://w.atwiki.jp/retropcgame/pages/566.html)�l���Q�l�ɂ����Ē����܂����B
- �e�o�[�W�����̃Z�[�u�f�[�^�̌݊����͂���܂���B
- ���z��o�O�Ȃǂ���܂����炲[���](https://twitter.com/akkera102)���������B

## ������

- �G���f�B���O�摜�͉�͂ł��Ȃ������̂ŃZ�s�A���ɂȂ�܂���B�{�҉摜���玗���č��܂����i���ʂʁB


## ���C�Z���X

- ���̏�����GBA�\�[�X�R�[�h�iCC0�j
- SYSTEM-98�R���o�[�^�֘A��python�R�[�h�AC�R�[�h�iGPL2�j
- 8AD decoder engine�iMIT�j
- libgba(LGPL2.0 dynamic link)
- crt0.s(MPL2.0)

���ɂ��l�X�ȃc�[����R�[�h���g�킹�Ă��������܂����B����҂̃��C�Z���X�ɏ]���Ă��������B


## �����

- mGBA 0.10.3
- GBA.emu(Android) Feb 25 2024
- EverDrive X5


## �J����

- windows10 pro 64bit
- devkitPro(gcc v13.2.0 devkitARM r63)
- Python3.12.3 + pillow10.3.0
- VisualBoyAdvance v1.8.0-beta3


## �ȒP�ȗ���

2024/04/18 v0.01 �����J


