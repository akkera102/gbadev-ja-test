#include "bak.h"

//---------------------------------------------------------------------------
ST_BAK Bak;


//---------------------------------------------------------------------------
EWRAM_CODE void BakInit(void)
{
	_Memset(&Bak, 0x00, sizeof(ST_BAK));
}
//---------------------------------------------------------------------------
EWRAM_CODE void BakSeek(u32 adr)
{
	Bak.p = (u8*)SRAM + adr;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 BakRead(void)
{
	return *Bak.p++;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 BakRead2(u32 adr)
{
	BakSeek(adr);
	return BakRead();
}
//---------------------------------------------------------------------------
EWRAM_CODE void BakWrite(u8 dat)
{
	if(Bak.id == 0)
	{
		*Bak.p++ = dat;
		__asm("NOP");

		return;
	}

	// Byte-Program
	BakWriteCmd(0x5555, 0xAA);
	BakWriteCmd(0x2AAA, 0x55);
	BakWriteCmd(0x5555, 0xA0);

	*Bak.p++ = dat;
	__asm("NOP");

	BakWait20us();
}
//---------------------------------------------------------------------------
EWRAM_CODE void BakWrite2(u32 adr, u8 dat)
{
	BakSeek(adr);
	BakWrite(dat);
}
//---------------------------------------------------------------------------
// FlashêÍóp
EWRAM_CODE void BakWriteCmd(u32 adr, u8 cmd)
{
	u8* p = (u8*)SRAM + adr;

	*p = cmd;

	__asm("NOP");
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* BakGetPointer(void)
{
	return Bak.p;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 BakGetId(void)
{
	// ID Entry
	BakWriteCmd(0x5555, 0xAA);
	BakWriteCmd(0x2AAA, 0x55);
	BakWriteCmd(0x5555, 0x90);

	// Read ID
//	u8 id0 = BakRead2(0x0000);
	u8 id1 = BakRead2(0x0001);

	// ID Exit
	BakWriteCmd(0x5555, 0xAA);
	BakWriteCmd(0x2AAA, 0x55);
	BakWriteCmd(0x5555, 0xF0);

	// Microchip
	// SST39VF010 : 0xBFD5
	// SST39VF020 : 0xBFD6
	// SST39VF040 : 0xBFD7

//	Bak.id = (id0 << 8) | id1;
	Bak.id = id1;
	TRACEOUT("[BakGetId %x]\n", Bak.id);

	return Bak.id;
}
//---------------------------------------------------------------------------
EWRAM_CODE void BakSetId(u8 id)
{
	Bak.id = id;
}
//---------------------------------------------------------------------------
EWRAM_CODE void BakEraseAll(void)
{
	if(Bak.id == 0)
	{
		BakSeek(0);
		s32 i;

		for(i=0; i<0x10000; i++)
		{
			BakWrite(0xFF);
		}

		return;
	}

	// Chip-Erase
	BakWriteCmd(0x5555, 0xAA);
	BakWriteCmd(0x2AAA, 0x55);
	BakWriteCmd(0x5555, 0x80);
	BakWriteCmd(0x5555, 0xAA);
	BakWriteCmd(0x2AAA, 0x55);
	BakWriteCmd(0x5555, 0x10);

	BakWait100ms();
}
//---------------------------------------------------------------------------
EWRAM_CODE void BakEraseSector(u32 sec)
{
	if(Bak.id == 0)
	{
		return;
	}

	// Sector-Erase
	BakWriteCmd(0x5555, 0xAA);
	BakWriteCmd(0x2AAA, 0x55);
	BakWriteCmd(0x5555, 0x80);
	BakWriteCmd(0x5555, 0xAA);
	BakWriteCmd(0x2AAA, 0x55);
	BakWriteCmd(sec * 0x1000, 0x30);

	BakWait25ms();
}
//---------------------------------------------------------------------------
EWRAM_CODE void BakWait20us(void)
{
	for(vu32 i=0; i<400; i++)
	{
		// 1èT ëÂéGîcÇ…0.0625usÅi1clk = 16MhzÅj
		__asm("NOP");
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void BakWait25ms(void)
{
	for(vu32 i=0; i<3; i++)
	{
		// 1èT 16.743ms
		while(REG_VCOUNT >= 160) {};
		while(REG_VCOUNT <  160) {};
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void BakWait100ms(void)
{
	for(vu32 i=0; i<10; i++)
	{
		// 1èT 16.743ms
		while(REG_VCOUNT >= 160) {};
		while(REG_VCOUNT <  160) {};
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool BakIsFlash(void)
{
	u8 t1 = BakRead2(0x7FFF);
	u8 t2 = ~t1;

	BakWrite2(0x7FFF, t2);
	BakWrite2(0x7FFF, t2+1);

	if(BakRead2(0x7FFF) == t2+1)
	{
		BakWrite2(0x7FFF, t1);

		return FALSE;
	}

	return TRUE;
}
