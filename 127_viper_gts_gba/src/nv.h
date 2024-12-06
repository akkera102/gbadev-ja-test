#ifndef __NV_H__
#define __NV_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define NV_MAX_PARSE_CNT				39
#define NV_MAX_VAR_CNT					256
#define NV_MAX_CALL_CNT					5


enum {
	NV_ACT_PARSE,
	NV_ACT_KEY,
	NV_ACT_SEL,
	NV_ACT_LOAD,
};

//---------------------------------------------------------------------------

typedef struct {
	char* pStr;
	void  (*pFunc)(void);

} ST_NV_PARSE_TABLE;


typedef struct {
	s32   reg;			// 登録数
	s32   ret;			// 選択後の返却先変数
	s32   cnt;			// 現在の選択肢
	char* p[3];			// 選択肢の文字列

} ST_NV_SEL;


typedef struct {
	s32   act;
	s32   step;
	s32   sleep;

	char* pStr;						// スクリプトファイル名
	u8*   pScn;						// スクリプト先頭
	char* pCur;						// カーソル
	u32*  pLbl;						// ジャンプテーブル先頭
	s32   lblMax;					// ジャンプテーブルの個数
	bool  isLoop;


	// 描画完了ウェイト有無
	bool  isBuf;
	s32   bNo;

	// スクロール完了ウェイト有無
	bool  isScr;
	s32   sNo;

	// キー入力時のPCM再生完了ウェイト有無
	bool  isPcm;
	s32   pcmWait;

	// キー入力のスクロール操作と表示有無
	bool  isKeyScr;


	s32   callCnt;
	char* call[NV_MAX_CALL_CNT];

	u16   lastVar;
	u16   var[NV_MAX_VAR_CNT];

	ST_NV_SEL sel;

} ST_NV;


//---------------------------------------------------------------------------
EWRAM_CODE void  NvInit(void);
EWRAM_CODE void  NvExec(void);
EWRAM_CODE void  NvExecKey(void);
EWRAM_CODE void  NvExecSel(void);
EWRAM_CODE void  NvExecLoad(void);

EWRAM_CODE void  NvSetAct(s32 act);
EWRAM_CODE void  NvSetScn(char* pStr);
EWRAM_CODE void  NvSetScn2(s32 no);
EWRAM_CODE void  NvSetScn3(s32 no);
EWRAM_CODE void  NvSetLbl(s32 no);
EWRAM_CODE void  NvSetVar(s32 no, s32 num);

EWRAM_CODE s32   NvGetVar(s32 no);
EWRAM_CODE s32   NvGetSelReg(void);
EWRAM_CODE s32   NvGetSelCnt(void);
EWRAM_CODE char* NvGetSelStr(s32 no);
EWRAM_CODE char* NvGetStr(void);
EWRAM_CODE void  NvPopAct(void);

EWRAM_CODE void  NvPushCall(s32 no);
EWRAM_CODE void  NvPopCall(void);

EWRAM_CODE bool  NvIsActSel(void);

EWRAM_CODE s32   NvNextCurNum(void);
EWRAM_CODE char* NvNextCurStr(void);


#ifdef __cplusplus
}
#endif
#endif

