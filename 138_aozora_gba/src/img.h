#ifndef __IMG_H__
#define __IMG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------

enum {
	IMG_EFFECT_NORMAL = 1,		//  1.通常コピー
	IMG_EFFECT_ZIRI,			//  2.じりじり
	IMG_EFFECT_ALPHA,			//  3.アルファブレンド（重たいので代用）
	IMG_EFFECT_BLACK_FLASH,		//  4.黒フラッシュ
	IMG_EFFECT_WHITE_FLASH,		//  5.白フラッシュ
	IMG_EFFECT_BLACK_IN,		//  6.背景→黒
	IMG_EFFECT_WHITE_IN,		//  7.背景→白

	// GBA追加
	IMG_EFFECT_BLACK_OUT,		//  8.黒→背景
	IMG_EFFECT_WHITE_OUT,		//  9.白→背景
	IMG_EFFECT_SET_MSG,			// 10.メッセージボックス表示
	IMG_EFFECT_CLR_MSG,			// 12.メッセージボックス非表示
	IMG_EFFECT_LOAD,			// 13.ロード用
	IMG_EFFECT_BOOT,			// 14.起動用
};

//---------------------------------------------------------------------------

typedef struct {

	bool isExec;
	bool isMsg;
	bool isClr;

	s32  step;
	s32  var;

	s32  bg;
	s32  chr;
	s32  eff;
	s32  fade;

} ST_IMG;


//---------------------------------------------------------------------------
void ImgInit(void);

bool ImgExec(void);
void ImgExecNormal(void);
void ImgExecZiri(void);
void ImgExecAlpha(void);
void ImgExecBlackFlash(void);
void ImgExecWhiteFlash(void);
void ImgExecBlackIn(void);
void ImgExecWhiteIn(void);
void ImgExecBlackOut(void);
void ImgExecWhiteOut(void);
void ImgExecSetMsg(void);
void ImgExecClrMsg(void);
void ImgExecLoad(void);
void ImgExecBoot(void);

void ImgDrawBg(void);
void ImgDrawChr(void);

void ImgSetBg(s32 no);
void ImgSetChr(s32 no);
void ImgSetExec(s32 no);
void ImgSetExecCond(s32 no);
void ImgSetNoWait(void);
void ImgSetFade(s32 num);
s32  ImgGetBg(void);
s32  ImgGetFade(void);

bool ImgIsExec(void);


#ifdef __cplusplus
}
#endif
#endif
