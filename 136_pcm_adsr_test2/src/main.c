#include "libgba/gba.h"
#include "irq.arm.h"
#include "snd.arm.h"
#include "bg.h"
#include "key.h"
#include "mem.h"
#include "res.h"


//---------------------------------------------------------------------------
const char* const inst[] = {
	wav_0_sine_bin,
	wav_1_guitar_bin,
	wav_2_harmonica_bin,
	wav_3_piano_bin,
	wav_4_brass_bin,
	wav_5_clarinet_bin,
	wav_6_string_bin,
	wav_7_organ_bin,
	wav_8_vibe_bin,
	wav_9_electric_lead_bin,
};

const s32 adsr[] = {
//  atkS, decS, susS,  relS,  atkL,  susL
    1800, 1500,    2,  1200, 18000,  8000,    // 0: Sine
    1800, 4500,    0,  1200, 22000,  4000,    // 1: Guitar
    1600, 1000,    5,  1200, 18000, 10000,    // 2: Harmonica
    1800, 5000,    0,  1200, 22000,  2000,    // 3: Piano
    1800, 2500,    3,  1200, 20000, 12000,    // 4: Brass
    1600, 1200,    5,  1200, 17000, 10000,    // 5: Clarinet
    1600,  800,    8,  1200, 18000, 15000,    // 6: Strings
    1800,    0,   10,  1200, 16000, 16000,    // 7: Organ
    1800, 5000,    0,  1200, 22000,  1500,    // 8: Vibe
    1800, 3000,    2,  1200, 21000, 11000     // 9: Electric Lead
};
//---------------------------------------------------------------------------
enum {
	CMD_NOTE = 0,
	CMD_WAIT,
	CMD_STOP,
};

const u32 CanonData[] = {
    CMD_NOTE, SND_NOTE_C4, 0,
    CMD_NOTE, SND_NOTE_E3, 1,
    CMD_NOTE, SND_NOTE_C3, 6,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_B3, 0,
    CMD_NOTE, SND_NOTE_D3, 1,
    CMD_NOTE, SND_NOTE_G2, 6,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_A3, 0,
    CMD_NOTE, SND_NOTE_C3, 1,
    CMD_NOTE, SND_NOTE_A2, 6,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_G3, 0,
    CMD_NOTE, SND_NOTE_B2, 1,
    CMD_NOTE, SND_NOTE_E2, 6,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_F3, 0,
    CMD_NOTE, SND_NOTE_A2, 1,
    CMD_NOTE, SND_NOTE_F2, 6,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_E3, 0,
    CMD_NOTE, SND_NOTE_G2, 1,
    CMD_NOTE, SND_NOTE_C2, 6,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_F3, 0,
    CMD_NOTE, SND_NOTE_A2, 1,
    CMD_NOTE, SND_NOTE_F2, 6,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_G3, 0,
    CMD_NOTE, SND_NOTE_B2, 1,
    CMD_NOTE, SND_NOTE_G2, 6,
    CMD_WAIT, 60, 0,

    CMD_NOTE, SND_NOTE_C3, 6,
    CMD_NOTE, SND_NOTE_E4, 1,
    CMD_NOTE, SND_NOTE_C5, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_B4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_G2, 6,
    CMD_NOTE, SND_NOTE_D4, 1,
    CMD_NOTE, SND_NOTE_B4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_C5, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_A2, 6,
    CMD_NOTE, SND_NOTE_C4, 1,
    CMD_NOTE, SND_NOTE_A4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_G4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_E2, 6,
    CMD_NOTE, SND_NOTE_B3, 1,
    CMD_NOTE, SND_NOTE_G4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_F4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_F2, 6,
    CMD_NOTE, SND_NOTE_A3, 1,
    CMD_NOTE, SND_NOTE_F4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_E4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_C2, 6,
    CMD_NOTE, SND_NOTE_G3, 1,
    CMD_NOTE, SND_NOTE_D4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_C4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_F2, 6,
    CMD_NOTE, SND_NOTE_A3, 1,
    CMD_NOTE, SND_NOTE_C4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_D4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_G2, 6,
    CMD_NOTE, SND_NOTE_B3, 1,
    CMD_NOTE, SND_NOTE_D4, 0,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_E4, 0,
    CMD_WAIT, 30, 0,

    CMD_NOTE, SND_NOTE_C3, 6,
    CMD_NOTE, SND_NOTE_E4, 1,
    CMD_NOTE, SND_NOTE_G4, 1,
    CMD_NOTE, SND_NOTE_C5, 0,
    CMD_NOTE, SND_NOTE_E5, 0,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_G2, 6,
    CMD_NOTE, SND_NOTE_D4, 1,
    CMD_NOTE, SND_NOTE_F4, 1,
    CMD_NOTE, SND_NOTE_B4, 0,
    CMD_NOTE, SND_NOTE_D5, 0,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_A2, 6,
    CMD_NOTE, SND_NOTE_C4, 1,
    CMD_NOTE, SND_NOTE_E4, 1,
    CMD_NOTE, SND_NOTE_A4, 0,
    CMD_NOTE, SND_NOTE_C5, 0,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_E2, 6,
    CMD_NOTE, SND_NOTE_B3, 1,
    CMD_NOTE, SND_NOTE_D4, 1,
    CMD_NOTE, SND_NOTE_G4, 0,
    CMD_NOTE, SND_NOTE_B4, 0,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_F2, 6,
    CMD_NOTE, SND_NOTE_A3, 1,
    CMD_NOTE, SND_NOTE_C4, 1,
    CMD_NOTE, SND_NOTE_F4, 0,
    CMD_NOTE, SND_NOTE_A4, 0,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_C2, 6,
    CMD_NOTE, SND_NOTE_G3, 1,
    CMD_NOTE, SND_NOTE_B3, 1,
    CMD_NOTE, SND_NOTE_E4, 0,
    CMD_NOTE, SND_NOTE_G4, 0,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_F2, 6,
    CMD_NOTE, SND_NOTE_A3, 1,
    CMD_NOTE, SND_NOTE_C4, 1,
    CMD_NOTE, SND_NOTE_F4, 0,
    CMD_NOTE, SND_NOTE_A4, 0,
    CMD_WAIT, 60, 0,
    CMD_NOTE, SND_NOTE_G2, 6,
    CMD_NOTE, SND_NOTE_B3, 1,
    CMD_NOTE, SND_NOTE_D4, 1,
    CMD_NOTE, SND_NOTE_G4, 0,
    CMD_NOTE, SND_NOTE_B4, 0,
    CMD_WAIT, 60, 0,

    CMD_NOTE, SND_NOTE_C3, 6,
    CMD_NOTE, SND_NOTE_G4, 1,
    CMD_NOTE, SND_NOTE_C5, 0,
    CMD_WAIT, 120, 0,
    CMD_STOP, 0, 0
};


