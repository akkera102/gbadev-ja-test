#include "vgm.arm.h"
#include "irq.arm.h"
#include "gbfs.h"

//---------------------------------------------------------------------------
ST_VGM Vgm;


//---------------------------------------------------------------------------
IWRAM_CODE void VgmInit(void)
{
	_Memset(&Vgm, 0x00, sizeof(ST_VGM));
	Vgm.vol = VGM_VOL_DEF_CNT;

	// REG_SOUNDCNT_X
	// REG_SOUNDCNT_H
//	*(vu8*)(REG_BASE + 0x84) = 0x80;
//	*(vu8*)(REG_BASE + 0x82) = 0x05;

	VgmStop();
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmPlay(u8* pFile, bool isLoop)
{
	if(Vgm.act == VGM_ACT_PLAY)
	{
		Vgm.pFile2  = pFile;
		Vgm.isLoop2 = isLoop;
		Vgm.fade    = Vgm.vol;
		Vgm.act     = VGM_ACT_PLAY_NEXT;

		return;
	}

	if(Vgm.act == VGM_ACT_PLAY_FADE)
	{
		Vgm.pFile2  = pFile;
		Vgm.isLoop2 = isLoop;
		Vgm.act     = VGM_ACT_PLAY_NEXT;

		return;
	}

	if(Vgm.act == VGM_ACT_PLAY_NEXT)
	{
		Vgm.pFile2  = pFile;
		Vgm.isLoop2 = isLoop;

		return;
	}

	Vgm.pFile  = pFile;
	Vgm.pCur   = pFile;
	Vgm.isLoop = isLoop;
	Vgm.act    = VGM_ACT_PLAY;

	VgmSetVolReg(Vgm.vol);
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmPlayFade(void)
{
	Vgm.fade = Vgm.vol;
	Vgm.act  = VGM_ACT_PLAY_FADE;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
	Vgm.act = VGM_ACT_STOP;

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

	VgmSetVolReg(0);
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmSetHeadset(void)
{
	Vgm.isHeadset = (Vgm.isHeadset == true) ? false : true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmSetVolReg(s32 vol)
{
	switch(vol)
	{
	case 12:
		*(vu8*)(REG_BASE + 0x80) = 0x77;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x06;
		break;

	case 11:
		*(vu8*)(REG_BASE + 0x80) = 0x66;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x06;
		break;

	case 10:
		*(vu8*)(REG_BASE + 0x80) = 0x55;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x06;
		break;

	case 9:
		*(vu8*)(REG_BASE + 0x80) = 0x44;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x06;
		break;

	case 8:
		*(vu8*)(REG_BASE + 0x80) = 0x77;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x05;
		break;

	case 7:
		*(vu8*)(REG_BASE + 0x80) = 0x66;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x05;
		break;

	case 6:
		*(vu8*)(REG_BASE + 0x80) = 0x55;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x05;
		break;

	case 5:
		*(vu8*)(REG_BASE + 0x80) = 0x44;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x05;
		break;

	case 4:
		*(vu8*)(REG_BASE + 0x80) = 0x33;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x05;
		break;

	case 3:
		*(vu8*)(REG_BASE + 0x80) = 0x22;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x05;
		break;

	case 2:
		*(vu8*)(REG_BASE + 0x80) = 0x11;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x05;
		break;

	case 1:
		*(vu8*)(REG_BASE + 0x80) = 0x00;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		*(vu8*)(REG_BASE + 0x82) = 0x05;
		break;

	default:
		*(vu8*)(REG_BASE + 0x80) = 0x00;
		*(vu8*)(REG_BASE + 0x81) = 0x00;
		*(vu8*)(REG_BASE + 0x82) = 0x04;
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmSetVol(s32 vol)
{
	_ASSERT(vol >= 0 && vol <= VGM_VOL_MAX_CNT);

	Vgm.vol = vol;

	if(Vgm.act != VGM_ACT_STOP)
	{
		VgmSetVolReg(Vgm.vol);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 VgmGetVol(void)
{
	return Vgm.vol;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 VgmGetMaxVol(void)
{
	return VGM_VOL_MAX_CNT;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool VgmIsHeadset(void)
{
	return Vgm.isHeadset;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool VgmIsPlay(void)
{
	return (Vgm.act == VGM_ACT_STOP) ? false : true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmIntrVblank(void)
{
	if(Vgm.act == VGM_ACT_STOP)
	{
		return;
	}

	if(Vgm.act == VGM_ACT_PLAY_NEXT || Vgm.act == VGM_ACT_PLAY_FADE)
	{
		VgmSetVolReg(Vgm.fade);

		if(Vgm.fade != 0)
		{
			Vgm.fade--;
		}
		else if(Vgm.act == VGM_ACT_PLAY_FADE)
		{
			VgmStop();

			return;
		}
		else if(Vgm.act == VGM_ACT_PLAY_NEXT)
		{
			VgmStop();
			VgmPlay(Vgm.pFile2, Vgm.isLoop2);

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
				if(Vgm.isHeadset == true && adr == 0x90 && dat == 0x04)
				{
					*(vu8*)(REG_BASE + adr) = 0x01;
				}
				else if(Vgm.isHeadset == true && adr == 0x91 && dat == 0x92)
				{
					*(vu8*)(REG_BASE + adr) = 0x31;
				}
				else
				{
					*(vu8*)(REG_BASE + adr) = dat;
				}

				continue;
			}

			// reg
			if(Vgm.vol == 0 && adr == 0x81)
			{
				dat = 0x00;
			}

			*(vu8*)(REG_BASE + adr) = dat;

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

		SystemError("VgmIntrVblank Tick adr=%x", Vgm.pCur - Vgm.pFile);
	}
}
