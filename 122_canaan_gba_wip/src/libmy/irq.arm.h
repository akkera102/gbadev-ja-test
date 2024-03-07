#ifndef __IRQ_H__
#define __IRQ_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define IRQ_VCOUNT_START					37
#define IRQ_VCOUNT_ADD						38
#define IRQ_VCOUNT_END						(IRQ_VCOUNT_START + IRQ_VCOUNT_ADD * 5)

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
