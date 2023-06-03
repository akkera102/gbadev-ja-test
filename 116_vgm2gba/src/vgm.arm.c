#include "vgm.arm.h"

//---------------------------------------------------------------------------
ST_VGM Vgm;


//---------------------------------------------------------------------------
EWRAM_CODE void VgmInit(void)
{
	_Memset(&Vgm, 0x00, sizeof(ST_VGM));
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmPlay(u8* pFile, bool isLoop)
{
	VgmStop();
	VgmInit();

	Vgm.id     = VGM_ID_PLAY;
	Vgm.pBuf   = pFile;
	Vgm.pFile  = pFile;
	Vgm.isLoop = isLoop;

	REG_TM3CNT_L = 0xffff;
	REG_TM2CNT_L = 0xffff;
	REG_TM3CNT_H = TIMER_CASCADE    | TIMER_START | TIMER_IRQ;
	REG_TM2CNT_H = TIMER_FREQ_PER_1 | TIMER_START;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmIntrTimer(void)
{
	if(Vgm.id == VGM_ID_STOP)
	{
		return;
	}

cmdChk:

	u8 cmd = *Vgm.pBuf++;

	if(cmd == VGM_CMD_WREG)
	{
		u8 adr = *Vgm.pBuf++;
		u8 dat = *Vgm.pBuf++;
		*(u8*)(REG_BASE + adr) = dat;

		goto cmdChk;
	}

	if(cmd == VGM_CMD_WAIT)
	{
		u16 tm3 = (u16)(*Vgm.pBuf++);
		tm3    |= (u16)(*Vgm.pBuf++) << 8;

		u16 tm2 = (u16)(*Vgm.pBuf++);
		tm2    |= (u16)(*Vgm.pBuf++) << 8;

		REG_TM3CNT_H = 0;
		REG_TM2CNT_H = 0;

		REG_TM3CNT_L = tm3;
		REG_TM2CNT_L = tm2;
		REG_TM3CNT_H = TIMER_CASCADE    | TIMER_START | TIMER_IRQ;
		REG_TM2CNT_H = TIMER_FREQ_PER_1 | TIMER_START;

		return;
	}

	if(cmd == VGM_CMD_EOM)
	{
		if(Vgm.isLoop == TRUE)
		{
			Vgm.pBuf = Vgm.pFile;
		}
		else
		{
			VgmStop();
		}

		return;
	}


	TRACE("ERR\n");
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
	REG_TM3CNT_H = 0;
	Vgm.id = VGM_ID_STOP;

	*(u8*)(REG_BASE + 0x60) = 0;
	*(u8*)(REG_BASE + 0x63) = 0;
	*(u8*)(REG_BASE + 0x69) = 0;
	*(u8*)(REG_BASE + 0x7c) = 0;
	*(u8*)(REG_BASE + 0x62) = 0;
	*(u8*)(REG_BASE + 0x68) = 0;
	*(u8*)(REG_BASE + 0x70) = 0;
	*(u8*)(REG_BASE + 0x79) = 0;

	*(u8*)(REG_BASE + 0x84) = 0x8f;
	*(u8*)(REG_BASE + 0x81) = 0xff;
	*(u8*)(REG_BASE + 0x80) = 0x77;
	*(u8*)(REG_BASE + 0x73) = 0x20;
	*(u8*)(REG_BASE + 0x79) = 0xf7;
}
