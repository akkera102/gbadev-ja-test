#include "irq.arm.h"
#include "vgm.arm.h"
#include "snd.arm.h"
#include "../ags.arm.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void IrqSetVbl(void)
{
	REG_IME = 0;

	REG_IE       = IRQ_VBLANK;
	REG_DISPSTAT = LCDC_VBL;
	INT_VECTOR   = (void*)IrqHandler;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VBLANK)
	{
		SndIntrVblank();
		VgmIntrVblank();
		AgsIntrVblank();

		REG_IRQ_WAITFLAGS |= flag;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
