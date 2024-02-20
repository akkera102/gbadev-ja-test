#include "se.h"
#include "libmy/vgm.arm.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_SE Se;


//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void)
{
	_Memset(&Se, 0x00, sizeof(ST_SE));
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlay(u8* p, bool isWait)
{
	VgmPlay(p, false);

	Se.isWait = isWait;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlaySsg(s32 no, bool isWait)
{
	u8* p = FileGetSsg(no);

	SePlay(p, isWait);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlayFmx(s32 no, bool isWait)
{
	u8* p = FileGetFmx(no);

	SePlay(p, isWait);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SeStop(void)
{
	VgmStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SeIsPlay(void)
{
	if(Se.isWait == false)
	{
		return false;
	}

	return VgmIsPlay();
}
