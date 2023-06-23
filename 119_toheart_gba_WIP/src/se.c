#include "se.h"
#include "libmy/snd.h"
#include "file.h"


//---------------------------------------------------------------------------
ST_SE Se;


//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void)
{
	_Memset(&Se, 0x00, sizeof(ST_SE));
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlay(s32 cnt)
{
	u8* pDat = FileGetSe(Se.no);
	s32 size = FileGetSize();

	SndPlay(pDat, size, -6, cnt);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SeStop(void)
{
	SndStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE void SeSetNo(s32 no)
{
	Se.no = no;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SeIsEnd(void)
{
	return SndIsEnd();
}
