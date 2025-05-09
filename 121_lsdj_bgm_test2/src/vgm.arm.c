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

/*
	// REG_SOUNDCNT
	*(vu8*)(REG_BASE + 0x84) = 0x00;

	// ch1
	*(vu8*)(REG_BASE + 0x60) = 0x80;
	*(vu8*)(REG_BASE + 0x62) = 0xBF;
	*(vu8*)(REG_BASE + 0x63) = 0xF3;
	*(vu8*)(REG_BASE + 0x64) = 0xC1;
	*(vu8*)(REG_BASE + 0x65) = 0xBF;

	// ch2
	*(vu8*)(REG_BASE + 0x68) = 0x00;
	*(vu8*)(REG_BASE + 0x69) = 0x00;
	*(vu8*)(REG_BASE + 0x6c) = 0x00;
	*(vu8*)(REG_BASE + 0x6d) = 0xB8;

	// ch3
	*(vu8*)(REG_BASE + 0x70) = 0x7F;
	*(vu8*)(REG_BASE + 0x72) = 0x00;
	*(vu8*)(REG_BASE + 0x73) = 0x9F;
	*(vu8*)(REG_BASE + 0x74) = 0x00;
	*(vu8*)(REG_BASE + 0x75) = 0xB8;

	// wave
	*(vu8*)(REG_BASE + 0x90 + 0x0) = 0x96;
	*(vu8*)(REG_BASE + 0x90 + 0x1) = 0xF2;
	*(vu8*)(REG_BASE + 0x90 + 0x2) = 0xAA;
	*(vu8*)(REG_BASE + 0x90 + 0x3) = 0xA7;
	*(vu8*)(REG_BASE + 0x90 + 0x4) = 0x24;
	*(vu8*)(REG_BASE + 0x90 + 0x5) = 0x4C;
	*(vu8*)(REG_BASE + 0x90 + 0x6) = 0x8A;
	*(vu8*)(REG_BASE + 0x90 + 0x7) = 0xD5;
	*(vu8*)(REG_BASE + 0x90 + 0x8) = 0x11;
	*(vu8*)(REG_BASE + 0x90 + 0x9) = 0xF3;
	*(vu8*)(REG_BASE + 0x90 + 0xA) = 0xD0;
	*(vu8*)(REG_BASE + 0x90 + 0xB) = 0xC1;
	*(vu8*)(REG_BASE + 0x90 + 0xC) = 0x19;
	*(vu8*)(REG_BASE + 0x90 + 0xD) = 0xEA;
	*(vu8*)(REG_BASE + 0x90 + 0xE) = 0x18;
	*(vu8*)(REG_BASE + 0x90 + 0xF) = 0x6F;

	// ch4
	*(vu8*)(REG_BASE + 0x78) = 0xC0;
	*(vu8*)(REG_BASE + 0x79) = 0xC0;
	*(vu8*)(REG_BASE + 0x7c) = 0x00;
	*(vu8*)(REG_BASE + 0x7d) = 0xBF;

	// REG_SOUNDCNT
	*(vu8*)(REG_BASE + 0x80) = 0x77;
	*(vu8*)(REG_BASE + 0x81) = 0xF3;
//	*(vu8*)(REG_BASE + 0x84) = 0xF1;
*/
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
