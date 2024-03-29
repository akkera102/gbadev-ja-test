#include "fade.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void FadeInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetMode(s32 mode, s32 cnt)
{
	REG_BLDCNT = (mode | BLEND_TOP_BG2);

	REG_BLDY = cnt;
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetBlack(s32 cnt)
{
	FadeSetMode(BLEND_MODE_DARK, cnt);
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetWhite(s32 cnt)
{
	FadeSetMode(BLEND_MODE_LIGHT, cnt);
}
