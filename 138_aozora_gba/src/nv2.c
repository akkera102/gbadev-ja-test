#include "nv.h"
#include "nv2.h"
#include "libbios/swi.h"
#include "cur.h"
#include "info.h"
#include "img.h"
#include "seen.h"
#include "manage.h"
#include "mus.h"
#include "siori.h"
#include "snd.h"
#include "txt.h"

//---------------------------------------------------------------------------
ST_NV_PARSE_TBL NvParseTbl[NV_MAX_PARSE_CNT] = {
	{ "MES", NvExecParseMes },	// 人物と既読フラグ
	{ "MLF", NvExecParseMlf },	// 改ページ
	{ "GFX", NvExecParseGfx },	// 画面効果
	{ "GLB", NvExecParseGlb },	// 背景表示
	{ "GLG", NvExecParseGlg },	// 立ち絵表示
	{ "CLG", NvExecParseClg },	// 立ち絵非表示
	{ "CFR", NvExecParseCfr },	// 画面全体消去
	{ "MUS", NvExecParseMus },	// 音楽
	{ "SND", NvExecParseSnd },	// 効果音
	{ "VFL", NvExecParseVfl },	// フラグ変数
	{ "VFW", NvExecParseVfw },	// ワード変数
	{ "IF0", NvExecParseIf0 },	// IF開始ブロック
	{ "IFE", NvExecParseIfe },	// IF終了ブロック
	{ "GO0", NvExecParseGo0 },	// スクリプト移動
	{ "SET", NvExecParseSet },	// 選択肢マーキング
	{ "SEL", NvExecParseSel },	// 選択肢の開始
	{ "CAS", NvExecParseCas },	// 選択肢１つ開始ブロック
	{ "BRK", NvExecParseBrk },	// 選択肢１つ終了ブロック
	{ "SEE", NvExecParseSee },	// 選択肢の終了
	{ "WAS", NvExecParseWas },	// ウェイトフレーム
	{ "WAM", NvExecParseWam },	// ウェイトミリ秒？
	{ "END", NvExecParseEnd },	// 特殊コマンド
};


//---------------------------------------------------------------------------
extern ST_NV Nv;


