#ifndef __IRQ_H__
#define __IRQ_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
void IrqInit(void);

IWRAM_CODE void IrqHandler(void);


#ifdef __cplusplus
}
#endif
#endif
