#include "manage.h"
#include "libmy/libmy.h"
#include "bgm.h"
#include "cur.h"
#include "file.h"
#include "img.h"
#include "info.h"
#include "log.h"
#include "menu.h"
#include "nv.h"
#include "se.h"
#include "siori.h"
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

		case MANAGE_ACT_RES:
			ManageExecRes();
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
void ManageExecInit(void)
{
	SioriInit();

	FileInit();
	BgmInit();
	SeInit();

	InfoInit();
	ImgInit();
	TxtInit();
	CurInit();
	LogInit();
	MenuInit();
	NvInit();

	// DEBUG
//	NvSetScn(3);
//	NvSetScn(7);
//	NvSetScn(12);
//	NvSetScn(20);
//	NvSetScn(75);

//	NvSetScn(84);
//	NvSetVar(28, 1);	// 香織
//	NvSetVar(29, 1);	// 緑
//	NvSetVar(30, 1);	// いろは
//	NvSetVar(31, 1);	// 歌奈

	NvSetScn(0);
	ManageSetAct(MANAGE_ACT_NV);
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
void ManageExecRes(void)
{
	CurSetExec();
	TxtExecRes();

	ManageSetAct(MANAGE_ACT_NV);
}
//---------------------------------------------------------------------------
void ManageExecMenu(void)
{
	// オプションの画像処理用
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
void ManageSetAct(s32 act)
{
	Manage.prv = Manage.act;
	Manage.act = act;
}
//---------------------------------------------------------------------------
bool ManageIsPrv(s32 act)
{
	return (Manage.prv == act) ? true : false;
}
