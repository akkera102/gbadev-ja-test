#include "nv2.h"
#include "libmy/lex.h"
#include "nv.h"
#include "img.h"
#include "bgm.h"
#include "siori.h"
#include "text.h"
#include "se.h"
#include "bgm.h"


//---------------------------------------------------------------------------
const ST_NV_PARSE_TABLE NvParseTable[NV_MAX_PARSE_CNT] = {
	{ "endScn",      (void*)NvExecParseEndScn      },
	{ "title",       (void*)NvExecParseTitle       },
	{ "sel",         (void*)NvExecParseSel         },
	{ "jmpScn",      (void*)NvExecParseJmpScn      },
	{ "jmpBlk",      (void*)NvExecParseJmpBlk      },
	{ "selOpt",      (void*)NvExecParseSelOpt      },
	{ "pushA",       (void*)NvExecParsePushA       },
	{ "retA",        (void*)NvExecParseRetA        },
	{ "pushB",       (void*)NvExecParsePushB       },
	{ "retB",        (void*)NvExecParseRetB        },
	{ "day",         (void*)NvExecParseDay         },
	{ "time",        (void*)NvExecParseTime        },
	{ "flagAdd",     (void*)NvExecParseFlagAdd     },
	{ "flagSub",     (void*)NvExecParseFlagSub     },
	{ "bg",          (void*)NvExecParseBg          },
	{ "chrClr",      (void*)NvExecParseChrClr      },
	{ "visLoad",     (void*)NvExecParseVisLoad     },
	{ "chrLoad",     (void*)NvExecParseChrLoad     },
	{ "disp",        (void*)NvExecParseDisp        },
	{ "sepia",       (void*)NvExecParseSepia       },
	{ "jmpAdr",      (void*)NvExecParseJmpAdr      },
	{ "if==",        (void*)NvExecParseIf1         },
	{ "if!=",        (void*)NvExecParseIf2         },
	{ "if>",         (void*)NvExecParseIf3         },
	{ "if<",         (void*)NvExecParseIf4         },
	{ "if>=",        (void*)NvExecParseIf5         },
	{ "if<=",        (void*)NvExecParseIf6         },
	{ "ifBitSet",    (void*)NvExecParseIfBitSet    },
	{ "ifBitRes",    (void*)NvExecParseIfBitRes    },
	{ "flagSet",     (void*)NvExecParseFlagSet     },
	{ "flagBit",     (void*)NvExecParseFlagBit     },
	{ "msgClr",      (void*)NvExecParseMsgClr      },
	{ "msg",         (void*)NvExecParseMsg         },
	{ "light",       (void*)NvExecParseLight       },
	{ "whiteOut",    (void*)NvExecParseWhiteOut    },
	{ "whiteIn",     (void*)NvExecParseWhiteIn     },
	{ "bgm",         (void*)NvExecParseBgm         },
	{ "bgmFade",     (void*)NvExecParseBgmFade     },
	{ "bgmStop",     (void*)NvExecParseBgmStop     },
	{ "bgmWaitFade", (void*)NvExecParseBgmWaitFade },
	{ "bgm2",        (void*)NvExecParseBgm2        },
	{ "bgmNext",     (void*)NvExecParseBgmNext     },
	{ "gameEnd",     (void*)NvExecParseGameEnd     },
	{ "ending",      (void*)NvExecParseEnding      },
	{ "pcmLoad",     (void*)NvExecParsePcmLoad     },
	{ "pcmStop",     (void*)NvExecParsePcmStop     },
	{ "pcmPlay",     (void*)NvExecParsePcmPlay     },
	{ "pcmWait",     (void*)NvExecParsePcmWait     },
	{ "endMsg",      (void*)NvExecParseEndMsg      },
	{ "cr",          (void*)NvExecParseCr          },
	{ "key",         (void*)NvExecParseKey         },
	{ "page",        (void*)NvExecParsePage        },
	{ "timeTxt",     (void*)NvExecParseTimeTxt     },
	{ "timeWait",    (void*)NvExecParseTimeWait    },
	{ "txtXY",       (void*)NvExecParseTxtXy       },
	{ "flash",       (void*)NvExecParseFlash       },
	{ "vibrate",     (void*)NvExecParseShake       },
	{ "bg2",         (void*)NvExecParseBg2         },
	{ "visLoad2",    (void*)NvExecParseVisLoad2    },
	{ "loadH",       (void*)NvExecParseLoadH       },
	{ "chrChg",      (void*)NvExecParseChrChg      },
	{ "chrDisp",     (void*)NvExecParseChrDisp     },
	{ "chrClrAll",   (void*)NvExecParseChrClrAll   },
	{ "bgChr",       (void*)NvExecParseBgChr       },
	{ "chr3",        (void*)NvExecParseChr3        },
	{ "day2",        (void*)NvExecParseDay2        },
	{ "rein",        (void*)NvExecParseRain        },
	{ "sakura",      (void*)NvExecParseSakura      },
	{ "endEvent",    (void*)NvExecParseEndEvent    },
	{ "skip",        (void*)NvExecParseSkip        },
};