const u32 FrogData[] = {
    CMD_NOTE, SND_NOTE_C4, 2,
    CMD_NOTE, SND_NOTE_C3, 3,
    CMD_NOTE, SND_NOTE_G3, 3,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_D4, 2,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_E4, 2,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_F4, 2,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_E4, 2,
    CMD_NOTE, SND_NOTE_E3, 3,
    CMD_NOTE, SND_NOTE_B3, 3,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_D4, 2,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_C4, 2,
    CMD_WAIT, 60, 0,

    CMD_NOTE, SND_NOTE_E4, 2,
    CMD_NOTE, SND_NOTE_C5, 4,
    CMD_NOTE, SND_NOTE_C3, 3,
    CMD_NOTE, SND_NOTE_G3, 3,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_F4, 2,
    CMD_NOTE, SND_NOTE_D5, 4,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_G4, 2,
    CMD_NOTE, SND_NOTE_E5, 4,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_A4, 2,
    CMD_NOTE, SND_NOTE_F5, 4,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_G4, 2,
    CMD_NOTE, SND_NOTE_E5, 4,
    CMD_NOTE, SND_NOTE_E3, 3,
    CMD_NOTE, SND_NOTE_B3, 3,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_F4, 2,
    CMD_NOTE, SND_NOTE_D5, 4,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_E4, 2,
    CMD_NOTE, SND_NOTE_C5, 4,
    CMD_WAIT, 60, 0,

    CMD_NOTE, SND_NOTE_C4, 2,
    CMD_NOTE, SND_NOTE_C5, 4,
    CMD_NOTE, SND_NOTE_C3, 3,
    CMD_NOTE, SND_NOTE_E3, 3,
    CMD_NOTE, SND_NOTE_G3, 3,
    CMD_WAIT, 15, 0,
    CMD_NOTE, SND_NOTE_C4, 2,
    CMD_NOTE, SND_NOTE_C5, 4,
    CMD_WAIT, 15, 0,
    CMD_NOTE, SND_NOTE_C4, 2,
    CMD_NOTE, SND_NOTE_C5, 4,
    CMD_WAIT, 15, 0,
    CMD_NOTE, SND_NOTE_C4, 2,
    CMD_NOTE, SND_NOTE_C5, 4,
    CMD_WAIT, 15, 0,

    CMD_NOTE, SND_NOTE_D4, 2,
    CMD_NOTE, SND_NOTE_F4, 2,
    CMD_NOTE, SND_NOTE_A2, 3,
    CMD_NOTE, SND_NOTE_D3, 3,
    CMD_NOTE, SND_NOTE_A4, 4,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_E4, 2,
    CMD_NOTE, SND_NOTE_G4, 2,
    CMD_NOTE, SND_NOTE_G2, 3,
    CMD_NOTE, SND_NOTE_C3, 3,
    CMD_NOTE, SND_NOTE_B4, 4,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_F4, 2,
    CMD_NOTE, SND_NOTE_A4, 2,
    CMD_NOTE, SND_NOTE_G2, 3,
    CMD_NOTE, SND_NOTE_B2, 3,
    CMD_NOTE, SND_NOTE_D5, 4,
    CMD_WAIT, 30, 0,
    CMD_NOTE, SND_NOTE_E4, 2,
    CMD_NOTE, SND_NOTE_G4, 2,
    CMD_NOTE, SND_NOTE_C3, 3,
    CMD_NOTE, SND_NOTE_G3, 3,
    CMD_NOTE, SND_NOTE_C5, 4,
    CMD_WAIT, 30, 0,

    CMD_NOTE, SND_NOTE_C4, 2,
    CMD_NOTE, SND_NOTE_G3, 3,
    CMD_NOTE, SND_NOTE_C3, 3,
    CMD_WAIT, 90, 0,
    CMD_STOP, 0, 0
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

Restart:

	bool isKey = false;
	u32  i = 0;
	u32  n = 0;
	u32  s = 0;
	u32  w = 2;		// mGBA puti noise wait...
	u32* d = (u32*)&CanonData;

	BgDrawPrintf(0, 10, "13359Hz/256-sample resolution");

	for(;;)
	{
		VBlankIntrWait();

		// start vcount 0
		while(*(vu16*)0x4000006 != 0) {};

		*(vu16*)0x5000000 = RGB5(0, 15, 0);
		SndMix();
		*(vu16*)0x5000000 = RGB5(0,  0, 0);

		BgDrawPrintf(0, 12, "VCNT:%03d", REG_VCOUNT);
		BgDrawPrintf(0, 13, " ACT:%03d", SndGetCnt());
		BgDrawPrintf(0, 15, "SONG!  ");

		KeyExec();
		u32 trg = KeyGetTrg();

		if(trg & KEY_A)
		{
			break;
		}

		if(w > 0)
		{
			w--;

			continue;
		}

		u32 cmd = d[s+0];
		n = d[s+1];
		i = d[s+2];
		s += 3;

		if(cmd == CMD_WAIT)
		{
			w = n;

			continue;
		}

		if(cmd == CMD_NOTE)
		{
			SndPlay(n, (s8*)inst[i], adsr[i*6+0], adsr[i*6+1], adsr[i*6+2], adsr[i*6+3], adsr[i*6+4], adsr[i*6+5]);

			continue;
		}

		if(cmd == CMD_STOP)
		{
			if(d == FrogData)
			{
				break;
			}

			s = 0;
			w = 15;
			d = (u32*)&FrogData;

			continue;
		}
	}

	for(;;)
	{
		VBlankIntrWait();

		// start vcount 0
		while(*(vu16*)0x4000006 != 0) {};

		*(vu16*)0x5000000 = RGB5(0, 15, 0);
		SndMix();
		*(vu16*)0x5000000 = RGB5(0,  0, 0);

		BgDrawPrintf(0, 12, "VCNT:%03d", REG_VCOUNT);
		BgDrawPrintf(0, 13, " ACT:%03d", SndGetCnt());
		BgDrawPrintf(0, 15, "INST:%d", i);


		KeyExec();
		u32 trg = KeyGetTrg();

		if(trg & KEY_L)     { isKey = true; n = SND_NOTE_C4; };
		if(trg & KEY_R)     { isKey = true; n = SND_NOTE_D4; };
		if(trg & KEY_A)     { isKey = true; n = SND_NOTE_E4; };
		if(trg & KEY_B)     { isKey = true; n = SND_NOTE_F4; };
		if(trg & KEY_LEFT)  { isKey = true; n = SND_NOTE_G4; };
		if(trg & KEY_UP)    { isKey = true; n = SND_NOTE_A4; };
		if(trg & KEY_DOWN)  { isKey = true; n = SND_NOTE_B4; };
		if(trg & KEY_RIGHT) { isKey = true; n = SND_NOTE_C5; };

		if(trg & KEY_SELECT)
		{
			goto Restart;
		}

		if(trg & KEY_START)
		{
			SndStop();
			i++;

			if(i >= 10)
			{
				i = 0;
			}
		}

		if(isKey == true)
		{
			SndPlay(n, (s8*)inst[i], adsr[i*6+0], adsr[i*6+1], adsr[i*6+2], adsr[i*6+3], adsr[i*6+4], adsr[i*6+5]);

			isKey = false;
		}
	}
}
