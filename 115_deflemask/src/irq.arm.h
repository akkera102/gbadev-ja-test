#ifndef IRQ_H
#define IRQ_H
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void);
IWRAM_CODE void IrqHandler(void);


#ifdef __cplusplus
}
#endif
#endif
