#include "txt.h"
#include "libmy/spr.h"
#include "libmy/mem.arm.h"
#include "img.h"
#include "log.h"
#include "menu.h"
#include "nv.h"


//---------------------------------------------------------------------------
ST_TXT Txt;


//---------------------------------------------------------------------------
void TxtInit(void)
{
	_Memset(&Txt, 0x00, sizeof(ST_TXT));

	Txt.read = 1;
}
//---------------------------------------------------------------------------
void TxtExecNv(void)
{
	// VCOUNT 160 -> 216

	if(NvIsReadSeen() == true)
	{
		SprSetRead();
	}
	else
	{
		SprSetBase();
	}

	s32 cnt = 0;
	s32 x, y;

	for(y=0; y<SPR_MAX_TXT_CY; y++)
	{
		for(x=0; x<SPR_MAX_TXT_CX; x++)
		{
			SprVramSjis(x, y, Txt.buf[cnt++]);
		}
	}

	Txt.isExec = false;
}
//---------------------------------------------------------------------------
void TxtExecSel(void)
{
	TxtClrSpr();
	SprSetBase();

	s32 reg = NvGetSelReg();
	s32 cnt = NvGetSelCnt();
	s32 i;

	for(i=0; i<reg; i++)
	{
		if(i == cnt)
		{
			SprSetBase();
		}
		else
		{
			SprSetGray();
		}

		TxtDrawStr(0, i, NvGetSelStr(i));
	}

	Txt.isExec = false;
}
//---------------------------------------------------------------------------
void TxtExecLog(void)
{
	SprSetGray();

	u16* p = LogGetBuf();
	s32 x, y;

	for(y=0; y<SPR_MAX_TXT_CY; y++)
	{
		for(x=0; x<SPR_MAX_TXT_CX; x++)
		{
			SprVramSjis(x, y, *p++);
		}
	}

	Txt.isExec = false;
}
//---------------------------------------------------------------------------
void TxtExecMenu(void)
{
	TxtClrSpr();
	SprSetBase();

	TxtDrawStr(0, 0, MenuGetStrTitle());

	s32 reg = MenuGetReg();
	s32 sel = MenuGetSel();
	s32 i;

	for(i=0; i<reg; i++)
	{
		if(i == sel)
		{
			SprSetBase();
		}
		else
		{
			SprSetGray();
		}

		TxtDrawStr(1, 1+i, MenuGetStrSel(i));
	}

	Txt.isExec = false;
}
//---------------------------------------------------------------------------
void TxtDrawStr(s32 x, s32 y, char* p)
{
	while(*p != '\0' && *p != ',')
	{
		u16 c;

		c  = *p++ << 8;
		c += *p++;

		_ASSERT(x < SPR_MAX_TXT_CX);
		_ASSERT(y < SPR_MAX_TXT_CY);

		SprVramSjis(x++, y, c);
	}
}
//---------------------------------------------------------------------------
void TxtClrBuf(void)
{
//	TRACE("[TxtClrBuf]\n");

	Txt.x = 0;
	Txt.y = 0;

	MemClear(Txt.buf, sizeof(Txt.buf));
}
//---------------------------------------------------------------------------
void TxtClrSpr(void)
{
	SprClearDat();
}
//---------------------------------------------------------------------------
void TxtAddBuf(char* s)
{
	TRACE("%s\n", s);

	if(Txt.x != 0)
	{
		Txt.y++;
		Txt.x = 0;
	}

	while(*s != '\0')
	{
		u16 c;

		c  = *s++ << 8;
		c += *s++;

		_ASSERT(Txt.x < SPR_MAX_TXT_CX);
		_ASSERT(Txt.y < SPR_MAX_TXT_CY);

		Txt.buf[Txt.y * SPR_MAX_TXT_CX + Txt.x++] = c;
	}
}
//---------------------------------------------------------------------------
void TxtAddLog(void)
{
	LogAddBuf(Txt.buf);
}
//---------------------------------------------------------------------------
void TxtAddLog2(char* p)
{
	TxtClrBuf();

	while(*p != '\0' && *p != ',')
	{
		u16 c;

		c  = *p++ << 8;
		c += *p++;

		_ASSERT(Txt.x < SPR_MAX_TXT_CX);

		Txt.buf[Txt.x++] = c;
	}

	LogAddBuf(Txt.buf);
}
//---------------------------------------------------------------------------
void TxtSetTitle(char* p)
{
	_Strncpy(Txt.title, p, TXT_MAX_TITLE_LEN-1);

	Txt.title[TXT_MAX_TITLE_LEN-1] = '\0';
}
//---------------------------------------------------------------------------
void TxtSetExec(void)
{
	Txt.isExec = true;
}
//---------------------------------------------------------------------------
void TxtSetBase(s32 no)
{
	SprSetBaseCol(no);
	Txt.base = no;
}
//---------------------------------------------------------------------------
void TxtSetRead(s32 no)
{
	SprSetReadCol(no);
	Txt.read = no;
}
//---------------------------------------------------------------------------
s32 TxtGetBase(void)
{
	return Txt.base;
}
//---------------------------------------------------------------------------
s32 TxtGetRead(void)
{
	return Txt.read;
}
//---------------------------------------------------------------------------
s32 TxtGetX(void)
{
	return Txt.x;
}
//---------------------------------------------------------------------------
s32 TxtGetY(void)
{
	return Txt.y;
}
//---------------------------------------------------------------------------
void TxtShow(void)
{
	SprShowMsg();
}
//---------------------------------------------------------------------------
void TxtHide(void)
{
	SprHideMsg();
}
//---------------------------------------------------------------------------
void TxtLoad(void)
{
	SprSetBaseCol(Txt.base);
	SprSetReadCol(Txt.read);
}
//---------------------------------------------------------------------------
bool TxtIsExec(void)
{
	return Txt.isExec;
}
