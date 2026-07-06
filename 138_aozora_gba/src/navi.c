#include "navi.h"
#include "libmy/spr.h"


//---------------------------------------------------------------------------
ST_NAVI Navi;


//---------------------------------------------------------------------------
void NaviInit(void)
{
	_Memset(&Navi, 0x00, sizeof(ST_NAVI));
}
//---------------------------------------------------------------------------
void NaviExec(void)
{
	NaviShow();

	Navi.isExec = false;
}
//---------------------------------------------------------------------------
void NaviSetExec(s32 sel)
{
	Navi.sel = sel;
	Navi.isExec = true;
}
//---------------------------------------------------------------------------
void NaviShow(void)
{
	SprMoveNavi(Navi.sel);

	SprShowNavi();
}
//---------------------------------------------------------------------------
void NaviHide(void)
{
	SprHideNavi();
}
//---------------------------------------------------------------------------
bool NaviIsExec(void)
{
	return Navi.isExec;
}
