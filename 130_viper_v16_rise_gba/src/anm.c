#include "anm.h"
#include "libmy/mode4.arm.h"
#include "file.h"
#include "res.h"

//---------------------------------------------------------------------------
ST_ANM Anm;


//---------------------------------------------------------------------------
EWRAM_CODE void AnmInit(void)
{
	_Memset(&Anm, 0x00, sizeof(ST_ANM));
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmExec(void)
{
	if(Anm.c.isWork == true)
	{
		AnmExecCol();
	}

//	Anm.isDraw0 = AnmIsDraw(0);

	s32 i;

	for(i=0; i<ANM_BUF_MAX_CNT; i++)
	{
		if(Anm.b[i].isWork == true)
		{
			AnmExecBuf(i);
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmExecCol(void)
{
	if(Anm.c.waitCnt != 0)
	{
		Anm.c.waitCnt--;

		return;
	}

	Anm.c.waitCnt = Anm.c.wait;

	TRACE("[AnmExecCol %d]\n", Anm.c.cnt);

	s32 i;

	for(i=0; i<Anm.c.max; i++)
	{
		u32 n = Anm.c.d[i].i;
		u32 r = Anm.c.d[i].r;
		u32 g = Anm.c.d[i].g;
		u32 b = Anm.c.d[i].b;

		r = tbl_effpal_bin[r * 32 + Anm.c.cnt];
		g = tbl_effpal_bin[g * 32 + Anm.c.cnt];
		b = tbl_effpal_bin[b * 32 + Anm.c.cnt];

		Mode4SetCol(n, r, g, b);
	}

	Anm.c.cnt++;

	if(Anm.c.cnt >= 32)
	{
		Anm.c.isWork = false;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmExecScr(s32 no)
{
	ST_ANM_SCR* s = (ST_ANM_SCR*)&Anm.s[no];

	switch(s->type)
	{
	case ANM_TYPE_SCR_SX:
		// EMPTY

		TRACE("[AnmExecScr SX no:%d sx:%d]\n", no, s->st);
		goto End;

	case ANM_TYPE_SCR_SY:
		// EMPTY

		TRACE("[AnmExecScr SY no:%d sy:%d]\n", no, s->st);
		goto End;

	case ANM_TYPE_SCR_UD:
		s->st += s->mv;

		if(s->st >= s->en)
		{
			s->st = s->en;

			goto End;
		}

		TRACE("[AnmExecScr UD no:%d st:%d mv:%d]\n", no, s->st, s->mv);
		break;

	case ANM_TYPE_SCR_DU:
		s->st -= s->mv;

		if(s->st <= 0)
		{
			s->st = 0;

			goto End;
		}

		TRACE("[AnmExecScr DU no:%d st:%d mv:%d]\n", no, s->st, s->mv);
		break;

	case ANM_TYPE_SCR_LR:
		s->st += s->mv;

		if(s->st >= s->en)
		{
			s->st = s->en;

			goto End;
		}

		TRACE("[AnmExecScr LR no:%d st:%d mv:%d]\n", no, s->st, s->mv);
		break;

	case ANM_TYPE_SCR_RL:
		s->st -= s->mv;

		if(s->st <= 0)
		{
			s->st = 0;

			goto End;
		}

		TRACE("[AnmExecScr RL no:%d st:%d mv:%d]\n", no, s->st, s->mv);
		break;

	case ANM_TYPE_SCR_UP:
		s->st -= s->mv;

		if(s->st <= 0)
		{
			s->st = 0;
		}

		TRACE("[AnmExecScr UP no:%d]\n", no);
		goto End;

	case ANM_TYPE_SCR_DOWN:
		s->st += s->mv;

		if(s->st >= Anm.b[0].d[0].cy - 160)
		{
			s->st = Anm.b[0].d[0].cy - 160;
		}

		TRACE("[AnmExecScr DO no:%d]\n", no);
		goto End;

	default:
		SystemError("[Err] AnmExecScr %x\n", Anm.s[no].type);
		break;
	}

	return;

End:

	s->isWork = false;
	s->isComp = true;

	TRACE("[AnmExecScr END no:%d st:%d mv:%d en:%d]\n", no, s->st, s->mv, s->en);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmExecBuf(s32 no)
{
	ST_ANM_BUF* b = (ST_ANM_BUF*)&Anm.b[no];
	ST_ANM_SCR* s = (ST_ANM_SCR*)&Anm.s[no];
	ST_ANM_BUF_DAT* d = (ST_ANM_BUF_DAT*)&Anm.b[no].d[b->cnt];

	b->wait--;

	if(b->wait != 0)
	{
		return;
	}

	if(b->cnt >= b->max)
	{
		b->isComp = true;
	}
	else
	{
		b->isComp = false;
	}

	if(b->isComp == true)
	{
		b->isWork = b->isLoop;
		b->cnt    = 0;
		b->wait   = 1;

		return;
	}


	TRACE("no:%02d cnt:%02d max:%02d --- f:%03d w:%03d sx%03d sy%03d cy:%03d\n", no, b->cnt, b->max, d->f, d->w, d->sx, d->sy, d->cy);

	b->wait = d->w;
	b->cnt++;

	if(s->isWork == true)
	{
		AnmExecScr(no);
	}


	if(d->p == NULL)
	{
		TRACE("NULL\n");
	}
	else if(d->cx == 240 && d->cy == 160)
	{
		Mode4DrawScreen(d->p);
		Mode4SetFlip();
	}
	else if(d->cx > 240)
	{
		Mode4DrawScrollX(s->st, d->p);
	}
	else if(d->cy > 160)
	{
		Mode4DrawScrollY(s->st, d->p);
	}
	else
	{
		Mode4DrawParts(d->sx, d->sy, d->cx, d->cy, d->p);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetDat(char* pStr)
{
	u16* p = FileGetDat(pStr);

	Anm.pStr = pStr;
	Anm.pPal = p + 8;
	Anm.pDat = p + 8 + 256;
	Anm.dMax = *p;

	TRACE("[AnmSetDat %s]\n", pStr);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetBuf1(s32 bNo, bool isLoop, s32 max)
{
	ST_ANM_BUF* b = (ST_ANM_BUF*)&Anm.b[bNo];

	b->isWork = true;
	b->isComp = false;
	b->isLoop = isLoop;
	b->max    = max;
	b->cnt    = 0;
	b->wait   = 1;

	TRACE("[AnmSetBuf1 bNo:%d loop:%02d max:%02d]\n", bNo, isLoop, max);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetBuf2(s32 bNo, s32 dNo, s32 frame, s32 wait)
{
	ST_ANM_BUF_DAT* d = (ST_ANM_BUF_DAT*)&Anm.b[bNo].d[dNo];

	u16* p = Anm.pDat + (frame - 1) * 4;

	d->f  = frame;
	d->w  = wait;
	d->sx = p[0];
	d->sy = p[1];
	d->cx = p[2];
	d->cy = p[3];
	d->p  = FileGetImg(Anm.pStr, frame);

	TRACE("[AnmSetBuf2 bNo:%d dNo:%03d frame:%02d wait:%02d cx:%03d cy:%03d]\n", bNo, dNo, frame, wait, d->cx, d->cy);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetScr1(s32 no, s32 type, s32 st, s32 en, s32 mv)
{
	ST_ANM_SCR* s = (ST_ANM_SCR*)&Anm.s[no];

	s->isWork = true;
	s->isComp = false;
	s->type   = type;
	s->st     = st;
	s->en     = en;
	s->mv     = mv;

	TRACE("[AnmSetScr1 no:%d type:%d inst:%d en:%d mv:%d]\n", no, type, st, en, mv);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetScr2(s32 no, s32 type, s32 mv)
{
	ST_ANM_BUF* b = (ST_ANM_BUF*)&Anm.b[no];
	ST_ANM_SCR* s = (ST_ANM_SCR*)&Anm.s[no];

	b->isWork = true;
	b->isComp = false;

	s->isWork = true;
	s->isComp = false;
	s->type   = type;
	s->mv     = mv;

	TRACE("[AnmSetScr2 no:%d type:%d mv:%d]\n", no, type, mv);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetScr3(s32 st)
{
	Anm.s[0].st = st;

	TRACE("[AnmSetScr3 st:%d\n", st);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetPal(void)
{
	Mode4SetPal(Anm.pPal);

	TRACE("[AnmSetPal]\n");
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetCol1(s32 wait, s32 max)
{
	Anm.c.isWork  = true;
	Anm.c.max     = max;
	Anm.c.cnt     = 0;
	Anm.c.wait    = wait;
	Anm.c.waitCnt = 0;

	TRACE("[AnmSetCol1 %d %d]\n", wait, max);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetCol2(s32 no, s32 i, s32 r, s32 g, s32 b)
{
	Anm.c.d[no].i = i;
	Anm.c.d[no].r = r;
	Anm.c.d[no].g = g;
	Anm.c.d[no].b = b;

	TRACE("[AnmSetCol2 %d %d %d %d]\n", i, r, g, b);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetCol3(s32 i, s32 r, s32 g, s32 b)
{
	Mode4SetCol(i, r, g, b);

	TRACE("[AnmSetCol3 %d %d %d %d]\n", i, r, g, b);
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetBufWork(s32 no, bool is)
{
	Anm.b[no].isWork = false;
	Anm.b[no].isComp = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetScrWork(s32 no, bool is)
{
	Anm.s[no].isWork = false;
	Anm.s[no].isComp = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void AnmSetPause(bool is)
{
	Anm.isPause = is;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool AnmIsBufComp(s32 no)
{
	return Anm.b[no].isComp;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool AnmIsScrComp(s32 no)
{
	return Anm.s[no].isComp;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool AnmIsDraw(s32 no)
{
	return (Anm.b[no].isWork == true && Anm.b[no].wait == 1) ? true : false;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool AnmIsPause(void)
{
	return Anm.isPause;
}
