#ifndef __TXT_H__
#define __TXT_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define TXT_SCREEN_CX					17
#define TXT_SCREEN_CY					10
#define TXT_CURSOR_WAIT_CNT				30
#define TXT_SIORI_SIZE					(22+1)


//---------------------------------------------------------------------------
typedef struct {

	// 表示有無
	bool isShow;

	// 改ページ有無
	bool isPage;

	// テキスト復帰
	bool isRes;

	// 文字表示
	u8   x;
	u8   y;

	// 文字表示
	bool isChr;
	u8   drawCnt;
	u8   waitCnt;
	u8   waitMax;

	// カーソル
	bool isCur;
	bool isCurBlink;
	u8   curCnt;

	// 禁則文字処理ワークエリア
	u16  work[TXT_SCREEN_CX * TXT_SCREEN_CY] ALIGN(4);
	u8   workCnt;

	// メッセージ退避用バッファ
	u16  buf[TXT_SCREEN_CX * TXT_SCREEN_CY] ALIGN(4);
	bool isBuf;

	// しおり用バッファ
	char siori[TXT_SIORI_SIZE];

} ST_TXT;


//---------------------------------------------------------------------------
EWRAM_CODE void TxtInit(void);
EWRAM_CODE void TxtExecChr(void);
EWRAM_CODE void TxtExecCur(void);
EWRAM_CODE void TxtExecLog(void);
EWRAM_CODE void TxtExecMenu(void);

EWRAM_CODE void TxtDrawChr(u16 code);
EWRAM_CODE void TxtDrawStr(char* p);
EWRAM_CODE void TxtDrawStrXy(u32 x, u32 y, char* p);
EWRAM_CODE void TxtDrawWork(void);
EWRAM_CODE void TxtDrawLog(void);
EWRAM_CODE void TxtDrawMenu(void);
EWRAM_CODE void TxtDrawFull(u16* pStr);

EWRAM_CODE void TxtSetChr(void);
EWRAM_CODE void TxtSetCur(bool is);
EWRAM_CODE void TxtSetRes(void);
EWRAM_CODE void TxtSetPage(void);
EWRAM_CODE void TxtSetPageNew(void);
EWRAM_CODE void TxtSetDraw(char* p);
IWRAM_CODE bool TxtCalcStr(char* p);
IWRAM_CODE bool TxtIsChrFront(u16 code);
IWRAM_CODE bool TxtIsChrBack(u16 code);

EWRAM_CODE void TxtClear(void);
EWRAM_CODE void TxtClearBuf(void);
EWRAM_CODE void TxtClearDat(void);
EWRAM_CODE void TxtClearXY(void);

EWRAM_CODE void TxtShowWindow(void);
EWRAM_CODE void TxtShowMsg(void);
EWRAM_CODE void TxtHideWindow(void);
EWRAM_CODE void TxtHideMsg(void);

EWRAM_CODE bool TxtIsChr(void);
EWRAM_CODE bool TxtIsCur(void);

EWRAM_CODE void TxtSetSiori(char* p);

EWRAM_CODE void TxtSetWaitMax(u32 num);
EWRAM_CODE u32  TxtGetWaitMax(void);

EWRAM_CODE void TxtRestart(void);

EWRAM_CODE void TxtSetLf(void);
EWRAM_CODE void TxtSetBuf(bool is);



#ifdef __cplusplus
}
#endif
#endif
