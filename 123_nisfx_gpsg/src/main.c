#include "lib/gba.h"
#include "bg.h"
#include "irq.arm.h"
#include "key.h"
#include "vgm.arm.h"
#include "string.h"

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
	BgDrawPrintf(1, row, "ch 1:");
	row++;
	BgDrawPrintf(1, row, "ch 2:");
	row++;
	BgDrawPrintf(1, row, "ch 3:");
	row++;
	BgDrawPrintf(1, row, "ch 4:");
	row++;
	BgDrawPrintf(1, row, "ctrl:");

	row = 11;
	BgDrawPrintf(1, row, "wave:");

	row = 16;
	BgDrawPrintf(1, row, "HBlank Interrupt - <360Tick>");

	row = 18;
	BgDrawPrintf(1, row, "GB-PSG SFX Test");
	row++;
	BgDrawPrintf(3, row, "for PC98 V-Novel GBA Ports");

	// BgDrawPrintf(0, 21, "support loop");

	// BgDrawPrintf(0, 14, "Downsample PoC <44.1k to 720>");
	// BgDrawPrintf(0, 15, " and 0x61, 62, 63  Supported");

	// BgDrawPrintf(0, 17, "v0.03 added display filename");
	// BgDrawPrintf(1, 18, "v0.02 changed timer->vblank");
	// BgDrawPrintf(1, 19, "v0.01 added loop function");

	s32 sel = 0;
	s32 opt_loop = 0;
	// s32 opt_bias = 0;

	s32 dbg_wave = 0;
	s32 ptr_wave = 0;

	s32 max = GbfsGetArcCnt() - 1;

	u8*   pS = GbfsGetSafePointer2(sel);
	char* pF = GbfsGetFileName();

	VgmStop();
	// VgmPlay(pS, pF, 0);

	for(;;)
	{
		VBlankIntrWait();
		opt_loop = VgmGetIsLoop();

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
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetRegs(0x00));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetRegs(0x02));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetRegs(0x03));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetRegs(0x04));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetRegs(0x05));

		row++;
		BgDrawPrintf(7+0*3, row, "--");
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetRegs(0x08));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetRegs(0x09));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetRegs(0x0c));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetRegs(0x0d));

		row++;
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetRegs(0x10));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetRegs(0x12));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetRegs(0x13));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetRegs(0x14));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetRegs(0x15));

		row++;
		BgDrawPrintf(7+0*3, row, "--");
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetRegs(0x18));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetRegs(0x19));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetRegs(0x1c));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetRegs(0x1d));

		row++;
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetRegs(0x20));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetRegs(0x21));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetRegs(0x24));

		BgDrawPrintf(7+4*3, row, "%02X", *((u16 volatile *) (REG_BASE + 0x088)));

		row = 11;

		s32 wav_i = 0;
		s32 pos_i = 7;
		for(;wav_i<0x08;)
		{
			BgDrawPrintf(pos_i, row, "%02X", VgmGetWave(wav_i));
			wav_i++;
			pos_i=pos_i+2;
			if(wav_i==0x04)
			{
				pos_i=pos_i+1;
			}
		}
		row++;
		BgDrawPrintf(0, row, (dbg_wave != 0) ? "(edit)" : "      ");
		BgDrawPrintf(6, row, "                        ");

		row++;
		pos_i = 7;
		for(;wav_i<0x10;)
		{
			BgDrawPrintf(pos_i, row, "%02X", VgmGetWave(wav_i));
			wav_i++;
			pos_i=pos_i+2;
			if(wav_i==0x0C)
			{
				pos_i=pos_i+1;
			}
		}
		row++;
		BgDrawPrintf(0, row, "                              ");

		if(dbg_wave != 0){
			if(ptr_wave<0x08)
			{
				BgDrawPrintf(7+ptr_wave, row-2, "^");
			}
			else if(ptr_wave<0x10)
			{
				BgDrawPrintf(7+ptr_wave+1, row-2, "^");
			}
			else if(ptr_wave<0x18)
			{
				BgDrawPrintf(7+ptr_wave-0x10, row, "^");
			}
			else
			{
				BgDrawPrintf(7+ptr_wave+1-0x10, row, "^");
			}
		}

		KeyExec();
		u16 trg = KeyGetTrg();
		if(0 == dbg_wave)
		{
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
		}
		else
		{
			if((trg & KEY_RIGHT))
			{
				ptr_wave = (ptr_wave + 1) % 32;

			}
			if((trg & KEY_LEFT))
			{
				ptr_wave = (ptr_wave + 31) % 32;

			}

			if((trg & KEY_DOWN))
			{
			}
			if((trg & KEY_UP))
			{
			}
		}

		if((trg & KEY_START))
		{
			dbg_wave = (dbg_wave + 1) % 2;
		}
		if((trg & KEY_SELECT))
		{
			opt_loop = (opt_loop + 1) % 2;
			VgmSetLoop(opt_loop);
		}

		if(trg & KEY_A)
		{
			VgmPlay(pS, pF, 0);
		}
		if(trg & KEY_B)
		{
			VgmStop();
		}

	}
}
