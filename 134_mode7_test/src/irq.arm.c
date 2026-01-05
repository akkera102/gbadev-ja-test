#include "irq.arm.h"
#include "eff.arm.h"

//---------------------------------------------------------------------------
void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (void*)IrqHandler;
	REG_IE       = IRQ_VBLANK | IRQ_HBLANK | IRQ_KEYPAD;
	REG_DISPSTAT = LCDC_VBL | LCDC_HBL;
	REG_KEYCNT   = KEYIRQ_ENABLE | KEYIRQ_OR | KEY_A;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_KEYPAD)
	{
		EffInitCam();
	}

	if(flag & IRQ_HBLANK)
	{
		u32 v = REG_VCOUNT;

		// 0-227
		if(v < 159)
		{
			EffIntrHblank(v + 1);
		}
	}

	if(flag & IRQ_VBLANK)
	{
		EffAddCamZ();
		EffIntrHblank(0);

		REG_IRQ_WAITFLAGS |= flag;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
