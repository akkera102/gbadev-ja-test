// スクリプトデコーダー（可変選択肢未対応（未完成）002 タイトルメニュー、005 回想シーンは除外）
// gcc scn2txt.c -s -o scn2txt

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

//---------------------------------------------------------------------------
#define MAX_SCN_SEL_CNT					20
#define MAX_SCN_TMP_SIZE				0x1000

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
	u32    selJmp[MAX_SCN_SEL_CNT];			// ジャンプ先
	char*  selStr[MAX_SCN_SEL_CNT];			// テキスト

	u8     unKnown1[0x06];					// 謎1
	u8     unKnown2[MAX_SCN_SEL_CNT];		// 謎2
	u8     unKnown3[MAX_SCN_SEL_CNT][12];	// 謎3
	u8     unKnown4[MAX_SCN_SEL_CNT];		// 謎4

	char   tmp[MAX_SCN_TMP_SIZE];			// 文字列編集ワークエリア
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
char* BitGetStrFix(void);
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
char* BitGetStrFix(void)
{
	char* s = BitGetStr();
	char* d = Scn.tmp;

	for(;;)
	{
		u8 c1 = *(s+0);
		u8 c2 = *(s+1);

		if(c1 == '\0')
		{
			break;
		}

		if(c1 == '_' && (c2 == 'r' || c2 == 's' || c2 == 't' || c2 == 'b' || c2 == 'n' || c2 == 'w'))
		{
			s += 2;

			*d++ = c1;
			*d++ = c2;

			continue;
		}

		// 全角空白
		if(c1 == 0x81 && c2 == 0x40)
		{
			s += 2;

			continue;
		}

		// 全角
		if(((c1)>=0x81 && (c1)<=0x9f) || ((c1)>=0xe0 && (c1)<=0xef))
		{
			s += 2;

			*d++ = c1;
			*d++ = c2;

			continue;
		}

		// 半角
		s++;
		u16 z;

		if(c1 >= 'a' && c1 <= 'z')
		{
			z = 0x8220 + c1;
		}
		else if(c1 >= 'A' && c1 <= 'Z')
		{
			z = 0x821F + c1;
		}
		else if(c1 >= '0' && c1 <= '9')
		{
			z = 0x821F + c1;
		}
		else if(c1 == '.')
		{
			z = 0x8144;
		}
		else if(c1 == '!')
		{
			z = 0x8149;
		}
		else if(c1 == 0xa2)		// ｢ typo?
		{
			z = 0x8175;
		}
		else if(c1 == '-')
		{
			z = 0x817C;
		}
		else
		{
			printf("%c %x\n", c1, c1);
			assert("c1" && 0);
		}

		*d++ = z >> 8;
		*d++ = z & 0xff;
	}

	*d++ = '\0';
	assert(d - Scn.tmp < MAX_SCN_TMP_SIZE);

	return Scn.tmp;
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

	for(i=0; i<0x06; i++)
	{
		Scn.unKnown1[i] = BitGet8();
	}

	Scn.cmdOffset = BitGetSize() - BitGet16();
	Scn.selCnt = BitGet8() - 1;

	for(i=0; i<5; i++)
	{
		Scn.unKnown2[i] = BitGet8();
	}

	// printf("%d\n", Scn.selCnt);

	// 選択肢なし or あり
	if(Scn.selCnt == 0)
	{
		fprintf(Scn.fp, "%d\n", Scn.selCnt);

		return;
	}
	fprintf(Scn.fp, "%d", Scn.selCnt);

	for(i=0; i<Scn.selCnt; i++)
	{
		for(j=0; j<12; j++)
		{
			Scn.unKnown3[i][j] = BitGet8();
		}
	}

	for(i=0; i<Scn.selCnt; i++)
	{
		Scn.selJmp[i] = BitGet32() + 1;
	}

	for(i=0; i<Scn.selCnt; i++)
	{
		Scn.unKnown4[i] = BitGet8();
		Scn.selStr[i] = BitGetStr();
	}

	for(i=0; i<Scn.selCnt; i++)
	{
		fprintf(Scn.fp, " %s", Scn.selStr[i]);
		fprintf(Scn.fp, " %04X", Scn.selJmp[i] + Scn.cmdOffset);
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
		fprintf(Scn.fp, "%04X %c", BitGetPos() - 1, op);

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
	u32 a, b, c, d, e;
	char* s;

	u8 op = BitGet8();
	fprintf(Scn.fp, "%c", op);

	switch(op)
	{
	// 背景
	case 'g':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// 背景番号
		fprintf(Scn.fp, " %d", b);
		break;

	// 音楽再生
	case 'b':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// ファイル番号
		fprintf(Scn.fp, " %d", b);
		break;

	// 効果音再生
	case 'e':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// ファイル番号
		c = BitGet8();		// 必ず1
		fprintf(Scn.fp, " %d", b);
		break;

	// 立ち絵
	case 'x':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// ファイル番号
		c = BitGet8();		// 1:表示 0:非表示
		fprintf(Scn.fp, " %d %d", b, c);
		break;

	// スクリプトジャンプ（条件判定あり）
	case 'j':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// スクリプト番号
		fprintf(Scn.fp, " %d", b);
		break;

	// タイトル
	case 't':
		s = BitGetStrFix();	// 文字列
		fprintf(Scn.fp, " %s", s);
		break;

	// テキスト
	case 's':
		a = BitGet8();		// テキストのユニーク番号1
		b = BitGet8();		// テキストのユニーク番号2
		c = BitGet8();		// 謎
		s = BitGetStrFix();	// 文字列

		d = (b * 256 + a) / 8;
		e = (b * 256 + a) % 8;

		fprintf(Scn.fp, " %d %d", d, e);

		if(s[0] != '\0')
		{
			fprintf(Scn.fp, " %s", s);
		}
		break;

	// 謎
	case 'p':
		a = BitGet8();
		b = BitGet8();

		while((c = BitGet8()) != 0)
		{
			// EMPTY
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
	fprintf(Scn.fp, "%c", op);

	switch(op)
	{
	// CALL
	case 'g':
		a = BitGet8();		// 必ず0
		b = BitGet8();		// スクリプト番号
		fprintf(Scn.fp, " %d", b);
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

		fprintf(Scn.fp, " %d %c %d", z[3], z[5], z[6]);
		break;

	// エフェクト
	case 'W':
		a = BitGet8();		// エフェクト番号

		if(a == 0)
		{
			// αフェード（高速化）
			a = 200;
		}
		else if(a == 1)
		{
			// カーテン
			a = 1;
		}
		else if(a == 11)
		{
			// 通常コピー（高速化）
			a = 201;
		}
		else
		{
			// CLS
			a--;
		}

		fprintf(Scn.fp, " %d", a);
		break;

	// 謎
	case 'b':
		a = BitGet8();
		b = BitGet8();
		break;

	// ウェイト
	case 't':
		a = BitGet8();
		b = BitGet8();	// ウェイト値

		assert(a == 't');
		fprintf(Scn.fp, " %d", b);
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
	// 選択肢コマンド or ファイル終端記号
	if(BitGetPos() != BitGetSize())
	{
		// 選択肢コマンドの場合、パラメータ1個で固定値1
		// skip
		BitGet8();
	}

	fprintf(Scn.fp, ";\n");
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
