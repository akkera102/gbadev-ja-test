#ifndef __IMG_H__
#define __IMG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define IMG_VAR_MAX_CNT				5


enum {
	IMG_EFFECT_BLACK_OUT = 1,			//  1.ブラックアウト
	IMG_EFFECT_BLACK_IN,				//  2.ブラックイン
	IMG_EFFECT_WHITE_OUT,				//  3.ホワイトアウト
	IMG_EFFECT_WHITE_IN,				//  4.ホワイトイン
	IMG_EFFECT_FILL_BLACK,				//  5.黒塗りつぶし

	IMG_EFFECT_TXT_OUT = 30,			// 30.テキストアウト
	IMG_EFFECT_TXT_IN,					// 31.テキストイン
	IMG_EFFECT_TXT_HIDE_OUT,			// 32.テキストアウト（非表示のみ）
	IMG_EFFECT_TXT_HIDE_IN,				// 32.テキストイン（表示のみ）
};


//---------------------------------------------------------------------------

typedef struct {

	bool isEff;
	bool isTxt;
	s32  no;
	s32  arg;
	s32  var[IMG_VAR_MAX_CNT];

} ST_IMG;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgInit(void);
EWRAM_CODE void ImgInitVar(void);

EWRAM_CODE void ImgExec(void);
EWRAM_CODE void ImgExecBlackOut(void);
EWRAM_CODE void ImgExecBlackIn(void);
EWRAM_CODE void ImgExecWhiteOut(void);
EWRAM_CODE void ImgExecWhiteIn(void);
EWRAM_CODE void ImgExecFillBlack(void);
EWRAM_CODE void ImgExecTxtOut(void);
EWRAM_CODE void ImgExecTxtIn(void);
EWRAM_CODE void ImgExecTxtHideOut(void);
EWRAM_CODE void ImgExecTxtHideIn(void);

EWRAM_CODE void ImgSetEff(s32 no, s32 arg);

EWRAM_CODE bool ImgIsEff(void);
EWRAM_CODE bool ImgIsTxt(void);


#ifdef __cplusplus
}
#endif
#endif
