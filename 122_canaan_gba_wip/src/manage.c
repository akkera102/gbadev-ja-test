#include "manage.h"
#include "libmy/libmy.h"
#include "img.h"
#include "txt.h"
#include "log.h"
#include "menu.h"
#include "nv.h"
#include "bgm.h"
#include "file.h"
#include "siori.h"
#include "anime.h"
#include "se.h"

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

	Manage.act = MANAGE_ACT_NOVEL;
	AnimeSetDat(ANIME_DAT_TITLE);

	// DEBUG1
	// NvSetTxt(0, 1);				// �����G�t�F�N�g
	// NvSetTxt(9, 19);				// DU�X�N���[���G�t�F�N�g
	// NvSetTxt(23, 2);				// DUUD�X�N���[���G�t�F�N�g

	// DEBUG2
	// AnimeSetDat(ANIME_DAT_ENDING);
	// AnimeSetDat(ANIME_DAT_OPENING);
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecNovel(void)
{
	if(SeIsPlay() == true)
	{
		return;
	}

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
	if(ImgIsEffect() == true)
	{
		ImgExec();

		return;
	}

	if(TxtIsChr() == true)
	{
		TxtExecMenu();
	}

	MenuExec();
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
