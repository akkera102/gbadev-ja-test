#include "bgm.h"
#include "libmy/vgm.arm.h"
#include "file.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void BgmInit(void)
{
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
EWRAM_CODE void BgmStop(void)
{
	if(VgmIsPlay() == false)
	{
		return;
	}

	VgmStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool BgmIsPlay(void)
{
	return VgmIsPlay();
}
