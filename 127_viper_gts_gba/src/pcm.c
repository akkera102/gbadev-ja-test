#include "pcm.h"
#include "libmy/snd.arm.h"
#include "file.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void PcmInit(void)
{
	PcmStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE void PcmPlay(char* p, s32 adj, bool isLoop)
{
	u8* pDat = FileGetRaw(p);
	s32 size = FileGetSize();

	TRACE("[PcmPlay %s loop:%d]\n", p, isLoop);

	SndPlay(pDat, size, adj, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void PcmStop(void)
{
	if(SndIsPlay() == false)
	{
		return;
	}

	SndStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool PcmIsPlay(void)
{
	return SndIsPlay();
}
