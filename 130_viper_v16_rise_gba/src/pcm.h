#ifndef __PCM_H__
#define __PCM_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void PcmInit(void);

EWRAM_CODE void PcmPlay(char* p, s32 adj, bool isLoop);
EWRAM_CODE void PcmStop(void);
EWRAM_CODE bool PcmIsPlay(void);


#ifdef __cplusplus
}
#endif
#endif
