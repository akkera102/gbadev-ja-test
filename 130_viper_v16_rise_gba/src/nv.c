#include "nv.h"
#include "nv2.h"
#include "libmy/key.h"
#include "img.h"
#include "menu.h"
#include "file.h"
#include "ags.arm.h"
#include "bgm.h"
#include "pcm.h"
#include "anm.h"
#include "info.h"

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
	if(Nv.sleep != 0)
	{
		Nv.sleep--;

		return;
	}

	if(Nv.isBuf == true)
	{
		if(AnmIsBufComp(Nv.bNo) == false)
		{
			return;
		}

		Nv.isBuf = false;
	}

	if(Nv.isScr == true)
	{
		if(AnmIsScrComp(Nv.sNo) == false)
		{
			return;
		}

		Nv.isScr = false;
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

	if(Nv.isPcm == true)
	{
		if(Nv.pcmWait != 0)
		{
			Nv.pcmWait--;
		}
		else if(PcmIsPlay() == false)
		{
			goto next;
		}
	}

	if(cnt & KEY_R || trg & KEY_A || trg & KEY_RIGHT)
	{
next:
		Nv.isPcm = false;
		Nv.pcmWait = 0;
		PcmStop();

		NvSetAct(NV_ACT_PARSE);

		return;
	}

	if(trg & KEY_B)
	{
		TxtHideCur();
		TxtShowMsg();

		MenuSetSystem(MENU_SYSTEM_SEL_JUMP);
		AgsSetMenu();

		return;
	}

	if(trg & KEY_SELECT)
	{
		TxtHideCur();
		TxtShowMsg();

		MenuSetDebug();
		AgsSetMenu();

		return;
	}

	if(trg & KEY_L)
	{
		ImgSetEff(IMG_EFFECT_TXT_HIDE_IN, 0);

		MenuSetNone(MENU_RET_NOVEL);
		AgsSetMenu();

		return;
	}


	// 以下、スクロール操作
	if(Nv.isKeyScr == false)
	{
		return;
	}

	u16 rep = KeyGetRep();

	if(rep & KEY_UP)
	{
		AnmSetScr2(0, ANM_TYPE_SCR_UP, 10);

		return;
	}

	if(rep & KEY_DOWN)
	{
		AnmSetScr2(0, ANM_TYPE_SCR_DOWN, 10);

		return;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecSel(void)
{
	switch(Nv.step)
	{
	// 項目の表示
	case 0:
		TxtSetMsg();
		Nv.step++;
		break;

	// 選択中
	case 1: ;
		u16 trg = KeyGetTrg();

		if((trg & KEY_A || trg & KEY_RIGHT) && Nv.sel.cnt != -1)
		{
			Nv.step++;
		}
		else if(trg & KEY_B)
		{
			// パンチ、キック、チョップ
			if(Nv.sel.reg == 3)
			{
				Nv.sel.cnt = 65535;
				Nv.step++;
			}
			else
			{
				TxtHideCur();
				TxtShowMsg();

				MenuSetSystem(MENU_SYSTEM_SEL_JUMP);
				AgsSetMenu();

				Nv.step--;
			}
		}
		else if(trg & KEY_START)
		{
			// バトル時のみ表示
			u16 v = NvGetVar(16);

			if(v == 11 || v == 16 || v == 28)
			{
				TxtHideCur();
				TxtShowMsg();

				MenuSetBattle();
				AgsSetMenu();

				Nv.step--;
			}
		}
		else if(trg & KEY_SELECT)
		{
			TxtHideCur();
			TxtShowMsg();

			MenuSetDebug();
			AgsSetMenu();

			Nv.step--;
		}
		else if(trg & KEY_L)
		{
			ImgSetEff(IMG_EFFECT_TXT_HIDE_IN, 0);

			MenuSetNone(MENU_RET_NOVEL);
			AgsSetMenu();

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

	// 選択終了
	case 2:
		TxtClrMsg();

		NvSetVar(Nv.sel.ret, Nv.sel.cnt);
		NvSetAct(NV_ACT_PARSE);
		AgsSetNovel();
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecLoad(void)
{
	switch(Nv.step)
	{
	case 0:
		AnmSetPause(true);
		TxtClr();

		Nv.step++;
		break;

	case 1:
		PcmStop();
		ImgSetEff(IMG_EFFECT_BLACK_OUT, 0);

		Nv.step++;
		break;

	case 2:
		ImgSetEff(IMG_EFFECT_FILL_BLACK, 0);

		Nv.step++;
		break;

	case 3:
		AgsSetLoad();
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetAct(s32 act)
{
	Nv.act  = act;
	Nv.step = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetScn(char* pStr)
{
	Nv.pStr    = pStr;
	Nv.pScn    = FileGetScn(pStr);
	Nv.pLbl    = (u32*)Nv.pScn;
	Nv.lblMax  = *Nv.pLbl;
	Nv.pCur    = (char*)Nv.pScn + 4 + Nv.lblMax * 4;
	Nv.callCnt = 0;

	TRACE("\n\n[NvSetScn %s]\n", pStr);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetScn2(s32 no)
{
	char* p = InfoGetFile(no);

	NvSetScn(p);
	NvSetVar(16, no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetLbl(s32 no)
{
	Nv.pCur = (char*)Nv.pScn + *(Nv.pLbl + 1 + no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetVar(s32 no, s32 num)
{
	_ASSERT(no < NV_MAX_VAR_CNT);

	Nv.var[no & 0xff] = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 NvGetVar(s32 no)
{
	_ASSERT(no < NV_MAX_VAR_CNT);

	return Nv.var[no & 0xff];
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
EWRAM_CODE char* NvGetStr(void)
{
	return Nv.pStr;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvPushCall(s32 no)
{
	_ASSERT(Nv.callCnt < NV_MAX_CALL_CNT);

	Nv.call[Nv.callCnt++] = Nv.pCur;
	NvSetLbl(no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvPopCall(void)
{
	_ASSERT(Nv.callCnt != 0);

	Nv.pCur = Nv.call[--Nv.callCnt];
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
