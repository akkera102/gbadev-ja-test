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
EWRAM_CODE void SePlay2(s32 no, bool isLoop, bool isWait)
{
	Se.no = no;
	Se.isLoop = isLoop;
	Se.isWait = isWait;

	SePlay(Se.no, Se.isLoop);
}
//---------------------------------------------------------------------------
// �Z�[�u�f�[�^�̃��[�h���Ɏg���܂��i���[�v�Đ��̌��ʉ��̂݉��t�j
EWRAM_CODE void SePlayLoad(void)
{
	if(Se.isLoop == false)
	{
		SeStop();

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
EWRAM_CODE bool SeIsWait(void)
{
	return (VgmIsPlay() && Se.isWait) ? true : false;
}
