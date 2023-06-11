#include "manage.h"
#include "img.h"
#include "text.h"
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
IWRAM_CODE void ManageExec(void)
{
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
//---------------------------------------------------------------------------
IWRAM_CODE void ManageExecInit(void)
{
	FileInit();

	BgmInit();
	SeInit();

	ImgInit();
	TextInit();

	LogInit();
	MenuInit();
	NvInit();

	SioriInit();
//	MenuSetTitle();


// TODO ƒeƒXƒg
	NvSetScn(0);
	NvSetEvt(1);

	Manage.act = MANAGE_ACT_NOVEL;
//	Manage.act = MANAGE_ACT_TITLE;
}
//---------------------------------------------------------------------------
IWRAM_CODE void ManageExecTitle(void)
{
/*
	ImgExec();
	MenuExec();

	if(MenuIsEnd() == TRUE)
	{
		Manage.act = MANAGE_ACT_SCRIPT;
	}
*/
}
//---------------------------------------------------------------------------
IWRAM_CODE void ManageExecNovel(void)
{
	if(ImgIsEffect() == TRUE)
	{
		ImgExec();
		return;
	}

	if(TextIsChr() == TRUE)
	{
		TextExecChr();
		return;
	}

	if(TextIsCur() == TRUE)
	{
		TextExecCur();
	}

	NvExec();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecLog(void)
{
	LogExec();

	if(TextIsChr() == TRUE)
	{
		TextExecLog();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecMenu(void)
{
	MenuExec();

	if(TextIsChr() == TRUE)
	{
		TextExecMenu();
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
