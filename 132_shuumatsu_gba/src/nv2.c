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
	{ "_r", 1, (void*)NvExecParse1R  },	// �L�[���́{���y�[�W�i���A�C�R���j
	{ "_t", 1, (void*)NvExecParse1T  },	// �L�[���́{���s�i�w�A�C�R���j
	{ "_m", 1, (void*)NvExecParse1M  },	// �e�L�X�g�\��
	{ "_n", 1, (void*)NvExecParse1N  },	// ���s
	{ "!g", 1, (void*)NvExecParse2G  },	// �w�i
	{ "!b", 1, (void*)NvExecParse2B  },	// ���y
	{ "!e", 1, (void*)NvExecParse2E  },	// ���ʉ�
	{ "!x", 2, (void*)NvExecParse2X  },	// �����G
	{ "!j", 1, (void*)NvExecParse2J  },	// �X�N���v�g�W�����v
	{ "!t", 1, (void*)NvExecParse2T  },	// �^�C�g��
	{ "!s", 2, (void*)NvExecParse2S  },	// ����
	{ "#g", 1, (void*)NvExecParse3G  },	// CALL
	{ "#r", 0, (void*)NvExecParse3R  },	// RET
	{ "#l", 0, (void*)NvExecParse3L  },	// ELSE
	{ "#n", 0, (void*)NvExecParse3N  },	// ENDIF
	{ "#i", 3, (void*)NvExecParse3I  },	// IF
	{ "#W", 1, (void*)NvExecParse3W  },	// �G�t�F�N�g
	{ "#t", 1, (void*)NvExecParse3T  },	// �E�F�C�g
	{ ";;", 0, (void*)NvExecParseSel },	// �I����
	{ "[]", 3, (void*)NvExecParseCal },	// �v�Z��
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
// �L�[���́{���y�[�W�i���A�C�R���j
void NvExecParse1R(void)
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
// �L�[���́{���s�i�w�A�C�R���j
void NvExecParse1T(void)
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
// �e�L�X�g�\��
void NvExecParse1M(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetMsg(s);
	TxtSetExec();
}
//---------------------------------------------------------------------------
// ���s
void NvExecParse1N(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetMsg(s);
	TxtSetLf();
}
//---------------------------------------------------------------------------
// �w�i
void NvExecParse2G(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	ImgClrChrAll();
	ImgSetBg(no);

	Nv.isEffect = true;
}
//---------------------------------------------------------------------------
// ���y
void NvExecParse2B(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	BgmPlay(no);
}
//---------------------------------------------------------------------------
// ���ʉ�
void NvExecParse2E(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	// �w�Z�̃x������
	if(Nv.isSkip == true && no == 0)
	{
		return;
	}

	SePlay(no);
}
//---------------------------------------------------------------------------
// �����G
void NvExecParse2X(void)
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
// �X�N���v�g�W�����v
void NvExecParse2J(void)
{
	s32 no = NvCurNum();

	TRACE("%d\n", no);

	Nv.isLoop = false;

	if(no != 1)
	{
		NvSetScn2(no);

		return;
	}

	// �I�[�v�j���O����
	NvSetRead(Nv.idx, Nv.bit);
	Nv.isSkip = false;

	ImgSetEff(IMG_EFFECT_TITL);
	Nv.isEffect = true;

	MenuSetTitle(MENU_TITLE_SEL_LOAD);
	ManageSetAct(MANAGE_ACT_MENU);
}
//---------------------------------------------------------------------------
// �^�C�g��
void NvExecParse2T(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetTitle(s);
}
//---------------------------------------------------------------------------
// ����
void NvExecParse2S(void)
{
	s32 i = NvCurNum();
	s32 b = NvCurNum();

	TRACE("%d %d\n", i, b);

	// 1�O�̊��ǃt���O��L���ɂ��܂�
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
void NvExecParse3G(void)
{
	s32 no = NvCurNum();

	TRACE("%d\n", no);

	_ASSERT(Nv.call.isUse == false);


	s32   tmp  = Nv.no;
	char* pTmp = Nv.pCur;

	NvSetScn2(no);

	Nv.call.no    = tmp;
	Nv.call.pCur  = pTmp;
	Nv.call.isUse = true;
}
//---------------------------------------------------------------------------
// RET
void NvExecParse3R(void)
{
	_ASSERT(Nv.call.isUse == true);

	NvSetScn2(Nv.call.no);

	Nv.pCur = Nv.call.pCur;
}
//---------------------------------------------------------------------------
// ELSE
void NvExecParse3L(void)
{
	NvExprFlip();
}
//---------------------------------------------------------------------------
// ENDIF
void NvExecParse3N(void)
{
	NvExprPop();
}
//---------------------------------------------------------------------------
// IF
void NvExecParse3I(void)
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
// �G�t�F�N�g
void NvExecParse3W(void)
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
// �E�F�C�g
void NvExecParse3T(void)
{
	s32 w = NvCurNum();

	TRACE("%d\n", w);

	// �Q�[���I���u�ǂ��I�����v�̃^�C�~���O
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
// �I����
void NvExecParseSel(void)
{
	Nv.sel.cnt = -1;

	NvSetAct(NV_ACT_SEL);
	ManageSetAct(MANAGE_ACT_SEL);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �v�Z��
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
// �X�N���v�g�R�}���h�̎��s�L��
bool NvIsExecParseCmd(char* p)
{
	// IF���߂̃l�X�g�^�U�iexpr�j���m�F
	if(NvIsExpr() == true)
	{
		return true;
	}

	// # �ȊO�͎��s���Ȃ�
	if(p[0] != '#')
	{
		return false;
	}

	// IF, ELSE, ENDIF���߂͎��s
	if(p[1] == 'i' || p[1] == 'l' || p[1] == 'n')
	{
		return true;
	}

	return false;
}
