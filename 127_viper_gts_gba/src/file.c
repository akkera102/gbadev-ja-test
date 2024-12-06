#include "file.h"
#include "libmy/gbfs.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void FileInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE u16* FileGetImg(char* p, s32 no)
{
	char buf[20];
	_Sprintf(buf, "%s_%02d.img", p, no);

	return GbfsGetPointer(buf);				// no safe!
}
//---------------------------------------------------------------------------
EWRAM_CODE u16* FileGetDat(char* p)
{
	char buf[20];
	_Sprintf(buf, "%s.dat", p);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetScn(char* p)
{
	char buf[20];
	_Sprintf(buf, "%s.scn", p);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetRaw(char* p)
{
	char buf[20];
	_Sprintf(buf, "%s.raw", p);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetBgm(s32 no)
{
	char buf[20];
	_Sprintf(buf, "bgm%02d.bin", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 FileGetSize(void)
{
	return GbfsGetFileSize();
}
