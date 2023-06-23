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


	BgDrawPrintf(1, 1, "To Heart BGM Test");
	BgDrawPrintf(1, 2, "GBS2VGM modoki");

	s32 sel = 0;
	s32 max = GbfsGetArcCnt() - 1;

	u8*   pS = GbfsGetSafePointer2(sel);
	char* pF = GbfsGetFileName();
	VgmPlay(pS, true);

	for(;;)
	{
		VBlankIntrWait();

		BgDrawPrintf(11, 5, "        ");
		BgDrawPrintf( 1, 5, "Offset: 0x%x", VgmGetOffsetPlay());
		BgDrawPrintf( 1, 6, "Select: (%2d/%2d)", sel, max);
		BgDrawPrintf( 9, 7, "            ");
		BgDrawPrintf( 1, 7, "fname : %s", pF);


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
			VgmPlay(pS, true);
		}

		if(trg & KEY_B)
		{
			VgmStop();
		}
	}
}
