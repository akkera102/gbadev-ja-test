#include "sakura.h"
#include "libmy/spr.h"

// 例外処理：メモリバッファを用意せずOAMへ直接書き込みます。チラつきに注意。

//---------------------------------------------------------------------------
ST_SAKURA Sakura;


//---------------------------------------------------------------------------
EWRAM_CODE void SakuraInit(void)
{
	_Memset(&Sakura, 0x00, sizeof(ST_SAKURA));
}
//---------------------------------------------------------------------------
IWRAM_CODE void SakuraExec(void)
{
	s32 i;

	for(i=0; i<SAKURA_MAX_DAT; i++)
	{
		ST_SAKURA_DAT* p = &Sakura.dat[i];

		p->x += p->mx;
		p->y += p->my;

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

		if(p->type == 0)
		{
			SprDirectSetSize(i, OBJ_SIZE(Sprite_8x8), OBJ_SQUARE, OBJ_16_COLOR);
			SprDirectSetChr (i, 32 + p->pat);
			SprDirectMove   (i, FIX2INT(p->x), FIX2INT(p->y));
		}
		else
		{
			SprDirectSetSize(i, OBJ_SIZE(Sprite_16x16), OBJ_SQUARE, OBJ_16_COLOR);
			SprDirectSetChr (i, p->pat * 4);
			SprDirectMove   (i, FIX2INT(p->x), FIX2INT(p->y));
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void SakuraStop(void)
{
	s32 i;

	for(i=0; i<SAKURA_MAX_DAT; i++)
	{
		SprDirectMove(i, SCREEN_CX, SCREEN_CY);
	}

	Sakura.isEffect = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SakuraStart(bool isScn)
{
	s32 i;

	for(i=0; i<SAKURA_MAX_DAT; i++)
	{
		SakuraRegDat(i);

		// 画面上から桜を表示させる場合
		if(isScn == true)
		{
			Sakura.dat[i].x = INT2FIX(SakuraRnd(SCREEN_CX + 240));
			Sakura.dat[i].y = INT2FIX(SakuraRnd(SCREEN_CY + 160));
		}
	}

	Sakura.isEffect = true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SakuraRegDat(u32 no)
{
	Sakura.dat[no].type = SakuraRnd(3);
	Sakura.dat[no].wait = 0;
	Sakura.dat[no].pat  = SakuraRnd(8);
	Sakura.dat[no].x    = INT2FIX((SakuraRnd(120) - 180));
	Sakura.dat[no].y    = INT2FIX((SakuraRnd(160) *  -1));
	Sakura.dat[no].mx   = SakuraRnd(128) + 32;
	Sakura.dat[no].my   = SakuraRnd(96)  + 16;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SakuraSeed(u32 rnd)
{
	tinymt32_init(&Sakura.mt, rnd);
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
