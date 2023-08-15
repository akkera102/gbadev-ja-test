#include "bgm.h"
#include "libmy/vgm.arm.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_BGM Bgm;


//---------------------------------------------------------------------------
EWRAM_CODE void BgmInit(void)
{
	_Memset(&Bgm, 0x00, sizeof(ST_BGM));

	BgmStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmPlay(s32 no, bool isLoop)
{
	if(Bgm.no == no)
	{
		return;
	}

	BgmPlay2(no, isLoop);

	Bgm.isPlay = true;
	Bgm.isLoop = isLoop;
	Bgm.no = no;
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmPlay2(s32 no, bool isLoop)
{
	u8* pDat = FileGetMus(no);

	VgmPlay(pDat, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmStop(void)
{
	Bgm.isPlay = false;

	VgmStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmRestart(void)
{
	if(Bgm.isPlay == true)
	{
		BgmPlay2(Bgm.no, Bgm.isLoop);
	}
	else
	{
		BgmStop();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool BgmIsEnd(void)
{
	return VgmIsEnd();
}
