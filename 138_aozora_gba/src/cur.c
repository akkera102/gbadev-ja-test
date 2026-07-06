#include "cur.h"
#include "libmy/spr.h"
#include "txt.h"
#include "nv.h"

//---------------------------------------------------------------------------
ST_CUR Cur;


//---------------------------------------------------------------------------
void CurInit(void)
{
	_Memset(&Cur, 0x00, sizeof(ST_CUR));
}
//---------------------------------------------------------------------------
void CurExec(void)
{
	if(Cur.wait != 0)
	{
		Cur.wait--;

		return;
	}

	Cur.wait = Cur.blink;


	CurShow();

	Cur.cnt++;

	if(Cur.cnt >= Cur.max)
	{
		Cur.cnt = 0;
	}
}
//---------------------------------------------------------------------------
void CurSetExec(void)
{
	Cur.cnt    = 0;
	Cur.wait   = 0;
	Cur.isExec = true;
}
//---------------------------------------------------------------------------
void CurSetPage(void)
{
	Cur.spr   = (NvIsRead() == true) ? 8 : 0;
	Cur.max   = 2;
	Cur.blink = 30;
}
//---------------------------------------------------------------------------
void CurShow(void)
{
	s32 x = TxtGetX();
	s32 y = TxtGetY();

	SprMoveCur(x, y);
	SprShowCur(Cur.spr + Cur.cnt * 4);
}
//---------------------------------------------------------------------------
void CurHide(void)
{
	SprHideCur();

	Cur.isExec = false;
}
//---------------------------------------------------------------------------
bool CurIsExec(void)
{
	return Cur.isExec;
}
