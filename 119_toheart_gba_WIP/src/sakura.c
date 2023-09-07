#include "sakura.h"
#include "libmy/spr.h"
#include "libmy/irq.arm.h"

// 例外処理：メモリバッファを用意せずOAMへ直接書き込みます。チラつきに注意。
// 例外参照：irq.arm.c
extern u32 IrqVblankCnt;

//---------------------------------------------------------------------------
ST_SAKURA Sakura;


//---------------------------------------------------------------------------
EWRAM_CODE void SakuraInit(void)
{
	_Memset(&Sakura, 0x00, sizeof(ST_SAKURA));

	SakuraSeed(5489);
	SakuraStop();
}
//---------------------------------------------------------------------------
IWRAM_CODE void SakuraExec(void)
{
	s32 i;

	for(i=0; i<SAKURA_MAX_DAT; i++)
	{
		ST_SAKURA_DAT* p = &Sakura.dat[i];

		if(FIX2INT(p->x) >= SCREEN_CX || FIX2INT(p->y) >= SCREEN_CY)
		{
			SakuraRegDat(i);

			continue;
		}

		if(p->wait++ >= SAKURA_MAX_WAIT)
		{
			p->pat++;
			p->pat &= 0x7;

			p->wait = 0;
		}

		p->x += p->mx;
		p->y += p->my;


		if(p->type == 0)
		{
			SprDirectSetSize(i, OBJ_SIZE(Sprite_8x8), OBJ_SQUARE, 1);
			SprDirectSetChr (i, p->pat + 32);
			SprDirectMove   (i, FIX2INT(p->x), FIX2INT(p->y));
		}
		else
		{
			SprDirectSetSize(i, OBJ_SIZE(Sprite_16x16), OBJ_SQUARE, 1);
			SprDirectSetChr (i, p->pat * 4);
			SprDirectMove   (i, FIX2INT(p->x), FIX2INT(p->y));
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SakuraStart(bool isScn)
{
	s32 i;

	for(i=0; i<SAKURA_MAX_DAT; i++)
	{
		SakuraRegDat(i);

		// 画面上から桜を表示させる場合
		if(isScn == true)
		{
			Sakura.dat[i].x = INT2FIX(SakuraRnd(SCREEN_CX + SCREEN_CX));
			Sakura.dat[i].y = INT2FIX(SakuraRnd(SCREEN_CY + SCREEN_CY));
		}
	}

	Sakura.isEffect = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SakuraStop(void)
{
	s32 i;

	for(i=0; i<SAKURA_MAX_DAT; i++)
	{
		SprDirectMove(i, SCREEN_CX, SCREEN_CY);
	}

	Sakura.isEffect = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SakuraRegDat(u32 no)
{
	Sakura.dat[no].type = SakuraRnd(3);
	Sakura.dat[no].wait = 0;
	Sakura.dat[no].pat  = SakuraRnd(8);
	Sakura.dat[no].x    = INT2FIX((SakuraRnd(120) - 180));
	Sakura.dat[no].y    = INT2FIX((SakuraRnd(160) *  -1));
	Sakura.dat[no].mx   = SakuraRnd(160) + 32;
	Sakura.dat[no].my   = SakuraRnd(96)  + 16;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SakuraSeed(u32 rnd)
{
	tinymt32_init(&Sakura.mt, rnd + IrqVblankCnt);
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 SakuraRnd(s32 num)
{
	return DivMod(tinymt32_generate_uint32(&Sakura.mt) & 0x7FFFFFFF , num);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SakuraIsEffect(void)
{
	return Sakura.isEffect;
}
