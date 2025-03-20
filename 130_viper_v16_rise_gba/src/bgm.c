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
//	u8* pDat = FileGetBgm(no);

	TRACE("[BgmPlay no:%d loop:%d]\n", no, isLoop);

//	VgmPlay(pDat, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmPlay2(s32 no, bool isLoop)
{
	if(Bgm.isPlay == true && Bgm.no == no)
	{
		return;
	}

	Bgm.no = no;
	Bgm.isLoop = isLoop;
	Bgm.isPlay = true;

	BgmPlay(no, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmStop(void)
{
	if(VgmIsPlay() == false)
	{
		return;
	}

	Bgm.isPlay = false;

//	VgmStop();
	VgmPlayFade();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool BgmIsPlay(void)
{
	return VgmIsPlay();
}
