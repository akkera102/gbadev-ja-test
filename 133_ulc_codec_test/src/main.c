#include "libgba/gba.h"
#include "irq.arm.h"
#include "ulc.arm.h"
#include "bg.h"
#include "key.h"
#include "gbfs.h"
#include "mem.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	MemInit();
	GbfsInit();
	BgInit();
	KeyInit();

	UlcInit();
	IrqInit();

	BgDrawPrintf(1, 8, "13379Hz ulc-codec Test");

	s32 i = 0;
	s32 m = 0;
	s32 v;
	s32 a = GbfsGetArcCnt();

	for(;;)
	{
		VBlankIntrWait();

		// start vcount 0
		while(*(vu16*)0x4000006 != 0) {};

		*(vu16*)0x5000000 = RGB5(0, 15, 0);
		UlcMix();
		*(vu16*)0x5000000 = RGB5(0,  0, 0);

		v = REG_VCOUNT;
		BgDrawPrintf(1, 10, "VCNT:%03d", v);
		BgDrawPrintf(1, 11, "VMAX:%03d", m);
		BgDrawPrintf(1, 12, " BLK:%05d", UlcGetBlkRem());
		BgDrawPrintf(1, 13, " SEL:%03d/%03d", i, a - 1);

		// see... mGBA or vba1.8.0-beta3
		TRACE("%d\n", v);

		if(m < v)
		{
			m = v;
		}

		if(UlcIsPlay() == true)
		{
			BgDrawPrintf(1, 15, "PLAY");
		}
		else
		{
			BgDrawPrintf(1, 15, "STOP");
		}

		KeyExec();
		u16 trg = KeyGetTrg();

		if((trg & KEY_RIGHT) && i < a - 1)
		{
			i++;
		}

		if((trg & KEY_LEFT ) && i > 0)
		{
			i--;
		}

		if(trg & KEY_A)
		{
			u8* p = GbfsGetSafePointer2(i);
			UlcPlay(p, false);
		}

		if(trg & KEY_B)
		{
			UlcStop();
		}
	}
}
