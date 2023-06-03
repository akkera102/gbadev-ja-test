#include "lib/gba.h"
#include "bg.h"
#include "irq.arm.h"
#include "key.h"
#include "vgm.arm.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	GbfsInit();
	BgInit();
	KeyInit();

	VgmInit();
	IrqInit();

	u8* p = GbfsGetSafePointer("1.bin");
	VgmPlay(p, TRUE);

	BgDrawPrintf(1, 1, "VGM Player for GBA");
	BgDrawPrintf(1, 3, "File is valid only");
	BgDrawPrintf(1, 4, "hUGETracker 1.01");

	s32 sel = 0;
	s32 max = GbfsGetArcCnt() - 1;

	for(;;)
	{
	    VBlankIntrWait();

		BgDrawPrintf(1, 7, "Select: (%2d/%2d)\n", sel, max);

		KeyExec();
		u16 trg = KeyGetTrg();

		if((trg & KEY_RIGHT) && sel < max)
		{
			sel++;
		}

		if((trg & KEY_LEFT) && sel > 0)
		{
			sel--;
		}

		if(trg & KEY_A)
		{
			p = GbfsGetSafePointer2(sel);
			VgmPlay(p, TRUE);
		}

		if(trg & KEY_B)
		{
			VgmStop();
		}
	}
}
