#include "text.h"
#include "libmy/spr.h"
#include "libmy/bios.h"
#include "log.h"
#include "img.h"
#include "menu.h"


//---------------------------------------------------------------------------
ST_TEXT Text;


//---------------------------------------------------------------------------
EWRAM_CODE void TextInit(void)
{
	_Memset(&Text, 0x00, sizeof(ST_TEXT));

//	Text.waitMax = 1;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextExecChr(void)
{
	TextShowMsg();

	if(Text.waitMax == 0)
	{
		// �ꊇ�\��
		SprSetImgWhite();
		TextDrawWork();
		Text.drawCnt = Text.workCnt;
	}
	else
	{
		if(Text.waitCnt != 0)
		{
			Text.waitCnt--;
			return;
		}
		Text.waitCnt = Text.waitMax - 1;


		// �P�����\��
		SprSetImgWhite();
		TextDrawChr(Text.work[Text.drawCnt++]);
	}

	if(Text.drawCnt >= Text.workCnt)
	{
		Text.isChr = FALSE;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextExecCur(void)
{
	if(Text.curCnt != 0)
	{
		Text.curCnt--;
		return;
	}
	Text.curCnt = TEXT_CURSOR_WAIT_CNT;


	if(Text.isCurBlink == TRUE)
	{
		Text.isCurBlink = FALSE;

		SprHideCursor();
	}
	else
	{
		Text.isCurBlink = TRUE;

		SprMoveCursor(Text.x, Text.y);
		SprShowCursor();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextExecLog(void)
{
	Text.isChr = FALSE;

	if(Text.isRes == TRUE)
	{
		SprSetImgWhite();

		TextDrawFull(Text.buf);
		Text.isRes = FALSE;
		return;
	}

	TextDrawLog();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextExecMenu(void)
{
	Text.isChr = FALSE;

	if(Text.isRes == TRUE)
	{
		SprSetImgWhite();

		TextDrawFull(Text.buf);
		Text.isRes = FALSE;
		return;
	}

	TextDrawMenu();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextDrawChr(u16 code)
{
	_ASSERT(Text.x < TEXT_SCREEN_CX && Text.y < TEXT_SCREEN_CY);


	SprDrawDatChr(Text.x, Text.y, code);

	if(Text.isBuf == TRUE)
	{
		Text.buf[(Text.y * TEXT_SCREEN_CX) + Text.x] = code;
	}


	Text.x++;

	if(Text.x >= TEXT_SCREEN_CX)
	{
		Text.x = 0;
		Text.y++;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextDrawStr(char* p)
{
	u16 code;

	while(*p != '\0')
	{
		code  = *p++ << 8;
		code += *p++;

	TRACE("%x\n", code);

		TextDrawChr(code);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextDrawStrXy(u32 x, u32 y, char* p)
{
	u32 tx = Text.x;
	u32 ty = Text.y;

	Text.x = x;
	Text.y = y;

	TextDrawStr(p);

	Text.x = tx;
	Text.y = ty;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextDrawWork(void)
{
	u32 i;

	for(i=0; i<Text.workCnt; i++)
	{
		TextDrawChr(Text.work[i]);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextDrawLog(void)
{
	SprSetImgGray();

	u16* p = LogGetBuf();
	TextDrawFull(p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextDrawMenu(void)
{
	u32 reg = MenuGetReg();
	u32 sel = MenuGetSel();
	u32 i;

	Text.isBuf = FALSE;
	TextClearDat();

	// �^�C�g��
	SprSetImgWhite();
	TextDrawStrXy(2, 0, MenuGetSelStr(0));

	for(i=1; i<reg+1; i++)
	{
		if(i == sel+1)
		{
			SprSetImgWhite();
		}
		else
		{
			SprSetImgGray();
		}

		// �I����
		char* p = MenuGetSelStr(i);
		TextDrawStrXy(3, 1+i, p);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextDrawFull(u16* pStr)
{
	u32 x, y;

	for(y=0; y<TEXT_SCREEN_CY; y++)
	{
		for(x=0; x<TEXT_SCREEN_CX; x++)
		{
			SprDrawDatChr(x, y, *pStr++);
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextSetChr(void)
{
	Text.isChr = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextSetCur(bool is)
{
	Text.isCur      = is;
	Text.curCnt     = 0;
	Text.isCurBlink = FALSE;

	if(is == FALSE)
	{
		SprHideCursor();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextSetRes(void)
{
	Text.isRes = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextSetPage(void)
{
	Text.isPage = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextSetDraw(char* p)
{
	TextSetSiori(p);

	if(Text.isPage == TRUE)
	{
		// ���y�[�W
		Text.isPage = FALSE;

		LogAddBuf(Text.buf);
		TextClear();
		TextCalcStr(p);
	}
	else if(TextCalcStr(p) == TRUE)
	{
		// ��ʂɎ��܂�Ȃ��ꍇ�A������\��
		LogAddBuf(Text.buf);
		TextClear();
		TextCalcStr(p);
	}

	Text.waitCnt = 0;
	Text.drawCnt = 0;
	Text.isChr   = TRUE;
	Text.isBuf   = TRUE;
}
//---------------------------------------------------------------------------
// �֑���������
IWRAM_CODE bool TextCalcStr(char* p)
{
	u32 x = Text.x;
	u32 y = Text.y;
	u32 i = 0;
	u32 j = 0;
	u16 code;


	while(p[i] != '\0')
	{
		if(j >= TEXT_SCREEN_CX * TEXT_SCREEN_CY)
		{
			return TRUE;
		}

		if(y >= TEXT_SCREEN_CY)
		{
			return TRUE;
		}

		code  = p[i++] << 8;
		code += p[i++];

		// �s��
		if(x == 0 && j != 0 && TextIsChrFront(code) == TRUE)
		{
			Text.work[j+0] = Text.work[j-1];
			Text.work[j-1] = 0x0000;
			Text.work[j+1] = code;

			x = 2;
			j += 2;

			continue;
		}

		// �s��
		if(x == (TEXT_SCREEN_CX-1) && TextIsChrBack(code) == TRUE)
		{
			Text.work[j+0] = 0x0000;
			Text.work[j+1] = code;

			y++;
			x = 1;
			j += 2;

			continue;
		}

		// �ʏ�
		Text.work[j++] = code;
		x++;

		if(x >= TEXT_SCREEN_CX)
		{
			x = 0;
			y++;
		}
	}

	Text.workCnt = j;
	return FALSE;
}
//---------------------------------------------------------------------------
IWRAM_CODE bool TextIsChrFront(u16 code)
{
	switch(code)
	{
	case 0x82E1:	// ��
	case 0x82E3:	// ��
	case 0x82E5:	// ��
	case 0x82C1:	// ��
	case 0x8142:	// �B
	case 0x8141:	// �A
	case 0x8145:	// �E
	case 0x8163:	// �c
	case 0x8184:	// ��
	case 0x8178:	// �x
	case 0x8176:	// �v
	case 0x816A:	// �j
	case 0x816E:	// �n
	case 0x8148:	// �H
	case 0x8149:	// �I
	case 0x817C:	// �|
	case 0x815B:	// �[
	case 0x8383:	// ��
	case 0x8385:	// ��
	case 0x8387:	// ��
	case 0x8362:	// �b
	case 0x8396:	// ��
	case 0x829F:	// ��
	case 0x82A1:	// ��
	case 0x82A3:	// ��
	case 0x82A5:	// ��
	case 0x82A7:	// ��
	case 0x8340:	// �@
	case 0x8342:	// �B
	case 0x8344:	// �D
	case 0x8346:	// �F
	case 0x8348:	// �H
	case 0x8144:	// �D
	case 0x8160:	// �`
		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------
IWRAM_CODE bool TextIsChrBack(u16 code)
{
	switch(code)
	{
	case 0x8183:	// ��
	case 0x8177:	// �w
	case 0x8175:	// �u
	case 0x816D:	// �m
	case 0x8169:	// �i
		return TRUE;
	}

	return FALSE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextClear(void)
{
	TextClearBuf();
	TextClearDat();
	TextClearXY();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextClearBuf(void)
{
	BiosCpuSetFixClear(Text.buf, TEXT_SCREEN_CX * TEXT_SCREEN_CY * 2);
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextClearDat(void)
{
	SprClearDat();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextClearXY(void)
{
	Text.x = 0;
	Text.y = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextShowWindow(void)
{
	ImgShowWindow();
	TextShowMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextShowMsg(void)
{
	if(Text.isShow == TRUE)
	{
		return;
	}

	SprShowWindow();
	Text.isShow = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextHideWindow(void)
{
	ImgHideWindow();
	TextHideMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextHideMsg(void)
{
	SprHideWindow();
	Text.isShow = FALSE;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool TextIsChr(void)
{
	return Text.isChr;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool TextIsCur(void)
{
	return Text.isCur;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextSetSiori(char* p)
{
	u32 i;

	for(i=0; i<TEXT_SIORI_SIZE-1 && p[i] != '\0'; i++)
	{
		Text.siori[i] = p[i];
	}

	Text.siori[i] = '\0';
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextSetWaitMax(u32 num)
{
	Text.waitMax = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 TextGetWaitMax(void)
{
	return Text.waitMax;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextRestart(void)
{
	Text.waitCnt = 0;
	Text.drawCnt = 0;
	Text.isChr   = TRUE;
	Text.isBuf   = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void TextSetLf(void)
{
	if(Text.x == 0)
	{
		return;
	}

	Text.x = 0;
	Text.y++;
}
