#include "siori.h"
#include "libmy/sav.h"
#include "cur.h"
#include "nv.h"
#include "txt.h"
#include "img.h"
#include "bgm.h"
#include "se.h"


// ヘッダ　　　0x0000 - 0x000F
// データ１　　0x0010 - 0x1FFF
// データ２　　0x1010 - 0x2FFF
// （中略）
// データ８　　0x7010 - 0x7FFF


//---------------------------------------------------------------------------
// 例外参照
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
	// ヘッダ
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

	// ヘッダ
	if(no == 0)
	{
		SavWriteFlash(0, 'A');
		SavWriteFlash(1, 'P');
		SavWriteFlash(2, SIORI_TYPE_FLASH);
	}

	// データ
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
	// ヘッダ
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

	// データ
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
// 読み込みはSRAM, FLASH共通
void SioriLoad(s32 no)
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
		return "－－－－－－－－－－－";
	}

	return (char*)SavGetPointer(0x1000 * no + 16 + 2 + sizeof(ST_NV) + (u32)&Txt.title - (u32)&Txt);
}
//---------------------------------------------------------------------------
// 全てのセーブデータの既読ビットをORで算出
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
