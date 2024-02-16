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
	"�V�X�e�����j���[",
	"�@�@�Z�[�u",
	"�@�@���[�h",
	"�@�@��������",
	"�@�@����������",
	"�@�@�V�i���I��z",
	"�@�@�I�v�V����",
	"�@�@�Q�[���I��",

	// 8
	"�V�X�e���ݒ�",
	"�@�w�i�P�x�@�@�@�O�O",
	"�@�w�i�E�F�C�g�@�O�O",
	"�@�̓W�����v�@�@�O�O",
	"�@�I�����@�@�@�@�F",
	"�@�I�����@�@�@�@���F",
	"�@�I�����@�@�@�@���F",

	// 14
	"�@�@�@�Z�[�u",

	// 15
	"�@�@�@���[�h",

	// 16
	"",

	// 17
	"",
	"�@�@�Q�[�����n�߂�",
	"�@�@���[�h����",
	"�@�@�@�O�@��",
	"�@�@�@��@��",
};

//---------------------------------------------------------------------------
ST_MENU Menu;


//---------------------------------------------------------------------------
EWRAM_CODE void MenuInit(void)
{
	_Memset(&Menu, 0x00, sizeof(ST_MENU));

	// �̓W�����v�̈ړ��͈͂�ݒ�
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
	// �Z�[�u
	case 0:
		MenuSetSave(MENU_RET_SYSTEM);
		break;

	// ���[�h
	case 1:
		MenuSetLoad(MENU_RET_SYSTEM);
		break;

	// ��������
	case 2:
		NvSetSkip();
		TxtSetChr();

		ManageSetNovel();
		break;

	// ����������
	case 3:
		TxtHideMsg();
		ImgSetFade2(0);
		ImgSetEff(IMG_EFFECT_IGNORE_BG_CHR_SCR);

		MenuSetNone(MENU_RET_SYSTEM);
		break;

	// �V�i���I��z
	case 4:
		if(LogIsEmpty() == false)
		{
			LogSetInit(LOG_RET_MENU);

			ManageSetLog();
		}
		break;

	// �I�v�V����
	case 5:
		MenuSetOption(MENU_OPTION_SEL_WINDOW);
		break;

	// �Q�[���I��
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
	// �w�i�P�x
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

	// �w�i�E�F�C�g
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

	// �̓W�����v
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

	// �I�����̐F
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
			// �V�X�e�����j���[�ɕ��A
			MenuSetSystem(MENU_SYSTEM_SEL_NONE);
			TxtShowMsg();
		}
		else
		{
			// �m�x���ɕ��A
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
	// �Q�[�����n�߂�
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

	// ���[�h����
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
		// �e�L�X�g�̈��\���ς݂��m�F
		if(ImgIsTxt() == true)
		{
			// �I������`��
			TxtSetChr();
		}
		else
		{
			// �G�t�F�N�g���s���Ă���`��
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
			// �O��
			n = 3;
		}
		else
		{
			// ���
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
		// �I��F
		if(sel == 3)
		{
			s32 selCol = ImgGetSelCol();

			_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 4 + selCol], MENU_BUF_SIZE);

			return Menu.buf;
		}

		s32 num;

		// �w�i�P�x�A�w�i�E�F�C�g�A�̓W�����v
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
		// 0x82 0x4f = SJIS�R�[�h�u�O�v
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
