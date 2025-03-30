#include "vgm.arm.h"
#include "irq.arm.h"
#include "gbfs.h"

//---------------------------------------------------------------------------
ST_VGM Vgm;


//---------------------------------------------------------------------------
IWRAM_CODE void VgmInit(void)
{
	_Memset(&Vgm, 0x00, sizeof(ST_VGM));
	VgmStop();

	// REG_SOUNDBIAS
	*(vu8*)(REG_BASE + 0x88) = 0x80;
	*(vu8*)(REG_BASE + 0x89) = 0xC1;

	// REG_SOUNDCNT_X
	*(vu8*)(REG_BASE + 0x84) = 0x80;

	// REG_SOUNDCNT_H（DMG+DirectSound設定）
	*(vu8*)(REG_BASE + 0x82) = 0x05;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmPlay(u8* pFile, bool isLoop)
{
	if(Vgm.act == VGM_ACT_PLAY)
	{
		Vgm.pFile2  = pFile;
		Vgm.isLoop2 = isLoop;
		Vgm.fade    = VGM_MAX_FADE_CNT;
		Vgm.act     = VGM_ACT_PLAY_NEXT;

		return;
	}

	if(Vgm.act == VGM_ACT_PLAY_NEXT)
	{
		Vgm.pFile2  = pFile;
		Vgm.isLoop2 = isLoop;

		return;
	}

	if(Vgm.act == VGM_ACT_PLAY_FADE)
	{
		Vgm.pFile2  = pFile;
		Vgm.isLoop2 = isLoop;
		Vgm.act     = VGM_ACT_PLAY_NEXT;

		return;
	}

	_Memset(&Vgm, 0x00, sizeof(ST_VGM));
	VgmStop();

	Vgm.pFile  = pFile;
	Vgm.pCur   = pFile;
	Vgm.isLoop = isLoop;
	Vgm.act    = VGM_ACT_PLAY;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmPlayFade(void)
{
	Vgm.fade = VGM_MAX_FADE_CNT;
	Vgm.act  = VGM_ACT_PLAY_FADE;
}
//---------------------------------------------------------------------------
IWRAM_CODE void VgmStop(void)
{
	Vgm.act = VGM_ACT_STOP;

	// ch1
	*(vu8*)(REG_BASE + 0x60) = 0x00;
	*(vu8*)(REG_BASE + 0x62) = 0x00;
	*(vu8*)(REG_BASE + 0x63) = 0x08;		// NR12
	*(vu8*)(REG_BASE + 0x64) = 0x00;
	*(vu8*)(REG_BASE + 0x65) = 0x80;		// NR14

	// ch2
	*(vu8*)(REG_BASE + 0x68) = 0x00;
	*(vu8*)(REG_BASE + 0x69) = 0x08;		// NR22
	*(vu8*)(REG_BASE + 0x6c) = 0x00;
	*(vu8*)(REG_BASE + 0x6d) = 0x80;		// NR24

	// ch3
	for(u32 i=0; i<0x10; i++)
	{
		*(vu8*)(REG_BASE + 0x90 + i) = 0x00;
	}
	*(vu8*)(REG_BASE + 0x70) = 0x00;		// NR30
	*(vu8*)(REG_BASE + 0x72) = 0x00;
	*(vu8*)(REG_BASE + 0x73) = 0x00;
	*(vu8*)(REG_BASE + 0x74) = 0x00;
	*(vu8*)(REG_BASE + 0x75) = 0x00;

	// ch4
	*(vu8*)(REG_BASE + 0x78) = 0x00;
	*(vu8*)(REG_BASE + 0x79) = 0x08;		// NR42
	*(vu8*)(REG_BASE + 0x7c) = 0x00;
	*(vu8*)(REG_BASE + 0x7d) = 0x80;		// NR44

	// REG_SOUNDCNT_L
	*(vu8*)(REG_BASE + 0x80) = 0x77;		// NR50
	*(vu8*)(REG_BASE + 0x81) = 0xFF;
}
//---------------------------------------------------------------------------
EWRAM_CODE void VgmSetHeadset(void)
{
	Vgm.isHeadset = (Vgm.isHeadset == true) ? false : true;
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

	// フェード処理
	if(Vgm.act == VGM_ACT_PLAY_NEXT || Vgm.act == VGM_ACT_PLAY_FADE)
	{
		switch(Vgm.fade)
		{
		case 35: *(vu8*)(REG_BASE + 0x80) = 0x66; break;
		case 30: *(vu8*)(REG_BASE + 0x80) = 0x55; break;
		case 25: *(vu8*)(REG_BASE + 0x80) = 0x44; break;
		case 20: *(vu8*)(REG_BASE + 0x80) = 0x33; break;
		case 15: *(vu8*)(REG_BASE + 0x80) = 0x22; break;
		case 10: *(vu8*)(REG_BASE + 0x80) = 0x11; break;
		case  5: *(vu8*)(REG_BASE + 0x80) = 0x00; break;

		default:
			// EMPTY
			break;
		}

		Vgm.fade--;

		if(Vgm.fade == 0)
		{
			if(Vgm.act == VGM_ACT_PLAY_NEXT)
			{
				Vgm.act = VGM_ACT_STOP;
				VgmPlay(Vgm.pFile2, Vgm.isLoop2);

				return;
			}

			if(Vgm.act == VGM_ACT_PLAY_FADE)
			{
				VgmStop();

				return;
			}

			SystemError("VgmIntrVblank Fade act=%x", Vgm.act);
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
				if(Vgm.isHeadset == true && adr == 0x91 && dat == 0x92)
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
