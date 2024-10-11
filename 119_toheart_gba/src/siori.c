#include "siori.h"
#include "libmy/sav.h"
#include "nv.h"
#include "txt.h"
#include "img.h"
#include "bgm.h"
#include "se.h"

// SRAM
// �w�b�_�@�@�@0x0000 - 0x0004
// �f�[�^�P�@�@0x0010 - 0x0FFF
// �f�[�^�Q�@�@0x1010 - 0x1FFF
// �i�����j
// �f�[�^�W�@�@0x7010 - 0x7FFF


// FLASH (CUBIC STYLE���̂ݑΉ�)
// �w�b�_�@�@�@0x0000 - 0x0004
// �f�[�^�P�@�@0x1010 - 0x1FFF		+0x1000
// �f�[�^�Q�@�@0x2010 - 0x2FFF
// �i�����j
// �f�[�^�W�@�@0x8010 - 0x8FFF


//---------------------------------------------------------------------------
// ��O�Q��
extern ST_NV  Nv;
extern ST_TXT Txt;
extern ST_IMG Img;
extern ST_BGM Bgm;
extern ST_SE  Se;


//---------------------------------------------------------------------------
ST_SIORI Siori;


//---------------------------------------------------------------------------
EWRAM_CODE void SioriInit(void)
{
	_Memset(&Siori, 0x00, sizeof(ST_SIORI));

	Siori.size = 2 + sizeof(ST_NV) + sizeof(ST_TXT) + sizeof(ST_IMG) + sizeof(ST_BGM) + sizeof(ST_SE);

	TRACE("[SioriSize:%x]\n", Siori.size);
	_ASSERT(Siori.size < SIORI_MAX_SIZE);


	if(SioriIsInit() == true)
	{
		return;
	}

	// ����ݒ�
	if(SavIsFlash() == true)
	{
		TRACE("[SaveChip: Flash]\n");

		SavWriteFlashEraseSector(0);
		SavWriteFlash(0, 'T');
		SavWriteFlash(1, 'H');
		SavWriteFlash(2, SIORI_TYPE_FLASH);
		SavWriteFlash(3, 0x00);
		SavWriteFlash(4, 0x00);
	}
	else
	{
		TRACE("[SaveChip: SRAM]\n");

		SavWriteSram(0, 'T');
		SavWriteSram(1, 'H');
		SavWriteSram(2, SIORI_TYPE_SRAM);
		SavWriteSram(3, 0x00);
		SavWriteSram(4, 0x00);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSave(u32 no)
{
	TRACE("[SioriSave:%x]\n", no);
	_ASSERT(no < SIORI_MAX_CNT);

	if(SavReadSram(2) == SIORI_TYPE_FLASH)
	{
		SioriSaveFlashHeader();
		SioriSaveFlashData(no);
	}
	else
	{
		SioriSaveSramHeader();
		SioriSaveSramData(no);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSave2(void)
{
	TRACE("[SioriSave2]\n");

	if(SavReadSram(2) == SIORI_TYPE_FLASH)
	{
		SioriSaveFlashHeader();
	}
	else
	{
		SioriSaveSramHeader();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveFlashHeader(void)
{
	// �w�b�_
	SavWriteFlashEraseSector(0);
	SavWriteFlash(0, 'T');
	SavWriteFlash(1, 'H');
	SavWriteFlash(2, SIORI_TYPE_FLASH);
	SavWriteFlash(3, Nv.flag[0x50]);
	SavWriteFlash(4, Nv.flag[0x51]);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveFlashData(u32 no)
{
	// FLASH��SRAM�ƈႢ+0x1000���܂�
	no++;

	u32 adr = 0x1000 * no + 0x10;
	u32 i;
	u8* p;

	SavWriteFlashEraseSector(no);

	// �f�[�^
	SavWriteFlash(adr++, 'S');
	SavWriteFlash(adr++, 'I');

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
EWRAM_CODE void SioriSaveSramHeader(void)
{
	// �w�b�_
	SavWriteSram(0, 'T');
	SavWriteSram(1, 'H');
	SavWriteSram(2, SIORI_TYPE_SRAM);
	SavWriteSram(3, Nv.flag[0x50]);
	SavWriteSram(4, Nv.flag[0x51]);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveSramData(u32 no)
{
	u32 adr = 0x1000 * no + 0x10;
	u32 i;
	u8* p;

	// �f�[�^
	SavWriteSram(adr++, 'S');
	SavWriteSram(adr++, 'I');

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
// SRAM FLASH����
EWRAM_CODE bool SioriLoad(u32 no)
{
	TRACE("[SioriLoad:%x]\n", no);

	if(SioriIsItem(no) == false)
	{
		TRACE("[Failure]\n");
		return false;
	}

	if(SavReadSram(2) == SIORI_TYPE_FLASH)
	{
		no++;
	}

	u32 i;
	u8* p;

	// �f�[�^
	u32 adr = 0x1000 * no + 0x10 + 2;

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

	// �t���O
	SioriLoadFlag();

	return true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriLoadFlag(void)
{
	TRACE("[SioriLoadFlag]\n");

	Nv.flag[0x50] = SavReadSram(3);
	Nv.flag[0x51] = SavReadSram(4);
}
//---------------------------------------------------------------------------
EWRAM_CODE char* SioriGetStr(u32 no)
{
	if(SioriIsItem(no) == false)
	{
		return "�|�|�|�|�|�|�|�|�|�|�|";
	}

	if(SavReadSram(2) == SIORI_TYPE_FLASH)
	{
		no++;
	}

	return (char*)SavGetPointer(0x1000 * no + 0x10 + 2 + sizeof(ST_NV) + sizeof(ST_TXT) - TXT_SIORI_SIZE);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsInit(void)
{
	if(SavReadSram(0) != 'T') return false;
	if(SavReadSram(1) != 'H') return false;

	return true;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsItem(u32 no)
{
	if(SavReadSram(2) == SIORI_TYPE_FLASH)
	{
		no++;
	}

	if(SavReadSram(0x1000 * no + 0x10 + 0) != 'S') return false;
	if(SavReadSram(0x1000 * no + 0x10 + 1) != 'I') return false;

	return true;
}
