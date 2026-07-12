#include "menu.h"
#include "libbios/swi.h"
#include "libmy/key.h"
#include "cur.h"
#include "img.h"
#include "info.h"
#include "log.h"
#include "manage.h"
#include "mus.h"
#include "navi.h"
#include "nv.h"
#include "siori.h"
#include "snd.h"
#include "txt.h"

//---------------------------------------------------------------------------
ROM_DATA char MenuStrSel[][32+1] = {
	// 0
	"",

	// 1
	"【セーブ　１／８】",

	// 2
	"【ロード　１／８】",

	// 3
	"果てしなく青い、この空の下で…。",
	"ゲームを始める",
	"続きから始める",
	"－？－",

	// 7
	"【攻略情報】",
	"なし",
	"あり　",

	// 10
	"【システム】",
	"セーブ",
	"ロード",
	"オプション",
	"デバッグ",
	"ゲーム終了",

	// 16
	"【オプション】",
	"背景輝度　００",
	"通常文字　",
	"既読文字　",
	"既読無視　",
	"攻略情報　",

	// 22
	"【デバッグ】",
	"ＢＧ　　０００",
	"ＣＨＲ　０００",
	"ＭＵＳ　０００",
	"ＳＮＤ　０００",
	"ＴＸＴ　０００",
};

ROM_DATA char MenuStrCol[][4+1] = {
	"白色",
	"水色",
	"黄色",
	"緑色",
	"赤色",
};

ROM_DATA char MenuStrOpt[][4+1] = {
	"なし",
	"あり",
};

ROM_DATA char MenuStrNavi[][6+1] = {
	"雨音",			// 0
	"悠夏",
	"藍",
	"明日菜",
	"文乃",			// 4
	"なし",			// 5
};

//---------------------------------------------------------------------------
ST_MENU Menu;


