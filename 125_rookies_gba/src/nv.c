#include "nv.h"
#include "nv2.h"
#include "libmy/key.h"
#include "log.h"
#include "img.h"
#include "menu.h"
#include "file.h"
#include "manage.h"
#include "bgm.h"
#include "se.h"

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

		if(KeyGetCnt() & KEY_R)
		{
			Nv.wait = 0;
		}

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

	case NV_ACT_SEL:
		NvExecSel();
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

		TxtWritePage();
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
		ImgSetTxtFade2(0);

		MenuSetNone(MENU_RET_NOVEL);

		ManageSetMenu();
		return;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void  NvExecSel(void)
{
	switch(Nv.step)
	{
	// 項目の表示
	case 0:
		Nv.isSkip = false;

		ImgSetEff(IMG_EFFECT_TXT_IN, 0);
		TxtSetChr();
		TxtSetCur(false);

		// 攻略情報追加
		TxtSetNum(Nv.sel.ans, Nv.sel.reg);

		if(MenuIsHowto() == true)
		{
			TxtShowNum();
		}
		else
		{
			TxtHideNum();
		}

		Nv.step++;
		break;

	// 選択中
	case 1: ;
		u16 trg = KeyGetTrg();

		if((trg & KEY_A) && Nv.sel.cnt != -1)
		{
			Nv.step++;
		}
		else if((trg & KEY_LEFT) && (LogIsEmpty() == false))
		{
			TxtHideNum();
			LogSetInit(LOG_RET_NOVEL);
			ManageSetLog();

			Nv.step--;
		}
		else if(trg & KEY_B)
		{
			TxtHideNum();
			MenuSetSystem(MENU_SYSTEM_SEL_SAVE);
			ManageSetMenu();

			Nv.step--;
		}
		else if(trg & KEY_L)
		{
			TxtHideNum();
			TxtHideMsg();
			ImgSetTxtFade2(0);

			MenuSetNone(MENU_RET_NOVEL);
			ManageSetMenu();

			Nv.step--;
		}
		else if((trg & KEY_UP) && Nv.sel.cnt > 0)
		{
			Nv.sel.cnt--;

			Nv.step--;
		}
		else if((trg & KEY_DOWN) && (Nv.sel.cnt + 1) < Nv.sel.reg)
		{
			Nv.sel.cnt++;

			Nv.step--;
		}
		break;

	// 選択終了。履歴に選択肢を保存
	case 2:
		NvSetVar(Nv.sel.ret, Nv.sel.cnt);
		TxtWriteSel(Nv.sel.p[Nv.sel.cnt]);
		TxtHideNum();

		NvSetAct(NV_ACT_PARSE);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecLoad(void)
{
	switch(Nv.step)
	{
	case 0:
		LogInit();
		ImgSetEff(IMG_EFFECT_LOAD_IN, 0);

		Nv.step++;
		break;

	case 1:
		BgmPlayLoad();
		SePlayLoad();
		ImgSetEff(IMG_EFFECT_LOAD_OUT, 0);

		Nv.step++;
		break;

	case 2:
		ImgSetEff(IMG_EFFECT_TXT_IN, 0);

		if(Nv.actPrev == NV_ACT_KEY)
		{
			TxtSetCur(true);
		}

		NvSetAct(Nv.actPrev);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetAct(s32 act)
{
	Nv.actPrev = Nv.act;
	Nv.act = act;
	Nv.step = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetScn(char* p)
{
	Nv.pStr   = p;
	Nv.pScn   = (char*)FileGetScn(p);
	Nv.pLbl   = (u32*)Nv.pScn;
	Nv.lblMax = *Nv.pLbl;
	Nv.pCur   = Nv.pScn + 4 + Nv.lblMax * 4;

	TRACE("\n\n[NvSetScn %s]\n", p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetLbl(s32 no)
{
	Nv.pCur = Nv.pScn + *(Nv.pLbl + 1 + no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetSkip(void)
{
	Nv.isSkip = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetVar(s32 no, s32 num)
{
	_ASSERT(no < NV_MAX_VAR_CNT);

	Nv.var[no] = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 NvGetSelReg(void)
{
	return Nv.sel.reg;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 NvGetSelCnt(void)
{
	return Nv.sel.cnt;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* NvGetSelStr(s32 no)
{
	return Nv.sel.p[no];
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 NvGetVar(s32 no)
{
	_ASSERT(no < NV_MAX_VAR_CNT);

	return Nv.var[no];
}
//---------------------------------------------------------------------------
EWRAM_CODE bool NvIsSkip(void)
{
	return Nv.isSkip;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool NvIsActSel(void)
{
	return (Nv.act == NV_ACT_SEL) ? true : false;
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
