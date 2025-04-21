#include "vgm.arm.h"


//---------------------------------------------------------------------------
// Vcount Interrupt Table
s32 VgmVmap[6] = 
{
	0,
	38,
	76,
	114,
	152,
	190,
};


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
	Vgm.pCur   = pFile;
	Vgm.pFile  = pFile;
	Vgm.isLoop = isLoop;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
	Vgm.id = VGM_ID_STOP;

	// REG_SOUNDCNT
	*(vu8*)(REG_BASE + 0x84) = 0x00;

	// ch1
	*(vu8*)(REG_BASE + 0x60) = 0x00;
	*(vu8*)(REG_BASE + 0x62) = 0x00;
	*(vu8*)(REG_BASE + 0x63) = 0x08;
	*(vu8*)(REG_BASE + 0x64) = 0x00;
	*(vu8*)(REG_BASE + 0x65) = 0x80;

	// ch2
	*(vu8*)(REG_BASE + 0x68) = 0x00;
	*(vu8*)(REG_BASE + 0x69) = 0x08;
	*(vu8*)(REG_BASE + 0x6c) = 0x00;
	*(vu8*)(REG_BASE + 0x6d) = 0x80;

	// ch3
	for(u32 i=0; i<0x10; i++)
	{
		*(vu8*)(REG_BASE + 0x90 + i) = 0x00;
	}
	*(vu8*)(REG_BASE + 0x70) = 0x00;
	*(vu8*)(REG_BASE + 0x72) = 0x00;
	*(vu8*)(REG_BASE + 0x73) = 0x00;
	*(vu8*)(REG_BASE + 0x74) = 0x00;
	*(vu8*)(REG_BASE + 0x75) = 0x00;

	// ch4
	*(vu8*)(REG_BASE + 0x78) = 0x00;
	*(vu8*)(REG_BASE + 0x79) = 0x08;
	*(vu8*)(REG_BASE + 0x7c) = 0x00;
	*(vu8*)(REG_BASE + 0x7d) = 0x80;

	// REG_SOUNDCNT
	*(vu8*)(REG_BASE + 0x80) = 0x77;
	*(vu8*)(REG_BASE + 0x81) = 0xff;
	*(vu8*)(REG_BASE + 0x84) = 0x80;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmIntrVCount(void)
{
	if(Vgm.id == VGM_ID_STOP)
	{
		goto End;
	}

	for(;;)
	{
		u8 cmd = *Vgm.pCur++;

		if(cmd == VGM_CMD_WAIT)
		{
			goto End;
		}

		if(cmd == VGM_CMD_WREG)
		{
			u8 adr = *Vgm.pCur++;
			u8 dat = *Vgm.pCur++;
			*(vu8*)(REG_BASE + adr) = dat;

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

				goto End;
			}

			Vgm.pCur = Vgm.pFile;
			Vgm.loopCnt++;

			continue;
		}

		SystemError("VgmIntrVblank adr=%x", Vgm.pCur - Vgm.pFile);
	}

End:

	Vgm.vCnt++;

	if(Vgm.vCnt >= 6)
	{
		Vgm.vCnt = 0;
	}

	REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(VgmVmap[Vgm.vCnt]);
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetOffsetPlay(void)
{
	return (u32)(Vgm.pCur - Vgm.pFile);
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
