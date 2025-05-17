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
	BgDrawPrintf(3, row, "for ViperV16 RISE GBA Port");

	u32 sel = 0;
	u8 stat = PLAYER_STAT_STOP;
	s32 opt_loop = 0;
	s32 opt_waveedit = 0;
	s32 opt_headset = 0;
	s32 opt_fadeout = 0;

	u8 dev_waveedit = 1;

	s32 ptr_wave = 0;
	s8 wave_byte = 0;
	s8 upper_wave = 0;
	s8 lower_wave = 0;

	u32 max = GbfsGetArcCnt() - 1;

	// u8*   pS = GbfsGetSafePointer2(sel);
	GbfsGetSafePointer2(sel);
	char* pF = GbfsGetFileName();

	// VgmPlay(sel);

	for(;;)
	{
		VBlankIntrWait();
		stat = VgmGetStat();
		opt_loop = VgmGetIsLoop();
		opt_waveedit = VgmGetIsWaveEdit();
		opt_headset = VgmGetIsHeadset();
		opt_fadeout = VgmGetIsFade();

		row = 0;
		BgDrawPrintf(23, row, "       ");
		BgDrawPrintf(23, row, "%X", VgmGetOffsetPlay());

		row++;
		BgDrawPrintf(24, row, (stat == PLAYER_STAT_RESERVE) ? "%02d" : "  ", VgmGetFadeCnt());
		BgDrawPrintf(26, row, (stat == PLAYER_STAT_STOP) ? "[]" : "|>");
		BgDrawPrintf(28, row, "%02d", VgmGetTrId() + 1);

		row++;
		BgDrawPrintf(0, row, "%2d/%2d:", sel + 1, max + 1);

		BgDrawPrintf(7, row, "                        ");
		BgDrawPrintf(7, row, "%s", pF);
		row++;
		BgDrawPrintf(0, row, " ");


		row = 4;
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetAgReg(AGREG_NR10));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR11));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR12));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetAgReg(AGREG_NR13));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetAgReg(AGREG_NR14));

		BgDrawPrintf(28, row, (0 == opt_loop) ? "F" : "T");

		row++;
		BgDrawPrintf(7+0*3, row, "--");
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR21));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR22));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetAgReg(AGREG_NR23));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetAgReg(AGREG_NR24));

		row++;
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetAgReg(AGREG_NR30));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR31));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR32));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetAgReg(AGREG_NR33));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetAgReg(AGREG_NR34));

		row++;
		BgDrawPrintf(7+0*3, row, "--");
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR41));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR42));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetAgReg(AGREG_NR43));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetAgReg(AGREG_NR44));

		row++;
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetAgReg(AGREG_NR50));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR51));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR52));

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
		row++;
		BgDrawPrintf(0, row, (opt_waveedit != 0) ? "(edit)" : "      ");
		BgDrawPrintf(6, row, "                        ");

		row++;
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
		row++;
		BgDrawPrintf(0, row, "                              ");

		if(opt_waveedit != 0){
			if(ptr_wave < 0x08)
			{
				BgDrawPrintf(7+ptr_wave, row-2, "^");
			}
			else if(ptr_wave < 0x10)
			{
				BgDrawPrintf(7+ptr_wave+1, row-2, "^");
			}
			else if(ptr_wave < 0x18)
			{
				BgDrawPrintf(7+ptr_wave-0x10, row, "^");
			}
			else
			{
				BgDrawPrintf(7+ptr_wave+1-0x10, row, "^");
			}
		}

		row++;
		BgDrawPrintf(7, row, (0 == opt_waveedit) ? (0 == opt_headset) ? "speaker" : "headset": "debug  ");
		BgDrawPrintf(22, row, (0 == opt_fadeout) ? "F" : "T");


		KeyExec();
		u16 trg = KeyGetTrg();
		if(0 == opt_waveedit)
		{
			if((trg & KEY_RIGHT) && sel < max)
			{
				sel++;

				GbfsGetSafePointer2(sel);
				pF = GbfsGetFileName();
			}
			if((trg & KEY_LEFT) && sel > 0)
			{
				sel--;

				GbfsGetSafePointer2(sel);
				pF = GbfsGetFileName();
			}

			if((trg & KEY_DOWN) && sel < max)
			{
				sel = (sel + 10 <= max) ? sel + 10 : max;

				GbfsGetSafePointer2(sel);
				pF = GbfsGetFileName();
			}
			if((trg & KEY_UP) && sel > 0)
			{
				sel = (sel >= 10) ? sel - 10 : 0;

				GbfsGetSafePointer2(sel);
				pF = GbfsGetFileName();
			}

			if((trg & KEY_R) && sel < max)
			{
				sel = max;

				GbfsGetSafePointer2(sel);
				pF = GbfsGetFileName();
			}
			if((trg & KEY_L) && sel > 0)
			{
				sel = 0;

				GbfsGetSafePointer2(sel);
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
				wave_byte = VgmGetWave(ptr_wave / 2);
				upper_wave = wave_byte & 0xf0;
				lower_wave = wave_byte & 0x0f;

				if(1 == ptr_wave % 2)
				{
					lower_wave = (lower_wave + 0x0f) & 0x0f;
				}
				else
				{
					upper_wave = (upper_wave + 0xf0) & 0xf0;
				}
				VgmSetWave(ptr_wave / 2, upper_wave + lower_wave);
			}
			if((trg & KEY_UP))
			{
				wave_byte = VgmGetWave(ptr_wave / 2);
				upper_wave = wave_byte & 0xf0;
				lower_wave = wave_byte & 0x0f;

				if(1 == ptr_wave % 2)
				{
					lower_wave = (lower_wave + 0x01) & 0x0f;
				}
				else
				{
					upper_wave = (upper_wave + 0x10) & 0xf0;
				}
				VgmSetWave(ptr_wave / 2, upper_wave + lower_wave);
			}

			if((trg & KEY_R))
			{
				for(u32 i = 0; i < 0x10; i++)
				{
					VgmSetWave(i, 0x00);
				}
			}
			if((trg & KEY_L))
			{
				for(u32 i = 0; i < 0x10; i++)
				{
					VgmSetWave(i, 0x77);
				}
			}
		}

		if((trg & KEY_START) && dev_waveedit == 1)
		{
			opt_waveedit = (opt_waveedit + 1) % 2;
			VgmSetWaveEdit(opt_waveedit);
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
				VgmReserve(sel);
			}
			else
			{
				VgmPlay(sel);
			}
		}
		if(trg & KEY_B)
		{
			VgmStop();
		}

	}
}
