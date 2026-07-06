#ifndef __NV_H__
#define __NV_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define NV_MAX_PARSE_CNT				22
#define NV_MAX_SEL_CNT					6

enum {
	NV_ACT_PARSE,
	NV_ACT_KEY,
	NV_ACT_SEL,
	NV_ACT_JUMP,
};

//---------------------------------------------------------------------------

typedef struct {
	s32 reg;					// 登録数
	s32 max;					// 実際の表示数
	s32 cnt;					// 現在の位置
	s32 pos[NV_MAX_SEL_CNT+1];	// "CAS 文字列（,条件式）"の位置分、+1は"SEE 文字列"の位置分

} ST_NV_SEL;

typedef struct {
	s32   act;
	s32   step;
	s32   wait;
	bool  isLoop;				// スクリプト処理継続有無
	bool  isSkip;				// メッセージスキップ
	bool  isPass;				// メッセージスキップ無効フラグ
	bool  isDbg;				// デバッグジャンプ有無
	bool  isOmake;				// おまけモード有無
	s32   navi;					// 攻略情報のキャラ番号
	s32   naviCnt;

	char* p;
	s32   no;
	s32   size;

	s32   cur;
	s32   str;					// メッセージ位置（ロード用）
	s32   set;					// SETコマンド位置（ロード用）
	s32   mes;					// 人物インデックス
	s32   idx;					// 既読フラグ1
	s32   bit;					// 既読フラグ2

	ST_NV_SEL sel;

} ST_NV;


//---------------------------------------------------------------------------
void  NvInit(void);
void  NvInitVar(void);
void  NvExec(void);
void  NvExecKey(void);
void  NvExecSel(void);
void  NvExecLoad(void);

void  NvSetAct(s32 act);
void  NvSetActRest(void);
void  NvSetTxt(s32 no);
void  NvSetTxt2(s32 no);
void  NvSetSkip(void);
void  NvSetPass(bool is);
void  NvSetDbg(bool is);
void  NvSetOmake(bool is);
void  NvSetNavi(s32 no);

s32   NvGetNavi(void);
char* NvGetCur(void);
s32   NvGetSelReg(void);
s32   NvGetSelCnt(void);
char* NvGetSelStr(s32 no);

s32   NvCurNum(void);
s32   NvCurNum1(void);
s32   NvCurNum3(void);
u32   NvCurHex1(void);
u32   NvCurHex4(void);
char* NvCurStr(void);
char  NvCurChr(void);
s32   NvCurChrNum3(char chr);
void  NvCurSkip(void);
void  NvCurSkipIf(void);

void  NvLoad(void);

bool  NvIsSkip(void);
bool  NvIsPass(void);
bool  NvIsDbg(void);
bool  NvIsOmake(void);
bool  NvIsRead(void);
bool  NvIsCurSjis(void);
bool  NvIsSelItem(s32 pos);

#ifdef __cplusplus
}
#endif
#endif
