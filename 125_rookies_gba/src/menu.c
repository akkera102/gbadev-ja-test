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
char MenuSelectStr[][24+1] = {
	// 0
	"システムメニュー",
	"　　セーブ",
	"　　ロード",
	"　　文字送り",
	"　　文字を消す",
	"　　シナリオ回想",
	"　　オプション",
	"　　デバッグ",
	"　　ゲーム終了",

	// 9
	"システム設定",
	"　背景輝度　　　００",
	"　表\示ウェイト　００",
	"　静止ウェイト　００",
	"　攻略情報　　　あり",

	// 14
	"　　　セーブ",

	// 15
	"　　　ロード",

	// 16
	"",

	// 17
	"",
	"最初から始める",
	"続きから始める",

	// 20
	"　　デバッグ",
	"日付ジャンプ　０Ｄ",
	"１Ｄカメラ　　　　　　　",
	"１Ｄ吸殻　　　　　　　　",
	"３Ｄひろ質問　　　　　　",
	"４Ｄ恭子夢　　　　　　　",
};

//---------------------------------------------------------------------------
ST_MENU Menu;


//---------------------------------------------------------------------------
EWRAM_CODE void MenuInit(void)
{
	_Memset(&Menu, 0x00, sizeof(ST_MENU));

	Menu.isHowto = true;
	Menu.day = 1;
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
		TxtSetCur(true);

		ManageSetNovel();
		return;
	}

	if(!(trg & KEY_A))
	{
		return;
	}

	switch(Menu.sel)
	{
	// セーブ
	case 0:
		MenuSetSave(MENU_RET_SYSTEM);
		break;

	// ロード
	case 1:
		MenuSetLoad(MENU_RET_SYSTEM);
		break;

	// 文字送り
	case 2:
		NvSetSkip();
		TxtSetChr();

		ManageSetNovel();
		break;

	// 文字を消す
	case 3:
		TxtHideMsg();
		ImgSetTxtFade2(0);

		MenuSetNone(MENU_RET_SYSTEM);
		break;

	// シナリオ回想
	case 4:
		if(LogIsEmpty() == false)
		{
			LogSetInit(LOG_RET_MENU);

			ManageSetLog();
		}
		break;

	// オプション
	case 5:
		MenuSetOption(MENU_OPTION_SEL_TXT_FADE);
		break;

	// デバッグ
	case 6:
		MenuSetDebug(MENU_DEBUG_SEL_JUMP);
		break;

	// ゲーム終了
	case 7:
		ImgInit();
		TxtInit();
		LogInit();
		MenuInit();
		SioriInit();
		NvInit();

		NvSetScn("IPL2");
		ManageSetNovel();
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
	// 背景輝度
	case 0:
		s32 fade = ImgGetTxtFade();

		if(trg & KEY_LEFT && fade > 0)
		{
			fade--;

			ImgSetTxtFade(fade);
			TxtSetChr();
		}

		if(trg & KEY_RIGHT && fade < 10)
		{
			fade++;

			ImgSetTxtFade(fade);
			TxtSetChr();
		}
		break;

	// 表示ウェイト
	case 1:
		s32 txt = ImgGetTxtWait();

		if(trg & KEY_LEFT && txt > 0)
		{
			txt--;

			ImgSetTxtWait(txt);
			TxtSetChr();
		}

		if(trg & KEY_RIGHT && txt < 3)
		{
			txt++;

			ImgSetTxtWait(txt);
			TxtSetChr();
		}
		break;

	// 静止ウェイト
	case 2:
		s32 sti = ImgGetStiWait();

		if(trg & KEY_LEFT && sti > 0)
		{
			sti--;

			ImgSetStiWait(sti);
			TxtSetChr();
		}

		if(trg & KEY_RIGHT && sti < 10)
		{
			sti++;

			ImgSetStiWait(sti);
			TxtSetChr();
		}
		break;

	// 攻略情報
	case 3:
		if(trg & KEY_LEFT || trg & KEY_RIGHT)
		{
			if(Menu.isHowto == true)
			{
				Menu.isHowto = false;
			}
			else
			{
				Menu.isHowto = true;
			}

			TxtSetChr();
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
		Menu.siori = Menu.sel;
		SioriSave(Menu.sel);

		TxtSetChr();
		TxtSetCur(true);

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

	if(SioriIsItem(Menu.sel) == false)
	{
		return;
	}

	Menu.siori = Menu.sel;
	SioriLoad(Menu.sel);

	NvSetAct(NV_ACT_LOAD);
	ManageSetNovel();
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecNone(u16 trg)
{
	if(trg & KEY_B || trg & KEY_L)
	{
		s32 fade = ImgGetTxtFade();
		ImgSetTxtFade(fade);

		if(Menu.ret == MENU_RET_SYSTEM)
		{
			// システムメニューに復帰
			MenuSetSystem(MENU_SYSTEM_SEL_NONE);
			TxtShowMsg();
		}
		else
		{
			// ノベルに復帰
			TxtSetChr();
			TxtSetCur(true);
			TxtShowMsg();

			ManageSetNovel();
		}
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
	// 最初から始める
	case 0:
		LogInit();

		NvSetScn("OPENING");

		ManageSetNovel();
		break;

	// 途中から始める
	case 1:
		MenuSetLoad(MENU_RET_TITLE);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void  MenuExecDebug(u16 trg)
{
	if(trg & KEY_B)
	{
		MenuSetSystem(MENU_SYSTEM_SEL_DEBUG);

		return;
	}

	s32 v;

	switch(Menu.sel)
	{
	// 日付ジャンプ
	case 0:
		if(trg & KEY_LEFT && Menu.day > 1)
		{
			Menu.day--;

			TxtSetChr();
		}

		if(trg & KEY_RIGHT && Menu.day < 6)
		{
			Menu.day++;

			TxtSetChr();
		}

		if(trg & KEY_A)
		{
			TxtClear();
			LogInit();
			BgmStop();
			SeStop();

			ImgSetEff(IMG_EFFECT_BLACK_IN, 0);

			switch(Menu.day)
			{
			case 1: NvSetScn("1DAY_A"); break;
			case 2: NvSetScn("2DAY_A"); break;
			case 3: NvSetScn("3DAY_A"); break;
			case 4: NvSetScn("4DAY_A"); break;
			case 5: NvSetScn("5DAY_A"); break;
			case 6: NvSetScn("6DAY");   break;
			}

			NvSetAct(NV_ACT_PARSE);
			ManageSetNovel();
		}
		break;

	// １Ｄカメラ
	case 1:
		v = NvGetVar(12);

		if(trg & KEY_LEFT && v > 0)
		{
			NvSetVar(12, v - 1);

			TxtSetChr();
		}

		if(trg & KEY_RIGHT && v < 3)
		{
			NvSetVar(12, v + 1);

			TxtSetChr();
		}
		break;

	// １Ｄ吸殻
	case 2:
		v = NvGetVar(32);

		if(trg & KEY_LEFT && v > 0)
		{
			NvSetVar(32, v - 1);

			TxtSetChr();
		}

		if(trg & KEY_RIGHT && v < 1)
		{
			NvSetVar(32, v + 1);

			TxtSetChr();
		}
		break;

	// ３Ｄひろ質問
	case 3:
		v = NvGetVar(14);

		if(trg & KEY_LEFT && v > 0)
		{
			NvSetVar(14, v - 1);

			TxtSetChr();
		}

		if(trg & KEY_RIGHT && v < 2)
		{
			NvSetVar(14, v + 1);

			TxtSetChr();
		}
		break;

	// ４Ｄ恭子夢
	case 4:
		v = NvGetVar(15);

		if(trg & KEY_LEFT && v > 0)
		{
			NvSetVar(15, v - 1);

			TxtSetChr();
		}

		if(trg & KEY_RIGHT && v < 2)
		{
			NvSetVar(15, v + 1);

			TxtSetChr();
		}
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

	if(isDraw == true && ImgIsTxt() == true)
	{
		// 選択肢を描画
		TxtSetChr();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSystem(s32 sel)
{
	MenuSetInit(MENU_TYPE_SYSTEM, MENU_RET_NONE, sel, 0, 8, MenuExecSystem, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetOption(s32 sel)
{
	MenuSetInit(MENU_TYPE_OPTION, MENU_RET_SYSTEM, sel, 9, 4, MenuExecOption, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSave(s32 ret)
{
	MenuSetInit(MENU_TYPE_SAVE, ret, 0, 14, 8, MenuExecSave, true);

	Menu.sel = Menu.siori;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetLoad(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, 0, 15, 8, MenuExecLoad, true);

	Menu.sel = Menu.siori;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetNone(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, 0, 16, 0, MenuExecNone, false);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetTitle(s32 sel)
{
	MenuSetInit(MENU_TYPE_TITLE, MENU_RET_NONE, sel, 17, 2, MenuExecTitle, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetDebug(s32 ret)
{
	MenuSetInit(MENU_TYPE_DEBUG, MENU_RET_SYSTEM, ret, 20, 5, MenuExecDebug, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStrTitle(void)
{
	return (char*)MenuSelectStr[Menu.msg];
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStrSelect(s32 sel)
{
	switch(Menu.type)
	{
	case MENU_TYPE_SAVE:
	case MENU_TYPE_LOAD:
		return SioriGetStr(sel);

	case MENU_TYPE_OPTION:
		return MenuGetStrSelectOption(sel);

	case MENU_TYPE_DEBUG:
		return MenuGetStrSelectDebug(sel);
	}


	return (char*)MenuSelectStr[Menu.msg + 1 + sel];
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStrSelectOption(s32 sel)
{
	_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 1 + sel], MENU_BUF_SIZE);

	// 攻略情報
	if(sel == 3)
	{

		// SJIS「なし」0x82 0xC8 0x82 0xB5
		if(Menu.isHowto == false)
		{
			Menu.buf[17] = 0xC8;
			Menu.buf[19] = 0xB5;
		}

		return Menu.buf;
	}

	// 背景輝度、表示ウェイト
	s32 num;

	if(sel == 0)
	{
		num = ImgGetTxtFade();
	}
	else if(sel == 1)
	{
		num = ImgGetTxtWait();
	}
	else
	{
		// 2
		num = ImgGetStiWait();
	}

	// SJIS「０」0x82 0x4f
	Menu.buf[17] = 0x4f + Div(num, 10);
	Menu.buf[19] = 0x4f + DivMod(num, 10);

	return Menu.buf;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStrSelectDebug(s32 sel)
{
	_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 1 + sel], MENU_BUF_SIZE);

	s32 v;

	switch(sel)
	{
	case 0:
		// SJIS「０」0x82 0x4f
		Menu.buf[15] = 0x4f + Menu.day;
		break;

	// １Ｄカメラ
	case 1:
		v = NvGetVar(12);

		if(v == 0) _Strncpy(Menu.buf+14, "美術室　　", 10);
		if(v == 1) _Strncpy(Menu.buf+14, "家庭科室　", 10);
		if(v == 2) _Strncpy(Menu.buf+14, "音楽室　　", 10);
		if(v == 3) _Strncpy(Menu.buf+14, "科学実験室", 10);
		break;

	// １Ｄ吸殻
	case 2:
		v = NvGetVar(32);

		if(v == 0) _Strncpy(Menu.buf+14, "見てない", 8);
		if(v == 1) _Strncpy(Menu.buf+14, "見た　　", 8);
		break;

	// ３Ｄひろ質問
	case 3:
		v = NvGetVar(14);

		if(v == 0) _Strncpy(Menu.buf+14, "吸ってる", 8);
		if(v == 1) _Strncpy(Menu.buf+14, "知らない", 8);
		if(v == 2) _Strncpy(Menu.buf+14, "持ってる", 8);
		break;

	// ４Ｄ恭子夢
	case 4:
		v = NvGetVar(15);

		if(v == 0) _Strncpy(Menu.buf+14, "料理人", 6);
		if(v == 1) _Strncpy(Menu.buf+14, "芸術家", 6);
		if(v == 2) _Strncpy(Menu.buf+14, "漫画家", 6);
		break;
	}

	return Menu.buf;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 MenuGetSel(void)
{
	return Menu.sel;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 MenuGetReg(void)
{
	return Menu.reg;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 MenuGetType(void)
{
	return Menu.type;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool MenuIsHowto(void)
{
	return Menu.isHowto;
}
