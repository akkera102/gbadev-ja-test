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
EWRAM_CODE void NvExecParseSel(void);
EWRAM_CODE void NvExecParseKey(void);
EWRAM_CODE void NvExecParseBgl(void);
EWRAM_CODE void NvExecParseChr(void);
EWRAM_CODE void NvExecParseHsc(void);
EWRAM_CODE void NvExecParseEff(void);
EWRAM_CODE void NvExecParseVib(void);
EWRAM_CODE void NvExecParseSet(void);
EWRAM_CODE void NvExecParseClr(void);
EWRAM_CODE void NvExecParseBpl(void);
EWRAM_CODE void NvExecParseBst(void);
EWRAM_CODE void NvExecParseFmx(void);
EWRAM_CODE void NvExecParseWat(void);
EWRAM_CODE void NvExecParseMeu(void);
EWRAM_CODE void NvExecParseLds(void);
EWRAM_CODE void NvExecParseMap(void);
EWRAM_CODE void NvExecParseEnd(void);


#ifdef __cplusplus
}
#endif
#endif
