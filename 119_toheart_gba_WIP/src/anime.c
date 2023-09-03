#include "anime.h"
#include "res.h"
#include "libmy/key.h"
#include "libmy/lex.h"
#include "libmy/fade.h"
#include "libmy/vgm.arm.h"
#include "img.h"
#include "bgm.h"
#include "se.h"
#include "manage.h"
#include "txt.h"
#include "menu.h"

//---------------------------------------------------------------------------
ROM_DATA ST_ANIME_TABLE AnimePat[ANIME_MAX_PAT_CNT] = {
	{ "bgS",      (void*)AnimeExecBgS      },
	{ "bgV",      (void*)AnimeExecBgV      },
	{ "chr",      (void*)AnimeExecChr      },
	{ "str",      (void*)AnimeExecStr      },
	{ "strCls",   (void*)AnimeExecStrCls   },
	{ "effect1",  (void*)AnimeExecEffect1  },
	{ "effect2",  (void*)AnimeExecEffect2  },
	{ "wait",     (void*)AnimeExecWait     },
	{ "waitBgm",  (void*)AnimeExecWaitBgm  },
	{ "bgm",      (void*)AnimeExecBgm      },
	{ "bgmStop",  (void*)AnimeExecBgmStop  },
	{ "skip",     (void*)AnimeExecSkip     },
	{ "skipMark", (void*)AnimeExecSkipMark },
	{ "sprmode",  (void*)AnimeExecSprMode  },
	{ "end",      (void*)AnimeExecEnd      },
};

char* AnimeDat[ANIME_MAX_DAT_CNT] = {
	(char*)&ani_1_lo_txt,
	(char*)&ani_2_op_txt,
	(char*)&ani_3_ed_txt,
	(char*)&ani_4_ti_txt,
	(char*)&ani_5_om_txt,
};

//---------------------------------------------------------------------------
ST_ANIME Anime;


//---------------------------------------------------------------------------
EWRAM_CODE void AnimeInit(void)
{
	_Memset(&Anime, 0x00, sizeof(ST_ANIME));
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeSetDat(u32 no)
{
	TRACE("\n[AnimeSetDat: %x]\n", no);

	_ASSERT(no < ANIME_MAX_DAT_CNT);

	AnimeInit();

	Anime.pCur = AnimeDat[no];
	Anime.dat  = no;

	LexInit();
	LexSetCur(Anime.pCur);

	Anime.act = ANIME_ACT_EXEC;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExec(void)
{
	if(Anime.isSkip == true)
	{
		if(KeyGetCnt() & KEY_START)
		{
			LexSkipStr("skipMark");

			Anime.wait = 0;
			Anime.isWaitBgm = false;
			Anime.isSkip = false;
		}
	}

	if(Anime.isWaitBgm == true)
	{
		if(VgmGetOffset() < Anime.var)
		{
			return;
		}

		Anime.isWaitBgm = false;
	}

	if(Anime.wait != 0)
	{
		Anime.wait--;

		return;
	}


	Anime.isLoop = true;

	do
	{
		AnimeExecSub();

	} while(Anime.isLoop == true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecSub(void)
{
	char* p = LexGetStr();
	TRACE("[AnimeExec %s]\n", p);

	u32 i;

	for(i=0; i<ANIME_MAX_PAT_CNT; i++)
	{
		if(_Strncmp(p, AnimePat[i].pStr, ANIME_MAX_STR_SIZE) == 0)
		{
			break;
		}
	}
	_ASSERT(i < ANIME_MAX_PAT_CNT);


	AnimePat[i].pFunc();
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecBgS(void)
{
	u32 num = LexGetNum();

	ImgSetBgS(num);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecBgV(void)
{
	u32 num = LexGetNum();

	ImgSetBgV(num);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecChr(void)
{
	u32 num = LexGetNum();
	u32 pos = LexGetNum();

	ImgSetChr(num, pos);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecStr(void)
{
	u32 x = LexGetNum();
	u32 y = LexGetNum();
	char* s = LexGetStr();

	TxtDrawStrXy(x, y, s);
	TxtShowMsg();
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecStrCls(void)
{
	TxtClear();

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEffect1(void)
{
	u32 num = LexGetNum();

	ImgSetEffectBefore(num);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEffect2(void)
{
	u32 num = LexGetNum();

	ImgSetEffectAfter(num);

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
	u32 no   = LexGetNum();
	u32 loop = LexGetNum();

	BgmPlay(no, (loop == 1) ? true : false);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecWaitBgm(void)
{
	Anime.var = LexGetNum();

	Anime.isWaitBgm = true;
	Anime.isLoop = false;
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
	// ロゴもしくはタイトルの場合、選択肢へ
	if(Anime.dat == ANIME_DAT_LOGO || Anime.dat == ANIME_DAT_TITLE)
	{
		MenuSetTitle(MENU_TITLE_SEL_START);
		ManageSetMenu();
	}

	Anime.act = ANIME_ACT_END;
	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecSprMode(void)
{
	u32 num = LexGetNum();

	// spr属性を変更。sprとfadeを同時に行う
	FadeSetSpr((num == 1) ? true : false);
	FadeSetWhite(0);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool AnimeIsExec(void)
{
	return (Anime.act == ANIME_ACT_END) ? false : true;
}
