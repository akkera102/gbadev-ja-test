#include "libgba/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "mem.h"
#include "math.h"
#include "eff.arm.h"

//---------------------------------------------------------------------------
extern ST_EFF Eff;


//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	MathInit();
	MemInit();
	KeyInit();
	BgInit();
	EffInit();

	IrqInit();

	BgDrawPrintf(4,  0, "|MODE 1 ENGINE |");
	BgDrawPrintf(4,  1, "|              |");
	BgDrawPrintf(4,  2, "|PSEUDO-MODE 7 |");
	BgDrawPrintf(4,  3, "|H-BLANK EFFECT|");
	BgDrawPrintf(4,  4, "|              |");
	BgDrawPrintf(4,  5, "|CAM-X:  %5d |", Eff.cam.x >> 8);
	BgDrawPrintf(4,  6, "|CAM-Y:  %5d |", Eff.cam.y >> 8);
	BgDrawPrintf(4,  7, "|CAM-Z:  %5d |", Eff.cam.z >> 6);

	for(;;)
	{
		VBlankIntrWait();

		BgDrawPrintf(4,  5, "|CAM-X:  %5d |", Eff.cam.x >> 8);
		BgDrawPrintf(4,  6, "|CAM-Y:  %5d |", Eff.cam.y >> 8);
		BgDrawPrintf(4,  7, "|CAM-Z:  %5d |", Eff.cam.z >> 6);
	}
}
