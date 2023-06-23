#include "nv.h"
#include "nv2.h"
#include "nv3.h"
#include "libmy/gbfs.h"
#include "libmy/key.h"
#include "log.h"
#include "img.h"
#include "menu.h"
#include "siori.h"
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

	case NV_ACT_RESTART:
		NvExecRestart();
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

	if(Nv.isSkip == TRUE)
	{
		if(cnt & KEY_B)
		{
			Nv.isSkip = FALSE;
		}
		else
		{
			Nv.act = NV_ACT_PARSE;
			return;
		}
	}


	switch(Nv.step)
	{
	case 0:
		TextSetCur(TRUE);
		Nv.step++;
		break;

	case 1:
		if(cnt & KEY_R || trg & KEY_A || trg & KEY_DOWN)
		{
			TextSetCur(FALSE);
			Nv.act = NV_ACT_PARSE;
		}
		else if((trg & KEY_LEFT) && (LogIsEmpty() == FALSE))
		{
			LogSetInit(LOG_RET_NOVEL);
			ManageSetLog();
		}
		else if(trg & KEY_B)
		{
			MenuSetSystem(MENU_SYSTEM_SEL_SKIP);
			ManageSetMenu();
		}
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecRestart(void)
{
	// TODO 選択肢の場合
	// TODO 共有フラグ

	switch(Nv.step)
	{
	case 0:
		LogInit();
		TextClear();
		Nv.step++;
		break;

	case 1:
		ImgSetEffectBefore(IMG_EFFECT_WIPE_TTOB);
		Nv.step++;
		break;

	case 2:
		ImgSetEffectAfter(IMG_EFFECT_FADE_PALETTE);
		SeStop();
		BgmRestart();
		Nv.step++;
		break;

	case 3:
		TextRestart();
		ImgRestart();

		NvSetAct(NV_ACT_KEY);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEffectBefore(u8 no)
{
	if(Nv.isSkip == TRUE)
	{
		return;
	}

	ImgSetEffectBefore(no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEffectAfter(u8 no)
{
	if(Nv.isSkip == TRUE)
	{
		if(no == IMG_EFFECT_TEXT_ON)
		{
			return;
		}

		no = IMG_EFFECT_NORMAL;
	}

	ImgSetEffectAfter(no);
//	TODO ImgSetEffectAfter(IMG_EFFECT_WIPE_TTOB);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetScn(u32 no)
{
	u8* p = FileGetScn(no);

	Nv.size   = FileGetSize();
	Nv.pTxt   = p;
	Nv.pCur   = p;
	Nv.pEvt   = NvSeekCurChr('E');
	Nv.pMsg   = NvSeekCurChr('M');
	Nv.maxEvt = NvGetCurHex2(Nv.pEvt + 1);
	Nv.maxMsg = NvGetCurHex2(Nv.pMsg + 1);
	Nv.no     = no;
	Nv.evtNo  = 0;
	Nv.msgNo  = 0;

	TRACE("\n");
	TRACE("[NvSetScn %04x.txt E%02x M%02x]\n", no, Nv.maxEvt, Nv.maxMsg);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEvt(u32 no)
{
	_ASSERT(no < Nv.maxEvt);


	Nv.pCur = Nv.pEvt;
	NvSkipCurLine2(no + 1);

	u32 adr = NvGetCurHex();
	NvJumpCurAdr(adr);

	Nv.evtNo = no;
	TRACE("[NvSetEvt %x]\n", no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetMsg(u32 no)
{
	_ASSERT(no < Nv.maxMsg);


	Nv.pCur = Nv.pMsg;
	NvSkipCurLine2(no + 1);

	u32 adr = NvGetCurHex();
	NvJumpCurAdr(adr);

	Nv.msgNo = no;
	TRACE("[NvSetMsg %x]\n", no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetNext(void)
{
	Nv.isSkip = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetAct(s32 act)
{
	Nv.act  = act;
	Nv.step = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetFlag(u8 no, s8 val)
{
	Nv.flag[no] = val;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvAddFlag(u8 no, s8 val)
{
	Nv.flag[no] += val;
}
//---------------------------------------------------------------------------
EWRAM_CODE s8 NvGetFlag(u8 no)
{
	return Nv.flag[no];
}
//---------------------------------------------------------------------------
EWRAM_CODE u16 NvGetChrNo(u16 no)
{
	// TODO あかり髪型変更

	if((no >> 8) == 0)
	{
		if(Nv.flag[NV_FLAG_AKARI] & 0x01)
		{
			no |= 0x80;
		}
		no |= 0x100;
	}

	return no;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool NvIsSkip(void)
{
	return Nv.isSkip;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool NvIsRestart(void)
{
	return (Nv.act == NV_ACT_RESTART) ? TRUE : FALSE;
}
