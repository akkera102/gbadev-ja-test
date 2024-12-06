#include "fade.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void FadeInit(void)
{
	REG_WININ  = WIN_0_BG2 | WIN_0_OBJ | WIN_0_SPE;
	REG_WINOUT = WIN_0_BG2 | WIN_0_OBJ;

	FadeSetBlack(16);
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetScr(s32 mode, s32 cnt)
{
	REG_WIN0H  = WIN_LEFT(0) | WIN_RIGHT(240);
	REG_WIN0V  = WIN_TOP(0)  | WIN_DOWN(160);
	REG_BLDCNT = mode | BLEND_TOP_BG2;
	REG_BLDY   = cnt;
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetBlack(s32 cnt)
{
	FadeSetScr(BLEND_MODE_DARK, cnt);
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetWhite(s32 cnt)
{
	FadeSetScr(BLEND_MODE_LIGHT, cnt);
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetWin(void)
{
	REG_WIN0H  = WIN_LEFT(0)      | WIN_RIGHT(240);
	REG_WIN0V  = WIN_TOP(160-8*4) | WIN_DOWN(160-8);
	REG_BLDCNT = BLEND_MODE_DARK | BLEND_TOP_BG2;
	REG_BLDY   = 7;
}
