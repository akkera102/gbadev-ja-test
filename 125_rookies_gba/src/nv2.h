#ifndef __NV2_H__
#define __NV2_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	char* pStr;
	void  (*pFunc)(void);

} ST_NV_PARSE_TABLE;

//---------------------------------------------------------------------------
EWRAM_CODE void NvExecParse(void);
EWRAM_CODE void NvExecParseSub(void);

EWRAM_CODE void NvExecParseMsg(void);
EWRAM_CODE void NvExecParseKey(void);
EWRAM_CODE void NvExecParseBgl(void);
EWRAM_CODE void NvExecParseChr(void);
EWRAM_CODE void NvExecParseEff(void);
EWRAM_CODE void NvExecParseBgm(void);
EWRAM_CODE void NvExecParseBgs(void);
EWRAM_CODE void NvExecParseFmx(void);
EWRAM_CODE void NvExecParseFms(void);
EWRAM_CODE void NvExecParseWat(void);
EWRAM_CODE void NvExecParseSel(void);
EWRAM_CODE void NvExecParseJmp(void);
EWRAM_CODE void NvExecParseLbl(void);
EWRAM_CODE void NvExecParseVar(void);
EWRAM_CODE void NvExecParseLds(void);
EWRAM_CODE void NvExecParseGot(void);
EWRAM_CODE void NvExecParseScr(void);
EWRAM_CODE void NvExecParseSta(void);
EWRAM_CODE void NvExecParseTai(void);
EWRAM_CODE void NvExecParseEnd(void);


#ifdef __cplusplus
}
#endif
#endif
