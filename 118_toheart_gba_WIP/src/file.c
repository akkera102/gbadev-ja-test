#include "file.h"
#include "libmy/gbfs.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void FileInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetTxt(u32 no)
{
	char buf[20];
	_Sprintf(buf, "%04X.txt", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetBg(u32 no)
{
	u32 m = Mod(no, 50);
	u32 d = Div(no, 50);

	char buf[20];
	_Sprintf(buf, "S%02dD.img", m);

	switch(d)
	{
	case 0: buf[3] = 'D'; break;	// ’©
	case 1: buf[3] = 'E'; break;	// —[
	case 2: buf[3] = 'N'; break;	// “Ü
	case 3: buf[3] = 'X'; break;	// –é

	default:
		SystemError("[Err] FileGetBg m=%d d=%d\n", m, d);
		break;
	}

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetChr(u32 no)
{
	char buf[20];
	_Sprintf(buf, "C%04X.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetChrMask(u32 no)
{
	char buf[20];
	_Sprintf(buf, "C%04X_M.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetVis(u32 no)
{
	char buf[20];
	_Sprintf(buf, "V%02X.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetMus(u32 no)
{
	char buf[20];
	_Sprintf(buf, "tr_%02d.8ad", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetSe(u32 no)
{
	char buf[20];
	_Sprintf(buf, "TH_VD%02d.raw", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 FileGetSize(void)
{
	return GbfsGetFileSize();
}
