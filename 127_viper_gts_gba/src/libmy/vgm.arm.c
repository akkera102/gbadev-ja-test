#include "vgm.arm.h"
#include "irq.arm.h"

//---------------------------------------------------------------------------
ST_VGM Vgm;


//---------------------------------------------------------------------------
EWRAM_CODE void VgmInit(void)
{
	_Memset(&Vgm, 0x00, sizeof(ST_VGM));
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmPlay(u8* p, bool isLoop)
{
	VgmStop();

	Vgm.pCur = p;
	Vgm.pTop = p;
	Vgm.isLoop = isLoop;

	Vgm.act = VGM_ACT_PLAY;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
	Vgm.act = VGM_ACT_STOP;

	// ch1
	*(vu8*)(REG_BASE + 0x60) = 0x00;
	*(vu8*)(REG_BASE + 0x62) = 0x00;
	*(vu8*)(REG_BASE + 0x63) = 0x00;
	*(vu8*)(REG_BASE + 0x64) = 0x00;
	*(vu8*)(REG_BASE + 0x65) = 0x00;

	// ch2
	*(vu8*)(REG_BASE + 0x68) = 0x00;
	*(vu8*)(REG_BASE + 0x69) = 0x00;
	*(vu8*)(REG_BASE + 0x6c) = 0x00;
	*(vu8*)(REG_BASE + 0x6d) = 0x00;

	// ch3
	u32 i;

	for(i=0; i<0x10; i++)
	{
		*(vu8*)(REG_BASE + 0x90 + i) = 0x80;
	}
	*(vu8*)(REG_BASE + 0x70) = 0x00;
	*(vu8*)(REG_BASE + 0x72) = 0x00;
	*(vu8*)(REG_BASE + 0x73) = 0x00;
	*(vu8*)(REG_BASE + 0x74) = 0x00;
	*(vu8*)(REG_BASE + 0x75) = 0x00;

	// ch4
	*(vu8*)(REG_BASE + 0x78) = 0x00;
	*(vu8*)(REG_BASE + 0x79) = 0x00;
	*(vu8*)(REG_BASE + 0x7c) = 0x00;
	*(vu8*)(REG_BASE + 0x7d) = 0x00;

	// REG_SOUNDCNT
//	*(vu8*)(REG_BASE + 0x84) = 0x80;
	*(vu8*)(REG_BASE + 0x80) = 0x77;
	*(vu8*)(REG_BASE + 0x81) = 0xFF;
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

		if(cmd == VGM_CMD_WREG)
		{
			u8 adr = *Vgm.pCur++;
			u8 dat = *Vgm.pCur++;
			*(u8*)(REG_BASE + adr) = dat;

			continue;
		}

		if(cmd == VGM_CMD_EOM)
		{
			if(Vgm.isLoop == true)
			{
				Vgm.pCur = Vgm.pTop;

				return;
			}

			VgmStop();
			IrqSetVbl();

			return;
		}

		SystemError("VgmIntrVblank adr=%x", Vgm.pCur - Vgm.pTop);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool VgmIsPlay(void)
{
	return (Vgm.act == VGM_ACT_STOP) ? false : true;
}