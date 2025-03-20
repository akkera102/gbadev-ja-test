#ifndef __TXT_H__
#define __TXT_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define TXT_SCREEN_CX					30
#define TXT_SCREEN_CY					3
#define TXT_SCREEN_SIZE					(TXT_SCREEN_CX * TXT_SCREEN_CY)

//---------------------------------------------------------------------------

typedef struct {

	bool  isMsg;		// 描画トリガー
	char* p;
	s32   x;
	s32   y;
	s32   x2;
	s32   y2;

	bool  isOpt;		// 描画トリガー（ＨＰ表示用）
	s32   var1;
	s32   var2;

	bool  isBuf;		// テキスト復帰トリガー
	u16   buf[TXT_SCREEN_SIZE];

	bool  isCur;		// 描画有無
	s32   spr;
	s32   cnt;
	s32   max;
	s32   wait;
	s32   blink;

} ST_TXT;


//---------------------------------------------------------------------------
EWRAM_CODE void TxtInit(void);
EWRAM_CODE void TxtExecMsg(void);
EWRAM_CODE void TxtExecSel(void);
EWRAM_CODE void TxtExecOpt(void);
EWRAM_CODE void TxtExecCur(void);
EWRAM_CODE void TxtExecMenu(void);

EWRAM_CODE void TxtDrawChr(u16 code, bool isBuf);
EWRAM_CODE void TxtDrawStr(char* p, bool isBuf);
EWRAM_CODE void TxtDrawBuf(void);

EWRAM_CODE void TxtSetStr(char* p);
EWRAM_CODE void TxtSetMsg(void);
EWRAM_CODE void TxtSetOpt(bool is, s32 var1, s32 var2);
EWRAM_CODE void TxtSetBuf(void);
EWRAM_CODE void TxtSetCur(void);
EWRAM_CODE void TxtSetCurKey(void);
EWRAM_CODE void TxtSetCurScr(void);
EWRAM_CODE void TxtSetCurPcm(void);
EWRAM_CODE void TxtSetXy2(void);

EWRAM_CODE void TxtClr(void);
EWRAM_CODE void TxtClrMsg(void);
EWRAM_CODE void TxtClrXy(void);
EWRAM_CODE void TxtClrCur(void);

EWRAM_CODE void TxtShowMsg(void);
EWRAM_CODE void TxtShowCur(void);
EWRAM_CODE void TxtHideMsg(void);
EWRAM_CODE void TxtHideCur(void);

EWRAM_CODE bool TxtIsMsg(void);
EWRAM_CODE bool TxtIsCur(void);


#ifdef __cplusplus
}
#endif
#endif
