#include "txt.h"
#include "libmy/spr.h"
#include "libmy/mem.h"
#include "log.h"
#include "img.h"
#include "menu.h"


//---------------------------------------------------------------------------
ST_TXT Txt;


//---------------------------------------------------------------------------
EWRAM_CODE void TxtInit(void)
{
	_Memset(&Txt, 0x00, sizeof(ST_TXT));

	SprHideWindow();
	SprClearDat();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtExecChr(void)
{
	if(Txt.isRes == true)
	{
		SprSetImgWhite();
		TxtDrawFull(Txt.buf);

		Txt.isRes = false;
		Txt.isChr = false;
		return;
	}

	TxtShowMsg();

	if(Txt.waitMax == 0)
	{
		// 一括表示
		SprSetImgWhite();
		TxtDrawWork();
		Txt.drawCnt = Txt.workCnt;
	}
	else
	{
		if(Txt.waitCnt != 0)
		{
			Txt.waitCnt--;
			return;
		}
		Txt.waitCnt = Txt.waitMax - 1;


		// １文字表示
		SprSetImgWhite();
		TxtDrawChr(Txt.work[Txt.drawCnt++]);
	}

	if(Txt.drawCnt >= Txt.workCnt)
	{
		Txt.isChr = false;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtExecCur(void)
{
	if(Txt.curCnt != 0)
	{
		Txt.curCnt--;
		return;
	}
	Txt.curCnt = TXT_CURSOR_WAIT_CNT;


	if(Txt.isCurBlink == true)
	{
		Txt.isCurBlink = false;

		SprHideCursor();
	}
	else
	{
		Txt.isCurBlink = true;

		SprMoveCursor(Txt.x, Txt.y);
		SprShowCursor();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtExecLog(void)
{
	Txt.isChr = false;

	SprSetImgGray();

	u16* p = LogGetBuf();
	TxtDrawFull(p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtExecMenu(void)
{
	Txt.isChr = false;

	u32 reg = MenuGetReg();
	u32 sel = MenuGetSel();
	u32 i, x, y;

	if(MenuGetType() == MENU_TYPE_TITLE)
	{
		x = 2;
		y = 6;
	}
	else
	{
		x = 0;
		y = 0;
	}

	Txt.isBuf = false;
	TxtClearDat();

	// メニュー名
	SprSetImgWhite();
	TxtDrawStrXy(4, 0, MenuGetStrTitle());

	// 選択肢
	for(i=0; i<reg; i++)
	{
		if(i == sel)
		{
			SprSetImgWhite();
		}
		else
		{
			SprSetImgGray();
		}

		char* p = MenuGetStrSelect(i);
		TxtDrawStrXy(3+x, 2+y+i, p);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtDrawChr(u16 code)
{
	_ASSERT(Txt.x < TXT_SCREEN_CX && Txt.y < TXT_SCREEN_CY);


	SprDrawDatChr(Txt.x, Txt.y, code);

	if(Txt.isBuf == true)
	{
		Txt.buf[(Txt.y * TXT_SCREEN_CX) + Txt.x] = code;
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
EWRAM_CODE void TxtDrawStrXy(u32 x, u32 y, char* p)
{
	u32 tx = Txt.x;
	u32 ty = Txt.y;

	Txt.x = x;
	Txt.y = y;

	TxtDrawStr(p);

	Txt.x = tx;
	Txt.y = ty;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtDrawWork(void)
{
	s32 i;

	for(i=0; i<Txt.workCnt; i++)
	{
		TxtDrawChr(Txt.work[i]);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtDrawFull(u16* pStr)
{
	u32 x, y;

	for(y=0; y<TXT_SCREEN_CY; y++)
	{
		for(x=0; x<TXT_SCREEN_CX; x++)
		{
			SprDrawDatChr(x, y, *pStr++);
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetChr(void)
{
	Txt.isChr = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetCur(bool is)
{
	Txt.isCur      = is;
	Txt.curCnt     = 0;
	Txt.isCurBlink = false;

	if(is == false)
	{
		SprHideCursor();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetRes(void)
{
	Txt.isRes = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetPage(void)
{
	Txt.isPage = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetPageNew(void)
{
	LogAddBuf(Txt.buf);
	TxtClear();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetDraw(char* p)
{
	TxtSetSiori(p);

	if(Txt.isPage == true)
	{
		// 改ページ
		Txt.isPage = false;

		LogAddBuf(Txt.buf);

		TxtClear();
		TxtCalcStr(p);
	}
	else if(TxtCalcStr(p) == true)
	{
		// 画面に収まらない場合、消去後表示
		LogAddBuf(Txt.buf);

		TxtClear();
		TxtCalcStr(p);
	}

	Txt.waitCnt = 0;
	Txt.drawCnt = 0;
	Txt.isChr   = true;
	Txt.isBuf   = true;
}
//---------------------------------------------------------------------------
// 禁則文字処理
IWRAM_CODE bool TxtCalcStr(char* p)
{
	u32 x = Txt.x;
	u32 y = Txt.y;
	u32 i = 0;
	u32 j = 0;
	u16 code;


	while(p[i] != '\0')
	{
		if(j >= TXT_SCREEN_CX * TXT_SCREEN_CY)
		{
			return true;
		}

		if(y >= TXT_SCREEN_CY)
		{
			return true;
		}

		code  = p[i++] << 8;
		code += p[i++];

		// 行頭
		if(x == 0 && j != 0 && TxtIsChrFront(code) == true)
		{
			Txt.work[j+0] = Txt.work[j-1];
			Txt.work[j-1] = 0x0000;
			Txt.work[j+1] = code;

			x = 2;
			j += 2;

			continue;
		}

		// 行末
		if(x == (TXT_SCREEN_CX-1) && TxtIsChrBack(code) == true)
		{
			Txt.work[j+0] = 0x0000;
			Txt.work[j+1] = code;

			y++;
			x = 1;
			j += 2;

			continue;
		}

		// 通常
		Txt.work[j++] = code;
		x++;

		if(x >= TXT_SCREEN_CX)
		{
			x = 0;
			y++;
		}
	}

	Txt.workCnt = j;
	return false;
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
EWRAM_CODE void TxtClear(void)
{
	TxtClearBuf();
	TxtClearDat();
	TxtClearXY();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtClearBuf(void)
{
	MemClear(Txt.buf, TXT_SCREEN_CX * TXT_SCREEN_CY * 2);
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtClearDat(void)
{
	SprClearDat();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtClearXY(void)
{
	Txt.x = 0;
	Txt.y = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtShowWindow(void)
{
	ImgShowWindow();
	TxtShowMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtShowMsg(void)
{
	if(Txt.isShow == true)
	{
		return;
	}

	SprShowWindow();
	Txt.isShow = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtHideWindow(void)
{
	ImgHideWindow();
	TxtHideMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtHideMsg(void)
{
	SprHideWindow();
	Txt.isShow = false;
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
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetSiori(char* p)
{
	u32 i;

	for(i=0; i<TXT_SIORI_SIZE-1 && p[i] != '\0'; i++)
	{
		Txt.siori[i] = p[i];
	}

	Txt.siori[i] = '\0';
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetWaitMax(u32 num)
{
	Txt.waitMax = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 TxtGetWaitMax(void)
{
	return Txt.waitMax;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtRestart(void)
{
	TxtSetChr();
	TxtSetRes();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetLf(void)
{
	if(Txt.x == 0)
	{
		return;
	}

	Txt.x = 0;
	Txt.y++;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TxtSetBuf(bool is)
{
	Txt.isBuf = is;
}
