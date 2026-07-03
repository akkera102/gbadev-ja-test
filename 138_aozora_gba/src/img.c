#include "img.h"
#include "libmy/mode3.arm.h"
#include "libmy/fade.h"
#include "file.h"
#include "seen.h"
#include "txt.h"

//---------------------------------------------------------------------------
ST_IMG Img;


//---------------------------------------------------------------------------
void ImgInit(void)
{
	_Memset(&Img, 0x00, sizeof(ST_IMG));

	Img.fade = IMG_DEF_FADE_CNT;
}
//---------------------------------------------------------------------------
void ImgExec(void)
{
	if(Img.isClr == true)
	{
		ImgExecSub();
	}

	switch(Img.eff)
	{
	case IMG_EFFECT_NORMAL:
		ImgExecNormal();
		break;

	case IMG_EFFECT_ZIRI:
		ImgExecZiri();
		break;

	case IMG_EFFECT_ALPHA:
		ImgExecAlpha();
		break;

	case IMG_EFFECT_BLACK_FLASH:
		ImgExecBlackFlash();
		break;

	case IMG_EFFECT_WHITE_FLASH:
		ImgExecWhiteFlash();
		break;

	case IMG_EFFECT_BLACK_IN:
		ImgExecBlackIn();
		break;

	case IMG_EFFECT_WHITE_IN:
		ImgExecWhiteIn();
		break;

	case IMG_EFFECT_BLACK_OUT:
		ImgExecBlackOut();
		break;

	case IMG_EFFECT_WHITE_OUT:
		ImgExecWhiteOut();
		break;

	case IMG_EFFECT_SET_MSG:
		ImgExecSetMsg();
		break;

	case IMG_EFFECT_CLR_MSG:
		ImgExecClrMsg();
		break;

	case IMG_EFFECT_LOAD:
		ImgExecLoad();
		break;

	default:
		SystemError("[Err] ImgExec eff=%x\n", Img.eff);
		break;
	}
}
//---------------------------------------------------------------------------
void ImgExecSub(void)
{
	FadeSetMsg(0);

	TxtHide();
	TxtClrSpr();

	Img.isMsg = false;
	Img.isClr = false;
}
//---------------------------------------------------------------------------
void ImgExecNormal(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Img.step++;
		return;
	}

	Mode3VramEffCopy();

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgExecZiri(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		// VCOUNT 160 -> 213
		Mode3VramEffZiri(Img.var++);

		if(Img.var >= 8)
		{
			// 1ÉtÉåêﬂñÒ
			goto End;
		}

		return;
	}

End:
	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgExecAlpha(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		// VCOUNT 160 -> 208
//		TRACE("S:%d\n", REG_VCOUNT);
		Mode3VramEffAlpha(Img.var++);
//		TRACE("E:%d\n", REG_VCOUNT);

		if(Img.var >= 8)
		{
			// 1ÉtÉåêﬂñÒ
			goto End;
		}

		return;
	}

