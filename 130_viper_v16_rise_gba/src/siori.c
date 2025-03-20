#include "siori.h"
#include "libmy/sav.h"
#include "nv.h"
#include "info.h"

// ヘッダ　　　0x0000 - 0x000F
// データ１　　0x0010 - 0x1FFF
// データ２　　0x1010 - 0x2FFF
// （中略）
// データ８　　0x7010 - 0x7FFF


//---------------------------------------------------------------------------
// 例外参照
extern ST_NV Nv;


//---------------------------------------------------------------------------
EWRAM_CODE void SioriInit(void)
{
	s32 size = 3 * sizeof(u16);					// u16 Nv.var配列の16, 20, 21を保存

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
	SavWriteFlash(0, 'R');
	SavWriteFlash(1, 'I');
	SavWriteFlash(2, SIORI_TYPE_FLASH);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveFlashData(s32 no)
{
	TRACE("[SioriSaveFlashData]\n", no);
	SavWriteFlashEraseSector(no);

	// ヘッダ
	if(no == 0)
	{
		SavWriteFlash(0, 'R');
		SavWriteFlash(1, 'I');
		SavWriteFlash(2, SIORI_TYPE_FLASH);
	}

	// データ
	s32 adr = 0x1000 * no + 16;

	vu16 var[3];
	vu8* p = (u8*)&var;

	var[0] = NvGetVar(16);
	var[1] = NvGetVar(20);
	var[2] = NvGetVar(21);

	SavWriteFlash(adr++, 'S');
	SavWriteFlash(adr++, 'E');

	s32 i;

	for(i=0; i<3*2; i++)
	{
		SavWriteFlash(adr++, *p++);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveSramHeader(void)
{
	// ヘッダ
	SavWriteSram(0, 'R');
	SavWriteSram(1, 'I');
	SavWriteSram(2, SIORI_TYPE_SRAM);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSaveSramData(s32 no)
{
	TRACE("[SioriSaveSramData]\n", no);

	// データ
	s32 adr = 0x1000 * no + 16;

	vu16 var[3];
	vu8* p = (u8*)&var;

	var[0] = NvGetVar(16);
	var[1] = NvGetVar(20);
	var[2] = NvGetVar(21);

	SavWriteSram(adr++, 'S');
	SavWriteSram(adr++, 'E');

	s32 i;

	for(i=0; i<3*2; i++)
	{
		SavWriteSram(adr++, *p++);
	}
}
//---------------------------------------------------------------------------
// 読み込みはSRAM, FLASH共通
EWRAM_CODE void SioriLoad(s32 no)
{
	TRACE("\n[SioriLoad:%x]\n", no);

	// データ
	s32 adr = 0x1000 * no + 16 + 2;

	vu16 var[3];
	vu8* p = (u8*)&var;

	s32 i;

	for(i=0; i<3*2; i++)
	{
		*p++ = SavReadSram(adr++);
	}

	NvSetVar(16, var[0]);
	NvSetVar(20, var[1]);
	NvSetVar(21, var[2]);
}
//---------------------------------------------------------------------------
// Nv.var[16]を取得
EWRAM_CODE u16 SioriGetVar(s32 no)
{
	if(SioriIsItem(no) == false)
	{
		return 0xffff;
	}

	s32 adr = 0x1000 * no + 16 + 2;

	u16 ret  = SavReadSram(adr++);
	    ret |= SavReadSram(adr++) <<  8;

	return ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsExist(void)
{
	if(SavReadSram(0) != 'R') return false;
	if(SavReadSram(1) != 'I') return false;

	return true;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsItem(s32 no)
{
	if(SavReadSram(0x1000 * no + 16) != 'S') return false;
	if(SavReadSram(0x1000 * no + 17) != 'E') return false;

	return true;
}
