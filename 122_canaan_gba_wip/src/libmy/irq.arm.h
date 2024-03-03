#ifndef __IRQ_H__
#define __IRQ_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define IRQ_MAX_VCOUNT_CNT				6


//---------------------------------------------------------------------------

typedef struct {
	s32 vCnt;

} ST_IRQ;


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void);
IWRAM_CODE void IrqHandler(void);


#ifdef __cplusplus
}
#endif
#endif
