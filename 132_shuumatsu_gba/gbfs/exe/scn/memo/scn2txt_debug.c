// �I���̉߂������iAbogado Powers�j scn2txt�i�ϑI�������Ή��B002 �^�C�g�����j���[�A005 ��z�V�[���͏��O�j
// gcc scn2txt_debug.c -s -o scn2txt_debug

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

//---------------------------------------------------------------------------
#define MAX_SEL_CNT					20

typedef unsigned char			 u8;
typedef char					 s8;
typedef unsigned short			u16;
typedef short					s16;
typedef unsigned int			u32;
typedef int						s32;

typedef struct {
	u8* p;
	s32 size;
	s32 pos;

} ST_BIT;

typedef struct {
	FILE*  fp;
	u16    cmdOffset;

	s32    selCnt;							// �I��
	u32    selJmp[MAX_SEL_CNT];				// �W�����v��
	char*  selStr[MAX_SEL_CNT];				// �e�L�X�g

	u8     unKnown1[0x06];					// ��1
	u8     unKnown2[MAX_SEL_CNT];			// ��2
	u8     unKnown3[MAX_SEL_CNT][12];		// ��3
	u8     unKnown4[MAX_SEL_CNT];			// ��4

} ST_SCN;


//---------------------------------------------------------------------------
ST_BIT Bit;
ST_SCN Scn;


//---------------------------------------------------------------------------
void  BitCalloc(char* fname);
void  BitFree(void);
void  BitSeek(s32 pos);
u8    BitGet8(void);
u16   BitGet16(void);
u32   BitGet32(void);
char* BitGetStr(void);
s32   BitGetPos(void);
s32   BitGetSize(void);

void  ScnExecHed(void);
void  ScnExecCmd(void);
void  ScnExecCmdSub1(void);
void  ScnExecCmdSub2(void);
void  ScnExecCmdSub3(void);
void  ScnExecCmdSub4(void);
void  ScnError(void);

