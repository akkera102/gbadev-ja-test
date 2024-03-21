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
IWRAM_CODE void VgmPlay(u8* pDat)
{
	_ASSERT(Vgm.pNext == NULL);

	// ‰‰‘t’†‚È‚çŽŸ‚Ì‰¹‚ð—\–ñ‚µ‚Ü‚·
	if(Vgm.act == VGM_ACT_PLAY)
	{
		Vgm.pNext = pDat;

		return;
	}

	VgmStop();

	Vgm.act  = VGM_ACT_PLAY;
	Vgm.pCur = pDat;
	Vgm.pTop = pDat;

	IrqSetVblVcnt();
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
	Vgm.act = VGM_ACT_STOP;

	// REG_SOUNDCNT
//	*(u8*)(REG_BASE + 0x84) = 0x80;

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
		*(u8*)(REG_BASE + 0x90 + i) = 0x80;
	}
	*(u8*)(REG_BASE + 0x70) = 0x00;
	*(u8*)(REG_BASE + 0x72) = 0x00;
	*(u8*)(REG_BASE + 0x73) = 0x00;
	*(u8*)(REG_BASE + 0x74) = 0x00;
	*(u8*)(REG_BASE + 0x75) = 0x00;

	// ch4
	*(u8*)(REG_BASE + 0x78) = 0x00;
	*(u8*)(REG_BASE + 0x79) = 0x00;
	*(u8*)(REG_BASE + 0x7c) = 0x00;
	*(u8*)(REG_BASE + 0x7d) = 0x00;

	// REG_SOUNDCNT
	*(u8*)(REG_BASE + 0x80) = 0x77;
	*(u8*)(REG_BASE + 0x81) = 0xFF;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop2(void)
{
	VgmStop();
	VgmInit();			// pNextÁ‹Ž
	IrqSetVbl();		// Š„‚èž‚Ýƒnƒ“ƒhƒ‰•ÏX
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmIntrVCount(void)
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
			if(Vgm.pNext != NULL)
			{
				VgmStop();

				Vgm.act   = VGM_ACT_PLAY;
				Vgm.pCur  = Vgm.pNext;
				Vgm.pTop  = Vgm.pNext;
				Vgm.pNext = NULL;

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
//---------------------------------------------------------------------------
EWRAM_CODE bool VgmIsPlayNext(void)
{
	return (Vgm.pNext == NULL) ? false : true;
}
