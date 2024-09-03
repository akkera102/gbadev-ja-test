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
EWRAM_CODE bool SeIsLoopNo(s32 no)
{
	switch(no)
	{
		case 2:		// �d�b�R�[��1
		case 13:	// �d�b�R�[��2
		case 14:	// ����
		case 26:	// ��������������
		case 31:	// �x��
		case 42:	// �d�b�؂�����
		case 47:	// �n�k
		case 50:	// �h�����R����
		case 55:	// �d�b�R�[��3
		case 56:	// �d�b�R�[��4
		case 57:	// �K�`���A�d�b�؂�����

		// PMD�t�@�C��������ʉ��ɕύX
		case 66:	// �J
		case 67:	// �W����
		case 68:	// ���i�����j
			return true;
	}

	return false;
}
