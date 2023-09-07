#include "rein.h"
#include "libmy/spr.h"
#include "libmy/irq.arm.h"

// 例外処理：メモリバッファを用意せずOAMへ直接書き込みます。チラつきに注意。
// 例外参照：irq.arm.c
extern u32 IrqVblankCnt;

//---------------------------------------------------------------------------
ST_REIN Rein;


//---------------------------------------------------------------------------
EWRAM_CODE void ReinInit(void)
{
	_Memset(&Rein, 0x00, sizeof(ST_REIN));

	ReinSeed(5489);
	ReinStop();
}
//---------------------------------------------------------------------------
IWRAM_CODE void ReinExec(void)
{
	s32 i;

	for(i=0; i<REIN_MAX_DAT; i++)
	{
		ST_REIN_DAT* p = &Rein.dat[i];

		if(p->wait < 5)
		{
			p->wait++;

			continue;
		}
		p->wait = 0;

		if(p->x >= SCREEN_CX || p->y >= SCREEN_CY)
		{
			ReinRegDat(i);

			continue;
		}

		p->x +=  8;
		p->y += 16;

		SprDirectMove(i, p->x, p->y);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void ReinStart(void)
{
	s32 i;

	for(i=0; i<REIN_MAX_DAT; i++)
	{
		ReinRegDat(i);

		SprDirectSetSize(i, OBJ_SIZE(Sprite_8x16), OBJ_TALL, 2);
		SprDirectSetChr (i, 40);
	}

	Rein.isEffect = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ReinStop(void)
{
	s32 i;

	for(i=0; i<REIN_MAX_DAT; i++)
	{
		SprDirectMove(i, SCREEN_CX, SCREEN_CY);
	}

	Rein.isEffect = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void ReinRegDat(u32 no)
{
	Rein.dat[no].wait = 0;
	Rein.dat[no].x = ReinRnd(240) - 80;
	Rein.dat[no].y = ReinRnd(120) *  -1;
}
//---------------------------------------------------------------------------
EWRAM_CODE void ReinSeed(u32 rnd)
{
	tinymt32_init(&Rein.mt, rnd + IrqVblankCnt);
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 ReinRnd(s32 num)
{
	return DivMod(tinymt32_generate_uint32(&Rein.mt) & 0x7FFFFFFF , num);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool ReinIsEffect(void)
{
	return Rein.isEffect;
}
