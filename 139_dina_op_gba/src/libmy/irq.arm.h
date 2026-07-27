#ifndef __IRQ_H__
#define __IRQ_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	s32 cnt;

} ST_IRQ;



//---------------------------------------------------------------------------
void IrqInit(void);

IWRAM_CODE void IrqHandler(void);
IWRAM_CODE void IrqSetCnt(s32 cnt);
IWRAM_CODE s32  IrqGetCnt(void);


#ifdef __cplusplus
}
#endif
#endif
