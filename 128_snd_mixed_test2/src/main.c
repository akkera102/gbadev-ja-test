#include "libgba/gba.h"
#include "irq.arm.h"
#include "snd.arm.h"
#include "bg.h"
#include "key.h"
#include "gbfs.h"

//---------------------------------------------------------------------------
void play(s32 no)
{
	s8* p = GbfsGetSafePointer2(no);
	u32 size = GbfsGetFileSize();

	SndPlay(p, size, 64);
}
//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	GbfsInit();
	BgInit();
	KeyInit();

	SndInit();
	IrqInit();

	BgDrawPrintf(1, 1, "13379Hz Sound Mixing Test");

	for(;;)
	{
		VBlankIntrWait();

		// start vcount 0
		while(*(vu16*)0x4000006 != 0) {};

		*(vu16*)0x5000000 = RGB5(0, 15, 0);
		SndMix();
		*(vu16*)0x5000000 = RGB5(0,  0, 0);


		BgDrawPrintf(1, 3, "VCNT:%03d", REG_VCOUNT, SndGetReg());
		BgDrawPrintf(1, 4, " REG:%3d", SndGetReg());

		s32 i;

		for(i=0; i<SndGetMax(); i++)
		{
			BgDrawPrintf(2, 6+i, "%d. %4X", i, SndGetCur(i));
		}

		BgDrawPrintf(1, 16, " START: chancel");


		KeyExec();
		u16 trg = KeyGetTrg();

		if(trg & KEY_A)     play(0);
		if(trg & KEY_B)     play(1);
		if(trg & KEY_L)     play(2);
		if(trg & KEY_R)     play(3);
		if(trg & KEY_UP)    play(4);
		if(trg & KEY_DOWN)  play(5);
		if(trg & KEY_LEFT)  play(6);
		if(trg & KEY_RIGHT) play(7);
		if(trg & KEY_START) SndClear();
	}
}
