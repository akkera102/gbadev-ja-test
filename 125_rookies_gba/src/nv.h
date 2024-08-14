#ifndef __NV_H__
#define __NV_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define NV_MAX_PARSE_CNT				20
#define NV_MAX_VAR_CNT					50


enum {
	NV_ACT_PARSE,
	NV_ACT_KEY,
	NV_ACT_SEL,
	NV_ACT_LOAD,
};

//---------------------------------------------------------------------------

typedef struct {
	s32   ans;			// ëIëéàçUó™èÓïÒ
	s32   reg;			// ìoò^êî
	s32   ret;			// ëIëå„ÇÃï‘ãpêÊïœêî
	s32   cnt;			// åªç›ÇÃëIëéà
	char* p[4];			// ëIëéàÇÃï∂éöóÒ

} ST_NV_SEL;

typedef struct {
	s32   act;
	s32   actPrev;
	s32   step;

	bool  isLoop;
	bool  isSkip;
	s32   wait;

	char* pStr;
	char* pScn;
	char* pCur;
	u32*  pLbl;
	s32   lblMax;

	u8    var[NV_MAX_VAR_CNT];

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
EWRAM_CODE void  NvSetLbl(s32 no);
EWRAM_CODE void  NvSetSkip(void);
EWRAM_CODE void  NvSetVar(s32 no, s32 num);

EWRAM_CODE s32   NvGetSelReg(void);
EWRAM_CODE s32   NvGetSelCnt(void);
EWRAM_CODE char* NvGetSelStr(s32 no);
EWRAM_CODE s32   NvGetVar(s32 no);

EWRAM_CODE bool  NvIsSkip(void);
EWRAM_CODE bool  NvIsActSel(void);

EWRAM_CODE s32   NvNextCurNum(void);
EWRAM_CODE char* NvNextCurStr(void);


#ifdef __cplusplus
}
#endif
#endif

