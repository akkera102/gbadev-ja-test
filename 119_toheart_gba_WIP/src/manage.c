#include "manage.h"
#include "libmy/libmy.h"
#include "img.h"
#include "txt.h"
#include "log.h"
#include "menu.h"
#include "nv.h"
#include "bgm.h"
#include "se.h"
#include "file.h"
#include "siori.h"


//---------------------------------------------------------------------------
ST_MANAGE Manage;


//---------------------------------------------------------------------------
EWRAM_CODE void ManageInit(void)
{
	_Memset(&Manage, 0x00, sizeof(ST_MANAGE));
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExec(void)
{
	for(;;)
	{
//		if(NvIsNext() == false)
//		{
			VBlankIntrWait();
//			SystemCall(5);
//		}

		LibMyExec();


		switch(Manage.act)
		{
		case MANAGE_ACT_INIT:
			ManageExecInit();
			break;

		case MANAGE_ACT_TITLE:
			ManageExecTitle();
			break;

		case MANAGE_ACT_NOVEL:
			ManageExecNovel();
			break;

		case MANAGE_ACT_LOG:
			ManageExecLog();
			break;

		case MANAGE_ACT_MENU:
			ManageExecMenu();
			break;

		default:
			SystemError("[Err] ManageExec act=%x\n", Manage.act);
			break;
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecInit(void)
{
	FileInit();

	BgmInit();
	SeInit();

	ImgInit();
	TxtInit();

	LogInit();
	MenuInit();
	SioriInit();
	NvInit();

//	MenuSetTitle();


// TODO ƒeƒXƒg
	NvSetScn(0);
	NvSetEvt(1);

	Manage.act = MANAGE_ACT_NOVEL;
//	Manage.act = MANAGE_ACT_TITLE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecTitle(void)
{
	ImgExec();
	MenuExec();

//	if(MenuIsEnd() == true)
//	{
//		Manage.act = MANAGE_ACT_SCRIPT;
//	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecNovel(void)
{
	if(ImgIsEffect() == true)
	{
		ImgExec();
		return;
	}

	if(TxtIsChr() == true)
	{
		TxtExecChr();
		return;
	}

	if(TxtIsCur() == true)
	{
		TxtExecCur();
	}

	NvExec();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecLog(void)
{
	LogExec();

	if(TxtIsChr() == true)
	{
		TxtExecLog();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecMenu(void)
{
	MenuExec();

	if(TxtIsChr() == true)
	{
		TxtExecMenu();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageSetLog(void)
{
	Manage.act = MANAGE_ACT_LOG;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageSetMenu(void)
{
	Manage.act = MANAGE_ACT_MENU;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageSetNovel(void)
{
	Manage.act = MANAGE_ACT_NOVEL;
}
