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
EWRAM_CODE void BgmPlay(s32 no, bool isLoop)
{
	u8* pDat = FileGetMus(no);
	s32 size = FileGetSize();

	TRACE("[BgmPlay no:%d loop:%d]\n", no, isLoop);
	AdPlay(pDat, size, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmPlay2(s32 no, bool isLoop)
{
	if(Bgm.no == no && Bgm.isPlay == true)
	{
		return;
	}

	BgmPlay(no, isLoop);

	Bgm.isPlay = true;
	Bgm.isLoop = isLoop;
	Bgm.no = no;
}
//---------------------------------------------------------------------------
// セーブデータのロード時に使います
EWRAM_CODE void BgmPlayLoad(void)
{
	if(Bgm.isPlay == false)
	{
		BgmStop();

		return;
	}

	BgmPlay(Bgm.no, Bgm.isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgmStop(void)
{
	Bgm.isPlay = false;

	AdStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 BgmGetOffset(void)
{
	return AdGetOffset();
}
