#include "dme.arm.h"

//---------------------------------------------------------------------------
ST_DME Dme;


//---------------------------------------------------------------------------
EWRAM_CODE void DmeInit(void)
{
	_Memset(&Dme, 0x00, sizeof(ST_DME));
}
//---------------------------------------------------------------------------
EWRAM_CODE void DmePlay(u8* pFile, u32 time)
{
	DmeInit();

	Dme.id    = DME_ID_PLAY;
	Dme.bank  = 0;
	Dme.wait  = 1;
	Dme.pVgm  = pFile;
	Dme.pFile = pFile;

	REG_TM3CNT_L = 0x10000 - time;
	REG_TM3CNT_H = TIMER_FREQ_PER_64 | TIMER_IRQ | TIMER_START;
}
//---------------------------------------------------------------------------
IWRAM_CODE void DmeIntrTimer(void)
{
	if(Dme.id == DME_ID_STOP)
	{
		return;
	}

	if(Dme.wait != 0)
	{
		Dme.wait--;
		return;
	}

cmdChk:

	u8 cmd = *Dme.pVgm++;
//	TRACE("Adr=%x cmd=%x\n", Dme.pVgm - Dme.pFile - 1, cmd);

	// DME_CMD_1
	if((cmd & 0x80) == 0)
	{
		u8 dat = *Dme.pVgm++;
		DmeWriteReg(cmd, dat);

		goto cmdChk;
	}

	if(cmd == DME_CMD_2)
	{
		Dme.wait = *Dme.pVgm++;

		return;
	}

	if(cmd == DME_CMD_3)
	{
		Dme.bank++;
		Dme.pVgm = Dme.pFile + 0x3fff * Dme.bank;

		return;
	}

	if(cmd == DME_CMD_4)
	{
		u8 adr = *Dme.pVgm++;
		u8 dat = *Dme.pVgm++;
		DmeWriteReg(adr, dat);

		goto cmdChk;
	}

	if(cmd == DME_CMD_5)
	{
		Dme.pVgm = Dme.pFile;
		Dme.bank = 0;

		return;
	}

	if(cmd == DME_CMD_6)
	{
		DmeStop();

		return;
	}

	TRACE("ERR\n");
}
//---------------------------------------------------------------------------
IWRAM_CODE void DmeStop(void)
{
	REG_TM3CNT_H = 0;
	Dme.id = DME_ID_STOP;

	DmeWriteReg(0x60-0x50, 0);
	DmeWriteReg(0x63-0x50, 0);
	DmeWriteReg(0x69-0x50, 0);
	DmeWriteReg(0x7c-0x50, 0);
	DmeWriteReg(0x62-0x50, 0);
	DmeWriteReg(0x68-0x50, 0);
	DmeWriteReg(0x70-0x50, 0);
	DmeWriteReg(0x79-0x50, 0);

	DmeWriteReg(0x84-0x50, 0x8f);
	DmeWriteReg(0x81-0x50, 0xff);
	DmeWriteReg(0x80-0x50, 0x77);
	DmeWriteReg(0x73-0x50, 0x20);
	DmeWriteReg(0x79-0x50, 0xf7);
}
//---------------------------------------------------------------------------
IWRAM_CODE void DmeWriteReg(u8 adr, u8 byte)
{
	*(u8*)(REG_BASE + adr + 0x50) = byte;

	if(adr >= 0x40 && adr <= 0x4f)
	{
		REG_SOUND3CNT_L = 0x0040;
	}
}
