#include "mus.h"
#include "libmy/ad.arm.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_MUS Mus;


//---------------------------------------------------------------------------
void MusInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
void MusPlay(void)
{
	u8* p = FileGetMus();
	s32 size = FileGetSize();

	AdPlay(p, size, false);
}
//---------------------------------------------------------------------------
void MusStop(void)
{
	if(AdIsPlay() == false)
	{
		return;
	}

	AdStop();
}
