#include "img.h"
#include "libmy/mode4.arm.h"
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
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgInitVar(void)
{
	_Memset(&Img.var, 0x00, sizeof(Img.var));
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExec(void)
{
	switch(Img.no)
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

	case IMG_EFFECT_FILL_BLACK:
		ImgExecFillBlack();
		break;

	case IMG_EFFECT_TXT_OUT:
		ImgExecTxtOut();
		break;

	case IMG_EFFECT_TXT_IN:
		ImgExecTxtIn();
		break;

	case IMG_EFFECT_TXT_HIDE_OUT:
		ImgExecTxtHideOut();
		break;

	case IMG_EFFECT_TXT_HIDE_IN:
		ImgExecTxtHideIn();
		break;

	default:
		SystemError("[Err] ImgExec effect=%d\n", Img.no);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBlackOut(void)
{
	if(Img.arg == 255)
	{
		FadeSetBlack(16);

		goto End;
	}

	if(Img.var[0]++ < Img.arg)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetBlack(Img.var[1]);

		return;
	}


End:
	Img.isTxt = false;
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBlackIn(void)
{
	if(Img.arg == 255)
	{
		FadeSetBlack(0);

		goto End;
	}

	if(Img.var[0]++ < Img.arg)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetBlack(16 - Img.var[1]);

		return;
	}

End:
	Img.isTxt = false;
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecWhiteOut(void)
{
	if(Img.arg == 255)
	{
		FadeSetWhite(16);

		goto End;
	}

	if(Img.var[0]++ < Img.arg)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetWhite(Img.var[1]);

		return;
	}

End:
	Img.isTxt = false;
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecWhiteIn(void)
{
	if(Img.arg == 255)
	{
		FadeSetWhite(0);

		goto End;
	}

	if(Img.var[0]++ < Img.arg)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetWhite(16 - Img.var[1]);

		return;
	}

End:
	Img.isTxt = false;
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecFillBlack(void)
{
	Mode4DrawFill(1);
	Mode4SetFlip();

	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecTxtOut(void)
{
	FadeSetWin();
	TxtShowMsg();

	Img.isTxt = true;
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecTxtIn(void)
{
	FadeSetBlack(0);
	TxtClrMsg();
	TxtClrCur();

	Img.isTxt = false;
	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecTxtHideOut(void)
{
	if(Img.isTxt == true)
	{
		FadeSetWin();
	}

	TxtShowMsg();
	TxtShowCur();

	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecTxtHideIn(void)
{
	FadeSetBlack(0);
	TxtHideMsg();
	TxtHideCur();

	Img.isEff = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetEff(s32 no, s32 arg)
{
	TRACE("[ImgSetEff no:%d arg:%d]\n", no, arg);

	ImgInitVar();

	Img.no  = no;
	Img.arg = arg;
	Img.isEff = true;
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
