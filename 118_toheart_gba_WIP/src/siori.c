#include "siori.h"
#include "libmy/bak.h"

#include "nv.h"
#include "text.h"
#include "img.h"
#include "bgm.h"

#include "se.h"
#include "log.h"


// �t���O�@�@�@0x0000 - 0x0FFF
// �f�[�^�P�@�@0x1000 - 0x1FFF
// �f�[�^�Q�@�@0x2000 - 0x2FFF
// �i�����j
// �f�[�^�W�@�@0x9000 - 0x9FFF


//---------------------------------------------------------------------------
// ��O�Q��
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

	TRACEOUT("[SioriSize:%x]\n", Siori.size);
	_ASSERT(Siori.size < SIORI_MAX_SIZE);

	// ����N��
	if(SioriIsInit() == FALSE)
	{
		if(BakIsFlash() == TRUE)
		{
			Siori.id = BakGetId();
		}

		BakEraseSector(0);
		BakSeek(0);
		BakWrite('T');
		BakWrite('H');
		BakWrite(Siori.id);
	}
	else
	{
		Siori.id = BakRead2(2);
		BakSetId(Siori.id);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriSave(u32 no)
{
	TRACEOUT("[SioriSave:%x]\n", no);
	_ASSERT(no < SIORI_MAX_CNT);

	u32 i;
	u8* p;

	// �t���O
	// TODO
	// BakEraseSector(0);
//		BakSeek(0);
//		BakWrite('T');
//		BakWrite('H');
//		BakWrite(Siori.type);

	// �f�[�^
	BakEraseSector(1 + no);
	BakSeek(0x1000 + 0x1000 * no);
	BakWrite('S');
	BakWrite('I');

	p = (u8*)&Nv;
	for(i=0; i<sizeof(ST_NV); i++)
	{
		BakWrite(*p++);
	}

	p = (u8*)&Text;
	for(i=0; i<sizeof(ST_TEXT); i++)
	{
		BakWrite(*p++);
	}

	p = (u8*)&Img;
	for(i=0; i<sizeof(ST_IMG); i++)
	{
		BakWrite(*p++);
	}

	p = (u8*)&Bgm;
	for(i=0; i<sizeof(ST_BGM); i++)
	{
		BakWrite(*p++);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriLoad(u32 no)
{
	TRACEOUT("[SioriLoad:%x]\n", no);

	if(SioriIsItem(no) == FALSE)
	{
		TRACEOUT("[Failure]\n");
		return FALSE;
	}

	u32 i;
	u8* p;

	// �t���O
	BakSeek(0);
	// TODO

	// �f�[�^
	BakSeek(0x1000 + 0x1000 * no + 2);

	p = (u8*)&Nv;
	for(i=0; i<sizeof(ST_NV); i++)
	{
		*p++ = BakRead();
	}

	p = (u8*)&Text;
	for(i=0; i<sizeof(ST_TEXT); i++)
	{
		*p++ = BakRead();
	}

	p = (u8*)&Img;
	for(i=0; i<sizeof(ST_IMG); i++)
	{
		*p++ = BakRead();
	}

	p = (u8*)&Bgm;
	for(i=0; i<sizeof(ST_BGM); i++)
	{
		*p++ = BakRead();
	}

	return TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SioriLoadFlag(void)
{
	// TODO ���ʃt���O
	TRACEOUT("[SioriLoadFlag]");
}
//---------------------------------------------------------------------------
EWRAM_CODE char* SioriGetStr(u32 no)
{
	if(SioriIsItem(no) == FALSE)
	{
		return "�|�|�|�|�|�|�|�|�|�|�|";
	}

	BakSeek(0x1000 + 0x1000 * no + 2 + sizeof(ST_NV) + sizeof(ST_TEXT) - TEXT_SIORI_SIZE);

	return (char*)BakGetPointer();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsInit(void)
{
	BakSeek(0);

	if(BakRead() != 'T') return FALSE;
	if(BakRead() != 'H') return FALSE;

	return TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SioriIsItem(u32 no)
{
	BakSeek(0x1000 + 0x1000 * no);

	if(BakRead() != 'S') return FALSE;
	if(BakRead() != 'I') return FALSE;

	return TRUE;
}
