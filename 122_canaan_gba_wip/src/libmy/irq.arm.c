#include "irq.arm.h"
#include "ad.arm.h"
#include "vgm.arm.h"

// 注意　VCOUNT6回割り込み　37 75 113 151 189 227
// 効果音再生時はVblVcnt、音楽再生時

//---------------------------------------------------------------------------
ST_IRQ Irq;


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	_Memset(&Irq, 0x00, sizeof(ST_IRQ));

	IrqSetVbl();
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqSetVbl(void)
{
	REG_IME = 0;

	REG_IE       = IRQ_VBLANK;
	REG_DISPSTAT = LCDC_VBL;
	INT_VECTOR   = (void*)IrqHandlerVbl;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqSetVblVcnt(void)
{
	REG_IME = 0;

	Irq.vCnt = IRQ_VCOUNT_START;

	REG_IE       = IRQ_VBLANK | IRQ_VCOUNT;
	REG_DISPSTAT = LCDC_VBL | LCDC_VCNT | VCOUNT(Irq.vCnt);
	INT_VECTOR   = (void*)IrqHandlerVblVcnt;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandlerVbl(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VBLANK)
	{
		AdIntrVblank();

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandlerVblVcnt(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VCOUNT)
	{
		VgmIntrVCount();

		if(Irq.vCnt >= IRQ_VCOUNT_END)
		{
			Irq.vCnt = IRQ_VCOUNT_START;
		}
		else
		{
			Irq.vCnt += IRQ_VCOUNT_ADD;
		}

		REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(Irq.vCnt);
	}

	if(flag & IRQ_VBLANK)
	{
		AdIntrVblank();

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
