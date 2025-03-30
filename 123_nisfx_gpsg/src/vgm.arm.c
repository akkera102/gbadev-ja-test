#include "vgm.arm.h"

//---------------------------------------------------------------------------
ST_VGM Vgm;


//---------------------------------------------------------------------------
EWRAM_CODE void VgmInit(void)
{
	_Memset(&Vgm, 0x00, sizeof(ST_VGM));
	Vgm.regs[0x80 - 0x60] = 0x77;
	Vgm.regs[0x81 - 0x60] = 0xFF;
	Vgm.regs[0x84 - 0x60] = 0x80;
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmPlay(u8* pFile, char* pName, u32 bias)
{
	VgmInit();
	VgmStop();

	Vgm.id     = VGM_ID_PLAY;
	Vgm.pCur   = pFile;
	Vgm.pFile  = pFile;

	if('N' == pName[0] && 'I' == pName[1])
	{
		if('0' == pName[2] && '1' == pName[3])
		{
			Vgm.isLoop = true;
		}
	}

	if('R' == pName[0] && 'K' == pName[1])
	{
		if('S' == pName[5] && 'L' == pName[6]){
			Vgm.isLoop = true;
		}
		if('M' == pName[5] && 'L' == pName[6]){
			Vgm.isLoop = true;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetLoop(u32 loop)
{
	Vgm.isLoop = (loop == 0) ? false : true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
	Vgm.id = VGM_ID_STOP;

	// REG_SOUNDCNT
	*(u8*)(REG_BASE + 0x84) = 0x80; //常に0x80

	// ch1
	*(u8*)(REG_BASE + 0x60) = 0x00;
	*(u8*)(REG_BASE + 0x62) = 0x00;
	*(u8*)(REG_BASE + 0x63) = 0x08; // NR12
	*(u8*)(REG_BASE + 0x64) = 0x00;
	*(u8*)(REG_BASE + 0x65) = 0x80; // NR14

	// ch2
	*(u8*)(REG_BASE + 0x68) = 0x00;
	*(u8*)(REG_BASE + 0x69) = 0x08; // NR22
	*(u8*)(REG_BASE + 0x6c) = 0x00;
	*(u8*)(REG_BASE + 0x6d) = 0x80; // NR24

	// ch3
	for(u32 i=0; i<0x10; i++)
	{
		*(u8*)(REG_BASE + 0x90 + i) = 0x80;
	}
	*(u8*)(REG_BASE + 0x70) = 0x00;
	*(u8*)(REG_BASE + 0x72) = 0x00;
	*(u8*)(REG_BASE + 0x73) = 0x00;
	*(u8*)(REG_BASE + 0x74) = 0x00;
	*(u8*)(REG_BASE + 0x75) = 0x00;

	// ch4
	*(u8*)(REG_BASE + 0x78) = 0x00;
	*(u8*)(REG_BASE + 0x79) = 0x08; // NR42
	*(u8*)(REG_BASE + 0x7c) = 0x00;
	*(u8*)(REG_BASE + 0x7d) = 0x80; // NR44

	// REG_SOUNDCNT
	*(u8*)(REG_BASE + 0x80) = 0x77;
	*(u8*)(REG_BASE + 0x81) = 0xFF;
	// *(u8*)(REG_BASE + 0x84) = 0x80;

	// *(u8*)(REG_BASE + 0x82) = 0x02;
	// *(u8*)(REG_BASE + 0x88) = 0xC0;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmTick(void)
{
	if(Vgm.id == VGM_ID_STOP)
	{
		return;
	}

	for(;;)
	{
		u8 cmd = *Vgm.pCur++;

		if(cmd == VGM_CMD_WAIT)
		{
			return;
		}

		if(cmd == VGM_CMD_WREG)
		{
			u8 adr = *Vgm.pCur++;
			u8 dat = *Vgm.pCur++;
			*(u8*)(REG_BASE + adr) = dat;

			if(adr >= 0x60 && adr <= 0x88)
			{
				Vgm.regs[adr - 0x60] = dat;
			}
			if(adr >= 0x90 && adr <= 0x9f)
			{
				Vgm.wave[adr - 0x90] = dat;
			}

			continue;
		}

		if(cmd == VGM_CMD_EOM)
		{
			if(Vgm.isLoop == false)
			{
				VgmStop();

				return;
			}

			u32 loop;

			loop  = *Vgm.pCur++;
			loop |= *Vgm.pCur++ << 8;
			loop |= *Vgm.pCur++ << 16;
			loop |= *Vgm.pCur++ << 24;

			Vgm.pCur = Vgm.pFile + loop;
			Vgm.loopCnt++;

			continue;
		}

		SystemError("VgmTick adr=%x", Vgm.pCur - Vgm.pFile);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetOffsetPlay(void)
{
	return (u32)(Vgm.pCur - Vgm.pFile);
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetIsLoop(void)
{
	return Vgm.isLoop;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetLoopCnt(void)
{
	return Vgm.loopCnt;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetWave(u32 i)
{
	return Vgm.wave[i & 0xf];
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetRegs(u32 i)
{
	return Vgm.regs[i];
}