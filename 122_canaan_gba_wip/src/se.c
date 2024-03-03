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
EWRAM_CODE void SePlay(u8* p)
{
	VgmPlay(p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlaySsg(s32 no, bool isWait)
{
	u8* p = FileGetSsg(no);
	Se.isWait = isWait;

	SePlay(p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlayFmx(s32 no, bool isWait)
{
	u8* p = FileGetFmx(no);
	Se.isWait = isWait;

	SePlay(p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SeStop(void)
{
	VgmStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SeIsWait(void)
{
	if(Se.isWait == true)
	{
		return VgmIsPlay();
	}

	// 演奏中であり、次の演奏の予約がある場合はウェイトを入れます
	return VgmIsPlayNext();
}
