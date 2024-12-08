#include "nv.h"
#include "nv2.h"
#include "img.h"
#include "bgm.h"
#include "pcm.h"
#include "txt.h"
#include "menu.h"
#include "anm.h"
#include "ags.arm.h"

//---------------------------------------------------------------------------
ST_NV_PARSE_TABLE NvParseTable[NV_MAX_PARSE_CNT] = {
	{ "BUF", (void*)NvExecParseBuf },		// SET_BUFFER_PROPERTIES
	{ "BUI", (void*)NvExecParseBui },		// SET_IMAGE_PROPERTIES
	{ "BUR", (void*)NvExecParseBur },		// RESET_BUFFER_FLAGS
	{ "BUA", (void*)NvExecParseBua },		// RESET_ALL_BUFFER_FLAGS
	{ "SCR", (void*)NvExecParseScr },		// SCROLL_VIEWPORT
	{ "SCM", (void*)NvExecParseScm },		// MODIFY_SCROLL_PROPERTIES
	{ "SLP", (void*)NvExecParseSlp },		// SLEEP
	{ "EFF", (void*)NvExecParseEff },		// EFFECT（GBA追加）
	{ "ANM", (void*)NvExecParseAnm },		// LOAD_ANM
	{ "ANI", (void*)NvExecParseAni },		// DISABLE_ANIM_PAUSE
	{ "ANE", (void*)NvExecParseAne },		// ENABLE_ANIM_PAUSE
	{ "WAB", (void*)NvExecParseWab },		// WAIT_FOR_BUFFER
	{ "WAY", (void*)NvExecParseWay },		// WAIT_FOR_BUFFER_WITH_SYNC
	{ "WAI", (void*)NvExecParseWai },		// WAIT_FOR_INPUT
	{ "WAP", (void*)NvExecParseWap },		// WAIT_FOR_INPUT_OR_PCM
	{ "WAS", (void*)NvExecParseWas },		// WAIT_FOR_SCROLL
	{ "PAL", (void*)NvExecParsePal },		// SET_PALETTE_FROM_ANM
	{ "PAE", (void*)NvExecParsePae },		// MODIFY_PALETTE
	{ "PAF", (void*)NvExecParsePaf },		// MODIFY_PALETTE_WITH_EFFECT
	{ "BGM", (void*)NvExecParseBgm },		// PLAY_MIDI
	{ "BGS", (void*)NvExecParseBgs },		// STOP_MIDI
	{ "PCM", (void*)NvExecParsePcm },		// PLAY_PCM
	{ "PCS", (void*)NvExecParsePcs },		// STOP_PCM
	{ "PCN", (void*)NvExecParsePcn },		// STOP_PCM_ON_NEXT_REFRESH
	{ "TXT", (void*)NvExecParseTxt },		// DISPLAY_TEXT
	{ "TXC", (void*)NvExecParseTxc },		// DISPLAY_TEXT_CLEAR（GBA追加）
	{ "LBL", (void*)NvExecParseLbl },		// LABEL（GBA追加）
	{ "JMP", (void*)NvExecParseJmp },		// JUMP（GBA追加）
	{ "IFR", (void*)NvExecParseIfr },		// JUMP_IF_REGISTER_EQUAL
	{ "IFL", (void*)NvExecParseIfl },		// JUMP_IF_LAST_READ_NOT_EQUAL
	{ "CAL", (void*)NvExecParseCal },		// CALL
	{ "RET", (void*)NvExecParseRet },		// RET
	{ "SEL", (void*)NvExecParseSel },		// DISPLAY_HOT_ZONE_TEXT
	{ "WIN", (void*)NvExecParseWin },		// LOAD_WIN
	{ "VRR", (void*)NvExecParseVrr },		// READ
	{ "VRW", (void*)NvExecParseVrw },		// WRITE
	{ "CPY", (void*)NvExecParseCpy },		// COPY
	{ "INC", (void*)NvExecParseInc },		// INC
	{ "OR0", (void*)NvExecParseOr0 },		// OR
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

	TRACE("\n[%04X][%s]\n", Nv.pCur - (char*)Nv.pScn - 4, cmd);

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
// SET_BUFFER_PROPERTIES
EWRAM_CODE void NvExecParseBuf(void)
{
	s32 no   = NvNextCurNum();
	s32 flag = NvNextCurNum();
	s32 max  = NvNextCurNum();

//	bool isLeng = (flag & 0x10) ? true : false;		// スクロール画像有無？
//	bool isDrew = (flag & 0x08) ? true : false;		// フレーム描画完了後、バッファ0（スクロール画像）で上書き有無？
//	bool isKeep = (flag & 0x02) ? true : false;		// スクロール処理終了後、フレーム描画の続行有無？
	bool isLoop = (flag & 0x01) ? true : false;		// ループ有無

	AnmSetBuf1(no, isLoop, max);


	s32 i, f, w;

	for(i=0; i<max; i++)
	{
		f = NvNextCurNum();
		w = NvNextCurNum();

		AnmSetBuf2(no, i, f, w);
	}

//	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// SET_IMAGE_PROPERTIES
EWRAM_CODE void NvExecParseBui(void)
{
	s32 no = NvNextCurNum();
	s32 f  = NvNextCurNum();

	AnmSetScr1(no, f);
}
//---------------------------------------------------------------------------
// RESET_BUFFER_FLAGS
EWRAM_CODE void NvExecParseBur(void)
{
	s32 no = NvNextCurNum();

	AnmSetBufWork(no, false);
}
//---------------------------------------------------------------------------
// RESET_ALL_BUFFER_FLAGS
EWRAM_CODE void NvExecParseBua(void)
{
	s32 i;

	for(i=0; i<ANM_BUF_MAX_CNT; i++)
	{
		AnmSetBufWork(i, false);
		AnmSetScrWork(i, false);
	}

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// SCROLL_VIEWPORT
EWRAM_CODE void NvExecParseScr(void)
{
	s32 no   = NvNextCurNum();
	s32 type = NvNextCurNum();
	s32 sy   = NvNextCurNum();
	s32 ey   = NvNextCurNum();
	s32 my   = NvNextCurNum();

	AnmSetScr2(no, type, sy, ey, my);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// MODIFY_SCROLL_PROPERTIES
EWRAM_CODE void NvExecParseScm(void)
{
	s32 sy = NvNextCurNum();
	s32 ey = NvNextCurNum();

	if(ey == 0)
	{
		Nv.isKeyScr = false;
	}
	else
	{
		Nv.isKeyScr = true;
	}

	if(sy != 0)
	{
		AnmSetScr4(sy);
	}
}
//---------------------------------------------------------------------------
// SLEEP
EWRAM_CODE void NvExecParseSlp(void)
{
	s32 slp = NvNextCurNum();

//	TRACE("%d\n", slp);

	Nv.sleep = slp;
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// EFFECT（GBA追加）
EWRAM_CODE void NvExecParseEff(void)
{
	s32 eff = NvNextCurNum();
	s32 var = NvNextCurNum();

	ImgSetEff(eff, var);
	TxtClrCur();

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// LOAD_ANM
EWRAM_CODE void NvExecParseAnm(void)
{
	char* s = NvNextCurStr();

	AnmInit();
	AnmSetDat(s);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// DISABLE_ANIM_PAUSE
EWRAM_CODE void NvExecParseAni(void)
{
	AnmSetPause(false);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// ENABLE_ANIM_PAUSE
EWRAM_CODE void NvExecParseAne(void)
{
	AnmSetPause(true);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// WAIT_FOR_BUFFER
EWRAM_CODE void NvExecParseWab(void)
{
	s32 no = NvNextCurNum();

	TRACE("%d\n", no);

	Nv.bNo = no;
	Nv.isBuf = true;
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// WAIT_FOR_BUFFER_WITH_SYNC
EWRAM_CODE void NvExecParseWay(void)
{
	NvExecParseWab();
}
//---------------------------------------------------------------------------
// WAIT_FOR_INPUT
EWRAM_CODE void NvExecParseWai(void)
{
	if(Nv.isKeyScr == true)
	{
		TxtSetCurScr();
	}
	else
	{
		TxtSetCurKey();
	}

	NvSetAct(NV_ACT_KEY);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// WAIT_FOR_INPUT_OR_PCM
EWRAM_CODE void NvExecParseWap(void)
{
	Nv.isPcm = true;

	if(PcmIsPlay() == false)
	{
		Nv.pcmWait = 200;
	}

	NvExecParseWai();
}
//---------------------------------------------------------------------------
// WAIT_FOR_SCROLL
EWRAM_CODE void NvExecParseWas(void)
{
	s32 no  = NvNextCurNum();

	TRACE("%d\n", no);

	Nv.sNo = no;
	Nv.isScr = true;
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// SET_PALETTE_FROM_ANM
EWRAM_CODE void NvExecParsePal(void)
{
	AnmSetPal();
}
//---------------------------------------------------------------------------
// MODIFY_PALETTE
EWRAM_CODE void NvExecParsePae(void)
{
	s32 max = NvNextCurNum();
	s32 i, j, r, g, b;

	for(i=0; i<max; i++)
	{
		j = NvNextCurNum();
		r = NvNextCurNum();
		g = NvNextCurNum();
		b = NvNextCurNum();

		AnmSetCol3(j, r, g, b);
	}

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// MODIFY_PALETTE_WITH_EFFECT
EWRAM_CODE void NvExecParsePaf(void)
{
	s32 wait = NvNextCurNum();
	s32 max  = NvNextCurNum();
	s32 i, j, r, g, b;

	AnmSetCol1(wait, max);

	for(i=0; i<max; i++)
	{
		j = NvNextCurNum();
		r = NvNextCurNum();
		g = NvNextCurNum();
		b = NvNextCurNum();

		AnmSetCol2(i, j, r, g, b);
	}

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// PLAY_MIDI
EWRAM_CODE void NvExecParseBgm(void)
{
	s32 no = NvNextCurNum();
	s32 loop = NvNextCurNum();

	BgmPlay2(no, (loop == 1) ? true : false);
}
//---------------------------------------------------------------------------
// STOP_MIDI
EWRAM_CODE void NvExecParseBgs(void)
{
	BgmStop();
}
//---------------------------------------------------------------------------
// PLAY_PCM
EWRAM_CODE void NvExecParsePcm(void)
{
	char* p = NvNextCurStr();
	s32 adj = NvNextCurNum();
	s32 loop = NvNextCurNum();

	PcmPlay(p, adj, (loop == 1) ? true : false);
}
//---------------------------------------------------------------------------
// STOP_PCM
EWRAM_CODE void NvExecParsePcs(void)
{
	PcmStop();
}
//---------------------------------------------------------------------------
// STOP_PCM_ON_NEXT_REFRESH
EWRAM_CODE void NvExecParsePcn(void)
{
	if(PcmIsPlay() == false)
	{
		return;
	}

	// ロゴ場面はアイコン表示しない
	if(NvGetVar(17) == 0)
	{
		return;
	}

	TxtSetCurPcm();
	NvSetAct(NV_ACT_KEY);

	Nv.isPcm = true;
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// DISPLAY_TEXT
EWRAM_CODE void NvExecParseTxt(void)
{
	char* s = NvNextCurStr();

	TRACE("%s\n", s);

	TxtSetStr(s);
	ImgSetEff(IMG_EFFECT_TXT_OUT, 0);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// DISPLAY_TEXT_CLEAR（GBA追加）
EWRAM_CODE void NvExecParseTxc(void)
{
	TxtClr();

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// LABEL（GBA追加）
EWRAM_CODE void NvExecParseLbl(void)
{
	s32 no = NvNextCurNum();

	TRACE("%d\n", no);

	// EMPTY
}
//---------------------------------------------------------------------------
// JUMP（GBA追加）
EWRAM_CODE void NvExecParseJmp(void)
{
	s32 no = NvNextCurNum();

	NvSetLbl(no);
}
//---------------------------------------------------------------------------
// JUMP_IF_REGISTER_EQUAL
EWRAM_CODE void NvExecParseIfr(void)
{
	s32 reg = NvNextCurNum();
	s32 var = NvNextCurNum();
	s32 lbl = NvNextCurNum();

	if(NvGetVar(reg) == var)
	{
		NvSetLbl(lbl);
	}
}
//---------------------------------------------------------------------------
// JUMP_IF_LAST_READ_NOT_EQUAL
EWRAM_CODE void NvExecParseIfl(void)
{
	s32 var = NvNextCurNum();
	s32 lbl = NvNextCurNum();

	if(Nv.lastVar != var)
	{
		NvSetLbl(lbl);
	}
}
//---------------------------------------------------------------------------
// CALL
EWRAM_CODE void NvExecParseCal(void)
{
	s32 no = NvNextCurNum();

	NvPushCall(no);
}
//---------------------------------------------------------------------------
// RET
EWRAM_CODE void NvExecParseRet(void)
{
	NvPopCall();
}
//---------------------------------------------------------------------------
// DISPLAY_HOT_ZONE_TEXT
EWRAM_CODE void NvExecParseSel(void)
{
	s32 ret = NvNextCurNum();
	s32 reg = NvNextCurNum();

//	TRACE("%d %d\n", ret, reg);

	Nv.sel.reg = reg;
	Nv.sel.ret = ret;
	Nv.sel.cnt = -1;

	s32 i;

	for(i=0; i<reg; i++)
	{
		Nv.sel.p[i] = NvNextCurStr();

//		TRACE("%d: %s\n", i, Nv.sel.p[i]);
	}

	ImgSetEff(IMG_EFFECT_TXT_OUT, 0);

	NvSetAct(NV_ACT_SEL);
	AgsSetSelect();

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// LOAD_WIN
EWRAM_CODE void NvExecParseWin(void)
{
	char* s = NvNextCurStr();

	NvSetScn(s);
}
//---------------------------------------------------------------------------
// READ
EWRAM_CODE void NvExecParseVrr(void)
{
	s32 a = NvNextCurNum();

	TRACE("%d\n", a);

	Nv.lastVar = NvGetVar(a);
}
//---------------------------------------------------------------------------
// WRITE
EWRAM_CODE void NvExecParseVrw(void)
{
	s32 a = NvNextCurNum();
	s32 b = NvNextCurNum();

	TRACE("%d %d\n", a, b);

	NvSetVar(a, b);

	// メニューの場面ジャンプ値も変更
	if(a == 17)
	{
		MenuSetJmp(b);
	}
}
//---------------------------------------------------------------------------
// COPY
EWRAM_CODE void NvExecParseCpy(void)
{
	s32 a = NvNextCurNum();
	s32 b = NvNextCurNum();
	s32 c = NvGetVar(b);

	NvSetVar(a, c);
}
//---------------------------------------------------------------------------
// INC
EWRAM_CODE void NvExecParseInc(void)
{
	s32 a = NvNextCurNum();
	s32 b = NvGetVar(a);

	NvSetVar(a, b + 1);
}
//---------------------------------------------------------------------------
// OR
EWRAM_CODE void NvExecParseOr0(void)
{
	s32 a = NvNextCurNum();
	s32 b = NvNextCurNum();
	s32 c = NvGetVar(a);

	NvSetVar(a, c | b);
}
