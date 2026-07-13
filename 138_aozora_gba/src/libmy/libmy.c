#include "libmy.h"
#include "fade.h"
#include "gbfs.h"
#include "irq.arm.h"
#include "key.h"
#include "mem.arm.h"
#include "mode3.arm.h"
#include "sav.h"
#include "sfx.arm.h"
#include "sjis.h"
#include "spr.h"
#include "ulc.arm.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void LibMyInit(void)
{
	REG_WSCNT = 0x4317;

	GbfsInit();
	MemInit();
	KeyInit();
	SavInit();

	SprInit();
	SjisInit();
	Mode3Init();
	FadeInit();

	UlcInit();
	SfxInit();
	IrqInit();
}
//---------------------------------------------------------------------------
IWRAM_CODE void LibMyExec(void)
{
	KeyExec();
}
