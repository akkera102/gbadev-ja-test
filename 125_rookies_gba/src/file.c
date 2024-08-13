#include "file.h"
#include "libmy/gbfs.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void FileInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetScn(char* p)
{
	char buf[20];
	_Sprintf(buf, "%s.scn", p);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetLz7(char* p)
{
	char buf[20];
	_Sprintf(buf, "%s.lz7", p);

	return GbfsGetSafePointer(buf);
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
EWRAM_CODE u8* FileGetSnd(char* p)
{
	char buf[20];
	_Sprintf(buf, "%s.snd", p);

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
EWRAM_CODE s32 FileGetSize(void)
{
	return GbfsGetFileSize();
}
