#include "lib/gba.h"
#include "bg.h"
#include "irq.arm.h"
#include "key.h"
#include "dme.arm.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	GbfsInit();
	BgInit();
	KeyInit();

	DmeInit();
	IrqInit();

	u8* p = GbfsGetSafePointer("all.bin");
	DmePlay(p, 0x800);

	BgAsciiDrawStr(1, 1, "DeflemaskGBVGM v0.6");

	for(;;)
	{
	    VBlankIntrWait();

		KeyExec();
	}
}
