#include "nv.h"
#include "nv2.h"
#include "nv3.h"
#include "img.h"
#include "bgm.h"
#include "txt.h"
#include "manage.h"
#include "se.h"
#include "menu.h"
#include "cur.h"

//---------------------------------------------------------------------------
ST_NV_PARSE_TBL NvParseTbl[NV_MAX_PARSE_CNT] = {
	{ "!g", 1, (void*)NvExecParse1G  },	// 背景
	{ "!b", 1, (void*)NvExecParse1B  },	// 音楽
	{ "!e", 1, (void*)NvExecParse1E  },	// 効果音
	{ "!x", 2, (void*)NvExecParse1X  },	// 立ち絵
	{ "!j", 1, (void*)NvExecParse1J  },	// スクリプトジャンプ
	{ "!t", 1, (void*)NvExecParse1T  },	// タイトル
	{ "!s", 2, (void*)NvExecParse1S  },	// 既読
	{ "#g", 1, (void*)NvExecParse2G  },	// CALL
	{ "#r", 0, (void*)NvExecParse2R  },	// RET
	{ "#l", 0, (void*)NvExecParse2L  },	// ELSE
	{ "#n", 0, (void*)NvExecParse2N  },	// ENDIF
	{ "#i", 3, (void*)NvExecParse2I  },	// IF
	{ "#W", 1, (void*)NvExecParse2W  },	// エフェクト
	{ "#t", 1, (void*)NvExecParse2T  },	// ウェイト
	{ "_r", 1, (void*)NvExecParse3R  },	// キー入力＋改ページ（紙アイコン）
	{ "_t", 1, (void*)NvExecParse3T  },	// キー入力＋改行（指アイコン）
	{ "_m", 1, (void*)NvExecParse3M  },	// テキスト表示
	{ "_n", 1, (void*)NvExecParse3N  },	// 改行
	{ ";;", 0, (void*)NvExecParseSel },	// 選択肢
	{ "[]", 3, (void*)NvExecParseCal },	// 計算式
};


//---------------------------------------------------------------------------
extern ST_NV Nv;


