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
	s32  no;

} ST_BGM;


//---------------------------------------------------------------------------
EWRAM_CODE void BgmInit(void);

EWRAM_CODE void BgmPlay(s32 no, bool isLoop);
EWRAM_CODE void BgmPlay2(s32 no, bool isLoop);
EWRAM_CODE void BgmPlayLoad(void);
EWRAM_CODE void BgmStop(void);
EWRAM_CODE u32  BgmGetOffset(void);


#ifdef __cplusplus
}
#endif
#endif
