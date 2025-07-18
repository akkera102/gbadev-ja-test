#include "siori.h"
#include "libmy/sav.h"
#include "cur.h"
#include "nv.h"
#include "txt.h"
#include "img.h"
#include "bgm.h"
#include "se.h"


// �w�b�_�@�@�@0x0000 - 0x000F
// �f�[�^�P�@�@0x0010 - 0x1FFF
// �f�[�^�Q�@�@0x1010 - 0x2FFF
// �i�����j
// �f�[�^�W�@�@0x7010 - 0x7FFF


//---------------------------------------------------------------------------
// ��O�Q��
extern ST_NV  Nv;
extern ST_TXT Txt;
extern ST_CUR Cur;
extern ST_IMG Img;
extern ST_BGM Bgm;
extern ST_SE  Se;

//---------------------------------------------------------------------------
void SioriInit(void)
{
	s32 size = 2 + sizeof(ST_NV) + sizeof(ST_TXT) + sizeof(ST_CUR) + sizeof(ST_IMG) + sizeof(ST_BGM) + sizeof(ST_SE);

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
void SioriSave(s32 no)
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
void SioriSaveFlashHeader(void)
{
	// �w�b�_
	SavWriteFlashEraseSector(0);
	SavWriteFlash(0, 'A');
	SavWriteFlash(1, 'P');
	SavWriteFlash(2, SIORI_TYPE_FLASH);
}
//---------------------------------------------------------------------------
void SioriSaveFlashData(s32 no)
{
	s32 adr = 0x1000 * no + 16;
	u32 i;
	u8* p;

	TRACE("[SioriSaveFlashData]\n", no);
	SavWriteFlashEraseSector(no);

	// �w�b�_
	if(no == 0)
	{
		SavWriteFlash(0, 'A');
		SavWriteFlash(1, 'P');
		SavWriteFlash(2, SIORI_TYPE_FLASH);
	}

	// �f�[�^
	SavWriteFlash(adr++, 'S');
	SavWriteFlash(adr++, 'H');

	p = (u8*)&Nv;
	for(i=0; i<sizeof(ST_NV); i++)
	{
		SavWriteFlash(adr++, *p++);
	}

	p = (u8*)&Txt;
	for(i=0; i<sizeof(ST_TXT); i++)
	{
		SavWriteFlash(adr++, *p++);
	}

	p = (u8*)&Cur;
	for(i=0; i<sizeof(ST_CUR); i++)
	{
		SavWriteFlash(adr++, *p++);
	}

	p = (u8*)&Img;
	for(i=0; i<sizeof(ST_IMG); i++)
	{
		SavWriteFlash(adr++, *p++);
	}

	p = (u8*)&Bgm;
	for(i=0; i<sizeof(ST_BGM); i++)
	{
		SavWriteFlash(adr++, *p++);
	}

	p = (u8*)&Se;
	for(i=0; i<sizeof(ST_SE); i++)
	{
		SavWriteFlash(adr++, *p++);
	}
}
//---------------------------------------------------------------------------
void SioriSaveSramHeader(void)
{
	// �w�b�_
	SavWriteSram(0, 'A');
	SavWriteSram(1, 'P');
	SavWriteSram(2, SIORI_TYPE_SRAM);
}
//---------------------------------------------------------------------------
void SioriSaveSramData(s32 no)
{
	s32 adr = 0x1000 * no + 16;
	u32 i;
	u8* p;

	TRACE("[SioriSaveSramData]\n", no);

	// �f�[�^
	SavWriteSram(adr++, 'S');
	SavWriteSram(adr++, 'H');

	p = (u8*)&Nv;
	for(i=0; i<sizeof(ST_NV); i++)
	{
		SavWriteSram(adr++, *p++);
	}

	p = (u8*)&Txt;
	for(i=0; i<sizeof(ST_TXT); i++)
	{
		SavWriteSram(adr++, *p++);
	}

	p = (u8*)&Cur;
	for(i=0; i<sizeof(ST_CUR); i++)
	{
		SavWriteSram(adr++, *p++);
	}

	p = (u8*)&Img;
	for(i=0; i<sizeof(ST_IMG); i++)
	{
		SavWriteSram(adr++, *p++);
	}

	p = (u8*)&Bgm;
	for(i=0; i<sizeof(ST_BGM); i++)
	{
		SavWriteSram(adr++, *p++);
	}

	p = (u8*)&Se;
	for(i=0; i<sizeof(ST_SE); i++)
	{
		SavWriteSram(adr++, *p++);
	}
}
//---------------------------------------------------------------------------
// �ǂݍ��݂�SRAM, FLASH����
void SioriLoad(s32 no)
{
	TRACE("\n[SioriLoad:%x]\n", no);

	u32 i;
	u8* p;

	// �f�[�^
	s32 adr = 0x1000 * no + 16 + 2;

	p = (u8*)&Nv;
	for(i=0; i<sizeof(ST_NV); i++)
	{
		*p++ = SavReadSram(adr++);
	}

	p = (u8*)&Txt;
	for(i=0; i<sizeof(ST_TXT); i++)
	{
		*p++ = SavReadSram(adr++);
	}

	p = (u8*)&Cur;
	for(i=0; i<sizeof(ST_CUR); i++)
	{
		*p++ = SavReadSram(adr++);
	}

	p = (u8*)&Img;
	for(i=0; i<sizeof(ST_IMG); i++)
	{
		*p++ = SavReadSram(adr++);
	}

	p = (u8*)&Bgm;
	for(i=0; i<sizeof(ST_BGM); i++)
	{
		*p++ = SavReadSram(adr++);
	}

	p = (u8*)&Se;
	for(i=0; i<sizeof(ST_SE); i++)
	{
		*p++ = SavReadSram(adr++);
	}
}
//---------------------------------------------------------------------------
char* SioriGetTitle(s32 no)
{
	if(SioriIsItem(no) == false)
	{
		return "�|�|�|�|�|�|�|�|�|�|�|";
	}

	return (char*)SavGetPointer(0x1000 * no + 16 + 2 + sizeof(ST_NV) + (u32)&Txt.title - (u32)&Txt);
}
//---------------------------------------------------------------------------
// �S�ẴZ�[�u�f�[�^�̊��ǃr�b�g��OR�ŎZ�o
void SioriLoadNvRead(void)
{
	u32 i, j;

	for(i=0; i<SIORI_MAX_CNT; i++)
	{
		if(SioriIsItem(i) == false)
		{
			continue;
		}

		u8* s = SavGetPointer(0x1000 * i + 16 + 2 + (u32)&Nv.read - (u32)&Nv);

		for(j=0; j<sizeof(Nv.read); j++)
		{
			Nv.read[j] |= *s++;
		}
	}
}
//---------------------------------------------------------------------------
bool SioriIsExist(void)
{
	if(SavReadSram(0) != 'A') return false;
	if(SavReadSram(1) != 'P') return false;

	return true;
}
//---------------------------------------------------------------------------
bool SioriIsItem(s32 no)
{
	if(SavReadSram(0x1000 * no + 16) != 'S') return false;
	if(SavReadSram(0x1000 * no + 17) != 'H') return false;

	return true;
}
