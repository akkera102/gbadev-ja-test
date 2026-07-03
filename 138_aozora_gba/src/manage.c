#include "manage.h"
#include "libmy/libmy.h"
#include "cur.h"
#include "file.h"
#include "img.h"
#include "info.h"
#include "log.h"
#include "menu.h"
#include "mus.h"
#include "nv.h"
#include "seen.h"
#include "siori.h"
#include "snd.h"
#include "txt.h"

//---------------------------------------------------------------------------
ST_MANAGE Manage;


//---------------------------------------------------------------------------
void ManageInit(void)
{
	_Memset(&Manage, 0x00, sizeof(ST_MANAGE));

	LibMyInit();
}
//---------------------------------------------------------------------------
void ManageExec(void)
{
	for(;;)
	{
		if(NvIsSkip() == false)
		{
			VBlankIntrWait();
		}

		LibMyExec();


		switch(Manage.act)
		{
		case MANAGE_ACT_INIT:
			ManageExecInit();
			break;

		case MANAGE_ACT_NV:
			ManageExecNv();
			break;

		case MANAGE_ACT_SEL:
			ManageExecSel();
			break;

		case MANAGE_ACT_LOG:
			ManageExecLog();
			break;

		case MANAGE_ACT_MENU:
			ManageExecMenu();
			break;

		case MANAGE_ACT_EXIT:
			ManageExecExit();
			break;

		default:
			SystemError("[Err] ManageExec act=%x\n", Manage.act);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void ManageExecInit(void)
{
	SioriInit();

	FileInit();
	MusInit();
	SndInit();

	LogInit();
	InfoInit();
	ImgInit();
	TxtInit();
	CurInit();
	MenuInit();
	NvInit();
	SeenInit();

	// DEBUG
//	NvSetNavi(0);
//	NvSetNavi(1);

//	NvSetTxt(1);
//	NvSetTxt(12);
//	NvSetTxt(608);
//	NvSetTxt(609);
//	NvSetTxt(611);
//	NvSetTxt(649);
//	NvSetAct(NV_ACT_PARSE);
//	ManageSetAct(MANAGE_ACT_NV);


///*
	ImgSetBg(5);
	ImgSetChr(800);
	ImgSetExec(IMG_EFFECT_BLACK_OUT);

	ManageSetAct(MANAGE_ACT_EXIT);
//*/
}
//---------------------------------------------------------------------------
void ManageExecNv(void)
{
	if(ImgIsExec() == true)
	{
		ImgExec();

		return;
	}

	if(TxtIsExec() == true)
	{
		TxtExecNv();
	}

	if(CurIsExec() == true)
	{
		CurExec();
	}

	NvExec();
}
//---------------------------------------------------------------------------
void ManageExecSel(void)
{
	if(ImgIsExec() == true)
	{
		ImgExec();

		return;
	}

	if(TxtIsExec() == true)
	{
		TxtExecSel();
	}

	NvExec();
}
//---------------------------------------------------------------------------
void ManageExecLog(void)
{
	if(TxtIsExec() == true)
	{
		TxtExecLog();
	}

	LogExec();
}
//---------------------------------------------------------------------------
void ManageExecMenu(void)
{
	if(ImgIsExec() == true)
	{
		ImgExec();

		return;
	}

	if(TxtIsExec() == true)
	{
		TxtExecMenu();
	}

	MenuExec();
}
//---------------------------------------------------------------------------
void ManageExecExit(void)
{
	if(ImgIsExec() == true)
	{
		ImgExec();

		return;
	}

	NvSetNavi(0);

	LogInit();
	SeenInit();

	SndStop();
	MusPlay(29, true);

	MenuSetTitle(MENU_TITLE_SEL_START);
	ManageSetAct(MANAGE_ACT_MENU);
}
//---------------------------------------------------------------------------
void ManageSetAct(s32 act)
{
	Manage.act = act;
}
