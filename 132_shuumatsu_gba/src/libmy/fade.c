#include "fade.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void FadeInit(void)
{
	REG_WININ  = WIN_0_BG2 | WIN_0_OBJ | WIN_0_SPE;
	REG_WINOUT = WIN_0_BG2 | WIN_0_OBJ;
}
//---------------------------------------------------------------------------
void FadeSetBlend(s32 mode, s32 cnt)
{
	REG_WIN0H  = WIN_LEFT(0) | WIN_RIGHT(240);
	REG_WIN0V  = WIN_TOP(0)  | WIN_DOWN(160);
	REG_BLDCNT = mode | BLEND_TOP_BG2;
	REG_BLDY   = cnt;
}
//---------------------------------------------------------------------------
void FadeSetBlack(s32 cnt)
{
	FadeSetBlend(BLEND_MODE_DARK, cnt);
}
//---------------------------------------------------------------------------
void FadeSetWhite(s32 cnt)
{
	FadeSetBlend(BLEND_MODE_LIGHT, cnt);
}
