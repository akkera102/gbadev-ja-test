#include "file.h"
#include "libmy/gbfs.h"
#include "info.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void FileInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
u8* FileGetScn(s32 no)
{
	char buf[20];
	_Sprintf(buf, "SCN%03d.bin", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetImg(s32 no)
{
	char buf[20];
	_Sprintf(buf, "img%03d.bin", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetMsk(s32 no)
{
	char buf[20];
	_Sprintf(buf, "msk%02d.bin", InfoGetMskNo(no));

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetEff(s32 no)
{
	char buf[20];
	_Sprintf(buf, "CLS%02d.bin", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetBgm(s32 no)
{
	char buf[20];
	_Sprintf(buf, "bgm%02d.bin", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetFmx(s32 no)
{
	char buf[20];
	_Sprintf(buf, "fmx%02d.bin", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
s32 FileGetSize(void)
{
	return GbfsGetFileSize();
}
