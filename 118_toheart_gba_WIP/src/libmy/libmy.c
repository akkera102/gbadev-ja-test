#include "libmy.h"
#include "ad_arm.h"
#include "bios_arm.h"
#include "fade.h"
#include "gbfs.h"
#include "irq_arm.h"
#include "key.h"
#include "lex.h"
#include "mode3.h"
#include "snd.h"
#include "spr.h"
#include "bak.h"

//---------------------------------------------------------------------------
EWRAM_CODE void LibMyInit(void)
{
	REG_WSCNT = 0x4317;

	AdInit();
	BiosInit();
	FadeInit();
	GbfsInit();
	KeyInit();
	LexInit();
	Mode3Init();
	SndInit();
	SprInit();
	BakInit();

	IrqInit();
}
//---------------------------------------------------------------------------
IWRAM_CODE void LibMyExec(void)
{
	KeyExec();
	SprExec();
	Mode3Exec();
}
