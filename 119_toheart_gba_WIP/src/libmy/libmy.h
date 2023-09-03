#ifndef __LIBMY_H__
#define __LIBMY_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void LibMyInit(void);
IWRAM_CODE void LibMyExec(void);

EWRAM_CODE u32  LibMyGetVblankCnt(void);


#ifdef __cplusplus
}
#endif
#endif
