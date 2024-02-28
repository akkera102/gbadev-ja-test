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

EWRAM_CODE void SePlay(u8* p);
EWRAM_CODE void SePlayFmx(s32 no);
EWRAM_CODE void SePlaySsg(s32 no);
EWRAM_CODE void SeStop(void);
EWRAM_CODE bool SeIsPlay(void);


#ifdef __cplusplus
}
#endif
#endif
