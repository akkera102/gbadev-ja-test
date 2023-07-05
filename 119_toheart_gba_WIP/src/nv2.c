#include "nv.h"
#include "nv2.h"
#include "nv3.h"
#include "img.h"
#include "bgm.h"
#include "siori.h"
#include "txt.h"
#include "se.h"


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
	Nv.isLoop = true;

	do
	{
		NvExecParseSub();

	} while(Nv.isLoop == true);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecParseSub(void)
{
	// �A�h���X
	u16 n = NvGetCurHex();
	TRACE("[%04X] ", n);
	Nv.curAdr = n;

	// �e�L�X�gor���߃Z�b�g

	NvSetCurStr();

	if(_IsSJIS(Nv.str[0]) == true)
	{
		NvExecParseTxt();
		Nv.isLoop = false;

		return;
	}

	u32 i;

	for(i=0; i<NV_MAX_PARSE_CNT; i++)
	{
		if(_Strncmp(Nv.str, NvParseTable[i].pStr, 20) == 0)
		{
			break;
		}
	}
	_ASSERT(i < NV_MAX_PARSE_CNT);

	NvParseTable[i].pFunc();
}
//---------------------------------------------------------------------------
// �V�i���I�I�� 0x20
EWRAM_CODE void NvExecParseEndScn(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �^�C�g������ 0x21+0x03
EWRAM_CODE void NvExecParseTitle(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �I���� 0x24
EWRAM_CODE void NvExecParseSel(void)
{
	TRACE("sel ");

	Nv.sel.cnt = NvGetCurHex();
	Nv.sel.msg = NvGetCurHex();
	Nv.sel.num = -1;

	TRACE("%x %x\n", Nv.sel.cnt, Nv.sel.msg);

	s32 i;

	for(i=0; i<Nv.sel.cnt; i++)
	{
		Nv.sel.item[i] = NvGetCurHex();
		Nv.sel.jump[i] = NvGetCurHex();
	}

	Nv.sel.pSrc   = Nv.pCur;
	Nv.sel.srcAdr = Nv.curAdr;


	for(i=0; i<Nv.sel.cnt; i++)
	{
		NvSetMsg(Nv.sel.item[i]);

		while(_IsSJIS(*Nv.pCur) == false)
		{
			Nv.pCur++;
		}

		Nv.sel.pStr[i] = Nv.pCur;
	}

	NvSetMsg(Nv.sel.msg);

	Nv.isSel  = true;
}
//---------------------------------------------------------------------------
// �W�����v�t�@�C�� 0x28
EWRAM_CODE void NvExecParseJmpScn(void)
{
	u16 n1 = NvGetCurHex();
	u8  n2 = NvGetCurHex();

	TRACE("jmpScn %x %x\n", n1, n2);

	NvSetScn(n1);
	NvSetEvt(n2);
}
//---------------------------------------------------------------------------
// �W�����v�u���b�N 0x29
EWRAM_CODE void NvExecParseJmpBlk(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �ϑI���� 0x2b
EWRAM_CODE void NvExecParseSelOpt(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// PUSH A 0x2b
EWRAM_CODE void NvExecParsePushA(void)
{
	u8 n1 = NvGetCurHex();
	u8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();

	TRACE("pushA %x %x\n", n1, n2);

	NvAddFlag(NV_FLAG_A_SCN1, n1);
	NvAddFlag(NV_FLAG_A_SCN2, n2);
	NvAddFlag(NV_FLAG_A_BLK,  n3);
}
//---------------------------------------------------------------------------
// RET A 0x2e
EWRAM_CODE void NvExecParseRetA(void)
{
	TRACE("retA\n");

	u16 scn = NvGetFlag(NV_FLAG_A_SCN2) + (NvGetFlag(NV_FLAG_A_SCN1) << 8);
	u8  evt = NvGetFlag(NV_FLAG_A_BLK);

	NvSetScn(scn);
	NvSetEvt(evt);
}
//---------------------------------------------------------------------------
// PUSH B 0x2f
EWRAM_CODE void NvExecParsePushB(void)
{
	u8 n1 = NvGetCurHex();
	u8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();

	TRACE("pushB %x %x\n", n1, n2);

	NvAddFlag(NV_FLAG_B_SCN1, n1);
	NvAddFlag(NV_FLAG_B_SCN2, n2);
	NvAddFlag(NV_FLAG_B_BLK,  n3);
}
//---------------------------------------------------------------------------
// RET B 0x30
EWRAM_CODE void NvExecParseRetB(void)
{
	TRACE("retB\n");

	u16 scn = NvGetFlag(NV_FLAG_B_SCN2) + (NvGetFlag(NV_FLAG_B_SCN1) << 8);
	u8  evt = NvGetFlag(NV_FLAG_B_BLK);

	NvSetScn(scn);
	NvSetEvt(evt);
}
//---------------------------------------------------------------------------
// ���t�X�V�i�J�����_�[���j 0x32
EWRAM_CODE void NvExecParseDay(void)
{
	u8 n = NvGetCurHex();

	TRACE("day %x\n", n);


	if(n == 0xf0)
	{
		NvSetFlag(NV_FLAG_DAY, 3);
	}
	else
	{
		NvAddFlag(NV_FLAG_DAY, 1);
	}

	NvSetFlag(NV_FLAG_WEEK, DivMod(NvGetFlag(NV_FLAG_DAY) + 5, 7));
}
//---------------------------------------------------------------------------
// ���Ԑݒ� 0x33
EWRAM_CODE void NvExecParseTime(void)
{
	u8 n = NvGetCurHex();

	TRACE("time %x\n", n);

	// �s���t���O�������B�����ŗǂ��̂��ǂ����͕s��
	Nv.flag[NV_FLAG_EVENT_DONE] = 0;
	Nv.flag[NV_FLAG_IDOU] = 0;

	if(n >= 0xf0)
	{
		// �\�������X�V
		Nv.flag[NV_FLAG_TIME] = n - 0xf0;
	}
	else
	{
		// �\���L��X�V
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
// �t���O���Z 0x34,0x62
EWRAM_CODE void NvExecParseFlagAdd(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �t���O���Z 0x35
EWRAM_CODE void NvExecParseFlagSub(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �w�i���[�h 0x3c
EWRAM_CODE void NvExecParseBg(void)
{
	u8 n = NvGetCurHex();

	TRACE("bg %x\n", n);

	ImgSetBg(n);
}
//---------------------------------------------------------------------------
// �L�����N�^���� 0x3d
EWRAM_CODE void NvExecParseChrClr(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// VISUAL���[�h 0x42
EWRAM_CODE void NvExecParseVisLoad(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �L�����N�^�\�� 0x43
EWRAM_CODE void NvExecParseChrLoad(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �\������ 0x45
EWRAM_CODE void NvExecParseDisp(void)
{
	u8 n = NvGetCurHex();

	TRACE("disp %x\n", n);

	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �Z�s�A 0x47 0x01
EWRAM_CODE void NvExecParseSepia(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// ������W�����v 0x55
EWRAM_CODE void NvExecParseJmpAdr(void)
{
	u8 n = NvGetCurHex();

	TRACE("jmpAdr %x\n", n);

	NvJumpCurAdr(Nv.curAdr + 2 + n);
}
//---------------------------------------------------------------------------
// if== 0x56
EWRAM_CODE void NvExecParseIf1(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();
	u8 f  = NvGetFlag(n1);

	TRACE("if [%x](%x) == %x goto %x\n", n1, f, n2, n3);

	if(f == n2)
	{
		NvJumpCurAdr(Nv.curAdr + 4 + n3);
	}
}
//---------------------------------------------------------------------------
// if!= 0x57
EWRAM_CODE void NvExecParseIf2(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();
	u8 f  = NvGetFlag(n1);

	TRACE("if [%x](%x) != %x goto %x\n", n1, f, n2, n3);

	if(f != n2)
	{
		NvJumpCurAdr(Nv.curAdr + 4 + n3);
	}
}
//---------------------------------------------------------------------------
// if> 0x58
EWRAM_CODE void NvExecParseIf3(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();
	u8 f  = NvGetFlag(n1);

	TRACE("if [%x](%x) > %x goto %x\n", n1, f, n2, n3);

	if(f > n2)
	{
		NvJumpCurAdr(Nv.curAdr + 4 + n3);
	}
}
//---------------------------------------------------------------------------
// if< 0x59
EWRAM_CODE void NvExecParseIf4(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();
	u8 f  = NvGetFlag(n1);

	TRACE("if [%x](%x) < %x goto %x\n", n1, f, n2, n3);

	if(f < n2)
	{
		NvJumpCurAdr(Nv.curAdr + 4 + n3);
	}
}
//---------------------------------------------------------------------------
// if>= 0x5a
EWRAM_CODE void NvExecParseIf5(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();
	u8 f  = NvGetFlag(n1);

	TRACE("if [%x](%x) >= %x goto %x\n", n1, f, n2, n3);

	if(f >= n2)
	{
		NvJumpCurAdr(Nv.curAdr + 4 + n3);
	}
}
//---------------------------------------------------------------------------
// if<= 0x5b
EWRAM_CODE void NvExecParseIf6(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();
	u8 f  = NvGetFlag(n1);

	TRACE("if [%x](%x) <= %x goto %x\n", n1, f, n2, n3);

	if(f <= n2)
	{
		NvJumpCurAdr(Nv.curAdr + 4 + n3);
	}
}
//---------------------------------------------------------------------------
// ifBitSet 0x5e
EWRAM_CODE void NvExecParseIfBitSet(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();
	u8 f  = NvGetFlag(n1);

	TRACE("ifBitSet [%x](%x) & %x goto %x\n", n1, f, 1 << n2, n3);

	if(f & (1 << n2))
	{
		NvJumpCurAdr(Nv.curAdr + 4 + n3);
	}
}
//---------------------------------------------------------------------------
// ifBitRes 0x5f
EWRAM_CODE void NvExecParseIfBitRes(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();
	u8 f  = NvGetFlag(n1);

	TRACE("ifBitRes [%x](%x) & %x goto %x\n", n1, f, 1 << n2, n3);

	if(!(f & (1 << n2)))
	{
		NvJumpCurAdr(Nv.curAdr + 4 + n3);
	}
}
//---------------------------------------------------------------------------
// flagSet 0x61
EWRAM_CODE void NvExecParseFlagSet(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();

	TRACE("flagSet [%x] = %x\n", n1, n2);

	NvSetFlag(n1, n2);
}
//---------------------------------------------------------------------------
// flagBit 0x63
EWRAM_CODE void NvExecParseFlagBit(void)
{
	u8 n1 = NvGetCurHex();
	s8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();
	u8 f  = NvGetFlag(n1);

	if(n3 != 0)
	{
		TRACE("flagBit [%x](%x) |=  %x\n", n1, f,  (1 << n2));
		f |=  (1 << n2);
	}
	else
	{
		TRACE("flagBit [%x](%x) &= ~%x\n", n1, f, ~(1 << n2));
		f &= ~(1 << n2);
	}

	NvSetFlag(n1, f);
}
//---------------------------------------------------------------------------
// ���b�Z�[�W�\����N���A 0x69
EWRAM_CODE void NvExecParseMsgClr(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// ���b�Z�[�W�\�� 0x6a
EWRAM_CODE void NvExecParseMsg(void)
{
	u16 n = NvGetCurHex();

	TRACE("msg %x\n", n);

	NvSetMsg(n);
}
//---------------------------------------------------------------------------
// ��ʂ𖾂邭���� 0x73
EWRAM_CODE void NvExecParseLight(void)
{
	TRACE("light\n");

	NvSetEffectBefore(IMG_EFFECT_WHITE);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �z���C�g�A�E�g 0x77
EWRAM_CODE void NvExecParseWhiteOut(void)
{
	TRACE("whiteOut\n");

	NvSetEffectBefore(IMG_EFFECT_WHITE);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �z���C�g�C�� 0x78
EWRAM_CODE void NvExecParseWhiteIn(void)
{
	TRACE("whiteIn\n");

	NvSetEffectAfter(IMG_EFFECT_WHITE);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// BGM�J�n 0x80
EWRAM_CODE void NvExecParseBgm(void)
{
	u16 n = NvGetCurHex();

	TRACE("bgm %x\n", n);

	BgmPlay(n, true);
}
//---------------------------------------------------------------------------
// BGM�t�F�[�h 0x81
EWRAM_CODE void NvExecParseBgmFade(void)
{
	TRACE("bgmFade\n");

	BgmStop();
}
//---------------------------------------------------------------------------
// BGM��~ 0x82
EWRAM_CODE void NvExecParseBgmStop(void)
{
	TRACE("bgmStop\n");

	BgmStop();
}
//---------------------------------------------------------------------------
// BGM�t�F�[�h�I���҂� 0x85
EWRAM_CODE void NvExecParseBgmWaitFade(void)
{
	TRACE("bgmFade\n");

	// EMPTY
}
//---------------------------------------------------------------------------
// BGM�J�n2 0x87
EWRAM_CODE void NvExecParseBgm2(void)
{
	u16 n = NvGetCurHex();

	TRACE("bgm2 %x\n", n);

	BgmPlay(n, true);
}
//---------------------------------------------------------------------------
// BGM NEXT 0x88
EWRAM_CODE void NvExecParseBgmNext(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �Q�[���I�� 0x94
EWRAM_CODE void NvExecParseGameEnd(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �G���f�B���O 0x95
EWRAM_CODE void NvExecParseEnding(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// PCM���[�h 0xa0
EWRAM_CODE void NvExecParsePcmLoad(void)
{
	u8 n = NvGetCurHex();

	TRACE("pcmLoad %x\n", n);

	SeSetNo(n);
}
//---------------------------------------------------------------------------
// PCM��~ 0xa1
EWRAM_CODE void NvExecParsePcmStop(void)
{
	TRACE("pcmStop\n");

	SeStop();
}
//---------------------------------------------------------------------------
// PCM�Đ� 0xa2
EWRAM_CODE void NvExecParsePcmPlay(void)
{
	u8 n = NvGetCurHex();		// ���[�v�J�E���^

	TRACE("pcmPlay %x\n", n);

	SePlay(n);
}
//---------------------------------------------------------------------------
// PCM�҂� 0xa3
EWRAM_CODE void NvExecParsePcmWait(void)
{
	TRACE("pcmWait\n");

	// EMPTY
}
//---------------------------------------------------------------------------
// ���b�Z�[�W�I�� 0xaf
EWRAM_CODE void NvExecParseEndMsg(void)
{
	TRACE("endMsg\n");

	Nv.pCur = Nv.pRet;

	// �I�������b�Z�[�W�̏ꍇ
	if(Nv.isSel == true)
	{
		Nv.isSel = false;
		Nv.isLoop = false;

		TxtSetPageNew();
		NvSetAct(NV_ACT_SELECT);
	}
}
//---------------------------------------------------------------------------
// ���s 0xb0
EWRAM_CODE void NvExecParseCr(void)
{
	TRACE("cr\n");

	// EMPTY
}
//---------------------------------------------------------------------------
// �L�[���͑҂� 0xb2
EWRAM_CODE void NvExecParseKey(void)
{
	TRACE("key\n");

	Nv.act = NV_ACT_KEY;
	Nv.step = 0;

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// ���y�[�W 0xb3
EWRAM_CODE void NvExecParsePage(void)
{
	TRACE("page\n");

	TxtSetPage();

	Nv.act = NV_ACT_KEY;
	Nv.step = 0;

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �����`�摬�x�ύX 0xb6
EWRAM_CODE void NvExecParseTimeTxt(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// ���ԑ҂� 0xb7
EWRAM_CODE void NvExecParseTimeWait(void)
{
	u16 n = NvGetCurHex();

	TRACE("timeWait %x\n", n);

	if(Nv.isSkip == true)
	{
		return;
	}

	Nv.wait = n * 10 / 16;		// n * 10ms / 16ms(vblank)
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �����ʒu�ύX 0xb9
EWRAM_CODE void NvExecParseTxtXy(void)
{
	TRACE("txtXY\n");

	// EMPTY
}
//---------------------------------------------------------------------------
// �t���b�V���G�t�F�N�g 0xbb
EWRAM_CODE void NvExecParseFlash(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �u�ǂ����v��ʐU�� 0xbc
EWRAM_CODE void NvExecParseShake(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �w�i���[�h����2 0xbd, 0xbe
EWRAM_CODE void NvExecParseBg2(void)
{
	u8 n1 = NvGetCurHex();
	u8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();

	TRACE("Bg2 %x %x %x\n", n1, n2, n3);

	NvSetEffectBefore(n2);
	ImgSetBg(n1);
	NvSetEffectAfter(n3);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// VISUAL���[�h2 0xbf
EWRAM_CODE void NvExecParseVisLoad2(void)
{
	u8 n1 = NvGetCurHex();
	u8 n2 = NvGetCurHex();
	u8 n3 = NvGetCurHex();

	TRACE("visLoad2 %x %x %x\n", n1, n2, n3);

	NvSetEffectBefore(n2);
	ImgSetBgV(n1);
	NvSetEffectAfter(n3);

	Nv.isLoop = false;
/*
	TODO
        // ������̔��^����
        if ((no == 0x11 || no == 0x13) && 
            (state->flag[TOHEART_FLAG_AKARI] & 0x01)) {
            no = 0x12;
        }
*/

// ToHeartClearCharacter(lvns, 3);

}
//---------------------------------------------------------------------------
// H�V�[�����[�h 0xc0
EWRAM_CODE void NvExecParseLoadH(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �L�����N�^�ύX 0xc1
EWRAM_CODE void NvExecParseChrChg(void)
{
	u8  n1 = NvGetCurHex();
	u16 n2 = NvGetCurHex();
	u16 no = NvGetChrNo(n2);

	TRACE("chrChg %x %x\n", n1, n2);

	ImgSetChr(no, n1);
	NvSetEffectAfter(IMG_EFFECT_FADE_MASK);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �L�����N�^�\�� 0xc2
EWRAM_CODE void NvExecParseChrDisp(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �L�����N�^�S������\�� 0xc3
EWRAM_CODE void NvExecParseChrClrAll(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �w�i�t���L�����N�^���[�h 0xc4
EWRAM_CODE void NvExecParseBgChr(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// 3�L���������\�� 0xc6
EWRAM_CODE void NvExecParseChr3(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// ���t�X�V�i�J�����_�[�L�j 0xf5
EWRAM_CODE void NvExecParseDay2(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �J 0xf7 0x01
EWRAM_CODE void NvExecParseRain(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// ������ 0xf7 0x04
EWRAM_CODE void NvExecParseSakura(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �C�x���g�G���h 0xff
EWRAM_CODE void NvExecParseEndEvent(void)
{
	_ASSERT(0);
}
//---------------------------------------------------------------------------
// �X�L�b�v
EWRAM_CODE void NvExecParseSkip(void)
{
	TRACE("skip\n");

	NvSkipCurLine();
}
//---------------------------------------------------------------------------
// �e�L�X�g
EWRAM_CODE void NvExecParseTxt(void)
{
	TRACE("%s\n", Nv.str);

	TxtSetDraw(Nv.str);
	NvSetEffectAfter(IMG_EFFECT_TXT_ON);
}
