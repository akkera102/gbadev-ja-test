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
// �Q�[���e�L�X�g��\��
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
// ���͑҂�
EWRAM_CODE void NvExecParseKey(void)
{
	TxtSetCur(true);

	Nv.isLoop = false;
	NvSetAct(NV_ACT_KEY);
}
//---------------------------------------------------------------------------
// �w�i�Z�b�g
EWRAM_CODE void NvExecParseBgl(void)
{
	char* p = NvNextCurStr();

//	TRACE("%s\n", p);

	ImgClrBg();
	ImgClrChr();
	ImgSetBg(p);
}
//---------------------------------------------------------------------------
// �L�����N�^�Z�b�g
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
// �G�t�F�N�g
EWRAM_CODE void NvExecParseEff(void)
{
	s32 no = NvNextCurNum();

//	TRACE("%d\n", no);

	ImgSetEff(no, 0);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// BGM�X�^�[�g
EWRAM_CODE void NvExecParseBgm(void)
{
	s32 b = NvNextCurNum();
	char* p = NvNextCurStr();

//	TRACE("%s %d\n", p, b);

	BgmPlay2(p, (b == 1) ? true : false);
}
//---------------------------------------------------------------------------
// BGM�X�g�b�v
EWRAM_CODE void NvExecParseBgs(void)
{
	BgmStop();
}
//---------------------------------------------------------------------------
// ���ʉ��X�^�[�g
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
// ���ʉ��X�g�b�v
EWRAM_CODE void NvExecParseFms(void)
{
	SeStop();
}
//---------------------------------------------------------------------------
// �E�F�C�g
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
// �I����
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
// �����t���W�����v
EWRAM_CODE void NvExecParseJmp(void)
{
	s32 x  = NvNextCurNum();
	s32 op = NvNextCurNum();
	s32 y  = NvNextCurNum();
	s32 z  = NvNextCurNum();
	s32 v  = NvGetVar(x);

	// != �� == �̂ݎg�p
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
// ���x��
EWRAM_CODE void NvExecParseLbl(void)
{
	// skip
	NvNextCurNum();
}
//---------------------------------------------------------------------------
// �ϐ��v�Z
EWRAM_CODE void NvExecParseVar(void)
{
	s32 x  = NvNextCurNum();
	s32 op = NvNextCurNum();
	s32 y  = NvNextCurNum();
	s32 v  = NvGetVar(x);

	// = �̂ݎg�p
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
// �X�N���v�g�W�����v
EWRAM_CODE void NvExecParseLds(void)
{
	char* p = NvNextCurStr();

	// TRACE("%s\n", p);

	NvSetScn(p);
}
//---------------------------------------------------------------------------
// ���x���W�����v
EWRAM_CODE void NvExecParseGot(void)
{
	s32 no = NvNextCurNum();

	// TRACE("%d\n", no);

	NvSetLbl(no);
}
//---------------------------------------------------------------------------
// �X�N���[���摜�̐ݒ�
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
// �X�^�[�g���j���[�iPIL2�݂̂Ŏg�p�j
EWRAM_CODE void NvExecParseSta(void)
{
	ImgSetEff(IMG_EFFECT_TXT_IN, 0);

	MenuSetTitle(MENU_TITLE_SEL_LOAD);
	ManageSetMenu();

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �I�[�v�j���O���b�Z�[�W�iTAI�݂̂Ŏg�p�j
EWRAM_CODE void NvExecParseTai(void)
{
	s32 x   = NvNextCurNum();
	s32 y   = NvNextCurNum();
	char* p = NvNextCurStr();

	if(y == 0)
	{
		TxtHideMsg();	// �e�L�X�g�S�̏���
		TxtShowMsg();
	}

	TxtDrawStrXy(x, y, p);
}
//---------------------------------------------------------------------------
// �X�N���v�g�G���h
EWRAM_CODE void NvExecParseEnd(void)
{
	SystemError("[Err] NvExecParseEnd\n");
}
