#include "img.h"
#include "libmy/mode3.arm.h"
#include "libmy/fade.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_IMG Img;


//---------------------------------------------------------------------------
void ImgInit(void)
{
	_Memset(&Img, 0x00, sizeof(ST_IMG));

	Img.fade = IMG_DEF_FADE_CNT;
}
//---------------------------------------------------------------------------
void ImgExec(void)
{
	switch(Img.eff)
	{
	default:
		ImgExecCls();
		break;

	case IMG_EFFECT_FADE:
		ImgExecFade();
		break;

	case IMG_EFFECT_COPY:
		ImgExecCopy();
		break;

	case IMG_EFFECT_TITL:
		ImgExecTitl();
		break;

	case IMG_EFFECT_FADE_OUT:
		ImgExecFadeOut();
		break;

	case IMG_EFFECT_FADE_IN:
		ImgExecFadeIn();
		break;
	}
}
//---------------------------------------------------------------------------
void ImgExecCls(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Img.step++;
		return;
	}

	// ��O�����@VBLANK����
	while(Img.step < Img.max)
	{
		Mode3VramEffCls(Img.step, Img.pEff);

		Img.step++;
	}

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgExecFade(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Img.step = 6;
		return;
	}

	// ��O�����@VBLANK����
	while(Img.step <= 31)
	{
		Mode3VramEffAlpha(Img.step);

		Img.step += 5;
	}

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgExecCopy(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Mode3VramCpyStep1();

		Img.step++;
		return;
	}

	Mode3VramCpyStep2();

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgExecTitl(void)
{
	// ���w�i�ɐݒ�
	if(Img.step == 0)
	{
		ImgSetBg(2);
		ImgClrChrAll();
		ImgDrawBg();

		Mode3VramCpyStep1();

		Img.step++;
		return;
	}

	// ���w�i
	if(Img.step == 1)
	{
		ImgSetFade2(0);
		Mode3VramCpyStep2();

		Img.step++;
		return;
	}

	// �E�����^�C�g�����o�b�t�@�ɕ`��{���X�N���[���͈͊O
	if(Img.step == 2)
	{
		ImgSetBg(900);
		ImgDrawBg();

		Mode3ScrollX(0);
		Mode3VramCpyStep1();
		Mode3VramCpyStep2();

		Img.step++;
		return;
	}

	// �E�����^�C�g�����X�N���[��
	if(Img.step == 3)
	{
		Mode3ScrollX(Img.step2);
		Img.step2 += 4;

		if(Img.step2 >= 214)
		{
			Img.step2 = 901;
			Img.step++;
		}
		return;
	}

	// �t���b�V��
	if(Img.step == 4)
	{
		ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(Img.step2);
		Mode3VramDpx((u16*)(h + 1));

		Img.step2++;

		if(Img.step2 >= 932)
		{
			Img.step++;
		}
		return;
	}

	// �����^�C�g���o�b�t�@�ɕ`��
	if(Img.step == 5)
	{
		ImgSetBg(932);
		ImgDrawBg();

		Mode3FlipBuf();

		ImgSetBg(990);
		ImgDrawBg();

		Img.step2 = 1;
		Img.step++;
		return;
	}

	// �����^�C�g���A���t�@�u�����h
	if(Img.step == 6)
	{
		while(Img.step2 <= 31)
		{
			Mode3VramEffAlpha(Img.step2);

			Img.step2 += 2;
		}

		Img.step++;
		return;
	}

	// �㑤�^�C�g�����o�b�t�@�ɕ`��
	if(Img.step == 7)
	{
		ImgSetBg(990);
		ImgDrawBg();

		Mode3FlipBuf();

		ImgSetBg(991);
		ImgDrawBg();

		Img.step2 = 1;
		Img.step++;
		return;
	}

	// �㑤�^�C�g���A���t�@�u�����h
	if(Img.step == 8)
	{
		while(Img.step2 <= 31)
		{
			Mode3VramEffAlpha(Img.step2);

			Img.step2++;
		}

		Img.step++;
		return;
	}

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
// �����F�w�i
void ImgExecFadeOut(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Mode3VramCpyStep1();

		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		Img.step2 = 16;
		FadeSetBlack(Img.step2);

		Mode3VramCpyStep2();

		Img.step++;
		return;
	}

	if(Img.step == 2)
	{
		Img.step2--;
		FadeSetBlack(Img.step2);

		if(Img.step2 <= Img.fade)
		{
			Img.step++;
		}
		return;
	}

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
// �F�w�i����
void ImgExecFadeIn(void)
{
	if(Img.step == 0)
	{
		ImgDrawBg();
		ImgDrawChr();

		Mode3VramCpyStep1();

		Img.step2 = Img.fade;
		Img.step++;
		return;
	}

	if(Img.step == 1)
	{
		Img.step2++;
		FadeSetBlack(Img.step2);

		if(Img.step2 >= 16)
		{
			Img.step++;
		}
		return;
	}

	if(Img.step == 2)
	{
		Mode3VramCpyStep2();
		FadeSetBlack(Img.fade);

		Img.step++;
		return;
	}

	Mode3FlipBuf();
	Img.isExec = false;
}
//---------------------------------------------------------------------------
void ImgDrawBg(void)
{
	_ASSERT(Img.bg.pDat != NULL);

	Mode3DrawBg(Img.bg.pDat);
}
//---------------------------------------------------------------------------
void ImgDrawChr(void)
{
	s32 i;

	for(i=0; i<IMG_MAX_CHR_CNT; i++)
	{
		if(Img.chr[i].pDat == NULL)
		{
			continue;
		}

		Mode3DrawChr(Img.chr[i].sx, Img.chr[i].sy, Img.chr[i].cx, Img.chr[i].cy, Img.chr[i].pDat, Img.chr[i].pMsk);
	}
}
//---------------------------------------------------------------------------
void ImgClrBg(void)
{
	Img.bg.pDat = NULL;
}
//---------------------------------------------------------------------------
void ImgClrChr(s32 no)
{
	s32 i;

	for(i=0; i<IMG_MAX_CHR_CNT; i++)
	{
		if(Img.chr[i].no == no && Img.chr[i].pDat != NULL)
		{
			Img.chr[i].pDat = NULL;

			return;
		}
	}

	// �I�v�V�����̉摜����ɉe�����邽�ߖ������i�Q�[�����̕s��͐��K�\���ŏC����
	// SystemError("[Err] ImgClrChr %d\n", no);
}
//---------------------------------------------------------------------------
void ImgClrChrAll(void)
{
	s32 i;

	for(i=0; i<IMG_MAX_CHR_CNT; i++)
	{
		Img.chr[i].pDat = NULL;
	}
}
//---------------------------------------------------------------------------
void ImgSetBg(s32 no)
{
	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(no);

	Img.bg.no   = no;
	Img.bg.cx   = h->cx;
	Img.bg.cy   = h->cy;
	Img.bg.pDat = (u16*)(h + 1);

	TRACE("[ImgSetBg %d %d %d]\n", no, Img.bg.cx, Img.bg.cy);
}
//---------------------------------------------------------------------------
void ImgSetChr(s32 no)
{
	s32 i;

	for(i=0; i<IMG_MAX_CHR_CNT; i++)
	{
		if(Img.chr[i].pDat == NULL)
		{
			break;
		}
	}
	_ASSERT(i < IMG_MAX_CHR_CNT);


	ST_FILE_IMG_HEADER* h = (ST_FILE_IMG_HEADER*)FileGetImg(no);
	ST_FILE_MSK_HEADER* m = (ST_FILE_MSK_HEADER*)FileGetMsk(no);

	Img.chr[i].no   = no;
	Img.chr[i].sx   = m->sx;
	Img.chr[i].sy   = m->sy;
	Img.chr[i].cx   = h->cx;
	Img.chr[i].cy   = h->cy;
	Img.chr[i].pDat = (u16*)(h + 1);
	Img.chr[i].pMsk =  (u8*)(m + 1);

	TRACE("[ImgSetChr %d %d %d %d %d %d]\n", i, no, Img.chr[i].sx, Img.chr[i].sy, Img.chr[i].cx, Img.chr[i].cy);
}
//---------------------------------------------------------------------------
void ImgSetEff(s32 no)
{
	TRACE("[ImgSetEff %d]\n", no);

	Img.eff = no;

	if(no >= IMG_EFFECT_FADE)
	{
		return;
	}

	ST_FILE_EFF_HEADER* h = (ST_FILE_EFF_HEADER*)FileGetEff(no);

	Img.cx   = h->cx;
	Img.cy   = h->cy;
	Img.max  = h->max;
	Img.pEff = (u8*)(h + 1);
}
//---------------------------------------------------------------------------
void ImgSetExec(void)
{
	TRACE("[ImgSetExec %d]\n", Img.eff);

	// �O���p�t�F�[�h�̏ꍇ�A���ɖ߂�
	if(Img.eff == IMG_EFFECT_FADE_IN || Img.eff == IMG_EFFECT_FADE_OUT)
	{
		Img.eff = IMG_EFFECT_FADE;
	}

	// �t�F�[�h�ō����F�w�i�A�F�w�i�����̏ꍇ�A��p�G�t�F�N�g�ɕύX
	if(Img.eff == IMG_EFFECT_FADE)
	{
		if(Img.bg.no == 2)
		{
			Img.eff = IMG_EFFECT_FADE_IN;
		}

		if(Img.bg.pv == 2)
		{
			Img.eff = IMG_EFFECT_FADE_OUT;
		}
	}

	Img.bg.pv = Img.bg.no;

	Img.step   = 0;
	Img.step2  = 0;
	Img.isExec = true;
}
//---------------------------------------------------------------------------
void ImgSetFade(s32 num)
{ 
	Img.fade = num;

	FadeSetBlack(num);
}
//---------------------------------------------------------------------------
void ImgSetFade2(s32 num)
{
	FadeSetBlack(num);
}
//---------------------------------------------------------------------------
void ImgLoadFade(void)
{
	FadeSetBlack(Img.fade);
}
//---------------------------------------------------------------------------
s32 ImgGetFade(void)
{
	return Img.fade;
}
//---------------------------------------------------------------------------
bool ImgIsExec(void)
{
	return Img.isExec;
}
