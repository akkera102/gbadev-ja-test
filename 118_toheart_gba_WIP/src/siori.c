#include "siori.h"
#include "libmy/sav.h"

#include "nv.h"
#include "text.h"
#include "img.h"
#include "bgm.h"

#include "se.h"
#include "log.h"


// フラグ　　　0x0000 - 0x0FFF
// データ１　　0x1000 - 0x1FFF
// データ２　　0x2000 - 0x2FFF
// （中略）
// データ８　　0x9000 - 0x9FFF


//---------------------------------------------------------------------------
// 例外参照
extern ST_NV   Nv;
extern ST_TEXT Text;
extern ST_IMG  Img;
extern ST_BGM  Bgm;


//---------------------------------------------------------------------------
ST_SIORI Siori;


//---------------------------------------------------------------------------
EWRAM_CODE void SioriInit(void)
{
	_Memset(&Siori, 0x00, sizeof(ST_SIORI));

	Siori.size = 2 + sizeof(ST_NV) + sizeof(ST_TEXT) + sizeof(ST_IMG) + sizeof(ST_BGM);

	TRACE("[SioriSize:%x]\n", Siori.size);
	_ASSERT(Siori.size < SIORI_MAX_SIZE);


	if(SioriIsInit() == TRUE)
	{
		return;
	}

	// 初回設定
	if(SavIsFlash() == TRUE)
	{
		SavFlashEraseSector(0);
		SavFlashWrite(0, 'T');
		SavFlashWrite(1, 'H');
		SavFlashWrite(2, SIORI_TYPE_FLASH);
	}
	else
	{
		SavFlashWrite(0, 'T');
		SavFlashWrite(1, 'H');
		SavFlashWrite(2, SIORI_TYPE_SRAM);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSave(u32 no)
{
	TRACE("[SioriSave:%x]\n", no);
	_ASSERT(no < SIORI_MAX_CNT);

	if(SavSramRead(2) == SIORI_TYPE_SRAM)
	{
		SioriSaveSram(no);
	}
	else
	{
		SioriSaveFlash(no);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void  SioriSaveSram(u32 no)
{
	u32 adr = 0x1000 + 0x1000 * no;
	u32 i;
	u8* p;

	SavSramWrite(0, 'T');
	SavSramWrite(1, 'H');
	SavSramWrite(2, SIORI_TYPE_SRAM);

	// フラグ
	// TODO

	// データ
	SavSramWrite(adr++, 'S');
	SavSramWrite(adr++, 'I');

	p = (u8*)&Nv;
	for(i=0; i<sizeof(ST_NV); i++)
	{
		SavSramWrite(adr++, *p++);
	}

	p = (u8*)&Text;
	for(i=0; i<sizeof(ST_TEXT); i++)
	{
		SavSramWrite(adr++, *p++);
	}

	p = (u8*)&Img;
	for(i=0; i<sizeof(ST_IMG); i++)
	{
		SavSramWrite(adr++, *p++);
	}

	p = (u8*)&Bgm;
	for(i=0; i<sizeof(ST_BGM); i++)
	{
		SavSramWrite(adr++, *p++);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void  SioriSaveFlash(u32 no)
{
	u32 adr = 0x1000 + 0x1000 * no;
	u32 i;
	u8* p;

	SavFlashEraseSector(0);
	SavFlashWrite(0, 'T');
	SavFlashWrite(1, 'H');
	SavFlashWrite(2, SIORI_TYPE_FLASH);

	// フラグ
	// TODO

	// データ
	SavFlashEraseSector(1 + no);
	SavFlashWrite(adr++, 'S');
	SavFlashWrite(adr++, 'I');

	p = (u8*)&Nv;
	for(i=0; i<sizeof(ST_NV); i++)
	{
		SavFlashWrite(adr++, *p++);
	}

	p = (u8*)&Text;
	for(i=0; i<sizeof(ST_TEXT); i++)
	{
		SavFlashWrite(adr++, *p++);
	}

	p = (u8*)&Img;
	for(i=0; i<sizeof(ST_IMG); i++)
	{
		SavFlashWrite(adr++, *p++);
	}

	p = (u8*)&Bgm;
	for(i=0; i<sizeof(ST_BGM); i++)
	{
		SavFlashWrite(adr++, *p++);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriLoad(u32 no)
{
	TRACE("[SioriLoad:%x]\n", no);

	if(SioriIsItem(no) == FALSE)
	{
		TRACE("[Failure]\n");
		return FALSE;
	}

	u32 i;
	u8* p;

	// フラグ
	// TODO

	// データ
	u32 adr = 0x1000 + 0x1000 * no + 2;

	p = (u8*)&Nv;
	for(i=0; i<sizeof(ST_NV); i++)
	{
		*p++ = SavSramRead(adr++);
	}

	p = (u8*)&Text;
	for(i=0; i<sizeof(ST_TEXT); i++)
	{
		*p++ = SavSramRead(adr++);
	}

	p = (u8*)&Img;
	for(i=0; i<sizeof(ST_IMG); i++)
	{
		*p++ = SavSramRead(adr++);
	}

	p = (u8*)&Bgm;
	for(i=0; i<sizeof(ST_BGM); i++)
	{
		*p++ = SavSramRead(adr++);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriLoadFlag(void)
{
	// TODO 共通フラグ
	TRACE("[SioriLoadFlag]");
}
//---------------------------------------------------------------------------
EWRAM_CODE char* SioriGetStr(u32 no)
{
	if(SioriIsItem(no) == FALSE)
	{
		return "－－－－－－－－－－－";
	}

	return (char*)SavGetPointer(0x1000 + 0x1000 * no + 2 + sizeof(ST_NV) + sizeof(ST_TEXT) - TEXT_SIORI_SIZE);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsInit(void)
{
	if(SavSramRead(0) != 'T') return FALSE;
	if(SavSramRead(1) != 'H') return FALSE;

	return TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsItem(u32 no)
{
	if(SavSramRead(0x1000 + 0x1000 * no + 0) != 'S') return FALSE;
	if(SavSramRead(0x1000 + 0x1000 * no + 1) != 'I') return FALSE;

	return TRUE;
}