//---------------------------------------------------------------------------
void NvExecParse(void)
{
	Nv.isLoop = true;

	do
	{
		NvExecParseSub();

	} while(Nv.isLoop == true);


	if(Nv.isEffect == true)
	{
		ImgSetExec();

		if(Nv.isPage == true)
		{
			TxtHide();
			CurHide();
		}

		Nv.isEffect = false;
	}
}
//---------------------------------------------------------------------------
void NvExecParseSub(void)
{
	char* pA = NvCurStr();
	char* pC = NvCurStr();

	TRACE("\n[%03d][%s] %s\n", Nv.no, pA, pC);

	s32 i;

	for(i=0; i<NV_MAX_PARSE_CNT; i++)
	{
		if(_Strncmp(pC, NvParseTbl[i].cmd, 2) == 0)
		{
			break;
		}
	}
	_ASSERT(i < NV_MAX_PARSE_CNT);


	if(NvIsExecParseCmd(pC) == false)
	{
		NvCurSkip(NvParseTbl[i].argv);
	}
	else
	{
		NvParseTbl[i].pFunc();
	}
}
//---------------------------------------------------------------------------
// 背景
void NvExecParse1G(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	ImgClrChrAll();
	ImgSetBg(no);

	Nv.isEffect = true;
}
//---------------------------------------------------------------------------
// 音楽
void NvExecParse1B(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	BgmPlay(no);
}
//---------------------------------------------------------------------------
// 効果音
void NvExecParse1E(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	// ベルの無効化
	if(Nv.isSkip == true && no == 0)
	{
		return;
	}

	SePlay(no);
}
//---------------------------------------------------------------------------
// 立ち絵
void NvExecParse1X(void)
{
	s32 no = NvCurNum();
	s32 is = NvCurNum();

//	TRACE("%d %d\n", no, is);

	if(is == 1)
	{
		ImgSetChr(no);
	}
	else
	{
		ImgClrChr(no);
	}

	Nv.isEffect = true;
}
//---------------------------------------------------------------------------
// スクリプトジャンプ
void NvExecParse1J(void)
{
	s32 no = NvCurNum();

	TRACE("%d\n", no);

	Nv.isLoop = false;

	if(no != 1)
	{
		NvSetScn(no);

		return;
	}

	// オープニング処理
	ImgSetEff(IMG_EFFECT_TITL);
	Nv.isEffect = true;
	Nv.isSkip = false;

	MenuSetTitle(MENU_TITLE_SEL_LOAD);
	ManageSetAct(MANAGE_ACT_MENU);
}
//---------------------------------------------------------------------------
// タイトル
void NvExecParse1T(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetTitle(s);
}
//---------------------------------------------------------------------------
// 既読
void NvExecParse1S(void)
{
	s32 i = NvCurNum();
	s32 b = NvCurNum();

	TRACE("%d %d\n", i, b);

	// 1つ前の既読フラグを有効にします
	NvSetRead(Nv.idx, Nv.bit);

	Nv.idx = i;
	Nv.bit = b;


	if(NvIsRead(i, b) == false && Nv.isOmit == false)
	{
		Nv.isSkip = false;
	}

	if(Nv.isEffect == true)
	{
		Nv.isLoop = false;
	}
}
//---------------------------------------------------------------------------
// CALL
void NvExecParse2G(void)
{
	s32 no = NvCurNum();

	TRACE("%d\n", no);

	_ASSERT(Nv.call.isUse == false);


	s32   tmp  = Nv.no;
	char* pTmp = Nv.pCur;

	NvSetScn(no);

	Nv.call.no    = tmp;
	Nv.call.pCur  = pTmp;
	Nv.call.isUse = true;
}
//---------------------------------------------------------------------------
// RET
void NvExecParse2R(void)
{
	_ASSERT(Nv.call.isUse == true);


	NvSetScn(Nv.call.no);

	Nv.pCur = Nv.call.pCur;
}
//---------------------------------------------------------------------------
// ELSE
void NvExecParse2L(void)
{
	NvExprFlip();
}
//---------------------------------------------------------------------------
// ENDIF
void NvExecParse2N(void)
{
	NvExprPop();
}
//---------------------------------------------------------------------------
// IF
void NvExecParse2I(void)
{
	s32 v  = NvCurNum();
	s32 op = NvCurChr();
	s32 r  = NvCurNum();
	s32 l  = NvGetVar(v);

	switch(op)
	{
	case '>':
		TRACE("var[%d] %d > %d\n", v, l, r);

		NvExprPush((l > r) ? true : false);
		break;

	case '=':
		TRACE("var[%d] %d == %d\n", v, l, r);

		NvExprPush((l == r) ? true : false);
		break;

	default:
		SystemError("[Err] NvExecParse2I %c\n", op);
		break;
	}
}
//---------------------------------------------------------------------------
// エフェクト
void NvExecParse2W(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	if(Nv.isSkip == true)
	{
		ImgSetEff(IMG_EFFECT_COPY);
	}
	else
	{
		ImgSetEff(no);
	}
}
//---------------------------------------------------------------------------
// ウェイト
void NvExecParse2T(void)
{
	s32 w = NvCurNum();

	TRACE("%d\n", w);

	// ゲーム終了の「良い終末を」のタイミング
	if(w == 50 && Nv.no == 84)
	{
		Nv.isSkip = false;
	}

	if(Nv.isSkip == true)
	{
		return;
	}

	Nv.wait = w * 2;
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// キー入力＋改ページ（紙アイコン）
void NvExecParse3R(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetMsg(s);
	TxtSetExec();
	CurSetPage();
	CurSetExec();

	Nv.isPage = true;
	Nv.isLoop = false;
	NvSetAct(NV_ACT_KEY);
}
//---------------------------------------------------------------------------
// キー入力＋改行（指アイコン）
void NvExecParse3T(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetMsg(s);
	TxtSetExec();
	CurSetLf();
	CurSetExec();

	Nv.isPage = false;
	Nv.isLoop = false;
	NvSetAct(NV_ACT_KEY);
}
//---------------------------------------------------------------------------
// テキスト表示
void NvExecParse3M(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetMsg(s);
	TxtSetExec();
}
//---------------------------------------------------------------------------
// 改行
void NvExecParse3N(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetMsg(s);
	TxtSetLf();
}
//---------------------------------------------------------------------------
// 選択肢
void NvExecParseSel(void)
{
	Nv.sel.cnt = -1;

	NvSetAct(NV_ACT_SEL);
	ManageSetAct(MANAGE_ACT_SEL);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 計算式
void NvExecParseCal(void)
{
	s32 v  = NvCurNum();
	s32 op = NvCurChr();
	s32 r  = NvCurNum();

	switch(op)
	{
	case '=':
		TRACE("v%d = %d\n", v, r);
		NvSetVar(v, r);
		break;

	case '+':
		TRACE("v%d += %d\n", v, r);
		NvSetVar(v, r + NvGetVar(v));
		break;

	default:
		SystemError("[Err] NvExecParseCal %d %c %d\n", v, op, r);
		break;
	}
}
//---------------------------------------------------------------------------
// スクリプトコマンドの実行有無
bool NvIsExecParseCmd(char* p)
{
	// IF命令のネスト真偽（expr）を確認
	if(NvIsExpr() == true)
	{
		return true;
	}

	// # 以外は実行
	if(p[0] != '#')
	{
		return false;
	}

	// IF, ELSE, ENDIF命令は実行
	if(p[1] == 'i' || p[1] == 'l' || p[1] == 'n')
	{
		return true;
	}

	return false;
}
