#include "menu.h"
#include "libmy/key.h"
#include "libmy/vgm.arm.h"
#include "libbios/swi.h"
#include "ags.arm.h"
#include "txt.h"
#include "siori.h"
#include "nv.h"
#include "img.h"
#include "info.h"

//---------------------------------------------------------------------------
char MenuSelectStr[][16+1] = {
	// 0
	"‚r‚`‚u‚d",
	"‚k‚n‚`‚c",
	"‚i‚t‚l‚o@‚O‚O@",

	// 3
	"‚O‚O@",
	"||||||",

	// 5
	"‚e‚k‚f‚P@",
	"‚e‚k‚f‚Q@",
	"‚l‚n‚c‚d@",

	// 8
	"Ÿ‚Â",
	"•‰‚¯‚é",
};

//---------------------------------------------------------------------------
ST_MENU Menu;


//---------------------------------------------------------------------------
EWRAM_CODE void MenuInit(void)
{
	_Memset(&Menu, 0x00, sizeof(ST_MENU));

	Menu.idx = 1;
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExec(void)
{
	u16 trg = KeyGetTrg();
	u16 rep = KeyGetRep();

	if(trg & KEY_A || trg & KEY_B || trg & KEY_L || trg & KEY_R || rep & KEY_LEFT || rep & KEY_RIGHT)
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

		return;
	}

	switch(Menu.cnt)
	{
	// ƒZ[ƒu
	case 0:
		if(trg & KEY_A)
		{
			MenuSetSave(MENU_RET_SYSTEM);
		}
		return;

	// ƒ[ƒh
	case 1:
		if(trg & KEY_A)
		{
			MenuSetLoad(MENU_RET_SYSTEM);
		}
		return;

	// ê–Ê
	case 2:
		if(rep & KEY_LEFT)
		{
			Menu.idxCur = InfoGetPrev(Menu.idxCur);

			TxtSetMsg();
			return;
		}

		if(rep & KEY_L)
		{
			Menu.idxCur = InfoGetPrev2(Menu.idxCur);

			TxtSetMsg();
			return;
		}

		if(rep & KEY_RIGHT)
		{
			Menu.idxCur = InfoGetNext(Menu.idxCur);

			TxtSetMsg();
			return;
		}

		if(rep & KEY_R)
		{
			Menu.idxCur = InfoGetNext2(Menu.idxCur);

			TxtSetMsg();
			return;
		}

		if(trg & KEY_A)
		{
			Menu.idx = Menu.idxCur;

			NvSetVar(16, Menu.idx);
			NvSetAct(NV_ACT_LOAD);

			AgsSetNovel();
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
EWRAM_CODE void  MenuExecDebug(u16 trg, u16 rep)
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

		return;
	}

	if(trg & KEY_RIGHT)
	{
		if(Menu.cnt == 0)
		{
			s32 v = NvGetVar(21) + 1;

			if(v > 1)
			{
				v = 0;
			}

			NvSetVar(21, v);
		}
		else if(Menu.cnt == 1)
		{
			s32 v = NvGetVar(20) + 1;

			if(v > 2)
			{
				v = 0;
			}

			NvSetVar(20, v);
		}
		else
		{
			VgmSetHeadset();
		}

		TxtSetMsg();
		return;
	}

	if(trg & KEY_LEFT)
	{
		if(Menu.cnt == 0)
		{
			s32 v = NvGetVar(21) - 1;

			if(v < 0)
			{
				v = 1;
			}

			NvSetVar(21, v);
		}
		else if(Menu.cnt == 1)
		{
			s32 v = NvGetVar(20) - 1;

			if(v < 0)
			{
				v = 2;
			}

			NvSetVar(20, v);
		}
		else
		{
			VgmSetHeadset();
		}

		TxtSetMsg();
		return;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuExecBattle(u16 trg, u16 rep)
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

		return;
	}

	if(trg & KEY_A)
	{
		if(Menu.cnt == 0)
		{
			// Ÿ‚¿
			NvSetVar(102, 0);
			NvSetLbl(197);
		}
		else
		{
			// •‰‚¯
			NvSetVar(101, 0);
			NvSetLbl(188);
		}

		NvSetAct(NV_ACT_PARSE);
		AgsSetNovel();
		return;
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

	s32 idx = NvGetVar(16);

	Menu.idx = idx;
	Menu.idxCur = idx;
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
	MenuSetInit(MENU_TYPE_NONE, ret, 0, 0, 0, MenuExecNone, false);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetDebug(void)
{
	MenuSetInit(MENU_TYPE_DEBUG, MENU_RET_NONE, 0, 5, 3, MenuExecDebug, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void MenuSetBattle(void)
{
	MenuSetInit(MENU_TYPE_BATTLE, MENU_RET_NONE, 0, 8, 2, MenuExecBattle, true);
}
//---------------------------------------------------------------------------
EWRAM_CODE char* MenuGetStr(s32 sel)
{
	if(Menu.type == MENU_TYPE_SAVE || Menu.type == MENU_TYPE_LOAD)
	{
		u16 var = SioriGetVar(sel);

		if(var == 0xffff)
		{
			_Strncpy(Menu.buf, MenuSelectStr[Menu.msg + 1], MENU_BUF_SIZE);
		}
		else
		{
			_Strncpy(Menu.buf, MenuSelectStr[Menu.msg + 0], MENU_BUF_SIZE);
			Menu.buf[1] += SwiDiv(var, 10);
			Menu.buf[3] += SwiDivMod(var, 10);

			_Strcat(Menu.buf, InfoGetTxt(var));
		}

		return Menu.buf;
	}

	if(Menu.type == MENU_TYPE_SYSTEM && sel == 2)
	{
		_Strncpy(Menu.buf, MenuSelectStr[Menu.msg + sel], MENU_BUF_SIZE);
		Menu.buf[11] += SwiDiv(Menu.idxCur, 10);
		Menu.buf[13] += SwiDivMod(Menu.idxCur, 10);

		_Strcat(Menu.buf, InfoGetTxt(Menu.idxCur));

		return Menu.buf;
	}

	if(Menu.type == MENU_TYPE_DEBUG)
	{
		_Strncpy(Menu.buf, MenuSelectStr[Menu.msg + sel], MENU_BUF_SIZE);

		if(sel == 0)
		{
			s32 v = NvGetVar(21);

			if(v == 0)
			{
				_Strcat(Menu.buf, "‚O@‚Æ‚É‚©‚­“¦‚°‚é");
			}
			else
			{
				_Strcat(Menu.buf, "‚P@—lq‚ğŒ©‚é");
			}
		}
		else if(sel == 1)
		{
			s32 v = NvGetVar(20);

			if(v == 0)
			{
				_Strcat(Menu.buf, "‚O@‚Ql‚¢‚é");
			}
			else if(v == 1)
			{
				_Strcat(Menu.buf, "‚P@ƒTƒL•ß‚Ü‚é");
			}
			else
			{
				_Strcat(Menu.buf, "‚Q@‚Ql•ß‚Ü‚é");
			}
		}
		else
		{
			if(VgmIsHeadset() == true)
			{
				_Strcat(Menu.buf, "ƒwƒbƒhƒZƒbƒg");

			}
			else
			{
				_Strcat(Menu.buf, "ƒXƒs[ƒJ[");
			}
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
//---------------------------------------------------------------------------
EWRAM_CODE s32 MenuGetIdx(void)
{
	return Menu.idx;
}
