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


	BgDrawPrintf(1, 1, "VGM Player for GBA");
	BgDrawPrintf(1, 3, "File is valid only");
	BgDrawPrintf(1, 4, "hUGETracker 1.01");

	BgDrawPrintf(1, 6, "Don't use");
	BgDrawPrintf(1, 7, "\"Enable timer-based tempo\"");
	BgDrawPrintf(1, 8, "option.");

	BgDrawPrintf(1, 17, "v0.02 changed timer->vblank");
	BgDrawPrintf(1, 18, "v0.01 added loop function");

	s32 sel = 5;
	s32 max = GbfsGetArcCnt() - 1;

	u8* p = GbfsGetSafePointer2(sel);
	VgmPlay(p, TRUE);

	for(;;)
	{
		VBlankIntrWait();

		BgDrawPrintf(11, 11, "        ");
		BgDrawPrintf(1, 11, "Offset: 0x%x", VgmGetOffsetPlay());
		BgDrawPrintf(1, 12, "Select: (%2d/%2d)", sel, max);


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
