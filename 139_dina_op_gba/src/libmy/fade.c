#include "fade.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void FadeInit(void)
{
	while(REG_VCOUNT == 159) {};
	while(REG_VCOUNT != 159) {};

	REG_DISPCNT = MODE_4 | BG2_ON;

	FadeSetWhite(16);
}
//---------------------------------------------------------------------------
void FadeSetScr(s32 mode, s32 cnt)
{
	REG_BLDCNT = mode | BLEND_TOP_BG2 | BLEND_TOP_BD;
	REG_BLDY   = cnt;
}
//---------------------------------------------------------------------------
void FadeSetBlack(s32 cnt)
{
	FadeSetScr(BLEND_MODE_DARK, cnt);
}
//---------------------------------------------------------------------------
void FadeSetWhite(s32 cnt)
{
	FadeSetScr(BLEND_MODE_LIGHT, cnt);
}
