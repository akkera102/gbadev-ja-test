#include "vgm.arm.h"

//---------------------------------------------------------------------------
ST_VGM Vgm;
ST_VGM_PLAYER VgmPlayer;

//---------------------------------------------------------------------------
EWRAM_CODE void VgmPlayerInit(void)
{
	_Memset(&VgmPlayer, 0x00, sizeof(ST_VGM_PLAYER));
	VgmPlayer.isFade = true;

	// REG_SOUNDBIAS
	*(vu8*)(REG_BASE + 0x89) = 0xC1;
	*(vu8*)(REG_BASE + 0x88) = 0x80;
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmInit(void)
{
	_Memset(&Vgm, 0x00, sizeof(ST_VGM));
	Vgm.regs[0x80 - 0x60] = 0x77;
	Vgm.regs[0x81 - 0x60] = 0xFF;
	Vgm.regs[0x84 - 0x60] = 0x80;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
	VgmPlayer.stat = PLAYER_STAT_STOP;

	// REG_SOUNDCNT_L
	*(vu8*)(REG_BASE + 0x84) = 0x80; //常に0x80

	// ch1
	*(vu8*)(REG_BASE + 0x60) = 0x00;
	*(vu8*)(REG_BASE + 0x62) = 0x00;
	*(vu8*)(REG_BASE + 0x63) = 0x08; // NR12
	*(vu8*)(REG_BASE + 0x64) = 0x00;
	*(vu8*)(REG_BASE + 0x65) = 0x80; // NR14

	// ch2
	*(vu8*)(REG_BASE + 0x68) = 0x00;
	*(vu8*)(REG_BASE + 0x69) = 0x08; // NR22
	*(vu8*)(REG_BASE + 0x6c) = 0x00;
	*(vu8*)(REG_BASE + 0x6d) = 0x80; // NR24

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
	*(vu8*)(REG_BASE + 0x79) = 0x08; // NR42
	*(vu8*)(REG_BASE + 0x7c) = 0x00;
	*(vu8*)(REG_BASE + 0x7d) = 0x80; // NR44

	// REG_SOUNDCNT_L
	*(vu8*)(REG_BASE + 0x80) = 0x77;
	*(vu8*)(REG_BASE + 0x81) = 0xFF;

	// REG_SOUNDCNT_H
	VgmUpdSoundcntH(PLAYER_SOUNDCNT_H); // エミュの初期値が0x00で実機と異なるため必須

	// *(vu8*)(REG_BASE + 0x84) = 0x80;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmUpdSoundcntL(u8 dat)
{
	Vgm.regs[0x80 - 0x60] = dat;
	*(vu8*)(REG_BASE + 0x80) = dat;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmUpdSoundcntH(u8 dat)
{
	*(vu8*)(REG_BASE + 0x82) = ((*((u16 volatile *) (REG_BASE + 0x082))) & 0xFC) | dat;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmPatchHeadset(u8 adr, u8 dat)
{
	if(0x90 == adr && 0x04 == dat)
	{
		Vgm.wave[adr - 0x90] = 0x01;
	}
	else if(0x91 == adr && 0x92 == dat)
	{
		Vgm.wave[adr - 0x90] = 0x31;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmPlay(u8* pFile)
{
	VgmInit();
	VgmStop();

	Vgm.pCur   = pFile;
	Vgm.pFile  = pFile;
	Vgm.isLoop = true;

	VgmPlayer.stat    = PLAYER_STAT_PLAY;
	VgmPlayer.fadeCnt = 0;
	VgmPlayer.pNextFile = pFile;
	// VgmPlayer.isHeadset = false;
	// VgmPlayer.isFade = false;
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmReserve(u8* pNextFile)
{
	VgmPlayer.stat    = PLAYER_STAT_RESERVE;
	VgmPlayer.fadeCnt = PLAYER_FADE_CNT;
	VgmPlayer.pNextFile = pNextFile;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetLoop(u32 loop)
{
	Vgm.isLoop = (loop == 0) ? false : true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetFade(u32 fade)
{
	VgmPlayer.isFade = (fade == 0) ? false : true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetHeadset(u32 headset)
{
	VgmPlayer.isHeadset = (headset == 0) ? false : true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmTick(void)
{

	// STOP
	if(VgmPlayer.stat == PLAYER_STAT_STOP)
	{
		return;
	}

	// RESERVE
	if(VgmPlayer.stat == PLAYER_STAT_RESERVE)
	{
		VgmPlayer.fadeCnt--;

		switch(VgmPlayer.fadeCnt)
		{
			case 80:
				VgmUpdSoundcntL(0x77);
				break;
			case 70:
				VgmUpdSoundcntL(0x66);
				break;
			case 60:
				VgmUpdSoundcntL(0x55);
				break;
			case 50:
				VgmUpdSoundcntL(0x44);
				break;
			case 40:
				VgmUpdSoundcntL(0x77);
				VgmUpdSoundcntH(0x01);
				break;
			case 30:
				VgmUpdSoundcntL(0x66);
				break;
			case 20:
				VgmUpdSoundcntL(0x55);
				break;
			case 10:
				VgmUpdSoundcntL(0x44);
				break;
		}

		if(0 == VgmPlayer.fadeCnt)
		{
			VgmPlay(VgmPlayer.pNextFile);

			return;
		}
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

			// wave
			if(adr >= 0x90 && adr <= 0x9f)
			{
				Vgm.wave[adr - 0x90] = dat;
				if(VgmPlayer.isHeadset)
				{
					VgmPatchHeadset(adr, dat);
				}

				*(vu8*)(REG_BASE + adr) = Vgm.wave[adr - 0x90];
			}
			else
			{
				*(vu8*)(REG_BASE + adr) = dat;

				// regs
				if(adr >= 0x60 && adr <= 0x88)
				{
					Vgm.regs[adr - 0x60] = dat;
				}
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
EWRAM_CODE u32 VgmGetRegs(u32 i)
{
	return Vgm.regs[i];
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetWave(u32 i)
{
	return Vgm.wave[i & 0xf];
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetStat(void)
{
	return VgmPlayer.stat;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetIsFade(void)
{
	return VgmPlayer.isFade;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetFadeCnt(void)
{
	return VgmPlayer.fadeCnt;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetIsHeadset(void)
{
	return VgmPlayer.isHeadset;
}
