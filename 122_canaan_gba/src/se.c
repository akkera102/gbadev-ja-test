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
EWRAM_CODE void SePlay(u8* p)
{
	VgmPlay(p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlaySsg(s32 no)
{
	u8* p = FileGetSsg(no);

	SePlay(p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlayFmx(s32 no)
{
	u8* p = FileGetFmx(no);

	SePlay(p);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SeStop(void)
{
	VgmStop2();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SeIsWait(void)
{
	// ���t���ł���A���̉��t�̗\�񂪂���ꍇ�̓E�F�C�g�����܂�
	return VgmIsPlayNext();
}