#include "img.h"
#include "libmy/mode4.arm.h"
#include "libmy/irq.arm.h"
#include "libmy/fade.h"
#include "file.h"
#include "mus.h"

//---------------------------------------------------------------------------
ST_IMG  Img;
ST_IMG2 Img2 EWRAM_BSS;

//---------------------------------------------------------------------------
void ImgInit(void)
{
	_Memset(&Img, 0x00, sizeof(ST_IMG));
	_Memset(&Img2, 0x00, sizeof(ST_IMG2));
}
//---------------------------------------------------------------------------
void ImgExec(void)
{
	switch(Img.eff)
	{
	case IMG_EFFECT_BOOT:
		ImgExecBoot();
		break;

	case IMG_EFFECT_ANIME:
		ImgExecAnime();
		break;

	case IMG_EFFECT_EXIT:
		ImgExecExit();
		break;

	default:
		SystemError("[Err] ImgExec eff=%x\n", Img.eff);
		break;
	}
}
//---------------------------------------------------------------------------
// îíÅ®ÉçÉSÅ®çï
IWRAM_CODE void ImgExecBoot(void)
{
	if(Img.step == 0)
	{
		// SPRING.GI
		Img2.pImg[8400] = FileGetImg(8400);
		Img2.pPal[8400] = FileGetPal(8400);
		ImgDrawBg(8400);

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		FadeSetWhite(16);
		ImgDrawPal();

		Img.var = 32;
		Img.step++;
		return;
	}

	if(Img.step == 2)
	{
		Img.var--;
		FadeSetWhite(Img.var/2);

		if(Img.var == 0)
		{
			Img.step++;
		}
		return;
	}

	// wait
	if(Img.step == 3)
	{
		// åÉèd èâä˙âªèàóù(^^;
		s32 i;

		for(i=0; i<8500; i++)
		{
			Img2.pImg[i] = FileGetImg(i);
			Img2.pPal[i] = FileGetPal(i);
		}

		Img.step++;
		return;
	}

	if(Img.step == 4)
	{
		Img.var++;
		FadeSetBlack(Img.var/2);

		if(Img.var >= 32)
		{
			Img.step++;
		}
		return;
	}

	if(Img.step == 5)
	{
		ImgDrawBgClr();

		Img.step++;
		return;
	}

	if(Img.step == 6)
	{
		ImgDrawPalClr();

		Img.step++;
		return;
	}

	FadeSetBlack(0);

	Img.isExec = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgExecAnime(void)
{
	if(Img.step == 0)
	{
		IrqSetCnt(0);

		for(;;)
		{
			s32 v = IrqGetCnt();

			ImgDrawBg(v);
//			Img2.isUse[v] = true;

			VBlankIntrWait();

			ImgDrawPal();

			if(v >= 8370)
			{
				Img.step++;

				return;
			}
		}
	}

/*
	s32 i;

	for(i=0; i<4000; i++)
	{
		if(Img2.isUse[i] == false)
		{
			TRACE("f%04d.bmp\n", Img2.isUse[i]);
		}
	}
*/

	// wait
	if(Img.step <= 241)
	{
		Img.step++;
		return;
	}

	if(Img.step == 242)
	{
		Img.var++;
		FadeSetBlack(Img.var/2);

		if(Img.var >= 32)
		{
			Img.step++;
		}
		return;
	}

	if(Img.step == 243)
	{
		ImgDrawBgClr();

		Img.step++;
		return;
	}

	if(Img.step == 244)
	{
		ImgDrawPalClr();

		Img.step++;
		return;
	}

	// wait
	if(Img.step <= 245+180)
	{
		Img.step++;
		return;
	}

	FadeSetBlack(0);

	Img.isExec = false;
}
//---------------------------------------------------------------------------
// çïÅ®ÉçÉSÅ®çï
IWRAM_CODE void ImgExecExit(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg(8400);

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		FadeSetBlack(16);
		ImgDrawPal();

		Img.var = 32;
		Img.step++;
		return;
	}

	if(Img.step == 2)
	{
		Img.var--;
		FadeSetBlack(Img.var/2);

		if(Img.var == 0)
		{
			Img.step++;
		}
		return;
	}

	// wait
	if(Img.step <= 3+120)
	{
		Img.step++;
		return;
	}

	if(Img.step == 124)
	{
		Img.var++;
		FadeSetBlack(Img.var/2);

		if(Img.var >= 32)
		{
			Img.step++;
		}
		return;
	}

	if(Img.step == 125)
	{
		ImgDrawBgClr();

		Img.step++;
		return;
	}

	if(Img.step == 126)
	{
		ImgDrawPalClr();

		Img.step++;
		return;
	}

	FadeSetBlack(0);

	Img.isExec = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgDrawBg(s32 no)
{
	u16* p = Img2.pImg[no];
	Img.bg = no;

	if(p == NULL)
	{
		return;
	}

	Mode4Draw(p);
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgDrawPal(void)
{
	u16* p = Img2.pPal[Img.bg];

	if(p == NULL)
	{
		return;
	}

	Mode4Pal(p);
	Mode4Exec();
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgDrawBgClr(void)
{
	Mode4DrawClr();
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgDrawPalClr(void)
{
	Mode4PalClr();
	Mode4Exec();
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgSetExec(s32 no)
{
	Img.eff    = no;
	Img.step   = 0;
	Img.var    = 0;
	Img.bg     = 0;
	Img.isExec = true;
}
//---------------------------------------------------------------------------
bool ImgIsExec(void)
{
	return Img.isExec;
}
