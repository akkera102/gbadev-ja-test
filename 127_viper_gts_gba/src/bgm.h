#ifndef __BGM_H__
#define __BGM_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void BgmInit(void);

EWRAM_CODE void BgmPlay(s32 no, bool isLoop);
EWRAM_CODE void BgmStop(void);
EWRAM_CODE bool BgmIsPlay(void);



#ifdef __cplusplus
}
#endif
#endif