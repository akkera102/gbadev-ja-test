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
	{ "!g", 1, (void*)NvExecParse1G  },	// �w�i
	{ "!b", 1, (void*)NvExecParse1B  },	// ���y
	{ "!e", 1, (void*)NvExecParse1E  },	// ���ʉ�
	{ "!x", 2, (void*)NvExecParse1X  },	// �����G
	{ "!j", 1, (void*)NvExecParse1J  },	// �X�N���v�g�W�����v
	{ "!t", 1, (void*)NvExecParse1T  },	// �^�C�g��
	{ "!s", 2, (void*)NvExecParse1S  },	// ����
	{ "#g", 1, (void*)NvExecParse2G  },	// CALL
	{ "#r", 0, (void*)NvExecParse2R  },	// RET
	{ "#l", 0, (void*)NvExecParse2L  },	// ELSE
	{ "#n", 0, (void*)NvExecParse2N  },	// ENDIF
	{ "#i", 3, (void*)NvExecParse2I  },	// IF
	{ "#W", 1, (void*)NvExecParse2W  },	// �G�t�F�N�g
	{ "#t", 1, (void*)NvExecParse2T  },	// �E�F�C�g
	{ "_r", 1, (void*)NvExecParse3R  },	// �L�[���́{���y�[�W�i���A�C�R���j
	{ "_t", 1, (void*)NvExecParse3T  },	// �L�[���́{���s�i�w�A�C�R���j
	{ "_m", 1, (void*)NvExecParse3M  },	// �e�L�X�g�\��
	{ "_n", 1, (void*)NvExecParse3N  },	// ���s
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
// �w�i
void NvExecParse1G(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	ImgClrChrAll();
	ImgSetBg(no);

	Nv.isEffect = true;
}
//---------------------------------------------------------------------------
// ���y
void NvExecParse1B(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	BgmPlay(no);
}
//---------------------------------------------------------------------------
// ���ʉ�
void NvExecParse1E(void)
{
	s32 no = NvCurNum();

//	TRACE("%d\n", no);

	// �x���̖�����
	if(Nv.isSkip == true && no == 0)
	{
		return;
	}

	SePlay(no);
}
//---------------------------------------------------------------------------
// �����G
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
// �X�N���v�g�W�����v
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

	// �I�[�v�j���O����
	ImgSetEff(IMG_EFFECT_TITL);
	Nv.isEffect = true;
	Nv.isSkip = false;

	MenuSetTitle(MENU_TITLE_SEL_LOAD);
	ManageSetAct(MANAGE_ACT_MENU);
}
//---------------------------------------------------------------------------
// �^�C�g��
void NvExecParse1T(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetTitle(s);
}
//---------------------------------------------------------------------------
// ����
void NvExecParse1S(void)
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
// �G�t�F�N�g
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
// �E�F�C�g
void NvExecParse2T(void)
{
	s32 w = NvCurNum();

	TRACE("%d\n", w);

	// �Q�[���I���́u�ǂ��I�����v�̃^�C�~���O
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
// �L�[���́{���y�[�W�i���A�C�R���j
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
// �L�[���́{���s�i�w�A�C�R���j
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
// �e�L�X�g�\��
void NvExecParse3M(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetMsg(s);
	TxtSetExec();
}
//---------------------------------------------------------------------------
// ���s
void NvExecParse3N(void)
{
	char* s = NvCurStr();

	TRACE("%s\n", s);

	TxtSetMsg(s);
	TxtSetLf();
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

	// # �ȊO�͎��s
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
