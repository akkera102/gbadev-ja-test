#include "se.h"
#include "libmy/snd.arm.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_SE Se;


//---------------------------------------------------------------------------
void SeInit(void)
{
	_Memset(&Se, 0x00, sizeof(ST_SE));
}
//---------------------------------------------------------------------------
void SePlay(s32 no)
{
	Se.no = no;

	TRACE("[SePlay no:%d]\n", no);

	u8* p = FileGetFmx(no);
	s32 size = FileGetSize();

	SndPlay(SND_ID_FMX, p, size, 2, false);
}
//---------------------------------------------------------------------------
void SeStop(void)
{
	if(SndIsPlay(SND_ID_FMX) == false)
	{
		return;
	}

	SndStop(SND_ID_FMX);
}
//---------------------------------------------------------------------------
bool SeIsPlay(void)
{
	return SndIsPlay(SND_ID_FMX);
}
