#include "sav.h"
#include "../res.h"

// SRAM‚Ì‚Ý‘Î‰ž

//---------------------------------------------------------------------------
ROM_DATA char SavId[] ALIGN(16) = "SRAM_Vnnn";


//---------------------------------------------------------------------------
u8* SavInit(void)
{
	// dummy
	return (u8*)SavId;
}
//---------------------------------------------------------------------------
u8 SavReadSram(u32 adr)
{
	vu8* p  = (vu8*)SRAM + adr;
	vu8 ret = *p;

	return ret;
}
//---------------------------------------------------------------------------
u16 SavReadSram16(u32 adr)
{
	u16 ret;

	ret  = SavReadSram(adr + 0);
	ret += SavReadSram(adr + 1) << 8;

	return ret;
}
//---------------------------------------------------------------------------
void SavWriteSram(u32 adr, u8 dat)
{
	vu8* p = (vu8*)SRAM + adr;

	*p = dat;
}
//---------------------------------------------------------------------------
void SavWriteSram16(u32 adr, u16 dat)
{
	SavWriteSram(adr + 0, (dat     ) & 0xff);
	SavWriteSram(adr + 1, (dat >> 8) & 0xff);
}
//---------------------------------------------------------------------------
u8* SavGetPointer(u32 adr)
{
	return (u8*)SRAM + adr;
}
