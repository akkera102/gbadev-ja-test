#ifndef LIBMY_H
#define LIBMY_H
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void LibMyInit(void);
IWRAM_CODE void LibMyExec(void);


#ifdef __cplusplus
}
#endif
#endif
