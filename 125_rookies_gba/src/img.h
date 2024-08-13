#ifndef __IMG_H__
#define __IMG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define IMG_VAR_MAX_CNT				5

enum {
	IMG_EFFECT_BLACK_OUT = 1,		//  1.�u���b�N�A�E�g
	IMG_EFFECT_BLACK_IN,			//  2.�u���b�N�C��
	IMG_EFFECT_WHITE_OUT,			//  3.�z���C�g�A�E�g
	IMG_EFFECT_WHITE_IN,			//  4.�z���C�g�C��
	IMG_EFFECT_CURTAIN_OPEN,		//  5.�H�`�G�t�F�N�g���\��
	IMG_EFFECT_CURTAIN_CLOSE,		//  6.�H�`�G�t�F�N�g�����w�i
	IMG_EFFECT_NORMAL_COPY,			//  7.�ʏ�R�s�[
	IMG_EFFECT_FILL_BLACK,			//  8.���h��Ԃ�
	IMG_EFFECT_SCROLL_UD,			//  9.�X�N���[���ォ�牺
	IMG_EFFECT_SCROLL_DU,			// 10.�X�N���[���������

	// �ȍ~�̓e�L�X�g�t�F�[�h����
	IMG_EFFECT_TXT_IN,				// 11.�e�L�X�g�C��
	IMG_EFFECT_TXT_OUT,				// 12.�e�L�X�g�A�E�g
	IMG_EFFECT_LOAD_IN,				// 13.���[�h���C��
	IMG_EFFECT_LOAD_OUT,			// 14.���[�h���A�E�g
	IMG_EFFECT_NORMAL_COPY2,		// 15.�ʏ�R�s�[�i�e�L�X�g�t�F�[�h�Ȃ��j
	IMG_EFFECT_FILL_BLACK2,			// 16.���h��Ԃ��i�e�L�X�g�t�F�[�h�Ȃ��j
	IMG_EFFECT_EMPTY,				// 17.�������Ȃ��i�e�L�X�g�t�F�[�h�Ȃ��j
};

enum {
	IMG_TYPE_SCROLL_DOWN,
	IMG_TYPE_SCROLL_UP,
	IMG_TYPE_LEFT,
};

//---------------------------------------------------------------------------

typedef struct {
	s32  type;
	u16* pDat;
	u16* pPrv;
	s32  cx;
	s32  cy;
} ST_IMG_BG;

typedef struct {
	u16* pDat;
	u16* pPrv;
	u8*  pMsk;
	s32  sx;
	s32  sy;
	s32  cx;
	s32  cy;
} ST_IMG_CHR;

typedef struct {

	bool isEff;
	s32  effNo;
	s32  effWait;			// �G�t�F�N�g�E�F�C�g

	bool isTxt;				// �e�L�X�g�\�����̗L��
	s32  txtFade;			// �e�L�X�g�t�F�[�h�̔Z��
	s32  txtWait;			// �e�L�X�g�E�F�C�g
	s32  stiWait;			// �Î~�E�F�C�g

	s32  var[IMG_VAR_MAX_CNT];

	ST_IMG_BG  bg;
	ST_IMG_CHR chr1;
	ST_IMG_CHR chr2;

} ST_IMG;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgInit(void);
EWRAM_CODE void ImgInitVar(void);

EWRAM_CODE void ImgExec(void);
EWRAM_CODE void ImgExecBlackOut(void);
EWRAM_CODE void ImgExecBlackIn(void);
EWRAM_CODE void ImgExecWhiteOut(void);
EWRAM_CODE void ImgExecWhiteIn(void);
EWRAM_CODE void ImgExecCurtainOpen(void);
EWRAM_CODE void ImgExecCurtainClose(void);
EWRAM_CODE void ImgExecNomarlCopy(void);
EWRAM_CODE void ImgExecFillBlack(void);
EWRAM_CODE void ImgExecScrollUd(void);
EWRAM_CODE void ImgExecScrollDu(void);
EWRAM_CODE void ImgExecTxtIn(void);
EWRAM_CODE void ImgExecTxtOut(void);
EWRAM_CODE void ImgExecLoadIn(void);
EWRAM_CODE void ImgExecLoadOut(void);
EWRAM_CODE void ImgExecEmpty(void);

EWRAM_CODE void ImgDrawBg(void);
EWRAM_CODE void ImgDrawChr(void);
EWRAM_CODE void ImgClrBg(void);
EWRAM_CODE void ImgClrChr(void);

EWRAM_CODE void ImgSetBg(char* p);
EWRAM_CODE void ImgSetScr(char* p, s32 type);
EWRAM_CODE void ImgSetChr1(char* p);
EWRAM_CODE void ImgSetChr2(char* p);
EWRAM_CODE void ImgSetEff(s32 no, s32 wait);

EWRAM_CODE void ImgSetTxtFade(s32 num);
EWRAM_CODE void ImgSetTxtFade2(s32 num);
EWRAM_CODE void ImgSetTxtWait(s32 num);
EWRAM_CODE void ImgSetStiWait(s32 num);
EWRAM_CODE s32  ImgGetTxtFade(void);
EWRAM_CODE s32  ImgGetTxtWait(void);
EWRAM_CODE s32  ImgGetStiWait(void);

EWRAM_CODE bool ImgIsPrevBgChr(void);
EWRAM_CODE bool ImgIsEff(void);
EWRAM_CODE bool ImgIsTxt(void);


#ifdef __cplusplus
}
#endif
#endif
