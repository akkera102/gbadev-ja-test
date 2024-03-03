#include "irq.arm.h"
#include "ad.arm.h"
#include "vgm.arm.h"

//---------------------------------------------------------------------------
// VCOUNTŠ„‚èž‚Ýƒ‰ƒCƒ“
u32 irqVcountTable[IRQ_MAX_VCOUNT_CNT] = 
{
	 37,
	 75,
	113,
	151,
	189,
	227,
};

ST_IRQ Irq;


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	_Memset(&Irq, 0x00, sizeof(ST_IRQ));

	REG_IME = 0;

	INT_VECTOR   = (void*)IrqHandler;
	REG_IE       = IRQ_VBLANK | IRQ_VCOUNT;
	REG_DISPSTAT = LCDC_VBL | LCDC_VCNT | VCOUNT(irqVcountTable[Irq.vCnt]);

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VCOUNT)
	{
		VgmIntrVCount();

		if(irqVcountTable[Irq.vCnt] == 37)
		{
			AdIntrVcount();
		}

		Irq.vCnt++;
		REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(irqVcountTable[Irq.vCnt]);

		if(Irq.vCnt >= 5)
		{
			Irq.vCnt = 0;
		}
	}

	if(flag & IRQ_VBLANK)
	{
		AdIntrVblank();

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
