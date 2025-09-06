#include "menu.h"
#include "libbios/swi.h"
#include "libmy/key.h"
#include "libmy/vgm.arm.h"
#include "bgm.h"
#include "cur.h"
#include "img.h"
#include "info.h"
#include "log.h"
#include "manage.h"
#include "nv.h"
#include "se.h"
#include "siori.h"
#include "txt.h"

//---------------------------------------------------------------------------
ROM_DATA char MenuSelectStr[][26+1] = {
	// 0
	"",
	"�@�@�Z�[�u",
	"�@�@���[�h",
	"�@�@��������",
	"�@�@����������",
	"�@�@���b�Z�[�W����",
	"�@�@�I�v�V����",
	"�@�@�f�o�b�O",
	"�@�@�Q�[���I��",

	// 9
	"�@�I�v�V����",
	"�@�w�i�P�x�@�@�O�O",
	"�@���y���ʁ@�@�O�O",
	"�@�摜�@�@�@�@�O�O",
	"�@���y�@�@�@�@�O�O",
	"�@���ʉ��@�@�@�O�O",
	"�@���Ǖ����@�@",
	"�@���ǖ����@�@",

	// 17
	"�@�@�@�Z�[�u",

	// 18
	"�@�@�@���[�h",

	// 19
	"",

	// 20
	"",
	"�ŏ�����n�߂�",
	"�@���[�h����",

	// 23
	"�D���x�A�����t���O",
	"���D�@�@�P�U�F�O�@�Q�W�F�O",
	"�΁@�@�@�Q�P�F�O�@�Q�X�F�O",
	"����́@�Q�Q�F�O�@�R�O�F�O",
	"�̓ށ@�@�Q�O�F�O�@�R�P�F�O",
	"��G�q�@�Q�U�F�O�@�R�Q�F�O",
	"����@�@�Q�V�F�O�@�R�R�F�O",
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

		TxtSetExec();
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

		TxtSetExec();
	}
}
//---------------------------------------------------------------------------
void MenuExecSystem(u16 trg)
{
	if(trg & KEY_B)
	{
		// �߂��F�m�x�� or �I����
		if(NvIsAct(NV_ACT_KEY) == true)
		{
			ManageSetAct(MANAGE_ACT_RES);
		}
		else
		{
			ManageSetAct(MANAGE_ACT_SEL);
		}

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
		// �߂��F�m�x�� or �I����
		if(NvIsAct(NV_ACT_KEY) == true)
		{
			NvSetSkip();
			ManageSetAct(MANAGE_ACT_RES);
		}
		else
		{
			ManageSetAct(MANAGE_ACT_SEL);
		}
		break;

	// ����������
	case 3:
		MenuSetNone(MENU_RET_SYSTEM);
		break;

	// �V�i���I��z
	case 4:
		if(LogIsEmpty() == false)
		{
			LogSetInit();

			ManageSetAct(MANAGE_ACT_LOG);
		}
		break;

	// �I�v�V����
	case 5:
		MenuSetOption(MENU_OPTION_SEL_FADE);
		break;

	// �f�o�b�O
	case 6:
		MenuSetDebug(MENU_DEBUG_VAR_1);
		break;

	// �Q�[���I��
	case 7:
		LogInit();
		TxtClear();

		SeStop();
		BgmPlay(0);

		MenuSetTitle(MENU_TITLE_SEL_LOAD);

		ImgSetEff(IMG_EFFECT_TITL);
		ImgSetExec();
		break;
	}
}
//---------------------------------------------------------------------------
void MenuExecOption(u16 trg)
{
	if(trg & KEY_B)
	{
		MenuSetSystem(MENU_SYSTEM_SEL_OPTION);

		return;
	}

	switch(Menu.sel)
	{
	// �w�i�P�x
	case 0:
		s32 fade = ImgGetFade();

		if(trg & KEY_LEFT && fade > 0)
		{
			fade--;

			ImgSetFade(fade);
			TxtSetExec();
		}

		if(trg & KEY_RIGHT && fade < 9)
		{
			fade++;

			ImgSetFade(fade);
			TxtSetExec();
		}
		break;

	// ���y����
	case 1:
		s32 vol = VgmGetVol();

		if(trg & KEY_LEFT && vol > 0)
		{
			vol--;

			VgmSetVol(vol);
			TxtSetExec();
		}

		if(trg & KEY_RIGHT && vol < VGM_VOL_MAX_CNT)
		{
			vol++;

			VgmSetVol(vol);
			TxtSetExec();
		}
		break;

	// �摜
	case 2:
		if(trg & KEY_L)
		{
			Menu.img -= 10;

			if(Menu.img < 0)
			{
				Menu.img = 0;
			}

			TxtSetExec();
		}

		if(trg & KEY_R)
		{
			Menu.img += 10;

			if(Menu.img > INFO_MAX_IMG_CNT-1)
			{
				Menu.img = INFO_MAX_IMG_CNT-1;
			}

			TxtSetExec();
		}

		if(trg & KEY_LEFT && Menu.img > 0)
		{
			Menu.img--;

			TxtSetExec();
		}

		if(trg & KEY_RIGHT && Menu.img < INFO_MAX_IMG_CNT-1)
		{
			Menu.img++;

			TxtSetExec();
		}

		if(trg & KEY_A)
		{
			s32 no = InfoGetImg(Menu.img);

			ImgSetBg(no);
			ImgClrChrAll();
			ImgSetEff(IMG_EFFECT_COPY);
			ImgSetExec();
		}
		break;

	// ���y
	case 3:
		if(trg & KEY_L)
		{
			Menu.bgm -= 10;

			if(Menu.bgm < 0)
			{
				Menu.bgm = 0;
			}

			TxtSetExec();
		}

		if(trg & KEY_R)
		{
			Menu.bgm += 10;

			if(Menu.bgm > INFO_MAX_BGM_CNT-1)
			{
				Menu.bgm = INFO_MAX_BGM_CNT-1;
			}

			TxtSetExec();
		}

		if(trg & KEY_LEFT && Menu.bgm > 0)
		{
			Menu.bgm--;

			TxtSetExec();
		}

		if(trg & KEY_RIGHT && Menu.bgm < INFO_MAX_BGM_CNT-1)
		{
			Menu.bgm++;

			TxtSetExec();
		}

		if(trg & KEY_A)
		{
			s32 no = InfoGetBgm(Menu.bgm);

			BgmPlay(no);
		}
		break;

	// ���ʉ�
	case 4:
		if(trg & KEY_L)
		{
			Menu.fmx -= 10;

			if(Menu.fmx < 0)
			{
				Menu.fmx = 0;
			}

			TxtSetExec();
		}

		if(trg & KEY_R)
		{
			Menu.fmx += 10;

			if(Menu.fmx > INFO_MAX_FMX_CNT-1)
			{
				Menu.fmx = INFO_MAX_FMX_CNT-1;
			}

			TxtSetExec();
		}

		if(trg & KEY_LEFT && Menu.fmx > 0)
		{
			Menu.fmx--;

			TxtSetExec();
		}

		if(trg & KEY_RIGHT && Menu.fmx < INFO_MAX_FMX_CNT-1)
		{
			Menu.fmx++;

			TxtSetExec();
		}

		if(trg & KEY_A)
		{
			s32 no = InfoGetFmx(Menu.fmx);

			SePlay(no);
		}
		break;

	// ���Ǖ���
	case 5:
		if(trg & KEY_L)
		{
			Menu.col = 0;

			TxtSetExec();
		}

		if(trg & KEY_R)
		{
			Menu.col = 3-1;

			TxtSetExec();
		}

		if(trg & KEY_LEFT && Menu.col > 0)
		{
			Menu.col--;
			SprSetSelectCol(Menu.col);

			TxtSetExec();
		}

		if(trg & KEY_RIGHT && Menu.col < 3-1)
		{
			Menu.col++;
			SprSetSelectCol(Menu.col);

			TxtSetExec();
		}
		break;

	// ���ǖ���
	case 6:
		if(trg & KEY_LEFT || trg & KEY_RIGHT)
		{
			if(NvIsOmit() == true)
			{
				NvSetOmit(false);
			}
			else
			{
				NvSetOmit(true);
			}

			TxtSetExec();
		}
		break;
	}
}
//---------------------------------------------------------------------------
void MenuExecSave(u16 trg)
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

		// �߂��F�m�x�� or �I����
		if(NvIsAct(NV_ACT_KEY) == true)
		{
			ManageSetAct(MANAGE_ACT_RES);
		}
		else
		{
			ManageSetAct(MANAGE_ACT_SEL);
		}

		return;
	}
}
//---------------------------------------------------------------------------
void MenuExecLoad(u16 trg)
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
	SioriLoadNvRead();

	NvSetAct(NV_ACT_LOAD);
	ManageSetAct(MANAGE_ACT_NV);
}
//---------------------------------------------------------------------------
void MenuExecNone(u16 trg)
{
	if(trg & KEY_B || trg & KEY_L)
	{
		ImgLoadFade();

		if(Menu.ret == MENU_RET_SYSTEM)
		{
			// �V�X�e�����j���[�ɕ��A
			MenuSetSystem(MENU_SYSTEM_SEL_NONE);
		}
		else
		{
			// �m�x�� or �I����
			if(ManageIsPrv(MANAGE_ACT_NV) == true)
			{
				ManageSetAct(MANAGE_ACT_RES);
			}
			else
			{
				ManageSetAct(MANAGE_ACT_SEL);
			}
		}
	}
}
//---------------------------------------------------------------------------
void MenuExecTitle(u16 trg)
{
	if(!(trg & KEY_A))
	{
		return;
	}

	switch(Menu.sel)
	{
	// �ŏ�����n�߂�
	case 0:
		ImgLoadFade();

		LogInit();
		TxtClear();

		NvInitVar();
		NvSetScn(3);

		NvSetAct(NV_ACT_PARSE);
		ManageSetAct(MANAGE_ACT_NV);
		break;

	// ���[�h����
	case 1:
		MenuSetLoad(MENU_RET_TITLE);
		break;
	}
}
//---------------------------------------------------------------------------
void MenuExecDebug(u16 trg)
{
	if(trg & KEY_B)
	{
		MenuSetSystem(MENU_SYSTEM_SEL_DEBUG);

		return;
	}
}
//---------------------------------------------------------------------------
void MenuSetInit(s32 type, s32 ret, s32 sel, s32 msg, s32 reg, void* pFunc, bool isDraw)
{
	Menu.type  = type;
	Menu.ret   = ret;
	Menu.sel   = sel;
	Menu.msg   = msg;
	Menu.reg   = reg;
	Menu.pFunc = pFunc;

	CurHide();

	if(isDraw == true)
	{
		TxtSetExec();
	}
}
//---------------------------------------------------------------------------
void MenuSetSystem(s32 sel)
{
	MenuSetInit(MENU_TYPE_SYSTEM, MENU_RET_NONE, sel, 0, 8, MenuExecSystem, true);
}
//---------------------------------------------------------------------------
void MenuSetOption(s32 sel)
{
	MenuSetInit(MENU_TYPE_OPTION, MENU_RET_SYSTEM, sel, 9, 7, MenuExecOption, true);
}
//---------------------------------------------------------------------------
void MenuSetSave(s32 ret)
{
	MenuSetInit(MENU_TYPE_SAVE, ret, Menu.siori, 17, 8, MenuExecSave, true);
}
//---------------------------------------------------------------------------
void MenuSetLoad(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, Menu.siori, 18, 8, MenuExecLoad, true);
}
//---------------------------------------------------------------------------
void MenuSetNone(s32 ret)
{
	MenuSetInit(MENU_TYPE_LOAD, ret, 0, 19, 0, MenuExecNone, false);

	TxtHide();
	ImgSetFade2(0);
}
//---------------------------------------------------------------------------
void MenuSetTitle(s32 sel)
{
	MenuSetInit(MENU_TYPE_TITLE, MENU_RET_NONE, sel, 20, 2, MenuExecTitle, true);
}
//---------------------------------------------------------------------------
void MenuSetDebug(s32 ret)
{
	MenuSetInit(MENU_TYPE_DEBUG, MENU_RET_SYSTEM, ret, 23, 6, MenuExecDebug, true);
}
//---------------------------------------------------------------------------
void MenuLoadSelCol(void)
{
	SprSetSelectCol(Menu.col);
}
//---------------------------------------------------------------------------
char* MenuGetStrTitle(void)
{
	return (char*)MenuSelectStr[Menu.msg];
}
//---------------------------------------------------------------------------
char* MenuGetStrSel(s32 sel)
{
	switch(Menu.type)
	{
	case MENU_TYPE_SAVE:
	case MENU_TYPE_LOAD:
		return SioriGetTitle(sel);

	case MENU_TYPE_OPTION:
		return MenuGetStrSelOpt(sel);

	case MENU_TYPE_DEBUG:
		return MenuGetStrSelDbg(sel);
	}

	return (char*)MenuSelectStr[Menu.msg + 1 + sel];
}
//---------------------------------------------------------------------------
char* MenuGetStrSelOpt(s32 sel)
{
	_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 1 + sel], MENU_BUF_SIZE);

	s32 num = 0;

	switch(sel)
	{
	case 0:
		num = ImgGetFade();
		break;

	case 1:
		num = VgmGetVol();
		break;

	case 2:
		num = Menu.img;
		break;

	case 3:
		num = Menu.bgm;
		break;

	case 4:
		num = Menu.fmx;
		break;

	case 5:
		if(Menu.col == 0)
		{
			_Strcat(Menu.buf, "���F");
		}
		else if(Menu.col == 1)
		{
			_Strcat(Menu.buf, "���F");
		}
		else
		{
			_Strcat(Menu.buf, "���F");
		}
		return Menu.buf;

	default:
		if(NvIsOmit() == true)
		{
			_Strcat(Menu.buf, "����");
		}
		else
		{
			_Strcat(Menu.buf, "�Ȃ�");
		}
		return Menu.buf;
	}

	// SJIS�u�O�v0x82 0x4f
	Menu.buf[15] = 0x4f + SwiDiv(num, 10);
	Menu.buf[17] = 0x4f + SwiDivMod(num, 10);

	return Menu.buf;
}
//---------------------------------------------------------------------------
char* MenuGetStrSelDbg(s32 sel)
{
	_Strncpy(Menu.buf, (char*)MenuSelectStr[Menu.msg + 1 + sel], MENU_BUF_SIZE);

	s32 v1 = 0;
	s32 v2 = 0;

	switch(sel)
	{
	case 0:
		v1 = NvGetVar(16);
		v2 = NvGetVar(28);
		break;

	case 1:
		v1 = NvGetVar(21);
		v2 = NvGetVar(29);
		break;

	case 2:
		v1 = NvGetVar(22);
		v2 = NvGetVar(30);
		break;

	case 3:
		v1 = NvGetVar(20);
		v2 = NvGetVar(31);
		break;

	case 4:
		v1 = NvGetVar(26);
		v2 = NvGetVar(32);
		break;

	case 5:
		v1 = NvGetVar(27);
		v2 = NvGetVar(33);
		break;

	default:
		SystemError("[Err] MenuGetStrSelDbg sel=%x\n", sel);
		break;
	}

	// SJIS�u�O�v0x82 0x4f
	Menu.buf[15] = 0x4f + v1;
	Menu.buf[25] = 0x4f + v2;

	return Menu.buf;
}
//---------------------------------------------------------------------------
s32 MenuGetSel(void)
{
	return Menu.sel;
}
//---------------------------------------------------------------------------
s32 MenuGetReg(void)
{
	return Menu.reg;
}
//---------------------------------------------------------------------------
s32 MenuGetType(void)
{
	return Menu.type;
}
//---------------------------------------------------------------------------
s32 MenuGetCol(void)
{
	return Menu.col;
}
