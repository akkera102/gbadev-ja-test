// PC98 Rookies(�C�����쏊) SCP2TXT
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
	s32   size;			// �𓀃T�C�Y
	u8*   pDat;			// �𓀃f�[�^
	s32   ip;			// ��ƃJ�[�\��
	s32   selCnt;		// �I�����J�E���^

	// �e�L�X�g�t�@�C���ۑ���
	FILE* fp;
	// �r�b�g����p
	u8    chr;
	s32   bitp;

} ST_SCP;


ST_SCP Scp;

//---------------------------------------------------------------------------
char* embedded_string[] = {
	"�݂��Ђ�",
	"�݂��Ђ�",
	"�x�����Ă����ڂ̈����V���[�g�J�b�g�̃J���C�C���q�Z��",
	"�x�����Ă����ڂ��������i�������V���[�g�J�b�g�̏��q�Z��",
	"�x�����Ă������i�������V���[�g�J�b�g�̏��q�Z��",
	"��t��",
	"�t��",
	"�r�`�b�j�x",
	"�x����",
	"�L�n����",
	"�����x����",
	"�F�삳��̖�",
	"�K��",
	"�ъ�",
	"����",
	"�Ђ�q",
	"����",
	"���q",
	"���",
	"�]��",
	"�R���q",
	"�c��",
	"���t",
	"���",
	"���i",
	"�{�X",
	"�z�R",
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

	while(Scp.pDat[Scp.ip] != '\0')
	{
		u8 c = Scp.pDat[Scp.ip];

		// 2Byte SJIS
		if(((c >= 0x81 && c <= 0x9f) || (c >= 0xe0 && c <= 0xef)))
		{
			Scp.ip += 2;

			continue;
		}

		// 1Byte
		if((c >= 'a') && (c <= 'z'))
		{
			// ��������啶���ɕύX
			Scp.pDat[Scp.ip] -= ('a' - 'A');
		}

		Scp.ip++;
	}

	// skip '\0'
	Scp.ip++;

	return pRet;
}
//---------------------------------------------------------------------------
u8 get_scp8(void)
{
	return Scp.pDat[Scp.ip];
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

	sb[0] = (code >>   8) | 0x80;		// ��xJIS -> EUC-JP�ɕϊ�
	sb[1] = (code & 0xff) | 0x80;
	sb[2] = '\0';

	iconv_t ic = iconv_open("SJIS", "EUC-JP");
	iconv(ic, &ps, &ss, &pd, &sd);
	iconv_close(ic);

	return (db[0] << 8) | db[1];
}
//---------------------------------------------------------------------------
void func_jis(void)
{
Re:

	// ������\��
	do
	{
		u16 code = cur_scp16();
		code = jis2sjis(code);

		fprintf(Scp.fp, "%c%c", code >> 8, code);

	} while(isprint(get_scp8()) != 0);


	// ��l���̖��O
	if(get_scp8() == 0x80)
	{
		u8 s = cur_scp8();
		u8 i = cur_scp8();
		assert(s == 0x80 && i == 0);


		fprintf(Scp.fp, "%s", embedded_string[i]);

		goto Re;
	}

	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_00(void)
{
	fprintf(Scp.fp, "END %d\n", cur_scp8());
}
//---------------------------------------------------------------------------
void func_01(void)
{
	fprintf(Scp.fp, "KEY\n");
}
//---------------------------------------------------------------------------
void func_02(void)
{
	cur_scp8();	// �����F�w��

	fprintf(Scp.fp, "BGL %s\n", cur_scp_str());
}
//---------------------------------------------------------------------------
void func_03(void)
{
	fprintf(Scp.fp, "GOT loc_%04X\n", cur_scp16());
}
//---------------------------------------------------------------------------
// call
void func_04(void)
{
	cur_scp16();

	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_05(void)
{
	u8 c = cur_scp8();		// �I�����̐�
	u8 v = cur_scp8();		// �Ԃ�l�̏ꏊ�i�ϐ��w��j
	s32 i;

	fprintf(Scp.fp, "SEL %d %d %d ", 10 + Scp.selCnt++,  c, v);		// �J�E���^�l��txt_re.py�ɂčU���I�����ɒu��

	for(i=0; i<c; i++)
	{
		s32 len = 0;

		// �P�I�𕪂̎��\��
		while(get_scp8() != 1)
		{
			u16 code = cur_scp16();
			code = jis2sjis(code);

			fprintf(Scp.fp, "%c%c", code >> 8, code);
		}

		// �I�[�L���X�L�b�v
		cur_scp8();

		if(i == c - 1)
		{
			fprintf(Scp.fp, "\n");
		}
		else
		{
			fprintf(Scp.fp, " ");
		}
	}
}
//---------------------------------------------------------------------------
// setup_zurizuri
void func_06(void)
{
	u8    n1 = cur_scp8();
	char* s1 = cur_scp_str();
	u8    n2 = cur_scp8();
	char* s2 = cur_scp_str();

	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_07(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	case 1: // zurizuri_scroll
	case 2: // scroll_up_two_screen
		fprintf(Scp.fp, "\n");
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
// free_ani_data
void func_08(void)
{
	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_09(void)
{
	u8 x  = cur_scp8();
	u8 op = cur_scp8();
	u8 y  = cur_scp8();

	switch(op)
	{
	case 0:   // var =  num
	case 1:   // var += num
	case 2:   // var -= num
	case 3:   // var *= num
	case 4:   // var /= num
	case 5:   // var %= num
	case 6:   // var =  rnd
	case 7:   // var =  var
	case 8:   // var += var
	case 9:   // var -= var
	case 0xa: // var *= var
	case 0xb: // var /= var
	case 0xc: // var %= var
	case 0xd: // var =  rnd % var
		fprintf(Scp.fp, "VAR %d %d %d\n", x, op, y);
		break;

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
	case 1: // var != num
	case 2: // var == num
	case 3: // var <= num
	case 4: // var >= num
	case 5: // var != var
	case 6: // var == var
	case 7: // var <= var
	case 8: // var >= var
		fprintf(Scp.fp, "JMP %d %d %d loc_%04X\n", x, op, y, z);
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
// set_xy
void func_0b(void)
{
	u16 x = cur_scp16();
	u16 y = cur_scp16();

	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
// define_dialog_box
void func_0c(void)
{
	u8 x1 = cur_scp8();
	u8 y1 = cur_scp8();
	u8 x2 = cur_scp8();
	u8 y2 = cur_scp8();

	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_0d(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	case 0: // show_prompt
	case 1: // hide_prompt
	case 2: // no_timeout_confirm
	case 3: // timeout_confirm
		fprintf(Scp.fp, "\n");
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
void func_0e(void)
{
	fprintf(Scp.fp, "LDS %s\n", cur_scp_str());
}
//---------------------------------------------------------------------------
void func_0f(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	// str
	case 0:
		fprintf(Scp.fp, "BGM 1 %s\n", cur_scp_str());		// 1�̓��[�v�w��B���[�v�łȂ��Ȃ�txt_re.py�ŕύX
		break;

	// void
	case 1:
		fprintf(Scp.fp, "\n");
		break;

	case 2:
		fprintf(Scp.fp, "BGS\n");		// BGM STOP
		break;

	case 7:
		fprintf(Scp.fp, "FMS\n");		// SE STOP
		break;

	case 8:
	case 9:
		fprintf(Scp.fp, "\n");
		break;

	// char
	case 3:
	case 4:
	case 6:
		cur_scp8();
		fprintf(Scp.fp, "\n");
		break;

	case 5:
		fprintf(Scp.fp, "FMX %d\n", cur_scp8());
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
// wait_for_key
void func_10(void)
{
	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_11(void)
{
	u8 cmd = cur_scp8();
	u8 spd = cur_scp8();

	switch(cmd)
	{
	case 1: // fade_out_black
	case 2: // fade_in_black
	case 3: // fade_out_white
	case 4: // fade_in_white
	case 5: // open_curtain  �H�`�G�t�F�N�g���\��
	case 6: // close_curtain �H�`�G�t�F�N�g�����w�i�\��
		fprintf(Scp.fp, "EFF %d\n", cmd);
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
// run_dos_prg
void func_12(void)
{
	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_13(void)
{
	cur_scp8();

	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_14(void)
{
//	fprintf(Scp.fp, "IDX %s\n", cur_scp_str());

	fprintf(Scp.fp, "BGL %s\n", cur_scp_str());
}
//---------------------------------------------------------------------------
void func_15(void)
{
//	fprintf(Scp.fp, "PIX %s\n", cur_scp_str());

	cur_scp_str();
	fprintf(Scp.fp, "\n");
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

//		fprintf(Scp.fp, "0x%02X 0x%02X 0x%02X 0x%02X\n", 0x16, cmd, v1, v2);
		Scp.ip += i;
		break;

	// char, int, int, int, char
	// w: rookies �ł͏�� 0
	// x: �X�N���[������̈�̍���
	// y: �X�^�[�g���C��
	// z: �G���h���C��
	// s: �X�s�[�h
	case 2:
		u8  w = cur_scp8();
		u16 x = cur_scp16();
		u16 y = (cur_scp16() == 0) ? 0 : 1;		// �ォ����
		u16 z = cur_scp16();
		u8  s = cur_scp8();

		fprintf(Scp.fp, "EFF %d\n", 9 + y);		// 9��GBA���̌��ߑł�
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
// �s��
void func_17(void)
{
	cur_scp8();

	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
// �s��
void func_18(void)
{
	fprintf(Scp.fp, "\n");
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
		// copy_sub_to_main(x1, y1, x2, y2)
		// �P���R�s�[�ifunc_11�̑����̃G�t�F�N�g�ԍ��j
		fprintf(Scp.fp, "EFF 7\n");
		break;

	case 2:
		// fill_rectangle(x1, y1, x2, y2, f)
		// ���h��Ԃ�
		fprintf(Scp.fp, "EFF 8\n");
		break;

	case 3:
		// clear_75(x1, y1, x2, y2)
		fprintf(Scp.fp, "\n");
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
// �s��
void func_1a(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	// int
	case 0:
		cur_scp16();
		fprintf(Scp.fp, "\n");
		break;

	// void
	case 1:
	case 3:
		fprintf(Scp.fp, "\n");
		break;

	// char
	case 2:
		cur_scp8();
		fprintf(Scp.fp, "\n");
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
// return
void func_1b(void)
{
	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
// set_palette
void func_1c(void)
{
	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_1d(void)
{
	fprintf(Scp.fp, "WAT %d\n", cur_scp8());
}
//---------------------------------------------------------------------------
void func_1e(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	// void
	case 1:
		// input_name
		fprintf(Scp.fp, "\n");
		break;

	// void
	case 2:
	case 3:
	case 4:
	case 5:
		// �s��
		fprintf(Scp.fp, "\n");
		break;

	// char
	case 6:
		// �N���A�t���O�������� save_hoehoe_dat
		cur_scp8();
		fprintf(Scp.fp, "\n");
		break;

	// void
	case 7: // change_destination_and_esc
	case 8: // change_destination_and_esc_to_default
	case 9: // save_load_menu
		fprintf(Scp.fp, "\n");
		break;

	default:
		assert(0);
		break;
	}
}
//---------------------------------------------------------------------------
// change_diskette
void func_1f(void)
{
	cur_scp8();

	fprintf(Scp.fp, "\n");
}
//---------------------------------------------------------------------------
void func_20(void)
{
	u8 cmd = cur_scp8();

	switch(cmd)
	{
	case 0: // enable_system_menu
	case 1: // disable_system_menu
	case 2: // make_check_point
		fprintf(Scp.fp, "\n");
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
		fprintf(Scp.fp, "MSG %s\n", embedded_string[i]);
	}
	else
	{
		fprintf(Scp.fp, "MSG �y%s�z", embedded_string[i]);
	}

	u8 cmd = get_scp8();

	if(cmd > 0x20 && cmd != 0x80)
	{
		func_jis();
	}
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
		fprintf(Scp.fp, "%04X ", Scp.ip);

		u8 cmd = Scp.pDat[Scp.ip];

		if(cmd > 0x20 && cmd != 0x80)
		{
			fprintf(Scp.fp, "MSG ");
			func_jis();

			continue;
		}

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

	fclose(Scp.fp);
}
//---------------------------------------------------------------------------
s32 msb(u32 var)
{
	s32 m;

	for(m=-1; var!=0; m++)
	{
		var >>= 1;
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

	printf("scp2txt... %s\n", argv[1]);


	FILE* fp = fopen(argv[1], "rb");

	if((fp = fopen(argv[1], "rb")) == NULL)
	{
		fprintf(stderr, "couldn't find scp file \"%s\"\n", argv[1]);
		exit(1);
	}


	u8 buf[4];

	// �t�@�C���`�F�b�N
	fread(buf, 4, 1, fp);

	if(memcmp(buf, "LZ96", 4) != 0)
	{
		fprintf(stderr, "this is NOT a scp file: \"%s\"\n", argv[1]);
		exit(1);
	}

	// �𓀃T�C�Y�擾
	fread(buf, 4, 1, fp);

	Scp.size = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0];
	Scp.pDat = calloc(Scp.size, sizeof(u8));

	if(Scp.pDat == NULL)
	{
		fprintf(stderr, "calloc error\n");
		exit(1);
	}

	// ��
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
