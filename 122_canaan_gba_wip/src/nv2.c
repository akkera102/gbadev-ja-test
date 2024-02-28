#include "nv.h"
#include "nv2.h"
#include "img.h"
#include "bgm.h"
#include "siori.h"
#include "txt.h"
#include "anime.h"
#include "manage.h"
#include "se.h"
#include "file.h"
#include "menu.h"

//---------------------------------------------------------------------------
ST_NV_PARSE_TABLE NvParseTable[NV_MAX_PARSE_CNT] = {
	{ "MSG", (void*)NvExecParseMsg },
	{ "SEL", (void*)NvExecParseSel },
	{ "KEY", (void*)NvExecParseKey },
	{ "CHR", (void*)NvExecParseChr },
	{ "BGL", (void*)NvExecParseBgl },
	{ "HSC", (void*)NvExecParseHsc },
	{ "BPL", (void*)NvExecParseBpl },
	{ "BST", (void*)NvExecParseBst },
	{ "EFF", (void*)NvExecParseEff },
	{ "PTY", (void*)NvExecParsePty },
	{ "ICO", (void*)NvExecParseIco },
	{ "MIN", (void*)NvExecParseMin },
	{ "SET", (void*)NvExecParseSet },
	{ "CLR", (void*)NvExecParseClr },
	{ "SSG", (void*)NvExecParseSsg },
	{ "FMX", (void*)NvExecParseFmx },
	{ "PAT", (void*)NvExecParsePat },
	{ "LDS", (void*)NvExecParseLds },
	{ "SCR", (void*)NvExecParseScr },
	{ "WAT", (void*)NvExecParseWat },
	{ "END", (void*)NvExecParseEnd },
};


//---------------------------------------------------------------------------
extern ST_NV Nv;


