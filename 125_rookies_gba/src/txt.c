#include "txt.h"
#include "libmy/spr.h"
#include "libmy/mem.h"
#include "log.h"
#include "img.h"
#include "menu.h"
#include "nv.h"


//---------------------------------------------------------------------------
ST_TXT Txt;


//---------------------------------------------------------------------------
EWRAM_CODE void TxtInit(void)
{
	_Memset(&Txt, 0x00, sizeof(ST_TXT));

	SprHideMsg();
	SprClearDat();
}
//---------------------------------------------------------------------------
IWRAM_CODE void TxtExecNv(void)
{
	if(NvIsActSel() == true)
	{
		TxtExecNvSel();
	}
	else
	{
		TxtExecNvMsg();
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void TxtExecNvMsg(void)
{
	SprClearDat();

	Txt.isRes = true;
	s32 i;

	Txt.x = 0;
	Txt.y = 0;

	SprSetWhite();

	for(i=0; i<Txt.msgCnt; i++)
	{
		TxtDrawChr(Txt.msgBuf[i]);
	}

	Txt.isChr = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void TxtExecNvSel(void)
{
	SprClearDat();

	Txt.isRes = false;

	s32 reg = NvGetSelReg();
	s32 cnt = NvGetSelCnt();
	s32 i;

	Txt.x = 0;
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

		TxtDrawStr(NvGetSelStr(i));

		if(Txt.x != 0)
		{
			Txt.x = 0;
			Txt.y++;
		}
	}

	Txt.isChr = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void TxtExecCur(void)
{
	if(Txt.curWaitCnt != 0)
	{
		Txt.curWaitCnt--;
		return;
	}
	Txt.curWaitCnt = TXT_CURSOR_WAIT_CNT;


	if(Txt.isCurBlink == true)
	{
		SprHideCur();
		Txt.isCurBlink = false;
	}
	else
	{
		SprMoveCur(Txt.x, Txt.y);
		SprShowCur();
		Txt.isCurBlink = true;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void TxtExecLog(void)
{
	u16* p = LogGetBuf();

	SprSetGray();

	s32 x, y;

	for(y=0; y<TXT_SCREEN_CY; y++)
	{
		for(x=0; x<TXT_SCREEN_CX; x++)
		{
			SprDrawDatChr(x, y, *p++);
		}
	}

	Txt.isChr = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void TxtExecMenu(void)
{
	SprClearDat();
	Txt.isRes = false;

	s32 type = MenuGetType();
	s32 reg  = MenuGetReg();
	s32 sel  = MenuGetSel();
	s32 i, x, y;

	// タイトル
	SprSetWhite();
	TxtDrawStrXy(4, 0, MenuGetStrTitle());

	// 選択肢
	if(type == MENU_TYPE_TITLE)
	{
		x = 5;
		y = 8;
	}
	else
	{
		x = 3;
		y = 2;
	}

	for(i=0; i<reg; i++)
	{
		if(i == sel)
		{
			SprSetWhite();
		}
		else
		{
			SprSetGray();
		}

		TxtDrawStrXy(x, y+i, MenuGetStrSelect(i));
	}

	Txt.isChr = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtDrawChr(u16 code)
{
	_ASSERT(Txt.x < TXT_SCREEN_CX && Txt.y < TXT_SCREEN_CY);
	SprDrawDatChr(Txt.x, Txt.y, code);

	if(Txt.isRes == true)
	{
		Txt.resBuf[(Txt.y * TXT_SCREEN_CX) + Txt.x] = code;
	}

	Txt.x++;

	if(Txt.x >= TXT_SCREEN_CX)
	{
		Txt.x = 0;
		Txt.y++;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtDrawStr(char* p)
{
	u16 code;

	while(*p != '\0')
	{
		code  = *p++ << 8;
		code += *p++;

		TxtDrawChr(code);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtDrawStrXy(s32 x, s32 y, char* p)
{
	s32 tx = Txt.x;
	s32 ty = Txt.y;

	Txt.x = x;
	Txt.y = y;

	TxtDrawStr(p);

	Txt.x = tx;
	Txt.y = ty;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetChr(void)
{
	Txt.isChr = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetCur(bool is)
{
	if(is == false)
	{
		SprHideCur();
	}

	Txt.isCur = is;
	Txt.curWaitCnt = 0;
	Txt.isCurBlink = false;
}
//---------------------------------------------------------------------------
// 禁則文字処理
IWRAM_CODE void TxtSetMsg(char* p)
{
	u16 code;

	while(*p != '\0')
	{
		_ASSERT(Txt.msgCnt < TXT_SCREEN_CX * TXT_SCREEN_CY);

		code  = *p++ << 8;
		code += *p++;

		// 行頭
		if(Txt.x == 0 && Txt.msgCnt != 0 && TxtIsChrFront(code) == true)
		{
			Txt.msgBuf[Txt.msgCnt+0] = Txt.msgBuf[Txt.msgCnt-1];
			Txt.msgBuf[Txt.msgCnt-1] = 0x0000;
			Txt.msgBuf[Txt.msgCnt+1] = code;

			Txt.x = 2;
			Txt.msgCnt += 2;

			continue;
		}

		// 行末
		if(Txt.x == (TXT_SCREEN_CX-1) && TxtIsChrBack(code) == true)
		{
			Txt.msgBuf[Txt.msgCnt+0] = 0x0000;
			Txt.msgBuf[Txt.msgCnt+1] = code;

			Txt.y++;
			Txt.x = 1;
			Txt.msgCnt += 2;

			continue;
		}

		// 通常
		Txt.msgBuf[Txt.msgCnt++] = code;
		Txt.x++;

		if(Txt.x >= TXT_SCREEN_CX)
		{
			Txt.x = 0;
			Txt.y++;

			continue;
		}

		// 】名前表示
		if(code == 0x817A)
		{
			vs32 i;

			for(i=0; i<TXT_SCREEN_CX - Txt.x; i++)
			{
				Txt.msgBuf[Txt.msgCnt++] = 0x0000;
			}

			Txt.x = 0;
			Txt.y++;

			continue;
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetSiori(char* p)
{
	s32 i;

	for(i=0; i<TXT_SIORI_SIZE-1 && p[i] != '\0'; i++)
	{
		Txt.sioriBuf[i] = p[i];
	}

	Txt.sioriBuf[i] = '\0';
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetNum(s32 ans, s32 reg)
{
	SprSetNum(ans, reg);
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtWritePage(void)
{
	if(Txt.msgCnt == 0)
	{
		return;
	}

	LogAddBuf(Txt.resBuf);
	TxtClear();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtWriteSel(char* p)
{
	TxtClear();

	s32 i = 0;
	u16 code;

	while(p[i] != '\0')
	{
		code  = *p++ << 8;
		code += *p++;

		_ASSERT(Txt.x < TXT_SCREEN_CX && Txt.y < TXT_SCREEN_CY);
		Txt.resBuf[(Txt.y * TXT_SCREEN_CX) + Txt.x] = code;


		Txt.x++;

		if(Txt.x >= TXT_SCREEN_CX)
		{
			Txt.x = 0;
			Txt.y++;
		}
	}

	LogAddBuf(Txt.resBuf);
	TxtClear();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtClear(void)
{
	TRACE("[TxtClear]\n");
	TxtSetCur(false);

	Txt.msgCnt = 0;
	Txt.x = 0;
	Txt.y = 0;

	MemClear(Txt.resBuf, TXT_SCREEN_CX * TXT_SCREEN_CY * 2);
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtShowMsg(void)
{
	TRACE("[TxtShowMsg]\n");
	SprShowMsg();

	Txt.isMsg = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtHideMsg(void)
{
	TRACE("[TxtHideMsg]\n");
	TxtSetCur(false);

	SprHideMsg();
	SprClearDat();

	Txt.isMsg = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtShowNum(void)
{
	SprShowNum();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtHideNum(void)
{
	SprHideNum();
}
//---------------------------------------------------------------------------
IWRAM_CODE bool TxtIsChrFront(u16 code)
{
	switch(code)
	{
	case 0x82E1:	// ゃ
	case 0x82E3:	// ゅ
	case 0x82E5:	// ょ
	case 0x82C1:	// っ
	case 0x8142:	// 。
	case 0x8141:	// 、
	case 0x8145:	// ・
	case 0x8163:	// …
	case 0x8184:	// ＞
	case 0x8178:	// 』
	case 0x8176:	// 」
	case 0x816A:	// ）
	case 0x816E:	// ］
	case 0x8148:	// ？
	case 0x8149:	// ！
	case 0x817C:	// －
	case 0x815B:	// ー
	case 0x8383:	// ャ
	case 0x8385:	// ュ
	case 0x8387:	// ョ
	case 0x8362:	// ッ
	case 0x8396:	// ヶ
	case 0x829F:	// ぁ
	case 0x82A1:	// ぃ
	case 0x82A3:	// ぅ
	case 0x82A5:	// ぇ
	case 0x82A7:	// ぉ
	case 0x8340:	// ァ
	case 0x8342:	// ィ
	case 0x8344:	// ゥ
	case 0x8346:	// ェ
	case 0x8348:	// ォ
	case 0x8144:	// ．
	case 0x8160:	// ～
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------
IWRAM_CODE bool TxtIsChrBack(u16 code)
{
	switch(code)
	{
	case 0x8183:	// ＜
	case 0x8177:	// 『
	case 0x8175:	// 「
	case 0x816D:	// ［
	case 0x8169:	// （
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool TxtIsChr(void)
{
	return Txt.isChr;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool TxtIsCur(void)
{
	return Txt.isCur;
}
