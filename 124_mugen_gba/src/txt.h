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

	bool isMsg;				// 表示有無
	bool isChr;				// メッセージ描画有無
	s32  x;					// 文字表示位置
	s32  y;

	// カーソル
	bool isCur;
	bool isCurBlink;
	s32  curWaitCnt;

	// セレクトバッファ
	u16  selBuf[TXT_SCREEN_CX] ALIGN(4);
	s32  selCnt;

	// メッセージバッファ
	u16  msgBuf[TXT_SCREEN_CX * TXT_SCREEN_CY] ALIGN(4);
	s32  msgCnt;

	// 退避用バッファ
	u16  resBuf[TXT_SCREEN_CX * TXT_SCREEN_CY] ALIGN(4);
	bool isBuf;

	// しおり用バッファ
	char sioriBuf[TXT_SIORI_SIZE];

} ST_TXT;


//---------------------------------------------------------------------------
EWRAM_CODE void TxtInit(void);
IWRAM_CODE void TxtExecChr(void);
IWRAM_CODE void TxtExecCur(void);
IWRAM_CODE void TxtExecLog(void);
IWRAM_CODE void TxtExecMenu(void);

EWRAM_CODE void TxtDrawChr(u16 code);
EWRAM_CODE void TxtDrawStr(char* p);
EWRAM_CODE void TxtDrawStr2(s32 x, s32 y, char* p);

EWRAM_CODE void TxtSetChr(void);
EWRAM_CODE void TxtSetCur(bool is);
EWRAM_CODE void TxtSetSel(char* p);
IWRAM_CODE void TxtSetMsg(char* p);
EWRAM_CODE void TxtSetLf(void);
EWRAM_CODE void TxtSetPage(void);
EWRAM_CODE void TxtSetSiori(char* p);

EWRAM_CODE void TxtClear(void);

EWRAM_CODE void TxtShowMsg(void);
EWRAM_CODE void TxtHideMsg(void);

IWRAM_CODE bool TxtIsChrFront(u16 code);
IWRAM_CODE bool TxtIsChrBack(u16 code);
EWRAM_CODE bool TxtIsChr(void);
EWRAM_CODE bool TxtIsCur(void);


#ifdef __cplusplus
}
#endif
#endif
