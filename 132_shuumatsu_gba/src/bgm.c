#include "bgm.h"
#include "libmy/snd.arm.h"
#include "libmy/vgm.arm.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_BGM Bgm;


//---------------------------------------------------------------------------
void BgmInit(void)
{
	_Memset(&Bgm, 0x00, sizeof(ST_BGM));
}
//---------------------------------------------------------------------------
void BgmPlay(s32 no)
{
	Bgm.no = no;

	if(no == 1)
	{
		BgmStop();

		return;
	}

	if(no == 3 || no == 11)
	{
		BgmPlayRaw(no);
	}
	else
	{
		BgmPlayVgm(no);
	}
}
//---------------------------------------------------------------------------
void BgmPlayRaw(s32 no)
{
	TRACE("[BgmPlayRaw %d]\n", no);

	u8* p = FileGetBgm(no);
	s32 size = FileGetSize();

	SndPlay(SND_ID_BGM, p, size, 2, false);
}
//---------------------------------------------------------------------------
void BgmPlayVgm(s32 no)
{
	TRACE("[BgmPlayVgm %d]\n", no);

//	u8* p = FileGetBgm(no);

//	VgmPlay(p, true);
}
//---------------------------------------------------------------------------
void BgmLoadPlay(void)
{
	BgmPlay(Bgm.no);
}
//---------------------------------------------------------------------------
void BgmStop(void)
{
	TRACE("[BgmStop]\n");

	if(VgmIsPlay() == true)
	{
//		VgmStop();
		VgmPlayFade();
	}

	if(SndIsPlay(SND_ID_BGM) == true)
	{
		SndStop(SND_ID_BGM);
	}

	Bgm.no = 1;
}
