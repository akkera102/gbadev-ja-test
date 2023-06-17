#include "irq.arm.h"
#include "ad.arm.h"
#include "snd.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (u32)IrqHandler;
	REG_IE       = IRQ_VBLANK | IRQ_VCOUNT;
	REG_DISPSTAT = LCDC_VBL | LCDC_VCNT | VCOUNT(0);

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VCOUNT)
	{
		AdIntrVcount();
	}

	if(flag & IRQ_VBLANK)
	{
		AdIntrVblank();
		SndIntrVblank();

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
