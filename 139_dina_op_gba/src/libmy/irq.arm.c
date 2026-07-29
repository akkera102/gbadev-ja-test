#include "irq.arm.h"
#include "ad.arm.h"

//---------------------------------------------------------------------------
ST_IRQ Irq;

//---------------------------------------------------------------------------
void IrqInit(void)
{
	_Memset(&Irq, 0x00, sizeof(ST_IRQ));


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
		AdIntrVcount();
	}

	if(flag & IRQ_VBLANK)
	{
		AdIntrVblank();

		Irq.cnt++;
		REG_IRQ_WAITFLAGS |= flag;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqSetCnt(s32 cnt)
{
	Irq.cnt = cnt;
}
//---------------------------------------------------------------------------
IWRAM_CODE s32 IrqGetCnt(void)
{
	return Irq.cnt;
}
