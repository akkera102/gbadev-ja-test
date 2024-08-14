#include "nv.h"
#include "nv2.h"
#include "img.h"
#include "bgm.h"
#include "txt.h"
#include "manage.h"
#include "se.h"
#include "menu.h"

//---------------------------------------------------------------------------
ST_NV_PARSE_TABLE NvParseTable[NV_MAX_PARSE_CNT] = {
	{ "MSG", (void*)NvExecParseMsg },
	{ "KEY", (void*)NvExecParseKey },
	{ "BGL", (void*)NvExecParseBgl },
	{ "CHR", (void*)NvExecParseChr },
	{ "EFF", (void*)NvExecParseEff },
	{ "BGM", (void*)NvExecParseBgm },
	{ "BGS", (void*)NvExecParseBgs },
	{ "FMX", (void*)NvExecParseFmx },
	{ "FMS", (void*)NvExecParseFms },
	{ "WAT", (void*)NvExecParseWat },
	{ "SEL", (void*)NvExecParseSel },
	{ "JMP", (void*)NvExecParseJmp },
	{ "LBL", (void*)NvExecParseLbl },
	{ "VAR", (void*)NvExecParseVar },
	{ "LDS", (void*)NvExecParseLds },
	{ "GOT", (void*)NvExecParseGot },
	{ "SCR", (void*)NvExecParseScr },
	{ "STA", (void*)NvExecParseSta },
	{ "TAI", (void*)NvExecParseTai },
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

	TRACE("\n[%s %04X][%s]\n", Nv.pStr, Nv.pCur - Nv.pScn - 4, cmd);

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
// ゲームテキストを表示
EWRAM_CODE void NvExecParseMsg(void)
{
	char* p = NvNextCurStr();

	TRACE("%s\n", p);

	TxtSetMsg(p);
	TxtSetSiori(p);
	ImgSetEff(IMG_EFFECT_TXT_IN, 0);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 入力待ち
EWRAM_CODE void NvExecParseKey(void)
{
	TxtSetCur(true);

	Nv.isLoop = false;
	NvSetAct(NV_ACT_KEY);
}
//---------------------------------------------------------------------------
// 背景セット
EWRAM_CODE void NvExecParseBgl(void)
{
	char* p = NvNextCurStr();

//	TRACE("%s\n", p);

	ImgClrBg();
	ImgClrChr();
	ImgSetBg(p);
}
//---------------------------------------------------------------------------
// キャラクタセット
EWRAM_CODE void NvExecParseChr(void)
{
	s32  no = NvNextCurNum();
	char* p = NvNextCurStr();

//	TRACE("%d %s\n",no, p);

	if(no == 1)
	{
		ImgSetChr1(p);
	}
	else
	{
		ImgSetChr2(p);
	}
}
//---------------------------------------------------------------------------
// エフェクト
EWRAM_CODE void NvExecParseEff(void)
{
	s32 no = NvNextCurNum();

//	TRACE("%d\n", no);

	ImgSetEff(no, 0);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// BGMスタート
EWRAM_CODE void NvExecParseBgm(void)
{
	s32 b = NvNextCurNum();
	char* p = NvNextCurStr();

//	TRACE("%s %d\n", p, b);

	BgmPlay2(p, (b == 1) ? true : false);
}
//---------------------------------------------------------------------------
// BGMストップ
EWRAM_CODE void NvExecParseBgs(void)
{
	BgmStop();
}
//---------------------------------------------------------------------------
// 効果音スタート
EWRAM_CODE void NvExecParseFmx(void)
{
	s32 no = NvNextCurNum();

//	TRACE("%d\n", no);

	if(Nv.isSkip == true)
	{
		return;
	}

	SePlay2(no);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 効果音ストップ
EWRAM_CODE void NvExecParseFms(void)
{
	SeStop();
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
// 選択肢
EWRAM_CODE void NvExecParseSel(void)
{
	s32 ans = NvNextCurNum();
	s32 reg = NvNextCurNum();
	s32 ret = NvNextCurNum();

//	TRACE("ans:%d reg:%d ret:%d\n", ans, reg, ret);

	Nv.sel.ans = ans;
	Nv.sel.reg = reg;
	Nv.sel.ret = ret;
	Nv.sel.cnt = -1;

	s32 i;

	for(i=0; i<reg; i++)
	{
		Nv.sel.p[i] = NvNextCurStr();
	}

	Nv.isLoop = false;
	NvSetAct(NV_ACT_SEL);
}
//---------------------------------------------------------------------------
// 条件付きジャンプ
EWRAM_CODE void NvExecParseJmp(void)
{
	s32 x  = NvNextCurNum();
	s32 op = NvNextCurNum();
	s32 y  = NvNextCurNum();
	s32 z  = NvNextCurNum();
	s32 v  = NvGetVar(x);

	// != と == のみ使用
	switch(op)
	{
	case 1:
		TRACE("var[%d] %d != %d goto %d\n", x, v, y, z);

		if(v != y)
		{
			TRACE("jump!\n");
			NvSetLbl(z);
		}
		break;

	case 2:
		TRACE("var[%d] %d == %d goto %d\n", x, v, y, z);

		if(v == y)
		{
			TRACE("jump!\n");
			NvSetLbl(z);
		}
		break;

	default:
		SystemError("[Err] NvExecParseJmp %d\n", op);
		break;
	}
}
//---------------------------------------------------------------------------
// ラベル
EWRAM_CODE void NvExecParseLbl(void)
{
	// skip
	NvNextCurNum();
}
//---------------------------------------------------------------------------
// 変数計算
EWRAM_CODE void NvExecParseVar(void)
{
	s32 x  = NvNextCurNum();
	s32 op = NvNextCurNum();
	s32 y  = NvNextCurNum();
	s32 v  = NvGetVar(x);

	// = のみ使用
	switch(op)
	{
	case 1:
		TRACE("var[%d](%d) = %d\n", x, v, y);
		NvSetVar(x, y);
		break;

	default:
		SystemError("[Err] NvExecParseVar %d\n", op);
		break;
	}
}
//---------------------------------------------------------------------------
// スクリプトジャンプ
EWRAM_CODE void NvExecParseLds(void)
{
	char* p = NvNextCurStr();

	// TRACE("%s\n", p);

	NvSetScn(p);
}
//---------------------------------------------------------------------------
// ラベルジャンプ
EWRAM_CODE void NvExecParseGot(void)
{
	s32 no = NvNextCurNum();

	// TRACE("%d\n", no);

	NvSetLbl(no);
}
//---------------------------------------------------------------------------
// スクロール画像の設定
EWRAM_CODE void NvExecParseScr(void)
{
	s32 t = NvNextCurNum();
	char* p = NvNextCurStr();

//	TRACE("%s %d\n", p, t);

	ImgClrBg();
	ImgClrChr();
	ImgSetScr(p, t);
}
//---------------------------------------------------------------------------
// スタートメニュー（PIL2のみで使用）
EWRAM_CODE void NvExecParseSta(void)
{
	ImgSetEff(IMG_EFFECT_TXT_IN, 0);

	MenuSetTitle(MENU_TITLE_SEL_LOAD);
	ManageSetMenu();

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// オープニングメッセージ（TAIのみで使用）
EWRAM_CODE void NvExecParseTai(void)
{
	s32 x   = NvNextCurNum();
	s32 y   = NvNextCurNum();
	char* p = NvNextCurStr();

	if(y == 0)
	{
		TxtHideMsg();	// テキスト全体消去
		TxtShowMsg();
	}

	TxtDrawStrXy(x, y, p);
}
//---------------------------------------------------------------------------
// スクリプトエンド
EWRAM_CODE void NvExecParseEnd(void)
{
	SystemError("[Err] NvExecParseEnd\n");
}
