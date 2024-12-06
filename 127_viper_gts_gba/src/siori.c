#include "siori.h"
#include "libmy/sav.h"
#include "nv.h"
#include "info.h"

// �w�b�_�@�@�@0x0000 - 0x000F
// �f�[�^�P�@�@0x0010 - 0x1FFF
// �f�[�^�Q�@�@0x1010 - 0x2FFF
// �i�����j
// �f�[�^�W�@�@0x7010 - 0x7FFF


//---------------------------------------------------------------------------
// ��O�Q��
extern ST_NV Nv;


//---------------------------------------------------------------------------
EWRAM_CODE void SioriInit(void)
{
	s32 size = 3*2;					// u16 Nv.var�z���17, 200, 201��ۑ�

	TRACE("[SioriSize:%x]\n", size);
	_ASSERT(size < SIORI_MAX_SIZE);


	if(SioriIsExist() == true)
	{
		return;
	}

	// ����ݒ�
	if(SavIsFlash() == true)
	{
		TRACE("[SaveChip: Flash]\n");

		SioriSaveFlashHeader();
	}
	else
	{
		TRACE("[SaveChip: SRAM]\n");

		SioriSaveSramHeader();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSave(s32 no)
{
	TRACE("[SioriSave:%x]\n", no);
	_ASSERT(no < SIORI_MAX_CNT);

	if(SavReadSram(2) == SIORI_TYPE_FLASH)
	{
		SioriSaveFlashData(no);
	}
	else
	{
		SioriSaveSramData(no);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveFlashHeader(void)
{
	// �w�b�_
	SavWriteFlashEraseSector(0);
	SavWriteFlash(0, 'S');
	SavWriteFlash(1, 'O');
	SavWriteFlash(2, SIORI_TYPE_FLASH);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveFlashData(s32 no)
{
	TRACE("[SioriSaveFlashData]\n", no);
	SavWriteFlashEraseSector(no);

	// �w�b�_
	if(no == 0)
	{
		SavWriteFlash(0, 'S');
		SavWriteFlash(1, 'O');
		SavWriteFlash(2, SIORI_TYPE_FLASH);
	}

	// �f�[�^
	s32 adr = 0x1000 * no + 16;

	vu16 var[3];
	vu8* p = (u8*)&var;

	var[0] = NvGetVar(17);
	var[1] = NvGetVar(200);
	var[2] = NvGetVar(201);

	SavWriteFlash(adr++, 'G');
	SavWriteFlash(adr++, 'T');

	s32 i;

	for(i=0; i<3*2; i++)
	{
		SavWriteFlash(adr++, *p++);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveSramHeader(void)
{
	// �w�b�_
	SavWriteSram(0, 'S');
	SavWriteSram(1, 'O');
	SavWriteSram(2, SIORI_TYPE_SRAM);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveSramData(s32 no)
{
	TRACE("[SioriSaveSramData]\n", no);

	// �f�[�^
	s32 adr = 0x1000 * no + 16;

	vu16 var[3];
	vu8* p = (u8*)&var;

	var[0] = NvGetVar(17);
	var[1] = NvGetVar(200);
	var[2] = NvGetVar(201);

	SavWriteSram(adr++, 'G');
	SavWriteSram(adr++, 'T');

	s32 i;

	for(i=0; i<3*2; i++)
	{
		SavWriteSram(adr++, *p++);
	}
}
//---------------------------------------------------------------------------
// �ǂݍ��݂�SRAM, FLASH����
EWRAM_CODE void SioriLoad(s32 no)
{
	TRACE("\n[SioriLoad:%x]\n", no);

	// �f�[�^
	s32 adr = 0x1000 * no + 16 + 2;

	vu16 var[3];
	vu8* p = (u8*)&var;

	s32 i;

	for(i=0; i<3*2; i++)
	{
		*p++ = SavReadSram(adr++);
	}

	NvSetVar( 17, var[0]);
	NvSetVar(200, var[1]);
	NvSetVar(201, var[2]);
}
//---------------------------------------------------------------------------
EWRAM_CODE u16 SioriGetVar(s32 no)
{
	if(SioriIsItem(no) == false)
	{
		return 0xff;
	}

	s32 adr = 0x1000 * no + 16 + 2;

	u16 ret  = SavReadSram(adr++);
	    ret |= SavReadSram(adr++) <<  8;

	return ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsExist(void)
{
	if(SavReadSram(0) != 'S') return false;
	if(SavReadSram(1) != 'O') return false;

	return true;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsItem(s32 no)
{
	if(SavReadSram(0x1000 * no + 16) != 'G') return false;
	if(SavReadSram(0x1000 * no + 17) != 'T') return false;

	return true;
}
