#include "libmy.h"
#include "fade.h"
#include "gbfs.h"
#include "irq.arm.h"
#include "mem.arm.h"
#include "mode4.arm.h"
#include "ad.arm.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void LibMyInit(void)
{
	REG_WSCNT = 0x4317;

	GbfsInit();
	MemInit();

	FadeInit();
	Mode4Init();

	AdInit();
	IrqInit();
}
//---------------------------------------------------------------------------
IWRAM_CODE void LibMyExec(void)
{
	// EMPTY
}
