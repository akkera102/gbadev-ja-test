#include "anime.h"
#include "res.h"
#include "libmy/key.h"
#include "libmy/lex.h"
#include "libmy/mode3.arm.h"
#include "libmy/spr.h"
#include "img.h"
#include "bgm.h"
#include "manage.h"
#include "txt.h"
#include "menu.h"
#include "file.h"
#include "nv.h"
#include "se.h"

//---------------------------------------------------------------------------
ST_ANIME_TABLE AnimePat[ANIME_MAX_PAT_CNT] = {
	{ "set",      (void*)AnimeExecSet      },
	{ "clear",    (void*)AnimeExecClear    },
	{ "str",      (void*)AnimeExecStr      },
	{ "strCls",   (void*)AnimeExecStrCls   },
	{ "effect",   (void*)AnimeExecEffect   },
	{ "wait",     (void*)AnimeExecWait     },
	{ "bgm",      (void*)AnimeExecBgm      },
	{ "bgmStop",  (void*)AnimeExecBgmStop  },
	{ "skip",     (void*)AnimeExecSkip     },
	{ "skipMark", (void*)AnimeExecSkipMark },
	{ "end",      (void*)AnimeExecEnd      },
};

char* AnimeDat[ANIME_MAX_DAT_CNT] = {
	(char*)&ani_1_ed_txt,
	(char*)&ani_2_ti_txt,
	(char*)&ani_3_pa_txt,
};

//---------------------------------------------------------------------------
ST_ANIME Anime;


//---------------------------------------------------------------------------
EWRAM_CODE void AnimeInit(void)
{
	_Memset(&Anime, 0x00, sizeof(ST_ANIME));
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeSetDat(s32 num)
{
	TRACE("\n[AnimeSetDat:%x]\n", num);

	_ASSERT(num < ANIME_MAX_DAT_CNT);

	AnimeInit();
	Anime.pCur = AnimeDat[num];
	Anime.dat = num;

	LexInit();
	LexSetCur(Anime.pCur);

	Anime.act = ANIME_ACT_EXEC;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeSetArg(s32 num)
{
	Anime.arg = num;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExec(void)
{
	if(Anime.wait != 0)
	{
		Anime.wait--;

		return;
	}


	Anime.isLoop = true;

	do
	{
		char* p = LexGetStr();
		TRACE("[AnimeExec %s]\n", p);

		s32 i;

		for(i=0; i<ANIME_MAX_PAT_CNT; i++)
		{
			if(_Strncmp(p, AnimePat[i].pStr, ANIME_MAX_STR_SIZE) == 0)
			{
				break;
			}
		}
		_ASSERT(i < ANIME_MAX_PAT_CNT);

		AnimePat[i].pFunc();


	} while(Anime.isLoop == true);
}
//---------------------------------------------------------------------------
// スキップ処理の実行有無
EWRAM_CODE void AnimeExecChk(void)
{
	if(KeyGetCnt() & KEY_START)
	{
		LexSkipStr("skipMark");
		ImgSetEff(IMG_EFFECT_BLACK_RECT);

		Anime.wait = 0;
		Anime.isSkip = false;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecSet(void)
{
	char* p = LexGetStr();
	s32  no = LexGetNum();

	switch(no)
	{
	case 1: ImgSetBg(p);  break;
	case 2: ImgSetChr(p); break;

	default:
		SystemError("[Err] AnimeExecSet no=%x\n", no);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecClear(void)
{
	s32 no = LexGetNum();

	switch(no)
	{
	case 1: ImgClrBg();    break;
	case 2: ImgClrChr();   break;
	case 3: ImgClrBgChr(); break;

	default:
		SystemError("[Err] AnimeExecClear no=%x\n", no);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecStr(void)
{
	s32 x = LexGetNum();
	s32 y = LexGetNum();
	char* s = LexGetStr();

	TxtDrawStr2(x, y, s);
	TxtShowMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecStrCls(void)
{
	TxtHideMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEffect(void)
{
	s32 num = LexGetNum();

	ImgSetEff(num);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecWait(void)
{
	Anime.wait = LexGetNum();

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecBgm(void)
{
	s32 no   = LexGetNum();
	s32 loop = LexGetNum();

	BgmPlay2(no, (loop == 1) ? true : false);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecBgmStop(void)
{
	BgmStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecSkip(void)
{
	Anime.isSkip = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecSkipMark(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEnd(void)
{
	Anime.act = ANIME_ACT_END;
	Anime.isLoop = false;


	switch(Anime.dat)
	{
	case ANIME_DAT_TITLE:
		MenuSetTitle(MENU_TITLE_SEL_LOAD);
		ManageSetMenu();
		break;

	case ANIME_DAT_ENDING:
		AnimeSetDat(ANIME_DAT_TITLE);
		break;

	default:
		// EMPTY
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool AnimeIsExec(void)
{
	return (Anime.act == ANIME_ACT_END) ? false : true;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool AnimeIsSkip(void)
{
	return Anime.isSkip;
}
