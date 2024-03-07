#include "irq.arm.h"
#include "ad.arm.h"
#include "vgm.arm.h"

// 注意　VCOUNT値　直書き込みしています
// 6回割り込み　37 75 113 151 189 227


//---------------------------------------------------------------------------
ST_IRQ Irq;


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	_Memset(&Irq, 0x00, sizeof(ST_IRQ));
	Irq.vCnt = IRQ_VCOUNT_START;

	REG_IME = 0;

	INT_VECTOR   = (void*)IrqHandler;
	REG_IE       = IRQ_VBLANK | IRQ_VCOUNT;
	REG_DISPSTAT = LCDC_VBL | LCDC_VCNT | VCOUNT(Irq.vCnt);

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

		// vcountの1つは8ADルーチンを呼び出します
		if(Irq.vCnt == IRQ_VCOUNT_START)
		{
			AdIntrVcount();
		}

		Irq.vCnt += IRQ_VCOUNT_ADD;
		REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(Irq.vCnt);

		if(Irq.vCnt >= IRQ_VCOUNT_END) 
		{
			Irq.vCnt = IRQ_VCOUNT_START;
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
