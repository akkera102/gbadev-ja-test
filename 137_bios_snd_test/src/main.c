#include "libgba/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "mem.h"
#include "mp.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	KeyInit();
	MemInit();
	MpInit();
	IrqInit();

	BgDrawPrintf(1,  2, "BIOS SOUND TEST(0x1A-21)");
	BgDrawPrintf(1,  4, "A    : boot first half");
	BgDrawPrintf(1,  5, "B    : boot second half");
	BgDrawPrintf(1,  7, "UP   : Multiboot standby1");
	BgDrawPrintf(1,  8, "DOWN : Multiboot standby2");
	BgDrawPrintf(1,  9, "LEFT : Multiboot ready");
	BgDrawPrintf(1, 10, "RIGH : Repeat music");
	BgDrawPrintf(1, 11, "L    : mode change");
	BgDrawPrintf(1, 12, "R    : doremi");

	bool isMode = false;
	s32 cnt = 0;

	MpSetModeNor();
	MpPlayMus();

	for(;;)
	{
		VBlankIntrWait();

		BgDrawPrintf(0,  0, "%02d", MpGetActiveCnt());
		BgDrawPrintf(1, 15, "mode set to %c", (isMode == true) ? 'R' : 'N');

		// start vcount 0
		while(*(vu16*)0x4000006 != 0) {};

		*(vu16*)0x5000000 = RGB5(0, 15, 0);
		MpExecSwi1D();
		MpExecSwi1C();
		*(vu16*)0x5000000 = RGB5(0,  0, 0);


		KeyExec();
		u16 trg = KeyGetTrg();

		if(trg & KEY_A)
		{
			MpPlayAdr(0x3908);
		}

		if(trg & KEY_B)
		{
			MpPlayAdr(0x39c0);
		}

		if(trg & KEY_UP)
		{
			MpPlayAdr(0x389c);
		}

		if(trg & KEY_DOWN)
		{
			MpPlayAdr(0x3818);
		}

		if(trg & KEY_LEFT)
		{
			MpPlayAdr(0x3980);
		}

		if(trg & KEY_RIGHT)
		{
			MpStopAll();

			if(isMode == true)
			{
				MpSetModeRev();
			}
			else
			{
				MpSetModeNor();
			}

			MpPlayMus();
		}

		if(trg & KEY_L)
		{
			if(isMode == false)
			{
				MpSetModeRev();
				isMode = true;
			}
			else
			{
				MpSetModeNor();
				isMode = false;
			}
		}

		if(trg & KEY_R)
		{
			MpPlayKey(cnt, 60 + cnt);		// ch, midikey

			cnt++;

			if(cnt >= MP_MAX_CH)
			{
				cnt = 0;
			}
		}
	}
}
