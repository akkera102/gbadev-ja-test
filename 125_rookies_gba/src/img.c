#include "img.h"
#include "libmy/mode3.arm.h"
#include "libmy/spr.h"
#include "libmy/fade.h"
#include "file.h"
#include "txt.h"


//---------------------------------------------------------------------------
ST_IMG Img;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgInit(void)
{
	_Memset(&Img, 0x00, sizeof(ST_IMG));

	Img.txtFade = 6;
	Img.txtWait = 1;
	Img.stiWait = 3;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgInitVar(void)
{
	_Memset(&Img.var, 0x00, sizeof(Img.var));
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExec(void)
{
	if(Img.isTxt == true && Img.effNo <= IMG_EFFECT_SCROLL_DU && Img.effNo != IMG_EFFECT_BLACK_IN)
	{
		ImgExecTxtOut();

		return;
	}

	switch(Img.effNo)
	{
	case IMG_EFFECT_BLACK_OUT:
		ImgExecBlackOut();
		break;

	case IMG_EFFECT_BLACK_IN:
		ImgExecBlackIn();
		break;

	case IMG_EFFECT_WHITE_OUT:
		ImgExecWhiteOut();
		break;

	case IMG_EFFECT_WHITE_IN:
		ImgExecWhiteIn();
		break;

	case IMG_EFFECT_CURTAIN_OPEN:
		ImgExecCurtainOpen();
		break;

	case IMG_EFFECT_CURTAIN_CLOSE:
		ImgExecCurtainClose();
		break;

	case IMG_EFFECT_NORMAL_COPY:
	case IMG_EFFECT_NORMAL_COPY2:
		ImgExecNomarlCopy();
		break;

	case IMG_EFFECT_FILL_BLACK:
	case IMG_EFFECT_FILL_BLACK2:
		ImgExecFillBlack();
		break;

	case IMG_EFFECT_SCROLL_UD:
		ImgExecScrollUd();
		break;

	case IMG_EFFECT_SCROLL_DU:
		ImgExecScrollDu();
		break;

	case IMG_EFFECT_TXT_IN:
		ImgExecTxtIn();
		break;

	case IMG_EFFECT_LOAD_IN:
		ImgExecLoadIn();
		break;

	case IMG_EFFECT_LOAD_OUT:
		ImgExecLoadOut();
		break;

	case IMG_EFFECT_EMPTY:
		ImgExecEmpty();
		break;

	default:
		SystemError("[Err] ImgExec effect=%d\n", Img.effNo);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBlackOut(void)
{
	if(Img.var[0]++ < Img.effWait)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetBlack(16 - Img.var[1]);

		return;
	}

	Img.isEff = false;
}
//---------------------------------------------------------------------------
// フェードを初期値にしてブラックイン
EWRAM_CODE void ImgExecBlackIn(void)
{
	if(Img.var[0]++ == 0)
	{
		// 例外処理
		TxtHideMsg();
		Img.isTxt = false;

		Img.var[2] = Img.txtFade;
	}

	if(Img.var[1]++ < Img.effWait)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2]++ < 16)
	{
		FadeSetBlack(Img.var[2]);

		return;
	}

	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecWhiteOut(void)
{
	if(Img.var[0]++ < Img.effWait)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetWhite(16 - Img.var[1]);

		return;
	}

	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecWhiteIn(void)
{
	if(Img.var[0]++ < Img.effWait)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetWhite(Img.var[1]);

		return;
	}

	Img.isEff = false;
}
//---------------------------------------------------------------------------
// 5.菱形エフェクト→表示
EWRAM_CODE void ImgExecCurtainOpen(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		return;
	}

	if(Img.var[1]++ < 1)
	{
		return;
	}
	Img.var[1] = 0;

	Mode3VramEff5(Img.var[2]);

	if(Img.var[2]++ < 8)
	{
		return;
	}

	Img.isEff = false;
}
//---------------------------------------------------------------------------
// 6.菱形エフェクト→黒背景
EWRAM_CODE void ImgExecCurtainClose(void)
{
	if(Img.var[0]++ < 1)
	{
		return;
	}
	Img.var[0] = 0;

	Mode3VramEff6(Img.var[1]);

	if(Img.var[1]++ < 8)
	{
		return;
	}

	ImgClrBg();
	ImgClrChr();
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecNomarlCopy(void)
{
	ImgDrawBg();
	ImgDrawChr();

	Mode3SetDraw();

	if(Img.var[0]++ < Img.stiWait)
	{
		return;
	}

	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecFillBlack(void)
{
	ImgClrBg();
	ImgDrawBg();
	Mode3SetDraw();

	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecScrollUd(void)
{
	if(Img.var[0]++ < 1)
	{
		return;
	}
	Img.var[0] = 0;


	Mode3VramScrY(Img.bg.pDat, Img.var[1]);
//	TRACE("Ud %d\n", Img.var[1]);
	Img.var[1]++;

	if(Img.var[1] <= Img.bg.cy - 140)
	{
		return;
	}

	Img.bg.type = IMG_TYPE_SCROLL_DOWN;
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecScrollDu(void)
{
	if(Img.var[0]++ == 0)
	{
		Img.var[2] = Img.bg.cy - 140;
	}

	if(Img.var[1]++ < 1)
	{
		return;
	}
	Img.var[1] = 0;


	Mode3VramScrY(Img.bg.pDat, Img.var[2]);
//	TRACE("Du %d\n", Img.var[2]);
	Img.var[2]--;

	if(Img.var[2] >= 0)
	{
		return;
	}

	Img.bg.type = IMG_TYPE_SCROLL_UP;
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecTxtIn(void)
{
	if(Img.var[0]++ < Img.txtWait)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < Img.txtFade)
	{
		FadeSetBlack(Img.var[1]);

		return;
	}

	TxtShowMsg();
	TxtSetChr();

	Img.isTxt = true;
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecTxtOut(void)
{
	if(Img.var[0]++ == 0)
	{
		TxtHideMsg();
	}

	if(Img.var[1]++ < Img.txtWait)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2]++ < Img.txtFade)
	{
		FadeSetBlack(Img.txtFade - Img.var[2]);

		return;
	}

	ImgInitVar();
	Img.isTxt = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecLoadIn(void)
{
	if(Img.var[0]++ == 0)
	{
		TxtHideMsg();
		Img.isTxt = false;

		Img.var[2] = Img.txtFade;
	}

	if(Img.var[1]++ < Img.effWait)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2]++ < 16)
	{
		FadeSetBlack(Img.var[2]);

		return;
	}

	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecLoadOut(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgDrawBg();
		ImgDrawChr();
		Mode3SetDraw();

		return;
	}

	if(Img.var[1]++ < Img.effWait)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2]++ < 16)
	{
		FadeSetBlack(16 - Img.var[2]);

		return;
	}

	Img.isEff = false;
}
//---------------------------------------------------------------------------
// オープニング用（TAI）スクリプト処理を抜ける為に使用
EWRAM_CODE void ImgExecEmpty(void)
{
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawBg(void)
{
	if(Img.bg.pDat == NULL)
	{
		Mode3DrawFill(RGB5(0,0,0));

		return;
	}

	// スクロール下表示
	if(Img.bg.type == IMG_TYPE_SCROLL_DOWN)
	{
		Mode3DrawScr(Img.bg.pDat + Img.bg.cx * Img.bg.cy - SCREEN_CX * 140);

		return;
	}

	// スクロール上表示
	if(Img.bg.type == IMG_TYPE_SCROLL_UP)
	{
		Mode3DrawScr(Img.bg.pDat);

		return;
	}

	// 通常背景
	Mode3DrawBg(Img.bg.cx, Img.bg.cy, Img.bg.pDat);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawChr(void)
{
	if(Img.chr1.pDat != NULL)
	{
		Mode3DrawChr(Img.chr1.sx, Img.chr1.sy, Img.chr1.cx, Img.chr1.cy, Img.chr1.pDat, Img.chr1.pMsk);
	}

	if(Img.chr2.pDat != NULL)
	{
		Mode3DrawChr(Img.chr2.sx, Img.chr2.sy, Img.chr2.cx, Img.chr2.cy, Img.chr2.pDat, Img.chr2.pMsk);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrBg(void)
{
	Img.bg.pDat = NULL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrChr(void)
{
	Img.chr1.pDat = NULL;
	Img.chr2.pDat = NULL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetBg(char* p)
{
	ST_FILE_LZ7_HEADER* h = (ST_FILE_LZ7_HEADER*)FileGetLz7(p);

	Img.bg.cx   = h->cx;
	Img.bg.cy   = h->cy;
	Img.bg.pDat = (u16*)(h + 1);
	Img.bg.type = IMG_TYPE_LEFT;

	TRACE("[ImgSetBg %s %d %d]\n", p, Img.bg.cx, Img.bg.cy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetScr(char* p, s32 type)
{
	ST_FILE_IMG_HEADER* i = (ST_FILE_IMG_HEADER*)FileGetImg(p);

	Img.bg.cx   = i->cx;
	Img.bg.cy   = i->cy;
	Img.bg.pDat = (u16*)(i + 1);
	Img.bg.type = type;

	TRACE("[ImgSetScr %s %d %d %d]\n", p, Img.bg.cx, Img.bg.cy, type);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetChr1(char* p)
{
	ST_FILE_IMG_HEADER* i = (ST_FILE_IMG_HEADER*)FileGetImg(p);
	ST_FILE_MSK_HEADER* m = (ST_FILE_MSK_HEADER*)FileGetMsk(p);

	Img.chr1.sx   = m->sx;
	Img.chr1.sy   = m->sy;
	Img.chr1.cx   = i->cx;
	Img.chr1.cy   = i->cy;
	Img.chr1.pDat = (u16*)(i + 1);
	Img.chr1.pMsk =  (u8*)(m + 1);

	TRACE("[ImgSetChr1 %s %d %d %d %d]\n", p, Img.chr1.sx, Img.chr1.sy, Img.chr1.cx, Img.chr1.cy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetChr2(char* p)
{
	ST_FILE_IMG_HEADER* i = (ST_FILE_IMG_HEADER*)FileGetImg(p);
	ST_FILE_MSK_HEADER* m = (ST_FILE_MSK_HEADER*)FileGetMsk(p);

	Img.chr2.sx   = m->sx;
	Img.chr2.sy   = m->sy;
	Img.chr2.cx   = i->cx;
	Img.chr2.cy   = i->cy;
	Img.chr2.pDat = (u16*)(i + 1);
	Img.chr2.pMsk =  (u8*)(m + 1);

	TRACE("[ImgSetchr2 %s %d %d %d %d]\n", p, Img.chr2.sx, Img.chr2.sy, Img.chr2.cx, Img.chr2.cy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetEff(s32 no, s32 wait)
{
	/// 既にテキスト表示している場合
	if(no == IMG_EFFECT_TXT_IN && Img.isTxt == true)
	{
		TxtSetChr();
		return;
	}

	// 通常コピーエフェクトかつ、前回分の表示リソースだった場合
	if(no == IMG_EFFECT_NORMAL_COPY && ImgIsPrevBgChr() == true)
	{
		return;
	}
	Img.bg.pPrv   = Img.bg.pDat;
	Img.chr1.pPrv = Img.chr1.pDat;
	Img.chr2.pPrv = Img.chr2.pDat;


	TRACE("[ImgSetEff no:%d wait:%d]\n", no, wait);

	ImgInitVar();

	Img.effNo   = no;
	Img.effWait = wait;
	Img.isEff   = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetTxtFade(s32 num)
{
	Img.txtFade = num;

	FadeSetBlack(num);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetTxtFade2(s32 num)
{
	FadeSetBlack(num);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetTxtWait(s32 num)
{
	Img.txtWait = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetStiWait(s32 num)
{
	Img.stiWait = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 ImgGetTxtFade(void)
{
	return Img.txtFade;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 ImgGetTxtWait(void)
{
	return Img.txtWait;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 ImgGetStiWait(void)
{
	return Img.stiWait;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool ImgIsPrevBgChr(void)
{
	if(Img.bg.pPrv   != Img.bg.pDat)   return false;
	if(Img.chr1.pPrv != Img.chr1.pDat) return false;
	if(Img.chr2.pPrv != Img.chr2.pDat) return false;

	return true;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool ImgIsEff(void)
{
	return Img.isEff;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool ImgIsTxt(void)
{
	return Img.isTxt;
}
