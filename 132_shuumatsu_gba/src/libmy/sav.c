#include "sav.h"

// SRAM��Flash�ɑΉ�

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void SavInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
u8 SavReadSram(u32 adr)
{
	u8* p = (u8*)SRAM + adr;

	u8 ret = *p;

	return ret;
}
//---------------------------------------------------------------------------
u8 SavReadFlash(u32 adr)
{
	return SavReadSram(adr);
}
//---------------------------------------------------------------------------
void SavWriteSram(u32 adr, u8 dat)
{
	u8* p = (u8*)SRAM + adr;

	*p = dat;

	__asm volatile("NOP");
}
//---------------------------------------------------------------------------
void SavWriteFlash(u32 adr, u8 dat)
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
		__asm volatile("NOP");
	}
}
//---------------------------------------------------------------------------
void SavWriteFlashCmd(u32 adr, u8 dat)
{
	u8* p = (u8*)SRAM + adr;

	*p = dat;

	__asm volatile("NOP");
}
//---------------------------------------------------------------------------
void SavWriteFlashEraseSector(s32 sector)
{
	// Sector-Erase
	SavWriteFlashCmd(0x5555, 0xAA);
	SavWriteFlashCmd(0x2AAA, 0x55);
	SavWriteFlashCmd(0x5555, 0x80);
	SavWriteFlashCmd(0x5555, 0xAA);
	SavWriteFlashCmd(0x2AAA, 0x55);
	SavWriteFlashCmd(sector * 0x1000, 0x30);

	// wait 25ms ��G�c��
	for(vu32 i=0; i<3; i++)
	{
		// 1�T 16.743ms
		while(REG_VCOUNT >= 160) {};
		while(REG_VCOUNT <  160) {};
	}
}
//---------------------------------------------------------------------------
bool SavIsFlash(void)
{
	u8 t1 = SavReadSram(0);
	u8 t2 = ~t1;

	SavWriteSram(0, t2);

	if(SavReadSram(0) == t2)
	{
		// SRAM
		SavWriteSram(0, t1);
		return false;
	}

	return true;
}
//---------------------------------------------------------------------------
u8* SavGetPointer(u32 adr)
{
	return (u8*)SRAM + adr;
}
