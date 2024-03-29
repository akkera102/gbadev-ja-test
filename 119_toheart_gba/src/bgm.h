#ifndef __BGM_H__
#define __BGM_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	bool isPlay;
	bool isLoop;
	u32  no;

} ST_BGM;


//---------------------------------------------------------------------------
EWRAM_CODE void BgmInit(void);

EWRAM_CODE void BgmPlay(u32 no, bool isLoop);
EWRAM_CODE void BgmPlay2(u32 no, bool isLoop);
EWRAM_CODE void BgmStop(void);
EWRAM_CODE void BgmRestart(void);

EWRAM_CODE bool BgmIsEnd(void);


#ifdef __cplusplus
}
#endif
#endif
