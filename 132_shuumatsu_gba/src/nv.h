#ifndef __NV_H__
#define __NV_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define NV_MAX_PARSE_CNT				20
#define NV_MAX_VAR_CNT					40				// スクリプト変数：最大 33（調査済）
#define NV_MAX_READ_CNT					180				// 既読フラグ　　：最大177（調査済）(256*5+136) / 8
#define NV_MAX_EXPR_CNT					10

enum {
	NV_ACT_PARSE,
	NV_ACT_KEY,
	NV_ACT_SEL,
	NV_ACT_LOAD,
};

//---------------------------------------------------------------------------

typedef struct {
	bool isUse[NV_MAX_EXPR_CNT];
	s32  cnt;
} ST_NV_EXPR;

typedef struct {
	bool  isUse;
	s32   no;
	char* pCur;
} ST_NV_CALL;

typedef struct {
	s32   reg;			// 登録数
	s32   cnt;			// 現在の選択肢
	char* p[4];			// テキスト
	u16   ofs[4];		// ジャンプオフセット
} ST_NV_SEL;


typedef struct {
	s32   act;
	s32   prev;			// 前のact状態
	s32   step;
	s32   wait;

	bool  isLoop;
	bool  isSkip;		// メッセージスキップ
	bool  isOmit;		// メッセージスキップ無効フラグ
	bool  isPage;		// 改ページ
	bool  isEffect;		// エフェクト発行

	s32   no;
	char* pScn;
	char* pCur;

	// 既読フラグ
	u8    read[NV_MAX_READ_CNT];
	s32   idx;
	s32   bit;

	// スクリプト変数
	u8    var[NV_MAX_VAR_CNT];

	ST_NV_EXPR expr;
	ST_NV_CALL call;
	ST_NV_SEL  sel;

} ST_NV;


//---------------------------------------------------------------------------
void  NvInit(void);
void  NvInitVar(void);
void  NvExec(void);
void  NvExecKey(void);
void  NvExecSel(void);
void  NvExecLoad(void);

void  NvSetAct(s32 act);
void  NvSetScn(s32 no);
void  NvSetScn2(s32 no);
void  NvSetSkip(void);
void  NvSetOmit(bool is);
void  NvSetRead(s32 i, s32 b);
void  NvSetVar(s32 no, s32 num);

s32   NvGetSelReg(void);
s32   NvGetSelCnt(void);
char* NvGetSelStr(s32 no);
s32   NvGetVar(s32 no);

s32   NvCurNum(void);
s32   NvCurHex(void);
char* NvCurStr(void);
char  NvCurChr(void);
void  NvCurSkip(s32 cnt);

bool  NvIsSkip(void);
bool  NvIsOmit(void);
bool  NvIsRead(s32 i, s32 b);
bool  NvIsReadValid(void);
bool  NvIsAct(s32 act);


#ifdef __cplusplus
}
#endif
#endif
