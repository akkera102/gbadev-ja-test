#include "file.h"
#include "libmy/gbfs.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void FileInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetImg(char* p)
{
	char buf[20];
	_Sprintf(buf, "%s.img", p);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetMsk(char* p)
{
	char buf[20];
	_Sprintf(buf, "%s.msk", p);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetMap(s32 no)
{
	char buf[20];
	_Sprintf(buf, "map%02d.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetMus(s32 no)
{
	char buf[20];
	_Sprintf(buf, "b%02d.snd", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetSsg(s32 no)
{
	char buf[20];
	_Sprintf(buf, "ssg%02d.bin", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetFmx(s32 no)
{
	char buf[20];
	_Sprintf(buf, "fmx%02d.bin", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE char* FileGetTxt(s32 chap, s32 no)
{
	char buf[20];
	_Sprintf(buf, "%x_%02d.txt", chap, no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 FileGetSize(void)
{
	return GbfsGetFileSize();
}
