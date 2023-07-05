#include "menu.h"
#include "libmy/key.h"
#include "manage.h"
#include "txt.h"
#include "siori.h"
#include "nv.h"
#include "log.h"
#include "img.h"
#include "bgm.h"
#include "se.h"


//---------------------------------------------------------------------------
const char MenuSelectStr[18][30] = {
	// 0
	"－　システムメニュー　－",
	"　文字送り",
	"　文字を消す",
	"　シナリオ回想",
	"　セーブ",
	"　ロード",
	"　オプション",
	"　ゲーム終了",

	// 8
	"　－　システム設定　－",
	"　文字ウェイト　００",
	"　背景輝度　　　００",

	// 11
	"　　　－　セーブ　－",

	// 12
	"　　　－　ロード　－",

	// 13
	"",
};

//---------------------------------------------------------------------------
ST_MENU Menu;


//---------------------------------------------------------------------------
EWRAM_CODE void MenuInit(void)
{
	_Memset(&Menu, 0x00, sizeof(ST_MENU));
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExec(void)
{
	u16 trg = KeyGetTrg();
	u16 rep = KeyGetRep();

	if(trg & KEY_A || trg & KEY_B || trg & KEY_LEFT || trg & KEY_RIGHT)
	{
		Menu.pFunc(trg);
		return;
	}

	if(rep & KEY_DOWN)
	{
		if((Menu.sel+1) < Menu.reg)
		{
			Menu.sel++;
		}
		else
		{
			Menu.sel = 0;
		}

		Menu.isDraw = true;
	}

	if(rep & KEY_UP)
	{
		if(Menu.sel != 0)
		{
			Menu.sel--;
		}
		else
		{
			Menu.sel = Menu.reg - 1;
		}

		Menu.isDraw = true;
	}


	if(Menu.isDraw == true)
	{
		Menu.isDraw = false;

		TxtSetCur(false);
		TxtSetChr();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecSystem(u16 trg)
{
	if(trg & KEY_B)
	{
		TxtSetChr();
		TxtSetRes();

		ManageSetNovel();
		return;
	}

	if(!(trg & KEY_A))
	{
		return;
	}

	switch(Menu.sel)
	{
	// 文字送り
	case 0:
		NvSetNext();

		TxtSetChr();
		TxtSetRes();

		ManageSetNovel();
		break;

	// 文字を消す
	case 1:
		TxtHideWindow();
		MenuSetNone();
		break;

	// シナリオ回想
	case 2:
		if(LogIsEmpty() == false)
		{
			LogSetInit(LOG_RET_SYSTEM);
			ManageSetLog();
		}
		break;

	// セーブ
	case 3:
		MenuSetSave(MENU_RET_SYSTEM);
		break;

	// ロード
	case 4:
		MenuSetLoad(MENU_RET_SYSTEM);
		break;

	// オプション
	case 5:
		MenuSetOption();
		break;

	// ゲーム終了
	case 6:
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecOption(u16 trg)
{
	if(trg & KEY_B)
	{
		MenuSetSystem(MENU_SYSTEM_SEL_OPTION);

		return;
	}

	switch(Menu.sel)
	{
	// 文字ウェイト
	case 0: ;
		s32 wait = TxtGetWaitMax();

		if(trg & KEY_LEFT && wait != 0)
		{
			wait--;
			TxtSetWaitMax(wait);
			Menu.isDraw = true;
		}

		if(trg & KEY_RIGHT && wait < 3)
		{
			wait++;
			TxtSetWaitMax(wait);
			Menu.isDraw = true;
		}
		break;

	// 背景輝度
	case 1: ;
		s32 fade = ImgGetFadeMax();

		if(trg & KEY_LEFT && fade != 0)
		{
			fade--;
			ImgSetFadeMax(fade);
			Menu.isDraw = true;
		}

		if(trg & KEY_RIGHT && fade < 16)
		{
			fade++;
			ImgSetFadeMax(fade);
			Menu.isDraw = true;
		}
		break;

	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecSave(u16 trg)
{
	if(trg & KEY_B)
	{
		MenuSetSystem(MENU_SYSTEM_SEL_SAVE);

		return;
	}

	if(trg & KEY_A)
	{
		SioriSave(Menu.sel);

		TxtSetChr();
		TxtSetRes();

		ManageSetNovel();
		return;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecLoad(u16 trg)
{
	if(trg & KEY_B)
	{
		MenuSetSystem(MENU_SYSTEM_SEL_LOAD);

		return;
	}

	if(!(trg & KEY_A))
	{
		return;
	}

	if(SioriLoad(Menu.sel) == false)
	{
		return;
	}

	NvSetAct(NV_ACT_RESTART);
	ManageSetNovel();
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecNone(u16 trg)
{
	if(trg & KEY_B)
	{
		MenuSetSystem(MENU_SYSTEM_SEL_NONE);
		TxtShowWindow();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetInit(s32 type, s32 ret, s32 sel, s32 msg, s32 reg, void* pFunc, bool isDraw)
{
	Menu.type   = type;
	Menu.ret    = ret;
	Menu.sel    = sel;
	Menu.msg    = msg;
	Menu.reg    = reg;
	Menu.pFunc  = pFunc;
	Menu.isDraw = isDraw;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSystem(s32 sel)
{
	MenuSetInit(MENU_TYPE_SYSTEM, MENU_RET_NONE, sel, 0, 7, MenuExecSystem, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetOption(void)
{
	MenuSetInit(MENU_TYPE_OPTION, MENU_RET_SYSTEM, 0, 8, 2, MenuExecOption, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSave(s32 ret)
{
	MenuSetInit(MENU_TYPE_SAVE, ret, 0, 11, 8, MenuExecSave, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetLoad(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, 0, 12, 8, MenuExecLoad, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void  MenuSetNone(void)
{
	MenuSetInit(MENU_TYPE_LOAD, MENU_RET_NONE, 0, 13, 0, MenuExecNone, false);
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetSelStr(s32 sel)
{
	if(sel != 0 && (Menu.type == MENU_TYPE_SAVE || Menu.type == MENU_TYPE_LOAD))
	{
		return SioriGetStr(sel - 1);
	}

	if((sel == 1 || sel == 2) && Menu.type == MENU_TYPE_OPTION)
	{
		_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + sel], MENU_BUF_SIZE-1);

		s32 max;

		if(sel == 1)
		{
			max = TxtGetWaitMax();
		}
		else
		{
			max = ImgGetFadeMax();
		}

		// 0x82 0x4f = SJISコード「０」
		Menu.buf[17] = 0x4f + Div(max, 10);
		Menu.buf[19] = 0x4f + DivMod(max, 10);

		return Menu.buf;
	}

	return (char*)MenuSelectStr[Menu.msg + sel];
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 MenuGetSel(void)
{
	return Menu.sel;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 MenuGetReg(void)
{
	return Menu.reg;
}
