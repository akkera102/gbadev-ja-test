#include "nv.h"
#include "nv2.h"
#include "libmy/key.h"
#include "bgm.h"
#include "cur.h"
#include "file.h"
#include "img.h"
#include "log.h"
#include "manage.h"
#include "menu.h"
#include "se.h"
#include "siori.h"
#include "txt.h"

//---------------------------------------------------------------------------
ST_NV Nv;


//---------------------------------------------------------------------------
void NvInit(void)
{
	_Memset(&Nv, 0x00, sizeof(ST_NV));

	// 最新の既読フラグを読み込みます
	SioriLoadNvRead();
}
//---------------------------------------------------------------------------
void NvInitVar(void)
{
	_Memset(&Nv.var, 0x00, sizeof(Nv.var));
}
//---------------------------------------------------------------------------
void NvExec(void)
{
	if(Nv.wait != 0)
	{
		if(KeyGetCnt() & KEY_R)
		{
			Nv.wait = 0;
		}
		else
		{
			Nv.wait--;

			return;
		}
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
void NvExecKey(void)
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

		if(Nv.isPage == true)
		{
			TxtWriteBuf();
			TxtSetCls();
		}

		CurHide();

		NvSetAct(NV_ACT_PARSE);
		return;
	}

	if(trg & KEY_LEFT && LogIsEmpty() == false)
	{
		LogSetInit();
		ManageSetAct(MANAGE_ACT_LOG);

		return;
	}

	if(trg & KEY_B)
	{
		MenuSetSystem(MENU_SYSTEM_SEL_SAVE);
		ManageSetAct(MANAGE_ACT_MENU);

		return;
	}

	if(trg & KEY_L)
	{
		MenuSetNone(MENU_RET_NOVEL);
		ManageSetAct(MANAGE_ACT_MENU);

		return;
	}

	if(trg & KEY_START || trg & KEY_SELECT)
	{
		NvSetSkip();

		return;
	}
}
//---------------------------------------------------------------------------
void NvExecSel(void)
{
	switch(Nv.step)
	{
	// 項目の表示
	case 0:
		CurHide();
		TxtSetExec();

		Nv.isSkip = false;
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
			LogSetInit();
			ManageSetAct(MANAGE_ACT_LOG);

			Nv.step--;
		}
		else if(trg & KEY_B)
		{
			MenuSetSystem(MENU_SYSTEM_SEL_SAVE);
			ManageSetAct(MANAGE_ACT_MENU);

			Nv.step--;
		}
		else if(trg & KEY_L)
		{
			MenuSetNone(MENU_RET_NOVEL);
			ManageSetAct(MANAGE_ACT_MENU);

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
		// ログに選択肢を保存
		TxtWriteSel(Nv.sel.p[Nv.sel.cnt]);
		TxtClearBuf();

		Nv.pCur = Nv.pScn + Nv.sel.ofs[Nv.sel.cnt];

		NvSetAct(NV_ACT_PARSE);
		ManageSetAct(MANAGE_ACT_NV);
		break;
	}
}
//---------------------------------------------------------------------------
void NvExecLoad(void)
{
	switch(Nv.step)
	{
	case 0:
		TxtHide();
		LogInit();

		Nv.step++;
		break;

	case 1:
		SeStop();

		BgmLoadPlay();
		MenuLoadSelCol();
		ImgLoadFade();

		ImgSetExec();

		Nv.step++;
		break;

	case 2:
		NvSetAct(Nv.prev);

		// キー入力 or 選択肢
		if(Nv.act == NV_ACT_KEY)
		{
			ManageSetAct(MANAGE_ACT_RES);
		}
		else
		{
			ManageSetAct(MANAGE_ACT_SEL);
		}
		break;
	}
}
//---------------------------------------------------------------------------
void NvSetAct(s32 act)
{
	Nv.prev = Nv.act;
	Nv.act  = act;
	Nv.step = 0;
}
//---------------------------------------------------------------------------
void NvSetScn(s32 no)
{
	TRACE("\n\n[NvSetScn no:%d]\n", no);

	Nv.no         = no;
	Nv.pScn       = (char*)FileGetScn(no);
	Nv.pCur       = Nv.pScn;
	Nv.sel.reg    = NvCurNum();
	Nv.expr.cnt   = 0;
	Nv.call.isUse = false;

	if(Nv.sel.reg == 0)
	{
		return;
	}

	s32 i;

	for(i=0; i<Nv.sel.reg; i++)
	{
		Nv.sel.p[i] = NvCurStr();
		Nv.sel.ofs[i] = NvCurHex();
	}
}
//---------------------------------------------------------------------------
void NvSetSkip(void)
{
	if(NvIsRead(Nv.idx, Nv.bit) == false && Nv.isOmit == false)
	{
		return;
	}

	Nv.isSkip = true;
}
//---------------------------------------------------------------------------
void NvSetOmit(bool is)
{
	Nv.isOmit = is;
}
//---------------------------------------------------------------------------
void NvSetRead(s32 i, s32 b)
{
	_ASSERT(i < NV_MAX_READ_CNT);
	_ASSERT(b < 8);

	Nv.read[i] |= 1 << b;
}
//---------------------------------------------------------------------------
void NvSetVar(s32 no, s32 num)
{
	_ASSERT(no < NV_MAX_VAR_CNT);

	Nv.var[no] = num;
}
//---------------------------------------------------------------------------
s32 NvGetSelReg(void)
{
	return Nv.sel.reg;
}
//---------------------------------------------------------------------------
s32 NvGetSelCnt(void)
{
	return Nv.sel.cnt;
}
//---------------------------------------------------------------------------
char* NvGetSelStr(s32 no)
{
	return Nv.sel.p[no];
}
//---------------------------------------------------------------------------
s32 NvGetVar(s32 no)
{
	_ASSERT(no < NV_MAX_VAR_CNT);

	return Nv.var[no];
}
//---------------------------------------------------------------------------
s32 NvCurNum(void)
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
s32 NvCurHex(void)
{
	s32 ret = 0;

	ret += *Nv.pCur++;
	ret += *Nv.pCur++ <<  8;
	ret += *Nv.pCur++ << 16;
	ret += *Nv.pCur++ << 24;

	// skip '\0'
	Nv.pCur++;

	return ret;
}
//---------------------------------------------------------------------------
char* NvCurStr(void)
{
	char* ret = Nv.pCur;

	while(*Nv.pCur++ != '\0')
	{
		// EMPTY
	}

	return ret;
}
//---------------------------------------------------------------------------
char NvCurChr(void)
{
	char ret = *Nv.pCur++;

	// skip '\0'
	Nv.pCur++;

	return ret;
}
//---------------------------------------------------------------------------
void NvCurSkip(s32 cnt)
{
	s32 i;

	for(i=0; i<cnt; i++)
	{
		NvCurStr();
	}
}
//---------------------------------------------------------------------------
bool NvIsSkip(void)
{
	return Nv.isSkip;
}
//---------------------------------------------------------------------------
bool NvIsOmit(void)
{
	return Nv.isOmit;
}
//---------------------------------------------------------------------------
bool NvIsRead(s32 i, s32 b)
{
	_ASSERT(i < NV_MAX_READ_CNT);
	_ASSERT(b < 8);

	return (Nv.read[i] & 1 << b) ? true : false;
}
//---------------------------------------------------------------------------
bool NvIsRead2(void)
{
	return NvIsRead(Nv.idx, Nv.bit);
}
//---------------------------------------------------------------------------
bool NvIsAct(s32 act)
{
	return (Nv.act == act) ? true : false;
}
