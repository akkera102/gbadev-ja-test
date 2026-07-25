#include "img.h"
#include "libmy/mode4.arm.h"
#include "libmy/irq.arm.h"
#include "libmy/fade.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_IMG Img;


//---------------------------------------------------------------------------
void ImgInit(void)
{
	_Memset(&Img, 0x00, sizeof(ST_IMG));
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
// 白→ロゴ→黒
IWRAM_CODE void ImgExecBoot(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg(20000);

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
		ImgDrawBg(2);

		Img.step++;
		return;
	}

	if(Img.step == 126)
	{
		ImgDrawPal();

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
		for(;;)
		{
			// 例外処理
			VBlankIntrWait();

			ImgDrawPal();
			ImgDrawBg(Img.bg++);

			// タイトル調整
			if(Img.bg == 4082)
			{
				TRACE("patch!\n");
				Img.bg = 4148;
			}

			// 終了
			if(Img.bg >= 8450)
			{
				Img.var = 0;
				Img.step++;

				return;
			}
		}
	}

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
		ImgDrawBg(2);

		Img.step++;
		return;
	}

	if(Img.step == 244)
	{
		ImgDrawPal();

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
// 黒→ロゴ→黒
IWRAM_CODE void ImgExecExit(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg(20000);

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
		ImgDrawBg(2);

		Img.step++;
		return;
	}

	if(Img.step == 126)
	{
		ImgDrawPal();

		Img.step++;
		return;
	}

	FadeSetBlack(0);

	Img.isExec = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgDrawBg(s32 no)
{
	u16* p = FileGetImg(no);

	if(p == NULL)
	{
		return;
	}

//	IrqSetCnt();
	Mode4Draw(p);
//	s32 cnt = IrqGetCnt();			// ズレありorz
	s32 cnt = 2;

	TRACE("%d %d\n", no, cnt);
//	TRACE("f%05d.img\n", no);

	Img.pal = no;
	Img.bg  = no + cnt;
}
//---------------------------------------------------------------------------
IWRAM_CODE void ImgDrawPal(void)
{
	if(Img.pal == 0)
	{
		return;
	}

	u16* p = FileGetPal(Img.pal);

	Mode4Pal(p);
	Mode4Exec();

	Img.pal = 0;
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
