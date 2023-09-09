#include "sav.h"

// SRAM‚ÆFlash‚É‘Î‰ž

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void SavInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 SavReadSram(u32 adr)
{
	u8* p = (u8*)SRAM + adr;

	u8 ret = *p;

	return ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 SavReadFlash(u32 adr)
{
	return SavReadSram(adr);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SavWriteSram(u32 adr, u8 dat)
{
	u8* p = (u8*)SRAM + adr;

	*p = dat;

	__asm("NOP");
}
//---------------------------------------------------------------------------
EWRAM_CODE void SavWriteFlash(u32 adr, u8 dat)
{
	// Byte-Program
	SavWriteFlashCmd(0x5555, 0xAA);
	SavWriteFlashCmd(0x2AAA, 0x55);
	SavWriteFlashCmd(0x5555, 0xA0);


	u8* p = (u8*)SRAM + adr;
	*p = dat;

	// wait 25us
	for(vu32 i=0; i<400; i++)
	{
		// 25us = 0.0625us * 400(1clk = 16Mhz)
		__asm("NOP");
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SavWriteFlashCmd(u32 adr, u8 dat)
{
	u8* p = (u8*)SRAM + adr;

	*p = dat;

	__asm("NOP");
}
//---------------------------------------------------------------------------
EWRAM_CODE void SavWriteFlashEraseSector(u32 sector)
{
	// Sector-Erase
	SavWriteFlashCmd(0x5555, 0xAA);
	SavWriteFlashCmd(0x2AAA, 0x55);
	SavWriteFlashCmd(0x5555, 0x80);
	SavWriteFlashCmd(0x5555, 0xAA);
	SavWriteFlashCmd(0x2AAA, 0x55);
	SavWriteFlashCmd(sector * 0x1000, 0x30);

	// wait 25ms
	for(vu32 i=0; i<3; i++)
	{
		// 1T 16.743ms
		while(REG_VCOUNT >= 160) {};
		while(REG_VCOUNT <  160) {};
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SavIsFlash(void)
{
	u8 t1 = SavReadSram(0x7FFF);
	u8 t2 = ~t1;

	SavWriteSram(0x7FFF, t2);

	if(SavReadSram(0x7FFF) != t2)
	{
		SavWriteSram(0x7FFF, t1);

		return true;
	}

	return false;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* SavGetPointer(u32 adr)
{
	return (u8*)SRAM + adr;
}
