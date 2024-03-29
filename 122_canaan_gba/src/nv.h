#ifndef __NV_H__
#define __NV_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define NV_MAX_PARSE_CNT				21


enum {
	NV_ACT_PARSE,
	NV_ACT_KEY,
	NV_ACT_LOAD,
};

//---------------------------------------------------------------------------

typedef struct {
	s32   act;
	s32   step;
	s32   wait;

	bool  isLoop;
	bool  isSkip;
	bool  isPty;
	bool  isIco;

	char* pTxt;
	char* pCur;
	s32   chap;
	s32   part;

} ST_NV;


//---------------------------------------------------------------------------
EWRAM_CODE void  NvInit(void);
EWRAM_CODE void  NvExec(void);
EWRAM_CODE void  NvExecKey(void);
EWRAM_CODE void  NvExecKeyTxt(void);
EWRAM_CODE void  NvExecKeyPty(void);
EWRAM_CODE void  NvExecLoad(void);

EWRAM_CODE void  NvSetTxt(s32 chap, s32 part);
EWRAM_CODE void  NvSetTxt2(s32 chap, s32 part, u32 offset);
EWRAM_CODE void  NvSetAct(s32 act);
EWRAM_CODE void  NvSetSkip(void);
EWRAM_CODE s32   NvGetChap(void);
EWRAM_CODE bool  NvIsSkip(void);

EWRAM_CODE s32   NvNextCurNum(void);
EWRAM_CODE char* NvNextCurStr(void);


#ifdef __cplusplus
}
#endif
#endif

