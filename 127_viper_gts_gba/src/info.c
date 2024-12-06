#include "info.h"

/*
	GTS0 1-6
	GTS1 7-25
	GTS2 26-39   132 136 137
	GTS3 40-72   144 155 172
	GTS4 73-105  175 176
*/


//---------------------------------------------------------------------------
ROM_DATA char InfoTbl[][4+1] = {
	"GTS0",
	"GTS1",
	"GTS2",
	"GTS3",
	"GTS4",
	"MAIN",
};

//---------------------------------------------------------------------------
EWRAM_CODE void InfoInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 InfoGetVarPrev(s32 var)
{
	if(var == 176)
	{
		var = 175;
	}
	else if(var == 175)
	{
		var = 105;
	}
	else if(var >= 74 && var <= 105)
	{
		var--;
	}
	else if(var == 73)
	{
		var = 172;
	}
	else if(var == 172)
	{
		var = 155;
	}
	else if(var == 155)
	{
		var = 144;
	}
	else if(var == 144)
	{
		var = 72;
	}
	else if(var >= 41 && var <= 72)
	{
		var--;
	}
	else if(var == 40)
	{
		var = 137;
	}
	else if(var == 137)
	{
		var = 136;
	}
	else if(var == 136)
	{
		var = 132;
	}
	else if(var == 132)
	{
		var = 39;
	}
	else if(var >= 2 && var <= 39)
	{
		var--;
	}

	return var;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 InfoGetVarPrev2(s32 var)
{
	if(var >= 1 && var <= 7)
	{
		var = 1;
	}
	else if(var >= 8 && var <= 26)
	{
		var = 7;
	}
	else if((var >= 27 && var <= 40) || var == 132 || var == 136 || var == 137)
	{
		var = 26;
	}
	else if((var >= 41 && var <= 73) || var == 144 || var == 155 || var == 172)
	{
		var = 40;
	}
	else if((var >= 74 && var <= 105) || var == 175 || var == 176)
	{
		var = 73;
	}

	return var;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 InfoGetVarNext(s32 var)
{
	if(var >= 1 && var <= 38)
	{
		var++;
	}
	else if(var == 39)
	{
		var = 132;
	}
	else if(var == 132)
	{
		var = 136;
	}
	else if(var == 136)
	{
		var = 137;
	}
	else if(var == 137)
	{
		var = 40;
	}
	else if(var >= 40 && var <= 71)
	{
		var++;
	}
	else if(var == 72)
	{
		var = 144;
	}
	else if(var == 144)
	{
		var = 155;
	}
	else if(var == 155)
	{
		var = 172;
	}
	else if(var == 172)
	{
		var = 73;
	}
	else if(var >= 73 && var <= 104)
	{
		var++;
	}
	else if(var == 105)
	{
		var = 175;
	}
	else if(var == 175)
	{
		var = 176;
	}

	return var;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 InfoGetVarNext2(s32 var)
{
	if(var >= 1 && var <= 6)
	{
		var = 7;
	}
	else if(var >= 7 && var <= 25)
	{
		var = 26;
	}
	else if((var >= 26 && var <= 39) || var == 132 || var == 136 || var == 137)
	{
		var = 40;
	}
	else if((var >= 40 && var <= 72) || var == 144 || var == 155 || var == 172)
	{
		var = 73;
	}
	else if((var >= 73 && var <= 105) || var == 175 || var == 176)
	{
		var = 176;
	}

	return var;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* InfoGetStr(s32 var)
{
	if(var ==  0)
	{
		return InfoTbl[5];
	}

	if(var >=   1 && var <=   6) return InfoTbl[0];
	if(var >=   7 && var <=  25) return InfoTbl[1];
	if(var >=  26 && var <=  39) return InfoTbl[2];
	if(var >=  40 && var <=  72) return InfoTbl[3];
	if(var >=  73 && var <= 105) return InfoTbl[4];

	switch(var)
	{
	case 132:
	case 136:
	case 137:
		return InfoTbl[2];

	case 144:
	case 155:
	case 172:
		return InfoTbl[3];

	case 175:
	case 176:
		return InfoTbl[4];
	}

	SystemError("[Err] InfoGetStr %x\n", var);
	return NULL;
}
