#include "fade.h"


//---------------------------------------------------------------------------
ST_FADE Fade;


//---------------------------------------------------------------------------
EWRAM_CODE void FadeInit(void)
{
	_Memset(&Fade, 0x00, sizeof(ST_FADE));
}
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetMode(u32 mode, u32 cnt)
{
	if(Fade.isSpr == true)
	{
		REG_BLDCNT = (mode | BLEND_TOP_BG2 | BLEND_TOP_OBJ);
	}
	else
	{
		REG_BLDCNT = (mode | BLEND_TOP_BG2);
	}

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
//---------------------------------------------------------------------------
EWRAM_CODE void FadeSetSpr(bool is)
{
	Fade.isSpr = is;
}
