// PC98 Rookies(海月製作所) SCP2TXT xrk ver
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <ctype.h>
#include <iconv.h>

// gcc scp2txt.c -o scp2txt -liconv -static

//---------------------------------------------------------------------------
typedef unsigned char		 u8;
typedef char				 s8;
typedef unsigned short		u16;
typedef short				s16;
typedef unsigned int		u32;
typedef int					s32;

typedef struct {
	s32   size;			// 解凍サイズ
	u8*   pDat;			// 解凍データ
	s32   ip;			// 作業カーソル

	// テキストファイル保存先
	FILE* fp;
	// ビット操作用
	u8    chr;
	s32   bitp;

} ST_SCP;


ST_SCP Scp;

//---------------------------------------------------------------------------
char* embedded_string[] = {
	"みちひこ",
	"みちひこ",
	"遅刻してきた目の悪いショートカットのカワイイ女子校生",
	"遅刻してきた目が悪く性格も悪いショートカットの女子校生",
	"遅刻してきた性格が悪いショートカットの女子校生",
	"受付嬢",
	"葉月",
	"ＳＡＣＫＹ",
	"警部補",
	"有馬巡査",
	"幡村警部補",
	"宇野さんの娘",
	"幸香",
	"紗希",
	"理沙",
	"ひろ子",
	"里美",
	"恭子",
	"浅野",
	"望月",
	"由美子",
	"議長",
	"教師",
	"雅美",
	"清司",
	"ボス",
	"諏山",
};
//---------------------------------------------------------------------------
u8 cur_scp8(void)
{
	return Scp.pDat[Scp.ip++];
}
//---------------------------------------------------------------------------
u16 cur_scp16(void)
{
	u16 ret = Scp.pDat[Scp.ip + 1] << 8 | Scp.pDat[Scp.ip];
	Scp.ip += 2;

	return ret;
}
//---------------------------------------------------------------------------
char* cur_scp_str(void)
{
	char* pRet = Scp.pDat + Scp.ip;

	while(Scp.pDat[Scp.ip++] != '\0')
	{
		// EMPTY
	}

	return pRet;
}
//---------------------------------------------------------------------------
u8 get_scp8(void)
{
	return Scp.pDat[Scp.ip];
}
//---------------------------------------------------------------------------
u16 get_scp16(void)
{
	return Scp.pDat[Scp.ip + 1] << 8 | Scp.pDat[Scp.ip];
}
//---------------------------------------------------------------------------
u16 jis2sjis(u16 code)
{
	u8     sb[3];	// src
	u8     db[3];	// det
	char*  ps = sb;
	char*  pd = db;
	size_t ss = 3;
	size_t sd = 3;

	sb[0] = (code >>   8) | 0x80;		// 一度JIS -> EUC-JPに変換
	sb[1] = (code & 0xff) | 0x80;
	sb[2] = '\0';

	iconv_t ic = iconv_open("SJIS", "EUC-JP");
	iconv(ic, &ps, &ss, &pd, &sd);
	iconv_close(ic);

	return (db[0] << 8) | db[1];
}
//---------------------------------------------------------------------------
void func_00(void)
{
	fprintf(Scp.fp, "exit(%d)\n", cur_scp8());
}
//---------------------------------------------------------------------------
void func_01(void)
{
	fprintf(Scp.fp, "newline()\n");
}
//---------------------------------------------------------------------------
void func_02(void)
{
	u8 num = cur_scp8();

	fprintf(Scp.fp, "draw_migfile(%d, \"%s\")\n", num, cur_scp_str());
}
//---------------------------------------------------------------------------
void func_03(void)
{
	fprintf(Scp.fp, "goto loc_%04X\n", cur_scp16());
}
//---------------------------------------------------------------------------
void func_04(void)
{
	fprintf(Scp.fp, "call sub_%04X\n", cur_scp16());
}
//---------------------------------------------------------------------------
void func_05(void)
{
	u8 c = cur_scp8();
	u8 v = cur_scp8();
	s32 i;

	fprintf(Scp.fp, "menu(%d, &val[%d], ", c, v);

	for(i=0; i<c; i++)
	{
		s32 len = 0;

		fprintf(Scp.fp, "\"");

		// １選択分の肢表示
		while(get_scp8() != 1)
		{
			u16 code = cur_scp16();
			code = jis2sjis(code);

			fputc(code >> 8, Scp.fp);
			fputc(code, Scp.fp);
		}
		fprintf(Scp.fp, "\"");

		// 終端記号スキップ
		cur_scp8();

		if(i == c - 1)
		{
			fprintf(Scp.fp, ")\n");
		}
		else
		{
			fprintf(Scp.fp, ", ");
		}
	}
}
//---------------------------------------------------------------------------
void func_06(void)
{
	u8    n1 = cur_scp8();
	char* s1 = cur_scp_str();
	u8    n2 = cur_scp8();
	char* s2 = cur_scp_str();

	fprintf(Scp.fp, "setup_zurizuri(%d, \"%s\", %d, \"%s\")\n", n1, s1, n2, s2);
}
//---------------------------------------------------------------------------
void func_07(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	case 1:
		fprintf(Scp.fp, "zurizuri_scroll()\n");
		break;
	case 2:
		fprintf(Scp.fp, "scroll_up_two_screen()\n");
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_08(void)
{
	fprintf(Scp.fp, "free_ani_data()\n");
}
//---------------------------------------------------------------------------
void func_09(void)
{
	u8 x  = cur_scp8();
	u8 op = cur_scp8();
	u8 y  = cur_scp8();

	switch(op)
	{
	case 0:   fprintf(Scp.fp, "val[%d] = %d\n", x, y);                break;
	case 1:   fprintf(Scp.fp, "val[%d] += %d\n", x, y);               break;
	case 2:   fprintf(Scp.fp, "val[%d] -= %d\n", x, y);               break;
	case 3:   fprintf(Scp.fp, "val[%d] *= %d\n", x, y);               break;
	case 4:   fprintf(Scp.fp, "val[%d] /= %d\n", x, y);               break;		// honto ha wari-zan?
	case 5:   fprintf(Scp.fp, "val[%d] %%= %d\n", x, y);              break;
	case 6:   fprintf(Scp.fp, "val[%d] = rand() %% %d\n", x, y);      break;		// hmm... rand?
	case 7:   fprintf(Scp.fp, "val[%d] = val[%d]\n", x, y);           break;
	case 8:   fprintf(Scp.fp, "val[%d] += val[%d]\n", x, y);          break;
	case 9:   fprintf(Scp.fp, "val[%d] -= val[%d]\n", x, y);          break;
	case 0xa: fprintf(Scp.fp, "val[%d] *= val[%d]\n", x, y);          break;
	case 0xb: fprintf(Scp.fp, "val[%d] /= val[%d]\n", x, y);          break;		// koremo wari-zan?
	case 0xc: fprintf(Scp.fp, "val[%d] %%= val[%d]\n", x, y);         break;
	case 0xd: fprintf(Scp.fp, "val[%d] = rand() %% val[%d]\n", x, y); break;		// hmm... rand??

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_0a(void)
{
	u8   x = cur_scp8();
	u8  op = cur_scp8();
	u8   y = cur_scp8();
	u16  z = cur_scp16();

	switch(op)
	{
	case 1: fprintf(Scp.fp, "if (val[%d] != %d) goto loc_%04X\n", x, y, z);      break; // je
	case 2: fprintf(Scp.fp, "if (val[%d] == %d) goto loc_%04X\n", x, y, z);      break; // jne
	case 3: fprintf(Scp.fp, "if (val[%d] <= %d) goto loc_%04X\n", x, y, z);      break; // jg
	case 4: fprintf(Scp.fp, "if (val[%d] >= %d) goto loc_%04X\n", x, y, z);      break; // jl
	case 5: fprintf(Scp.fp, "if (val[%d] != val[%d]) goto loc_%04X\n", x, y, z); break; // je
	case 6: fprintf(Scp.fp, "if (val[%d] == val[%d]) goto loc_%04X\n", x, y, z); break; // jne
	case 7: fprintf(Scp.fp, "if (val[%d] <= val[%d]) goto loc_%04X\n", x, y, z); break; // jg
	case 8: fprintf(Scp.fp, "if (val[%d] >= val[%d]) goto loc_%04X\n", x, y, z); break; // jl

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_0b(void)
{
	u16 x = cur_scp16();
	u16 y = cur_scp16();

	fprintf(Scp.fp, "set_xy(%d, %d)\n", x, y);
}
//---------------------------------------------------------------------------
void func_0c(void)
{
	u8 x1 = cur_scp8();
	u8 y1 = cur_scp8();
	u8 x2 = cur_scp8();
	u8 y2 = cur_scp8();

	fprintf(Scp.fp, "define_dialog_box(%d, %d, %d, %d)\n", x1, y1, x2, y2);
}
//---------------------------------------------------------------------------
void func_0d(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	case 0: fprintf(Scp.fp, "show_prompt()\n");        break;
	case 1: fprintf(Scp.fp, "hide_prompt()\n");        break;
	case 2: fprintf(Scp.fp, "no_timeout_confirm()\n"); break;
	case 3: fprintf(Scp.fp, "timeout_confirm()\n");    break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_0e(void)
{
	fprintf(Scp.fp, "exec(\"%s\")\n", cur_scp_str());
}
//---------------------------------------------------------------------------
void func_0f(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	// str
	case 0:
		fprintf(Scp.fp, "play_bgm(\"%s\")\n", cur_scp_str());
		break;

	// void
	case 1:
		fprintf(Scp.fp, "int_60_0()\n");
		break;
	case 2:
		fprintf(Scp.fp, "int_60_1()\n");
		break;
	case 7:
		fprintf(Scp.fp, "int_60_0D()\n");
		break;
	case 8:
		fprintf(Scp.fp, "int_60_1A()\n");
		break;
	case 9:
		fprintf(Scp.fp, "int_60_1B()\n");
		break;

	// char
	case 3:
		fprintf(Scp.fp, "int_60_2_0(%d)\n", cur_scp8());
		break;
	case 4:
		fprintf(Scp.fp, "int_60_2_1(%d)\n", cur_scp8());
		break;
	case 5:
		fprintf(Scp.fp, "int_60_0C(%d)\n", cur_scp8());
		break;
	case 6:
		fprintf(Scp.fp, "int_60_19(%d)\n", cur_scp8());
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_10(void)
{
	fprintf(Scp.fp, "wait_for_key()\n");
}
//---------------------------------------------------------------------------
void func_11(void)
{
	u8 cmd = cur_scp8();
	u8 spd = cur_scp8();

	switch(cmd)
	{
	case 1: fprintf(Scp.fp, "fade_in_black(%d)\n", spd);  break;
	case 2: fprintf(Scp.fp, "fade_out_black(%d)\n", spd); break;
	case 3: fprintf(Scp.fp, "fade_in_white(%d)\n", spd);  break;
	case 4: fprintf(Scp.fp, "fade_out_white(%d)\n", spd); break;
	case 5: fprintf(Scp.fp, "open_curtain()\n");          break;
	case 6: fprintf(Scp.fp, "close_curtain()\n");         break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_12(void)
{
	fprintf(Scp.fp, "run_dos_prg(\"%s\")\n", cur_scp_str());
}
//---------------------------------------------------------------------------
void func_13(void)
{
	fprintf(Scp.fp, "set_text_attribute(%d)\n", cur_scp8());
}
//---------------------------------------------------------------------------
void func_14(void)
{
	fprintf(Scp.fp, "read_idxfile(\"%s\")\n", cur_scp_str());
}
//---------------------------------------------------------------------------
void func_15(void)
{
	fprintf(Scp.fp, "read_pixfile(\"%s\")\n", cur_scp_str());
}
//---------------------------------------------------------------------------
void func_16(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	// char, char, char, char,
	case 0:
	case 1:
		u8 v1 = cur_scp8();
		u8 v2 = cur_scp8();
		s32 i;

		if(v1 < v2)
		{
			for(i=0; i<v2-v1; i++)
			{
				// EMPTY
				// buf[i] = ???
			}
		}

		fprintf(Scp.fp, "0x%02X 0x%02X 0x%02X 0x%02X\n", 0x16, cmd, v1, v2);
		Scp.ip += i;
		break;

	// char, int, int, int, char
	// w: rookies では常に 0
	// x: スクロールする領域の高さ
	// y: スタートライン
	// z: エンドライン
	// s: スピード
	case 2:
		u8  w = cur_scp8();
		u16 x = cur_scp16();
		u16 y = cur_scp16();
		u16 z = cur_scp16();
		u8  s = cur_scp8();

		fprintf(Scp.fp, "start_animation(%d, %d, %d, %d, %d)\n", w, x, y, z, s);
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_17(void)
{
	fprintf(Scp.fp, "0x%02X 0x%02X\n", 0x17, cur_scp8());
}
//---------------------------------------------------------------------------
void func_18(void)
{
	fprintf(Scp.fp, "0x%02X\n", 0x18);
}
//---------------------------------------------------------------------------
void func_19(void)
{
	u8  cmd = cur_scp8();
	u16  x1 = cur_scp16();
	u16  y1 = cur_scp16();
	u16  x2 = cur_scp16();
	u16  y2 = cur_scp16();
	u8    f = cur_scp8();

	switch(cmd)
	{
	case 1:
		fprintf(Scp.fp, "copy_sub_to_main(%d, %d, %d, %d)\n", x1, y1, x2, y2);
		break;

	case 2:
		fprintf(Scp.fp, "fill_rectangle(%d, %d, %d, %d, %d)\n", x1, y1, x2, y2, f);
		break;

	case 3:
		fprintf(Scp.fp, "clear_75(%d, %d, %d, %d)\n", x1, y1, x2, y2);
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_1a(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	// int
	case 0:
		fprintf(Scp.fp, "0x%02X 0x%02X 0x%04X\n", 0x1a, cmd, cur_scp16());
		break;

	// void
	case 1:
	case 3:
		fprintf(Scp.fp, "0x%02X 0x%02X\n", 0x1a, cmd);
		break;

	// char
	case 2:
		fprintf(Scp.fp, "0x%02X 0x%02X 0x%02X\n", 0x1a, cmd, cur_scp8());
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_1b(void)
{
	fprintf(Scp.fp, "return\n");
}
//---------------------------------------------------------------------------
void func_1c(void)
{
	fprintf(Scp.fp, "set_palette()\n");
}
//---------------------------------------------------------------------------
void func_1d(void)
{
	fprintf(Scp.fp, "delay(%d)\n", cur_scp8());
}
//---------------------------------------------------------------------------
void func_1e(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	// void
	case 1:
		fprintf(Scp.fp, "input_name()\n");
		break;

	// void
	case 2:
	case 3:
	case 4:
	case 5:
		fprintf(Scp.fp, "0x%02X 0x%02X\n", 0x1e, cmd);
		break;

	// char
	case 6:
		fprintf(Scp.fp, "save_hoehoe_dat(%d)\n", cur_scp8());
		break;

	// void
	case 7:
		fprintf(Scp.fp, "change_destination_and_esc()\n");
		break;
	case 8:
		fprintf(Scp.fp, "change_destination_and_esc_to_default()\n");
		break;
	case 9:
		fprintf(Scp.fp, "save_load_menu()\n");
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_1f(void)
{
	fprintf(Scp.fp, "change_diskette(%d)\n", cur_scp8());
}
//---------------------------------------------------------------------------
void func_20(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	case 0:
		fprintf(Scp.fp, "enable_system_menu()\n");
		break;

	case 1:
		fprintf(Scp.fp, "disable_system_menu()\n");
		break;

	case 2:
		fprintf(Scp.fp, "make_check_point()\n");
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_80(void)
{
	u8 i = cur_scp8();

	if(i == 0)
	{
		fprintf(Scp.fp, "refer_string(%d) = %s\n", i, embedded_string[i]);
	}
	else
	{
		fprintf(Scp.fp, "refer_string(%d) = 【%s】\n", i, embedded_string[i]);
	}
}
//---------------------------------------------------------------------------
void func_others(void)
{
	while(isprint(get_scp8()) != 0)
	{
		u16 code = get_scp16();
		code = jis2sjis(code);

		fputc(code >> 8, Scp.fp);
		fputc(code, Scp.fp);

		Scp.ip += 2;
	}

	fputc('\n', Scp.fp);
}
//---------------------------------------------------------------------------
void save_file(char* fname)
{
	char sname[20];
	strncpy(sname, fname, 20);

	char* p = strchr(sname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");
		exit(1);
	}

	p[1] = 't';
	p[2] = 'x';
	p[3] = 't';

	Scp.fp = fopen(sname, "wb");

	if(Scp.fp == NULL)
	{
		fprintf(stderr, "couldn't open savefille\n");
		exit(1);
	}


	Scp.ip = 0;

	while(Scp.ip < Scp.size)
	{
		fprintf(Scp.fp, "0x%04X: ", Scp.ip);

		u8 cmd = Scp.pDat[Scp.ip];

		if(cmd <= 0x20 || cmd == 0x80)
		{
			Scp.ip++;

			switch(cmd)
			{
			case 0x00: func_00(); break;
			case 0x01: func_01(); break;
			case 0x02: func_02(); break;
			case 0x03: func_03(); break;
			case 0x04: func_04(); break;
			case 0x05: func_05(); break;
			case 0x06: func_06(); break;
			case 0x07: func_07(); break;
			case 0x08: func_08(); break;
			case 0x09: func_09(); break;
			case 0x0a: func_0a(); break;
			case 0x0b: func_0b(); break;
			case 0x0c: func_0c(); break;
			case 0x0d: func_0d(); break;
			case 0x0e: func_0e(); break;
			case 0x0f: func_0f(); break;
			case 0x10: func_10(); break;
			case 0x11: func_11(); break;
			case 0x12: func_12(); break;
			case 0x13: func_13(); break;
			case 0x14: func_14(); break;
			case 0x15: func_15(); break;
			case 0x16: func_16(); break;
			case 0x17: func_17(); break;
			case 0x18: func_18(); break;
			case 0x19: func_19(); break;
			case 0x1a: func_1a(); break;
			case 0x1b: func_1b(); break;
			case 0x1c: func_1c(); break;
			case 0x1d: func_1d(); break;
			case 0x1e: func_1e(); break;
			case 0x1f: func_1f(); break;
			case 0x20: func_20(); break;
			case 0x80: func_80(); break;
			}
		}
		else
		{
			func_others();
		}
	}

	fclose(Scp.fp);
}
//---------------------------------------------------------------------------
s32 msb(u32 val)
{
	s32 m;

	for(m=-1; val!=0; m++)
	{
		val >>= 1;
	}

	return m;
}
//---------------------------------------------------------------------------
s32 getbit(FILE *fp)
{
	if(Scp.bitp <= 0)
	{
		Scp.bitp = 8;
		fread(&Scp.chr, 1, 1, fp);
	}

	Scp.bitp--;
	return (Scp.chr & (1 << Scp.bitp)) ? 1 : 0;
}
//---------------------------------------------------------------------------
u32 getbits(FILE* fp, s32 a1)
{
	s32 r = 0;
	s32 i;

	for(i=0; i<a1; i++)
	{
		r <<= 1;
		r += getbit(fp);
	}

	return r;
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "scp2txt [filename]\n");
		exit(1);
	}

	FILE* fp = fopen(argv[1], "rb");

	if((fp = fopen(argv[1], "rb")) == NULL)
	{
		fprintf(stderr, "couldn't find scp file \"%s\"\n", argv[1]);
		exit(1);
	}


	u8 buf[4];

	// ファイルチェック
	fread(buf, 4, 1, fp);

	if(memcmp(buf, "LZ96", 4) != 0)
	{
		fprintf(stderr, "this is NOT a scp file: \"%s\"\n", argv[1]);
		exit(1);
	}

	// 解凍サイズ取得
	fread(buf, 4, 1, fp);

	Scp.size = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0];
	Scp.pDat = calloc(Scp.size, sizeof(u8));

	if(Scp.pDat == NULL)
	{
		fprintf(stderr, "calloc error\n");
		exit(1);
	}

	// 解凍
	u32 l3, l5;
	s32 l4;
	u8  l7;
	u32 l1 = 0;

	Scp.bitp = 0;
	Scp.chr  = 0;

	while(l1 < Scp.size)
	{
		if(getbits(fp, 1) == 0)
		{
			Scp.pDat[l1++] = getbits(fp, 8);

			continue;
		}

		if((l1 & 0xffff) >= 0 && (l1 & 0xffff) < 0x4000)
		{
			l4 = msb(l1 & 0xffff) + 1;
		}
		else
		{
			l4 = 0xe;
		}

		l3 = getbits(fp, l4); 

		for(l7=2; l7!=8; l7++)
		{
			if(getbits(fp, 1) != 0)
			{
				 break;
			}
		}

		if(l7 == 8)
		{
			l7 = getbits(fp, 8);
		}

		for(l5=0; l5<l7; l5++)
		{
			Scp.pDat[l1] = Scp.pDat[l1 - l3];

			l1++;
		}
	}
	fclose(fp);

	save_file(argv[1]);

	return 0;
}
