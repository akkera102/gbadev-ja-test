#include "nv.h"
#include "nv2.h"
#include "nv3.h"
#include "libbios/swi.h"
#include "cur.h"
#include "img.h"
#include "info.h"
#include "seen.h"
#include "txt.h"
#include "manage.h"
#include "mus.h"
#include "siori.h"
#include "snd.h"
#include "menu.h"

// nv3.c
// 既読画面ジャンプ用の関数群

//---------------------------------------------------------------------------
ST_NV_JUMP_TBL NvJumpTbl[NV_MAX_PARSE_CNT] = {
	{ "MES", (void*)NvExecJumpMes },	// 人物と既読フラグ
	{ "MLF", (void*)NvExecJumpMlf },	// 改ページ
	{ "GFX", (void*)NvExecJumpGfx },	// 画面効果
	{ "GLB", (void*)NvExecJumpGlb },	// 背景表示
	{ "GLG", (void*)NvExecJumpGlg },	// 立ち絵表示
	{ "CLG", (void*)NvExecJumpClg },	// 立ち絵非表示
	{ "CFR", (void*)NvExecJumpCfr },	// 画面全体消去
	{ "MUS", (void*)NvExecJumpMus },	// 音楽
	{ "SND", (void*)NvExecJumpSnd },	// 効果音
	{ "VFL", (void*)NvExecJumpVfl },	// フラグ変数
	{ "VFW", (void*)NvExecJumpVfw },	// ワード変数
	{ "IF0", (void*)NvExecJumpIf0 },	// IF開始ブロック
	{ "IFE", (void*)NvExecJumpIfe },	// IF終了ブロック
	{ "GO0", (void*)NvExecJumpGo0 },	// スクリプト移動
	{ "SET", (void*)NvExecJumpSet },	// 選択肢マーキング
	{ "SEL", (void*)NvExecJumpSel },	// 選択肢の開始
	{ "CAS", (void*)NvExecJumpCas },	// 選択肢１つ開始ブロック
	{ "BRK", (void*)NvExecJumpBrk },	// 選択肢１つ終了ブロック
	{ "SEE", (void*)NvExecJumpSee },	// 選択肢の終了
	{ "WAS", (void*)NvExecJumpWas },	// ウェイトフレーム
	{ "WAM", (void*)NvExecJumpWam },	// ウェイトミリ秒？
	{ "END", (void*)NvExecJumpEnd },	// 特殊コマンド
};


//---------------------------------------------------------------------------
extern ST_NV Nv;


