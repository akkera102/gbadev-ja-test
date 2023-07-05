#include "nv.h"
#include "nv2.h"
#include "nv3.h"
#include "libmy/gbfs.h"
#include "libmy/key.h"
#include "libmy/spr.h"
#include "log.h"
#include "img.h"
#include "menu.h"
#include "siori.h"
#include "file.h"
#include "manage.h"
#include "bgm.h"
#include "se.h"
#include "siori.h"



//---------------------------------------------------------------------------
ST_NV Nv;


//---------------------------------------------------------------------------
EWRAM_CODE void NvInit(void)
{
	_Memset(&Nv, 0x00, sizeof(ST_NV));

	// ���ʃt���O�̏㏑��
	SioriLoadFlag();
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

	case NV_ACT_SELECT:
		NvExecSel();
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

	if(Nv.isSkip == true)
	{
		if(cnt & KEY_B)
		{
			Nv.isSkip = false;
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
		TxtSetCur(true);
		Nv.step++;
		break;

	case 1:
		if(cnt & KEY_R || trg & KEY_A || trg & KEY_DOWN)
		{
			TxtSetCur(false);
			Nv.act = NV_ACT_PARSE;
		}
		else if((trg & KEY_LEFT) && (LogIsEmpty() == false))
		{
			LogSetInit(LOG_RET_NOVEL);
			ManageSetLog();
			Nv.step--;
		}
		else if(trg & KEY_B)
		{
			MenuSetSystem(MENU_SYSTEM_SEL_SKIP);
			ManageSetMenu();
			Nv.step--;
		}
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecSel(void)
{
	switch(Nv.step)
	{
	// ���ڂ̕\��
	case 0:
		TxtClearXY();
		TxtSetBuf(false);
		TxtSetCur(false);

		s32 i;

		for(i=0; i<Nv.sel.cnt; i++)
		{
			if(i == Nv.sel.num)
			{
				SprSetImgWhite();
			}
			else
			{
				SprSetImgGray();
			}

			Nv.pCur = Nv.sel.pStr[i];
			NvSetCurStr();

			TxtDrawStr(Nv.str);
			TxtSetLf();
		}

		SprSetImgWhite();
		NvSetEffectAfter(IMG_EFFECT_TXT_ON);

		Nv.step++;
		break;

	// �I��
	case 1: ;
		u16 trg = KeyGetTrg();

		if((trg & KEY_A) && Nv.sel.num != -1)
		{
			Nv.step++;
		}
		else if((trg & KEY_LEFT) && (LogIsEmpty() == false))
		{
			LogSetInit(LOG_RET_NOVEL);
			ManageSetLog();
			Nv.step--;
		}
		else if(trg & KEY_B)
		{
			MenuSetSystem(MENU_SYSTEM_SEL_SKIP);
			ManageSetMenu();
			Nv.step--;
		}
		else if((trg & KEY_UP) && Nv.sel.num > 0)
		{
			TxtClearXY();
			Nv.step--;
			Nv.sel.num--;
		}
		else if((trg & KEY_DOWN) && (Nv.sel.num + 1) < Nv.sel.cnt)
		{
			TxtClearXY();
			Nv.step--;
			Nv.sel.num++;
		}
		break;

	// �I���I��
	case 2:
		TxtClearXY();
		TxtSetBuf(true);
		Nv.pCur = Nv.sel.pStr[Nv.sel.num];
		NvSetCurStr();

		TxtDrawStr(Nv.str);
		TxtSetPageNew();

		Nv.pCur   = Nv.sel.pSrc;
		Nv.curAdr = Nv.sel.srcAdr;
		NvJumpCurAdr(Nv.curAdr + 1 + 2 + 2*Nv.sel.cnt + Nv.sel.jump[Nv.sel.num]);

		NvSetAct(NV_ACT_PARSE);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecRestart(void)
{
	// TODO �I�����̏ꍇ

	switch(Nv.step)
	{
	case 0:
		LogInit();
		TxtClear();
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
		TxtRestart();
		ImgRestart();

		NvSetAct(NV_ACT_KEY);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEffectBefore(u8 no)
{
	if(Nv.isSkip == true)
	{
		return;
	}

	ImgSetEffectBefore(no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEffectAfter(u8 no)
{
	if(Nv.isSkip == true)
	{
		if(no == IMG_EFFECT_TXT_ON)
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
	Nv.scnNo  = no;
	Nv.evtNo  = 0;
	Nv.msgNo  = 0;

	TRACE("\n[NvSetScn %04x.txt E%02x M%02x]\n", no, Nv.maxEvt, Nv.maxMsg);
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


	Nv.pRet = Nv.pCur;
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
	Nv.isSkip = true;
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
	// TODO �����蔯�^�ύX

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
	return (Nv.act == NV_ACT_RESTART) ? true : false;
}