End:
	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgExecBlackFlash(void)
{
	if(Img.step == 0)
	{
		FadeSetBlack(16);

		Img.step++;
		return;
	}

	// wait
	if(Img.step < 15)
	{
		Img.step++;
		return;
	}

	FadeSetBlack(0);

	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgExecWhiteFlash(void)
{
	if(Img.step == 0)
	{
		FadeSetWhite(16);

		Img.step++;
		return;
	}

	// wait
	if(Img.step < 15)
	{
		Img.step++;
		return;
	}

	FadeSetWhite(0);

	Img.isExec = false;
}
//---------------------------------------------------------------------------
// îwåiÅ®çï
void ImgExecBlackIn(void)
{
	if(Img.step == 0)
	{
		ImgSetBg(0);
		ImgSetChr(0);

		ImgDrawBg();
		ImgDrawChr();

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		Img.var++;
		FadeSetBlack(Img.var);

		if(Img.var >= 16)
		{
			Img.step++;
		}
		return;
	}

	if(Img.step == 2)
	{
		FadeSetBlack(0);
		Mode3VramEffCopy();

		Img.step++;
		return;
	}

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
// îwåiÅ®îí
void ImgExecWhiteIn(void)
{
	if(Img.step == 0)
	{
		ImgSetBg(900);
		ImgSetChr(0);

		ImgDrawBg();
		ImgDrawChr();

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		Img.var++;
		FadeSetWhite(Img.var);

		if(Img.var >= 16)
		{
			Img.step++;
		}
		return;
	}

	if(Img.step == 2)
	{
		FadeSetWhite(0);
		Mode3VramEffCopy();

		Img.step++;
		return;
	}

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
// çïÅ®îwåi
void ImgExecBlackOut(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		Img.var = 16;
		FadeSetBlack(Img.var);

		Mode3VramEffCopy();

		Img.step++;
		return;
	}

	if(Img.step == 2)
	{
		Img.var--;
		FadeSetBlack(Img.var);

		if(Img.var == 0)
		{
			Img.step++;
		}
		return;
	}

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
// îíÅ®îwåi
void ImgExecWhiteOut(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		Img.var = 16;
		FadeSetWhite(Img.var);

		Mode3VramEffCopy();

		Img.step++;
		return;
	}

	if(Img.step == 2)
	{
		Img.var--;
		FadeSetWhite(Img.var);

		if(Img.var == 0)
		{
			Img.step++;
		}
		return;
	}

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgExecSetMsg(void)
{
	// wait
	if(Img.step <= 15)
	{
		Img.step++;
		return;
	}

	FadeSetMsg(Img.fade);
	TxtClrSpr();
	TxtShow();

	Img.isMsg = true;
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgExecClrMsg(void)
{
	FadeSetMsg(0);
	TxtHide();
	TxtClrSpr();

	Img.isMsg = false;
	Img.isExec = false;
}
//---------------------------------------------------------------------------
// îwåiÅ®çïÅ®îwåi
void ImgExecLoad(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		Img.var++;
		FadeSetBlack(Img.var);

		if(Img.var >= 16)
		{
			Img.step++;
		}
		return;
	}

	if(Img.step == 2)
	{
		Mode3VramEffCopy();

		Img.step++;
		return;
	}

	if(Img.step == 3)
	{
		Img.var--;
		FadeSetBlack(Img.var);

		if(Img.var == 0)
		{
			Img.step++;
		}
		return;
	}

	// wait
	if(Img.step <= 3+15)
	{
		Img.step++;
		return;
	}

	FadeSetMsg(Img.fade);
	TxtShow();

	Mode3FlipBuf();
	Img.isMsg = true;
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgDrawBg(void)
{
	if(Img.bg == 0)
	{
		Mode3DrawBg2(RGB8(0, 0, 0));

		return;
	}

	if(Img.bg == 900)
	{
		Mode3DrawBg2(RGB8(31, 31, 31));

		return;
	}


//	TRACE("[ImgDrawBg %d]\n", Img.bg);

	ST_FILE_BG_HEADER* h = (ST_FILE_BG_HEADER*)FileGetBg(Img.bg);

	Mode3DrawBg((u16*)(h + 1));
}
//---------------------------------------------------------------------------
void ImgDrawChr(void)
{
	if(Img.chr == 0)
	{
		return;
	}


//	TRACE("[ImgDrawChr %d]\n", Img.chr);

	ST_FILE_CHR_HEADER* h = (ST_FILE_CHR_HEADER*)FileGetChr(Img.chr);

	if(Img.chr == 800)
	{
		Mode3DrawIco(0, 0, h->cx, h->cy, SeenGetIcoBit(), (u16*)(h + 1), FileGetMsk(Img.chr));

		return;
	}

	s32 sx = 12;

	// ç∂í[å©êÿÇÍÇÃÉLÉÉÉââÊëúí≤êÆ
	switch(Img.chr)
	{
	case 4:
	case 5:
	case 104:
	case 105:
	case 110:
	case 111:
	case 112:
	case 113:
		sx = 0;
		break;
	}

	Mode3DrawChr(sx, 0, h->cx, h->cy, (u16*)(h + 1), FileGetMsk(Img.chr));
}
//---------------------------------------------------------------------------
void ImgSetBg(s32 no)
{
	Img.bg = no;
}
//---------------------------------------------------------------------------
void ImgSetChr(s32 no)
{
	Img.chr = no;
}
//---------------------------------------------------------------------------
// ÉÅÉbÉZÅ[ÉWëﬁîå„ÅAÉGÉtÉFÉNÉg
void ImgSetExec(s32 no)
{
	TRACE("[ImgSetExec %x]\n", no);

	Img.eff    = no;
	Img.var    = 0;
	Img.step   = 0;
	Img.isClr  = Img.isMsg;
	Img.isExec = true;
}
//---------------------------------------------------------------------------
void ImgSetExecCond(s32 no)
{
	TRACE("[ImgSetExecCond %d]\n", no);

	if(no == IMG_EFFECT_SET_MSG && Img.isMsg == true)
	{
		return;
	}

	Img.eff    = no;
	Img.var    = 0;
	Img.step   = 0;
	Img.isExec = true;
}
//---------------------------------------------------------------------------
void ImgSetNoWait(void)
{
	Img.step = 16;
}
//---------------------------------------------------------------------------
void ImgSetFade(s32 num)
{ 
	Img.fade = num;

	FadeSetMsg(num);
}
//---------------------------------------------------------------------------
s32 ImgGetBg(void)
{
	return Img.bg;
}
//---------------------------------------------------------------------------
s32 ImgGetFade(void)
{
	return Img.fade;
}
//---------------------------------------------------------------------------
void ImgShowNavi(s32 sel)
{
	SprMoveNavi(0, sel);
	SprShowNavi();
}
//---------------------------------------------------------------------------
void ImgHideNavi(void)
{
	SprHideNavi();
}
//---------------------------------------------------------------------------
bool ImgIsExec(void)
{
	return Img.isExec;
}
