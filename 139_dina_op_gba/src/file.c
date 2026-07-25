#include "file.h"
#include "libmy/gbfs.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void FileInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
u16* FileGetImg(s32 no)
{
	char buf[20];
	_Sprintf(buf, "f%05d.img", no);

	return GbfsGetPointer(buf);
}
//---------------------------------------------------------------------------
u16* FileGetPal(s32 no)
{
	char buf[20];
	_Sprintf(buf, "f%05d.pal", no);

	return GbfsGetPointer(buf);
}
//---------------------------------------------------------------------------
u8* FileGetMus(void)
{
	return GbfsGetSafePointer("DIN_OP00.8ad");
}
//---------------------------------------------------------------------------
s32 FileGetSize(void)
{
	return GbfsGetFileSize();
}
