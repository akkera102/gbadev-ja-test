#include "libmy.h"
#include "mem.h"
#include "gbfs.h"
#include "key.h"
#include "sav.h"
#include "mode3.h"
#include "spr.h"
#include "fade.h"
#include "sjis.h"
#include "irq.arm.h"
#include "lex.h"
#include "vgm.arm.h"
#include "ad.arm.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void LibMyInit(void)
{
	REG_WSCNT = 0x4317;
	REG_DISPCNT = MODE_3 | BG2_ON | OBJ_ON | OBJ_1D_MAP;

	GbfsInit();
	LexInit();
	MemInit();
	KeyInit();
	SavInit();

	SprInit();
	SjisInit();
	Mode3Init();
	FadeInit();

	VgmInit();
	AdInit();
	IrqInit();
}
//---------------------------------------------------------------------------
IWRAM_CODE void LibMyExec(void)
{
	KeyExec();
	Mode3Exec();
}
