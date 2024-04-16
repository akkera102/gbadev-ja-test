#ifndef __IMG_H__
#define __IMG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


enum {
	IMG_EFFECT_BLACK_IN = 1,			// 1  �u���b�N�C��
	IMG_EFFECT_BLACK_OUT,				// 2  �u���b�N�A�E�g
	IMG_EFFECT_WHITE_IN,				// 3  �z���C�g�C��
	IMG_EFFECT_WHITE_OUT,				// 4  �z���C�g�A�E�g
	IMG_EFFECT_BLACK_FILL,				// 5  ���F�h��Ԃ��i�`���Afade�Z�b�g�j
	IMG_EFFECT_BLACK_RECT,				// 6  �w�i���F�@�i�����`�G�t�F�N�g�j
	IMG_EFFECT_CLR_CHR,					// 7  �L���������i�E�F�[�u�G�t�F�N�g�Atxt�ޔ𕜋A�j
	IMG_EFFECT_DRAW_BG,					// 8  �w�i�\���@�i�����`�G�t�F�N�g�j
	IMG_EFFECT_DRAW_CHR,				// 9  �L�����\���i�E�F�[�u�G�t�F�N�g�Atxt�ޔ𕜋A�j
	IMG_EFFECT_VIB,						// 10 ��ʍ��E�U��
	IMG_EFFECT_MAP_IN,					// 11 �}�b�v�\���O
	IMG_EFFECT_MAP_OUT,					// 12 �}�b�v�\����

	IMG_EFFECT_TXT_IN = 30,				// 30
	IMG_EFFECT_TXT_OUT,
	IMG_EFFECT_LOAD_IN,
	IMG_EFFECT_LOAD_OUT,
	IMG_EFFECT_EMPTY,					// 34 �������Ȃ��i�����t�F�[�h�ޔ��j

	IMG_EFFECT_SCROLL_DU_FADE = 60,		// 60 �G���f�B���O�̉���ړ��{�t�F�[�h
	IMG_EFFECT_SCROLL_DC,				// 61 �G���f�B���O�̉������ړ�
	IMG_EFFECT_SCROLL_INIT,				// 62 �G���f�B���O�I�����X�N���[���l��߂�

};

#define IMG_MAP_MAX_CNT				30
#define IMG_VAR_MAX_CNT				10


//---------------------------------------------------------------------------

typedef struct {

	bool isTxt;				// �e�L�X�g�\�����̗L��
	s32  fade;				// �e�L�X�g�̃t�F�[�h�̔Z��
	s32  fadeWait;			// �e�L�X�g�̔w�i�E�F�C�g
	s32  selCol;			// �I�����̐F

	bool isEffect;
	s32  effect;
	s32  var[IMG_VAR_MAX_CNT];

	s32  mapNo;				// �����}�t�@�C���ԍ�
	s32  mapMsg;			// �����}���O�ԍ�

	u16* pBg;
	u16* pChr;
	u8*  pChrMsk;

} ST_IMG;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgInit(void);
EWRAM_CODE void ImgInitVar(void);

EWRAM_CODE void ImgExec(void);
EWRAM_CODE void ImgExecBlackIn(void);
EWRAM_CODE void ImgExecBlackOut(void);
EWRAM_CODE void ImgExecWhiteIn(void);
EWRAM_CODE void ImgExecWhiteOut(void);
EWRAM_CODE void ImgExecBlackFill(void);
EWRAM_CODE void ImgExecBlackRect(void);
EWRAM_CODE void ImgExecClrChr(void);
EWRAM_CODE void ImgExecDrawBg(void);
EWRAM_CODE void ImgExecDrawChr(void);
EWRAM_CODE void ImgExecVib(void);
EWRAM_CODE void ImgExecMapIn(void);
EWRAM_CODE void ImgExecMapOut(void);

EWRAM_CODE void ImgExecTxtIn(void);
EWRAM_CODE void ImgExecTxtOut(void);
EWRAM_CODE void ImgExecLoadIn(void);
EWRAM_CODE void ImgExecLoadOut(void);
EWRAM_CODE void ImgExecEmpty(void);
EWRAM_CODE void ImgExecScrDuFade(void);
EWRAM_CODE void ImgExecScrDc(void);
EWRAM_CODE void ImgExecScrInit(void);

EWRAM_CODE void ImgDrawBgChr(void);
EWRAM_CODE void ImgDrawBg(void);
EWRAM_CODE void ImgDrawChr(void);

EWRAM_CODE void ImgSetBg(char* p);
EWRAM_CODE void ImgSetChr(char* p);
EWRAM_CODE void ImgSetEff(s32 no);
EWRAM_CODE void ImgClrBgChr(void);
EWRAM_CODE void ImgClrBg(void);
EWRAM_CODE void ImgClrChr(void);

EWRAM_CODE s32  ImgGetFade(void);
EWRAM_CODE s32  ImgGetFadeWait(void);
EWRAM_CODE s32  ImgGetSelCol(void);

EWRAM_CODE void ImgSetFade(s32 num);
EWRAM_CODE void ImgSetFade2(s32 num);
EWRAM_CODE void ImgSetFadeWait(s32 num);
EWRAM_CODE void ImgSetSelCol(s32 num);
EWRAM_CODE void ImgSetSelCol2(void);
EWRAM_CODE void ImgSetMap(s32 map, s32 vis);

EWRAM_CODE bool ImgIsEffect(void);
EWRAM_CODE bool ImgIsTxt(void);


#ifdef __cplusplus
}
#endif
#endif
