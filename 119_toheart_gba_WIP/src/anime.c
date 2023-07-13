#include "anime.h"
#include "libmy/key.h"
#include "libmy/lex.h"
#include "res.h"
#include "img.h"
#include "img2.h"
#include "bgm.h"
#include "se.h"
#include "nv.h"


//---------------------------------------------------------------------------
ST_ANIME_TABLE AnimePat[ANIME_MAX_PAT_CNT] = {
	{ "img1",     (void*)AnimeExecImg1    },
	{ "img2",     (void*)AnimeExecImg2    },
	{ "img3",     (void*)AnimeExecImg3    },
	{ "img_line", (void*)AnimeExecImgLine },
	{ "effect1",  (void*)AnimeExecEffect1 },
	{ "effect2",  (void*)AnimeExecEffect2 },
	{ "fill",     (void*)AnimeExecFill    },
	{ "wait",     (void*)AnimeExecWait    },
	{ "key_wait", (void*)AnimeExecKeyWait },
	{ "bgm",      (void*)AnimeExecBgm     },
	{ "loop",     (void*)AnimeExecLoop    },
	{ "inc",      (void*)AnimeExecInc     },
	{ "dec",      (void*)AnimeExecDec     },
	{ "jae" ,     (void*)AnimeExecJae     },
	{ "jbe" ,     (void*)AnimeExecJbe     },
	{ "end",      (void*)AnimeExecEnd     },
};

const char* AnimeDat[ANIME_MAX_DAT_CNT] = {
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

	Anime.act = ANIME_ACT_END;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeSetDat(u32 no)
{
	TRACE("[AnimeSetDat: %x]\n", no);

	AnimeInit();

	_ASSERT(no < ANIME_MAX_DAT_CNT);
	Anime.pCur = (char*)AnimeDat[no];

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

	if(Anime.waitCnt != 0)
	{
		Anime.waitCnt--;
		return;
	}

	if(Anime.isKey == true)
	{
		return;
	}
	Anime.isKey = false;


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
EWRAM_CODE void AnimeExecImg1(void)
{
	u32 num = LexGetNum();
	ImgSetBg(num);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecImg2(void)
{
	u32 num = LexGetNum();
	u32 x   = LexGetNum();
	u32 y   = LexGetNum();

	ImgDirectCrop(num, x, y);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecImg3(void)
{
	u32 num = LexGetNum();
	u32 x   = LexGetNum();
	u32 y   = LexGetNum();

	ImgDirectBlend(num, x, y);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecImgLine(void)
{
	u32 num = LexGetNum();
	u32 cnt = Anime.var;

	if(cnt >= 160)
	{
		cnt = 159;
	}
	ImgDirectLine(num, cnt);

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEffect1(void)
{
	u32 num  = LexGetNum();

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
EWRAM_CODE void AnimeExecFill(void)
{
	u32 r = LexGetNum();
	u32 g = LexGetNum();
	u32 b = LexGetNum();

	ImgDirectFill(RGB5(r, g, b));

	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecWait(void)
{
	Anime.waitCnt = LexGetNum();
	Anime.isLoop  = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecKeyWait(void)
{
	Anime.isKey  = true;
	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecBgm(void)
{
	u32 n1 = LexGetNum();
	u32 n2 = LexGetNum();
	bool isLoop = (n2 == 1) ? true : false;

	BgmPlay2(n1, isLoop);

	Anime.isLoop  = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecLoop(void)
{
	Anime.var  = LexGetNum();
	Anime.pCur = LexGetCur();
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecInc(void)
{
	Anime.var++;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecDec(void)
{
	Anime.var--;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecJae(void)
{
	s32 v = LexGetNum();

	if(Anime.var >= v)
	{
		LexSetCur(Anime.pCur);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecJbe(void)
{
	s32 v = LexGetNum();

	if(Anime.var <= v)
	{
		LexSetCur(Anime.pCur);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEnd(void)
{
	Anime.act = ANIME_ACT_END;
	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool AnimeIsEnd(void)
{
	return (Anime.act == ANIME_ACT_END) ? true : false;
}
