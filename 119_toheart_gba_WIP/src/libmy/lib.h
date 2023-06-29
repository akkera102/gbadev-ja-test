#ifndef __LIB_H__
#define __LIB_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void LibInit(void);
IWRAM_CODE void LibExec(void);


#ifdef __cplusplus
}
#endif
#endif
