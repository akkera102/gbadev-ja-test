#include "file.h"
#include "libbios/swi.h"
#include "libmy/gbfs.h"


//---------------------------------------------------------------------------
ST_FILE File EWRAM_BSS;


//---------------------------------------------------------------------------
void FileInit(void)
{
	_Memset(&File, 0x00, sizeof(ST_FILE));
}
//---------------------------------------------------------------------------
u8* FileGetBg(s32 no)
{
	char buf[20];
	_Sprintf(buf, "B%03d.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetChr(s32 no)
{
	char buf[20];
	_Sprintf(buf, "A%03d.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetMsk(s32 no)
{
	char buf[20];
	_Sprintf(buf, "A%03d.msk", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetMus(s32 no)
{
	char buf[20];
	_Sprintf(buf, "M%03d.ulc", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetSnd(s32 no)
{
	char buf[20];
	_Sprintf(buf, "S%03d.raw", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
char* FileGetTxt(s32 no)
{
	char buf[20];
	_Sprintf(buf, "T%03d.bin", no);

	u32* p = GbfsGetSafePointer(buf);

	SwiLZ77UnCompWrite16bit(p, File.work);
	File.size = p[0] >> 8;

	return File.work;
}
//---------------------------------------------------------------------------
s32 FileGetTxtSize(void)
{
	return File.size;
}
//---------------------------------------------------------------------------
s32 FileGetSize(void)
{
	return GbfsGetFileSize();
}