//---------------------------------------------------------------------------
void NvExecJump(void)
{
	MusLock();
	SndLock();

	Nv.isLoop = true;

	do
	{
		if(Nv.cur >= Nv.size)
		{
			NvSetTxt2(Nv.no + 1);
		}

		NvExecJumpSub();

	} while(Nv.isLoop == true);

	MusLoad();
	SndLoad();
}
//---------------------------------------------------------------------------
void NvExecJumpSub(void)
{
	char* p = NvCurStr();

	TRACE("\n[%03d][%04X][J] %s\n", Nv.no, Nv.cur - 4, p);

	s32 i;

	for(i=0; i<NV_MAX_PARSE_CNT; i++)
	{
		if(_Strncmp(p, NvJumpTbl[i].cmd, 3) == 0)
		{
			break;
		}
	}
	_ASSERT(i < NV_MAX_PARSE_CNT);


	NvJumpTbl[i].pExec();
}
//---------------------------------------------------------------------------
// 人物と既読フラグ
void NvExecJumpMes(void)
{
	s32 m = NvCurNum();
	s32 i = NvCurNum();
	s32 b = NvCurNum();

	if(Nv.isDbg == false)
	{
		SeenSetRead(Nv.idx, Nv.bit);
	}

	Nv.mes = m;
	Nv.idx = i;
	Nv.bit = b;

	if(SeenIsRead(i, b) == false && Nv.isPass == false)
	{
		// 復旧処理
		CurSetPage();
		CurSetExec();
		TxtSetExec();

		NvSetAct(NV_ACT_KEY);
		ImgSetExec(IMG_EFFECT_LOAD);

		Nv.isSkip = false;
		Nv.isLoop = false;
	}

	NvExecJumpSjis();
}
//---------------------------------------------------------------------------
// 改ページ
void NvExecJumpMlf(void)
{
	NvExecJumpSjis();
}
//---------------------------------------------------------------------------
// 画面効果
void NvExecJumpGfx(void)
{
	NvCurNum();
}
//---------------------------------------------------------------------------
// 背景表示
void NvExecJumpGlb(void)
{
	s32 b = NvCurChrNum3('B');
	NvCurNum();

	ImgSetBg(b);
	ImgSetChr(0);
}
//---------------------------------------------------------------------------
// 立ち絵表示
void NvExecJumpGlg(void)
{
	s32 a = NvCurChrNum3('A');
	NvCurNum();

	ImgSetChr(a);
}
//---------------------------------------------------------------------------
// 立ち絵非表示
void NvExecJumpClg(void)
{
	NvCurNum();

	ImgSetChr(0);
}
//---------------------------------------------------------------------------
// 画面全体消去
void NvExecJumpCfr(void)
{
	NvCurNum();

	ImgSetBg(0);
	ImgSetChr(0);
}
//---------------------------------------------------------------------------
// 音楽
void NvExecJumpMus(void)
{
	NvExecParseMus();
}
//---------------------------------------------------------------------------
// 効果音
void NvExecJumpSnd(void)
{
	NvExecParseSnd();
}
//---------------------------------------------------------------------------
// フラグ変数
void NvExecJumpVfl(void)
{
	NvExecParseVfl();
}
//---------------------------------------------------------------------------
// ワード変数
void NvExecJumpVfw(void)
{
	NvExecParseVfw();
}
//---------------------------------------------------------------------------
// IF開始ブロック
void NvExecJumpIf0(void)
{
	NvExecParseIf0();
}
//---------------------------------------------------------------------------
// IF終了ブロック
void NvExecJumpIfe(void)
{
	NvExecParseIfe();
}
//---------------------------------------------------------------------------
// スクリプト移動
void NvExecJumpGo0(void)
{
	NvExecParseGo0();
}
//---------------------------------------------------------------------------
// 選択肢マーキング
void NvExecJumpSet(void)
{
	NvExecParseSet();
}
//---------------------------------------------------------------------------
// 選択肢の開始
void NvExecJumpSel(void)
{
	// 内部で復旧処理
	NvExecParseSel();

	// 復旧処理
	Nv.isSkip = false;
	ImgSetExec(IMG_EFFECT_LOAD);
}
//---------------------------------------------------------------------------
// 選択肢１つ開始ブロック
void NvExecJumpCas(void)
{
	NvExecParseCas();
}
//---------------------------------------------------------------------------
// 選択肢１つ終了ブロック
void NvExecJumpBrk(void)
{
	NvExecParseBrk();
}
//---------------------------------------------------------------------------
// 選択肢の終了
void NvExecJumpSee(void)
{
	NvExecParseSee();
}
//---------------------------------------------------------------------------
// ウェイトフレーム
void NvExecJumpWas(void)
{
	NvCurNum();
}
//---------------------------------------------------------------------------
// ウェイトミリ秒？
void NvExecJumpWam(void)
{
	NvCurNum();
}
//---------------------------------------------------------------------------
// 特殊コマンド
void NvExecJumpEnd(void)
{
	// 内部で復旧処理
	NvExecParseEnd();
}
//---------------------------------------------------------------------------
void NvExecJumpSjis(void)
{
	Nv.str = Nv.cur;

	TxtClrBuf();

	if(Nv.mes != 0)
	{
		TxtAddBuf(InfoGetStrMes(Nv.mes));
	}

	bool is = false;

	do {

		char* p = NvCurStr();

		if(is == false)
		{
			TxtSetSiori(p);
			is = true;
		}

		TxtAddBuf(p);

	} while(NvIsCurSjis() == true);
}
