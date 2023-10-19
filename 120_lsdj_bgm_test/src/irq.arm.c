#include "irq.arm.h"
#include "vgm.arm.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (void*)IrqHandler;
	REG_IE       = IRQ_VBLANK | IRQ_VCOUNT;
	REG_DISPSTAT = LCDC_VBL;
	REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(0);

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VBLANK)
	{
		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	if(flag & IRQ_VCOUNT)
	{
		VgmIntrVCount();
	}

	REG_IF  = flag;
	REG_IME = 1;
}
