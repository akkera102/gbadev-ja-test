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
void CurSetLf(void)
{
	Cur.spr   =  0;
	Cur.max   =  3;
	Cur.blink = 10;
}
//---------------------------------------------------------------------------
void CurSetPage(void)
{
	Cur.spr   = 12;
	Cur.max   =  4;
	Cur.blink = 10;
}
//---------------------------------------------------------------------------
void CurSetExec(void)
{
	Cur.cnt    = 0;
	Cur.wait   = 0;
	Cur.isExec = true;
}
//---------------------------------------------------------------------------
void CurShow(void)
{
	s32 x = TxtGetX();
	s32 y = TxtGetY();
	s32 i = 0;

	// Šù“Ç
	if(NvIsReadValid() == true)
	{
		i = 1;
	}

	SprMoveCur(x, y);
	SprShowCur(Cur.spr + Cur.cnt * 4, i);
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
