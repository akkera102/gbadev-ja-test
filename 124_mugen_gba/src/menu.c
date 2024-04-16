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
	"�@�̓W�����v�@�@�O�O",
	"�@�I�����@�@�@�@���F",
	"�@�I�����@�@�@�@���F",
	"�@�I�����@�@�@�@�ΐF",
	"�@�I�����@�@�@�@���F",

	// 15
	"�@�@�@�Z�[�u",

	// 16
	"�@�@�@���[�h",

	// 17
	"",

	// 18
	"",
	"�ŏ�����n�߂�",
	"�r������n�߂�",
	"�G���f�B���O�O",

	// 22
	"�I�����i�P�^�Q�j",
	"�@����",
	"�@���a�q",
	"�@�[�я�",
	"�@�R��",
	"�@����",
	"�@���",
	"�@������",
	"�@����l",

	// 31
	"�I�����i�Q�^�Q�j",
	"�@���a�q�@�a�`�c",
	"�@�����@�@���Ƃ���",
	"�@�������@�����",
	"�@����l�@�قɎc��",
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
	case 5: ;
		Menu.chap = NvGetChap();
		MenuSetOption(MENU_OPTION_SEL_WINDOW);
		break;

	// �Q�[���I��
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

	// �̓W�����v
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

	// �I�����̐F
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
	// �ŏ�����n�߂�
	case 0:
		LogInit();
		BgmStop();

		NvSetTxt(0, 0);
		NvSetAct(NV_ACT_PARSE);
		ImgSetEff(IMG_EFFECT_BLACK_RECT);

		ManageSetNovel();
		break;

	// �r������n�߂�
	case 1:
		MenuSetLoad(MENU_RET_TITLE);
		break;

	// �G���f�B���O�O
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
	// ����
	case 0:
		NvSetTxt(12, 3);
		break;
	// ���a�q
	case 1:
		NvSetTxt(12, 7);
		break;
	// �[�я�
	case 2:
		NvSetTxt(12, 4);
		break;
	// �R��
	case 3:
		NvSetTxt(12, 5);
		break;
	// ����
	case 4:
		NvSetTxt(12, 6);
		break;
	// ���
	case 5:
		NvSetTxt(12, 2);
		break;
	// ������
	case 6:
		NvSetTxt(12, 8);
		break;
	// ����l
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

		// �X�N���v�g�����s����O�ɔw�i�ƃL�����N�^��\�����܂�
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
	// ���a�q�@�a����
	case 0:
		NvSetTxt(12, 17);
		break;
	// �����@���Ƃ���
	case 1:
		NvSetTxt(12, 16);
		break;
	// �������@���̂܂܌����
	case 2:
		NvSetTxt(12, 18);
		break;
	// ����l�@�قɎc��
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

		// �X�N���v�g�����s����O�ɔw�i�ƃL�����N�^��\�����܂�
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
		// �I������`��
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
		// �I��F
		if(sel == 2)
		{
			s32 selCol = ImgGetSelCol();

			_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 3 + selCol], MENU_BUF_SIZE);

			return Menu.buf;
		}

		s32 num;

		// �w�i�P�x�A�̓W�����v
		if(sel == 0)
		{
			num = ImgGetFade();
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
