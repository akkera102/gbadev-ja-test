#include "irq.arm.h"
#include "vgm.arm.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (u32)IrqHandler;
	REG_IE       = IRQ_TIMER2 | IRQ_TIMER3 | IRQ_VBLANK;
	REG_DISPSTAT = LCDC_VBL;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_TIMER2)
	{
		VgmIntrTimer2();
	}

	if(flag & IRQ_TIMER3)
	{
		VgmIntrTimer3();
	}

	if(flag & IRQ_VBLANK)
	{
		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
