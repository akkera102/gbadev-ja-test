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

	VgmPlayerInit();

	VgmInit();
	VgmStop();

	IrqInit();


	u8 row = 0;
	BgDrawPrintf(0, row, "gPSG Player ADVANCE  0x");

	row = 4;
	BgDrawPrintf(1, row, "ch 1:");
	BgDrawPrintf(22, row, "loop:");
	row++;
	BgDrawPrintf(1, row, "ch 2:");
	row++;
	BgDrawPrintf(1, row, "ch 3:");
	row++;
	BgDrawPrintf(1, row, "ch 4:");
	row++;
	BgDrawPrintf(1, row, "ctrl:");

	row = 10;
	BgDrawPrintf(1, row, "wave:");

	row = 14;
	BgDrawPrintf(1, row, "mode:");
	BgDrawPrintf(16, row, "fade:");

	row = 16;
	BgDrawPrintf(1, row, "Interrupt - 60Tick (VBlank)");

	row = 18;
	BgDrawPrintf(1, row, "GB-PSG BGM Test");
	row++;
	BgDrawPrintf(3, row, "for PC98 ViperGTS GBA Port");

	u32 sel = 0;
	u8 stat = PLAYER_STAT_STOP;
	s32 opt_loop = 0;
	s32 opt_headset = 0;
	s32 opt_fadeout = 0;

	u32 max = GbfsGetArcCnt() - 1;

	u8*   pS = GbfsGetSafePointer2(sel);
	char* pF = GbfsGetFileName();

	VgmPlay(pS);

	for(;;)
	{
		VBlankIntrWait();
		stat = VgmGetStat();
		opt_loop = VgmGetIsLoop();
		opt_headset = VgmGetIsHeadset();
		opt_fadeout = VgmGetIsFade();

		row = 0;
		BgDrawPrintf(23, row, "       ");
		BgDrawPrintf(23, row, "%X", VgmGetOffsetPlay());

		row++;
		BgDrawPrintf(26, row, (stat == PLAYER_STAT_RESERVE) ? "%02d" : "  ", VgmGetFadeCnt());
		BgDrawPrintf(28, row, (stat == PLAYER_STAT_STOP) ? "[]" : "|>");

		row++;
		BgDrawPrintf(0, row, "%2d/%2d:", sel + 1, max + 1);

		BgDrawPrintf(7, row, "                        ");
		BgDrawPrintf(7, row, "%s", pF);
		row++;
		BgDrawPrintf(0, row, " ");


		row = 4;
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetRegs(0x00));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetRegs(0x02));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetRegs(0x03));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetRegs(0x04));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetRegs(0x05));

		BgDrawPrintf(28, row, (opt_loop == 0) ? "F" : "T");

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

		BgDrawPrintf(7+3*3, row, "%02X", *((u16 volatile *) (REG_BASE + 0x082)));
		BgDrawPrintf(7+4*3, row, "%02X", *((u16 volatile *) (REG_BASE + 0x089)));
		BgDrawPrintf(7+5*3, row, "%02X", *((u16 volatile *) (REG_BASE + 0x088)));


		row = 10;
		s32 wav_i = 0;
		s32 pos_i = 7;
		for(;wav_i < 0x08;)
		{
			BgDrawPrintf(pos_i, row, "%02X", VgmGetWave(wav_i));
			wav_i++;
			pos_i = pos_i + 2;
			if(wav_i == 0x04)
			{
				pos_i++;
			}
		}

		row = 12;
		pos_i = 7;
		for(;wav_i < 0x10;)
		{
			BgDrawPrintf(pos_i, row, "%02X", VgmGetWave(wav_i));
			wav_i++;
			pos_i = pos_i + 2;
			if(wav_i == 0x0C)
			{
				pos_i++;
			}
		}

		row = 14;
		BgDrawPrintf(7, row, (opt_headset == 0) ? "speaker" : "headset");
		BgDrawPrintf(22, row, (opt_fadeout == 0) ? "F" : "T");


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
			sel = (sel + 10 <= max) ? sel + 10 : max;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
		}
		if((trg & KEY_UP) && sel > 0)
		{
			sel = (sel >= 10) ? sel - 10 : 0;

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
			opt_fadeout = (opt_fadeout + 1) % 2;
			VgmSetFade(opt_fadeout);
		}
		if((trg & KEY_SELECT))
		{
			opt_headset = (opt_headset + 1) % 2;
			VgmSetHeadset(opt_headset);
		}

		if(trg & KEY_A)
		{
			if(1 == opt_fadeout && PLAYER_STAT_PLAY == stat)
			{
				VgmReserve(pS);
			}
			else
			{
				VgmPlay(pS);
			}
		}
		if(trg & KEY_B)
		{
			VgmStop();
		}

	}
}
