#ifndef __IMG_H__
#define __IMG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------

enum {
	IMG_BG_NORMAL,
	IMG_BG_VISUAL,
};

enum {
	IMG_CHR_LEFT,
	IMG_CHR_RIGHT,
	IMG_CHR_MID,
	IMG_CHR_ALL,
};

enum {
	IMG_EFFECT_NONE,				// 0x00
	IMG_EFFECT_FADE_PALETTE,
	IMG_EFFECT_FADE_MASK,
	IMG_EFFECT_FADE_SQUARE,
	IMG_EFFECT_WIPE_SQUARE_LTOR,
	IMG_EFFECT_WIPE_MASK_LTOR,
	IMG_EFFECT_SLIDE_LTOR,
	IMG_EFFECT_WIPE_LTOR,
	IMG_EFFECT_NORMAL,
	IMG_EFFECT_TOP_SCROLL,
	IMG_EFFECT_BLOOD,				// 0x0a

	// �ǉ�
	IMG_EFFECT_WHITE = 0x10,
	IMG_EFFECT_TEXT_ON,
	IMG_EFFECT_TEXT_ON_FAST,
	IMG_EFFECT_WIPE_TTOB,
};


//---------------------------------------------------------------------------

typedef struct {

	// ���
	bool isText;

	// �O�G�t�F�N�g
	bool isBefore;
	u8   before;

	// ��G�t�F�N�g
	bool isAfter;
	u8   after;

	// �w�i�A�L�����N�^�ԍ�
	u8   bg;
	u8   bgType;
	u16  chr[3];

	// �ϐ�
	u16  var1;
	u16  var2;
	u16  var3;
	u16  var4;
	u16  var5;
	u16  var6;

	// �I�v�V�����ݒ�
	u16  fadeMax;


} ST_IMG;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgInit(void);
EWRAM_CODE void ImgExec(void);
IWRAM_CODE void ImgExecText(void);
IWRAM_CODE void ImgExecBefore(void);
IWRAM_CODE void ImgExecAfter(void);

EWRAM_CODE void ImgDrawBg(void);
EWRAM_CODE void ImgDrawChr(void);

EWRAM_CODE void ImgSetBg(u8 no);
EWRAM_CODE void ImgSetBgV(u8 no);
EWRAM_CODE void ImgSetChr(u16 no, u8 pos);
EWRAM_CODE void ImgSetEffectBefore(u8 no);
EWRAM_CODE void ImgSetEffectAfter(u8 no);

EWRAM_CODE void ImgShowWindow(void);
EWRAM_CODE void ImgHideWindow(void);

EWRAM_CODE bool ImgIsEffect(void);

EWRAM_CODE void ImgSetFadeMax(u32 num);
EWRAM_CODE u32  ImgGetFadeMax(void);

EWRAM_CODE void ImgRestart(void);


#ifdef __cplusplus
}
#endif
#endif
