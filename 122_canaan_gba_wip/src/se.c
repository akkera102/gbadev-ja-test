#include "bgm.h"
#include "libmy/vgm.arm.h"
#include "file.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlaySsg(s32 no)
{
//	u8* p = FileGetSe(no);
//	VgmPlay(p, false);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlayFmx(s32 no)
{
	// TODO no�ɏ��׍H
	// SePlaySsg(no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SeStop(void)
{
	VgmStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SeIsEnd(void)
{
	return VgmIsEnd();
}
