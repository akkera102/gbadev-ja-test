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
	{ "bg",      (void*)AnimeExecBg      },
	{ "vis",     (void*)AnimeExecVis     },
	{ "chr",     (void*)AnimeExecChr     },
	{ "str",     (void*)AnimeExecStr     },
	{ "strcls",  (void*)AnimeExecStrCls  },
	{ "effect1", (void*)AnimeExecEffect1 },
	{ "effect2", (void*)AnimeExecEffect2 },
	{ "wait",    (void*)AnimeExecWait    },
	{ "waitBgm", (void*)AnimeExecWaitBgm },
	{ "bgm",     (void*)AnimeExecBgm     },
	{ "bgmstop", (void*)AnimeExecBgmStop },
	{ "skip",    (void*)AnimeExecSkip    },
	{ "mark",    (void*)AnimeExecMark    },
	{ "sprmode", (void*)AnimeExecSprMode },
	{ "end",     (void*)AnimeExecEnd     },
};

char* AnimeDat[ANIME_MAX_DAT_CNT] = {
	(char*)&ani_1_lo_txt,
	(char*)&ani_2_op_txt,
	(char*)&ani_3_ed_txt,
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

	LexInit();
	LexSetCur(Anime.pCur);

	Anime.act = ANIME_ACT_EXEC;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExec(void)
{
	if(AnimeIsEnd() == true)
	{
		return;
	}

	if(Anime.isSkip == true)
	{
		if(KeyGetCnt() & KEY_START)
		{
			LexSkipStr("mark");

			Anime.wait = 0;
			Anime.isSkip = false;
		}
	}

	if(Anime.wait != 0)
	{
		Anime.wait--;

		return;
	}

	if(Anime.isWaitBgm == true)
	{
		if(VgmGetOffset() < Anime.var)
		{
			return;
		}

		Anime.isWaitBgm = false;
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
EWRAM_CODE void AnimeExecBg(void)
{
	u32 num = LexGetNum();

	ImgSetBgS(num);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecVis(void)
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
	u32 num  = LexGetNum();

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
	u32 n1 = LexGetNum();
	u32 n2 = LexGetNum();

	BgmPlay(n1, (n2 == 1) ? true : false);
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
EWRAM_CODE void AnimeExecMark(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEnd(void)
{
	s32 v = LexGetNum();

	if(v == 0)
	{
		ManageSetNovel();
	}
	else
	{
		MenuSetTitle(MENU_TITLE_SEL_START);
		ManageSetTitle();
	}

	Anime.act = ANIME_ACT_END;
	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
// fadeモジュール内のspr属性を変更（アニメーション後にspr属性をfalseにする）
EWRAM_CODE void AnimeExecSprMode(void)
{
	u32 num = LexGetNum();

	FadeSetSpr((num == 1) ? true : false);
	FadeSetWhite(0);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool AnimeIsEnd(void)
{
	return (Anime.act == ANIME_ACT_END) ? true : false;
}
