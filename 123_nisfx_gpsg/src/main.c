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


	u8 row = 0;
	BgDrawPrintf(0, row, "gPSG Player ADVANCE  0x");

	row = 2;
	BgDrawPrintf(19, row, "loop:");

	row = 5;
	BgDrawPrintf(3, row, "ch 1:");
	row++;
	BgDrawPrintf(3, row, "ch 2:");
	row++;
	BgDrawPrintf(3, row, "ch 3:");
	row++;
	BgDrawPrintf(3, row, "ch 4:");
	row++;
	BgDrawPrintf(3, row, "ctrl:");

	row = 11;
	BgDrawPrintf(3, row, "wave:");

	row = 15;
	BgDrawPrintf(0, row, "HBlank Interrupt PoC <360Tick>");

	row = 17;
	BgDrawPrintf(0, row, "CANAAN SFX Port to GB-PSG");
	row++;
	BgDrawPrintf(10, row, "Demo for CANAAN-GBA");

	// BgDrawPrintf(0, 21, "support loop");

	// BgDrawPrintf(0, 14, "Downsample PoC <44.1k to 720>");
	// BgDrawPrintf(0, 15, " and 0x61, 62, 63  Supported");

	// BgDrawPrintf(0, 17, "v0.03 added display filename");
	// BgDrawPrintf(1, 18, "v0.02 changed timer->vblank");
	// BgDrawPrintf(1, 19, "v0.01 added loop function");

	s32 sel = 0;
	s32 opt_loop = 0;
	s32 opt_bias = 0;

	s32 max = GbfsGetArcCnt() - 1;

	u8*   pS = GbfsGetSafePointer2(sel);
	char* pF = GbfsGetFileName();
	VgmStop();
	VgmPlay(pS, opt_loop, opt_bias);

	for(;;)
	{
		VBlankIntrWait();

		row = 0;
		BgDrawPrintf(23, row, "       ");
		BgDrawPrintf(23, row, "%X", VgmGetOffsetPlay());

		row = 2;
		BgDrawPrintf(0, row, "%3d/%3d:", sel+1, max+1);
		BgDrawPrintf(25, row, (opt_loop == 0) ? "OFF" : "ON ");

		row++;
		BgDrawPrintf(3, row, "                         ");
		BgDrawPrintf(3, row, "%s", pF);

		row = 5;
		BgDrawPrintf(9+0*3, row, "%02X", VgmGetRegs(0x00));
		BgDrawPrintf(9+1*3, row, "%02X", VgmGetRegs(0x02));
		BgDrawPrintf(9+2*3, row, "%02X", VgmGetRegs(0x03));
		BgDrawPrintf(9+3*3, row, "%02X", VgmGetRegs(0x04));
		BgDrawPrintf(9+4*3, row, "%02X", VgmGetRegs(0x05));

		row++;
		BgDrawPrintf(9+0*3, row, "--");
		BgDrawPrintf(9+1*3, row, "%02X", VgmGetRegs(0x08));
		BgDrawPrintf(9+2*3, row, "%02X", VgmGetRegs(0x09));
		BgDrawPrintf(9+3*3, row, "%02X", VgmGetRegs(0x0c));
		BgDrawPrintf(9+4*3, row, "%02X", VgmGetRegs(0x0d));

		row++;
		BgDrawPrintf(9+0*3, row, "%02X", VgmGetRegs(0x10));
		BgDrawPrintf(9+1*3, row, "%02X", VgmGetRegs(0x12));
		BgDrawPrintf(9+2*3, row, "%02X", VgmGetRegs(0x13));
		BgDrawPrintf(9+3*3, row, "%02X", VgmGetRegs(0x14));
		BgDrawPrintf(9+4*3, row, "%02X", VgmGetRegs(0x15));

		row++;
		BgDrawPrintf(9+0*3, row, "--");
		BgDrawPrintf(9+1*3, row, "%02X", VgmGetRegs(0x18));
		BgDrawPrintf(9+2*3, row, "%02X", VgmGetRegs(0x19));
		BgDrawPrintf(9+3*3, row, "%02X", VgmGetRegs(0x1c));
		BgDrawPrintf(9+4*3, row, "%02X", VgmGetRegs(0x1d));

		row++;
		BgDrawPrintf(9+0*3, row, "%02X", VgmGetRegs(0x20));
		BgDrawPrintf(9+1*3, row, "%02X", VgmGetRegs(0x21));
		BgDrawPrintf(9+2*3, row, "%02X", VgmGetRegs(0x24));

		BgDrawPrintf(9+4*3, row, "%02X", *((u16 volatile *) (REG_BASE + 0x088)));

		s32 i;
		row = 12;
		for(i=0; i<0x10; i++)
		{
			BgDrawPrintf(i*2, row, "%02X", VgmGetWave(i));
		}


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

		if((trg & KEY_DOWN) && sel < max)
		{
			sel = (sel+10 <= max) ? sel+10 : max;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
		}
		if((trg & KEY_UP) && sel > 0)
		{
			sel = (sel-10 >= 0) ? sel-10 : 0;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
		}

		if((trg & KEY_R) && sel < max)
		{
			sel = max;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
		}
		if((trg & KEY_L) && sel > 0)
		{
			sel = 0;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
		}

		if((trg & KEY_START))
		{
			opt_bias = (opt_bias + 1) % 4;
		}
		if((trg & KEY_SELECT))
		{
			opt_loop = (opt_loop + 1) % 2;
		}

		if(trg & KEY_A)
		{
			VgmPlay(pS, opt_loop, opt_bias);
		}
		if(trg & KEY_B)
		{
			VgmStop();
		}

	}
}
