#include "sav.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void SavInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 SavSramRead(u32 adr)
{
	u8* p = (u8*)SRAM + adr;

	return *p;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SavSramWrite(u32 adr, u8 dat)
{
	u8* p = (u8*)SRAM + adr;

	*p = dat;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 SavFlashRead(u32 adr)
{
	return SavSramRead(adr);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SavFlashWrite(u32 adr, u8 dat)
{
	// Byte-Program
	SavFlashCmd(0x5555, 0xAA);
	SavFlashCmd(0x2AAA, 0x55);
	SavFlashCmd(0x5555, 0xA0);


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
EWRAM_CODE void SavFlashCmd(u32 adr, u8 dat)
{
	u8* p = (u8*)SRAM + adr;

	*p = dat;
	__asm("NOP");
}
//---------------------------------------------------------------------------
EWRAM_CODE void SavFlashEraseSector(u32 sec)
{
	// Sector-Erase
	SavFlashCmd(0x5555, 0xAA);
	SavFlashCmd(0x2AAA, 0x55);
	SavFlashCmd(0x5555, 0x80);
	SavFlashCmd(0x5555, 0xAA);
	SavFlashCmd(0x2AAA, 0x55);
	SavFlashCmd(sec * 0x1000, 0x30);

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
	u8 t1 = SavSramRead(0x7FFF);
	u8 t2 = ~t1;

	// eraseÏ‚Ý‚ðl—¶‚µ‚Ä‚Q‰ñ‘‚«ž‚Ý‚Ü‚·
	SavSramWrite(0x7FFF, t2);
	SavSramWrite(0x7FFF, t2+1);

	if(SavSramRead(0x7FFF) == t2+1)
	{
		SavSramWrite(0x7FFF, t1);

		return FALSE;
	}

	return TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* SavGetPointer(u32 adr)
{
	return (u8*)SRAM + adr;
}
