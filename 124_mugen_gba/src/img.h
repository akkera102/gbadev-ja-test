#ifndef __IMG_H__
#define __IMG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


enum {
	IMG_EFFECT_BLACK_IN = 1,			// 1  ブラックイン
	IMG_EFFECT_BLACK_OUT,				// 2  ブラックアウト
	IMG_EFFECT_WHITE_IN,				// 3  ホワイトイン
	IMG_EFFECT_WHITE_OUT,				// 4  ホワイトアウト
	IMG_EFFECT_BLACK_FILL,				// 5  黒色塗りつぶし（描画後、fadeセット）
	IMG_EFFECT_BLACK_RECT,				// 6  背景黒色　（長方形エフェクト）
	IMG_EFFECT_CLR_CHR,					// 7  キャラ消去（ウェーブエフェクト、txt退避復帰）
	IMG_EFFECT_DRAW_BG,					// 8  背景表示　（長方形エフェクト）
	IMG_EFFECT_DRAW_CHR,				// 9  キャラ表示（ウェーブエフェクト、txt退避復帰）
	IMG_EFFECT_VIB,						// 10 画面左右振動
	IMG_EFFECT_MAP_IN,					// 11 マップ表示前
	IMG_EFFECT_MAP_OUT,					// 12 マップ表示後

	IMG_EFFECT_TXT_IN = 30,				// 30
	IMG_EFFECT_TXT_OUT,
	IMG_EFFECT_LOAD_IN,
	IMG_EFFECT_LOAD_OUT,
	IMG_EFFECT_EMPTY,					// 34 何もしない（文字フェード退避）

	IMG_EFFECT_SCROLL_DU_FADE = 60,		// 60 エンディングの下上移動＋フェード
	IMG_EFFECT_SCROLL_DC,				// 61 エンディングの下中央移動
	IMG_EFFECT_SCROLL_INIT,				// 62 エンディング終了時スクロール値を戻す

};

#define IMG_MAP_MAX_CNT				30
#define IMG_VAR_MAX_CNT				10


//---------------------------------------------------------------------------

typedef struct {

	bool isTxt;				// テキスト表示中の有無
	s32  fade;				// テキストのフェードの濃さ
	s32  fadeWait;			// テキストの背景ウェイト
	s32  selCol;			// 選択肢の色

	bool isEffect;
	s32  effect;
	s32  var[IMG_VAR_MAX_CNT];

	s32  mapNo;				// 見取り図ファイル番号
	s32  mapMsg;			// 見取り図名前番号

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
