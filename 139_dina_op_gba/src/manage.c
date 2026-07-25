#include "manage.h"
#include "libmy/libmy.h"
#include "file.h"
#include "img.h"
#include "mus.h"

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
		VBlankIntrWait();

		switch(Manage.act)
		{
		case MANAGE_ACT_INIT:
			ManageExecInit();
			break;

		case MANAGE_ACT_LOGO:
			ManageExecLogo();
			break;

		case MANAGE_ACT_ANIME:
			ManageExecAnime();
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
	FileInit();
	MusInit();
	ImgInit();

	MusStop();
	ImgSetExec(IMG_EFFECT_BOOT);

	Manage.act = MANAGE_ACT_LOGO;
}
//---------------------------------------------------------------------------
void ManageExecLogo(void)
{
	if(ImgIsExec() == true)
	{
		ImgExec();

		return;
	}

	MusPlay();
	ImgSetExec(IMG_EFFECT_ANIME);

	Manage.act = MANAGE_ACT_ANIME;
}
//---------------------------------------------------------------------------
void ManageExecAnime(void)
{
	if(ImgIsExec() == true)
	{
		ImgExec();

		return;
	}

	ImgSetExec(IMG_EFFECT_EXIT);
	Manage.act = MANAGE_ACT_EXIT;
}
//---------------------------------------------------------------------------
void ManageExecExit(void)
{
	if(ImgIsExec() == true)
	{
		ImgExec();

		return;
	}

	MusPlay();
	ImgSetExec(IMG_EFFECT_ANIME);

	Manage.act = MANAGE_ACT_ANIME;
}
