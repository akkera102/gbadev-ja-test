#include "bgm.h"
#include "libmy/ad_arm.h"
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

	Bgm.no = no;
	Bgm.isLoop = isLoop;
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmPlay2(s32 no, bool isLoop)
{
	if(no == 0)
	{
		AdStop();
		return;
	}

	u8* pDat = FileGetMus(no);
	u32 size = FileGetSize();

	AdSetData(pDat, size, isLoop);
	AdPlay();
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmStop(void)
{
	Bgm.no = 0;
	AdStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmRestart(void)
{
	BgmPlay2(Bgm.no, Bgm.isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool BgmIsEnd(void)
{
	return AdIsEnd();
}
