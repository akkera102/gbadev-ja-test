#include "vgm.arm.h"
#include "irq.arm.h"
#include "gbfs.h"

//---------------------------------------------------------------------------
ST_VGM Vgm;


//---------------------------------------------------------------------------
void VgmInit(void)
{
	_Memset(&Vgm, 0x00, sizeof(ST_VGM));

	VgmSetVol(VGM_VOL_DEF_CNT);
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmPlay(u8* pFile, bool isLoop)
{
	VgmStop();

	Vgm.pFile  = pFile;
	Vgm.pCur   = pFile;
	Vgm.isLoop = isLoop;
	Vgm.act    = VGM_ACT_PLAY;
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
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmSetVol(s32 vol)
{
	_ASSERT(vol >= 0 && vol <= VGM_VOL_MAX_CNT);


	Vgm.vol = vol;

	switch(vol)
	{
	case 9:
		*(vu8*)(REG_BASE + 0x80) = 0x77;
		*(vu8*)(REG_BASE + 0x82) = 0x0E;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		break;

	case 8:
		*(vu8*)(REG_BASE + 0x80) = 0x66;
		*(vu8*)(REG_BASE + 0x82) = 0x0E;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		break;

	case 7:
		*(vu8*)(REG_BASE + 0x80) = 0x55;
		*(vu8*)(REG_BASE + 0x82) = 0x0E;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		break;

	case 6:
		*(vu8*)(REG_BASE + 0x80) = 0x44;
		*(vu8*)(REG_BASE + 0x82) = 0x0E;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		break;

	case 5:
		*(vu8*)(REG_BASE + 0x80) = 0x77;
		*(vu8*)(REG_BASE + 0x82) = 0x0D;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		break;

	case 4:
		*(vu8*)(REG_BASE + 0x80) = 0x66;
		*(vu8*)(REG_BASE + 0x82) = 0x0D;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		break;

	case 3:
		*(vu8*)(REG_BASE + 0x80) = 0x55;
		*(vu8*)(REG_BASE + 0x82) = 0x0D;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		break;

	case 2:
		*(vu8*)(REG_BASE + 0x80) = 0x44;
		*(vu8*)(REG_BASE + 0x82) = 0x0D;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		break;

	case 1:
		*(vu8*)(REG_BASE + 0x80) = 0x33;
		*(vu8*)(REG_BASE + 0x82) = 0x0D;
		*(vu8*)(REG_BASE + 0x81) = 0xFF;
		break;

	default:
		*(vu8*)(REG_BASE + 0x80) = 0x00;
		*(vu8*)(REG_BASE + 0x82) = 0x0D;
		*(vu8*)(REG_BASE + 0x81) = 0x00;
		break;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE s32 VgmGetVol(void)
{
	return Vgm.vol;
}
//---------------------------------------------------------------------------
IWRAM_CODE bool VgmIsPlay(void)
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

	for(;;)
	{
		u8 cmd = *Vgm.pCur++;

		if(cmd == VGM_CMD_WAIT)
		{
			return;
		}
		else if(cmd == VGM_CMD_WREG)
		{
			u8 adr = *Vgm.pCur++;
			u8 dat = *Vgm.pCur++;

			*(vu8*)(REG_BASE + adr) = dat;
		}
		else if(cmd == VGM_CMD_EOM)
		{
			if(Vgm.isLoop == false)
			{
				VgmStop();

				return;
			}

			u32 loop;

			loop  = *Vgm.pCur++;
			loop |= *Vgm.pCur++ <<  8;
			loop |= *Vgm.pCur++ << 16;
			loop |= *Vgm.pCur++ << 24;

			Vgm.pCur = Vgm.pFile + loop;

			return;
		}
	}
}
