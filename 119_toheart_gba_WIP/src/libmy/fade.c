#include "fade.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void FadeInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetMode(u32 mode, u32 cnt)
{
	REG_BLDCNT = (mode | BLEND_TOP_BG2);
	REG_BLDY = cnt;
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetBlack(u32 cnt)
{
	FadeSetMode(BLEND_MODE_DARK, cnt);
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetWhite(u32 cnt)
{
	FadeSetMode(BLEND_MODE_LIGHT, cnt);
}