//---------------------------------------------------------------------------
extern ST_NV Nv;


//---------------------------------------------------------------------------
EWRAM_CODE void NvExecParse(void)
{
	Nv.isLoop = TRUE;

	do
	{
		NvExecParseSub();

	} while(Nv.isLoop == TRUE);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecParseSub(void)
{
	LexSetCur(Nv.pCur);
	NvNextLine();

	u16   n = LexGetHex();
	char* p = LexGetStr();


	// アドレス
	TRACEOUT("[%04x]", n);
	Nv.curAdr = n;

	// テキスト
	if(_IsSJIS(*p) == TRUE)
	{
		NvExecParseText(p);
		return;
	}

	// 命令セット
	u32 i;

	for(i=0; i<NV_MAX_PARSE_CNT; i++)
	{
		if(_Strncmp(p, NvParseTable[i].pStr, 20) == 0)
		{
			break;
		}
	}
	_ASSERT(i < NV_MAX_PARSE_CNT);


	NvParseTable[i].pFunc();
}
//---------------------------------------------------------------------------
// シナリオ終了 0x20
EWRAM_CODE void NvExecParseEndScn(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// タイトル処理 0x21+0x03
EWRAM_CODE void NvExecParseTitle(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 選択肢 0x24
EWRAM_CODE void NvExecParseSel(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// ジャンプファイル 0x28
EWRAM_CODE void NvExecParseJmpScn(void)
{
	u16 n1 = LexGetHex();
	u8  n2 = LexGetHex();

	TRACEOUT("[jmpScn %x %x]\n", n1, n2);

	NvSetScn(n1);
	NvSetEvt(n2);
}
//---------------------------------------------------------------------------
// ジャンプブロック 0x29
EWRAM_CODE void NvExecParseJmpBlk(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 可変選択肢 0x2b
EWRAM_CODE void NvExecParseSelOpt(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// PUSH A 0x2b
EWRAM_CODE void NvExecParsePushA(void)
{
	u8 n1 = LexGetHex();
	u8 n2 = LexGetHex();
	u8 n3 = LexGetHex();

	TRACEOUT("[pushA %x %x]\n", n1, n2);

	NvAddFlag(NV_FLAG_A_SCN1, n1);
	NvAddFlag(NV_FLAG_A_SCN2, n2);
	NvAddFlag(NV_FLAG_A_BLK,  n3);
}
//---------------------------------------------------------------------------
// RET A 0x2e
EWRAM_CODE void NvExecParseRetA(void)
{
	TRACEOUT("[retA]\n");

	u16 scn = NvGetFlag(NV_FLAG_A_SCN2) + (NvGetFlag(NV_FLAG_A_SCN1) << 8);
	u8  evt = NvGetFlag(NV_FLAG_A_BLK);

	NvSetScn(scn);
	NvSetEvt(evt);
}
//---------------------------------------------------------------------------
// PUSH B 0x2f
EWRAM_CODE void NvExecParsePushB(void)
{
	u8 n1 = LexGetHex();
	u8 n2 = LexGetHex();
	u8 n3 = LexGetHex();

	TRACEOUT("[pushB %x %x]\n", n1, n2);

	NvAddFlag(NV_FLAG_B_SCN1, n1);
	NvAddFlag(NV_FLAG_B_SCN2, n2);
	NvAddFlag(NV_FLAG_B_BLK,  n3);
}
//---------------------------------------------------------------------------
// RET B 0x30
EWRAM_CODE void NvExecParseRetB(void)
{
	TRACEOUT("[retB]\n");

	u16 scn = NvGetFlag(NV_FLAG_B_SCN2) + (NvGetFlag(NV_FLAG_B_SCN1) << 8);
	u8  evt = NvGetFlag(NV_FLAG_B_BLK);

	NvSetScn(scn);
	NvSetEvt(evt);
}
//---------------------------------------------------------------------------
// 日付更新（カレンダー無） 0x32
EWRAM_CODE void NvExecParseDay(void)
{
	u8 n = LexGetHex();

	TRACEOUT("[day %x]\n", n);


	if(n == 0xf0)
	{
		NvSetFlag(NV_FLAG_DAY, 3);
	}
	else
	{
		NvAddFlag(NV_FLAG_DAY, 1);
	}

	NvSetFlag(NV_FLAG_WEEK, Mod(NvGetFlag(NV_FLAG_DAY) + 5, 7));
}
//---------------------------------------------------------------------------
// 時間設定 0x33
EWRAM_CODE void NvExecParseTime(void)
{
	u8 n = LexGetHex();

	TRACEOUT("[time %x]\n", n);

	// 行動フラグ初期化。ここで良いのかどうかは不明
	Nv.flag[NV_FLAG_EVENT_DONE] = 0;
	Nv.flag[NV_FLAG_IDOU] = 0;

	if(n >= 0xf0)
	{
		// 表示無し更新
		Nv.flag[NV_FLAG_TIME] = n - 0xf0;
	}
	else
	{
		// 表示有り更新
/*
		int i;
		int start;

		if (state->fast_clock) {
		    start = c[1];
		} else {
		    start = state->flag[TOHEART_FLAG_TIME];
		}

		state->flag[TOHEART_FLAG_TIME] = c[1];
		for (i=start; i<c[1]+1;i++) {
		    clock_anim[i].type = LVNS_ANIM_IMAGE_ADD;
		}
		clock_anim[i].type = LVNS_ANIM_NONE;
		LvnsAnimation(lvns, clock_anim + start);
*/
	}
}
//---------------------------------------------------------------------------
// フラグ加算 0x34,0x62
EWRAM_CODE void NvExecParseFlagAdd(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// フラグ減算 0x35
EWRAM_CODE void NvExecParseFlagSub(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 背景ロード 0x3c
EWRAM_CODE void NvExecParseBg(void)
{
	u8 n = LexGetHex();

	TRACEOUT("[bg %x]\n", n);

	ImgSetBg(n);
}
//---------------------------------------------------------------------------
// キャラクタ消去 0x3d
EWRAM_CODE void NvExecParseChrClr(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// VISUALロード 0x42
EWRAM_CODE void NvExecParseVisLoad(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// キャラクタ表示 0x43
EWRAM_CODE void NvExecParseChrLoad(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 表示処理 0x45
EWRAM_CODE void NvExecParseDisp(void)
{
	u8 n = LexGetHex();

	TRACEOUT("[disp %x]\n", n);

	_ASSERT(0);
}
//---------------------------------------------------------------------------
// セピア 0x47 0x01
EWRAM_CODE void NvExecParseSepia(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 同一内ジャンプ 0x55
EWRAM_CODE void NvExecParseJmpAdr(void)
{
	u8 n = LexGetHex();

	TRACEOUT("[jmpAdr %x]\n", n);

	NvAddCur(n);
}
//---------------------------------------------------------------------------
// if== 0x56
EWRAM_CODE void NvExecParseIf1(void)
{
	u8 n1 = LexGetHex();
	s8 n2 = LexGetHex();
	u8 n3 = LexGetHex();
	u8 f  = NvGetFlag(n1);

	TRACEOUT("[if [%x](%x) == %x goto %x]\n", n1, f, n2, n3);

	if(f == n2)
	{
		NvAddCur(n3);
	}
}
//---------------------------------------------------------------------------
// if!= 0x57
EWRAM_CODE void NvExecParseIf2(void)
{
	u8 n1 = LexGetHex();
	s8 n2 = LexGetHex();
	u8 n3 = LexGetHex();
	u8 f  = NvGetFlag(n1);

	TRACEOUT("[if [%x](%x) != %x goto %x]\n", n1, f, n2, n3);

	if(f != n2)
	{
		NvAddCur(n3);
	}
}
//---------------------------------------------------------------------------
// if> 0x58
EWRAM_CODE void NvExecParseIf3(void)
{
	u8 n1 = LexGetHex();
	s8 n2 = LexGetHex();
	u8 n3 = LexGetHex();
	u8 f  = NvGetFlag(n1);

	TRACEOUT("[if [%x](%x) > %x goto %x]\n", n1, f, n2, n3);

	if(f > n2)
	{
		NvAddCur(n3);
	}
}
//---------------------------------------------------------------------------
// if< 0x59
EWRAM_CODE void NvExecParseIf4(void)
{
	u8 n1 = LexGetHex();
	s8 n2 = LexGetHex();
	u8 n3 = LexGetHex();
	u8 f  = NvGetFlag(n1);

	TRACEOUT("[if [%x](%x) < %x goto %x]\n", n1, f, n2, n3);

	if(f < n2)
	{
		NvAddCur(n3);
	}
}
//---------------------------------------------------------------------------
// if>= 0x5a
EWRAM_CODE void NvExecParseIf5(void)
{
	u8 n1 = LexGetHex();
	s8 n2 = LexGetHex();
	u8 n3 = LexGetHex();
	u8 f  = NvGetFlag(n1);

	TRACEOUT("[if [%x](%x) >= %x goto %x]\n", n1, f, n2, n3);

	if(f >= n2)
	{
		NvAddCur(n3);
	}
}
//---------------------------------------------------------------------------
// if<= 0x5b
EWRAM_CODE void NvExecParseIf6(void)
{
	u8 n1 = LexGetHex();
	s8 n2 = LexGetHex();
	u8 n3 = LexGetHex();
	u8 f  = NvGetFlag(n1);

	TRACEOUT("[if [%x](%x) <= %x goto %x]\n", n1, f, n2, n3);

	if(f <= n2)
	{
		NvAddCur(n3);
	}
}
//---------------------------------------------------------------------------
// ifBitSet 0x5e
EWRAM_CODE void NvExecParseIfBitSet(void)
{
	u8 n1 = LexGetHex();
	s8 n2 = LexGetHex();
	u8 n3 = LexGetHex();
	u8 f  = NvGetFlag(n1);

	TRACEOUT("[ifBitSet [%x](%x) & %x goto %x]\n", n1, f, 1 << n2, n3);

	if(f & (1 << n2))
	{
		NvAddCur(n3);
	}
}
//---------------------------------------------------------------------------
// ifBitRes 0x5f
EWRAM_CODE void NvExecParseIfBitRes(void)
{
	u8 n1 = LexGetHex();
	s8 n2 = LexGetHex();
	u8 n3 = LexGetHex();
	u8 f  = NvGetFlag(n1);

	TRACEOUT("[ifBitRes [%x](%x) & %x goto %x]\n", n1, f, 1 << n2, n3);

	if(!(f & (1 << n2)))
	{
		NvAddCur(n3);
	}
}
//---------------------------------------------------------------------------
// flagSet 0x61
EWRAM_CODE void NvExecParseFlagSet(void)
{
	u8 n1 = LexGetHex();
	u8 n2 = LexGetHex();

	TRACEOUT("[flagSet [%x] = %x]\n", n1, n2);

	NvSetFlag(n1, n2);
}
//---------------------------------------------------------------------------
// flagBit 0x63
EWRAM_CODE void NvExecParseFlagBit(void)
{
	u8 n1 = LexGetHex();
	u8 n2 = LexGetHex();
	u8 n3 = LexGetHex();
	u8 f  = NvGetFlag(n1);

	if(n3 != 0)
	{
		TRACEOUT("[flagBit [%x](%x) |=  %x]\n", n1, f,  (1 << n2));
		f |=  (1 << n2);
	}
	else
	{
		TRACEOUT("[flagBit [%x](%x) &= ~%x]\n", n1, f, ~(1 << n2));
		f &= ~(1 << n2);
	}

	NvSetFlag(n1, f);
}
//---------------------------------------------------------------------------
// メッセージ表示後クリア 0x69
EWRAM_CODE void NvExecParseMsgClr(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// メッセージ表示 0x6a
EWRAM_CODE void NvExecParseMsg(void)
{
	u16 n = LexGetHex();

	TRACEOUT("[msg %x]\n", n);

	NvSetMsg(n);
}
//---------------------------------------------------------------------------
// 画面を明るくする 0x73
EWRAM_CODE void NvExecParseLight(void)
{
	TRACEOUT("[light]\n");

	NvSetEffectBefore(IMG_EFFECT_WHITE);

	Nv.isLoop = FALSE;
}
//---------------------------------------------------------------------------
// ホワイトアウト 0x77
EWRAM_CODE void NvExecParseWhiteOut(void)
{
	TRACEOUT("[whiteOut]\n");

	NvSetEffectBefore(IMG_EFFECT_WHITE);

	Nv.isLoop = FALSE;
}
//---------------------------------------------------------------------------
// ホワイトイン 0x78
EWRAM_CODE void NvExecParseWhiteIn(void)
{
	TRACEOUT("[whiteIn]\n");

	NvSetEffectAfter(IMG_EFFECT_WHITE);

	Nv.isLoop = FALSE;
}
//---------------------------------------------------------------------------
// BGM開始 0x80
EWRAM_CODE void NvExecParseBgm(void)
{
	u16 n = LexGetHex();

	TRACEOUT("[bgm %x]\n", n);

	BgmPlay(n, TRUE);
}
//---------------------------------------------------------------------------
// BGMフェード 0x81
EWRAM_CODE void NvExecParseBgmFade(void)
{
	TRACEOUT("[bgmFade]\n");

	BgmStop();
}
//---------------------------------------------------------------------------
// BGM停止 0x82
EWRAM_CODE void NvExecParseBgmStop(void)
{
	TRACEOUT("[bgmStop]\n");

	BgmStop();
}
//---------------------------------------------------------------------------
// BGMフェード終了待ち 0x85
EWRAM_CODE void NvExecParseBgmWaitFade(void)
{
	TRACEOUT("[bgmFade]\n");

	// EMPTY
}
//---------------------------------------------------------------------------
// BGM開始2 0x87
EWRAM_CODE void NvExecParseBgm2(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// BGM NEXT 0x88
EWRAM_CODE void NvExecParseBgmNext(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// ゲーム終了 0x94
EWRAM_CODE void NvExecParseGameEnd(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// エンディング 0x95
EWRAM_CODE void NvExecParseEnding(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// PCMロード 0xa0
EWRAM_CODE void NvExecParsePcmLoad(void)
{
	u8 n = LexGetHex();

	TRACEOUT("[pcmLoad %x]\n", n);

	SeSetNo(n);
}
//---------------------------------------------------------------------------
// PCM停止 0xa1
EWRAM_CODE void NvExecParsePcmStop(void)
{
	TRACEOUT("[pcmStop]\n");

	SeStop();
}
//---------------------------------------------------------------------------
// PCM再生 0xa2
EWRAM_CODE void NvExecParsePcmPlay(void)
{
	u8 n = LexGetHex();		// ループカウンタ

	TRACEOUT("[pcmPlay %x]\n", n);

	SePlay(n);
}
//---------------------------------------------------------------------------
// PCM待ち 0xa3
EWRAM_CODE void NvExecParsePcmWait(void)
{
	TRACEOUT("[pcmWait]\n");

	// EMPTY
}
//---------------------------------------------------------------------------
// メッセージ終了 0xaf
EWRAM_CODE void NvExecParseEndMsg(void)
{
	TRACEOUT("[endMsg]\n");

	Nv.pCur = Nv.pRet;
}
//---------------------------------------------------------------------------
// 改行 0xb0
EWRAM_CODE void NvExecParseCr(void)
{
	TRACEOUT("[cr]\n");

	// EMPTY
}
//---------------------------------------------------------------------------
// キー入力待ち 0xb2
EWRAM_CODE void NvExecParseKey(void)
{
	TRACEOUT("[key]\n");

	Nv.act = NV_ACT_KEY;
	Nv.step = 0;

	Nv.isLoop = FALSE;
}
//---------------------------------------------------------------------------
// 改ページ 0xb3
EWRAM_CODE void NvExecParsePage(void)
{
	TRACEOUT("[page]\n");

	TextSetPage();

	Nv.act = NV_ACT_KEY;
	Nv.step = 0;

	Nv.isLoop = FALSE;
}
//---------------------------------------------------------------------------
// 文字描画速度変更 0xb6
EWRAM_CODE void NvExecParseTimeTxt(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 時間待ち 0xb7
EWRAM_CODE void NvExecParseTimeWait(void)
{
	u16 n = LexGetHex();

	TRACEOUT("[timeWait %x]\n", n);

	if(Nv.isSkip == TRUE)
	{
		return;
	}

	Nv.wait = n * 10 / 16;		// n * 10ms / 16ms(vblank)
	Nv.isLoop = FALSE;
}
//---------------------------------------------------------------------------
// 文字位置変更 0xb9
EWRAM_CODE void NvExecParseTxtXy(void)
{
	TRACEOUT("[txtXY]\n");

	// EMPTY
}
//---------------------------------------------------------------------------
// フラッシュエフェクト 0xbb
EWRAM_CODE void NvExecParseFlash(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 「どかっ」画面振動 0xbc
EWRAM_CODE void NvExecParseShake(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 背景ロードその2 0xbd, 0xbe
EWRAM_CODE void NvExecParseBg2(void)
{
	u8 n1 = LexGetHex();
	u8 n2 = LexGetHex();
	u8 n3 = LexGetHex();

	TRACEOUT("[Bg2 %x %x %x]\n", n1, n2, n3);

	NvSetEffectBefore(n2);
	ImgSetBg(n1);
	NvSetEffectAfter(n3);

	Nv.isLoop = FALSE;
}
//---------------------------------------------------------------------------
// VISUALロード2 0xbf
EWRAM_CODE void NvExecParseVisLoad2(void)
{
	u8 n1 = LexGetHex();
	u8 n2 = LexGetHex();
	u8 n3 = LexGetHex();

	TRACEOUT("[visLoad2 %x %x %x]\n", n1, n2, n3);

	NvSetEffectBefore(n2);
	ImgSetBgV(n1);
	NvSetEffectAfter(n3);

	Nv.isLoop = FALSE;
/*
	TODO
        // あかりの髪型処理
        if ((no == 0x11 || no == 0x13) && 
            (state->flag[TOHEART_FLAG_AKARI] & 0x01)) {
            no = 0x12;
        }
*/

// ToHeartClearCharacter(lvns, 3);

}
//---------------------------------------------------------------------------
// Hシーンロード 0xc0
EWRAM_CODE void NvExecParseLoadH(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// キャラクタ変更 0xc1
EWRAM_CODE void NvExecParseChrChg(void)
{
	u8  n1 = LexGetHex();
	u16 n2 = LexGetHex();
	u16 no = NvGetChrNo(n2);

	TRACEOUT("[chrChg %x %x]\n", n1, n2);

	ImgSetChr(no, n1);
	NvSetEffectAfter(IMG_EFFECT_FADE_MASK);

	Nv.isLoop = FALSE;
}
//---------------------------------------------------------------------------
// キャラクタ表示 0xc2
EWRAM_CODE void NvExecParseChrDisp(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// キャラクタ全消去後表示 0xc3
EWRAM_CODE void NvExecParseChrClrAll(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 背景付きキャラクタロード 0xc4
EWRAM_CODE void NvExecParseBgChr(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 3キャラ同時表示 0xc6
EWRAM_CODE void NvExecParseChr3(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 日付更新（カレンダー有） 0xf5
EWRAM_CODE void NvExecParseDay2(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 雨 0xf7 0x01
EWRAM_CODE void NvExecParseRain(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// さくら 0xf7 0x04
EWRAM_CODE void NvExecParseSakura(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// イベントエンド 0xff
EWRAM_CODE void NvExecParseEndEvent(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// スキップ
EWRAM_CODE void NvExecParseSkip(void)
{
	TRACEOUT("[skip]\n");

	// EMPTY
}
//---------------------------------------------------------------------------
// テキスト
EWRAM_CODE void NvExecParseText(char* p)
{
	TRACEOUT("[%s]\n", p);

	TextSetDraw(p);
	NvSetEffectAfter(IMG_EFFECT_TEXT_ON);

	Nv.isLoop = FALSE;
}
