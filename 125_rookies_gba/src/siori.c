#include "siori.h"
#include "libmy/sav.h"
#include "nv.h"
#include "txt.h"
#include "img.h"
#include "bgm.h"
#include "Se.h"


// ヘッダ　　　0x0000 - 0x000F
// データ１　　0x0010 - 0x1FFF
// データ２　　0x1010 - 0x2FFF
// （中略）
// データ８　　0x7010 - 0x7FFF


//---------------------------------------------------------------------------
// 例外参照
extern ST_NV  Nv;
extern ST_TXT Txt;
extern ST_IMG Img;
extern ST_BGM Bgm;
extern ST_SE  Se;

//---------------------------------------------------------------------------
EWRAM_CODE void SioriInit(void)
{
	s32 size = 2 + sizeof(ST_NV) + sizeof(ST_TXT) + sizeof(ST_IMG) + sizeof(ST_BGM) + sizeof(ST_SE);

	TRACE("[SioriSize:%x]\n", size);
	_ASSERT(size < SIORI_MAX_SIZE);


	if(SioriIsExist() == true)
	{
		return;
	}

	// 初回設定
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
	// ヘッダ
	SavWriteFlashEraseSector(0);
	SavWriteFlash(0, 'K');
	SavWriteFlash(1, 'R');
	SavWriteFlash(2, SIORI_TYPE_FLASH);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveFlashData(s32 no)
{
	s32 adr = 0x1000 * no + 16;
	u32 i;
	u8* p;

	TRACE("[SioriSaveFlashData]\n", no);
	SavWriteFlashEraseSector(no);

	// ヘッダ
	if(no == 0)
	{
		SavWriteFlash(0, 'K');
		SavWriteFlash(1, 'R');
		SavWriteFlash(2, SIORI_TYPE_FLASH);
	}

	// データ
	SavWriteFlash(adr++, 'R');
	SavWriteFlash(adr++, 'O');

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
	// ヘッダ
	SavWriteSram(0, 'K');
	SavWriteSram(1, 'R');
	SavWriteSram(2, SIORI_TYPE_SRAM);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveSramData(s32 no)
{
	s32 adr = 0x1000 * no + 16;
	u32 i;
	u8* p;

	TRACE("[SioriSaveSramData]\n", no);

	// データ
	SavWriteSram(adr++, 'R');
	SavWriteSram(adr++, 'O');

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
// 読み込みはSRAM, FLASH共通
EWRAM_CODE void SioriLoad(s32 no)
{
	TRACE("\n[SioriLoad:%x]\n", no);

	u32 i;
	u8* p;

	// データ
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
EWRAM_CODE char* SioriGetStr(s32 no)
{
	if(SioriIsItem(no) == false)
	{
		return "－－－－－－－－－－－";
	}

	return (char*)SavGetPointer(0x1000 * no + 16 + 2 + sizeof(ST_NV) + sizeof(ST_TXT) - TXT_SIORI_SIZE);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsExist(void)
{
	if(SavReadSram(0) != 'K') return false;
	if(SavReadSram(1) != 'R') return false;

	return true;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsItem(s32 no)
{
	if(SavReadSram(0x1000 * no + 16) != 'R') return false;
	if(SavReadSram(0x1000 * no + 17) != 'O') return false;

	return true;
}
