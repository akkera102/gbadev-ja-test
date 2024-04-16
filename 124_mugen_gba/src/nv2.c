#include "nv.h"
#include "nv2.h"
#include "img.h"
#include "bgm.h"
#include "siori.h"
#include "txt.h"
#include "anime.h"
#include "manage.h"
#include "se.h"
#include "file.h"
#include "menu.h"

//---------------------------------------------------------------------------
ST_NV_PARSE_TABLE NvParseTable[NV_MAX_PARSE_CNT] = {
	{ "MSG", (void*)NvExecParseMsg },
	{ "SEL", (void*)NvExecParseSel },
	{ "KEY", (void*)NvExecParseKey },
	{ "BGL", (void*)NvExecParseBgl },
	{ "CHR", (void*)NvExecParseChr },
	{ "HSC", (void*)NvExecParseHsc },
	{ "EFF", (void*)NvExecParseEff },
	{ "VIB", (void*)NvExecParseVib },
	{ "SET", (void*)NvExecParseSet },
	{ "CLR", (void*)NvExecParseClr },
	{ "BPL", (void*)NvExecParseBpl },
	{ "BST", (void*)NvExecParseBst },
	{ "FMX", (void*)NvExecParseFmx },
	{ "WAT", (void*)NvExecParseWat },
	{ "MEU", (void*)NvExecParseMeu },
	{ "LDS", (void*)NvExecParseLds },
	{ "MAP", (void*)NvExecParseMap },
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

	TRACE("\n[%x_%02d.txt %04x][%s]\n", Nv.chap, Nv.part, Nv.pCur - Nv.pTxt - 4, cmd);

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
// ���b�Z�[�W�\��
EWRAM_CODE void NvExecParseMsg(void)
{
	char* p = NvNextCurStr();
	TRACE("%s\n", p);

	TxtSetMsg(p);
	TxtSetSiori(p);
	ImgSetEff(IMG_EFFECT_TXT_IN);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �Z���N�g�\��
EWRAM_CODE void NvExecParseSel(void)
{
	char* p = NvNextCurStr();
	TRACE("%s\n", p);

	TxtSetSel(p);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// ���͑҂�
EWRAM_CODE void NvExecParseKey(void)
{
	TxtSetCur(true);

	Nv.isLoop = false;
	Nv.act = NV_ACT_KEY;
}
//---------------------------------------------------------------------------
// �w�i�\��
EWRAM_CODE void NvExecParseBgl(void)
{
	char* p = NvNextCurStr();
//	TRACE("%s\n", p);

	ImgClrBgChr();
	ImgSetBg(p);
	ImgSetEff(IMG_EFFECT_DRAW_BG);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �L�����N�^�����G�ȂǕ\��
EWRAM_CODE void NvExecParseChr(void)
{
	char* p = NvNextCurStr();
//	TRACE("%s\n", p);

	ImgSetChr(p);
	ImgSetEff(IMG_EFFECT_DRAW_CHR);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// H�V�[��
EWRAM_CODE void NvExecParseHsc(void)
{
	char* p = NvNextCurStr();
//	TRACE("%s\n", p);

	ImgClrBgChr();
	ImgSetBg(p);
	ImgSetEff(IMG_EFFECT_DRAW_BG);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �G�t�F�N�g�\��
EWRAM_CODE void NvExecParseEff(void)
{
	s32 no = NvNextCurNum();
	s32 arg = NvNextCurNum();
//	TRACE("%d %d\n", no, arg);

	ImgSetEff(no);
	ImgSetFadeWait(arg);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �U���G�t�F�N�g
EWRAM_CODE void NvExecParseVib(void)
{
	ImgSetEff(IMG_EFFECT_VIB);

	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �ʎw��
EWRAM_CODE void NvExecParseSet(void)
{
	char* p = NvNextCurStr();
	s32  no = NvNextCurNum();
//	TRACE("%s %d\n", p, no);

	switch(no)
	{
	case 1: ImgSetBg(p);  break;
	case 2: ImgSetChr(p); break;

	default:
		SystemError("[Err] NvExecParseSet no=%x\n", no);
		break;
	}
}
//---------------------------------------------------------------------------
// ����
EWRAM_CODE void NvExecParseClr(void)
{
	s32 no = NvNextCurNum();
//	TRACE("%d\n", no);

	switch(no)
	{
	case 1: ImgClrBg();    break;
	case 2: ImgClrChr();   break;
	case 3: ImgClrBgChr(); break;

	default:
		SystemError("[Err] NvExecParseClr no=%x\n", no);
		break;
	}
}
//---------------------------------------------------------------------------
// BGM�X�^�[�g
EWRAM_CODE void NvExecParseBpl(void)
{
	s32 no = NvNextCurNum();
//	TRACE("%d\n", no);

	BgmPlay2(no, true);
}
//---------------------------------------------------------------------------
// BGM�X�g�b�v
EWRAM_CODE void NvExecParseBst(void)
{
	BgmStop();
}
//---------------------------------------------------------------------------
// ���ʉ�
EWRAM_CODE void NvExecParseFmx(void)
{
	s32 no = NvNextCurNum();
//	TRACE("%d\n", no);

	if(no == 0)
	{
		SeStop();

		return;
	}

	if(Nv.isSkip == true)
	{
		return;
	}

	SePlayFmx(no);

	Nv.isLoop = false;
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
// �G���f�B���O�I����
EWRAM_CODE void NvExecParseMeu(void)
{
	TxtSetCur(false);

	MenuSetEnding1(MENU_RET_NONE);
	ManageSetMenu();

	Nv.isSkip = false;
	Nv.isLoop = false;
}
//---------------------------------------------------------------------------
// �X�N���v�g�W�����v
EWRAM_CODE void NvExecParseLds(void)
{
	s32 chap = NvNextCurNum();
	s32 no   = NvNextCurNum();

	NvSetTxt(chap, no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecParseMap(void)
{
	s32 map = NvNextCurNum();
	s32 vis = NvNextCurNum();		// ���̂�\���A��\����
//	TRACE("%d %d\n", map, is);

	ImgSetMap(map, vis);
	ImgSetEff(IMG_EFFECT_MAP_IN);

	Nv.isMap = true;
	Nv.isLoop = false;
	Nv.act = NV_ACT_KEY;
}
//---------------------------------------------------------------------------
// ��҂փ��b�Z�[�W or �G���f�B���O
EWRAM_CODE void NvExecParseEnd(void)
{
	AnimeSetDat(ANIME_DAT_ENDING);

	Nv.isSkip = false;
	Nv.isLoop = false;
}
