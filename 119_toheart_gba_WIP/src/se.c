#include "se.h"
#include "libmy/snd.arm.h"
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

	Se.cnt = cnt;
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
EWRAM_CODE s32 SeGetNo(void)
{
	return Se.no;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SeIsEnd(void)
{
	return SndIsEnd();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SeIsEnd2(void)
{
	// 無限ループ指定は終了とします
	if(Se.cnt == 0)
	{
		return true;
	}

	return SndIsEnd();
}
