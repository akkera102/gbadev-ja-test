#include "lib/gba.h"
#include "bg.h"
#include "irq.arm.h"
#include "key.h"
#include "vgm.arm.h"
#include "string.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	GbfsInit();
	BgInit();
	KeyInit();

	VgmPlayerInit();

	VgmInit();
	VgmStop();

	IrqInit();


	u8 row = 0;
	BgDrawPrintf(0, row, "gPSG Player ADVANCE   0x");

	row = 4;
	BgDrawPrintf(5, row, ":");
	BgDrawPrintf(22, row, "EoF:");
	row++;
	BgDrawPrintf(5, row, ":");
	row++;
	BgDrawPrintf(5, row, ":");
	BgDrawPrintf(22, row, "Start:");
	row++;
	BgDrawPrintf(5, row, ":");
	row++;
	BgDrawPrintf(1, row, "ctrl:");
	// row++;
	// BgDrawPrintf(1, row, "fifo:");

	row = 10;
	BgDrawPrintf(1, row, "wave:");

	row = 14;
	BgDrawPrintf(1, row, "mode:");
	BgDrawPrintf(25, row, "vol");

	row = 18;
	BgDrawPrintf(1, row, "GB-PSG BGM Test (VBlank)");
	row++;
	BgDrawPrintf(10, row, "for W/end. GBA Port");

	u32 _tmp = 0;

	u32 offset_play = 0;
	u32 offset_jump = 0;
	u32 sel = 0;
	u32 volume = 9;
	u8 stat = PLAYER_STAT_STOP;
	s32 opt_loop = 0;
	s32 opt_waveedit = 0;
	s32 opt_headset = 0;
	s32 opt_fadeout = 0;

	u8 dev_waveedit = 1;
	u8 dev_enable_ch = 0xf;

	s32 ptr_wave = 0;
	s8 wave_byte = 0;
	s8 upper_wave = 0;
	s8 lower_wave = 0;

	u32 max = GbfsGetArcCnt() - 1;
	if(sel > max)
	{
		sel = max;
	}

	GbfsGetSafePointer2(sel);
	char* pF = GbfsGetFileName();

	u32 pL = GbfsGetFileSize();
	if(offset_jump > pL)
	{
		offset_jump = pL;
	}

	for(;;)
	{
		VBlankIntrWait();
		offset_play = VgmGetOffsetPlay();
		stat = VgmGetStat();
		opt_loop = VgmGetIsLoop();
		opt_waveedit = VgmGetIsWaveEdit();
		opt_headset = VgmGetIsHeadset();
		opt_fadeout = VgmGetIsFade();

		row = 0;
		BgDrawPrintf(24, row, "       ");
		BgDrawPrintf(24, row, (0 == offset_play >> 16) ? "%04X" : "%X", offset_play);

		row++;
		BgDrawPrintf(24, row, (stat == PLAYER_STAT_RESERVE) ? "%02d" : "  ", VgmGetFadeCnt());
		BgDrawPrintf(26, row, (stat == PLAYER_STAT_STOP) ? "[]" : "|>");
		BgDrawPrintf(28, row, "%02d", VgmGetTrId() + 1);

		row++;
		BgDrawPrintf(0, row, "%2d/%2d:", sel + 1, max + 1);

		BgDrawPrintf(7, row, "                        ");
		BgDrawPrintf(7, row, "%s", pF);
		row++;
		BgDrawPrintf(0, row, " ");


		row = 4;
		BgDrawPrintf(1, row, (dev_enable_ch & 0b0001) ? "ch 1" : "Mute");
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetAgReg(AGREG_NR10));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR11));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR12));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetAgReg(AGREG_NR13));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetAgReg(AGREG_NR14));

		row++;
		BgDrawPrintf(1, row, (dev_enable_ch & 0b0010) ? "ch 2" : "Mute");
		BgDrawPrintf(7+0*3, row, "--");
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR21));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR22));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetAgReg(AGREG_NR23));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetAgReg(AGREG_NR24));

		BgDrawPrintf(24, row, "      ");
		BgDrawPrintf(24, row, (0 == pL >> 16) ? "%04X" : "%X", pL);

		row++;
		BgDrawPrintf(1, row, (dev_enable_ch & 0b0100) ? "ch 3" : "Mute");
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetAgReg(AGREG_NR30));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR31));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR32));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetAgReg(AGREG_NR33));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetAgReg(AGREG_NR34));

		row++;
		BgDrawPrintf(1, row, (dev_enable_ch & 0b1000) ? "ch 4" : "Mute");
		BgDrawPrintf(7+0*3, row, "--");
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR41));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR42));
		BgDrawPrintf(7+3*3, row, "%02X", VgmGetAgReg(AGREG_NR43));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetAgReg(AGREG_NR44));

		BgDrawPrintf(24, row, "      ");
		BgDrawPrintf(24, row, (0 == offset_jump >> 16) ? "%04X" : "%X", offset_jump);

		row++;
		BgDrawPrintf(7+0*3, row, "%02X", VgmGetAgReg(AGREG_NR50));
		BgDrawPrintf(7+1*3, row, "%02X", VgmGetAgReg(AGREG_NR51));
		BgDrawPrintf(7+2*3, row, "%02X", VgmGetAgReg(AGREG_NR52));

		BgDrawPrintf(7+3*3, row, "%02X", VgmGetAgReg(AGREG_RESAMP));
		BgDrawPrintf(7+4*3, row, "%02X", VgmGetAgReg(AGREG_BIAS_H));
		BgDrawPrintf(6+5*3, row, "%02X", VgmGetAgReg(AGREG_BIAS_L));


		row = 10;
		s32 wav_i = 0;
		s32 pos_i = 7;
		for(;wav_i < 0x08;)
		{
			BgDrawPrintf(pos_i, row, "%02X", VgmGetWave(wav_i));
			wav_i++;
			pos_i = pos_i + 2;
			if(wav_i == 0x04)
			{
				pos_i++;
			}
		}
		row++;
		BgDrawPrintf(0, row, (0 != opt_waveedit) ? "(edit)" : "      ");
		BgDrawPrintf(6, row, "                        ");

		row++;
		pos_i = 7;
		for(;wav_i < 0x10;)
		{
			BgDrawPrintf(pos_i, row, "%02X", VgmGetWave(wav_i));
			wav_i++;
			pos_i = pos_i + 2;
			if(wav_i == 0x0C)
			{
				pos_i++;
			}
		}
		row++;
		BgDrawPrintf(0, row, "                              ");

		if(0 != opt_waveedit){
			if(ptr_wave < 0x08)
			{
				BgDrawPrintf(7+ptr_wave, row-2, "^");
			}
			else if(ptr_wave < 0x10)
			{
				BgDrawPrintf(7+ptr_wave+1, row-2, "^");
			}
			else if(ptr_wave < 0x18)
			{
				BgDrawPrintf(7+ptr_wave-0x10, row, "^");
			}
			else
			{
				BgDrawPrintf(7+ptr_wave+1-0x10, row, "^");
			}
		}

		// row++;
		// PCM DRIVER STATUS
		// row++;

		row++;
		BgDrawPrintf(7, row, (0 == opt_waveedit) ? (0 == opt_headset) ? "speaker" : "headset": " debug ");
		BgDrawPrintf(15, row, (0 == opt_fadeout) ? " -- " : "fade");
		BgDrawPrintf(20, row, (0 == opt_loop) ? " -- " : "loop");
		BgDrawPrintf(28, row, "%d", volume);


		KeyExec();
		u16 trg = KeyGetTrg();
		u16 hld = KeyGetHld();

		row = 16;
		BgDrawPrintf(26, row, (trg & KEY_L) ? "L" : " ");
		BgDrawPrintf(27, row, (trg & KEY_R) ? "R" : " ");
		BgDrawPrintf(28, row, (hld & KEY_L) ? "L" : " ");
		BgDrawPrintf(29, row, (hld & KEY_R) ? "R" : " ");
		row++;
		BgDrawPrintf(26, row, "%02X", trg);
		BgDrawPrintf(28, row, "%02X", hld);

		BgDrawPrintf(24, 8, (hld & KEY_B) ? (0 == offset_jump >> 16) ? "^^ " : " ^^" : "   ");

		// 波形メモリ編集モードではない時の十字キーとLR
		if(0 == opt_waveedit)
		{
			_tmp = sel;

			if(((trg & KEY_RIGHT) || (hld & KEY_RIGHT)) && !(hld & KEY_B) && sel < max)
			{
				sel++;

				GbfsGetSafePointer2(sel);
				pF = GbfsGetFileName();
				pL = GbfsGetFileSize();
			}
			if(((trg & KEY_LEFT) || (hld & KEY_LEFT)) && !(hld & KEY_B) && sel > 0)
			{
				sel--;

				GbfsGetSafePointer2(sel);
				pF = GbfsGetFileName();
				pL = GbfsGetFileSize();
			}

			if(((trg & KEY_DOWN) || (hld & KEY_DOWN)) && !(hld & KEY_B) && sel < max)
			{
				sel = (sel + 10 <= max) ? sel + 10 : max;

				GbfsGetSafePointer2(sel);
				pF = GbfsGetFileName();
				pL = GbfsGetFileSize();
			}
			if(((trg & KEY_UP) || (hld & KEY_UP)) && !(hld & KEY_B) && sel > 0)
			{
				sel = (sel >= 10) ? sel - 10 : 0;

				GbfsGetSafePointer2(sel);
				pF = GbfsGetFileName();
				pL = GbfsGetFileSize();
			}

			if(((trg & KEY_R) || (hld & KEY_R)) && !(hld & KEY_B) && volume < 9)
			{
				volume++;

				VgmSetVolume(volume);
			}
			if(((trg & KEY_L) || (hld & KEY_L)) && !(hld & KEY_B) && volume > 0)
			{
				volume--;

				VgmSetVolume(volume);
			}

			// 次再生される曲が変わりそうなら再生開始位置はリセット
			if(_tmp != sel)
			{
				offset_jump = 0;
				VgmSetStartOffset(offset_jump);
			}

		}
		// 波形メモリ編集モード有効時の十字キーとLR
		else
		{
			// 波形の編集位置
			if(((trg & KEY_RIGHT) || (hld & KEY_RIGHT)) && !(hld & KEY_B))
			{
				ptr_wave = (ptr_wave + 1) % 32;
			}
			if(((trg & KEY_LEFT) || (hld & KEY_LEFT)) && !(hld & KEY_B))
			{
				ptr_wave = (ptr_wave + 31) % 32;
			}

			//波形の値操作
			if(((trg & KEY_DOWN) || (hld & KEY_DOWN)) && !(hld & KEY_B))
			{
				wave_byte = VgmGetWave(ptr_wave / 2);
				upper_wave = wave_byte & 0xf0;
				lower_wave = wave_byte & 0x0f;

				if(1 == ptr_wave % 2)
				{
					lower_wave = (lower_wave + 0x0f) & 0x0f;
				}
				else
				{
					upper_wave = (upper_wave + 0xf0) & 0xf0;
				}
				VgmSetWave(ptr_wave / 2, upper_wave + lower_wave);
			}
			if(((trg & KEY_UP) || (hld & KEY_UP)) && !(hld & KEY_B))
			{
				wave_byte = VgmGetWave(ptr_wave / 2);
				upper_wave = wave_byte & 0xf0;
				lower_wave = wave_byte & 0x0f;

				if(1 == ptr_wave % 2)
				{
					lower_wave = (lower_wave + 0x01) & 0x0f;
				}
				else
				{
					upper_wave = (upper_wave + 0x10) & 0xf0;
				}
				VgmSetWave(ptr_wave / 2, upper_wave + lower_wave);
			}

			// “無音”波形メモリの確認用
			// (DMGだと0x77で無音だがGBAは違うので0x00を使うこと)
			if((trg & KEY_R) && !(hld & KEY_B))
			{
				for(u32 i = 0; i < 0x10; i++)
				{
					VgmSetWave(i, 0x00);
				}
			}
			if((trg & KEY_L) && !(hld & KEY_B))
			{
				for(u32 i = 0; i < 0x10; i++)
				{
					VgmSetWave(i, 0x77);
				}
			}
		}

		// 波形メモリ編集モード(制作用)
		if((trg & KEY_START) && !(hld & KEY_B) && 1 == dev_waveedit)
		{
			opt_waveedit = (opt_waveedit + 1) % 2;
			VgmSetWaveEdit(opt_waveedit);
		}
		// ヘッドホンモード
		if((trg & KEY_SELECT) && !(hld & KEY_B))
		{
			opt_headset = (opt_headset + 1) % 2;
			VgmSetHeadset(opt_headset);
		}

		//再生と停止
		if(trg & KEY_A)
		{
			if(1 == opt_fadeout && PLAYER_STAT_PLAY == stat)
			{
				VgmReserve(sel);
			}
			else
			{
				VgmPlay(sel);
			}
		}
		if(trg & KEY_B)
		{
			VgmStop();
		}

		// Bを押し続けながら
		if(hld & KEY_B)
		{
			// B長押し＋十字キーで再生開始位置の変更を可能にした
			if(((trg & KEY_RIGHT) || (hld & KEY_RIGHT)) && offset_jump < pL)
			{
				offset_jump = (offset_jump + 0x100 <= pL) ? offset_jump + 0x100 : pL;
				VgmSetStartOffset(offset_jump);
			}
			if(((trg & KEY_LEFT) || (hld & KEY_LEFT)) && offset_jump > 0)
			{
				offset_jump = (offset_jump >= 0x100) ? offset_jump - 0x100 : 0;
				VgmSetStartOffset(offset_jump);
			}

			if(((trg & KEY_DOWN) || (hld & KEY_DOWN)) && offset_jump < pL)
			{
				offset_jump = (offset_jump + 0x1000 <= pL) ? offset_jump + 0x1000 : pL;
				VgmSetStartOffset(offset_jump);
			}
			if(((trg & KEY_UP) || (hld & KEY_UP)) && offset_jump > 0)
			{
				offset_jump = (offset_jump >= 0x1000) ? offset_jump - 0x1000 : 0;
				VgmSetStartOffset(offset_jump);
			}

			// B長押し＋L,R,START,SELECTでチャンネルミュートを可能にした
			if(trg & KEY_L)
			{
				dev_enable_ch = (dev_enable_ch & 0b1110) | ((~dev_enable_ch & 0b0001));
				VgmSetMute(dev_enable_ch);
			}
			if(trg & KEY_R)
			{
				dev_enable_ch = (dev_enable_ch & 0b1101) | ((~dev_enable_ch & 0b0010));
				VgmSetMute(dev_enable_ch);
			}
			if(trg & KEY_START)
			{
				dev_enable_ch = (dev_enable_ch & 0b1011) | ((~dev_enable_ch & 0b0100));
				VgmSetMute(dev_enable_ch);
			}
			if(trg & KEY_SELECT)
			{
				dev_enable_ch = (dev_enable_ch & 0b0111) | ((~dev_enable_ch & 0b1000));
				VgmSetMute(dev_enable_ch);
			}
		}
	}
}
