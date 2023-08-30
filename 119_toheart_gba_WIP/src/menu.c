#include "menu.h"
#include "libmy/key.h"
#include "manage.h"
#include "txt.h"
#include "siori.h"
#include "nv.h"
#include "log.h"
#include "img.h"


//---------------------------------------------------------------------------
ROM_DATA char MenuSelectStr[][30] = {
	// 0
	"０月００日　曜日",
	"　　文字送り",
	"　　文字を消す",
	"　　シナリオ回想",
	"　　セーブ",
	"　　ロード",
	"　　オプション",
	"　　ゲーム終了",

	// 8
	"　システム設定",
	"　文字ウェイト　００",
	"　背景輝度　　　００",
	"　好感度１",
	"　好感度２",
	"　おまけ",

	// 14
	"　　　セーブ",

	// 15
	"　　　ロード",

	// 16
	"",

	// 17
	"",
	"ゲームを始める",
	"ロードする",

	// 20
	"　　好感度１",
	"　神岸あかり　００",
	"　来栖川芹香　００",
	"　保科智子　　００",
	"　長岡志保　　００",
	"　松原葵　　　００",
	"　マルチ　　　００",
	"　姫川琴音　　００",
	"　宮内レミィ　００",

	// 29
	"　　好感度２",
	"　雛山理緒　　００",
	"　あ芹智志葵マ琴レ雅理お",
	"　×××××××××××",
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

	if(trg & KEY_A || trg & KEY_B || trg & KEY_LEFT || trg & KEY_RIGHT || trg & KEY_L || trg & KEY_R)
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

		TxtSetChr();
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
			LogSetDisp(LOG_RET_SYSTEM);

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
		MenuSetOption(MENU_OPTION_SEL_WAIT);
		break;

	// ゲーム終了
	case 6:
		ManageSetInit();
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
			TxtSetChr();
		}

		if(trg & KEY_RIGHT && wait < 3)
		{
			wait++;

			TxtSetWaitMax(wait);
			TxtSetChr();
		}
		break;

	// 背景輝度
	case 1: ;
		s32 fade = ImgGetFadeMax();

		if(trg & KEY_LEFT && fade != 0)
		{
			fade--;

			ImgSetFadeMax(fade);
			TxtSetChr();
		}

		if(trg & KEY_RIGHT && fade < 16)
		{
			fade++;

			ImgSetFadeMax(fade);
			TxtSetChr();
		}
		break;

	// デバッグ１
	case 2:
		if(trg & KEY_A)
		{
			MenuSetDebug1();
		}
		break;

	// デバッグ２
	case 3:
		if(trg & KEY_A)
		{
			MenuSetDebug2();
		}
		break;

	// おまけ
	case 4:
		// TODO
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecDebug1(u16 trg)
{
	if(trg & KEY_B)
	{
		MenuSetOption(MENU_OPTION_SEL_DEBUG1);

		return;
	}

	if(!(trg & KEY_RIGHT || trg & KEY_R || trg & KEY_LEFT || trg & KEY_L))
	{
		return;
	}

	s8 flag = NvGetFlag(0x14 + Menu.sel);

	if(trg & KEY_RIGHT) flag +=  1;
	if(trg & KEY_R    ) flag += 10;
	if(trg & KEY_LEFT ) flag -=  1;
	if(trg & KEY_L    ) flag -= 10;

	if(flag > 99) flag = 99;
	if(flag <  0) flag =  0;

	NvSetFlag(0x14 + Menu.sel, flag);

	TxtSetChr();
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecDebug2(u16 trg)
{
	if(trg & KEY_B)
	{
		MenuSetOption(MENU_OPTION_SEL_DEBUG2);

		return;
	}

	if(!(trg & KEY_RIGHT || trg & KEY_R || trg & KEY_LEFT || trg & KEY_L))
	{
		return;
	}

	if(Menu.sel != 0)
	{
		return;
	}

	s8 flag = NvGetFlag(0x1d + Menu.sel);

	if(trg & KEY_RIGHT) flag +=  1;
	if(trg & KEY_R    ) flag += 10;
	if(trg & KEY_LEFT ) flag -=  1;
	if(trg & KEY_L    ) flag -= 10;

	if(flag > 99) flag = 99;
	if(flag <  0) flag =  0;

	NvSetFlag(0x1d + Menu.sel, flag);

	TxtSetChr();
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
		if(Menu.ret == MENU_RET_SYSTEM)
		{
			MenuSetSystem(MENU_SYSTEM_SEL_LOAD);
		}
		else
		{
			MenuSetTitle(MENU_TITLE_SEL_LOAD);
		}

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

	NvPushAct(NV_ACT_RESTART);
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
EWRAM_CODE void MenuExecTitle(u16 trg)
{
	if(!(trg & KEY_A))
	{
		return;
	}

	switch(Menu.sel)
	{
	// ゲームを始める
	case 0:
		TxtClear();
		TxtSetChr();
		TxtSetRes();

		NvSetScn(0);
		NvSetEvt(1);

		ManageSetNovel();
		break;

	// ロードする
	case 1:
		MenuSetLoad(MENU_RET_TITLE);
		break;
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

	TxtSetCur(false);

	if(isDraw == true)
	{
		TxtShowMsg();
		TxtSetChr();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSystem(s32 sel)
{
	MenuSetInit(MENU_TYPE_SYSTEM, MENU_RET_NONE, sel, 0, 7, MenuExecSystem, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetOption(s32 sel)
{
	MenuSetInit(MENU_TYPE_OPTION, MENU_RET_SYSTEM, sel, 8, 5, MenuExecOption, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSave(s32 ret)
{
	MenuSetInit(MENU_TYPE_SAVE, ret, 0, 14, 8, MenuExecSave, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetLoad(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, 0, 15, 8, MenuExecLoad, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetNone(void)
{
	MenuSetInit(MENU_TYPE_LOAD, MENU_RET_NONE, 0, 16, 0, MenuExecNone, false);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetTitle(s32 sel)
{
	MenuSetInit(MENU_TYPE_TITLE, MENU_RET_NONE, sel, 17, 2, MenuExecTitle, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetDebug1(void)
{
	MenuSetInit(MENU_TYPE_DEBUG1, MENU_RET_OPTION, 0, 20, 8, MenuExecDebug1, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetDebug2(void)
{
	MenuSetInit(MENU_TYPE_DEBUG2, MENU_RET_OPTION, 0, 29, 3, MenuExecDebug2, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStrTitle(void)
{
	if(Menu.type == MENU_TYPE_SYSTEM)
	{
		u8 v = NvGetFlag(NV_FLAG_DAY);

		// エピローグ
		if(v == 0xff)
		{
			_Strncpy(Menu.buf, "", 2);

			return Menu.buf;
		}

		// 日付表示
		_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg], MENU_BUF_SIZE-1);

		u8 m = NvGetCalMonth(v);
		u8 d = NvGetCalDay(v);
		u8 w = NvGetCalWeek(v);

		// "０月００日　曜日",
		//  01  4567  AB

		// Mon
		Menu.buf[1] = 0x4f + m;

		// Day
		if(d < 10)
		{
			Menu.buf[4] = 0x81;
			Menu.buf[5] = 0x40;
			Menu.buf[7] = 0x4f + d;
		}
		else
		{
			Menu.buf[5] = 0x4f + Div(d, 10);
			Menu.buf[7] = 0x4f + DivMod(d, 10);
		}

		// Week SJISの日月火水木金土
		switch(w)
		{
		case 0: Menu.buf[10] = 0x93; Menu.buf[11] = 0xfa; break;
		case 1: Menu.buf[10] = 0x8c; Menu.buf[11] = 0x8e; break;
		case 2: Menu.buf[10] = 0x89; Menu.buf[11] = 0xce; break;
		case 3: Menu.buf[10] = 0x90; Menu.buf[11] = 0x85; break;
		case 4: Menu.buf[10] = 0x96; Menu.buf[11] = 0xd8; break;
		case 5: Menu.buf[10] = 0x8b; Menu.buf[11] = 0xe0; break;
		case 6: Menu.buf[10] = 0x93; Menu.buf[11] = 0x79; break;
		default:
			SystemError("[Err] MenuGetSelStr w=%x\n", w);
			break;
		}

		return Menu.buf;
	}

	return (char*)MenuSelectStr[Menu.msg];
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStrSelect(s32 sel)
{
	if(Menu.type == MENU_TYPE_SAVE || Menu.type == MENU_TYPE_LOAD)
	{
		return SioriGetStr(sel);
	}

	if(Menu.type == MENU_TYPE_OPTION && (sel == 0 || sel == 1))
	{
		_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 1 + sel], MENU_BUF_SIZE-1);

		s32 max;

		if(sel == 0)
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

	if(Menu.type == MENU_TYPE_DEBUG1)
	{
		_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 1 + sel], MENU_BUF_SIZE-1);

		s8 flag = NvGetFlag(0x14 + sel);

		// 0x82 0x4f = SJISコード「０」
		Menu.buf[15] = 0x4f + Div(flag, 10);
		Menu.buf[17] = 0x4f + DivMod(flag, 10);

		return Menu.buf;
	}

	if(Menu.type == MENU_TYPE_DEBUG2)
	{
		if(sel == 0)
		{
			_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 1 + sel], MENU_BUF_SIZE-1);

			s8 flag = NvGetFlag(0x1d + sel);

			// 0x82 0x4f = SJISコード「０」
			Menu.buf[15] = 0x4f + Div(flag, 10);
			Menu.buf[17] = 0x4f + DivMod(flag, 10);

			return Menu.buf;
		}

		if(sel == 2)
		{
			_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 1 + sel], MENU_BUF_SIZE-1);

			// "　あ芹智志葵マ琴レ雅理お"
			// "　×××××××××××"
			// "　 3 5 7 9 B D F 1 3 5 7

			u8 flag1 = NvGetFlag(0x50);
			u8 flag2 = NvGetFlag(0x51);

			if(flag1 & 0x01) Menu.buf[0x03] = 0x5A;
			if(flag1 & 0x02) Menu.buf[0x05] = 0x5A;
			if(flag1 & 0x04) Menu.buf[0x07] = 0x5A;
			if(flag1 & 0x08) Menu.buf[0x09] = 0x5A;
			if(flag1 & 0x10) Menu.buf[0x0B] = 0x5A;
			if(flag1 & 0x20) Menu.buf[0x0D] = 0x5A;
			if(flag1 & 0x40) Menu.buf[0x0F] = 0x5A;
			if(flag1 & 0x80) Menu.buf[0x11] = 0x5A;

			if(flag2 & 0x01) Menu.buf[0x13] = 0x5A;
			if(flag2 & 0x02) Menu.buf[0x15] = 0x5A;
			if(flag2 & 0x80) Menu.buf[0x17] = 0x5A;

			return Menu.buf; 
		}
	}

	return (char*)MenuSelectStr[Menu.msg + 1 + sel];
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
//---------------------------------------------------------------------------
EWRAM_CODE u8 MenuGetType(void)
{
	return Menu.type;
}
