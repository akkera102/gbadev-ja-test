#include "libmy.h"
#include "mem.h"
#include "gbfs.h"
#include "key.h"
#include "sav.h"
#include "mode4.arm.h"
#include "spr.h"
#include "fade.h"
#include "sjis.h"
#include "irq.arm.h"
#include "vgm.arm.h"
#include "snd.arm.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void LibMyInit(void)
{
	REG_WSCNT = 0x4317;
	REG_DISPCNT = MODE_4 | BG2_ON | OBJ_ON | OBJ_2D_MAP | WIN0_ENABLE;

	GbfsInit();
	MemInit();
	KeyInit();
	SavInit();

	SprInit();
	SjisInit();
	Mode4Init();
	FadeInit();

	SndInit();
	VgmInit();
	IrqInit();
}
//---------------------------------------------------------------------------
IWRAM_CODE void LibMyExec(void)
{
	KeyExec();
	Mode4Exec();
}
