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

	// 追加
	IMG_EFFECT_WHITE = 0x10,		// 0x10
	IMG_EFFECT_TXT_ON,
	IMG_EFFECT_TXT_ON_FAST,
	IMG_EFFECT_WIPE_TTOB,
	IMG_EFFECT_TITLE,
	IMG_EFFECT_OP_SCROLL1,			// 0x15
	IMG_EFFECT_OP_SCROLL2,
	IMG_EFFECT_SAKURA1_BLACK,		// 0x17 画面上に桜あり（ブラックイン）
	IMG_EFFECT_SAKURA1_WHITE,		// 0x18 画面上に桜あり（ホワイトイン）
	IMG_EFFECT_SAKURA2,				// 0x19 画面外から桜
	IMG_EFFECT_SHAKE,				// 0x20 どかっ
};


//---------------------------------------------------------------------------

typedef struct {

	// 状態
	bool isTxt;

	// 前エフェクト
	bool isBefore;
	u8   before;

	// 後エフェクト
	bool isAfter;
	u8   after;

	// 背景、キャラクタ番号
	u8   bg;
	u8   bgType;
	u16  chr[3];

	// 変数
	u16  var1;
	u16  var2;
	u16  var3;
	u16  var4;
	u16  var5;
	u16  var6;

	// オプション設定
	u16  fadeMax;

} ST_IMG;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgInit(void);
EWRAM_CODE void ImgExec(void);
IWRAM_CODE void ImgExecTxt(void);
IWRAM_CODE void ImgExecBefore(void);
IWRAM_CODE void ImgExecAfter(void);

EWRAM_CODE void ImgDrawBg(void);
EWRAM_CODE void ImgDrawChr(void);

EWRAM_CODE void ImgSetBg(u8 no);
EWRAM_CODE void ImgSetVis(u8 no);
EWRAM_CODE void ImgSetChr(u16 no, u8 pos);
EWRAM_CODE void ImgSetChrClr(void);
EWRAM_CODE void ImgSetEffectBefore(u8 no);
EWRAM_CODE void ImgSetEffectAfter(u8 no);
EWRAM_CODE u16  ImgGetChr(u8 no);

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
