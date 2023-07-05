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

EWRAM_CODE void NvExecParseEndScn(void);
EWRAM_CODE void NvExecParseTitle(void);
EWRAM_CODE void NvExecParseSel(void);
EWRAM_CODE void NvExecParseJmpScn(void);
EWRAM_CODE void NvExecParseJmpBlk(void);
EWRAM_CODE void NvExecParseSelOpt(void);
EWRAM_CODE void NvExecParsePushA(void);
EWRAM_CODE void NvExecParseRetA(void);
EWRAM_CODE void NvExecParsePushB(void);
EWRAM_CODE void NvExecParseRetB(void);
EWRAM_CODE void NvExecParseDay(void);
EWRAM_CODE void NvExecParseTime(void);
EWRAM_CODE void NvExecParseFlagAdd(void);
EWRAM_CODE void NvExecParseFlagSub(void);
EWRAM_CODE void NvExecParseBg(void);
EWRAM_CODE void NvExecParseChrClr(void);
EWRAM_CODE void NvExecParseVisLoad(void);
EWRAM_CODE void NvExecParseChrLoad(void);
EWRAM_CODE void NvExecParseDisp(void);
EWRAM_CODE void NvExecParseSepia(void);
EWRAM_CODE void NvExecParseJmpAdr(void);
EWRAM_CODE void NvExecParseIf1(void);
EWRAM_CODE void NvExecParseIf2(void);
EWRAM_CODE void NvExecParseIf3(void);
EWRAM_CODE void NvExecParseIf4(void);
EWRAM_CODE void NvExecParseIf5(void);
EWRAM_CODE void NvExecParseIf6(void);
EWRAM_CODE void NvExecParseIfBitSet(void);
EWRAM_CODE void NvExecParseIfBitRes(void);
EWRAM_CODE void NvExecParseFlagSet(void);
EWRAM_CODE void NvExecParseFlagBit(void);
EWRAM_CODE void NvExecParseMsgClr(void);
EWRAM_CODE void NvExecParseMsg(void);
EWRAM_CODE void NvExecParseLight(void);
EWRAM_CODE void NvExecParseWhiteOut(void);
EWRAM_CODE void NvExecParseWhiteIn(void);
EWRAM_CODE void NvExecParseBgm(void);
EWRAM_CODE void NvExecParseBgmFade(void);
EWRAM_CODE void NvExecParseBgmStop(void);
EWRAM_CODE void NvExecParseBgmWaitFade(void);
EWRAM_CODE void NvExecParseBgm2(void);
EWRAM_CODE void NvExecParseBgmNext(void);
EWRAM_CODE void NvExecParseGameEnd(void);
EWRAM_CODE void NvExecParseEnding(void);
EWRAM_CODE void NvExecParsePcmLoad(void);
EWRAM_CODE void NvExecParsePcmStop(void);
EWRAM_CODE void NvExecParsePcmPlay(void);
EWRAM_CODE void NvExecParsePcmWait(void);
EWRAM_CODE void NvExecParseEndMsg(void);
EWRAM_CODE void NvExecParseCr(void);
EWRAM_CODE void NvExecParseKey(void);
EWRAM_CODE void NvExecParsePage(void);
EWRAM_CODE void NvExecParseTimeTxt(void);
EWRAM_CODE void NvExecParseTimeWait(void);
EWRAM_CODE void NvExecParseTxtXy(void);
EWRAM_CODE void NvExecParseFlash(void);
EWRAM_CODE void NvExecParseShake(void);
EWRAM_CODE void NvExecParseBg2(void);
EWRAM_CODE void NvExecParseVisLoad2(void);
EWRAM_CODE void NvExecParseLoadH(void);
EWRAM_CODE void NvExecParseChrChg(void);
EWRAM_CODE void NvExecParseChrDisp(void);
EWRAM_CODE void NvExecParseChrClrAll(void);
EWRAM_CODE void NvExecParseBgChr(void);
EWRAM_CODE void NvExecParseChr3(void);
EWRAM_CODE void NvExecParseDay2(void);
EWRAM_CODE void NvExecParseRain(void);
EWRAM_CODE void NvExecParseSakura(void);
EWRAM_CODE void NvExecParseEndEvent(void);
EWRAM_CODE void NvExecParseSkip(void);

EWRAM_CODE void NvExecParseTxt(void);


#ifdef __cplusplus
}
#endif
#endif
