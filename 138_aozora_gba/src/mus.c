#include "mus.h"
#include "libmy/ulc.arm.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_MUS Mus;


//---------------------------------------------------------------------------
void MusInit(void)
{
	_Memset(&Mus, 0x00, sizeof(ST_MUS));
}
//---------------------------------------------------------------------------
void MusPlay(s32 no, bool isLoop)
{
//	TRACE("[MusPlay %d %d]\n", no, isLoop);

	if(Mus.no == no && Mus.isLoop == isLoop)
	{
		return;
	}

	Mus.no = no;
	Mus.isLoop = isLoop;

	if(Mus.isLock == true)
	{
		return;
	}

	UlcPlay(FileGetMus(no), isLoop);
}
//---------------------------------------------------------------------------
void MusLock(void)
{
	Mus.isLock = true;
}
//---------------------------------------------------------------------------
void MusLoad(void)
{
	Mus.isLock = false;

	if(Mus.no == 0 || Mus.isLoop == false)
	{
		MusStop();

		return;
	}

	UlcPlay(FileGetMus(Mus.no), Mus.isLoop);
}
//---------------------------------------------------------------------------
void MusStop(void)
{
//	TRACE("[MusStop]\n");

	Mus.no = 0;

	if(UlcIsPlay() == false)
	{
		return;
	}

	UlcStop();
}
