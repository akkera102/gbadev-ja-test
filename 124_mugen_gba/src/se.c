#include "se.h"
#include "libmy/vgm.arm.h"
#include "file.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlay(u8* p, bool isLoop)
{
	VgmPlay(p, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlayFmx(s32 no)
{
	bool isLoop = false;

	if(no == 1)
	{
		isLoop = true;
	}

	u8* p = FileGetFmx(no);

	SePlay(p, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SeStop(void)
{
	if(VgmIsPlay() == false)
	{
		return;
	}

	VgmStop2();
}
