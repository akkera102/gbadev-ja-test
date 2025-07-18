#include "nv.h"
#include "nv2.h"
#include "nv3.h"


//---------------------------------------------------------------------------
extern ST_NV Nv;


//---------------------------------------------------------------------------
void NvExprPush(bool is)
{
	_ASSERT(Nv.expr.cnt+1 < NV_MAX_EXPR_CNT);

	Nv.expr.isUse[Nv.expr.cnt++] = is;
}
//---------------------------------------------------------------------------
void NvExprPop(void)
{
	_ASSERT(Nv.expr.cnt != 0);

	Nv.expr.cnt--;
}
//---------------------------------------------------------------------------
void NvExprFlip(void)
{
	_ASSERT(Nv.expr.cnt != 0);

	Nv.expr.isUse[Nv.expr.cnt - 1] ^= 1;
}
//---------------------------------------------------------------------------
bool NvIsExpr(void)
{
	if(Nv.expr.cnt == 0)
	{
		return true;
	}

	s32 i;

	for(i=0; i<Nv.expr.cnt; i++)
	{
		if(Nv.expr.isUse[i] == false)
		{
			return false;
		}
	}

	return true;
}
