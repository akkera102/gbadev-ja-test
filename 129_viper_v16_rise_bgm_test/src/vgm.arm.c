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
  // *(vu8*)(REG_BASE + AGREG_BIAS_H) = 0xC1;
  // *(vu8*)(REG_BASE + AGREG_BIAS_L) = 0x80;
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmInit(void)
{
	_Memset(&Vgm, 0x00, sizeof(ST_VGM));
  Vgm.regs[AGREG_NR50 - AGREG_START] = 0x77;
  Vgm.regs[AGREG_NR51 - AGREG_START] = 0xFF;
  Vgm.regs[AGREG_NR52 - AGREG_START] = 0x80;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
  VgmPlayer.stat = PLAYER_STAT_STOP;

  // REG_SOUNDCNT_L
  *(vu8*)(REG_BASE + AGREG_NR52) = 0x80; //常に0x80

  // ch1
  *(vu8*)(REG_BASE + AGREG_NR10) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR11) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR12) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR13) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR14) = 0x80;

  // ch2
  *(vu8*)(REG_BASE + AGREG_NR21) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR22) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR23) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR24) = 0x80;

  // ch3
  for(u32 i=0; i<WAVE_LEN; i++)
  {
    *(vu8*)(REG_BASE + AGREG_WAVE + i) = 0x00;
  }
  *(vu8*)(REG_BASE + AGREG_NR30) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR31) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR32) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR33) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR34) = 0x00;

  // ch4
  *(vu8*)(REG_BASE + AGREG_NR41) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR42) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR43) = 0x00;
  *(vu8*)(REG_BASE + AGREG_NR44) = 0x80;

  // REG_SOUNDCNT_L
  *(vu8*)(REG_BASE + AGREG_NR50) = 0x77;
  *(vu8*)(REG_BASE + AGREG_NR51) = 0xFF;

  // REG_SOUNDCNT_H
  VgmUpdSoundcntH(PLAYER_SOUNDCNT_H); // エミュの初期値が0x00で実機と異なる
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmUpdSoundcntL(u8 dat)
{
  Vgm.regs[AGREG_NR50 - AGREG_START] = dat;
  *(vu8*)(REG_BASE + AGREG_NR50) = Vgm.regs[AGREG_NR50 - AGREG_START];
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmUpdSoundcntH(u8 dat)
{
  *(vu8*)(REG_BASE + AGREG_RESAMP) = ((*((u16 volatile *) (REG_BASE + AGREG_RESAMP))) & 0xFC) | dat;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmUpdWave(u8 adr, u8 dat)
{
  if(AGREG_WAVE == adr && 0x04 == dat)
  {
    Vgm.wave[adr - AGREG_WAVE] = 0x01;
  }
  else if((AGREG_WAVE + 1) == adr && 0x92 == dat)
  {
    Vgm.wave[adr - AGREG_WAVE] = 0x31;
  }
  else if((AGREG_WAVE + 1) == adr && 0x71 == dat)
  {
    Vgm.wave[adr - AGREG_WAVE] = 0x31;
  }
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmPlay(u8 trId)
{
	VgmInit();
	VgmStop();

	u8* pFile = GbfsGetSafePointer2(trId);

	Vgm.pCur   = pFile;
	Vgm.pFile  = pFile;
	Vgm.isLoop = true;

	VgmPlayer.stat    = PLAYER_STAT_PLAY;
	VgmPlayer.fadeCnt = 0;
	// VgmPlayer.pNextFile = pFile;
	VgmPlayer.isWaveEdit = false;
	// VgmPlayer.isHeadset = false;
	// VgmPlayer.isFade = false;
	VgmPlayer.trId = trId;
	VgmPlayer.trIdReserve = trId;
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmReserve(u8 trIdReserve)
{
	VgmPlayer.stat    = PLAYER_STAT_RESERVE;
	VgmPlayer.fadeCnt = PLAYER_FADE_CNT;
	// VgmPlayer.pNextFile = pNextFile;
	VgmPlayer.trIdReserve = trIdReserve;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetLoop(u32 loop)
{
	Vgm.isLoop = (loop == 0) ? false : true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetWave(u32 i, u32 dat)
{
	Vgm.wave[i & (WAVE_LEN - 1)] = dat;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetWaveEdit(u32 waveedit)
{
	VgmPlayer.isWaveEdit = (waveedit == 0) ? false : true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetHeadset(u32 headset)
{
	VgmPlayer.isHeadset = (headset == 0) ? false : true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetFade(u32 fade)
{
	VgmPlayer.isFade = (fade == 0) ? false : true;
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
			VgmPlay(VgmPlayer.trIdReserve);

			return;
		}
	}

	// PLAY
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

			//wave
			if(adr >= AGREG_WAVE && adr < AGREG_WAVE + WAVE_LEN)
			{
				if(!VgmPlayer.isWaveEdit)
				{
					Vgm.wave[adr - AGREG_WAVE] = dat;

					if(VgmPlayer.isHeadset)
					{
						VgmUpdWave(adr, dat);
					}
				}
				*(vu8*)(REG_BASE + adr) = Vgm.wave[adr - AGREG_WAVE];
			}
			else
			{
				*(vu8*)(REG_BASE + adr) = dat;

				//regs
				if(adr >= AGREG_START && adr <= AGREG_START + 0x28)
				{
					Vgm.regs[adr - AGREG_START] = dat;
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
EWRAM_CODE u32 VgmGetAgReg(u32 i)
{
  return Vgm.regs[i - AGREG_START];
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetWave(u32 i)
{
  return Vgm.wave[i & (WAVE_LEN - 1)];
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetStat(void)
{
	return VgmPlayer.stat;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetIsWaveEdit(void)
{
	return VgmPlayer.isWaveEdit;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 VgmGetIsHeadset(void)
{
	return VgmPlayer.isHeadset;
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
EWRAM_CODE u32 VgmGetTrId(void)
{
  return VgmPlayer.trId;
}
