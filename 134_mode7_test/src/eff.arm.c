#include "eff.arm.h"
#include "math.h"

//---------------------------------------------------------------------------
ST_EFF Eff;

//---------------------------------------------------------------------------
void EffInit(void)
{
	_Memset(&Eff, 0x00, sizeof(ST_EFF));

	EffInitCam();
}
//---------------------------------------------------------------------------
IWRAM_CODE void EffInitCam(void)
{
	Eff.cam.x = 128 << 8;
	Eff.cam.y =  80 << 8;
	Eff.cam.z = 128 << 8;
	Eff.rot   = 0;
	Eff.dis   = 280;
}
//---------------------------------------------------------------------------
IWRAM_CODE void EffAddCamZ(void)
{
	Eff.cam.z += (1 << 6);

	// 見えなくなった場合、初期値に戻します
	if((Eff.cam.z >> 6) > 2000)
	{
		EffInitCam();
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void EffIntrHblank(u32 y)
{
	s32 d_val = MathDiv(y);

	s32 lam   = (Eff.cam.y * d_val) >> 12;
	s32 lcf   = (lam * (MathCos(Eff.rot) >> 4)) >> 8;
	s32 lsf   = (lam * (MathSin(Eff.rot) >> 4)) >> 8;
	REG_BG2PA = (s16)(lcf >> 4);
	REG_BG2PC = (s16)(lsf >> 4);

	s32 lxr  = 120 * (lcf >> 4);
	s32 lyr  = (Eff.dis * lsf) >> 4;
	REG_BG2X = Eff.cam.x - lxr + lyr;

	s32 lxr2 = 120 * (lsf >> 4);
	s32 lyr2 = (Eff.dis * lcf) >> 4;
	REG_BG2Y = Eff.cam.z - lxr2 - lyr2;

	// 文字カラーフェード（暗く）
	if(y < 48)
	{
		REG_BLDY = 16;
	}
	else if(y < 80)
	{
		REG_BLDY = 16 - (u16)((y - 48) >> 1);
	}
	else
	{
		REG_BLDY = 0;
	}
}
