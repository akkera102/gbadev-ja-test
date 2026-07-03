#ifndef __LIBMY_H__
#define __LIBMY_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void LibMyInit(void);

IWRAM_CODE void LibMyExec(void);


#ifdef __cplusplus
}
#endif
#endif
