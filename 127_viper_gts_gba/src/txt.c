#include "txt.h"
#include "libmy/spr.h"
#include "menu.h"
#include "nv.h"

//---------------------------------------------------------------------------
ST_TXT Txt;


//---------------------------------------------------------------------------
EWRAM_CODE void TxtInit(void)
{
	_Memset(&Txt, 0x00, sizeof(ST_TXT));

	SprHideCur();
	SprHideMsg();
	SprClearMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtExecMsg(void)
{
	SprSetWhite();

	// バッファメッセージ復帰 or スクリプト内メッセージ表示
	if(Txt.isBuf == true)
	{
		TxtDrawBuf();
		Txt.isBuf = false;
	}
	else
	{
		TxtDrawStr(Txt.p, true);
	}

	Txt.isMsg = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtExecSel(void)
{
	SprClearMsg();

	s32 reg = NvGetSelReg();
	s32 cnt = NvGetSelCnt();
	s32 i;

	Txt.x = 1;
	Txt.y = 0;

	for(i=0; i<reg; i++)
	{
		if(i == cnt)
		{
			SprSetWhite();
		}
		else
		{
			SprSetGray();
		}

		TxtDrawStr(NvGetSelStr(i), false);

		Txt.x = 1;
		Txt.y++;
	}

	Txt.isMsg = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtExecCur(void)
{
	if(Txt.wait != 0)
	{
		Txt.wait--;

		return;
	}
	Txt.wait = Txt.blink;


	SprShowCur(Txt.spr + Txt.cnt);
	Txt.cnt++;

	if(Txt.cnt >= Txt.max)
	{
		Txt.cnt = 0;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtExecMenu(void)
{
	SprClearMsg();

	s32 reg  = MenuGetReg();
	s32 cnt  = MenuGetCnt();
	s32 i;

	Txt.x = 1;
	Txt.y = 0;

	for(i=0; i<reg; i++)
	{
		if(i == cnt)
		{
			SprSetWhite();
		}
		else
		{
			SprSetGray();
		}

		TxtDrawStr(MenuGetStr(i), false);

		Txt.x = 1;
		Txt.y++;
	}

	Txt.isMsg = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtDrawChr(u16 code, bool isBuf)
{
	_ASSERT(Txt.x < TXT_SCREEN_CX && Txt.y < TXT_SCREEN_CY);


	SprDrawMsg(Txt.x, Txt.y, code);

	if(isBuf == true)
	{
		Txt.buf[Txt.y * TXT_SCREEN_CX + Txt.x] = code;
	}

	Txt.x++;

	if(Txt.x >= TXT_SCREEN_CX)
	{
		Txt.x = 0;
		Txt.y++;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtDrawStr(char* p, bool isBuf)
{
	_ASSERT(p != NULL);

	u16 code;

	while(*p != '\0')
	{
		code  = *p++ << 8;
		code += *p++;

		TxtDrawChr(code, isBuf);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtDrawBuf(void)
{
	Txt.x = 0;
	Txt.y = 0;

	s32 i;

	for(i=0; i<TXT_SCREEN_SIZE; i++)
	{
		TxtDrawChr(Txt.buf[i], false);
	}

	// テキスト描画位置の復旧
	Txt.x = Txt.x2;
	Txt.y = Txt.y2;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetStr(char* p)
{
	Txt.p = p;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetMsg(void)
{
	Txt.isMsg = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetBuf(void)
{
	Txt.isBuf = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetCur(void)
{
	Txt.cnt  = 0;
	Txt.wait = 0;
	Txt.isCur = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetCurKey(void)
{
	Txt.spr   = 0;
	Txt.cnt   = 0;
	Txt.max   = 2;
	Txt.wait  = 0;
	Txt.blink = 30;
	Txt.isCur = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetCurScr(void)
{
	Txt.spr   = 2;
	Txt.cnt   = 0;
	Txt.max   = 7;
	Txt.wait  = 0;
	Txt.blink = 10;
	Txt.isCur = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetCurPcm(void)
{
	Txt.spr   = 9;
	Txt.cnt   = 0;
	Txt.max   = 1;
	Txt.wait  = 0;
	Txt.blink = 60;
	Txt.isCur = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetXy2(void)
{
	Txt.x2 = Txt.x;
	Txt.y2 = Txt.y;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtClr(void)
{
	TxtClrMsg();
	TxtClrCur();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtClrMsg(void)
{
	SprHideMsg();
	SprClearMsg();

	Txt.x = 0;
	Txt.y = 0;
	Txt.p = NULL;

	_Memset(Txt.buf, 0x00, sizeof(Txt.buf));
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtClrXy(void)
{
	Txt.x = 0;
	Txt.y = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtClrCur(void)
{
	SprHideCur();

	Txt.isCur = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtShowMsg(void)
{
	SprShowMsg();

	TxtSetMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtShowCur(void)
{
	TxtSetCur();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtHideMsg(void)
{
	SprHideMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtHideCur(void)
{
	SprHideCur();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool TxtIsMsg(void)
{
	return Txt.isMsg;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool TxtIsCur(void)
{
	return Txt.isCur;
}
