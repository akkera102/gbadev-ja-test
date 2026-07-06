#include "libmy.h"
#include "mem.arm.h"
#include "gbfs.h"
#include "key.h"
#include "sav.h"
#include "mode3.arm.h"
#include "spr.h"
#include "fade.h"
#include "sjis.h"
#include "irq.arm.h"
#include "sfx.arm.h"
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
