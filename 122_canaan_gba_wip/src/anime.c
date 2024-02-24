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

//---------------------------------------------------------------------------
ST_ANIME_TABLE AnimePat[ANIME_MAX_PAT_CNT] = {
	{ "pata",     (void*)AnimeExecPata     },
	{ "pata2",    (void*)AnimeExecPata2    },
	{ "pat" ,     (void*)AnimeExecPat      },
	{ "set",      (void*)AnimeExecSet      },
	{ "clear",    (void*)AnimeExecClear    },
	{ "str",      (void*)AnimeExecStr      },
	{ "strCls",   (void*)AnimeExecStrCls   },
	{ "effect",   (void*)AnimeExecEffect   },
	{ "blend",    (void*)AnimeExecBlend    },
	{ "wait",     (void*)AnimeExecWait     },
	{ "waitBgm",  (void*)AnimeExecWaitBgm  },
	{ "bgm",      (void*)AnimeExecBgm      },
	{ "bgmStop",  (void*)AnimeExecBgmStop  },
	{ "skip",     (void*)AnimeExecSkip     },
	{ "skipMark", (void*)AnimeExecSkipMark },
	{ "fontCol",  (void*)AnimeExecFontCol  },
	{ "fontIn",   (void*)AnimeExecFontIn   },
	{ "fontOut",  (void*)AnimeExecFontOut  },
	{ "envSave",  (void*)AnimeExecEnvSave  },
	{ "envLoad",  (void*)AnimeExecEnvLoad  },
	{ "envFade",  (void*)AnimeExecEnvFade  },
	{ "end",      (void*)AnimeExecEnd      },
};

char* AnimeDat[ANIME_MAX_DAT_CNT] = {
	(char*)&ani_1_op_txt,
	(char*)&ani_2_ed_txt,
	(char*)&ani_3_ti_txt,
	(char*)&ani_4_p1_txt,
	(char*)&ani_5_p2_txt,
	(char*)&ani_6_p3_txt,
	(char*)&ani_7_p4_txt,
	(char*)&ani_8_p5_txt,
	(char*)&ani_9_p6_txt,
	(char*)&ani_A_nr_txt,
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
	if(Anime.isSkip == true && KeyGetCnt() & KEY_START)
	{
		LexSkipStr("skipMark");

		Anime.wait = 0;
		Anime.waitBgm = 0;
		Anime.isSkip = false;
	}

	if(Anime.wait != 0)
	{
		Anime.wait--;

		return;
	}

	if(Anime.waitBlend != 0)
	{
		Mode3VramBlendCopy(Anime.var[0], Anime.var[1], Anime.var[2], Anime.var[3], 32 - Anime.waitBlend);

		Anime.waitBlend--;
		return;
	}

	if(Anime.waitFontIn != 0)
	{
		u32 c = 32 - Anime.waitFontIn;
		SprSetSelectCol(RGB5(c, c, c));

		Anime.waitFontIn--;
		return;
	}

	if(Anime.waitFontOut != 0)
	{
		u32 c = Anime.waitFontOut - 1;
		SprSetSelectCol(RGB5(c, c, c));

		Anime.waitFontOut--;
		return;
	}

	if(Anime.waitBgm != 0)
	{
		if(BgmGetOffset() < Anime.waitBgm)
		{
			return;
		}

		Anime.waitBgm = 0;
	}

//	TRACE("%d\n", BgmGetOffset());


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
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecPata(void)
{
	s32 n = LexGetNum();
	s32 w = LexGetNum();

	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetPata(n);
	Mode3DrawPat(SCREEN_CX/2 - h->cx/2, SCREEN_CY/2 - h->cy/2 - 24, h->cx, h->cy, (u16*)(h + 1));
	Mode3SetDraw();

	Anime.wait = w;
	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecPata2(void)
{
	s32 n = LexGetNum();

	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetPata(n);
	Mode3DrawPat(SCREEN_CX/2 - h->cx/2, SCREEN_CY/2 - h->cy/2 - 24, h->cx, h->cy, (u16*)(h + 1));
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecPat(void)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetPat(Anime.arg);
	Mode3DrawFull((u16*)(h + 1));
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecSet(void)
{
	char* p = LexGetStr();
	s32  no = LexGetNum();

	switch(no)
	{
	case 1:  ImgSetBgl(p);   break;
	case 2:  ImgSetBgc(p);   break;
	case 3:  ImgSetBgb(p);   break;
	case 4:  ImgSetChr1(p);  break;
	case 5:  ImgSetChr2(p);  break;
	case 6:  ImgSetPty(p);   break;
	case 7:  ImgSetIco(p);   break;
	case 8:  ImgSetMin(p);   break;
	case 9:  ImgSetScrDu(p); break;
	case 10: ImgSetScrUd(p); break;

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
	case 1: ImgClrBg();   break;
	case 2: ImgClrChr1(); break;
	case 3: ImgClrChr2(); break;
	case 4: ImgClrPty();  break;
	case 5: ImgClrIco();  break;
	case 6: ImgClrMin();  break;
	case 7: ImgClrAll();  break;
	case 8: ImgClrIco(); ImgDrawIcoClear(); break;
	case 9: ImgClrMin(); ImgDrawMinClear(); break;

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
EWRAM_CODE void AnimeExecBlend(void)
{
	Anime.var[0] = LexGetNum();
	Anime.var[1] = LexGetNum();
	Anime.var[2] = LexGetNum();
	Anime.var[3] = LexGetNum();

	Anime.waitBlend = 31;
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
EWRAM_CODE void AnimeExecWaitBgm(void)
{
	Anime.waitBgm = LexGetNum();

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
EWRAM_CODE void AnimeExecFontCol(void)
{
	s32 n = LexGetNum();

	if(n == 1) SprSetWhite();
	if(n == 2) SprSetGray();

	if(n == 3)
	{
		SprSetSelect();
		SprSetSelectCol(RGB5(0,0,0));
	}

	if(n == 4)
	{
		SprSetSelect();
		SprSetSelectCol(RGB5(31,31,31));
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecFontIn(void)
{
	Anime.waitFontIn = 31;
	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecFontOut(void)
{
	Anime.waitFontOut = 31;
	Anime.isLoop = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEnvSave(void)
{
	Anime.envFadeWait = ImgGetFadeWait();
	Anime.envSelCol = ImgGetSelCol();

	ImgSetFadeWait(1);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEnvLoad(void)
{
	ImgSetFadeWait(Anime.envFadeWait);
	ImgSetSelCol(Anime.envSelCol);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnimeExecEnvFade(void)
{
	s32 n = LexGetNum();

	ImgSetFadeWait(n);
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

	case ANIME_DAT_NEXT_ROM:
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