//---------------------------------------------------------------------------
void BitCalloc(char* fname)
{
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't find file \"%s\"\n", fname);

		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Bit.size = ftell(fp);

	Bit.p = (u8*)calloc(Bit.size, sizeof(u8));

	if(Bit.p == NULL)
	{
		fprintf(stderr, "calloc error\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Bit.p, 1, Bit.size, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void BitFree(void)
{
	free(Bit.p);

	Bit.p = NULL;
}
//---------------------------------------------------------------------------
void BitSeek(s32 pos)
{
	Bit.pos = pos;
}
//---------------------------------------------------------------------------
u8 BitGet8(void)
{
	assert(Bit.pos < Bit.size);

	return Bit.p[Bit.pos++];
}
//---------------------------------------------------------------------------
u16 BitGet16(void)
{
	u16 b1 = BitGet8();
	u16 b2 = BitGet8() << 8;

	return b2 | b1;
}
//---------------------------------------------------------------------------
u32 BitGet32(void)
{
	u32 b1 = BitGet8();
	u32 b2 = BitGet8() <<  8;
	u32 b3 = BitGet8() << 16;
	u32 b4 = BitGet8() << 24;

	return b4 | b3 | b2 | b1;
}
//---------------------------------------------------------------------------
char* BitGetStr(void)
{
	char* pRet = Bit.p + Bit.pos;

	while(Bit.p[Bit.pos++] != '\0')
	{
		// EMPTY
	}

	return pRet;
}
//---------------------------------------------------------------------------
s32 BitGetPos(void)
{
	return Bit.pos;
}
//---------------------------------------------------------------------------
s32 BitGetSize(void)
{
	return Bit.size;
}
//---------------------------------------------------------------------------
void ScnExecHed(void)
{
	s32 i, j;

	// ��1 0x00-0x05
	fprintf(Scn.fp, "unKnown1:");

	for(i=0; i<0x06; i++)
	{
		Scn.unKnown1[i] = BitGet8();

		fprintf(Scn.fp, " %02X", Scn.unKnown1[i]);
	}
	fprintf(Scn.fp, "\n");

	Scn.cmdOffset = BitGetSize() - BitGet16();
	Scn.selCnt = BitGet8() - 1;

	// ��2 0x09-0x0D
	fprintf(Scn.fp, "unKnown2:");

	for(i=0; i<5; i++)
	{
		Scn.unKnown2[i] = BitGet8();

		fprintf(Scn.fp, " %02X", Scn.unKnown2[i]);
	}
	fprintf(Scn.fp, "\n");


	if(Scn.selCnt == 0)
	{
		return;
	}


	// ��3 �e12�o�C�g
	for(i=0; i<Scn.selCnt; i++)
	{
		fprintf(Scn.fp, "unKnown3[%d]:", i);

		for(j=0; j<12; j++)
		{
			Scn.unKnown3[i][j] = BitGet8();

			fprintf(Scn.fp, " %02X", Scn.unKnown3[i][j]);
		}

		fprintf(Scn.fp, "\n");
	}

	for(i=0; i<Scn.selCnt; i++)
	{
		Scn.selJmp[i] = BitGet32() + 1;
	}

	// ��4�A�I�������b�Z�[�W
	fprintf(Scn.fp, "unKnown4:", i);

	for(i=0; i<Scn.selCnt; i++)
	{
		Scn.unKnown4[i] = BitGet8();
		fprintf(Scn.fp, " %02X", Scn.unKnown4[i]);

		Scn.selStr[i] = BitGetStr();
	}
	fprintf(Scn.fp, "\n");


	printf("sel %d\n", Scn.selCnt);
	fprintf(Scn.fp, "%d", Scn.selCnt);

	for(i=0; i<Scn.selCnt; i++)
	{
		fprintf(Scn.fp, " %s", Scn.selStr[i]);
		fprintf(Scn.fp, " loc_0x%04X", Scn.selJmp[i]);
	}
	fprintf(Scn.fp, "\n");
}
//---------------------------------------------------------------------------
void ScnExecCmd(void)
{
	assert(BitGetPos() == Scn.cmdOffset);


	while(BitGetPos() < BitGetSize())
	{
		u8 op = BitGet8();
		fprintf(Scn.fp, "0x%04X(%04X): %c", BitGetPos() - 1, BitGetPos() - 1 - Scn.cmdOffset, op);

		switch(op)
		{
		case '!':
			ScnExecCmdSub1();
			break;

		case '#':
			ScnExecCmdSub2();
			break;

		case ';':
			ScnExecCmdSub3();
			break;

		case '[':
			ScnExecCmdSub4();
			break;

		default:
			ScnError();
			break;
		}
	}
}
//---------------------------------------------------------------------------
// !�R�}���h
void ScnExecCmdSub1(void)
{
	u32 a, b, c;
	char* s;

	u8 op = BitGet8();
	fprintf(Scn.fp, "%c ", op);

	switch(op)
	{
	// �w�i
	case 'g':
		a = BitGet8();		// �K��0
		b = BitGet8();		// �w�i�ԍ�
		fprintf(Scn.fp, "%d %d", a, b);
		break;

	// ���y�Đ�
	case 'b':
		a = BitGet8();		// �K��0
		b = BitGet8();		// �t�@�C���ԍ�
		fprintf(Scn.fp, "%d %d", a, b);
		break;

	// ���ʉ��Đ�
	case 'e':
		a = BitGet8();		// �K��0
		b = BitGet8();		// �t�@�C���ԍ�
		c = BitGet8();		// �K��1
		fprintf(Scn.fp, "%d %d %d", a, b, c);
		break;

	// �����G
	case 'x':
		a = BitGet8();		// �K��0
		b = BitGet8();		// �t�@�C���ԍ�
		c = BitGet8();		// 1:�\�� 0:��\��
		fprintf(Scn.fp, "%d %d %d", a, b, c);
		break;

	// �X�N���v�g�W�����v�i�������肠��j
	case 'j':
		a = BitGet8();		// �K��0
		b = BitGet8() + 1;	// �t�@�C���ԍ�
		fprintf(Scn.fp, "%d %d", a, b);
		break;

	// �^�C�g��
	case 't':
		s = BitGetStr();	// ������
		fprintf(Scn.fp, "%s", s);
		break;

	// �e�L�X�g
	case 's':
		a = BitGet8();		// �e�L�X�g�̃��j�[�N�ԍ�
		b = BitGet8();		// ��
		c = BitGet8();		// ��
		s = BitGetStr();	// ������

		fprintf(Scn.fp, "%d %d %d %s", a, b, c, s);
		break;

	// ��
	case 'p':
		a = BitGet8();
		b = BitGet8();
		fprintf(Scn.fp, "%d %d", a, b);

		while((c = BitGet8()) != 0)
		{
			fprintf(Scn.fp, " %d", c);
		}
		break;

	// ��
	case 'c':
		// EMPTY
		break;

	// ��
	case 'n':
	case 'r':
	case 'a':
	case 'v':
	case 'm':
	case 'i':
	case 'w':
	default:
		ScnError();
		break;
	}

	fprintf(Scn.fp, "\n");
}
//---------------------------------------------------------------------------
// #�R�}���h
void ScnExecCmdSub2(void)
{
	u32 z[9];
	u32 a, b, c;
	s32 i;

	u8 op = BitGet8();
	fprintf(Scn.fp, "%c ", op);

	switch(op)
	{
	// CALL
	case 'g':
		a = BitGet8();		// �K��0
		b = BitGet8();		// �X�N���v�g�ԍ�
		fprintf(Scn.fp, "%d %d", a, b);
		break;

	// RET
	case 'r':
		// EMPTY
		break;

	// ELSE
	case 'l':
		// EMPTY
		break;

	// ENDIF
	case 'n':
		// EMPTY
		break;

	// �������i!j�X�N���v�g�W�����v�ƘA���j
	case 'i':
		for(i=0; i<9; i++)
		{
			z[i] = BitGet8();
		}

		// �� or ������
		assert(z[0] == '(');
		assert(z[1] == '[');
		assert(z[2] == 0);
		assert(z[4] == ']');
		assert(z[5] == '=' || z[5] == '>');
		assert(z[7] == ')');
		assert(z[8] == ';');

		fprintf(Scn.fp, "%d %c %d", z[3], z[5], z[6]);
		break;

	// �G�t�F�N�g���ʕύX
	case 'W':
		a = BitGet8();		// �G�t�F�N�g�ԍ�
		fprintf(Scn.fp, "%d", a);
		break;

	// ��
	case 'b':
		a = BitGet8();
		b = BitGet8();
		fprintf(Scn.fp, "%d %d", a, b);
		break;

	// �E�F�C�g
	case 't':
		op = BitGet8();
		fprintf(Scn.fp, "%c ", op);

		switch(op)
		{
		case 't':
			a = BitGet8();		// �t���[�����H
			fprintf(Scn.fp, "%d", a);
			break;

		// ��
		case 'w':
		case 'r':
		default:
			ScnError();
			break;
		}
		break;

	// ��
	case 'x':
	case 's':
	case 'f':
	case 'e':
	case 'w':
	default:
		ScnError();
		break;
	}

	fprintf(Scn.fp, "\n");
}
//---------------------------------------------------------------------------
void ScnExecCmdSub3(void)
{
	// �t�@�C���I�[�`�F�b�N
	if(BitGetPos() == BitGetSize())
	{
		goto End;
	}

	// �I����
	u8 t = BitGet8();
	assert(t == 1);

End:
	fprintf(Scn.fp, "\n");
}
//---------------------------------------------------------------------------
// [�R�}���h
void ScnExecCmdSub4(void)
{
	fprintf(Scn.fp, "] ");

	u8 z[7];
	s32 i;

	for(i=0; i<7; i++)
	{
		z[i] = BitGet8();
	}

	// ��������Z����
	assert(z[0] == 0);
	assert(z[2] == ']');
	assert(z[3] == '=' || z[3] == '+');
	assert(z[4] == 'V');

	fprintf(Scn.fp, "%d %c %d\n", z[1], z[3], z[5] | (z[6] << 8));
}
//---------------------------------------------------------------------------
void ScnError(void)
{
	printf("\nERROR pos=0x%X\n", BitGetPos());

	fclose(Scn.fp);
	exit(1);
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("scn2txt [SCN File]\n");

		exit(0);
	}

	printf("scn2txt... %s\n", argv[1]);

	BitCalloc(argv[1]);


	char fname[30];

	strncpy(fname, argv[1], 20);
	char* p = strchr(fname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	p[0] = '.';
	p[1] = 't';
	p[2] = 'x';
	p[3] = 't';
	p[4] = '\0';

	Scn.fp = fopen(fname, "wb");

	if(Scn.fp == NULL)
	{
		fprintf(stderr, "couldn't open file\n");

		exit(1);
	}

	ScnExecHed();
	ScnExecCmd();

	fclose(Scn.fp);

	BitFree();

	return 0;
}
