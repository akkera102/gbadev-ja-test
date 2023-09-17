#include "irq.arm.h"
#include "vgm.arm.h"
#include "snd.arm.h"
#include "../sakura.h"
#include "../rein.h"

//---------------------------------------------------------------------------
u32 IrqVblankCnt;


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (void*)IrqHandler;
	REG_IE       = IRQ_VBLANK;
	REG_DISPSTAT = LCDC_VBL;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VBLANK)
	{
		IrqVblankCnt++;

		VgmIntrVblank();
		SndIntrVblank();

		if(SakuraIsEffect() == true)
		{
			SakuraIntrExec();
		}

		if(ReinIsEffect() == true)
		{
			ReinIntrExec();
		}

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
