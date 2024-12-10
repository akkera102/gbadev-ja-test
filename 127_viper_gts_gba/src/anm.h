#ifndef __ANM_H__
#define __ANM_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define ANM_BUF_MAX_CNT				3
#define ANM_BUF_DAT_MAX_CNT			70			// 最大数65（調査済）
#define ANM_SCR_MAX_CNT				3
#define ANM_COL_DAT_MAX_CNT			40			// 最大数38（調査済）


enum {
	ANM_TYPE_SCR_SET = 1,
	ANM_TYPE_SCR_UD,
	ANM_TYPE_SCR_DU,
	ANM_TYPE_SCR_UP,
	ANM_TYPE_SCR_DOWN,
};

//---------------------------------------------------------------------------

typedef struct {
	u16* p;
	s32  f;						// frame
	s32  w;						// wait
	s32  sx;
	s32  sy;
	s32  cx;
	s32  cy;
} ST_ANM_BUF_DAT;


typedef struct {
	bool isWork;				// 稼働有無
	bool isComp;				// フレーム全ての描画完了有無
	bool isLoop;				// フレームループ判定有無
	s32  max;
	s32  cnt;
	s32  wait;
	ST_ANM_BUF_DAT d[ANM_BUF_DAT_MAX_CNT];

} ST_ANM_BUF;


typedef struct {
	bool isWork;				// 稼働有無
	bool isComp;				// 動作完了有無
	u16* p;
	s32  f;
	s32  type;
	s32  sy;
	s32  my;
	s32  ey;
} ST_ANM_SCR;


typedef struct {
	u32  i;						// index
	u32  r;
	u32  g;
	u32  b;
} ST_ANM_COL_DAT;


typedef struct {
	bool isWork;
	s32  max;
	s32  cnt;
	s32  wait;
	s32  waitCnt;
	ST_ANM_COL_DAT d[ANM_COL_DAT_MAX_CNT];

} ST_ANM_COL;


typedef struct {
	bool  isPause;
	bool  isDrawScr;

	char* pStr;
	u16*  pPal;
	u16*  pDat;
	s32   dMax;					// DATに登録されているイメージ数

	ST_ANM_BUF b[ANM_BUF_MAX_CNT];
	ST_ANM_SCR s[ANM_SCR_MAX_CNT];
	ST_ANM_COL c;

} ST_ANM;

//---------------------------------------------------------------------------
EWRAM_CODE void AnmInit(void);
EWRAM_CODE void AnmExec(void);

IWRAM_CODE void AnmExecCol(void);
EWRAM_CODE void AnmExecScr(s32 no);
EWRAM_CODE void AnmExecFrm(s32 no);

EWRAM_CODE void AnmSetDat(char* pStr);
EWRAM_CODE void AnmSetBuf1(s32 bNo, bool isLoop, s32 max);
EWRAM_CODE void AnmSetBuf2(s32 bNo, s32 dNo, s32 frame, s32 wait);
EWRAM_CODE void AnmSetScr1(s32 no, s32 frame);
EWRAM_CODE void AnmSetScr2(s32 no, s32 type, s32 sy, s32 ey, s32 my);
EWRAM_CODE void AnmSetScr3(s32 no, s32 type, s32 my);
EWRAM_CODE void AnmSetScr4(s32 sy);
EWRAM_CODE void AnmSetPal(void);
EWRAM_CODE void AnmSetCol1(s32 wait, s32 max);
EWRAM_CODE void AnmSetCol2(s32 no, s32 i, s32 r, s32 g, s32 b);
EWRAM_CODE void AnmSetCol3(s32 i, s32 r, s32 g, s32 b);

EWRAM_CODE void AnmSetBufWork(s32 no, bool is);
EWRAM_CODE void AnmSetScrWork(s32 no, bool is);
EWRAM_CODE void AnmSetPause(bool is);

EWRAM_CODE bool AnmIsBufComp(s32 no);
EWRAM_CODE bool AnmIsScrComp(s32 no);
EWRAM_CODE bool AnmIsPause(void);


#ifdef __cplusplus
}
#endif
#endif
