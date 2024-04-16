#ifndef __SE_H__
#define __SE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void);

EWRAM_CODE void SePlay(u8* p, bool isLoop);
EWRAM_CODE void SePlayFmx(s32 no);
EWRAM_CODE void SeStop(void);


#ifdef __cplusplus
}
#endif
#endif
