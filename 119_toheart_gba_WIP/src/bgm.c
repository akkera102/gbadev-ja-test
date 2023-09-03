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
EWRAM_CODE void BgmPlay(u32 no, bool isLoop)
{
	if(Bgm.no == no && Bgm.isPlay == true)
	{
		return;
	}

	BgmPlay2(no, isLoop);

	Bgm.isPlay = true;
	Bgm.isLoop = isLoop;
	Bgm.no = no;
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmPlay2(u32 no, bool isLoop)
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
	if(Bgm.isPlay == false)
	{
		BgmStop();

		return;
	}

	BgmPlay2(Bgm.no, Bgm.isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool BgmIsEnd(void)
{
	return VgmIsEnd();
}
