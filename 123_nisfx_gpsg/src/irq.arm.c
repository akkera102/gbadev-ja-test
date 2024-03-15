#include "irq.arm.h"
#include "vgm.arm.h"

//---------------------------------------------------------------------------
extern ST_VGM Vgm;

//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (void*)IrqHandler;
	REG_IE       = IRQ_VBLANK | IRQ_HBLANK;
	REG_DISPSTAT = LCDC_VBL | LCDC_HBL;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VBLANK)
	{
		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	if(flag & IRQ_HBLANK)
	{
		switch(REG_VCOUNT)
		{
			// 60Hzの時は227だけ残す。720Hzの時はコメントを外して12個。
			// HBlankは228(=2*2*3*19)なので、更に割込回数を増やすことも可能(再生データが必要とするなら)。

		  // case 18:
		  case 37:
		  // case 56:
		  case 75:
		  // case 94:
		  case 113:
		  // case 132:
		  case 151:
		  // case 170:
		  case 189:
		  // case 208:
		  case 227:
				VgmTick();
			default:
		}
	}

	REG_IF  = flag;
	REG_IME = 1;
}
