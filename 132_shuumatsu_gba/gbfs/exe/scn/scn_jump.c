// �W�����v�I�t�Z�b�g���X�V
// gcc scn_jump.c -s -o scn_jump

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <assert.h>

//---------------------------------------------------------------------------
#define SCN_MAX_SEL_CNT				5

typedef unsigned char   u8;
typedef char            s8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;
typedef int            s32;


typedef struct {
	u8*  pSrc;
	u8*  pAdr;
	u8*  pCmd;
	s32  fsize;
	s32  pos;

	s32  selCnt;
	u8*  pSel[SCN_MAX_SEL_CNT];
	s32  selPos[SCN_MAX_SEL_CNT];
	bool isSel[SCN_MAX_SEL_CNT];

} ST_SCN;

//---------------------------------------------------------------------------
ST_SCN Scn;


//---------------------------------------------------------------------------
void  ScnInit(char* fname);
void  ScnFree(void);
void  ScnExec(void);

u8    ScnCurChr(void);
char* ScnCurStr(void);
s32   ScnCurNum(void);

void  ScnSkipStr(void);
void  ScnSkipStr2(s32 cnt);

//---------------------------------------------------------------------------
void ScnInit(char* fname)
{
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "error fp\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Scn.fsize = ftell(fp);

	Scn.pSrc = calloc(Scn.fsize, sizeof(u8));

	if(Scn.pSrc == NULL)
	{
		fprintf(stderr, "error calloc\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Scn.pSrc, 1, Scn.fsize, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void ScnFree(void)
{
	free(Scn.pSrc);
	Scn.pSrc = NULL;
}
//---------------------------------------------------------------------------
void ScnExec(void)
{
	Scn.selCnt = ScnCurNum();
	assert(Scn.selCnt < SCN_MAX_SEL_CNT);

	if(Scn.selCnt == 0)
	{
		return;
	}

	// �W�����v�A�h���X��ύX���܂�
	ScnSkipStr();

	s32 i;

	for(i=0; i<Scn.selCnt; i++)
	{
		ScnSkipStr();

		Scn.pSel[i] = ScnCurStr();
		ScnSkipStr();
	}

	// �e�s�̓A�h���X�A���߁A�σI�v�V����
	while(Scn.pos < Scn.fsize)
	{
		Scn.pAdr = ScnCurStr();
		ScnSkipStr();

		Scn.pCmd = ScnCurStr();
		ScnSkipStr();

		// �I�����A�h���X�`�F�b�N
		for(i=0; i<Scn.selCnt; i++)
		{
			if(strcmp(Scn.pAdr, Scn.pSel[i]) == 0 && Scn.isSel[i] == false)
			{
				Scn.isSel[i] = true;

				Scn.selPos[i] = Scn.pAdr - Scn.pSrc;
				assert(Scn.selPos[i] < 0x10000);

				u8* d = Scn.pSel[i];

				*d++ = Scn.selPos[i] >>  0;
				*d++ = Scn.selPos[i] >>  8;
				*d++ = Scn.selPos[i] >> 16;
				*d++ = Scn.selPos[i] >> 24;

				// printf("%d! %x\n", i, Scn.selPos[i]);
			}
		}

		switch(Scn.pCmd[0])
		{
		case '!':
			switch(Scn.pCmd[1])
			{
			// �w�i
			case 'g':
				ScnSkipStr2(1);
				break;
			// ���y�Đ�
			case 'b':
				ScnSkipStr2(1);
				break;
			// ���ʉ��Đ�
			case 'e':
				ScnSkipStr2(1);
				break;
			// �����G
			case 'x':
				ScnSkipStr2(2);
				break;
			// �X�N���v�g�W�����v�i�������肠��j
			case 'j':
				ScnSkipStr2(1);
				break;
			// �^�C�g��
			case 't':
				ScnSkipStr2(1);
				break;
			// �e�L�X�g�̃��j�[�N�ԍ��iGBA�ŕύX�j
			case 's':
				ScnSkipStr2(2);
				break;

			default:
				goto Err;
			}
			break;

		case '#':
			switch(Scn.pCmd[1])
			{
			// CALL
			case 'g':
				ScnSkipStr2(1);
				break;
			// RET, ELSE, ENDIF
			case 'r':
			case 'l':
			case 'n':
				// EMPTY
				break;
			// �������i!j�X�N���v�g�W�����v�ƘA���j
			case 'i':
				ScnSkipStr2(3);
				break;
			// �G�t�F�N�g
			case 'W':
				ScnSkipStr2(1);
				break;
			// �E�F�C�g
			case 't':
				ScnSkipStr2(1);
				break;

			default:
				goto Err;
			}
			break;

		// �I����
		case ';':
			assert(Scn.pCmd[1] == ';');
			break;

		// ��������Z
		case '[':
			assert(Scn.pCmd[1] == ']');
			ScnSkipStr2(3);
			break;

		// �e�L�X�g�\���iGBA�Œǉ��j
		case '_':
			ScnSkipStr2(1);
			break;

		default:
			goto Err;
		}
	}

	for(i=0; i<Scn.selCnt; i++)
	{
		if(Scn.isSel[i] == true)
		{
			continue;
		}

		fprintf(stderr, "offset not found %d\n", i);
	}

	return;

Err:

	fprintf(stderr, "parse error pos:0x%04X %s %s\n", Scn.pos, Scn.pAdr, Scn.pCmd);
}
//---------------------------------------------------------------------------
u8 ScnCurChr(void)
{
	assert(Scn.pos < Scn.fsize);

	return Scn.pSrc[Scn.pos++];
}
//---------------------------------------------------------------------------
char* ScnCurStr(void)
{
	return Scn.pSrc + Scn.pos;
}
//---------------------------------------------------------------------------
s32 ScnCurNum(void)
{
	s32 i = Scn.pos;
	s32 ret = 0;

	do {
		ret = (ret * 10) + (Scn.pSrc[i++] - '0');

	} while((Scn.pSrc[i] >= '0') && (Scn.pSrc[i] <= '9'));

	return ret;
}
//---------------------------------------------------------------------------
void ScnSkipStr(void)
{
	u8 c;

	do {
		c = ScnCurChr();

	} while(c != '\0');
}
//---------------------------------------------------------------------------
void ScnSkipStr2(s32 cnt)
{
	s32 i;

	for(i=0; i<cnt; i++)
	{
		ScnSkipStr();
	}
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "scn_jump [filename]\n");
		exit(1);
	}

	printf("scn_jump... %s\n", argv[1]);

	ScnInit(argv[1]);
	ScnExec();


	char dname[30];

	strncpy(dname, argv[1], 20);
	char* p = strchr(dname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	p[0] = '.';
	p[1] = 'b';
	p[2] = 'i';
	p[3] = 'n';
	p[4] = '\0';

	FILE* fp = fopen(dname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open fille\n");

		exit(1);
	}

	fwrite(Scn.pSrc, Scn.fsize, 1, fp);
	fclose(fp);


	ScnFree();

	return 0;
}
