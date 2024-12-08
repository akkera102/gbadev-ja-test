#include "menu.h"
#include "libmy/key.h"
#include "libmy/vgm.arm.h"
#include "ags.arm.h"
#include "txt.h"
#include "siori.h"
#include "nv.h"
#include "img.h"
#include "info.h"

//---------------------------------------------------------------------------
char MenuSelectStr[][16+1] = {
	// 0
	"ÇrÇ`ÇuÇd",
	"ÇkÇnÇ`Çc",
	"ÇiÇtÇlÇoÅ@ÇOÇOÇO",

	// 3
	"ÇcÇ`ÇsÇ`Å@ÇOÇOÇO",
	"Å|Å|Å|Å|Å|Å|Å|Å|",
};

//---------------------------------------------------------------------------
ST_MENU Menu;


//---------------------------------------------------------------------------
EWRAM_CODE void MenuInit(void)
{
	_Memset(&Menu, 0x00, sizeof(ST_MENU));

	Menu.sys = 2;
	Menu.jmp = 1;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExec(void)
{
	u16 trg = KeyGetTrg();
	u16 rep = KeyGetRep();

	if(trg & KEY_A || trg & KEY_B || trg & KEY_L || trg & KEY_R || trg & KEY_SELECT || trg & KEY_START || rep & KEY_LEFT || rep & KEY_RIGHT)
	{
		Menu.pFunc(trg, rep);

		return;
	}

	if(trg & KEY_DOWN)
	{
		if((Menu.cnt+1) < Menu.reg)
		{
			Menu.cnt++;
		}
		else
		{
			Menu.cnt = 0;
		}

		TxtSetMsg();
	}

	if(trg & KEY_UP)
	{
		if(Menu.cnt != 0)
		{
			Menu.cnt--;
		}
		else
		{
			Menu.cnt = Menu.reg - 1;
		}

		TxtSetMsg();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecSystem(u16 trg, u16 rep)
{
	if(trg & KEY_B)
	{
		ImgSetEff(IMG_EFFECT_TXT_HIDE_OUT, 0);

		if(NvIsActSel() == true)
		{
			AgsSetSelect();
		}
		else
		{
			TxtSetBuf();
			AgsSetNovel();
		}

		Menu.sys = Menu.cnt;

		return;
	}

	if(trg & KEY_SELECT)
	{
		u8 v0 = NvGetVar(200);		// 0 or 2
		u8 v1 = NvGetVar(201);		// 0 or 1

		if(v0 == 0 && v1 == 0)
		{
			v1 = 1;
		}
		else if(v0 == 0 && v1 == 1)
		{
			v0 = 2;
			v1 = 0;
		}
		else if(v0 == 2 && v1 == 0)
		{
			v1 = 1;
		}
		else
		{
			// v0 == 2 && v1 == 1
			v0 = 0;
			v1 = 0;
		}

		NvSetVar(200, v0);
		NvSetVar(201, v1);
		TxtSetMsg();

		return;
	}

	if(trg & KEY_START)
	{
		VgmSetHeadset();
		TxtSetMsg();

		return;
	}


	switch(Menu.cnt)
	{
	// ÉZÅ[Éu
	case 0:
		if(trg & KEY_A)
		{
			Menu.sys = Menu.cnt;

			MenuSetSave(MENU_RET_SYSTEM);
		}
		return;

	// ÉçÅ[Éh
	case 1:
		if(trg & KEY_A)
		{
			Menu.sys = Menu.cnt;

			MenuSetLoad(MENU_RET_SYSTEM);
		}
		return;

	// èÍñ 
	case 2:
		if(rep & KEY_LEFT)
		{
			Menu.jmpCur = InfoGetVarPrev(Menu.jmpCur);

			TxtSetMsg();
			return;
		}

		if(rep & KEY_L)
		{
			Menu.jmpCur = InfoGetVarPrev2(Menu.jmpCur);

			TxtSetMsg();
			return;
		}

		if(rep & KEY_RIGHT)
		{
			Menu.jmpCur = InfoGetVarNext(Menu.jmpCur);

			TxtSetMsg();
			return;
		}

		if(rep & KEY_R)
		{
			Menu.jmpCur = InfoGetVarNext2(Menu.jmpCur);

			TxtSetMsg();
			return;
		}

		if(trg & KEY_A)
		{
			Menu.jmp = Menu.jmpCur;

			NvSetVar(17, Menu.jmp);
			NvSetAct(NV_ACT_LOAD);

			AgsSetNovel();
			Menu.sys = Menu.cnt;

			return;
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecSave(u16 trg, u16 rep)
{
	if(trg & KEY_B)
	{
		MenuSetSystem(MENU_SYSTEM_SEL_SAVE);

		return;
	}

	if(trg & KEY_A)
	{
		SioriSave(Menu.cnt);

		ImgSetEff(IMG_EFFECT_TXT_HIDE_OUT, 0);

		if(NvIsActSel() == true)
		{
			AgsSetSelect();
		}
		else
		{
			TxtSetBuf();
			AgsSetNovel();
		}

		return;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecLoad(u16 trg, u16 rep)
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

	if(SioriIsItem(Menu.cnt) == false)
	{
		return;
	}

	SioriLoad(Menu.cnt);

	NvSetAct(NV_ACT_LOAD);
	AgsSetNovel();
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecNone(u16 trg, u16 rep)
{
	if(trg & KEY_B || trg & KEY_L)
	{
		ImgSetEff(IMG_EFFECT_TXT_HIDE_OUT, 0);

		if(NvIsActSel() == true)
		{
			AgsSetSelect();
		}
		else
		{
			TxtSetBuf();
			AgsSetNovel();
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetInit(s32 type, s32 ret, s32 cnt, s32 msg, s32 reg, void* pFunc, bool isDraw)
{
	Menu.type  = type;
	Menu.ret   = ret;
	Menu.cnt   = cnt;
	Menu.msg   = msg;
	Menu.reg   = reg;
	Menu.pFunc = pFunc;

	if(isDraw == true)
	{
		TxtSetMsg();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSystem(s32 cnt)
{
	MenuSetInit(MENU_TYPE_SYSTEM, MENU_RET_NONE, cnt, 0, 3, MenuExecSystem, true);

	Menu.jmpCur = Menu.jmp;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSystem2(void)
{
	MenuSetInit(MENU_TYPE_SYSTEM, MENU_RET_NONE, Menu.sys, 0, 3, MenuExecSystem, true);

	Menu.jmpCur = Menu.jmp;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetSave(s32 ret)
{
	MenuSetInit(MENU_TYPE_SAVE, ret, 0, 3, 3, MenuExecSave, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetLoad(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, 0, 3, 3, MenuExecLoad, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetNone(s32 ret)
{
	MenuSetInit(MENU_TYPE_NONE, ret, 0, 5, 0, MenuExecNone, false);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetJmp(s32 jmp)
{
	if(jmp == 0)
	{
		jmp = 1;
	}

	Menu.jmp = jmp;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStr(s32 sel)
{
	if(Menu.type == MENU_TYPE_SAVE || Menu.type == MENU_TYPE_LOAD)
	{
		u8 num = SioriGetVar(sel);

		if(num == 0xff)
		{
			// ÉZÅ[ÉuÉtÉ@ÉCÉãÇ»Çµ
			_Strncpy(Menu.buf, MenuSelectStr[Menu.msg + 1], MENU_BUF_SIZE);
		}
		else
		{
			// ïœêî17Çï\é¶
			_Strncpy(Menu.buf, MenuSelectStr[Menu.msg + 0], MENU_BUF_SIZE);

			Menu.buf[11] += Div(num, 100);
			Menu.buf[13] += DivMod(Div(num, 10), 10);
			Menu.buf[15] += DivMod(num, 10);
		}

		return Menu.buf;
	}

	if(Menu.type == MENU_TYPE_SYSTEM && sel == 2)
	{
		_Strncpy(Menu.buf, MenuSelectStr[Menu.msg + sel], MENU_BUF_SIZE);

		Menu.buf[11] += Div(Menu.jmpCur, 100);
		Menu.buf[13] += DivMod(Div(Menu.jmpCur, 10), 10);
		Menu.buf[15] += DivMod(Menu.jmpCur, 10);

		// Ç‡Ç¡Ç∆ÉJÉãÉâHÉtÉâÉOÇï\é¶
		if(NvGetVar(200) == 2)
		{
			// ï\é¶ÇÕÉvÉåÉCÉÑÅ[ÇÃç¨óêÇîÇØÇÈà◊ÇP
			_Strcat(Menu.buf, "Å@ÇbÇP");
		}
		else
		{
			_Strcat(Menu.buf, "Å@ÇbÇO");
		}

		// ÉÅÉãÉZÉfÉXHÉtÉâÉOÇï\é¶
		if(NvGetVar(201) == 1)
		{
			_Strcat(Menu.buf, "ÇlÇP");
		}
		else
		{
			_Strcat(Menu.buf, "ÇlÇO");
		}

		if(VgmIsHeadset() == true)
		{
			_Strcat(Menu.buf, "Å@ÇgÇÖÇÅÇÑÇìÇÖÇî");
		}
		else
		{
			_Strcat(Menu.buf, "Å@ÇrÇêÇÖÇÅÇãÇÖÇí");
		}

		return Menu.buf;
	}

	return MenuSelectStr[Menu.msg + sel];
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 MenuGetCnt(void)
{
	return Menu.cnt;
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
