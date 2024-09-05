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

	// DEBUG
//	NvSetVar(12, 2);	// 1day カメラ設置場所(true end選択肢)
//	NvSetVar(32, 1);	// 1day 吸殻
//	NvSetVar(14, 2);	// 3day ひろ子に質問
//	NvSetVar(15, 2);	// 4day 恭子の夢
//	NvSetScn("3DAY_A");
//	NvSetScn("4DAY_A");
//	NvSetScn("4DAY_B");
//	NvSetScn("5DAY_A");
//	NvSetScn("5DAY_B");
//	NvSetScn("4BAD");
//	NvSetScn("5BAD_A");
//	NvSetScn("5BAD_B");
//	NvSetScn("5BAD_C");
//	NvSetScn("5BAD_D");
//	NvSetScn("IPL2");
//	NvSetScn("TAI");


	NvSetScn("IPL");
	Manage.act = MANAGE_ACT_NOVEL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ManageExecNovel(void)
{
	if(SeIsWait() == true)
	{
		return;
	}

	if(ImgIsEff() == true)
	{
		ImgExec();

		return;
	}

	if(TxtIsChr() == true)
	{
		TxtExecNv();
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
	if(ImgIsEff() == true)
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