//---------------------------------------------------------------------------
void NvExecParse(void)
{
	Nv.isLoop = true;

	do
	{
		if(Nv.cur >= Nv.size)
		{
			NvSetTxt2(Nv.no + 1);
		}

		NvExecParseSub();

	} while(Nv.isLoop == true);
}
//---------------------------------------------------------------------------
void NvExecParseSub(void)
{
	char* p = NvCurStr();

	TRACE("\n[%03d][%04X] %s\n", Nv.no, Nv.cur - 4, p);

	s32 i;

	for(i=0; i<NV_MAX_PARSE_CNT; i++)
	{
		if(_Strncmp(p, NvParseTbl[i].cmd, 3) == 0)
		{
			break;
		}
	}
	_ASSERT(i < NV_MAX_PARSE_CNT);


	NvParseTbl[i].pExec();
}
//---------------------------------------------------------------------------
// 人物と既読フラグ
void NvExecParseMes(void)
{
	s32 m = NvCurNum();
	s32 i = NvCurNum();
	s32 b = NvCurNum();

	// TRACE("%d %d %d\n", m, i, b);

	if(Nv.isDbg == false)
	{
		// 1つ前の既読フラグを有効にします
		SeenSetRead(Nv.idx, Nv.bit);
	}

	Nv.mes = m;
	Nv.idx = i;
	Nv.bit = b;

	if(SeenIsRead(i, b) == false && Nv.isPass == false)
	{
		Nv.isSkip = false;
	}

	NvExecParseSjis();

	ImgSetExecCond(IMG_EFFECT_SET_MSG);
	NvSetAct(NV_ACT_KEY);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 改ページ
void NvExecParseMlf(void)
{
	NvExecParseSjis();

	ImgSetExecCond(IMG_EFFECT_SET_MSG);
	NvSetAct(NV_ACT_KEY);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 画面効果
void NvExecParseGfx(void)
{
	s32 e = NvCurNum();

	ImgSetExec(e);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 背景表示
void NvExecParseGlb(void)
{
	s32 b = NvCurChrNum3('B');
	s32 e = NvCurNum();

	// TRACE("%d %d\n", b, e);

	// パッチ
	if(e == IMG_EFFECT_ALPHA)
	{
		s32 now = ImgGetBg();

		if(now == 0)
		{
			e = IMG_EFFECT_BLACK_OUT;
		}
		else if(now == 900)
		{
			e = IMG_EFFECT_WHITE_OUT;
		}
	}

	ImgSetBg(b);
	ImgSetChr(0);
	ImgSetExec(e);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 立ち絵表示
void NvExecParseGlg(void)
{
	s32 a = NvCurChrNum3('A');
	s32 e = NvCurNum();

	if(Nv.isSkip == true)
	{
		e = IMG_EFFECT_NORMAL;
	}

	ImgSetChr(a);
	ImgSetExecCond(e);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 立ち絵非表示
void NvExecParseClg(void)
{
	s32 e = NvCurNum();

	if(Nv.isSkip == true)
	{
		e = IMG_EFFECT_NORMAL;
	}

	ImgSetChr(0);
	ImgSetExecCond(e);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 画面全体消去
void NvExecParseCfr(void)
{
	s32 e = NvCurNum();

	ImgSetBg(0);
	ImgSetChr(0);
	ImgSetExec(e);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 音楽
void NvExecParseMus(void)
{
	s32 n = NvCurNum();

	if(n == 0)
	{
		MusStop();

		return;
	}

	MusPlay(NvCurChrNum3('M'), (n == 2) ? true : false);
}
//---------------------------------------------------------------------------
// 効果音
void NvExecParseSnd(void)
{
	s32 n = NvCurNum();

	if(n == 0)
	{
		SndStop();

		return;
	}

	SndPlay(NvCurChrNum3('S'), (n == 2) ? true : false);
}
//---------------------------------------------------------------------------
// フラグ変数
void NvExecParseVfl(void)
{
	s32  n = NvCurNum3();
	char c = NvCurChr();

	SeenSetFl(n, (c == '+') ? 1 : 0);
}
//---------------------------------------------------------------------------
// ワード変数
void NvExecParseVfw(void)
{
	s32  n = NvCurNum3();
	char c = NvCurChr();
	s32  v = NvCurNum1();
	s32  t = SeenGetFw(n);

	switch(c)
	{
	case '=':
		t = v;
		break;

	case '+':
		t += v;
		break;

	case '-':
		t -= v;
		break;

	default:
		SystemError("[Err] NvExecParseVfw %c\n", c);
		break;
	}

	SeenSetFw(n, t);
}
//---------------------------------------------------------------------------
// IF開始ブロック
void NvExecParseIf0(void)
{
	s32 st[30];
	s32 sp = 0;
	s32 i, r, l;

	s32 cnt = NvCurNum();

	for(i=0; i<cnt; i++)
	{
		_ASSERT(sp < 30);

		char* s = NvGetCur();
//		TRACE("%d %s\n", i, s);

		switch(s[0])
		{
		case '=':
			r = st[--sp];
			l = st[--sp];
			st[sp++] = (l == r);

			NvCurSkip();
			break;

		case '@':
			r = st[--sp];
			l = st[--sp];
			st[sp++] = (l != r);

			NvCurSkip();
			break;

		case '&':
			r = st[--sp];
			l = st[--sp];
			st[sp++] = (l && r);

			NvCurSkip();
			break;

		case '|':
			r = st[--sp];
			l = st[--sp];
			st[sp++] = (l || r);

			NvCurSkip();
			break;

		case '>':
			r = st[--sp];
			l = st[--sp];
			st[sp++] = (l > r);

			NvCurSkip();
			break;

		case '<':
			r = st[--sp];
			l = st[--sp];
			st[sp++] = (l < r);

			NvCurSkip();
			break;

		case '!':
			r = st[--sp];
			st[sp++] = (!r);

			NvCurSkip();
			break;

		case 'F':
			NvCurChr();

			char c = NvCurChr();
			s32  n = NvCurNum3();

			if(c == 'W')
			{
				st[sp++] = SeenGetFw(n);
//				TRACE("%d\n", st[sp-1]);
			}
			else
			{
				st[sp++] = SeenGetFl(n);
//				TRACE("%d\n", st[sp-1]);
			}
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			st[sp++] = NvCurNum();
			break;

		default:
			SystemError("[Err] NvExecParseIf0 %s\n", s);
			break;
		}
	}

	_ASSERT(sp == 1);

	if(st[0] == 0)
	{
		NvCurSkipIf();
	}
}
//---------------------------------------------------------------------------
// IF終了ブロック
void NvExecParseIfe(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
// スクリプト移動
void NvExecParseGo0(void)
{
	s32 n = NvCurChrNum3('T');

	// TRACE("%d\n", n);

	NvSetTxt2(n);
}
//---------------------------------------------------------------------------
// 選択肢マーキング
void NvExecParseSet(void)
{
	Nv.set = Nv.cur - 4;

	// TRACE("%d\n", Nv.set);
}
//---------------------------------------------------------------------------
// 選択肢の開始
void NvExecParseSel(void)
{
	s32 reg = NvCurNum();
	s32 cnt = 0;
	s32 i;

	for(i=0; i<reg; i++)
	{
		s32 adr = NvCurHex4();
		// TRACE("%d %d\n", i, adr);

		// SEEコマンドは選択肢チェックを飛ばします
		if(i != reg-1)
		{
			if(NvIsSelItem(adr) == false)
			{
				continue;
			}
		}

		Nv.sel.pos[cnt] = adr;
		cnt++;
	}

	Nv.sel.reg = cnt - 1;
	Nv.sel.cnt = -1;

	// TRACE("Nv.sel.reg %d\n", Nv.sel.reg);

	if(Nv.isDbg == false)
	{
		SeenSetRead(Nv.idx, Nv.bit);
	}

	NvSetAct(NV_ACT_SEL);
	ManageSetAct(MANAGE_ACT_SEL);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 選択肢１つ開始ブロック
void NvExecParseCas(void)
{
	// skip "選択肢,（条件式）"
	NvCurStr();
}
//---------------------------------------------------------------------------
// 選択肢１つ終了ブロック
void NvExecParseBrk(void)
{
	Nv.cur = Nv.sel.pos[Nv.sel.reg];
}
//---------------------------------------------------------------------------
// 選択肢の終了
void NvExecParseSee(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
// ウェイトフレーム
void NvExecParseWas(void)
{
	s32 w = NvCurNum();

	// TRACE("%d\n", w);

	if(Nv.isSkip == true)
	{
		return;
	}

	Nv.wait = w * 60;
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// ウェイトミリ秒？
void NvExecParseWam(void)
{
	s32 m = NvCurNum();

	// TRACE("%d\n", m);

	if(Nv.isSkip == true)
	{
		return;
	}

	Nv.wait = SwiDiv(m , 10);		// 決め打ち
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// 特殊コマンド
void NvExecParseEnd(void)
{
	s32 n = NvCurNum();

	// TRACE("%d\n", n);

	switch(n)
	{
	// 季節の終了
	case 1:
		switch(Nv.no)
		{
		// 春へ
		case 101:
			NvSetTxt2(2);
			break;

		// 夏へ
		case 171:
		case 172:
		case 173:
		case 174:
		case 175:
			NvSetTxt2(3);
			break;

		// 秋へ
		case 267:
		case 273:
		case 280:
		case 283:
		case 291:
			NvSetTxt2(4);
			break;

		// 冬へ
		case 356:
		case 389:
		case 405:
		case 426:
		case 480:
		case 513:
			NvSetTxt2(5);
			break;

		default:
			SystemError("[Err] NvExecParseEnd case1 %d\n", Nv.no);
			break;
		}
		break;

	// エキスパートの終了
	// エンディングの終了
	case 2:
	case 3:
		if(Nv.isDbg == false)
		{
			SeenSetRead(Nv.idx, Nv.bit);

			SioriSaveLast();
			SioriSaveRead();
		}

		MusStop();
		SndStop();

		NvSetOmake(false);
		NvSetDbg(false);
		NvSetNavi(0);

		ImgSetBg(5);
		ImgSetChr(800);
		ImgSetExec(IMG_EFFECT_BLACK_OUT);

		ManageSetAct(MANAGE_ACT_EXIT);
		Nv.isSkip = false;
		Nv.isLoop = false;
		break;

	// エンディング曲の再生
	case 994:
		MusPlay(34, false);
		break;

	// エンディング曲の停止
	case 995:
		MusStop();
		break;

	// 台詞の自動改項処理を開始
	// 台詞の自動改項処理をやめる
	// ステータス表示を禁止
	// ステータス表示を再開
	case 996:
	case 997:
	case 998:
	case 999:
		// EMPTY
		break;

	default:
		SystemError("[Err] NvExecParseEnd %x\n", n);
		break;
	}
}
//---------------------------------------------------------------------------
void NvExecParseSjis(void)
{
	Nv.str = Nv.cur;

	CurSetPage();
	CurSetExec();

	TxtClrBuf();
	TxtSetExec();

	if(Nv.mes != 0)
	{
		// 名前
		TxtAddBuf(InfoGetStrMes(Nv.mes));
	}

	bool is = true;

	do {

		char* p = NvCurStr();

		if(is == true)
		{
			// しおりタイトル
			TxtSetSiori(p);
			is = false;
		}

		// スクリプトメッセージ
		TxtAddBuf(p);

	} while(NvIsCurSjis() == true);
}
