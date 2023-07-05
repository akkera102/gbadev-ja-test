#include "img.h"
#include "libmy/mode3.h"
#include "libmy/fade.h"
#include "file.h"
#include "txt.h"
#include "nv.h"

//---------------------------------------------------------------------------
ST_IMG Img;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgInit(void)
{
	_Memset(&Img, 0x00, sizeof(ST_IMG));

	Img.fadeMax = 8;

	Img.chr[0]  = 0xffff;
	Img.chr[1]  = 0xffff;
	Img.chr[2]  = 0xffff;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExec(void)
{
	if(Img.isTxt == true && NvIsSkip() == false && NvIsRestart() == false)
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

	Img.var1  = 0;
	Img.var2  = 0;
	Img.var3  = 0;
	Img.isTxt = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgExecBefore(void)
{
	switch(Img.before)
	{
	// 0x00
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
			// VCOUNT 160 -> 210
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
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetBgV(u8 no)
{
	TRACE("[ImgSetBgV %x]\n", no);

	Img.bg = no;
	Img.bgType = IMG_BG_VISUAL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetChr(u16 no, u8 pos)
{
	TRACE("[ImgSetChr no=%x pos=%x]\n", no, pos);

	_ASSERT(pos <= IMG_CHR_ALL);
	Img.chr[pos] = no;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetEffectBefore(u8 no)
{
	TRACE("[ImgSetEffectBefore %x]\n", no);

	Img.var1     = 0;
	Img.var2     = 0;
	Img.var3     = 0;
	Img.before   = no;
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

	Img.var4    = 0;
	Img.var5    = 0;
	Img.var6    = 0;
	Img.after   = no;
	Img.isAfter = true;
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
