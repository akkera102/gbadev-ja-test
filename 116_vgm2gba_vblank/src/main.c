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
	BgDrawPrintf(1, 2, "vblank version");

	BgDrawPrintf(1, 4, "File is valid only");
	BgDrawPrintf(1, 5, "hUGETracker 1.01");

	BgDrawPrintf(1, 7, "Don't use");
	BgDrawPrintf(1, 8, "\"Enable timer-based tempo\"");
	BgDrawPrintf(1, 9, "option.");

	BgDrawPrintf(1, 17, "v0.03 added display filename");
	BgDrawPrintf(1, 18, "v0.02 changed timer->vblank");
	BgDrawPrintf(1, 19, "v0.01 added loop function");

	s32 sel = 0;
	s32 max = GbfsGetArcCnt() - 1;

	u8*   pS = GbfsGetSafePointer2(sel);
	char* pF = GbfsGetFileName();
	VgmPlay(pS, TRUE);

	for(;;)
	{
		VBlankIntrWait();

		BgDrawPrintf(11, 12, "        ");
		BgDrawPrintf( 1, 12, "Offset: 0x%x", VgmGetOffsetPlay());
		BgDrawPrintf( 1, 13, "Select: (%2d/%2d)", sel, max);
		BgDrawPrintf( 9, 14, "            ");
		BgDrawPrintf( 1, 14, "fname : %s", pF);


		KeyExec();
		u16 trg = KeyGetTrg();

		if((trg & KEY_RIGHT) && sel < max)
		{
			sel++;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
		}

		if((trg & KEY_LEFT) && sel > 0)
		{
			sel--;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
		}

		if(trg & KEY_A)
		{
			VgmPlay(pS, TRUE);
		}

		if(trg & KEY_B)
		{
			VgmStop();
		}
	}
}
