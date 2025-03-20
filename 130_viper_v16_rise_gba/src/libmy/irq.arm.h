#ifndef __IRQ_H__
#define __IRQ_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void);

EWRAM_CODE void IrqSetVbl(void);
IWRAM_CODE void IrqHandler(void);

#ifdef __cplusplus
}
#endif
#endif
