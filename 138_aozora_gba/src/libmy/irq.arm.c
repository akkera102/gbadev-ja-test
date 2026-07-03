#include "irq.arm.h"
#include "sfx.arm.h"
#include "ulc.arm.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void IrqInit(void)
{
	REG_IME = 0;

	REG_IE       = IRQ_VBLANK | IRQ_VCOUNT;;
	REG_DISPSTAT = LCDC_VBL| LCDC_VCNT | VCOUNT(60);
	INT_VECTOR   = (void*)IrqHandler;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VCOUNT)
	{
		UlcIntrVcount();
	}

	if(flag & IRQ_VBLANK)
	{
		UlcIntrVblank();
		SfxIntrVblank();

		REG_IRQ_WAITFLAGS |= flag;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
