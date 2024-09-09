#include "bgm.h"
#include "libmy/ad.arm.h"
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
EWRAM_CODE void BgmPlay(char* p, bool isLoop)
{
	u8* pDat = FileGetSnd(p);
	s32 size = FileGetSize();

	TRACE("[BgmPlay %s loop:%d]\n", p, isLoop);

	AdPlay(pDat, size, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmPlay2(char* p, bool isLoop)
{
	Bgm.p = p;
	Bgm.isLoop = isLoop;
	Bgm.isPlay = true;

	BgmPlay(p, isLoop);
}
//---------------------------------------------------------------------------
// セーブデータのロード時に使います
EWRAM_CODE void BgmPlayLoad(void)
{
	if(Bgm.isPlay == false ||  Bgm.isLoop == false)
	{
		AdStop();
		return;
	}

	BgmPlay(Bgm.p, Bgm.isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmStop(void)
{
	Bgm.isPlay = false;

	AdStop();
}
