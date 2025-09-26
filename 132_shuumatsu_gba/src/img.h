#ifndef __IMG_H__
#define __IMG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define IMG_MAX_CHR_CNT			3
#define IMG_DEF_FADE_CNT		6

enum {
	IMG_EFFECT_CLS00 = 0,		// ���t�F�[�h�i200�ɕύX�j
	IMG_EFFECT_CLS01,			// �J�[�e��
	IMG_EFFECT_CLS02,			// �������킶��
	IMG_EFFECT_CLS03,			// �W����
	IMG_EFFECT_CLS10 = 10,		// �ʏ�R�s�[�i201�ɕύX�j
	IMG_EFFECT_CLS90 = 90,		// �㉺
	IMG_EFFECT_CLS91,			// ���E
	IMG_EFFECT_CLS92,			// �E��
	IMG_EFFECT_CLS93,			// �����������㉺
	IMG_EFFECT_CLS94,			// ���E�M�U�M�U
	IMG_EFFECT_CLS95,			// ���v
	IMG_EFFECT_CLS96,			// �����܂�
	IMG_EFFECT_CLS97,			// ��]�l�p�`
	IMG_EFFECT_CLS98,			// �ϑw
	IMG_EFFECT_CLS99,			// �ǎ�

	// GBA��p
	IMG_EFFECT_FADE = 200,		// ���t�F�[�h�i�������j
	IMG_EFFECT_COPY,			// �ʏ�R�s�[�i�������j
	IMG_EFFECT_TITL,			// �^�C�g���A�j��
	IMG_EFFECT_FADE_OUT,		// �t�F�[�h�A�E�g�i�����F�w�i�j
	IMG_EFFECT_FADE_IN,			// �t�F�[�h�C���@�i�F�w�i�����j
};

//---------------------------------------------------------------------------

typedef struct {
	s32  no;
	s32  cx;
	s32  cy;
	u16* pDat;

	s32  pv;
} ST_IMG_BG;

typedef struct {
	s32  no;
	s32  sx;
	s32  sy;
	s32  cx;
	s32  cy;
	u16* pDat;
	u8*  pMsk;
} ST_IMG_CHR;

typedef struct {

	bool isExec;
	s32  step;
	s32  step2;
	s32  fade;

	s32  eff;
	u8*  pEff;
	s32  cx;
	s32  cy;
	s32  max;

	ST_IMG_BG  bg;
	ST_IMG_CHR chr[IMG_MAX_CHR_CNT];

} ST_IMG;


//---------------------------------------------------------------------------
void ImgInit(void);

void ImgExec(void);
void ImgExecCls(void);
void ImgExecFade(void);
void ImgExecCopy(void);
void ImgExecTitl(void);
void ImgExecFadeOut(void);
void ImgExecFadeIn(void);

void ImgDrawBg(void);
void ImgDrawChr(void);

void ImgClrBg(void);
void ImgClrChr(s32 no);
void ImgClrChrAll(void);

void ImgSetBg(s32 no);
void ImgSetChr(s32 no);
void ImgSetEff(s32 no);
void ImgSetExec(void);
void ImgSetFade(s32 num);
void ImgSetFade2(s32 num);
void ImgSetBgPv(s32 pv);

void ImgLoadExec(void);
void ImgLoadFade(void);

s32  ImgGetFade(void);
s32  ImgGetBgNo(void);

bool ImgIsExec(void);


#ifdef __cplusplus
}
#endif
#endif
