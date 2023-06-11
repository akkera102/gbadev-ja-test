#ifndef __MAIN_H__
#define __MAIN_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE int  main(void);

EWRAM_CODE void MainInit(void);
IWRAM_CODE void MainExec(void);


#ifdef __cplusplus
}
#endif
#endif
