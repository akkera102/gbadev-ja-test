#ifndef __IMG_H__
#define __IMG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define IMG_PTY_CX			96
#define IMG_PTY_CY			160
#define IMG_ICO_CX			56
#define IMG_ICO_CY			56
#define IMG_MIN_CX			56
#define IMG_MIN_CY			56

enum {
	// スクリプトで決め打ちしたエフェクト
	IMG_EFFECT_SCRIPT_1 = 1,
	IMG_EFFECT_SCRIPT_2,
	IMG_EFFECT_SCRIPT_3,
	IMG_EFFECT_SCRIPT_4,
	IMG_EFFECT_SCRIPT_5,
	IMG_EFFECT_SCRIPT_6,
	IMG_EFFECT_SCRIPT_7,
	IMG_EFFECT_SCRIPT_8,
	IMG_EFFECT_SCRIPT_9,
	IMG_EFFECT_SCRIPT_10,
	IMG_EFFECT_SCRIPT_11,
	IMG_EFFECT_SCRIPT_12,
	IMG_EFFECT_SCRIPT_13,
	IMG_EFFECT_SCRIPT_14,
	IMG_EFFECT_SCRIPT_15,

	// img.cで使用されるエフェクト
	IMG_EFFECT_NONE = 30,			// 30
	IMG_EFFECT_NORMAL,				// 31
	IMG_EFFECT_WIPE_LR,				// 32
	IMG_EFFECT_WIPE_UD,				// 33
	IMG_EFFECT_FADE_WHITE_IN,		// 34
	IMG_EFFECT_FADE_WHITE_OUT,		// 35
	IMG_EFFECT_FADE_BLACK_IN,		// 36
	IMG_EFFECT_FADE_BLACK_OUT,		// 37
	IMG_EFFECT_SCROLL_UD,			// 38
	IMG_EFFECT_SCROLL_DU,			// 39
	IMG_EFFECT_FALL,				// 40
	IMG_EFFECT_FLASH,				// 41
	IMG_EFFECT_FLASH2,				// 42
	IMG_EFFECT_BUFFER,				// 43
	IMG_EFFECT_TXT_IN,				// 44
	IMG_EFFECT_TXT_OUT,				// 45

	// 以降はテキストフェード処理を無視したエフェクト
	IMG_EFFECT_IGNORE_NORMAL = 60,	// 60
	IMG_EFFECT_IGNORE_LOAD_IN,		// 61
	IMG_EFFECT_IGNORE_LOAD_OUT,		// 62
	IMG_EFFECT_IGNORE_BG_CHR_SCR,	// 63
	IMG_EFFECT_IGNORE_WAIT_ICO,		// 64
};

enum {
	IMG_TYPE_LEFT,
	IMG_TYPE_CENTER,
	IMG_TYPE_BLACK_BG,
	IMG_TYPE_SCROLL_DU,
	IMG_TYPE_SCROLL_UD,
};

//---------------------------------------------------------------------------

typedef struct {

	bool isTxt;				// テキスト表示中の有無
	s32  fade;				// テキストのフェードの濃さ
	s32  fadeWait;			// テキストの背景ウェイト
	s32  selCol;			// 選択肢の色

	bool isEffect;
	s32  effect;
	s32  var[10];

	u16* pBg;
	s32  bgCx;
	s32  bgCy;
	s32  bgType;

	u16* pChr1;
	u8*  pChr1Msk;
	s32  chr1Cx;
	s32  chr1Cy;

	u16* pChr2;
	u8*  pChr2Msk;
	s32  chr2Cx;
	s32  chr2Cy;

	u16* pPty;
	u16* pIco;
	u16* pMin;

} ST_IMG;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgInit(void);
EWRAM_CODE void ImgInitVar(void);

EWRAM_CODE void ImgExec(void);
EWRAM_CODE void ImgExecNone(void);
EWRAM_CODE void ImgExecNormal(void);
EWRAM_CODE void ImgExecWipeLr(void);
EWRAM_CODE void ImgExecWipeUd(void);
EWRAM_CODE void ImgExecFadeWhiteIn(void);
EWRAM_CODE void ImgExecFadeWhiteOut(void);
EWRAM_CODE void ImgExecFadeBlackIn(void);
EWRAM_CODE void ImgExecFadeBlackOut(void);
EWRAM_CODE void ImgExecScrollUd(void);
EWRAM_CODE void ImgExecScrollDu(void);
EWRAM_CODE void ImgExecFall(void);
EWRAM_CODE void ImgExecFlash(void);
EWRAM_CODE void ImgExecFlash2(void);
EWRAM_CODE void ImgExecBuffer(void);

EWRAM_CODE void ImgExecTxtIn(void);
EWRAM_CODE void ImgExecTxtOut(void);
EWRAM_CODE void ImgExecLoadIn(void);
EWRAM_CODE void ImgExecLoadOut(void);
EWRAM_CODE void ImgExecBgChrScr(void);
EWRAM_CODE void ImgExecWaitIco(void);

EWRAM_CODE void ImgDrawBuf(void);
EWRAM_CODE void ImgDrawVram(void);
EWRAM_CODE void ImgDrawVramClear(void);
EWRAM_CODE void ImgDrawBg(void);
EWRAM_CODE void ImgDrawChr1(void);
EWRAM_CODE void ImgDrawChr2(void);
EWRAM_CODE void ImgDrawPty(void);
EWRAM_CODE void ImgDrawIco(void);
EWRAM_CODE void ImgDrawIcoClear(void);
EWRAM_CODE void ImgDrawMin(void);
EWRAM_CODE void ImgDrawMinClear(void);

EWRAM_CODE void ImgSetBg(char* p);
EWRAM_CODE void ImgSetBgl(char* p);
EWRAM_CODE void ImgSetBgc(char* p);
EWRAM_CODE void ImgSetBgb(char* p);
EWRAM_CODE void ImgSetChr1(char* p);
EWRAM_CODE void ImgSetChr2(char* p);
EWRAM_CODE void ImgSetPty(char* p);
EWRAM_CODE void ImgSetIco(char* p);
EWRAM_CODE void ImgSetMin(char* p);
EWRAM_CODE void ImgSetScrDu(char* p);
EWRAM_CODE void ImgSetScrUd(char* p);
EWRAM_CODE void ImgSetEff(s32 no);
EWRAM_CODE void ImgSetEffTxt(s32 no);

EWRAM_CODE void ImgClrAll(void);
EWRAM_CODE void ImgClrBg(void);
EWRAM_CODE void ImgClrChr1(void);
EWRAM_CODE void ImgClrChr2(void);
EWRAM_CODE void ImgClrPty(void);
EWRAM_CODE void ImgClrIco(void);
EWRAM_CODE void ImgClrMin(void);

EWRAM_CODE s32  ImgGetFade(void);
EWRAM_CODE s32  ImgGetFadeWait(void);
EWRAM_CODE s32  ImgGetSelCol(void);
EWRAM_CODE void ImgSetFade(s32 num);
EWRAM_CODE void ImgSetFade2(s32 num);
EWRAM_CODE void ImgSetFadeWait(s32 num);
EWRAM_CODE void ImgSetSelCol(s32 num);

EWRAM_CODE bool ImgIsEffect(void);
EWRAM_CODE bool ImgIsTxt(void);


#ifdef __cplusplus
}
#endif
#endif
