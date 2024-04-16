#include "img.h"
#include "libmy/mode3.arm.h"
#include "libmy/spr.h"
#include "libmy/fade.h"
#include "file.h"
#include "txt.h"


//---------------------------------------------------------------------------
// �����}�@���́A������
char ImgMapStr[IMG_MAP_MAX_CNT][18+1] = {
	// 0
	"��",
	"�q",
	"���@�~",
	"���@��",
	"��@��",
	"�e���X",

	// 6
	"�P�K�@�q��",
	"�P�K�@���a�q�̕���",
	"�P�K�@����l�̕���",
	"�P�K�@����̕���",
	"�P�K�@�q��",
	"�P�K�@�o�X���[��",
	"�P�K�@���փz�[��",
	"�P�K�@�H��",
	"�P�K�@�n����",

	// 15
	"�Q�K�@�[�я��̕���",
	"�Q�K�@�q��",
	"�Q�K�@�q��",
	"�Q�K�@���R�̕���",
	"�Q�K�@�����̕���",
	"�Q�K�@��؂̕���",
	"�Q�K�@�q��",
	"�Q�K�@�o�X���[��",
	"�Q�K�@�P�K�ւ̊K�i",
	"�Q�K�@����",
	"�Q�K�@����K�i",

	// 26 �ǉ���
	"�P�K�@�L��",
	"�Q�K�@�L��",
	"�P�K�@�H�H�H",
	"�Q�K�@�H�H�H",
};


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
	if(Img.isTxt == true)
	{
		switch(Img.effect)
		{
		// �e�L�X�g�\���̂܂܃G�t�F�N�g���s��
		case IMG_EFFECT_DRAW_CHR:
		case IMG_EFFECT_CLR_CHR:
		case IMG_EFFECT_VIB:
		case IMG_EFFECT_MAP_IN:
			// EMPTY
			break;

		default:
			ImgExecTxtOut();
			return;
		}
	}

	switch(Img.effect)
	{
	case IMG_EFFECT_BLACK_IN:
		ImgExecBlackIn();
		break;

	case IMG_EFFECT_BLACK_OUT:
		ImgExecBlackOut();
		break;

	case IMG_EFFECT_WHITE_IN:
		ImgExecWhiteIn();
		break;

	case IMG_EFFECT_WHITE_OUT:
		ImgExecWhiteOut();
		break;

	case IMG_EFFECT_BLACK_FILL:
		ImgExecBlackFill();
		break;

	case IMG_EFFECT_BLACK_RECT:
		ImgExecBlackRect();
		break;

	case IMG_EFFECT_CLR_CHR:
		ImgExecClrChr();
		break;

	case IMG_EFFECT_DRAW_BG:
		ImgExecDrawBg();
		break;

	case IMG_EFFECT_DRAW_CHR:
		ImgExecDrawChr();
		break;

	case IMG_EFFECT_VIB:
		ImgExecVib();
		break;

	case IMG_EFFECT_MAP_IN:
		ImgExecMapIn();
		break;

	case IMG_EFFECT_MAP_OUT:
		ImgExecMapOut();
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

	case IMG_EFFECT_SCROLL_DU_FADE:
		ImgExecScrDuFade();
		break;

	case IMG_EFFECT_SCROLL_DC:
		ImgExecScrDc();
		break;

	case IMG_EFFECT_SCROLL_INIT:
		ImgExecScrInit();
		break;

	default:
		SystemError("[Err] ImgExec effect=%d\n", Img.effect);
		break;
	}
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

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBlackOut(void)
{
	if(Img.var[0]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetBlack(16 - Img.var[1]);

		return;
	}

	Img.isEffect = false;
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

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecWhiteOut(void)
{
	if(Img.var[0]++ < Img.fadeWait)
	{
		return;
	}
	Img.var[0] = 0;

	if(Img.var[1]++ < 16)
	{
		FadeSetWhite(16 - Img.var[1]);

		return;
	}

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBlackFill(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgClrBgChr();
		Mode3DrawFill(RGB5(0,0,0));
		Mode3SetDraw();

		return;
	}

	FadeSetBlack(Img.fade);
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecBlackRect(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgClrBgChr();
		Mode3DrawFill(RGB5(0,0,0));

		return;
	}

	if(Img.var[1]++ < 1)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2] < 8)
	{
		Mode3VramEffRect(Img.var[2]++);

		return;
	}

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecClrChr(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgClrChr();
		ImgDrawBgChr();
		TxtHideMsg();

		return;
	}

	if(Img.var[1]++ < 1)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2] < 5)
	{
		Mode3VramEffWave(Img.var[2]++);

		return;
	}

	TxtShowMsg();
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecDrawBg(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgDrawBgChr();

		return;
	}

	if(Img.var[1]++ < 1)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2] < 8)
	{
		Mode3VramEffRect(Img.var[2]++);

		return;
	}

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecDrawChr(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgDrawBgChr();
		TxtHideMsg();

		return;
	}

	if(Img.var[1]++ < 1)
	{
		return;
	}
	Img.var[1] = 0;

	if(Img.var[2] < 5)
	{
		Mode3VramEffWave(Img.var[2]++);

		return;
	}

	TxtShowMsg();
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecVib(void)
{
	if(Img.var[0]++ < 1)
	{
		return;
	}
	Img.var[0] = 0;

	Mode3VramVib(Img.var[1]++);

	if(Img.var[1] <= 10)
	{
		return;
	}

	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecMapIn(void)
{
	if(Img.var[0]++ == 0)
	{
		TxtHideMsg();
	}

	if(Img.var[1] < 30)
	{
		Mode3VramEffMarkRl(Img.var[1]++);

		return;
	}

	if(Img.var[2] < 30)
	{
		Img.var[2]++;

		return;
	}


	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetMap(Img.mapNo);
	Mode3VramCrop3(SCREEN_CX/2 - h->cx/2, 1, h->cx, h->cy, (u16*)(h + 1));

	FadeSetBlack(0);
	TxtDrawStr2(0, 9, ImgMapStr[Img.mapMsg]);
	TxtShowMsg();

	Img.isTxt = false;
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecMapOut(void)
{
	TxtHideMsg();
	TxtClear();

	ImgSetEff(IMG_EFFECT_BLACK_RECT);
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
		TxtHideMsg();
		Img.isTxt = false;

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

	if(Img.var[3]++ == 0)
	{
		Mode3DrawFill(RGB5(0,0,0));
		Mode3SetDraw();

		return;
	}

	FadeSetBlack(0);
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecLoadOut(void)
{
	if(Img.var[0]++ == 0)
	{
		FadeSetBlack(16);
		ImgDrawBgChr();
		Mode3SetDraw();

		return;
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
EWRAM_CODE void ImgExecEmpty(void)
{
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecScrDuFade(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgDrawBgChr();
		Mode3SetDraw();

		FadeSetBlack(0);
		Img.var[2] = -160;
		Mode3VramScrDu(Img.var[2]);

		return;
	}

	if(Img.var[1]++ < 1)
	{
		return;
	}
	Img.var[1] = 0;

	Mode3VramScrDu(Img.var[2]++);

	if(Img.var[2] >= 100)
	{
		Img.var[3] = ((Img.var[2] - 100) >> 2) + 1;
		// TRACE("%d\n", Img.var[3]);
		FadeSetBlack(Img.var[3]);
	}

	if(Img.var[2] < 160)
	{
		return;
	}

	if(Img.var[4]++ == 0)
	{
		ImgClrBgChr();
		ImgDrawBgChr();
		Mode3SetDraw();

		return;
	}

	FadeSetBlack(0);
	Mode3VramScrDu(0);
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecScrDc(void)
{
	if(Img.var[0]++ == 0)
	{
		ImgDrawBgChr();
		Mode3SetDraw();

		Img.var[2] = -160;
		Mode3VramScrDu(Img.var[2]);

		return;
	}

	if(Img.var[1]++ < 1)
	{
		return;
	}
	Img.var[1] = 0;

	Mode3VramScrDu(Img.var[2]++);

	if(Img.var[2] <= 0)
	{
		return;
	}

	Mode3VramScrDu(0);
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgExecScrInit(void)
{
	Mode3VramScrDu(0);
	Img.isEffect = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawBgChr(void)
{
	TRACE("[ImgDrawBgChr]\n");

	ImgDrawBg();
	ImgDrawChr();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawBg(void)
{
	if(Img.pBg == NULL)
	{
		Mode3DrawFill(RGB5(0,0,0));

		return;
	}


	Mode3DrawCrop(0, 0, SCREEN_CX, SCREEN_CY, Img.pBg);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDrawChr(void)
{
	if(Img.pChr == NULL)
	{
		return;
	}

	Mode3DrawBlend(0, 0, SCREEN_CX, SCREEN_CY, Img.pChr, Img.pChrMsk);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetBg(char* p)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(p);

	Img.pBg = (u16*)(h + 1);

	TRACE("[ImgSetBg %s]\n", p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetChr(char* p)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(p);

	Img.pChr = (u16*)(h + 1);
	Img.pChrMsk = (u8*)FileGetMsk(p);

	TRACE("[ImgSetChr %s]\n", p);
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

	Img.effect = no;
	Img.fadeWait = 1;

	ImgInitVar();
	Img.isEffect = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrBgChr(void)
{
	ImgClrBg();
	ImgClrChr();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrBg(void)
{
	Img.pBg = NULL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgClrChr(void)
{
	Img.pChr = NULL;
	Img.pChrMsk = NULL;
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

	u16 col = RGB5(0,31,31);				// ���F

	if(num == 1) col = RGB5(31,31, 0);		// ��
	if(num == 2) col = RGB5( 0,31, 0);		// ��
	if(num == 3) col = RGB5(31,31,31);		// ��

	SprSetSelectCol(col);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetSelCol2(void)
{
	ImgSetSelCol(Img.selCol);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgSetMap(s32 map, s32 vis)
{
	_ASSERT(map < IMG_MAP_MAX_CNT);

	Img.mapNo = map;
	Img.mapMsg = map;

	// ��\���̏ꍇ
	if(vis == 1)
	{
		if(map < 15)
		{
			// 1�K�H�H�H
			Img.mapMsg = 28;
		}
		else
		{
			// 2�K�H�H�H
			Img.mapMsg = 29;
		}
	}
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
