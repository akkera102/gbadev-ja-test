// 終末の過ごし方（Abogado Powers） scn2txt（可変選択肢未対応。002 タイトルメニュー、005 回想シーンは除外）
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

	s32    selCnt;							// 選択数
	u32    selJmp[MAX_SEL_CNT];				// ジャンプ先
	char*  selStr[MAX_SEL_CNT];				// テキスト

	u8     unKnown1[0x06];					// 謎1
	u8     unKnown2[MAX_SEL_CNT];			// 謎2
	u8     unKnown3[MAX_SEL_CNT][12];		// 謎3
	u8     unKnown4[MAX_SEL_CNT];			// 謎4

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

	// 謎1 0x00-0x05
	fprintf(Scn.fp, "unKnown1:");

	for(i=0; i<0x06; i++)
	{
		Scn.unKnown1[i] = BitGet8();

		fprintf(Scn.fp, " %02X", Scn.unKnown1[i]);
	}
	fprintf(Scn.fp, "\n");

	Scn.cmdOffset = BitGetSize() - BitGet16();
	Scn.selCnt = BitGet8() - 1;

	// 謎2 0x09-0x0D
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


	// 謎3 各12バイト
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

	// 謎4、選択肢メッセージ
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
// !コマンド
void ScnExecCmdSub1(void)
{
	u32 a, b, c;
	char* s;

	u8 op = BitGet8();
	fprintf(Scn.fp, "%c ", op);

	switch(op)
	{
	// 背景
	case 'g':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// 背景番号
		fprintf(Scn.fp, "%d %d", a, b);
		break;

	// 音楽再生
	case 'b':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// ファイル番号
		fprintf(Scn.fp, "%d %d", a, b);
		break;

	// 効果音再生
	case 'e':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// ファイル番号
		c = BitGet8();		// 必ず1
		fprintf(Scn.fp, "%d %d %d", a, b, c);
		break;

	// 立ち絵
	case 'x':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// ファイル番号
		c = BitGet8();		// 1:表示 0:非表示
		fprintf(Scn.fp, "%d %d %d", a, b, c);
		break;

	// スクリプトジャンプ（条件判定あり）
	case 'j':
		a = BitGet8();		// 必ず0
		b = BitGet8() + 1;	// ファイル番号
		fprintf(Scn.fp, "%d %d", a, b);
		break;

	// タイトル
	case 't':
		s = BitGetStr();	// 文字列
		fprintf(Scn.fp, "%s", s);
		break;

	// テキスト
	case 's':
		a = BitGet8();		// テキストのユニーク番号
		b = BitGet8();		// 謎
		c = BitGet8();		// 謎
		s = BitGetStr();	// 文字列

		fprintf(Scn.fp, "%d %d %d %s", a, b, c, s);
		break;

	// 謎
	case 'p':
		a = BitGet8();
		b = BitGet8();
		fprintf(Scn.fp, "%d %d", a, b);

		while((c = BitGet8()) != 0)
		{
			fprintf(Scn.fp, " %d", c);
		}
		break;

	// 謎
	case 'c':
		// EMPTY
		break;

	// 謎
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
// #コマンド
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
		a = BitGet8();		// 必ず0
		b = BitGet8();		// スクリプト番号
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

	// 条件式（!jスクリプトジャンプと連動）
	case 'i':
		for(i=0; i<9; i++)
		{
			z[i] = BitGet8();
		}

		// ＝ or ＞だけ
		assert(z[0] == '(');
		assert(z[1] == '[');
		assert(z[2] == 0);
		assert(z[4] == ']');
		assert(z[5] == '=' || z[5] == '>');
		assert(z[7] == ')');
		assert(z[8] == ';');

		fprintf(Scn.fp, "%d %c %d", z[3], z[5], z[6]);
		break;

	// エフェクト効果変更
	case 'W':
		a = BitGet8();		// エフェクト番号
		fprintf(Scn.fp, "%d", a);
		break;

	// 謎
	case 'b':
		a = BitGet8();
		b = BitGet8();
		fprintf(Scn.fp, "%d %d", a, b);
		break;

	// ウェイト
	case 't':
		op = BitGet8();
		fprintf(Scn.fp, "%c ", op);

		switch(op)
		{
		case 't':
			a = BitGet8();		// フレーム数？
			fprintf(Scn.fp, "%d", a);
			break;

		// 謎
		case 'w':
		case 'r':
		default:
			ScnError();
			break;
		}
		break;

	// 謎
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
	// ファイル終端チェック
	if(BitGetPos() == BitGetSize())
	{
		goto End;
	}

	// 選択肢
	u8 t = BitGet8();
	assert(t == 1);

End:
	fprintf(Scn.fp, "\n");
}
//---------------------------------------------------------------------------
// [コマンド
void ScnExecCmdSub4(void)
{
	fprintf(Scn.fp, "] ");

	u8 z[7];
	s32 i;

	for(i=0; i<7; i++)
	{
		z[i] = BitGet8();
	}

	// 代入か加算だけ
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
