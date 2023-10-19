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


	BgDrawPrintf(1, 1, "LSDJ BGM TEST");

	s32 sel = 0;
	s32 max = GbfsGetArcCnt() - 1;

	u8*   pS = GbfsGetSafePointer2(sel);
	char* pF = GbfsGetFileName();
	VgmPlay(pS, false);

	for(;;)
	{
		VBlankIntrWait();

		BgDrawPrintf(11, 3, "        ");
		BgDrawPrintf( 1, 3, "Offset: 0x%x", VgmGetOffsetPlay());
		BgDrawPrintf( 9, 4, "  ");
		BgDrawPrintf( 1, 4, "Loop  : %d", VgmGetLoopCnt());
		BgDrawPrintf( 9, 5, "            ");
		BgDrawPrintf( 1, 5, "Fname : %s", pF);
		BgDrawPrintf( 1, 6, "Select: %02d/%02d", sel, max);

		s32 i;

		for(i=0; i<=0x84 - 0x60; i++)
		{
			BgDrawPrintf(i*4, 9, "%02X", *((u16 volatile *) (REG_BASE + 0x060 + i)));
		}

		for(i=0; i<0x10; i++)
		{
			BgDrawPrintf(i*4, 15, "%02X", VgmGetWave(i));
		}


		KeyExec();
		u16 trg = KeyGetTrg();
		u16 rep = KeyGetRep();

		if((rep & KEY_RIGHT) && sel < max)
		{
			sel++;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
		}

		if((rep & KEY_LEFT) && sel > 0)
		{
			sel--;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
		}

		if(trg & KEY_A)
		{
			VgmPlay(pS, false);
		}

		if(trg & KEY_B)
		{
			VgmStop();
		}
	}
}
