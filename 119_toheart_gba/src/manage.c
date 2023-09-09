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
#include "anime.h"
#include "sakura.h"
#include "rein.h"


//---------------------------------------------------------------------------
ST_MANAGE Manage;


//---------------------------------------------------------------------------
EWRAM_CODE void ManageInit(void)
{
	_Memset(&Manage, 0x00, sizeof(ST_MANAGE));

	LibMyInit();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExec(void)
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

		case MANAGE_ACT_NOVEL:
			ManageExecNovel();
			break;

		case MANAGE_ACT_LOG:
			ManageExecLog();
			break;

		case MANAGE_ACT_MENU:
			ManageExecMenu();
			break;

		case MANAGE_ACT_END:
			ManageExecEnd();
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

	AnimeInit();
	SakuraInit();
	ReinInit();

/*
// DEBUG1
	MenuSetTitle(MENU_TITLE_SEL_START);
	Manage.act = MANAGE_ACT_MENU;
*/

/*
// DEBUG2
	NvSetScn(0x0072);
	NvSetEvt(1);
	Manage.act = MANAGE_ACT_NOVEL;
*/

	AnimeSetDat(ANIME_DAT_LOGO);
//	AnimeSetDat(ANIME_DAT_OPENING);
	Manage.act = MANAGE_ACT_NOVEL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecNovel(void)
{
	if(ImgIsEffect() == true)
	{
		ImgExec();

		return;
	}

	if(AnimeIsExec() == true)
	{
		AnimeExec();

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
	if(TxtIsChr() == true)
	{
		TxtExecLog();
	}

	LogExec();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecMenu(void)
{
	if(TxtIsChr() == true)
	{
		TxtExecMenu();
	}

	MenuExec();
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecEnd(void)
{
	if(ImgIsEffect() == true)
	{
		ImgExec();

		return;
	}

	ManageExecInit();

	AnimeSetDat(ANIME_DAT_TITLE);
	Manage.act = MANAGE_ACT_NOVEL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageSetNovel(void)
{
	Manage.act = MANAGE_ACT_NOVEL;
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
EWRAM_CODE void ManageSetEnd(void)
{
	Manage.act = MANAGE_ACT_END;
}
