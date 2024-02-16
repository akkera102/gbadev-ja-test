#include "menu.h"
#include "libmy/key.h"
#include "manage.h"
#include "txt.h"
#include "siori.h"
#include "nv.h"
#include "log.h"
#include "img.h"
#include "file.h"
#include "anime.h"

//---------------------------------------------------------------------------
char MenuSelectStr[][20+1] = {
	// 0
	"システムメニュー",
	"　　セーブ",
	"　　ロード",
	"　　文字送り",
	"　　文字を消す",
	"　　シナリオ回想",
	"　　オプション",
	"　　ゲーム終了",

	// 8
	"システム設定",
	"　背景輝度　　　００",
	"　背景ウェイト　００",
	"　章ジャンプ　　００",
	"　選択肢　　　　青色",
	"　選択肢　　　　黄色",
	"　選択肢　　　　白色",

	// 14
	"　　　セーブ",

	// 15
	"　　　ロード",

	// 16
	"",

	// 17
	"",
	"　　ゲームを始める",
	"　　ロードする",
	"　　　前　編",
	"　　　後　編",
};

//---------------------------------------------------------------------------
ST_MENU Menu;


//---------------------------------------------------------------------------
EWRAM_CODE void MenuInit(void)
{
	_Memset(&Menu, 0x00, sizeof(ST_MENU));

	// 章ジャンプの移動範囲を設定
	if(FileIsFirstPart() == true)
	{
		Menu.chap    =  0;
		Menu.chapMin =  0;
		Menu.chapMax = 17;
	}
	else
	{
		Menu.chap    = 18;
		Menu.chapMin = 18;
		Menu.chapMax = 28;
	}
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
		ImgSetFade2(0);
		ImgSetEff(IMG_EFFECT_IGNORE_BG_CHR_SCR);

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
		MenuSetOption(MENU_OPTION_SEL_WINDOW);
		break;

	// ゲーム終了
	case 6:
		AnimeSetDat(ANIME_DAT_TITLE);
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
	case 0: ;
		s32 fade = ImgGetFade();

		if(trg & KEY_LEFT && fade != 0)
		{
			fade--;

			ImgSetFade(fade);
			TxtSetChr();
		}

		if(trg & KEY_RIGHT && fade < 10)
		{
			fade++;

			ImgSetFade(fade);
			TxtSetChr();
		}
		break;

	// 背景ウェイト
	case 1: ;
		s32 fadeWait = ImgGetFadeWait();

		if(trg & KEY_LEFT && fadeWait != 0)
		{
			fadeWait--;

			ImgSetFadeWait(fadeWait);
			TxtSetChr();
		}

		if(trg & KEY_RIGHT && fadeWait < 2)
		{
			fadeWait++;

			ImgSetFadeWait(fadeWait);
			TxtSetChr();
		}
		break;

	// 章ジャンプ
	case 2:
		if(trg & KEY_LEFT && Menu.chap != Menu.chapMin)
		{
			Menu.chap--;

			TxtSetChr();
		}

		if(trg & KEY_RIGHT && Menu.chap < Menu.chapMax)
		{
			Menu.chap++;

			TxtSetChr();
		}

		if(trg & KEY_A)
		{
			NvSetTxt(Menu.chap, 1);
			NvSetAct(NV_ACT_PARSE);

			ManageSetNovel();
		}
		break;

	// 選択肢の色
	case 3:
		s32 selCol = ImgGetSelCol();

		if(trg & KEY_LEFT && selCol != 0)
		{
			selCol--;

			ImgSetSelCol(selCol);
			TxtSetChr();
		}

		if(trg & KEY_RIGHT && selCol < 2)
		{
			selCol++;

			ImgSetSelCol(selCol);
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

	SioriLoad(Menu.sel);

	NvSetAct(NV_ACT_LOAD);
	ManageSetNovel();
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecNone(u16 trg)
{
	if(trg & KEY_B || trg & KEY_L)
	{
		s32 fade = ImgGetFade();
		ImgSetFade(fade);
		ImgSetEff(IMG_EFFECT_IGNORE_NORMAL);

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
	// ゲームを始める
	case 0:
		ImgSetEff(IMG_EFFECT_FADE_BLACK_IN);

		if(FileIsFirstPart() == true)
		{
			NvSetTxt(0, 1);
			MenuSetChap(0);
		}
		else
		{
			NvSetTxt(18, 1);
			MenuSetChap(18);
		}

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

	if(isDraw == true)
	{
		// テキスト領域を表示済みか確認
		if(ImgIsTxt() == true)
		{
			// 選択肢を描画
			TxtSetChr();
		}
		else
		{
			// エフェクトを行ってから描画
			ImgSetEff(IMG_EFFECT_TXT_IN);
		}
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
	MenuSetInit(MENU_TYPE_OPTION, MENU_RET_SYSTEM, sel, 8, 4, MenuExecOption, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSave(s32 ret)
{
	MenuSetInit(MENU_TYPE_SAVE, ret, 0, 15, 8, MenuExecSave, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetLoad(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, 0, 16, 8, MenuExecLoad, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetNone(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, 0, 17, 0, MenuExecNone, false);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetTitle(s32 sel)
{
	MenuSetInit(MENU_TYPE_TITLE, MENU_RET_NONE, sel, 18, 2, MenuExecTitle, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetChap(s32 num)
{
	Menu.chap = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStrTitle(void)
{
	s32 n = 0;

	if(Menu.type == MENU_TYPE_TITLE)
	{
		if(FileIsFirstPart() == true)
		{
			// 前編
			n = 3;
		}
		else
		{
			// 後編
			n = 4;
		}
	}

	return (char*)MenuSelectStr[Menu.msg + n];
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStrSelect(s32 sel)
{
	if(Menu.type == MENU_TYPE_SAVE || Menu.type == MENU_TYPE_LOAD)
	{
		return SioriGetStr(sel);
	}

	if(Menu.type == MENU_TYPE_OPTION)
	{
		// 選択色
		if(sel == 3)
		{
			s32 selCol = ImgGetSelCol();

			_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 4 + selCol], MENU_BUF_SIZE);

			return Menu.buf;
		}

		s32 num;

		// 背景輝度、背景ウェイト、章ジャンプ
		if(sel == 0)
		{
			num = ImgGetFade();
		}
		else if(sel == 1)
		{
			num = ImgGetFadeWait();
		}
		else
		{
			num = Menu.chap;
		}

		_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 1 + sel], MENU_BUF_SIZE);
		// 0x82 0x4f = SJISコード「０」
		Menu.buf[17] = 0x4f + Div(num, 10);
		Menu.buf[19] = 0x4f + DivMod(num, 10);

		return Menu.buf;
	}


	return (char*)MenuSelectStr[Menu.msg + 1 + sel];
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
