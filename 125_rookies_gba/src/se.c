#include "se.h"
#include "libmy/vgm.arm.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_SE Se;


//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void)
{
	_Memset(&Se, 0x00, sizeof(ST_SE));

	SeStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlay(s32 no, bool isLoop)
{
//	u8* pDat = FileGetFmx(no);

	TRACE("[SePlay no:%d loop:%d]\n", no, isLoop);

//	VgmPlay(pDat, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlay2(s32 no)
{
	Se.no = no;
	Se.isLoop = SeIsLoopNo(no);

	SePlay(Se.no, Se.isLoop);
}
//---------------------------------------------------------------------------
// セーブデータのロード時に使います（ループ再生の効果音のみ演奏）
EWRAM_CODE void SePlayLoad(void)
{
	if(Se.isLoop == false)
	{
		if(VgmIsPlay() == true)
		{
			VgmStop2();
		}

		return;
	}

	SePlay(Se.no, Se.isLoop);
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
//---------------------------------------------------------------------------
EWRAM_CODE bool SeIsLoopNo(s32 no)
{
	switch(no)
	{
		case 64:
		case 65:
		case 66:
		case 67:
		case 68:
		case 69:
		case 70:
		case 71:
		case 72:
		case 73:
		case 74:
		case 75:
		return true;
	}

	return false;
}
