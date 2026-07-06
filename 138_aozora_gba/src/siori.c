#include "siori.h"
#include "libmy/sav.h"
#include "nv.h"
#include "txt.h"
#include "img.h"
#include "mus.h"
#include "menu.h"
#include "seen.h"
#include "snd.h"


// ヘッダ　　　0x0000 - 0x000F
// エンド　　　0x0010 - 0x001F
// 既読　　　　0x0020 - 0x1FFF
// データ１　　0x2000 - 0x20FF
// データ２　　0x2100 - 0x21FF
// データ３　　0x2200 - 0x22FF
// データ４　　0x2300 - 0x23FF
// データ５　　0x2400 - 0x24FF
// （中略）
// データ４０　0x4700 - 0x47FF

//---------------------------------------------------------------------------
// 例外参照
extern ST_NV   Nv;
extern ST_TXT  Txt;
extern ST_IMG  Img;
extern ST_MUS  Mus;
extern ST_SND  Snd;
extern ST_SEEN Seen;
extern ST_MENU Menu;

//---------------------------------------------------------------------------
void SioriInit(void)
{
	if(SioriIsHeader() == true)
	{
		return;
	}

	SioriSaveHeader();
}
//---------------------------------------------------------------------------
void SioriSaveHeader(void)
{
	TRACE("SioriSaveHeader\n");

	s32 i;

	for(i=0; i<0x4800; i++)
	{
		SavWriteSram(i, 0x00);
	}

	SavWriteSram(0, 'T');
	SavWriteSram(1, 'C');
	SavWriteSram(2, 0x02);		// Ver
	SavWriteSram(3, 0x01);		// SRAM
}
//---------------------------------------------------------------------------
void SioriSaveItem(s32 no)
{
	TRACE("[SioriSave:%x]\n", no);

	SioriSaveLast();
	SioriSaveRead();

	// データ
	s32 i;
	s32 adr = SIORI_BASE_ITEM_ADR + SIORI_MAX_ITEM_SIZE * no;
	SavWriteSram(adr++, 'H');
	SavWriteSram(adr++, 'K');

	// TXT
	for(i=0; i<TXT_MAX_SIORI_LEN; i++)
	{
		SavWriteSram(adr++, Txt.siori[i]);
	}
	SavWriteSram(adr++, Txt.base);
	SavWriteSram(adr++, Txt.read);

	// SEEN
	for(i=0; i<SEEN_MAX_FL_CNT; i++)
	{
		SavWriteSram(adr++, Seen.fl[i]);
	}
	for(i=0; i<SEEN_MAX_FW_CNT; i++)
	{
		SavWriteSram(adr++, Seen.fw[i]);
	}

	// NV
	SavWriteSram16(adr+0, Nv.no);
	SavWriteSram16(adr+2, Nv.str);
	SavWriteSram16(adr+4, Nv.set);
	SavWriteSram16(adr+6, Nv.idx);
	SavWriteSram16(adr+8, Nv.bit);
	adr += 10;

	SavWriteSram(adr++, Nv.act);
	SavWriteSram(adr++, Nv.isPass);
	SavWriteSram(adr++, Nv.mes);
	SavWriteSram(adr++, Nv.navi);
	SavWriteSram(adr++, Nv.naviCnt);

	// MUS
	SavWriteSram(adr++, Mus.no);
	SavWriteSram(adr++, Mus.isLoop);

	// SND
	SavWriteSram(adr++, Snd.no);
	SavWriteSram(adr++, Snd.isLoop);

	// IMG
	SavWriteSram16(adr+0, Img.bg);
	SavWriteSram16(adr+2, Img.chr);
	adr += 4;

	SavWriteSram(adr++, Img.eff);
	SavWriteSram(adr++, Img.fade);


	TRACE("save size:%d\n", adr - (SIORI_BASE_ITEM_ADR + SIORI_MAX_ITEM_SIZE * no));
	_ASSERT(adr - (SIORI_BASE_ITEM_ADR + SIORI_MAX_ITEM_SIZE * no) < SIORI_MAX_ITEM_SIZE);
}
//---------------------------------------------------------------------------
void SioriLoadItem(s32 no)
{
	TRACE("[SioriLoad:%x]\n", no);

	// データ
	s32 i;
	s32 adr = SIORI_BASE_ITEM_ADR + SIORI_MAX_ITEM_SIZE * no;
	adr += 2;

	// TXT
	for(i=0; i<TXT_MAX_SIORI_LEN; i++)
	{
		Txt.siori[i] = SavReadSram(adr++);
	}
	Txt.base = SavReadSram(adr++);
	Txt.read = SavReadSram(adr++);

	// SEEN
	for(i=0; i<SEEN_MAX_FL_CNT; i++)
	{
		Seen.fl[i] = SavReadSram(adr++);
	}
	for(i=0; i<SEEN_MAX_FW_CNT; i++)
	{
		Seen.fw[i] = SavReadSram(adr++);
	}

	// NV
	Nv.no  = SavReadSram16(adr+0);
	Nv.str = SavReadSram16(adr+2);
	Nv.set = SavReadSram16(adr+4);
	Nv.idx = SavReadSram16(adr+6);
	Nv.bit = SavReadSram16(adr+8);
	adr += 10;

	Nv.act     = SavReadSram(adr++);
	Nv.isPass  = SavReadSram(adr++);
	Nv.mes     = SavReadSram(adr++);
	Nv.navi    = SavReadSram(adr++);
	Nv.naviCnt = SavReadSram(adr++);

	// MUS
	Mus.no     = SavReadSram(adr++);
	Mus.isLoop = SavReadSram(adr++);

	// SND
	Snd.no     = SavReadSram(adr++);
	Snd.isLoop = SavReadSram(adr++);

	// IMG
	Img.bg  = SavReadSram16(adr+0);
	Img.chr = SavReadSram16(adr+2);
	adr += 4;

	Img.eff  = SavReadSram(adr++);
	Img.fade = SavReadSram(adr++);

	SioriLoadLast();
	SioriLoadRead();
}
//---------------------------------------------------------------------------
void SioriSaveLast(void)
{
	TRACE("[SioriSaveLast]\n");

	s32 i;

	for(i=8; i<=12; i++)
	{
		SavWriteSram(0x10+(i-8), Seen.fw[i]);
	}
}
//---------------------------------------------------------------------------
void SioriLoadLast(void)
{
	TRACE("[SioriLoadLast]\n");

	s32 i;

	for(i=8; i<=12; i++)
	{
		Seen.fw[i] = SavReadSram(0x10+(i-8));
	}
}
//---------------------------------------------------------------------------
void SioriSaveRead(void)
{
	TRACE("[SioriSaveRead]\n");

	_ASSERT(SEEN_MAX_READ_SIZE < 0x2000 - 0x20);

	s32 i;

	for(i=0; i<SEEN_MAX_READ_SIZE; i++)
	{
		SavWriteSram(0x20+i, Seen.read[i]);
	}
}
//---------------------------------------------------------------------------
void SioriLoadRead(void)
{
	TRACE("[SioriLoadRead]\n");

	s32 i;

	for(i=0; i<SEEN_MAX_READ_SIZE; i++)
	{
		Seen.read[i] = SavReadSram(0x20+i);
	}
}
//---------------------------------------------------------------------------
char* SioriGetTitle(s32 no)
{
	static const char s[] = "－－－－－－－－－－－－－－－";

	if(SioriIsItem(no) == false)
	{
		return (char*)s;
	}

	return (char*)SavGetPointer(SIORI_BASE_ITEM_ADR + SIORI_MAX_ITEM_SIZE * no + 2);
}
//---------------------------------------------------------------------------
bool SioriIsHeader(void)
{
	if(SavReadSram(0) != 'T') return false;
	if(SavReadSram(1) != 'C') return false;
	if(SavReadSram(2) != 0x2) return false;		// Ver

	return true;
}
//---------------------------------------------------------------------------
bool SioriIsItem(s32 no)
{
	if(SavReadSram(SIORI_BASE_ITEM_ADR + SIORI_MAX_ITEM_SIZE * no + 0) != 'H') return false;
	if(SavReadSram(SIORI_BASE_ITEM_ADR + SIORI_MAX_ITEM_SIZE * no + 1) != 'K') return false;

	return true;
}