//---------------------------------------------------------------------------
EWRAM_CODE void NvExecParse(void)
{
	Nv.isLoop = true;

	do
	{
		NvExecParseSub();

	} while(Nv.isLoop == true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecParseSub(void)
{
	char cmd[4];

	cmd[0] = *Nv.pCur++;
	cmd[1] = *Nv.pCur++;
	cmd[2] = *Nv.pCur++;
	cmd[3] = *Nv.pCur++;		// '\0'

	TRACE("\n[cs%02d_%02d.txt %04x][%s]\n", Nv.chap, Nv.part, Nv.pCur - Nv.pTxt - 4, cmd);

	s32 i;

	for(i=0; i<NV_MAX_PARSE_CNT; i++)
	{
		if(_Strncmp(cmd, NvParseTable[i].pStr, 3) == 0)
		{
			break;
		}
	}
	_ASSERT(i < NV_MAX_PARSE_CNT);


	NvParseTable[i].pFunc();
}
//---------------------------------------------------------------------------
// メッセージ表示
EWRAM_CODE void NvExecParseMsg(void)
{
	char* p = NvNextCurStr();
	TRACE("%s\n", p);

	TxtSetMsg(p);
	TxtSetSiori(p);
	ImgSetEff(IMG_EFFECT_TXT_IN);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// セレクト表示
EWRAM_CODE void NvExecParseSel(void)
{
	char* p = NvNextCurStr();
	TRACE("%s\n", p);

	TxtSetSel(p);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 入力待ち
EWRAM_CODE void NvExecParseKey(void)
{
	TxtSetCur(true);

	Nv.isIco = false;
	Nv.isLoop = false;
	Nv.act = NV_ACT_KEY;
}
//---------------------------------------------------------------------------
// キャラクタ立ち絵など表示
EWRAM_CODE void NvExecParseChr(void)
{
	char* p = NvNextCurStr();
//	TRACE("%s\n", p);

	ImgDrawVramClear();

	ImgClrIco();
	ImgClrMin();
	ImgSetChr1(p);
	ImgClrChr2();
	ImgSetEff(IMG_EFFECT_WIPE_UD);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 背景表示
EWRAM_CODE void NvExecParseBgl(void)
{
	char* p = NvNextCurStr();
//	TRACE("%s\n", p);

	ImgDrawVramClear();

	ImgClrAll();
	ImgSetBgl(p);
	ImgSetEff(IMG_EFFECT_WIPE_LR);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// Hシーン
EWRAM_CODE void NvExecParseHsc(void)
{
	char* p = NvNextCurStr();
//	TRACE("%s\n", p);

	ImgDrawVramClear();

	ImgClrAll();
	ImgSetBgc(p);
	ImgSetEff(IMG_EFFECT_WIPE_UD);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// BGMスタート
EWRAM_CODE void NvExecParseBpl(void)
{
	s32 no = NvNextCurNum();
//	TRACE("%d\n", no);

	BgmPlay2(no, true);
}
//---------------------------------------------------------------------------
// BGMストップ
EWRAM_CODE void NvExecParseBst(void)
{
	BgmStop();
}
//---------------------------------------------------------------------------
// エフェクト表示
EWRAM_CODE void NvExecParseEff(void)
{
	s32 no = NvNextCurNum();
//	TRACE("%d\n", no);

	ImgDrawVramClear();

	ImgClrIco();
	ImgClrMin();
	ImgSetEffTxt(no);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// パーティ表示
EWRAM_CODE void NvExecParsePty(void)
{
	char* p = NvNextCurStr();
//	TRACE("%s\n", p);

	ImgDrawVramClear();

	ImgClrIco();
	ImgClrMin();
	ImgSetPty(p);
	ImgSetEff(IMG_EFFECT_NORMAL);

	Nv.isPty = true;
	Nv.isLoop = false;
	Nv.act = NV_ACT_KEY;
}
//---------------------------------------------------------------------------
// アイコン表示
EWRAM_CODE void NvExecParseIco(void)
{
	char* p = NvNextCurStr();
//	TRACE("%s\n", p);

	ImgSetIco(p);

	if(Nv.isIco == true && Nv.isSkip == false)
	{
		ImgSetEff(IMG_EFFECT_IGNORE_WAIT_ICO);

		Nv.isIco = false;
		Nv.isLoop = false;
	}
	else
	{
		ImgDrawIco();

		Nv.isIco = true;
	}
}
//---------------------------------------------------------------------------
// ミニ表示
EWRAM_CODE void NvExecParseMin(void)
{
	char* p = NvNextCurStr();
//	TRACE("%s\n", p);

	ImgSetMin(p);
	ImgDrawMin();
}
//---------------------------------------------------------------------------
// 個別指定
EWRAM_CODE void NvExecParseSet(void)
{
	char* p = NvNextCurStr();
	s32  no = NvNextCurNum();
//	TRACE("%s %d\n", p, no);

	switch(no)
	{
	case 1: ImgSetBgl(p);  break;
	case 2: ImgSetBgc(p);  break;
	case 3: ImgSetBgb(p);  break;
	case 4: ImgSetChr1(p); break;
	case 5: ImgSetChr2(p); break;
	case 6: ImgSetPty(p);  break;
	case 7: ImgSetIco(p);  break;
	case 8: ImgSetMin(p);  break;

	default:
		SystemError("[Err] NvExecParseSet no=%x\n", no);
		break;
	}
}
//---------------------------------------------------------------------------
// 消去
EWRAM_CODE void NvExecParseClr(void)
{
	s32 no = NvNextCurNum();
//	TRACE("%d\n", no);

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
		SystemError("[Err] NvExecParseClr no=%x\n", no);
		break;
	}
}
//---------------------------------------------------------------------------
// 効果音SSG
EWRAM_CODE void NvExecParseSsg(void)
{
	s32 no = NvNextCurNum();
//	TRACE("%d\n", no);

//	SePlaySsg(no, true);
}
//---------------------------------------------------------------------------
// 効果音FMX
EWRAM_CODE void NvExecParseFmx(void)
{
	s32 no = NvNextCurNum();
//	TRACE("%d\n", no);

//	SePlayFmx(no, true);
}
//---------------------------------------------------------------------------
// パタパタアニメーション
EWRAM_CODE void NvExecParsePat(void)
{
	s32 arg = NvNextCurNum();
	s32 pat = NvNextCurNum();
//	TRACE("%d %d\n", pat, arg);

	AnimeSetDat(ANIME_DAT_PATA1 + pat - 1);
	AnimeSetArg(arg);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// スクリプトジャンプ
EWRAM_CODE void NvExecParseLds(void)
{
	s32 chap = NvNextCurNum();
	s32 no   = NvNextCurNum();

	NvSetTxt(chap, no);
}
//---------------------------------------------------------------------------
// スクロールエフェクト
EWRAM_CODE void NvExecParseScr(void)
{
	char* s = NvNextCurStr();
	s32 n = NvNextCurNum();
//	TRACE("%s %d\n", s, n);

	ImgDrawVramClear();
	ImgClrAll();

	if(n == 1)
	{
		ImgSetScrDu(s);
		ImgSetEff(IMG_EFFECT_SCROLL_DU);
	}
	else
	{
		ImgSetScrUd(s);
		ImgSetEff(IMG_EFFECT_SCROLL_UD);
	}

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// ウェイト
EWRAM_CODE void NvExecParseWat(void)
{
	s32 wait = NvNextCurNum();
//	TRACE("%d\n", wait);

	if(Nv.isSkip == true)
	{
		return;
	}

	Nv.wait = wait;
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 後編へメッセージ or エンディング
EWRAM_CODE void NvExecParseEnd(void)
{
	if(FileIsFirstPart() == true)
	{
		AnimeSetDat(ANIME_DAT_NEXT_ROM);
	}
	else
	{
		AnimeSetDat(ANIME_DAT_ENDING);
	}

	Nv.isSkip = false;
	Nv.isLoop = false;
}
