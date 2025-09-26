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
	IMG_EFFECT_CLS00 = 0,		// αフェード（200に変更）
	IMG_EFFECT_CLS01,			// カーテン
	IMG_EFFECT_CLS02,			// 中央じわじわ
	IMG_EFFECT_CLS03,			// 集中線
	IMG_EFFECT_CLS10 = 10,		// 通常コピー（201に変更）
	IMG_EFFECT_CLS90 = 90,		// 上下
	IMG_EFFECT_CLS91,			// 左右
	IMG_EFFECT_CLS92,			// 右左
	IMG_EFFECT_CLS93,			// 中央横線→上下
	IMG_EFFECT_CLS94,			// 左右ギザギザ
	IMG_EFFECT_CLS95,			// 時計
	IMG_EFFECT_CLS96,			// うずまき
	IMG_EFFECT_CLS97,			// 回転四角形
	IMG_EFFECT_CLS98,			// 積層
	IMG_EFFECT_CLS99,			// 壁紙

	// GBA専用
	IMG_EFFECT_FADE = 200,		// αフェード（高速化）
	IMG_EFFECT_COPY,			// 通常コピー（高速化）
	IMG_EFFECT_TITL,			// タイトルアニメ
	IMG_EFFECT_FADE_OUT,		// フェードアウト（黒→色背景）
	IMG_EFFECT_FADE_IN,			// フェードイン　（色背景→黒）
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
