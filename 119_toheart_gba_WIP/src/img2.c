#include "img.h"
#include "img2.h"
#include "libmy/mode3.h"
#include "libmy/fade.h"
#include "file.h"

//---------------------------------------------------------------------------
extern ST_IMG Img;


//---------------------------------------------------------------------------
EWRAM_CODE void ImgDirectCrop(u32 no, u32 x, u32 y)
{
	ST_FILE_IMG_HEADER* p = (ST_FILE_IMG_HEADER*)FileGetBg(no);

	Mode3DrawCrop(x, y, p->cx, p->cy, (u16*)(p + 1));
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDirectClip(u32 no, u32 x, u32 y, u32 gx, u32 gy, u32 gs)
{
	ST_FILE_IMG_HEADER* p = (ST_FILE_IMG_HEADER*)FileGetBg(no);

	Mode3DrawClip(x, y, p->cx, p->cy, gx, gy, gs, (u16*)(p + 1));
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDirectBlend(u32 no, u32 x, u32 y)
{
	ST_FILE_IMG_HEADER* p = (ST_FILE_IMG_HEADER*)FileGetChr(no);

	Mode3DrawBlend(x, y, p->cx, p->cy, (u16*)(p + 1), FileGetChrMask(no));
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDirectLine(u32 no, u32 cnt)
{
	ST_FILE_IMG_HEADER* p  = (ST_FILE_IMG_HEADER*)FileGetBg(no);

//	Mode3DrawLine(cnt, (u16*)(p + 1));
}
//---------------------------------------------------------------------------
EWRAM_CODE void ImgDirectFill(u32 col)
{
	Mode3DrawFill(col);
}
