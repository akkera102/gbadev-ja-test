#include "nv.h"
#include "nv2.h"
#include "libmy/key.h"
#include "log.h"
#include "img.h"
#include "menu.h"
#include "file.h"
#include "manage.h"
#include "bgm.h"

//---------------------------------------------------------------------------
ST_NV Nv;


//---------------------------------------------------------------------------
EWRAM_CODE void NvInit(void)
{
	_Memset(&Nv, 0x00, sizeof(ST_NV));
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExec(void)
{
	if(Nv.wait != 0)
	{
		Nv.wait--;
		return;
	}


	switch(Nv.act)
	{
	case NV_ACT_PARSE:
		NvExecParse();
		break;

	case NV_ACT_KEY:
		NvExecKey();
		break;

	case NV_ACT_LOAD:
		NvExecLoad();
		break;

	default:
		SystemError("[Err] NvExec Nv.act = %d\n", Nv.act);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecKey(void)
{
	if(Nv.isPty == true)
	{
		NvExecKeyPty();

		return;
	}

	NvExecKeyTxt();
}
//---------------------------------------------------------------------------
EWRAM_CODE void  NvExecKeyTxt(void)
{
	u16 cnt = KeyGetCnt();
	u16 trg = KeyGetTrg();

	// メッセージスキップ
	if(Nv.isSkip == true)
	{
		if(cnt & KEY_B)
		{
			Nv.isSkip = false;
		}
		else
		{
			goto KeyOn;
		}
	}


	if(cnt & KEY_R || trg & KEY_A || trg & KEY_DOWN)
	{
KeyOn:

		TxtSetPage();
		NvSetAct(NV_ACT_PARSE);
		return;
	}

	if(trg & KEY_LEFT && LogIsEmpty() == false)
	{
		TxtSetCur(false);
		LogSetInit(LOG_RET_NOVEL);

		ManageSetLog();
		return;
	}

	if(trg & KEY_B)
	{
		TxtSetCur(false);
		MenuSetSystem(MENU_SYSTEM_SEL_SAVE);

		ManageSetMenu();
		return;
	}

	if(trg & KEY_L)
	{
		TxtHideMsg();
		ImgSetFade2(0);
		ImgSetEff(IMG_EFFECT_IGNORE_BG_CHR_SCR);

		MenuSetNone(MENU_RET_NOVEL);

		ManageSetMenu();
		return;
	}

}
//---------------------------------------------------------------------------
EWRAM_CODE void  NvExecKeyPty(void)
{
	u16 cnt = KeyGetCnt();
	u16 trg = KeyGetTrg();

	// メッセージスキップ
	if(Nv.isSkip == true)
	{
		if(cnt & KEY_B)
		{
			Nv.isSkip = false;
		}
		else
		{
			goto KeyOn;
		}
	}


	if(cnt & KEY_R || trg & KEY_A || trg & KEY_DOWN)
	{
KeyOn:
		ImgClrPty();
		ImgSetEff(IMG_EFFECT_NORMAL);

		Nv.isPty = false;

		NvSetAct(NV_ACT_PARSE);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecLoad(void)
{
	switch(Nv.step)
	{
	case 0:
		LogInit();
		TxtHideMsg();
		ImgSetEff(IMG_EFFECT_IGNORE_LOAD_IN);

		Nv.step++;
		break;

	case 1:
		ImgSetFade3();
		BgmPlayLoad();
		ImgSetEff(IMG_EFFECT_IGNORE_LOAD_OUT);

		Nv.step++;
		break;

	case 2:
		ImgSetEff(IMG_EFFECT_TXT_IN);
		TxtSetCur(true);

		NvSetAct(NV_ACT_KEY);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetTxt(s32 chap, s32 part)
{
	Nv.pTxt = FileGetTxt(chap, part);
	Nv.pCur = Nv.pTxt;
	Nv.part = part;
	Nv.chap = chap;

	TRACE("\n\n[NvSetTxt cs%02d_%02d.txt]\n", chap, part);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetAct(s32 act)
{
	Nv.act  = act;
	Nv.step = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetSkip(void)
{
	Nv.isSkip = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 NvGetChap(void)
{
	return Nv.chap;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool NvIsSkip(void)
{
	return Nv.isSkip;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 NvNextCurNum(void)
{
	s32 ret = 0;

	do {
		ret = (ret * 10) + (*Nv.pCur++ - '0');

	} while(_IsDigit(*Nv.pCur) == true);


	// skip '\0'
	Nv.pCur++;

	return ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* NvNextCurStr(void)
{
	char* ret = Nv.pCur;

	while(*Nv.pCur++ != '\0')
	{
		// EMPTY
	}

	return ret;
}
