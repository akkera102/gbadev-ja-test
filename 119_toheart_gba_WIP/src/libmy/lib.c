#include "lib.h"
#include "bios.h"
#include "fade.h"
#include "gbfs.h"
#include "irq.arm.h"
#include "key.h"
#include "mode3.h"
#include "snd.h"
#include "spr.h"
#include "sav.h"
#include "sjis.h"
#include "vgm.arm.h"


//---------------------------------------------------------------------------
EWRAM_CODE void LibInit(void)
{
	REG_WSCNT = 0x4317;

	VgmInit();
	BiosInit();
	FadeInit();
	GbfsInit();
	KeyInit();
	Mode3Init();
	SndInit();
	SprInit();
	SavInit();
	SjisInit();

	IrqInit();
}
//---------------------------------------------------------------------------
IWRAM_CODE void LibExec(void)
{
	KeyExec();
	SprExec();
	Mode3Exec();
}
