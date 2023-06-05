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
	VgmInit();
	VgmStop();

	Vgm.id     = VGM_ID_PLAY;
	Vgm.pBuf   = pFile;
	Vgm.pFile  = pFile;
	Vgm.isLoop = isLoop;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
	Vgm.id = VGM_ID_STOP;

	// REG_SOUNDCNT
	*(u8*)(REG_BASE + 0x84) = 0x00;

	// ch1
	*(u8*)(REG_BASE + 0x60) = 0x00;
	*(u8*)(REG_BASE + 0x62) = 0x00;
	*(u8*)(REG_BASE + 0x63) = 0x00;
	*(u8*)(REG_BASE + 0x64) = 0x00;
	*(u8*)(REG_BASE + 0x65) = 0x00;

	// ch2
	*(u8*)(REG_BASE + 0x68) = 0x00;
	*(u8*)(REG_BASE + 0x69) = 0x00;
	*(u8*)(REG_BASE + 0x6c) = 0x00;
	*(u8*)(REG_BASE + 0x6d) = 0x00;

	// ch3
	for(u32 i=0; i<0x10; i++)
	{
		*(u8*)(REG_BASE + 0x90 + i) = 0;
	}
	*(u8*)(REG_BASE + 0x70) = 0x00;
	*(u8*)(REG_BASE + 0x72) = 0x00;
	*(u8*)(REG_BASE + 0x74) = 0x80;

	// ch4
	*(u8*)(REG_BASE + 0x78) = 0x00;
	*(u8*)(REG_BASE + 0x79) = 0x00;
	*(u8*)(REG_BASE + 0x7c) = 0x00;
	*(u8*)(REG_BASE + 0x7d) = 0x00;

	// REG_SOUNDCNT
	*(u8*)(REG_BASE + 0x80) = 0x77;
	*(u8*)(REG_BASE + 0x81) = 0xff;
	*(u8*)(REG_BASE + 0x84) = 0x80;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmIntrVblank(void)
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
		return;
	}

	if(cmd == VGM_CMD_EOM)
	{
		if(Vgm.isLoop == TRUE)
		{
			u32 loop = *Vgm.pBuf++;
			loop    |= *Vgm.pBuf++ << 8;
			loop    |= *Vgm.pBuf++ << 16;
			loop    |= *Vgm.pBuf++ << 24;

			Vgm.pBuf = Vgm.pFile + loop;
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
EWRAM_CODE u32 VgmGetOffsetPlay(void)
{
	return (u32)(Vgm.pBuf - Vgm.pFile);
}
