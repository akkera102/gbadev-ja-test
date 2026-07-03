#ifndef __NV2_H__
#define __NV2_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	char* cmd;
	void  (*pExec)(void);

} ST_NV_PARSE_TBL;

//---------------------------------------------------------------------------
void NvExecParse(void);
void NvExecParseSub(void);

void NvExecParseMes(void);
void NvExecParseMlf(void);
void NvExecParseGfx(void);
void NvExecParseGlb(void);
void NvExecParseGlg(void);
void NvExecParseClg(void);
void NvExecParseCfr(void);
void NvExecParseMus(void);
void NvExecParseSnd(void);
void NvExecParseVfl(void);
void NvExecParseVfw(void);
void NvExecParseIf0(void);
void NvExecParseIfe(void);
void NvExecParseGo0(void);
void NvExecParseSet(void);
void NvExecParseSel(void);
void NvExecParseCas(void);
void NvExecParseBrk(void);
void NvExecParseSee(void);
void NvExecParseWas(void);
void NvExecParseWam(void);
void NvExecParseEnd(void);

void NvExecParseSjis(void);
void NvExecParseSjisSub(void);


#ifdef __cplusplus
}
#endif
#endif
