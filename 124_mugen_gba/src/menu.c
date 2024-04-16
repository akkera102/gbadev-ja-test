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
#include "bgm.h"
#include "se.h"

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
	"　章ジャンプ　　００",
	"　選択肢　　　　水色",
	"　選択肢　　　　黄色",
	"　選択肢　　　　緑色",
	"　選択肢　　　　白色",

	// 15
	"　　　セーブ",

	// 16
	"　　　ロード",

	// 17
	"",

	// 18
	"",
	"最初から始める",
	"途中から始める",
	"エンディング前",

	// 22
	"選択肢（１／２）",
	"　摩耶",
	"　美和子",
	"　深紗緒",
	"　由羅",
	"　沙里",
	"　雪菜",
	"　亜璃沙",
	"　女主人",

	// 31
	"選択肢（２／２）",
	"　美和子　ＢＡＤ",
	"　沙里　　魔として",
	"　亜璃沙　見守る",
	"　女主人　館に残る",
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
	case 5: ;
		Menu.chap = NvGetChap();
		MenuSetOption(MENU_OPTION_SEL_WINDOW);
		break;

	// ゲーム終了
	case 6:
		ImgInit();
		TxtInit();
		LogInit();
		MenuInit();
		SioriInit();
		NvInit();
		AnimeInit();
		SeStop();

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

	// 章ジャンプ
	case 1:
		if(trg & KEY_LEFT && Menu.chap != 0)
		{
			Menu.chap--;

			TxtSetChr();
		}

		if(trg & KEY_RIGHT && Menu.chap < 12)
		{
			Menu.chap++;

			TxtSetChr();
		}

		if(trg & KEY_A)
		{
			LogInit();
			TxtHideMsg();
			TxtClear();
			BgmStop();
			SeStop();

			ImgSetEff(IMG_EFFECT_BLACK_RECT);

			NvSetTxt(Menu.chap, 0);
			NvSetAct(NV_ACT_PARSE);

			ManageSetNovel();
		}
		break;

	// 選択肢の色
	case 2:
		s32 selCol = ImgGetSelCol();

		if(trg & KEY_LEFT && selCol != 0)
		{
			selCol--;

			ImgSetSelCol(selCol);
			TxtSetChr();
		}

		if(trg & KEY_RIGHT && selCol < 3)
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
		BgmStop();

		NvSetTxt(0, 0);
		NvSetAct(NV_ACT_PARSE);
		ImgSetEff(IMG_EFFECT_BLACK_RECT);

		ManageSetNovel();
		break;

	// 途中から始める
	case 1:
		MenuSetLoad(MENU_RET_TITLE);
		break;

	// エンディング前
	case 2:
		MenuSetEnding1(MENU_RET_TITLE);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecEnding1(u16 trg)
{
	if(trg & KEY_RIGHT)
	{
		MenuSetEnding2(Menu.ret);

		return;
	}

	if(trg & KEY_B && Menu.ret == MENU_RET_TITLE)
	{
		MenuSetTitle(MENU_TITLE_SEL_ENDING);
	}

	if(!(trg & KEY_A))
	{
		return;
	}

	switch(Menu.sel)
	{
	// 摩耶
	case 0:
		NvSetTxt(12, 3);
		break;
	// 美和子
	case 1:
		NvSetTxt(12, 7);
		break;
	// 深紗緒
	case 2:
		NvSetTxt(12, 4);
		break;
	// 由羅
	case 3:
		NvSetTxt(12, 5);
		break;
	// 沙里
	case 4:
		NvSetTxt(12, 6);
		break;
	// 雪菜
	case 5:
		NvSetTxt(12, 2);
		break;
	// 亜璃沙
	case 6:
		NvSetTxt(12, 8);
		break;
	// 女主人
	case 7:
		NvSetTxt(12, 1);
		break;

	default:
		SystemError("[Err] MenuExecEnding1 Menu.sel=%x\n", Menu.sel);
		break;
	}

	if(Menu.ret == MENU_RET_TITLE)
	{
		LogInit();
		BgmStop();

		// スクリプトを実行する前に背景とキャラクタを表示します
		if(Menu.sel == 4 || Menu.sel == 7)
		{
			AnimeSetDat(ANIME_DAT_PATCH);
		}
	}

	NvSetAct(NV_ACT_PARSE);
	ManageSetNovel();
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecEnding2(u16 trg)
{
	if(trg & KEY_LEFT)
	{
		MenuSetEnding1(Menu.ret);

		return;
	}

	if(trg & KEY_B && Menu.ret == MENU_RET_TITLE)
	{
		MenuSetTitle(MENU_TITLE_SEL_ENDING);
	}

	if(!(trg & KEY_A))
	{
		return;
	}

	switch(Menu.sel)
	{
	// 美和子　Ｂａｄ
	case 0:
		NvSetTxt(12, 17);
		break;
	// 沙里　魔として
	case 1:
		NvSetTxt(12, 16);
		break;
	// 亜璃沙　このまま見守る
	case 2:
		NvSetTxt(12, 18);
		break;
	// 女主人　館に残る
	case 3:
		NvSetTxt(12, 11);
		break;

	default:
		SystemError("[Err] MenuExecEnding1 Menu.sel=%x\n", Menu.sel);
		break;
	}

	if(Menu.ret == MENU_RET_TITLE)
	{
		LogInit();
		BgmStop();

		// スクリプトを実行する前に背景とキャラクタを表示します
		if(Menu.sel == 1 || Menu.sel == 3)
		{
			AnimeSetDat(ANIME_DAT_PATCH);
		}
	}

	NvSetAct(NV_ACT_PARSE);
	ManageSetNovel();
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
	MenuSetInit(MENU_TYPE_SYSTEM, MENU_RET_NONE, sel, 0, 7, MenuExecSystem, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetOption(s32 sel)
{
	MenuSetInit(MENU_TYPE_OPTION, MENU_RET_SYSTEM, sel, 8, 3, MenuExecOption, true);
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
	MenuSetInit(MENU_TYPE_TITLE, MENU_RET_NONE, sel, 18, 3, MenuExecTitle, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetEnding1(s32 ret)
{
	MenuSetInit(NEMU_TYPE_ENDING1, ret, 0, 22, 8, MenuExecEnding1, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetEnding2(s32 ret)
{
	MenuSetInit(NEMU_TYPE_ENDING2, ret, 0, 31, 4, MenuExecEnding2, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetChap(s32 num)
{
	Menu.chap = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStrTitle(void)
{
	return (char*)MenuSelectStr[Menu.msg];
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
		if(sel == 2)
		{
			s32 selCol = ImgGetSelCol();

			_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 3 + selCol], MENU_BUF_SIZE);

			return Menu.buf;
		}

		s32 num;

		// 背景輝度、章ジャンプ
		if(sel == 0)
		{
			num = ImgGetFade();
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
