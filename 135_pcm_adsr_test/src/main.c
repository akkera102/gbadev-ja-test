#include "libgba/gba.h"
#include "irq.arm.h"
#include "snd.arm.h"
#include "bg.h"
#include "key.h"
#include "mem.h"
#include "res.h"


//---------------------------------------------------------------------------
const char* const inst[] = {
	inst_0_sine_bin,
	inst_1_piano_bin,
	inst_2_flute_bin,
	inst_3_violin_bin,
	inst_4_trumpet_bin,
	inst_5_bass_bin,
	inst_6_church_organ_bin,
	inst_7_music_box_bin,
	inst_8_xylophone_bin,
	inst_9_harmonica_bin,
};

const s32 adsr[] = {
//   atk, dec, sus_l, sus_s, rel
	1310, 100, 32768,  3340,  32,		// 0: Sine
	8000, 300, 15000,  5000,  64,		// 1: Piano (’@‚­‰¹)
	 500, 100, 45000,  6000, 100,		// 2: Flute (‚¶‚í‚Á‚Æo‚é)
	 300, 100, 50000,  6000,  80,		// 3: Violin (—§‚¿ã‚ª‚è‚ª’x‚¢)
	2000, 200, 40000,  5000,  40,		// 4: Trumpet (‰s‚¢)
	4000, 500, 10000,  2000,  32,		// 5: Wood Bass (’áˆæ‚ÌŒ¸Š)
	1000,   0, 60000,  8000, 150,		// 6: Organ (Á‚¦‚É‚­‚¢)
	9000, 100,  5000,  1000, 300,		// 7: Music Box (’·‚¢—]‰C)
	9500, 200, 15000,  3000,  40,		// 8: Xylophone (Ž©‘R‚ÉŒ¸Š)
	 800, 100, 40000,  6000,  60,		// 9: Harmonica
};

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	MemInit();
	BgInit();
	KeyInit();

	SndInit();
	IrqInit();

	u32 i = 0;

	SndSetAdsr();
	SndSetInst((s8*)inst[i], adsr[i*5+0], adsr[i*5+1], adsr[i*5+2], adsr[i*5+3], adsr[i*5+4]);

	BgDrawPrintf(0,  0, " L: c3 DO");
	BgDrawPrintf(0,  1, " R: d3 RE");
	BgDrawPrintf(0,  2, " A: e3 MI");
	BgDrawPrintf(0,  3, " B: f3 FA");
	BgDrawPrintf(0,  4, "LE: g3 SO");
	BgDrawPrintf(0,  5, "UP: a3 RA");
	BgDrawPrintf(0,  6, "DO: b3 SI");
	BgDrawPrintf(0,  7, "RI: c4 DO");

	BgDrawPrintf(0,  9, "INST: 0:sine 1:piano 2:flute");
	BgDrawPrintf(0, 10, "3:violin 4:trumpet 5:bass");
	BgDrawPrintf(0, 11, "6:organ 7:mbox 8:xylophone");
	BgDrawPrintf(0, 12, "9:harmonica");


	for(;;)
	{
		VBlankIntrWait();

		// start vcount 0
		while(*(vu16*)0x4000006 != 0) {};

		*(vu16*)0x5000000 = RGB5(0, 15, 0);
		SndMix();
		*(vu16*)0x5000000 = RGB5(0,  0, 0);

		BgDrawPrintf(0, 14, "VCNT: %03d", REG_VCOUNT);
		BgDrawPrintf(0, 15, " ACT: %03d 13379Hz", SndGetActCnt());

		if(SndIsAdsr() == true)
		{
			BgDrawPrintf(0, 16, "ADSR: ON ");
		}
		else
		{
			BgDrawPrintf(0, 16, "ADSR: OFF");
		}

		BgDrawPrintf(0, 17, "INST: %d", i);


		KeyExec();
		u32 trg = KeyGetTrg();

		if(trg & KEY_L)     SndPlay(SND_NOTE_C4);
		if(trg & KEY_R)     SndPlay(SND_NOTE_D);
		if(trg & KEY_A)     SndPlay(SND_NOTE_E);
		if(trg & KEY_B)     SndPlay(SND_NOTE_F);
		if(trg & KEY_LEFT)  SndPlay(SND_NOTE_G);
		if(trg & KEY_UP)    SndPlay(SND_NOTE_A);
		if(trg & KEY_DOWN)  SndPlay(SND_NOTE_B);
		if(trg & KEY_RIGHT) SndPlay(SND_NOTE_C5);

		if(trg & KEY_SELECT)
		{
			SndStop();
			SndSetAdsr();
		}

		if(trg & KEY_START)
		{
			i++;

			if(i >= 10)
			{
				i = 0;
			}

			SndStop();
			SndSetInst((s8*)inst[i], adsr[i*5+0], adsr[i*5+1], adsr[i*5+2], adsr[i*5+3], adsr[i*5+4]);
		}
	}
}
