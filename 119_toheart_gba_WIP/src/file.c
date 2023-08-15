#include "file.h"
#include "libmy/gbfs.h"


//---------------------------------------------------------------------------
ROM_DATA char* FileMusTable[FILE_MAX_BGM_CNT] = {
	"th00.bin",		// 0
	"th22.bin",		// 1
	"th02.bin",
	"th03.bin",
	"th04.bin",
	"th05a.bin",	// 5
	"th06.bin",
	"th07.bin",
	"th08.bin",
	"th09.bin",
	"th10.bin",		// 10
	"th11a.bin",
	"th12.bin",
	"th13.bin",
	"th14a.bin",
	"th15.bin",		// 15
	"th16.bin",
	"th17.bin",
	"th18.bin",
	"th19.bin",
	"th20.bin",		// 20
	"th21.bin",
	"th22.bin",
	"th23.bin",
	"th24.bin",
	"th25.bin",		// 25
	"th26.bin",
	"th27.bin",
	"th28.bin",
	"th29.bin",
	"th30.bin",		// 30
	"th31.bin",
	"th32.bin",
	"th33.bin",
};


//---------------------------------------------------------------------------
EWRAM_CODE void FileInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetScn(u32 no)
{
	char buf[20];
	_Sprintf(buf, "%04X.txt", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetBg(u32 no)
{
	u32 m = DivMod(no, 50);
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
	_ASSERT(no < FILE_MAX_BGM_CNT);

	return GbfsGetSafePointer((char*)FileMusTable[no]);
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
