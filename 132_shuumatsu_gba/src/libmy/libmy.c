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
#include "snd.arm.h"
#include "vgm.arm.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void LibMyInit(void)
{
	REG_WSCNT = 0x4317;
	REG_DISPCNT = MODE_3 | BG2_ON | OBJ_ON | OBJ_1D_MAP;

	GbfsInit();
	MemInit();
	KeyInit();
	SavInit();

	SprInit();
	SjisInit();
	Mode3Init();
	FadeInit();

	SndInit();
	VgmInit();
	IrqInit();
}
//---------------------------------------------------------------------------
IWRAM_CODE void LibMyExec(void)
{
	KeyExec();
}
