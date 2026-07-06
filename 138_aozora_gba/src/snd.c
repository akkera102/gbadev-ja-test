#include "snd.h"
#include "libmy/sfx.arm.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_SND Snd;


//---------------------------------------------------------------------------
void SndInit(void)
{
	_Memset(&Snd, 0x00, sizeof(ST_SND));
}
//---------------------------------------------------------------------------
void SndPlay(s32 no, bool isLoop)
{
//	TRACE("[SndPlay %d %d]\n", no, isLoop);

	if(Snd.no == no && Snd.isLoop == isLoop)
	{
		return;
	}

	Snd.no = no;
	Snd.isLoop = isLoop;

	if(Snd.isLock == true)
	{
		return;
	}

	u8* p = FileGetSnd(no);
	s32 size = FileGetSize();

	SfxPlay(p, size, isLoop);
}
//---------------------------------------------------------------------------
void SndLock(void)
{
	Snd.isLock = true;
}
//---------------------------------------------------------------------------
void SndLoad(void)
{
	Snd.isLock = false;

	if(Snd.no == 0 || Snd.isLoop == false)
	{
		SndStop();

		return;
	}

	u8* p = FileGetSnd(Snd.no);
	s32 size = FileGetSize();

	SfxPlay(p, size, Snd.isLoop);
}
//---------------------------------------------------------------------------
void SndStop(void)
{
//	TRACE("[SndStop]\n");

	Snd.no = 0;

	if(SfxIsPlay() == false)
	{
		return;
	}

	SfxStop();
}
