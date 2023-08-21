#include "img.h"
#include "libmy/mode3.h"
#include "libmy/fade.h"
#include "file.h"
#include "txt.h"
#include "nv.h"
#include "sakura.h"

//---------------------------------------------------------------------------
ST_IMG Img;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgInit(void)
{
	_Memset(&Img, 0x00, sizeof(ST_IMG));

	ImgSetChrClr();
	Img.fadeMax = 8;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExec(void)
{
	if(Img.isTxt == true && NvIsSkip() == false && NvIsRestart() == false && Img.after != IMG_EFFECT_VIBRATE)
	{
		ImgExecTxt();

		return;
	}

	if(Img.isBefore == true)
	{
		ImgExecBefore();

		return;
	}

	if(Img.isAfter == true)
	{
		ImgExecAfter();

		return;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgExecTxt(void)
{
	if(Img.var1++ == 0)
	{
		TxtHideMsg();
	}

	if(Img.var2++ < 2)
	{
		return;
	}
	Img.var2 = 0;


	if(Img.var3++ < Img.fadeMax)
	{
		FadeSetBlack(Img.fadeMax - Img.var3);
		return;
	}

	ImgSetVarClr();
	Img.isTxt = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgExecBefore(void)
{
	switch(Img.before)
	{
	// 0x00
	case IMG_EFFECT_NONE:
		Img.isBefore = false;
		break;

	// 0x01
	case IMG_EFFECT_FADE_PALETTE:
		if(Img.var1++ < 2)
		{
			return;
		}
		Img.var1 = 0;

		if(Img.var2++ < 16)
		{
			FadeSetBlack(Img.var2);
			return;
		}

		if(Img.var3 == 0)
		{
			Mode3DrawFill(RGB5(0,0,0));
			Mode3SetDraw();

			Img.var3++;
			return;
		}

		if(SakuraIsEffect() == true)
		{
			FadeSetSpr(false);
			SakuraStop();
		}

		FadeSetBlack(0);
		Img.isBefore = false;
		break;

	// 0x07
	case IMG_EFFECT_WIPE_LTOR:
		if(Img.var1++ < 2)
		{
			return;
		}
		Img.var1 = 0;

		if(Img.var2 < 8)
		{
			// VCOUNT 160 -> 189
			// TRACE("WIPE_LTOR S:%d\n", REG_VCOUNT);
			Mode3DrawLineH(Img.var2++);
			// TRACE("WIPE_LTOR E:%d\n", REG_VCOUNT);
		}
		else
		{
			Img.isBefore = false;
		}
		break;

	// 0x08
	case IMG_EFFECT_NORMAL:
//		ImgDrawBg();
//		ImgDrawChr();
//		Mode3SetDraw();
		Img.isBefore = false;
		break;

	// 0x10
	case IMG_EFFECT_WHITE:
		if(Img.var1++ < 2)
		{
			return;
		}
		Img.var1 = 0;


		if(Img.var2++ < 16)
		{
			FadeSetWhite(Img.var2);
			return;
		}

		if(Img.var3 == 0)
		{
			Mode3DrawFill(RGB5(31,31,31));
			Mode3SetDraw();

			Img.var3++;
			return;
		}

		if(SakuraIsEffect() == true)
		{
			FadeSetSpr(false);
			SakuraStop();
		}

		FadeSetWhite(0);
		Img.isBefore = false;
		break;

	// 0x13
	case IMG_EFFECT_WIPE_TTOB:
		if(Img.var1++ < 2)
		{
			return;
		}
		Img.var1 = 0;

		if(Img.var2 < 34)
		{
			// VCOUNT 160 -> 194
			// TRACE("WIPE_TTOB S:%d\n", REG_VCOUNT);
			Mode3DrawWipeTtoB(Img.var2++);
			// TRACE("WIPE_TTOB E:%d\n", REG_VCOUNT);
			return;
		}

		Img.isBefore = false;
		break;

	// 0x17
	case IMG_EFFECT_SAKURA1_BLACK:
		FadeSetSpr(true);
		FadeSetBlack(16);
		SakuraRegAll(true);

		Img.isBefore = false;
		break;

	// 0x18
	case IMG_EFFECT_SAKURA1_WHITE:
		FadeSetSpr(true);
		FadeSetWhite(16);
		SakuraRegAll(true);

		Img.isBefore = false;
		break;

	// 0x19
	case IMG_EFFECT_SAKURA2:
		FadeSetSpr(true);
		SakuraRegAll(false);

		Img.isBefore = false;
		break;

	default:
		SystemError("[Err] ImgExecBefore Img.before=%x\n", Img.before);
		break;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgExecAfter(void)
{
	switch(Img.after)
	{
	// 0x00
	case IMG_EFFECT_NONE:
		Img.isAfter = false;
		break;

	// 0x01
	case IMG_EFFECT_FADE_PALETTE:
		if(Img.var4++ == 0)
		{
			FadeSetBlack(16);

			ImgDrawBg();
			ImgDrawChr();
			Mode3SetDraw();
			return;
		}

		if(Img.var5++ < 2)
		{
			return;
		}
		Img.var5 = 0;

		if(Img.var6++ < 16)
		{
			FadeSetBlack(16 - Img.var6);
			return;
		}

		Img.isAfter = false;
		break;

	// 0x02
	case IMG_EFFECT_FADE_MASK:
		if(Img.var4++ == 0)
		{
			ImgDrawBg();
			ImgDrawChr();
			return;
		}

		if(Img.var6++ < 3)
		{
			return;
		}
		Img.var6 = 0;

		if(Img.var5 < 8)
		{
			// VCOUNT 160 -> 220
			// TRACE("FADE_MASK S:%d\n", REG_VCOUNT);
			Mode3DrawFadeMask(Img.var5++);
			// TRACE("FADE_MASK E:%d\n", REG_VCOUNT);
			return;
		}

		Img.isAfter = false;
		break;

	// 0x07
	case IMG_EFFECT_WIPE_LTOR:
		if(Img.var4++ == 0)
		{
			ImgDrawBg();
			ImgDrawChr();
			return;
		}

		if(Img.var6++ < 2)
		{
			return;
		}
		Img.var6 = 0;

		if(Img.var5 < 8)
		{
			// VCOUNT 160 -> 220
			// TRACE("WIPE_LTOR S:%d\n", REG_VCOUNT);
			Mode3DrawCopyH(Img.var5++);
			// TRACE("WIPE_LTOR E:%d\n", REG_VCOUNT);
			return;
		}

		Img.isAfter = false;
		break;

	// 0x08
	case IMG_EFFECT_NORMAL:
		ImgDrawBg();
		ImgDrawChr();
		Mode3SetDraw();

		Img.isAfter = false;
		break;

	// 0x10
	case IMG_EFFECT_WHITE:
		if(Img.var4++ == 0)
		{
			FadeSetWhite(16);

			ImgDrawBg();
			ImgDrawChr();
			Mode3SetDraw();
			return;
		}

		if(Img.var5++ < 2)
		{
			return;
		}
		Img.var5 = 0;

		if(Img.var6++ < 16)
		{
			FadeSetWhite(16 - Img.var6);
			return;
		}

		Img.isAfter = false;
		break;

	// 0x11
	case IMG_EFFECT_TXT_ON:
		if(Img.var4++ < 2)
		{
			return;
		}
		Img.var4 = 0;

		if(Img.var5++ < Img.fadeMax)
		{
			FadeSetBlack(Img.var5);
			return;
		}

		Img.isTxt = true;
		Img.isAfter = false;
		break;

	// 0x12
	case IMG_EFFECT_TXT_ON_FAST:
		FadeSetBlack(Img.fadeMax);

		Img.isTxt = true;
		Img.isAfter = false;
		break;

	// 0x14
	case IMG_EFFECT_TITLE:

		Mode3DrawTitle(Img.var4);
		Img.var4++;

		if(Img.var4 > 48)
		{
			Img.isAfter = false;
		}
		break;

	// 0x15
	case IMG_EFFECT_OP_SCROLL1:
		FadeSetSpr(true);
		FadeSetWhite(16);
		TxtShowMsg();
		Img.isAfter = false;
		break;

	// 0x16
	case IMG_EFFECT_OP_SCROLL2:
		// mGBA 3, VBA 5
		if(Img.var4++ < 3)
		{
			return;
		}
		Img.var4 = 0;

		if(Img.var5 == 0)
		{
			// 青空と校舎
			ST_FILE_IMG_HEADER* p1 = (ST_FILE_IMG_HEADER*)FileGetBg(19);
			ST_FILE_IMG_HEADER* p2 = (ST_FILE_IMG_HEADER*)FileGetBg(17);

			Mode3DrawScroll((u16*)(p1 + 1), (u16*)(p2 + 1));
		}

		// 白フェードアウト
		if(Img.var5 <= 16)
		{
			FadeSetWhite(16 - Img.var5);
		}

		// テキスト消去
		if(Img.var5 == 80)
		{
			TxtClear();
		}

		Mode3Scroll(Img.var5);
		Img.var5++;

		if(Img.var5 > SCREEN_CY)
		{
			Img.isAfter = false;
		}
		break;

	// 0x20
	case IMG_EFFECT_VIBRATE:
		Mode3DrawVibrate(Img.var4++);

		if(Img.var4 > 7)
		{
			Img.isAfter = false;
		}
		break;

	// 0x21
	case IMG_EFFECT_TIME:
		if(Img.var6++ == 0)
		{
			ST_FILE_IMG_HEADER* p = (ST_FILE_IMG_HEADER*)FileGetTime(Img.time);
			s32 sy = (SCREEN_CY / 2) - (p->cy / 2);
			s32 sx = (SCREEN_CX / 2) - (p->cx / 2);

			Mode3DrawBlend(sx, sy, p->cx, p->cy, (u16*)(p + 1), FileGetTimeMask());
		}

		if(Img.var5++ < 3)
		{
			return;
		}
		Img.var5 = 0;

		if(Img.var4 < 8)
		{
			// VCOUNT 160 -> 220
			// TRACE("FADE_MASK S:%d\n", REG_VCOUNT);
			Mode3DrawFadeMask(Img.var4++);
			// TRACE("FADE_MASK E:%d\n", REG_VCOUNT);
			return;
		}

		if(Img.var4++ < 8+10)
		{
			return;
		}

		ImgSetEffectAfter(IMG_EFFECT_FADE_MASK);
		break;

	// 0x21
	case IMG_EFFECT_CALENDAR:
		if(Img.var4 == 0)
		{
			s32 sx, sy;

			// Bg
			ST_FILE_IMG_HEADER* pB = (ST_FILE_IMG_HEADER*)FileGetName("CBAK.img");
			Mode3DrawBg((u16*)(pB + 1));

			// Month
			ST_FILE_IMG_HEADER* pM = (ST_FILE_IMG_HEADER*)FileGetMonth(Img.mon);
			sx = (SCREEN_CX / 2) - (pM->cx / 2);
			sy = (SCREEN_CY / 2) - (pM->cy / 2);
			Mode3DrawCrop(sx, sy, pM->cx, pM->cy, (u16*)(pM + 1));

			// Week
			ST_FILE_IMG_HEADER* pW = (ST_FILE_IMG_HEADER*)FileGetWeek(Img.week);
			sx = (SCREEN_CX / 2) - (pW->cx / 2);
			sy = 114;
			Mode3DrawCrop(sx, sy, pW->cx, pW->cy, (u16*)(pW + 1));

			// Day
			Img.day = 88;
			if(Img.day < 10)
			{
				ST_FILE_IMG_HEADER* pD1 = (ST_FILE_IMG_HEADER*)FileGetDay(Img.day);
				sx = (SCREEN_CX / 2) - (pD1->cx / 2);
				sy = (SCREEN_CY / 2) - (pD1->cy / 2) + 8;
				Mode3DrawCrop(sx, sy, pD1->cx, pD1->cy, (u16*)(pD1 + 1));
			}
			else
			{
				ST_FILE_IMG_HEADER* pD1 = (ST_FILE_IMG_HEADER*)FileGetDay2(Div(Img.day, 10));
				ST_FILE_IMG_HEADER* pD2 = (ST_FILE_IMG_HEADER*)FileGetDay2(DivMod(Img.day, 10));
				sx = (SCREEN_CX / 2) - (pD1->cx / 2) - (pD1->cx / 2);
				sy = (SCREEN_CY / 2) - (pD1->cy / 2) + 8;
				Mode3DrawCrop(sx, sy, pD1->cx, pD1->cy, (u16*)(pD1 + 1));

				sx = (SCREEN_CX / 2) - (pD2->cx / 2) + (pD2->cx / 2);
				sy = (SCREEN_CY / 2) - (pD2->cy / 2) + 8;
				Mode3DrawCrop(sx, sy, pD2->cx, pD2->cy, (u16*)(pD2 + 1));
			}

			FadeSetBlack(16);
			Mode3SetDraw();

			Img.var4++;
			Img.var5 = 256;
			Img.var6 = 0;
		}

		if(Img.var5 >= 0)
		{
			Mode3DrawScaling(Img.var5);
			FadeSetBlack(Div(Img.var5, 16));
			Img.var5 -= 4;

			return;
		}

		if(Img.var4 < 60)
		{
			Img.var4++;
			return;
		}

		if(Img.var6 <= 256)
		{
			Mode3DrawScaling(Img.var6);
			FadeSetBlack(Div(Img.var6, 16));
			Img.var6 += 4;

			return;
		}

		if(Img.var4 < 61)
		{
			ImgDrawBg();
			ImgDrawChr();
			Mode3SetDraw();

			Img.var4++;
			return;
		}

		FadeSetBlack(0);
		Mode3DrawScaling(0);
		Img.isAfter = false;
		break;

	default:
		SystemError("[Err] ImgExecAfter Img.after=%x\n", Img.after);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawBg(void)
{
	TRACE("[ImgDrawBg]\n");

	if(Img.bg == 0)
	{
		Mode3DrawFill(RGB5(0,0,0));
		return;
	}

	if(Img.bg == 0xfe)
	{
		Mode3DrawFill(RGB5(31,31,31));
		return;
	}


	ST_FILE_IMG_HEADER* p;

	if(Img.bgType == IMG_BG_NORMAL)
	{
		p = (ST_FILE_IMG_HEADER*)FileGetBg(Img.bg);
	}
	else
	{
		p = (ST_FILE_IMG_HEADER*)FileGetVis(Img.bg);
	}

	_ASSERT(p->cx <= SCREEN_CX && p->cy <= SCREEN_CY);

	Mode3DrawBg((u16*)(p + 1));
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawChr(void)
{
	TRACE("[ImgDrawChr]\n");
	s32 i;

	for(i=0; i<3; i++)
	{
		if(Img.chr[i] == 0xffff)
		{
			continue;
		}

		ST_FILE_IMG_HEADER* p = (ST_FILE_IMG_HEADER*)FileGetChr(Img.chr[i]);

		s32 sy = SCREEN_CY - p->cy;
		s32 sx;

		if(i == IMG_CHR_LEFT)
		{
			sx = 10;
		}
		else if(i == IMG_CHR_RIGHT)
		{
			sx = SCREEN_CX - p->cx - 10;
		}
		else
		{
			sx = (SCREEN_CX / 2) - (p->cx / 2);
		}

		Mode3DrawBlend(sx, sy, p->cx, p->cy, (u16*)(p + 1), FileGetChrMask(Img.chr[i]));
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetBg(u8 no)
{
	TRACE("[ImgSetBg %x]\n", no);

	Img.bg = no;
	Img.bgType = IMG_BG_NORMAL;

	ImgSetChrClr();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetVis(u8 no)
{
	TRACE("[ImgSetVis %x]\n", no);

	Img.bg = no;
	Img.bgType = IMG_BG_VISUAL;

	ImgSetChrClr();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetChr(u16 no, u8 pos)
{
	TRACE("[ImgSetChr no=%x pos=%x]\n", no, pos);

	_ASSERT(pos < IMG_CHR_ALL);

	Img.chr[pos] = no;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetChrClr(void)
{
	Img.chr[0] = 0xffff;
	Img.chr[1] = 0xffff;
	Img.chr[2] = 0xffff;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetVarClr(void)
{
	Img.var1 = 0;
	Img.var2 = 0;
	Img.var3 = 0;
	Img.var4 = 0;
	Img.var5 = 0;
	Img.var6 = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetEffectBefore(u8 no)
{
	TRACE("[ImgSetEffectBefore %x]\n", no);

	ImgSetVarClr();

	Img.before = no;
	Img.isBefore = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetEffectAfter(u8 no)
{
	if(Img.isTxt == true && no == IMG_EFFECT_TXT_ON)
	{
		return;
	}

	TRACE("[ImgSetEffectAfter %x]\n", no);

	ImgSetVarClr();

	Img.after = no;
	Img.isAfter = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetEffectTime(u8 num)
{
	Img.time = num;

	ImgSetEffectAfter(IMG_EFFECT_TIME);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetEffectCal(u8 mon, u8 day, u8 week)
{
	Img.mon  = mon;
	Img.day  = day;
	Img.week = week;

	ImgSetEffectAfter(IMG_EFFECT_CALENDAR);
}
//---------------------------------------------------------------------------
EWRAM_CODE u16 ImgGetChr(u8 no)
{
	_ASSERT(no < 3);

	return Img.chr[no];
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgShowWindow(void)
{
	FadeSetBlack(Img.fadeMax);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgHideWindow(void)
{
	FadeSetBlack(0);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool ImgIsEffect(void)
{
	return (Img.isBefore || Img.isAfter);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetFadeMax(u32 num)
{
	Img.fadeMax = num;

	ImgShowWindow();
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 ImgGetFadeMax(void)
{
	return Img.fadeMax;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgRestart(void)
{
	Img.isTxt = false;

	ImgSetEffectAfter(IMG_EFFECT_TXT_ON);
}
