#include "img.h"
#include "libmy/mode3.h"
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

	Img.fade = 6;
	Img.fadeWait = 1;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgInitVar(void)
{
	_Memset(&Img.var, 0x00, sizeof(Img.var));
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExec(void)
{
	if(Img.isTxt == true && Img.effect < IMG_EFFECT_IGNORE_NORMAL)
	{
		ImgExecTxtOut();

		return;
	}


	switch(Img.effect)
	{
	case IMG_EFFECT_NONE:
		ImgExecNone();
		break;

	case IMG_EFFECT_NORMAL:
	case IMG_EFFECT_IGNORE_NORMAL:
		ImgExecNormal();
		break;

	case IMG_EFFECT_WIPE_LR:
		ImgExecWipeLr();
		break;

	case IMG_EFFECT_WIPE_UD:
		ImgExecWipeUd();
		break;

	case IMG_EFFECT_WHITE_IN:
		ImgExecWhiteIn();
		break;

	case IMG_EFFECT_WHITE_OUT:
		ImgExecWhiteOut();
		break;

	case IMG_EFFECT_BLACK_IN:
		ImgExecBlackIn();
		break;

	case IMG_EFFECT_BLACK_OUT:
		ImgExecBlackOut();
		break;

	case IMG_EFFECT_SCROLL_UD:
		ImgExecScrollUd();
		break;

	case IMG_EFFECT_SCROLL_DU:
		ImgExecScrollDu();
		break;

	case IMG_EFFECT_FALL:
		ImgExecFall();
		break;

	case IMG_EFFECT_FLASH:
		ImgExecFlash();
		break;

	case IMG_EFFECT_FLASH2:
		ImgExecFlash2();
		break;

	case IMG_EFFECT_TXT_IN:
		ImgExecTxtIn();
		break;

	case IMG_EFFECT_BUFFER:
		ImgExecBuffer();
		break;

	case IMG_EFFECT_IGNORE_LOAD_IN:
		ImgExecLoadIn();
		break;

	case IMG_EFFECT_IGNORE_LOAD_OUT:
		ImgExecLoadOut();
		break;

	case IMG_EFFECT_IGNORE_BG_CHR_SCR:
		ImgExecBgChrScr();
		break;

	case IMG_EFFECT_IGNORE_WAIT_ICO:
		ImgExecWaitIco();
		break;

	default:
		SystemError("[Err] ImgExec effect=%d\n", Img.effect);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecNone(void)
{
	// EMPTY

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
// バッファ描画後、VRAM描画（Ico, Min）します
EWRAM_CODE void ImgExecNormal(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgDrawBuf();
		Mode3SetDraw();

		return;
	}

	ImgDrawVram();

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
// ２ライン飛ばし左右重ね合わせ
EWRAM_CODE void ImgExecWipeLr(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgDrawBuf();

		return;
	}

	s32 x1 = (Img.var[1] * 4) + 2;
	s32 x2 = (240 - 4) - (Img.var[1] * 4);

	Mode3VramCopy(x1, 0, x1+2, 160);
	Mode3VramCopy(x2, 0, x2+2, 160);

	Img.var[1]++;

	if(Img.var[1] >= 60)
	{
		Img.isEffect = false;
	}
}
//---------------------------------------------------------------------------
// ２ライン飛ばし上下重ね合わせ
EWRAM_CODE void ImgExecWipeUd(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgDrawBuf();

		return;
	}

	s32 y1 = (Img.var[1] * 4) + 2;
	s32 y2 = (160 - 4) - (Img.var[1] * 4);

	Mode3VramCopy(0, y1, 240, y1+2);
	Mode3VramCopy(0, y2, 240, y2+2);

	Img.var[1]++;

	if(Img.var[1] >= 40)
	{
		Img.isEffect = false;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecWhiteIn(void)
{
	if(Img.var[0]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetWhite(Img.var[1]);

		return;
	}

	if(Img.var[2]++ == 0)
	{
		Mode3DrawFill(RGB5(31,31,31));
		Mode3SetDraw();

		return;
	}

	FadeSetWhite(0);
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecWhiteOut(void)
{
	if(Img.var[0]++ == 0)
	{
		FadeSetWhite(16);
		ImgDrawBuf();
		Mode3SetDraw();
	}

	if(Img.var[1]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2]++ < 16)
	{
		FadeSetWhite(16 - Img.var[2]);

		return;
	}

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBlackIn(void)
{
	if(Img.var[0]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetBlack(Img.var[1]);

		return;
	}

	if(Img.var[2]++ == 0)
	{
		Mode3DrawFill(RGB5(0,0,0));
		Mode3SetDraw();

		return;
	}

	FadeSetBlack(0);
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBlackOut(void)
{
	if(Img.var[0]++ == 0)
	{
		FadeSetBlack(16);
		ImgDrawBuf();
		Mode3SetDraw();
	}

	if(Img.var[1]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2]++ < 16)
	{
		FadeSetBlack(16 - Img.var[2]);

		return;
	}

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecScrollUd(void)
{
	if(Img.var[0]++ < 1)
	{
		return;
	}
	Img.var[0] = 0;


	Mode3VramScroll(Img.pBg, Img.var[2]);
//	TRACE("%d\n", Img.var[2]);
	Img.var[2]++;

	if(Img.var[2] > Img.bgCy - SCREEN_CY)
	{
		ImgDrawBuf();
		Mode3SetDraw();

		Img.isEffect = false;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecScrollDu(void)
{
	if(Img.var[0]++ < 1)
	{
		return;
	}
	Img.var[0] = 0;


	if(Img.var[1]++ == 0)
	{
		Img.var[2] = Img.bgCy - SCREEN_CY;
	}

	Mode3VramScroll(Img.pBg, Img.var[2]);
//	TRACE("%d\n", Img.var[2]);
	Img.var[2]--;

	if(Img.var[2] < 0)
	{
		ImgDrawBuf();
		Mode3SetDraw();

		Img.isEffect = false;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecFall(void)
{
	if(Img.var[0] == 0)
	{
		s32 i;

		for(i=0; i<4; i++)
		{
			Mode3VramLine(159-i, RGB5(0,0,0));
		}
	}

	if(Img.var[0] < SCREEN_CY)
	{
		Mode3VramCrop2(0, 4, 240, 156-Img.var[0], 0, 0);
//		TRACE("%d\n", 156-Img.var[0]);
		Img.var[0] += 4;
		return;
	}

	// wait
	if(Img.var[1] < 60)
	{
		Img.var[1]++;
		return;
	}

	if(Img.var[2] == 0)
	{
		ImgClrAll();
		ImgSetBgl("waku06b");
		ImgDrawBuf();
		Img.var[2]++;
		return;
	}

	Mode3VramCrop(0, 0, 240, 4+Img.var[3], 0, 156-Img.var[3]);
//	TRACE("%d %d\n", 4+Img.var[3], 156-Img.var[3]);
	Img.var[3] += 4;

	if(Img.var[3] >= SCREEN_CY)
	{
		Img.isEffect = false;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecFlash(void)
{
	if(Img.var[0]++ < 16)
	{
		FadeSetWhite(Img.var[0]);

		return;
	}

	if(Img.var[1]++ < 16)
	{
		FadeSetWhite(16 - Img.var[1]);

		return;
	}

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecFlash2(void)
{
	if(Img.var[0]++ < 16)
	{
		FadeSetWhite(Img.var[0]);

		return;
	}

	if(Img.var[1]++ == 0)
	{
		ImgDrawBuf();
		Mode3SetDraw();
		return;
	}

	if(Img.var[2]++ < 16)
	{
		FadeSetWhite(16 - Img.var[2]);

		return;
	}

	Img.isEffect = false;
}

//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBuffer(void)
{
	Mode3SetDraw();

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecTxtIn(void)
{
	if(Img.var[0]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < Img.fade)
	{
		FadeSetBlack(Img.var[1]);

		return;
	}

	TxtShowMsg();
	TxtSetChr();

	Img.isTxt = true;
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecTxtOut(void)
{
	if(Img.var[0]++ == 0)
	{
		TxtHideMsg();
	}

	if(Img.var[1]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2]++ < Img.fade)
	{
		FadeSetBlack(Img.fade - Img.var[2]);

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
		Img.var[2] = Img.fade;
	}

	if(Img.var[1]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2]++ < 16)
	{
		FadeSetBlack(Img.var[2]);

		return;
	}

	Img.isTxt = false;
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecLoadOut(void)
{
	if(Img.var[0]++ == 0)
	{
		FadeSetBlack(16);
		ImgDrawBuf();
		Mode3SetDraw();

		return;
	}

	if(Img.var[0] == 2)
	{
		ImgDrawVram();
	}

	if(Img.var[1]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2]++ < 16)
	{
		FadeSetBlack(16 - Img.var[2]);

		return;
	}

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBgChrScr(void)
{
	ImgDrawBuf();
	Mode3SetDraw();

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecWaitIco(void)
{
	if(Img.var[0]++ < 15)
	{
		return;
	}

	if(Img.var[1]++ == 0)
	{
		ImgDrawIco();
	}

	if(Img.var[2]++ < 15)
	{
		return;
	}

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawBuf(void)
{
	TRACE("[ImgDrawBuf]\n");

	ImgDrawBg();
	ImgDrawChr1();
	ImgDrawChr2();
	ImgDrawPty();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawVram(void)
{
	TRACE("[ImgDrawVram]\n");

	// VBLANK無視
	ImgDrawIco();
	ImgDrawMin();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawVramClear(void)
{
	TRACE("[ImgDrawVramClear]\n");

	// VBLANK無視
	ImgDrawIcoClear();
	ImgDrawMinClear();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawBg(void)
{
	if(Img.pBg == NULL)
	{
		Mode3DrawFill(RGB5(0,0,0));

		return;
	}


	// スクロール上
	if(Img.bgType == IMG_TYPE_SCROLL_DU)
	{
		Mode3DrawFull2(Img.pBg);

		return;
	}

	// スクロール下
	if(Img.bgType == IMG_TYPE_SCROLL_UD)
	{
		Mode3DrawFull2(Img.pBg + Img.bgCx * Img.bgCy - SCREEN_CX * SCREEN_CY);

		return;
	}

	// フルスクリーン
	if(Img.bgCx == SCREEN_CX && Img.bgCy == SCREEN_CY)
	{
		Mode3DrawFull(Img.pBg);

		return;
	}


	// 下背景
	if(Img.bgType == IMG_TYPE_BLACK_BG)
	{
		Mode3DrawFill(RGB5(0,0,0));
	}
	else
	{
		ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg("waku");
		Mode3DrawFull2((u16*)(h + 1));
	}

	// 上背景
	s32 x = 0;

	if(Img.bgType == IMG_TYPE_CENTER)
	{
		x = SCREEN_CX/2 - Img.bgCx/2;
	}

	Mode3DrawCrop(x, SCREEN_CY/2 - Img.bgCy/2, Img.bgCx, Img.bgCy, Img.pBg);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawChr1(void)
{
	if(Img.pChr1 == NULL)
	{
		return;
	}

	Mode3DrawBlend(0, 0, Img.chr1Cx, Img.chr1Cy, Img.pChr1, Img.pChr1Msk);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawChr2(void)
{
	if(Img.pChr2 == NULL)
	{
		return;
	}

	Mode3DrawBlend(0, 0, Img.chr2Cx, Img.chr2Cy, Img.pChr2, Img.pChr2Msk);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawPty(void)
{
	if(Img.pPty == NULL)
	{
		return;
	}

	Mode3DrawCrop(SCREEN_CX - IMG_PTY_CX, 0, IMG_PTY_CX, IMG_PTY_CY, Img.pPty);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawIco(void)
{
	if(Img.pIco == NULL)
	{
		return;
	}

	Mode3VramCrop3(0, SCREEN_CY - IMG_ICO_CY, IMG_ICO_CX, IMG_ICO_CY, Img.pIco);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawIcoClear(void)
{
	Mode3VramCrop(0, SCREEN_CY - IMG_ICO_CY, IMG_ICO_CX, IMG_ICO_CY, 0, SCREEN_CY - IMG_ICO_CY);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawMin(void)
{
	if(Img.pMin == NULL)
	{
		return;
	}

	Mode3VramCrop3(0, 0, IMG_MIN_CX, IMG_MIN_CX, Img.pMin);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawMinClear(void)
{
	Mode3VramCrop(0, 0, IMG_MIN_CX, IMG_MIN_CX, 0, 0);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetBg(char* p)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(p);

	Img.bgCx = h->cx;
	Img.bgCy = h->cy;
	Img.pBg = (u16*)(h + 1);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetBgl(char* p)
{
	ImgSetBg(p);
	Img.bgType = IMG_TYPE_LEFT;

	TRACE("[ImgSetBgl %s cx:%d cy:%d]\n", p, Img.bgCx, Img.bgCy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetBgc(char* p)
{
	ImgSetBg(p);
	Img.bgType = IMG_TYPE_CENTER;

	TRACE("[ImgSetBgc %s cx:%d cy:%d]\n", p, Img.bgCx, Img.bgCy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetBgb(char* p)
{
	ImgSetBg(p);
	Img.bgType = IMG_TYPE_BLACK_BG;

	TRACE("[ImgSetBgb %s cx:%d cy:%d]\n", p, Img.bgCx, Img.bgCy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetChr1(char* p)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(p);

	Img.chr1Cx = h->cx;
	Img.chr1Cy = h->cy;
	Img.pChr1 = (u16*)(h + 1);
	Img.pChr1Msk = (u8*)FileGetMsk(p);

	TRACE("[ImgSetChr1 %s cx:%d cy:%d]\n", p, Img.chr1Cx, Img.chr1Cy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetChr2(char* p)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(p);

	Img.chr2Cx = h->cx;
	Img.chr2Cy = h->cy;
	Img.pChr2 = (u16*)(h + 1);
	Img.pChr2Msk = (u8*)FileGetMsk(p);

	TRACE("[ImgSetChr2 %s cx:%d cy:%d]\n", p, Img.chr2Cx, Img.chr2Cy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetPty(char* p)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(p);

	Img.pPty = (u16*)(h + 1);

	TRACE("[ImgSetPty %s]\n", p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetIco(char* p)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(p);

	Img.pIco = (u16*)(h + 1);

	TRACE("[ImgSetIco %s]\n", p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetMin(char* p)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(p);

	Img.pMin = (u16*)(h + 1);

	TRACE("[ImgSetMin %s]\n", p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetScrDu(char* p)
{
	ImgSetBg(p);
	Img.bgType = IMG_TYPE_SCROLL_DU;

	TRACE("[ImgSetScrDu %s cx:%d cy:%d]\n", p, Img.bgCx, Img.bgCy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetScrUd(char* p)
{
	ImgSetBg(p);
	Img.bgType = IMG_TYPE_SCROLL_UD;

	TRACE("[ImgSetScrUd %s cx:%d cy:%d]\n", p, Img.bgCx, Img.bgCy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetEff(s32 no)
{
	if(no == IMG_EFFECT_TXT_IN && Img.isTxt == true)
	{
		TxtSetChr();
		return;
	}

	TRACE("[ImgSetEff no:%d]\n", no);

	ImgInitVar();
	Img.effect = no;
	Img.isEffect = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetEffTxt(s32 no)
{
	TRACE("[ImgSetEffTxt no:%d]\n", no);

	switch(no)
	{
	// LR枠
	case IMG_EFFECT_SCRIPT_4:
	case IMG_EFFECT_SCRIPT_6:
	case IMG_EFFECT_SCRIPT_10:
		ImgClrAll();
		ImgSetBgl("waku06b");
		ImgSetEff(IMG_EFFECT_WIPE_LR);
		break;

	// UD黒
	case IMG_EFFECT_SCRIPT_9:
	case IMG_EFFECT_SCRIPT_13:
		ImgClrAll();
		ImgSetEff(IMG_EFFECT_WIPE_UD);
		break;

	// BlackOut枠
	case IMG_EFFECT_SCRIPT_11:
		ImgClrAll();
		ImgSetBgl("waku06b");
		ImgSetEff(IMG_EFFECT_BLACK_OUT);
		break;

	// 何もしない
	case IMG_EFFECT_SCRIPT_12:
		// EMPTY
	break;

	case IMG_EFFECT_SCRIPT_1:
	case IMG_EFFECT_SCRIPT_2:
	case IMG_EFFECT_SCRIPT_3:
	case IMG_EFFECT_SCRIPT_5:
	case IMG_EFFECT_SCRIPT_7:
	case IMG_EFFECT_SCRIPT_14:

	// 正規表現で変更済み
	case IMG_EFFECT_SCRIPT_8:
	case IMG_EFFECT_SCRIPT_15:

		SystemError("[Err] ImgSetEffTxt no=%d\n", no);
		break;

	default:
		ImgSetEff(no);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrAll(void)
{
	ImgClrBg();
	ImgClrChr1();
	ImgClrChr2();
	ImgClrPty();
	ImgClrIco();
	ImgClrMin();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrBg(void)
{
	Img.bgCx = 0;
	Img.bgCy = 0;
	Img.pBg = NULL;
	Img.bgType = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrChr1(void)
{
	Img.chr1Cx = 0;
	Img.chr1Cy = 0;
	Img.pChr1 = NULL;
	Img.pChr1Msk = NULL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrChr2(void)
{
	Img.chr2Cx = 0;
	Img.chr2Cy = 0;
	Img.pChr2 = NULL;
	Img.pChr2Msk = NULL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrPty(void)
{
	Img.pPty = NULL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrIco(void)
{
	Img.pIco = NULL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrMin(void)
{
	Img.pMin = NULL;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 ImgGetFade(void)
{
	return Img.fade;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 ImgGetFadeWait(void)
{
	return Img.fadeWait;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 ImgGetSelCol(void)
{
	return Img.selCol;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetFade(s32 num)
{
	Img.fade = num;

	FadeSetBlack(num);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetFade2(s32 num)
{
	FadeSetBlack(num);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetFadeWait(s32 num)
{
	Img.fadeWait = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetSelCol(s32 num)
{
	Img.selCol = num;

	u16 col = RGB5(0,31,31);				// 水色

	if(num == 1) col = RGB5(31,31, 0);		// 黄
	if(num == 2) col = RGB5( 0,31, 0);		// 緑
	if(num == 3) col = RGB5(31,31,31);		// 白

	SprSetSelectCol(col);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool ImgIsEffect(void)
{
	return Img.isEffect;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool ImgIsTxt(void)
{
	return Img.isTxt;
}
