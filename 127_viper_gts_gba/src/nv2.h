#ifndef __NV2_H__
#define __NV2_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void NvExecParse(void);
EWRAM_CODE void NvExecParseSub(void);

EWRAM_CODE void NvExecParseBuf(void);
EWRAM_CODE void NvExecParseBui(void);
EWRAM_CODE void NvExecParseBur(void);
EWRAM_CODE void NvExecParseBua(void);
EWRAM_CODE void NvExecParseScr(void);
EWRAM_CODE void NvExecParseScm(void);
EWRAM_CODE void NvExecParseSlp(void);
EWRAM_CODE void NvExecParseEff(void);
EWRAM_CODE void NvExecParseAnm(void);
EWRAM_CODE void NvExecParseAni(void);
EWRAM_CODE void NvExecParseAne(void);
EWRAM_CODE void NvExecParseWab(void);
EWRAM_CODE void NvExecParseWay(void);
EWRAM_CODE void NvExecParseWai(void);
EWRAM_CODE void NvExecParseWap(void);
EWRAM_CODE void NvExecParseWas(void);
EWRAM_CODE void NvExecParsePal(void);
EWRAM_CODE void NvExecParsePae(void);
EWRAM_CODE void NvExecParsePaf(void);
EWRAM_CODE void NvExecParseBgm(void);
EWRAM_CODE void NvExecParseBgs(void);
EWRAM_CODE void NvExecParsePcm(void);
EWRAM_CODE void NvExecParsePcs(void);
EWRAM_CODE void NvExecParsePcn(void);
EWRAM_CODE void NvExecParseTxt(void);
EWRAM_CODE void NvExecParseTxc(void);
EWRAM_CODE void NvExecParseLbl(void);
EWRAM_CODE void NvExecParseJmp(void);
EWRAM_CODE void NvExecParseIfr(void);
EWRAM_CODE void NvExecParseIfl(void);
EWRAM_CODE void NvExecParseCal(void);
EWRAM_CODE void NvExecParseRet(void);
EWRAM_CODE void NvExecParseSel(void);
EWRAM_CODE void NvExecParseWin(void);
EWRAM_CODE void NvExecParseVrr(void);
EWRAM_CODE void NvExecParseVrw(void);
EWRAM_CODE void NvExecParseCpy(void);
EWRAM_CODE void NvExecParseInc(void);
EWRAM_CODE void NvExecParseOr0(void);


#ifdef __cplusplus
}
#endif
#endif
