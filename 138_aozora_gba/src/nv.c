#include "nv.h"
#include "nv2.h"
#include "nv3.h"
#include "libmy/key.h"
#include "cur.h"
#include "file.h"
#include "img.h"
#include "info.h"
#include "log.h"
#include "manage.h"
#include "menu.h"
#include "mus.h"
#include "seen.h"
#include "siori.h"
#include "snd.h"
#include "txt.h"

//---------------------------------------------------------------------------
ST_NV Nv;


//---------------------------------------------------------------------------
void NvInit(void)
{
	_Memset(&Nv, 0x00, sizeof(ST_NV));
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

	case NV_ACT_JUMP:
		NvExecJump();
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

		CurHide();
		TxtAddLog();

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
		MenuSetSystem2();
		ManageSetAct(MANAGE_ACT_MENU);

		return;
	}

	if(trg & KEY_L)
	{
		MenuSetNone();
		ManageSetAct(MANAGE_ACT_MENU);

		return;
	}

	if(trg & KEY_START)
	{
		NvSetSkip();

		return;
	}

	if(trg & KEY_SELECT)
	{
		NvSetSkip();

		if(Nv.isSkip == true)
		{
			LogInit();
			CurHide();

			NvSetAct(NV_ACT_JUMP);
		}

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

		if(Nv.navi < 5)
		{
			ImgShowNavi(InfoGetNavi(Nv.navi, Nv.naviCnt));
		}

		TxtSetExec();
		ImgSetExecCond(IMG_EFFECT_SET_MSG);
		ImgSetNoWait();

		Nv.isSkip = false;
		Nv.step++;
		break;

	// 選択中
	case 1: ;
		u16 trg = KeyGetTrg();

		if(((trg & KEY_A) || (trg & KEY_RIGHT)) && Nv.sel.cnt != -1)
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
			MenuSetSystem2();
			ManageSetAct(MANAGE_ACT_MENU);

			Nv.step--;
		}
		else if(trg & KEY_L)
		{
			MenuSetNone();
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
	case 2: ;
//		TRACE("%d\n", Nv.sel.cnt);

		ImgHideNavi();

		if(Nv.navi < 5 && InfoGetNavi(Nv.navi, Nv.naviCnt) == Nv.sel.cnt)
		{
			Nv.naviCnt++;
		}
		else
		{
			Nv.navi = 5;
		}

		Nv.cur = Nv.sel.pos[Nv.sel.cnt];
		TxtAddLog2(Nv.p + Nv.cur + 4);

		NvSetAct(NV_ACT_PARSE);
		ManageSetAct(MANAGE_ACT_NV);
		break;
	}
}
//---------------------------------------------------------------------------
void NvSetAct(s32 act)
{
	Nv.act  = act;
	Nv.step = 0;
}
//---------------------------------------------------------------------------
void NvSetActRest(void)
{
	if(Nv.act == NV_ACT_SEL)
	{
		ManageSetAct(MANAGE_ACT_SEL);
	}
	else
	{
		ImgSetExecCond(IMG_EFFECT_SET_MSG);
		ImgSetNoWait();
		CurSetExec();
		TxtSetExec();

		ManageSetAct(MANAGE_ACT_NV);
	}
}
//---------------------------------------------------------------------------
void NvSetTxt(s32 no)
{
	TRACE("[NvSetTxt no:%d]\n", no);

	Nv.no    = no;
	Nv.p     = FileGetTxt(no);
	Nv.size  = FileGetTxtSize();
	Nv.cur   = 0;
	Nv.str   = 0;
	Nv.set   = 0;
	Nv.mes   = 0;
	Nv.idx   = 0;
	Nv.bit   = 0;
}
//---------------------------------------------------------------------------
void NvSetTxt2(s32 no)
{
	SeenSetRead(Nv.idx, Nv.bit);

	NvSetTxt(no);
}
//---------------------------------------------------------------------------
void NvSetSkip(void)
{
	if(SeenIsRead(Nv.idx, Nv.bit) == false && Nv.isRead == false)
	{
		return;
	}

	Nv.isSkip = true;
}
//---------------------------------------------------------------------------
void NvSetRead(bool is)
{
	Nv.isRead = is;
}
//---------------------------------------------------------------------------
void NvSetDbg(bool is)
{
	Nv.isDbg = is;
}
//---------------------------------------------------------------------------
void NvSetNavi(s32 no)
{
	Nv.navi = no;
	Nv.naviCnt = 0;
}
//---------------------------------------------------------------------------
s32 NvGetNavi(void)
{
	return Nv.navi;
}
//---------------------------------------------------------------------------
char* NvGetCur(void)
{
	return Nv.p + Nv.cur;
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
	return Nv.p + Nv.sel.pos[no] + 4;
}
//---------------------------------------------------------------------------
s32 NvCurNum(void)
{
	s32 ret = 0;

	do {
		ret = (ret * 10) + (Nv.p[Nv.cur++] - '0');

	} while(_IsDigit(Nv.p[Nv.cur]) == true);


	// skip '\0'
	Nv.cur++;

	return ret;
}
//---------------------------------------------------------------------------
s32 NvCurNum1(void)
{
	s32 ret = Nv.p[Nv.cur++] - '0';

	if(Nv.p[Nv.cur] == '\0')
	{
		Nv.cur++;
	}

	return ret;
}
//---------------------------------------------------------------------------
s32 NvCurNum3(void)
{
	s32 a = NvCurNum1() * 100;
	s32 b = NvCurNum1() *  10;
	s32 c = NvCurNum1();

	return a + b + c;
}
//---------------------------------------------------------------------------
u32 NvCurHex1(void)
{
	u32 c = (u8)Nv.p[Nv.cur++];

	if(Nv.p[Nv.cur] == '\0')
	{
		Nv.cur++;
	}

	if(_IsDigit(c) == true)
	{
		return c - '0';
	}

	return 10 + c - 'A';		// 必ず大文字
}
//---------------------------------------------------------------------------
u32 NvCurHex4(void)
{
	u32 a = NvCurHex1() << 12;
	u32 b = NvCurHex1() <<  8;
	u32 c = NvCurHex1() <<  4;
	u32 d = NvCurHex1();

	return a + b + c + d;
}
//---------------------------------------------------------------------------
char* NvCurStr(void)
{
	char* ret = Nv.p + Nv.cur;

	while(Nv.p[Nv.cur++] != '\0')
	{
		// EMPTY
	}

	return ret;
}
//---------------------------------------------------------------------------
char NvCurChr(void)
{
	char ret = Nv.p[Nv.cur++];

	if(Nv.p[Nv.cur] == '\0')
	{
		Nv.cur++;
	}

	return ret;
}
//---------------------------------------------------------------------------
s32 NvCurChrNum3(char chr)
{
	if(Nv.p[Nv.cur] != chr)
	{
		SystemError("[Err] NvCurChrNum3 %c(%x)\n", chr, chr);
	}

	Nv.cur++;

	return NvCurNum3();
}
//---------------------------------------------------------------------------
void NvCurSkip(void)
{
	NvCurStr();
}
//---------------------------------------------------------------------------
void NvCurSkipIf(void)
{
	TRACE("[NvCurSkipIf]\n");

	s32 nest = 0;

	for(;;)
	{
		char* p = NvCurStr();

//		TRACE("[NvCurSkipIf] %d %s\n", nest, p);

		if(_Strncmp(p, "IFE", 3) == 0 && nest == 0)
		{
			return;
		}

		if(_Strncmp(p, "IFE", 3) == 0)
		{
			nest--;

			continue;
		}

		if(_Strncmp(p, "IF0", 3) == 0)
		{
			nest++;

			continue;
		}
	}
}
//---------------------------------------------------------------------------
void NvLoad(void)
{
	TRACE("[NvLoad no:%d]\n", Nv.no);

	Nv.p    = FileGetTxt(Nv.no);
	Nv.size = FileGetTxtSize();

	// 復旧：選択肢 or メッセージ表示
	if(Nv.act == NV_ACT_SEL)
	{
		Nv.cur = Nv.set;

		ImgSetExec(IMG_EFFECT_BLACK_IN);
		NvSetAct(NV_ACT_PARSE);
	}
	else
	{
		Nv.cur = Nv.str;

		NvExecParseSjisSub();

		ImgSetExec(IMG_EFFECT_LOAD);
		NvSetAct(NV_ACT_KEY);
	}

	ManageSetAct(MANAGE_ACT_NV);
}
//---------------------------------------------------------------------------
bool NvIsDbg(void)
{
	return Nv.isDbg;
}
//---------------------------------------------------------------------------
bool NvIsSkip(void)
{
	return Nv.isSkip;
}
//---------------------------------------------------------------------------
bool NvIsRead(void)
{
	return Nv.isRead;
}
//---------------------------------------------------------------------------
bool NvIsReadSeen(void)
{
	return SeenIsRead(Nv.idx, Nv.bit);
}
//---------------------------------------------------------------------------
bool NvIsCurSjis(void)
{
	char c = Nv.p[Nv.cur];

	return ((c >= 0x81 && c <= 0x9F) || (c >= 0xE0 && c <= 0xFC)) ? true : false;
}
//---------------------------------------------------------------------------
bool NvIsSelItem(s32 pos)
{
	// skip "CAS "
	pos += 4;

	// 可変選択肢は','あり
	char* p = _Strchr(Nv.p + pos, ',');

	if(p == NULL)
	{
		return true;
	}

	// skip ','
	p++;

	bool is = false;

	if(*p == '!')
	{
		is = true;
		p++;
	}

	// skip "FL"
	p += 2;

	// nnn
	s32 n = 0;

	n += (*p++ - '0') * 100;
	n += (*p++ - '0') *  10;
	n += (*p++ - '0');

	// 必ずFL
	n = SeenGetFl(n);

	if(is == true)
	{
		n = !n;
	}

	return (n == 1) ? true : false;
}
