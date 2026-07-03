#include "fade.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void FadeInit(void)
{
	REG_WININ  = WIN_0_BG2 | WIN_0_OBJ | WIN_0_SPE;
	REG_WINOUT = WIN_0_BG2 | WIN_0_OBJ;
}
//---------------------------------------------------------------------------
void FadeSetBlend(s32 mode, s32 bldy, s32 l, s32 r, s32 t, s32 d)
{
	REG_WIN0H  = WIN_LEFT(l) | WIN_RIGHT(r);
	REG_WIN0V  = WIN_TOP(t)  | WIN_DOWN(d);
	REG_BLDCNT = mode | BLEND_TOP_BG2;
	REG_BLDY   = bldy;
}
//---------------------------------------------------------------------------
void FadeSetBlack(s32 bldy)
{
	FadeSetBlend(BLEND_MODE_DARK, bldy, 0, 240, 0, 160);
}
//---------------------------------------------------------------------------
void FadeSetWhite(s32 bldy)
{
	FadeSetBlend(BLEND_MODE_LIGHT, bldy, 0, 240, 0, 160);
}
//---------------------------------------------------------------------------
void FadeSetMsg(s32 bldy)
{
	FadeSetBlend(BLEND_MODE_DARK, bldy, 8, 240-8, 160-4-12*6-2, 160-4);
}