//---------------------------------------------------------------------------
void MenuInit(void)
{
	_Memset(&Menu, 0x00, sizeof(ST_MENU));
}
//---------------------------------------------------------------------------
void MenuExec(void)
{
	u16 trg = KeyGetTrg();
	u16 rep = KeyGetRep();

	if(trg & KEY_DOWN)
	{
		if((Menu.sel+1) < Menu.reg)
		{
			Menu.sel++;
		}
		else
		{
			Menu.sel = 0;
		}

		TxtSetExec();
		return;
	}

	if(trg & KEY_UP)
	{
		if(Menu.sel != 0)
		{
			Menu.sel--;
		}
		else
		{
			Menu.sel = Menu.reg - 1;
		}

		TxtSetExec();
		return;
	}

	Menu.pFunc(trg, rep);
}
//---------------------------------------------------------------------------
void MenuExecNone(u16 trg, u16 rep)
{
	if(trg & KEY_B || trg & KEY_L)
	{
		NvSetActRest();

		return;
	}
}
//---------------------------------------------------------------------------
void MenuExecSave(u16 trg, u16 rep)
{
	if(trg & KEY_B)
	{
		Menu.no = Menu.sel;
		MenuSetSystem(MENU_SYSTEM_SEL_SAVE);

		return;
	}

	if((trg & KEY_LEFT) || (trg & KEY_L))
	{
		Menu.page = InfoGetIdxLoop(Menu.page, -1, 8);
		TxtSetExec();

		return;
	}

	if((trg & KEY_RIGHT) || (trg & KEY_R))
	{
		Menu.page = InfoGetIdxLoop(Menu.page, 1, 8);
		TxtSetExec();

		return;
	}

	if(trg & KEY_A)
	{
		Menu.no = Menu.sel;
		SioriSaveItem(Menu.page * SIORI_MAX_ITEM_CNT + Menu.sel);
		NvSetActRest();

		return;
	}
}
//---------------------------------------------------------------------------
void MenuExecLoad(u16 trg, u16 rep)
{
	if(trg & KEY_B)
	{
		Menu.no = Menu.sel;

		if(Menu.var == MENU_TYPE_SYSTEM)
		{
			MenuSetSystem(MENU_SYSTEM_SEL_LOAD);
		}
		else
		{
			MenuSetTitle(MENU_TITLE_SEL_LOAD);
		}

		return;
	}

	if((trg & KEY_LEFT) || (trg & KEY_L))
	{
		Menu.page = InfoGetIdxLoop(Menu.page, -1, 8);
		TxtSetExec();

		return;
	}

	if((trg & KEY_RIGHT) || (trg & KEY_R))
	{
		Menu.page = InfoGetIdxLoop(Menu.page, 1, 8);
		TxtSetExec();

		return;
	}

	if(!(trg & KEY_A))
	{
		return;
	}

	if(SioriIsItem(Menu.page * SIORI_MAX_ITEM_CNT + Menu.sel) == false)
	{
		return;
	}

	Menu.no = Menu.sel;
	SioriLoadItem(Menu.page * SIORI_MAX_ITEM_CNT + Menu.sel);

	LogInit();
	SndLoad();
	MusLoad();
	TxtLoad();
	NvLoad();

	NvSetOmake(false);
	NvSetDbg(false);
}
//---------------------------------------------------------------------------
void MenuExecTitle(u16 trg, u16 rep)
{
	if(!(trg & KEY_A))
	{
		return;
	}

	switch(Menu.sel)
	{
	// ゲームを始める
	case 0:
		MenuSetNavi();
		break;

	// 続きから始める
	case 1:
		MenuSetLoad(MENU_TYPE_TITLE);
		break;

	// －？－
	case 2:
		NvSetOmake(true);
		NvSetNavi(5);
		NvSetTxt(612);

		NvSetAct(NV_ACT_PARSE);
		ManageSetAct(MANAGE_ACT_NV);
		break;
	}
}
//---------------------------------------------------------------------------
void MenuExecNavi(u16 trg, u16 rep)
{
	if(trg & KEY_B)
	{
		MenuSetTitle(MENU_TITLE_SEL_START);

		return;
	}

	switch(Menu.sel)
	{
	// ナビなし
	case 0:
		if(trg & KEY_A)
		{
			NvSetNavi(5);

Start:
//			TRACE("[MenuExecNavi navi:%d]\n", NvGetNavi());

			NvSetTxt(1);
			NvSetAct(NV_ACT_PARSE);

			ImgSetExec(IMG_EFFECT_BLACK_IN);
			ManageSetAct(MANAGE_ACT_NV);
		}
		break;

	// ナビあり（キャラ別指定）
	case 1:
		if(trg & KEY_LEFT)
		{
			s32 n = InfoGetIdxClmp(NvGetNavi(), -1, 5);

			NvSetNavi(n);
			TxtSetExec();
			return;
		}

		if(trg & KEY_RIGHT)
		{
			s32 n = InfoGetIdxClmp(NvGetNavi(), 1, 5);

			NvSetNavi(n);
			TxtSetExec();
			return;
		}

		if(trg & KEY_A)
		{
			goto Start;
		}
		break;
	}
}
//---------------------------------------------------------------------------
void MenuExecSystem(u16 trg, u16 rep)
{
	if(trg & KEY_B)
	{
		Menu.sys = Menu.sel;

		NvSetActRest();
		return;
	}

	if(!(trg & KEY_A))
	{
		return;
	}

	Menu.sys = Menu.sel;

	switch(Menu.sel)
	{
	// セーブ
	case 0:
		if(NvIsDbg() == false && NvIsOmake() == false)
		{
			MenuSetSave();
		}
		break;

	// ロード
	case 1:
		MenuSetLoad(MENU_TYPE_SYSTEM);
		break;

	// オプション
	case 2:
		MenuSetOption();
		break;

	// デバッグ
	case 3:
		MenuSetDebug();
		break;

	// ゲーム終了
	case 4:
		MusStop();
		SndStop();

		NvSetOmake(false);
		NvSetDbg(false);
		NvSetNavi(0);

		ImgSetBg(5);
		ImgSetChr(800);
		ImgSetExec(IMG_EFFECT_LOAD);

		ManageSetAct(MANAGE_ACT_EXIT);
		break;
	}
}
//---------------------------------------------------------------------------
void MenuExecOption(u16 trg, u16 rep)
{
	if(trg & KEY_B)
	{
		Menu.opt = Menu.sel;

		MenuSetSystem(MENU_SYSTEM_SEL_OPTION);
		return;
	}

	switch(Menu.sel)
	{
	// 背景輝度
	case 0:
		s32 fade = ImgGetFade();

		if(trg & KEY_LEFT && fade > 0)
		{
			fade--;

			ImgSetFade(fade);
			TxtSetExec();
		}

		if(trg & KEY_RIGHT && fade < 16)
		{
			fade++;

			ImgSetFade(fade);
			TxtSetExec();
		}
		break;

	// 通常文字
	case 1:
		s32 b = TxtGetBaseNo();

		if(trg & KEY_LEFT && b > 0)
		{
			b--;

			TxtSetBaseNo(b);
			TxtSetExec();
		}

		if(trg & KEY_RIGHT && b < 5-1)
		{
			b++;

			TxtSetBaseNo(b);
			TxtSetExec();
		}
		break;

	// 既読文字
	case 2:
		s32 r = TxtGetReadNo();

		if(trg & KEY_LEFT && r > 0)
		{
			r--;

			TxtSetReadNo(r);
			TxtSetExec();
		}

		if(trg & KEY_RIGHT && r < 5-1)
		{
			r++;

			TxtSetReadNo(r);
			TxtSetExec();
		}
		break;

	// 既読無視
	case 3:
		if(trg & KEY_LEFT || trg & KEY_RIGHT)
		{
			if(NvIsPass() == true)
			{
				NvSetPass(false);
			}
			else
			{
				NvSetPass(true);
			}

			TxtSetExec();
		}
		break;

	// 攻略情報
	case 4:
		// EMPTY
		break;
	}
}
//---------------------------------------------------------------------------
void MenuExecDebug(u16 trg, u16 rep)
{
	if(trg & KEY_B)
	{
		Menu.dbg = Menu.sel;

		MenuSetSystem(MENU_SYSTEM_SEL_DEBUG);
		return;
	}

	switch(Menu.sel)
	{
	// BG
	case 0:
		if(rep & KEY_L)
		{
			Menu.bg = InfoGetBg(Menu.bg, -10);
			TxtSetExec();
		}

		if(rep & KEY_R)
		{
			Menu.bg = InfoGetBg(Menu.bg, 10);
			TxtSetExec();
		}

		if(rep & KEY_LEFT)
		{
			Menu.bg = InfoGetBg(Menu.bg, -1);
			TxtSetExec();
		}

		if(rep & KEY_RIGHT)
		{
			Menu.bg = InfoGetBg(Menu.bg, 1);
			TxtSetExec();
		}

		if(trg & KEY_A)
		{
			ImgSetBg(Menu.bg);
			ImgSetChr(0);
			ImgSetExecCond(IMG_EFFECT_NORMAL);
		}
		break;

	// CHR
	case 1:
		if(rep & KEY_L)
		{
			Menu.chr = InfoGetChr(Menu.chr, -10);
			TxtSetExec();
		}

		if(rep & KEY_R)
		{
			Menu.chr = InfoGetChr(Menu.chr, 10);
			TxtSetExec();
		}

		if(rep & KEY_LEFT)
		{
			Menu.chr = InfoGetChr(Menu.chr, -1);
			TxtSetExec();
		}

		if(rep & KEY_RIGHT)
		{
			Menu.chr = InfoGetChr(Menu.chr, 1);
			TxtSetExec();
		}

		if(trg & KEY_A)
		{
			ImgSetChr(Menu.chr);
			ImgSetExecCond(IMG_EFFECT_NORMAL);
		}
		break;

	// MUS
	case 2:
		if(rep & KEY_L)
		{
			Menu.mus = InfoGetMus(Menu.mus, -10);
			TxtSetExec();
		}

		if(rep & KEY_R)
		{
			Menu.mus = InfoGetMus(Menu.mus, 10);
			TxtSetExec();
		}

		if(rep & KEY_LEFT)
		{
			Menu.mus = InfoGetMus(Menu.mus, -1);
			TxtSetExec();
		}

		if(rep & KEY_RIGHT)
		{
			Menu.mus = InfoGetMus(Menu.mus, 1);
			TxtSetExec();
		}

		if(trg & KEY_A)
		{
			if(Menu.mus == 0)
			{
				MusStop();
			}
			else
			{
				MusPlay(Menu.mus, true);
			}
		}
		break;

	// SND
	case 3:
		if(rep & KEY_L)
		{
			Menu.snd = InfoGetSnd(Menu.snd, -10);
			TxtSetExec();
		}

		if(rep & KEY_R)
		{
			Menu.snd = InfoGetSnd(Menu.snd, 10);
			TxtSetExec();
		}

		if(rep & KEY_LEFT)
		{
			Menu.snd = InfoGetSnd(Menu.snd, -1);
			TxtSetExec();
		}

		if(rep & KEY_RIGHT)
		{
			Menu.snd = InfoGetSnd(Menu.snd, 1);
			TxtSetExec();
		}

		if(trg & KEY_A)
		{
			if(Menu.snd == 0)
			{
				SndStop();
			}
			else
			{
				SndPlay(Menu.snd, false);
			}
		}
		break;

	// TXT
	case 4:
		if(rep & KEY_L)
		{
			Menu.txt = InfoGetTxt(Menu.txt, -10);
			TxtSetExec();
		}

		if(rep & KEY_R)
		{
			Menu.txt = InfoGetTxt(Menu.txt, 10);
			TxtSetExec();
		}

		if(rep & KEY_LEFT)
		{
			Menu.txt = InfoGetTxt(Menu.txt, -1);
			TxtSetExec();
		}

		if(rep & KEY_RIGHT)
		{
			Menu.txt = InfoGetTxt(Menu.txt, 1);
			TxtSetExec();
		}

		if(trg & KEY_A && Menu.txt != 0)
		{
			Menu.dbg = Menu.sel;

			MusStop();
			SndStop();

			NvSetOmake(false);
			NvSetDbg(true);
			NvSetNavi(5);


			NvSetTxt(Menu.txt);
			NvSetAct(NV_ACT_PARSE);

			ImgSetExec(IMG_EFFECT_BLACK_IN);
			ManageSetAct(MANAGE_ACT_NV);
		}
		break;
	}
}
//---------------------------------------------------------------------------
void MenuSetInit(s32 type, s32 ret, s32 sel, s32 msg, s32 reg, s32 var, void* pFunc, bool isShow)
{
	Menu.type  = type;
	Menu.sel   = sel;
	Menu.msg   = msg;
	Menu.reg   = reg;
	Menu.var   = var;
	Menu.pFunc = pFunc;

	if(isShow == true)
	{
		ImgSetExecCond(IMG_EFFECT_SET_MSG);
		TxtSetExec();
	}
	else
	{
		ImgSetExecCond(IMG_EFFECT_CLR_MSG);
	}

	CurHide();
	NaviHide();
}
//---------------------------------------------------------------------------
void MenuSetInit2(s32 type, s32 ret, s32 sel, s32 msg, s32 reg, s32 var, void* pFunc)
{
	Menu.type  = type;
	Menu.sel   = sel;
	Menu.msg   = msg;
	Menu.reg   = reg;
	Menu.var   = var;
	Menu.pFunc = pFunc;

	CurHide();
	NaviHide();
}
//---------------------------------------------------------------------------
void MenuSetNone(void)
{
	MenuSetInit(MENU_TYPE_NONE, 0, 0, 0, 0, 0, MenuExecNone, false);
}
//---------------------------------------------------------------------------
void MenuSetSave(void)
{
	MenuSetInit(MENU_TYPE_SAVE, 0, Menu.no, 1, 5, 0, MenuExecSave, true);
}
//---------------------------------------------------------------------------
void MenuSetLoad(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, Menu.no, 2, 5, ret, MenuExecLoad, true);
}
//---------------------------------------------------------------------------
void MenuSetTitle(s32 sel)
{
	MenuSetInit(MENU_TYPE_TITLE, 0, sel, 3, 3, 0, MenuExecTitle, true);
}
//---------------------------------------------------------------------------
void MenuSetTitle2(s32 sel)
{
	MenuSetInit2(MENU_TYPE_TITLE, 0, sel, 3, 3, 0, MenuExecTitle);
}
//---------------------------------------------------------------------------
void MenuSetNavi(void)
{
	MenuSetInit(MENU_TYPE_NAVI, 0, 0, 7, 2, 0, MenuExecNavi, true);
}
//---------------------------------------------------------------------------
void MenuSetSystem(s32 sel)
{
	MenuSetInit(MENU_TYPE_SYSTEM, 0, sel, 10, 5, 0, MenuExecSystem, true);
}
//---------------------------------------------------------------------------
void MenuSetSystem2(void)
{
	MenuSetInit(MENU_TYPE_SYSTEM, 0, Menu.sys, 10, 5, 0, MenuExecSystem, true);
}
//---------------------------------------------------------------------------
void MenuSetOption(void)
{
	MenuSetInit(MENU_TYPE_OPTION, 0, Menu.opt, 16, 5, 0, MenuExecOption, true);
}
//---------------------------------------------------------------------------
void MenuSetDebug(void)
{
	MenuSetInit(MENU_TYPE_DEBUG, 0, Menu.dbg, 22, 5, 0, MenuExecDebug, true);
}
//---------------------------------------------------------------------------
char* MenuGetStrTitle(void)
{
	switch(Menu.type)
	{
	case MENU_TYPE_SAVE:
	case MENU_TYPE_LOAD:
		_Strncpy(Menu.buf, MenuStrSel[Menu.msg], MENU_BUF_SIZE);
		// SJIS「０」0x82 0x4f
		Menu.buf[11] += Menu.page;

		return Menu.buf;
	}

	return (char*)MenuStrSel[Menu.msg];
}
//---------------------------------------------------------------------------
char* MenuGetStrSel(s32 sel)
{
	switch(Menu.type)
	{
	case MENU_TYPE_SAVE:
	case MENU_TYPE_LOAD:
		return SioriGetTitle(Menu.page * SIORI_MAX_ITEM_CNT + sel);

	case MENU_TYPE_OPTION:
		return MenuGetStrSelOpt(sel);

	case MENU_TYPE_DEBUG:
		return MenuGetStrSelDbg(sel);

	case MENU_TYPE_NAVI:
		return MenuGetStrSelNavi(sel);
	}

	return (char*)MenuStrSel[Menu.msg + 1 + sel];
}
//---------------------------------------------------------------------------
char* MenuGetStrSelOpt(s32 sel)
{
	_Strncpy(Menu.buf, (char*)MenuStrSel[Menu.msg + 1 + sel], MENU_BUF_SIZE);

	s32 n;

	switch(sel)
	{
	// "背景輝度　００"
	case 0:
		n = ImgGetFade();

		// SJIS「０」0x82 0x4f
		Menu.buf[11] = 0x4f + SwiDiv(n, 10);
		Menu.buf[13] = 0x4f + SwiDivMod(n, 10);
		break;

	// "通常文字　"
	case 1:
		n = TxtGetBaseNo();
		_Strcat(Menu.buf, MenuStrCol[n]);
		break;

	// "既読文字　"
	case 2:
		n = TxtGetReadNo();
		_Strcat(Menu.buf, MenuStrCol[n]);
		break;

	// "既読無視　"
	case 3:
		n = (NvIsPass() == true) ? 1 : 0;
		_Strcat(Menu.buf, MenuStrOpt[n]);
		break;

	// "攻略情報　"
	case 4:
		_Strcat(Menu.buf, MenuStrNavi[NvGetNavi()]);
		break;
	}

	return Menu.buf;
}
//---------------------------------------------------------------------------
char* MenuGetStrSelDbg(s32 sel)
{
	_Strncpy(Menu.buf, (char*)MenuStrSel[Menu.msg + 1 + sel], MENU_BUF_SIZE);

	s32 n = 0;

	switch(sel)
	{
	case 0: n = Menu.bg;  break;
	case 1: n = Menu.chr; break;
	case 2: n = Menu.mus; break;
	case 3: n = Menu.snd; break;
	case 4: n = Menu.txt; break;
	}

	// SJIS「０」0x82 0x4f
	Menu.buf[ 9] += SwiDiv(n, 100);
	Menu.buf[11] += SwiDivMod(SwiDiv(n, 10), 10);
	Menu.buf[13] += SwiDivMod(n, 10);

	return Menu.buf;
}
//---------------------------------------------------------------------------
char* MenuGetStrSelNavi(s32 sel)
{
	_Strncpy(Menu.buf, (char*)MenuStrSel[Menu.msg + 1 + sel], MENU_BUF_SIZE);

	if(sel == 1)
	{
		_Strcat(Menu.buf, MenuStrNavi[NvGetNavi()]);
	}

	return Menu.buf;
}
//---------------------------------------------------------------------------
s32 MenuGetReg(void)
{
	return Menu.reg;
}
//---------------------------------------------------------------------------
s32 MenuGetSel(void)
{
	return Menu.sel;
}
