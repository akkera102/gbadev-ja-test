#include "file.h"
#include "libmy/gbfs.h"


//---------------------------------------------------------------------------
ROM_DATA char* FileMusTable[FILE_MAX_BGM_CNT] = {
	"th00.bin",		// 0
	"th22.bin",		// 1	ダブり
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
EWRAM_CODE u8* FileGetBgS(u32 no)
{
	u32 m = DivMod(no, 50);
	u32 d = Div(no, 50);

	char buf[20];
	_Sprintf(buf, "S%02dD.img", m);

	switch(d)
	{
	case 0: buf[3] = 'D'; break;	// 朝
	case 1: buf[3] = 'E'; break;	// 夕
	case 2: buf[3] = 'N'; break;	// 曇
	case 3: buf[3] = 'X'; break;	// 夜
	case 4: buf[3] = 'Z'; break;	// オカルト研究会用

	default:
		SystemError("[Err] FileGetBgS m=%d d=%d\n", m, d);
		break;
	}

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetBgV(u32 no)
{
	char buf[20];
	_Sprintf(buf, "V%02X.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetBgH(u32 no)
{
	char buf[20];
	_Sprintf(buf, "H%02X.img", no);

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
EWRAM_CODE u8* FileGetMus(u32 no)
{
	_ASSERT(no < FILE_MAX_BGM_CNT);

	return GbfsGetSafePointer(FileMusTable[no]);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetSe(u32 no)
{
	char buf[20];
	_Sprintf(buf, "TH_VD%02d.raw", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetTime(u32 no)
{
	char buf[20];
	_Sprintf(buf, "OC_%02d.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetTimeMask(void)
{
	return GbfsGetSafePointer("OC_00_M.img");
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetMonth(u32 no)
{
	char buf[20];
	_Sprintf(buf, "CMON_%02d.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
// 1桁表示
EWRAM_CODE u8* FileGetDay(u32 no)
{
	char buf[20];
	_Sprintf(buf, "CLNO_%02d.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
// 2桁表示
EWRAM_CODE u8* FileGetDay2(u32 no)
{
	char buf[20];
	_Sprintf(buf, "CSNO_%02d.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetWeek(u32 no)
{
	char buf[20];
	_Sprintf(buf, "CWEEK_%02d.img", no);

	return GbfsGetSafePointer(buf);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* FileGetName(char* p)
{
	return GbfsGetSafePointer(p);
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 FileGetSize(void)
{
	return GbfsGetFileSize();
}
