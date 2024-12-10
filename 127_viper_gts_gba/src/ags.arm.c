#include "ags.arm.h"
#include "libmy/libmy.h"
#include "nv.h"
#include "anm.h"
#include "menu.h"
#include "img.h"
#include "txt.h"
#include "bgm.h"
#include "pcm.h"
#include "file.h"
#include "info.h"
#include "siori.h"


//---------------------------------------------------------------------------
ST_AGS Ags;


//---------------------------------------------------------------------------
EWRAM_CODE void AgsInit(void)
{
	_Memset(&Ags, 0x00, sizeof(ST_AGS));


	LibMyInit();

	FileInit();
	InfoInit();
	BgmInit();
	PcmInit();

	ImgInit();
	AnmInit();
	TxtInit();
	MenuInit();
	SioriInit();
	NvInit();

/*
	DEBUG

	GTS0 1-6
	GTS1 7-25
	GTS2 26-39   132 136 137
	GTS3 40-72   144 155 172
	GTS4 73-105  175 176
*/
//	NvSetVar(201, 1);			//   メルセデスH 0 or 1
//	NvSetVar(200, 2);			// もっとカルラH 0 or 2
//	NvSetScn3(7);


	NvSetScn("START");
	Ags.act = AGS_ACT_NOVEL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AgsIntrVblank(void)
{
	LibMyExec();

	switch(Ags.act)
	{
	case AGS_ACT_NOVEL:
		AgsExecNovel();
		break;

	case AGS_ACT_SELECT:
		AgsExecSelect();
		break;

	case AGS_ACT_MENU:
		AgsExecMenu();
		break;

	case AGS_ACT_LOAD:
		AgsExecLoad();
		break;

	default:
		SystemError("[Err] AgsExec act=%x\n", Ags.act);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AgsExecNovel(void)
{
	if(TxtIsMsg() == true)
	{
		TxtExecMsg();
	}

	if(TxtIsCur() == true)
	{
		TxtExecCur();
	}

	if(ImgIsEff() == true)
	{
		ImgExec();

		return;
	}

	NvExec();
}
//---------------------------------------------------------------------------
EWRAM_CODE void AgsExecSelect(void)
{
	if(TxtIsMsg() == true)
	{
		TxtExecSel();
	}

	if(ImgIsEff() == true)
	{
		ImgExec();

		return;
	}

	NvExec();
}
//---------------------------------------------------------------------------
EWRAM_CODE void AgsExecMenu(void)
{
	if(TxtIsMsg() == true)
	{
		TxtExecMenu();
	}

	if(ImgIsEff() == true)
	{
		ImgExec();

		return;
	}

	MenuExec();
}
//---------------------------------------------------------------------------
EWRAM_CODE void AgsExecLoad(void)
{
	u16 v1 = NvGetVar(17);
	u16 v2 = NvGetVar(201);
	u16 v3 = NvGetVar(200);

	NvInit();
	AnmInit();
	ImgInit();
	TxtInit();

	NvSetVar( 17, v1);
	NvSetVar(201, v2);
	NvSetVar(200, v3);
	NvSetScn2(v1);

	Ags.act = AGS_ACT_NOVEL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AgsSetNovel(void)
{
	Ags.act = AGS_ACT_NOVEL;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AgsSetSelect(void)
{
	Ags.act = AGS_ACT_SELECT;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AgsSetMenu(void)
{
	Ags.act = AGS_ACT_MENU;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AgsSetLoad(void)
{
	Ags.act = AGS_ACT_LOAD;
}
