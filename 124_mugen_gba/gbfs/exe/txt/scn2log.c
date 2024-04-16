// PC98 夢幻夜想曲 スクリプトデコーダー
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdbool.h>

//---------------------------------------------------------------------------
#define SYS_DEBUG_FLAG					0
#define SYS_DEBUG_START_ADR				0x100

#define SYS_MAX_REG_CNT					0x10000
#define SYS_MAX_STACK_CNT				0x100
#define SYS_MAX_WORK_CNT				10000
#define SYS_MAX_FNAME_CNT				20
#define SYS_MAX_STR_CNT					10
#define SYS_MAX_STR_LEN					20

#define OPE_MAX_STR_CNT					20
#define OPE_MAX_STR_SIZE				50
#define OPE_MAX_WORK_CNT				10000
#define OPE_MAX_FNAME_CNT				20
#define OPE_MAX_SEL_CNT					200

#define SRC_MAX_BUFFER_SIZE				0x8000
#define SRC_MAX_FILE_SIZE				0x4000
#define SRC_LIB_FNAME					"mug_sub.scn"

//---------------------------------------------------------------------------
typedef unsigned char   u8;
typedef char            s8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;
typedef int            s32;

// 入力シナリオ
typedef struct {
	u8  buf[SRC_MAX_BUFFER_SIZE];
	s32 size;
} ST_SRC;

// 出力テキスト
typedef struct {
	FILE* fp;
} ST_DST;

// スクリプト
typedef struct {
	// ファイル名
	char fname[SYS_MAX_FNAME_CNT];

	// 変数
	u16  reg[SYS_MAX_REG_CNT];
	u16  regLoop;
	u16  regComp;

	// 文字列変数
	u8   str[SYS_MAX_STR_CNT][SYS_MAX_STR_LEN];

	// スタック
	u16  stackBuf[SYS_MAX_STACK_CNT];
	s32  stackCnt;

	// ワークバッファ
	char printBuf[SYS_MAX_WORK_CNT];
	char writeBuf[SYS_MAX_WORK_CNT];

	bool isDebug;
} ST_SYS;

// コマンド
typedef struct {
	// 操作
	s32  cmdOrder;
	char cmdBuf[OPE_MAX_SEL_CNT];

	// テキスト
	s32  strCnt;
	char strBuf[OPE_MAX_STR_CNT][OPE_MAX_STR_SIZE];

	// ワークバッファ
	char workBuf[OPE_MAX_WORK_CNT];
} ST_OPE;

// コマンドテーブル
typedef struct {
	char fname[OPE_MAX_FNAME_CNT];
	char sel[OPE_MAX_SEL_CNT];
} ST_OPE_TABLE;

//---------------------------------------------------------------------------
// 選択肢コマンド一覧
ST_OPE_TABLE OpeTable[] = {
	{ "0_00.scn", "112344444355111" },
	{ "1_00.scn", "" },
	{ "1_01.scn", "1112121223333433331212124111213212223321121231313132323233332" },
	{ "1_02.scn", "1212222232434" },
	{ "1_26.scn", "11122222333" },
	{ "1_03.scn", "1222122223333" },
	{ "1_24.scn", "1112222333333" },
	{ "1_13.scn", "1212122222322222222" },
	{ "1_19.scn", "1222223333" },
	{ "1_18.scn", "1212222233" },
	{ "1_33.scn", "1112233222211121213113" },
	{ "1_28.scn", "11212222223" },
	{ "1_29.scn", "1212134" },
	{ "1_30.scn", "123" },
	{ "1_17.scn", "123" },
	{ "1_27.scn", "1223" },
	{ "1_06.scn", "123" },
	{ "1_07.scn", "1212222233" },
	{ "1_05.scn", "123" },
	{ "1_10.scn", "12122223" },
	{ "1_12.scn", "" },
	{ "1_34.scn", "122231313132333333333333331121233222212221112222" },
	{ "1_35.scn", "1213222222222231313232323333333333333333111212222223334111222123" },
	{ "1_36.scn", "123" },
	{ "1_58.scn", "1122" },
	{ "1_49.scn", "11122223333" },
	{ "1_54.scn", "122222" },
	{ "1_61.scn", "12212231313132323233333334343434344" },
	{ "1_64.scn", "1223" },
	{ "1_66.scn", "" },					// 初期変数変更　！！中身は1_36.scn！！
	{ "2_00.scn", "111221222223243" },
	{ "2_20.scn", "123" },
	{ "2_24.scn", "1222" },
	{ "2_18.scn", "1112222231313131323232323333333333" },
	{ "2_01.scn", "122223231313131313232323333333333" },
	{ "2_33.scn", "11111221111121212222223131313131313131313232323233333333" },
	{ "2_29.scn", "11223" },
	{ "2_34.scn", "122222" },
	{ "2_02.scn", "122313131323232333333" },
	{ "2_03.scn", "123131313232323333332" },
	{ "2_30.scn", "1221312222" },
	{ "2_08.scn", "11121222222223" },
	{ "2_31.scn", "12234" },
	{ "2_27.scn", "11212121223" },
	{ "2_28.scn", "1112234" },
	{ "2_35.scn", "" },
	{ "2_55.scn", "12222111223322222" },
	{ "2_41.scn", "12222223" },
	{ "2_46.scn", "122223333" },
	{ "2_61.scn", "1222331222222" },
	{ "2_64.scn", "122222233334" },
	{ "2_68.scn", "" },
	{ "2_71.scn", "122222222" },
	{ "2_62.scn", "12222" },
	{ "3_00.scn", "11122211221222233331222222" },
	{ "3_01.scn", "11222222233333333114111221212233333" },
	{ "3_02.scn", "11122333333331222222222112233" },
	{ "3_03.scn", "11112223333" },
	{ "3_04.scn", "122222222223" },
	{ "3_05.scn", "112222231112221211" },
	{ "3_06.scn", "12122222333444511222334" },
	{ "3_07.scn", "12341123333441122222214" },
	{ "3_08.scn", "12222" },
	{ "3_09.scn", "" },
	{ "3_10.scn", "111213222222222" },
	{ "4_00.scn", "113" },
	{ "4_24.scn", "" },
	{ "4_14.scn", "122222333334" },
	{ "4_26.scn", "12223333333" },
	{ "4_29.scn", "122223332213111112122223333332222222233333333" },
	{ "4_30.scn", "111122233334" },
	{ "4_31.scn", "11121222212122222222" },
	{ "4_32.scn", "11112223111112223" },
	{ "5_00.scn", "" },
	{ "5_01.scn", "113" },
	{ "5_16.scn", "122223" },
	{ "5_28.scn", "1222222221" },
	{ "5_26.scn", "122222223" },
	{ "5_31.scn", "122222" },
	{ "5_23.scn", "122222" },
	{ "5_32.scn", "12222231" },
	{ "5_33.scn", "" },
	{ "5_34.scn", "112222223" },
	{ "5_35.scn", "" },
	{ "5_36.scn", "11122222222" },
	{ "5_37.scn", "" },
	{ "5_38.scn", "111" },
	{ "5_62.scn", "11122222233333333333333" },
	{ "5_63.scn", "123" },
	{ "5_64.scn", "1111223333333222" },
	{ "5_65.scn", "" },
	{ "5_66.scn", "" },
	{ "6_00.scn", "" },
	{ "6_01.scn", "11223333" },
	{ "6_02.scn", "1222223333" },
	{ "6_03.scn", "12222222222222222223331111" },
	{ "6_04.scn", "1222" },
	{ "6_05.scn", "1222" },
	{ "6_06.scn", "122222222222" },
	{ "6_26.scn", "12222222223" },
	{ "6_27.scn", "122223" },
	{ "6_28.scn", "12223" },
	{ "6_30.scn", "1222223" },
	{ "6_29.scn", "122223" },
	{ "6_16.scn", "12223" },
	{ "6_12.scn", "1223" },
	{ "6_13.scn", "1223" },
	{ "6_14.scn", "12222223" },
	{ "6_15.scn", "1222223" },
	{ "6_11.scn", "122223" },
	{ "6_25.scn", "1223" },
	{ "6_20.scn", "122222223" },
	{ "6_21.scn", "122223" },
	{ "6_17.scn", "1222223" },
	{ "6_19.scn", "122222" },
	{ "6_31.scn", "1122223331112132222222221112131322222" },
	{ "6_32.scn", "11121213222222333333333333333333333311222" },
	{ "6_33.scn", "12222222222212112121222222222323231112222222222211111111111" },
	{ "6_34.scn", "111111111122233332" },
	{ "6_35.scn", "1" },					// 分岐。2も選択可
	{ "7_00.scn", "" },
	{ "7_02.scn", "112222222" },
	{ "7_01.scn", "11122222" },
	{ "7_03.scn", "111212222233333411121222222211111111111212" },
	{ "7_04.scn", "" },
	{ "7_05.scn", "1112222222211122121212121313141414111111" },
	{ "7_06.scn", "111212222231313131313131313131323232323232323333333333343434343434353535353536363636361122231313132323233333334343434" },
	{ "7_07.scn", "1222221112222211221123" },
	{ "7_34.scn", "1223" },
	{ "7_37.scn", "112222" },
	{ "7_35.scn", "111222222223" },
	{ "7_19.scn", "122223" },
	{ "7_23.scn", "1222223" },
	{ "7_25.scn", "12222" },
	{ "7_08.scn", "121223" },
	{ "7_12.scn", "121222222223" },
	{ "7_22.scn", "12223" },
	{ "7_33.scn", "11111112122121222222" },
	{ "7_38.scn", "1112221112231112222313212221112222231313131323232323232" },
	{ "7_39.scn", "111122221" },
	{ "7_40.scn", "1112132222222" },
	{ "7_41.scn", "11221113333331133132" },
	{ "7_42.scn", "11112222233" },
	{ "8_00.scn", "" },
	{ "8_01.scn", "1112222222" },
	{ "8_02.scn", "123" },
	{ "8_19.scn", "122222" },
	{ "8_13.scn", "12222222" },
	{ "8_16.scn", "1222222" },
	{ "8_28.scn", "11222" },
	{ "8_25.scn", "11122222313131313232323233333333334" },
	{ "8_29.scn", "2" },
	{ "8_30.scn", "1112222223" },
	{ "8_32.scn", "121222324242425121212223232222222222" },
	{ "8_33.scn", "11122233333122221122212222221121222332312223" },
	{ "8_34.scn", "1222212222222222122222" },
	{ "8_35.scn", "22222221111111112223" },
	{ "9_00.scn", "122222" },
	{ "9_01.scn", "122222" },
	{ "9_24.scn", "11222223131323232333334343434" },
	{ "9_26.scn", "1222222222" },
	{ "9_31.scn", "1112222122" },
	{ "9_08.scn", "12222222" },
	{ "9_13.scn", "122222" },
	{ "9_28.scn", "12" },
	{ "9_29.scn", "111222223" },
	{ "9_32.scn", "111122222111111222222112222222" },
	{ "9_33.scn", "1112231122222223311222" },
	{ "9_34.scn", "" },
	{ "9_36.scn", "1222223" },
	{ "9_37.scn", "1122222223" },
	{ "9_38.scn", "12223" },
	{ "9_39.scn", "11122" },
	{ "9_40.scn", "112233333112122222212221222122212222" },
	{ "9_41.scn", "1222112121212121211222111212122222222222222" },
	{ "9_42.scn", "111" },
	{ "a_00.scn", "" },
	{ "a_01.scn", "12222222111111122121212122111221212111222313131313232321222" },
	{ "a_01b.scn", "1111111222" },
	{ "a_02.scn", "1111" },
	{ "a_03.scn", "11111" },
	{ "a_04.scn", "111" },
	{ "a_05.scn", "1112111112122222222333333331122212222222111111111" },
	{ "a_06.scn", "11122311112111122222223" },
	{ "b_00.scn", "" },
	{ "b_03.scn", "12223" },
	{ "b_02.scn", "12222223" },
	{ "b_04.scn", "111222223" },
	{ "b_01.scn", "1222222" },
	{ "b_05.scn", "1212222232333111212122223311121221212121222111111222212" },
	{ "b_06.scn", "1222231313132323333333333333333331222222222222" },
	{ "b_07.scn", "122131313222222" },
	{ "b_08.scn", "122222111222211111111" },
	{ "b_14.scn", "1121222223232323233" },
	{ "b_09.scn", "122222" },
	{ "b_11.scn", "122222" },
	{ "b_10.scn", "122222" },
	{ "b_13.scn", "111222223" },
	{ "b_15.scn", "" },
	{ "b_16.scn", "111212132122222231222112222211121221312121222223232323112222333333333" },
	{ "b_17.scn", "111122223333312212" },
	{ "c_00.scn", "12222222222228" },
	{ "c_03.scn", "" },			// 摩耶
	{ "c_07.scn", "" },			// 美和子
	{ "c_04.scn", "" },			// 深紗緒
	{ "c_05.scn", "" },			// 由羅
	{ "c_06.scn", "1" },		// 沙里
	{ "c_02.scn", "" },			// 雪菜
	{ "c_08.scn", "1" },		// 亜璃沙
	{ "c_01.scn", "1" },		// 女主人
	{ "c_17.scn", "" },			// 美和子2　！！中身はc_07.scn！！
	{ "c_16.scn", "2" },		// 沙里2　　！！中身はc_06.scn！！
	{ "c_18.scn", "2" },		// 亜璃沙2　！！中身はc_08.scn！！
	{ "c_11.scn", "2" },		// 女主人2　！！中身はc_01.scn！！
};

//---------------------------------------------------------------------------
ST_SRC Src;
ST_DST Dst;
ST_SYS Sys;
ST_OPE Ope;


//---------------------------------------------------------------------------
void  SrcInit(char* fname);

void  DstInit(char* fname);
void  DstWrite(char* format, ...);
void  DstFree(void);

void  SysInit(char* fname);
void  SysExec(void);
u16   SysGetNum(u16 adr);
char* SysGetFile(u16 adr);
void  SysSetStr(s32 no, u16 adr);
void  SysPrint(u16 adr);
void  SysPushStack(u16 adr);
u16   SysPopStack(void);
void  SysDebug(char* format, ...);
char  SysGetHex2Chr(u8 hex);

void  OpeInit(char* fname, char* buf);
u16   OpeGetSel(void);
void  OpeAddSel(u16 adr);
void  OpeClrSel(void);

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("file not found\n");
		exit(1);
	}
	printf("scn2log... %s\n", argv[1]);


	SrcInit(argv[1]);
	DstInit(argv[1]);
	SysInit(argv[1]);

	if(argc == 3)
	{
		// 選択肢マニュアル操作
		OpeInit(argv[1], argv[2]);
	}
	else
	{
		// 用意した選択肢を使用
		OpeInit(argv[1], "");
	}
	SysExec();

	DstFree();

	return 0;
}
//---------------------------------------------------------------------------
void SrcInit(char* fname)
{
	FILE* fp;

	// get file size
	fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "Error: open src\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Src.size = ftell(fp);
	assert(Src.size < SRC_MAX_FILE_SIZE);

	// read file
	fseek(fp, 0, SEEK_SET);
	fread(Src.buf, 1, Src.size, fp);
	fclose(fp);


	// script library. get file size
	fp = fopen(SRC_LIB_FNAME, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "Error: open mug_scn\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	u32 size = ftell(fp);
	assert(size < SRC_MAX_FILE_SIZE);

	// script library. read file offset 0x4000
	fseek(fp, 0, SEEK_SET);
	fread(&Src.buf[0x4000], 1, size, fp);
	fclose(fp);
}
//---------------------------------------------------------------------------
void DstInit(char* fname)
{
	char sname[20];
	strncpy(sname, fname, 20);

	char* p = strchr(sname, '.');
	p[1] = 'l';
	p[2] = 'o';
	p[3] = 'g';

	Dst.fp = fopen(sname, "wb");

	if(Dst.fp == NULL)
	{
		printf("Error: Save %s\n", sname);
		exit(1);
	}
}
//---------------------------------------------------------------------------
void DstWrite(char* format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsprintf(Sys.writeBuf, format, ap);
	va_end(ap);

	fprintf(Dst.fp, "%s", Sys.writeBuf);
}
//---------------------------------------------------------------------------
void DstFree(void)
{
	fclose(Dst.fp);
}
//---------------------------------------------------------------------------
void SysInit(char* fname)
{
	memset(&Sys, 0x00, sizeof(ST_SYS));

	strcpy(Sys.fname, fname);

	s32 i;

	for(i=0; i<SYS_MAX_STR_CNT; i++)
	{
		strcpy(Sys.str[i], "■■■");
	}
}
//---------------------------------------------------------------------------
void SysExec(void)
{
	//
	// 例外処理
	//

	if(strcmp(Sys.fname, "1_36.scn") == 0)
	{
		// 目が冴えてる
		Sys.reg[128]  = 9999;
	}
	else if(strcmp(Sys.fname, "1_66.scn") == 0)
	{
		// 眠気が襲ってきた
		Sys.reg[144]  = 2048;
		Sys.reg[145]  = 30;
	}
	else if(strcmp(Sys.fname, "2_00.scn") == 0)
	{
		// 朝だ、のメッセージ表示
		Sys.reg[176] = 2;
	}
	else if(strcmp(Sys.fname, "2_29.scn") == 0)
	{
		// 深沙緒と会った
		Sys.reg[177] = 1;
	}
	else if(strcmp(Sys.fname, "4_00.scn") == 0)
	{
		// 4章名言
		Sys.reg[177] = 10;
	}
	else if(strcmp(Sys.fname, "7_22.scn") == 0)
	{
		// 鬼退治用のお酒
		Sys.reg[148] = 2048;
	}
	else if(strcmp(Sys.fname, "c_00.scn") == 0)
	{
		// エンディング選択肢
		Sys.reg[179] = 1;
	}
	else if(strcmp(Sys.fname, "c_17.scn") == 0)
	{
		// 美和子ｂａｄ
		Sys.reg[150] = 64;
	}

	// 変数にて86音源を選択
	Sys.reg[1024] = 2;
	Sys.reg[512] = 255;

	u16 n1, n2, n3;
	u16 r1, r2;

	s32 i;
	u16 op;
	u16 adr = 0x100;

	for(;;)
	{
		if(SYS_DEBUG_FLAG == 1 && SYS_DEBUG_START_ADR == adr)
		{
			Sys.isDebug = true;
		}

		op = SysGetNum(adr);
		SysDebug("[%04X] %04X | ", adr, op);
		adr += 2;

		switch(op)
		{
		// exit to DOS
		case 0x00:
			SysDebug("DOSEXIT\n");
			return;

		// undefined
		case 0x01:
			SysDebug("CMD01\n");
			break;

		// load image
		case 0x02:
			SysDebug("IMGLOAD %s\n", SysGetFile(adr+8));
			DstWrite("IMG %s\n", SysGetFile(adr+8));
			adr += 0xC;
			break;

		// open text box
		case 0x03:
			SysDebug("TBOPEN\n");
			adr += 0xC;
			break;

		// close text box
		case 0x04:
			SysDebug("TBCLOSE\n");
			adr += 0x2;
			break;

		// clear text box
		case 0x05:
			SysDebug("TBCLEAR\n");
			adr += 0x2;
			break;

		// apply palette
		case 0x06:
			SysDebug("PALAPL\n");
			break;

		// palette fade: black/white
		case 0x07:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);

			SysDebug("PALBW %d %d\n", n1, n2);
			DstWrite("PBW %d %d\n", n1, n2);

			adr += 0x4;
			break;

		// palette fade: out/in
		case 0x08:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);

			SysDebug("PALFADE %d %d\n", n1, n2);
			DstWrite("PFA %d %d\n", n1, n2);

			adr += 0x4;
			break;

		// toggle Palette Colour Lock Mask
		case 0x09:
			SysDebug("PALLCKT\n");
			adr += 0x2;
			break;

		// jump to offset
		case 0x0A:
			n1 = SysGetNum(adr);
			SysDebug("JP %04X\n", n1);
			adr = n1;
			break;

		// compare registers
		case 0x0B:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			r1 = Sys.reg[n1];
			r2 = Sys.reg[n2];

			if(r1 == r2) Sys.regComp = 0;
			if(r1 <  r2) Sys.regComp = 1;
			if(r1 >  r2) Sys.regComp = 2;

			SysDebug("CMPR i%d(%d) i%d(%d) | %d\n", n1, r1, n2, r2, Sys.regComp);

			adr += 0x4;
			break;

		// compare register and value
		case 0x0C:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			r1 = Sys.reg[n1];

			if(r1 == n2) Sys.regComp = 0;
			if(r1 <  n2) Sys.regComp = 1;
			if(r1 >  n2) Sys.regComp = 2;

			SysDebug("CMPI i%d(%d) %d | %d\n", n1, r1, n2, Sys.regComp);

			adr += 0x4;
			break;

		// conditional jump: equal == 0
		case 0x0D:
			n1 = SysGetNum(adr);
			SysDebug("JEQ %04X \n", n1);

			if(Sys.regComp == 0) adr  =  n1;
			else                 adr += 0x2;

			break;

		// conditional jump: less than == 1
		case 0x0E:
			n1 = SysGetNum(adr);
			SysDebug("JLT %04X \n", n1);

			if(Sys.regComp == 1) adr  =  n1;
			else                 adr += 0x2;

			break;

		case 0x0F:
		// conditional jump: greater than == 2
			n1 = SysGetNum(adr);
			SysDebug("JGT %04X \n", n1);

			if(Sys.regComp == 2) adr  =  n1;
			else                 adr += 0x2;

			break;

		case 0x10:
		// conditional jump: greater or equal != 1
			n1 = SysGetNum(adr);
			SysDebug("JGE %04X \n", n1);

			if(Sys.regComp != 1) adr  =  n1;
			else                 adr += 0x2;

			break;

		case 0x11:
		// conditional jump: less or equal != 2
			n1 = SysGetNum(adr);
			SysDebug("JLE %04X \n", n1);

			if(Sys.regComp != 2) adr  =  n1;
			else                 adr += 0x2;

			break;

		case 0x12:
		// conditional jump: not equal != 0
			n1 = SysGetNum(adr);
			SysDebug("JNE %04X\n", n1);

			if(Sys.regComp != 0) adr  =  n1;
			else                 adr += 0x2;

			break;

		// execute jump table
		case 0x13:
			n1 = SysGetNum(adr);
			r1 = Sys.reg[n1];
			SysDebug("JTBL i%d | %d\n", n1, r1);

			adr = SysGetNum(adr + 2 + r1 * 2);
			break;

		// set palette colour
		case 0x14:
			SysDebug("PCOLSET\n");
			adr += 0x8;
			break;

		// show text
		case 0x15:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);

			// 例外処理
			if(strcmp(Sys.fname, "3_01.scn") == 0 && n2 == 0x1F75)
			{
				// 摩耶 屋根裏部屋
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "3_03.scn") == 0 && n2 == 0x0420)
			{
				// 摩耶H 屋根裏部屋
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "3_07.scn") == 0 && (n2 == 0x07DA || n2 == 0x0808 || n2 == 0x09D3 || n2 == 0x0C10 || n2 == 0x1359))
			{
				// 摩耶H 玄関ホール
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "3_10.scn") == 0 && (n2 == 0x0420 || n2 == 0x043E))
			{
				// 女主人と摩耶
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "4_30.scn") == 0 && (n2 == 0x0B92 || n2 == 0x0BB0 || n2 == 0x0BDD))
			{
				// 人魚H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "4_32.scn") == 0 && (n2 == 0x0984 || n2 == 0x1AD9 || n2 == 0x1AE3 || n2 == 0x1AF8))
			{
				// 摩耶H 部屋
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "5_63.scn") == 0 && (n2 == 0x0619 || n2 == 0x0AD8))
			{
				// 美和子H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "5_64.scn") == 0 && n2 == 0x049A)
			{
				// 美和子H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "6_33.scn") == 0 && n2 == 0x165A)
			{
				// 深紗緒 髪型
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "6_34.scn") == 0 && (n2 == 0x0D0E || n2 == 0x18C5 || n2 == 0x1D97 || n2 == 0x1D9C))
			{
				// 深紗緒H バスルーム
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "6_35.scn") == 0 && n2 == 0x0288)
			{
				// 深紗緒H バスルーム
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "7_39.scn") == 0 && n2 == 0x0ADF)
			{
				// 刀入手 バスルーム
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "7_41.scn") == 0 && (n2 == 0x071D || n2 == 0x0A20))
			{
				// 由羅H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "7_42.scn") == 0 && (n2 == 0x09AA || n2 == 0x1AF7))
			{
				// 由羅H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "8_34.scn") == 0 && (n2 == 0x0E0E || n2 == 0x1203 || n2 == 0x1C6A))
			{
				// 沙里と雪菜
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "8_35.scn") == 0 && (n2 == 0x0BF0 || n2 == 0x0C14 || n2 == 0x2B78))
			{
				// 沙里H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "9_33.scn") == 0 && (n2 == 0x0F81 || n2 == 0x1735 || n2 == 0x1EC6))
			{
				// 雪菜H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "9_42.scn") == 0 && n2 == 0x230F)
			{
				// 赤ずきんと狼
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "a_06.scn") == 0 && (n2 == 0x0947 || n2 == 0x095B || n2 == 0x0F10 || n2 == 0x0F19 || n2 == 0x16BB || n2 == 0x1A95))
			{
				// 雪菜H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "b_08.scn") == 0 && (n2 == 0x0CEF || n2 == 0x19A6 || n2 == 0x19C4 || n2 == 0x1F7A || n2 == 0x1F81))
			{
				// 亜璃沙H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "b_16.scn") == 0 && n2 == 0x151E)
			{
				// 亜璃沙と美和子H
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "b_17.scn") == 0 && (n2 == 0x0B14 || n2 == 0x0B32 || n2 == 0x1869 || n2 == 0x232C))
			{
				// 亜璃沙H
				OpeAddSel(adr+2);
			}
			else if(n1 == 12 || n1 == 13)
			{
				OpeAddSel(adr+2);
			}
			else
			{
				SysPrint(adr+2);
			}

			adr += 0x4;
			break;

		// ??
		case 0x16:
			SysDebug("CMD16\n");
			adr += 0x6;
			break;

		// undefined
		case 0x17:
			SysDebug("CMD17\n");
			break;

		// set register = value
		case 0x18:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			SysDebug("MOVI i%d %d\n", n1, n2);

			Sys.reg[n1] = n2;
			adr += 0x4;
			break;

		// set register = other register
		case 0x19:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			r2 = Sys.reg[n2];
			SysDebug("MOVR i%d i%d(%d)\n", n1, n2, r2);

			Sys.reg[n1] = r2;
			adr += 0x4;
			break;

		// play music
		case 0x1A:
			SysDebug("BGMPLAY %s\n", SysGetFile(adr));
			DstWrite("BPL %d\n", Sys.reg[544]);
			adr += 0x2;
			break;

		// fade music out
		case 0x1B:
			SysDebug("BGMFADE\n");
			// ストップに変更
			DstWrite("BST\n");
			break;

		// stop music
		case 0x1C:
			SysDebug("BGMSTOP\n");
			DstWrite("BST\n");
			break;

		// get music mode
		case 0x1D:
			n1 = SysGetNum(adr);
			SysDebug("BGMODEG i%d\n", n1);

			// 86音源を使用
			Sys.reg[n1] = 2;
			adr += 0x2;
			break;

		// ??
		case 0x1E:
			SysDebug("CMD1E\n");
			adr += 0x2;
			break;

		// load new scene file
		case 0x1F:
			SysDebug("LDSCENE %s\n", SysGetFile(adr));
			DstWrite("LDS %s\n", SysGetFile(adr));
			return;

		// fill GVRAM
		case 0x20:
			SysDebug("GV02\n");
			break;

		// delay script execution by N frames
		case 0x21:
			n1 = SysGetNum(adr);
			r1 = Sys.reg[n1];
			SysDebug("WAIT i%d(%d)\n", n1, r1);
			DstWrite("WAT %d\n", r1);

			adr += 0x2;
			break;

		// ??
		case 0x22:
			SysDebug("CHRDLY\n");
			adr += 0x2;
			break;

		// undefined
		case 0x23:
			SysDebug("CMD23\n");
			break;

		// add value to register
		case 0x24:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			SysDebug("ADDI i%d %d\n", n1, n2);

			Sys.reg[n1] += n2;
			adr += 0x4;
			break;

		// subtract value from register
		case 0x25:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			SysDebug("SUBI i%d %d\n", n1, n2);

			Sys.reg[n1] -= n2;
			adr += 0x4;
			break;

		// text buffer clear 1
		case 0x26:
			SysDebug("TXCLR1\n");
			adr += 0xC;
			break;

		// add source to destination with differing register types
		case 0x27:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			SysDebug("ADDR i%d i%d\n", n1, n2);

			Sys.reg[n1] += Sys.reg[n2];
			adr += 0x4;
			break;

		// subtract source from destination with differing register types
		case 0x28:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			SysDebug("SUBR i%d i%d\n", n1, n2);

			Sys.reg[n1] -= Sys.reg[n2];
			adr += 0x4;
			break;

		// read value from XY buffer to register
		case 0x29:
			SysDebug("XYREAD\n");
			adr += 0x6;
			break;

		// write value from register into XY buffer
		case 0x2A:
			SysDebug("XYWRT\n");
			adr += 0x6;
			break;

		// undefined
		case 0x2B:
			SysDebug("CMD2B\n");
			break;

		// undefined
		case 0x2C:
			SysDebug("CMD2C\n");
			break;

		// clear registers
		case 0x2D:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			SysDebug("REGCLR\n");

			for(i=n1; i<=n2; i++)
			{
				Sys.reg[i] = 0;
			}
			adr += 0x4;
			break;

		// undefined
		case 0x2E:
			SysDebug("CMD2E\n");
			break;

		// ?? (GFX related)
		case 0x2F:
			SysDebug("CMD2F\n");
			adr += 0x10;
			break;

		// undefined
		case 0x30:
			SysDebug("CMD30\n");
			break;

		// undefined
		case 0x31:
			SysDebug("CMD31\n");
			break;

		// print register as text
		case 0x32:
			SysDebug("PRINTR\n");
			adr += 0x4;
			break;

		// set Port A4 state
		case 0x33:
			SysDebug("PA4GET\n");
			adr += 0x2;
			break;

		// get Port A4 state
		case 0x34:
			SysDebug("PA4SET\n");
			adr += 0x2;
			break;

		// text buffer fill
		case 0x35:
			SysDebug("TXFILL\n");
			adr += 0xC;
			break;

		// ?? (some GFX clear)
		case 0x36:
			SysDebug("GFX36\n");
			break;

		// load XY buffer from file
		case 0x37:
			SysDebug("XYFLOAD\n");
			adr += 0x2;
			break;

		// "AND" source with destination register
		case 0x38:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);

			SysDebug("ANDR\n");
			Sys.reg[n1] &= Sys.reg[n2];
			adr += 0x4;
			break;

		// "OR" source with destination register
		case 0x39:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);

			SysDebug("ORR\n");
			Sys.reg[n1] |= Sys.reg[n2];
			adr += 0x4;
			break;

		// ?? (GFX related)
		case 0x3A:
			SysDebug("GFX3A\n");
			adr += 0x10;
			break;

		// ?? (GFX related)
		case 0x3B:
			SysDebug("GFX3B\n");
			adr += 0x10;
			break;

		// text buffer clear 2
		case 0x3C:
			SysDebug("TXCLR2\n");
			adr += 0xA;
			break;

		// multiply source with destination register
		case 0x3D:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);

			SysDebug("MULR\n");
			Sys.reg[n1] *= Sys.reg[n2];
			adr += 0x4;
			break;

		// divide destination by source register
		case 0x3E:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);

			SysDebug("DIVR\n");
			Sys.reg[n1] /= Sys.reg[n2];
			adr += 0x4;
			break;

		// ?? (screen resolution related?)
		case 0x3F:
			SysDebug("CMD3F\n");
			adr += 0x4;
			break;

		// run menu selection
		case 0x40:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			SysDebug("MENUSEL i%d i%d\n", n1, n2);

			// 選択肢インデックスを取得
			n3 = OpeGetSel();
			Sys.reg[n1] = n3;
			Sys.reg[n2] = 0;

			// 選択肢のテキストを書き込む
			n3--;

			assert(n3 <= Ope.strCnt);
			assert(Ope.strBuf[n3][0] != '\0');

			SysDebug("SEL %s\n", Ope.strBuf[n3]);
			DstWrite("SEL %s\n", Ope.strBuf[n3]);

			// 選択肢リセット
			OpeClrSel();

			adr = SysGetNum(adr+6);
			break;

		// ??
		case 0x41:
			SysDebug("CMD41\n");
			adr += 0x8;
			break;

		// ??
		case 0x42:
			SysDebug("CMD42\n");
			adr += 0x2;
			break;

		// ?? (screen resolution related?)
		case 0x43:
			SysDebug("CMD43\n");
			adr += 0x4;
			break;

		// ??
		case 0x44:
			SysDebug("CMD44\n");
			break;
		case 0x45:
			SysDebug("CMD45\n");
			break;
		case 0x46:
			SysDebug("CMD46\n");
			break;
		case 0x47:
			SysDebug("CMD47\n");
			break;
		case 0x48:
			SysDebug("CMD48\n");
			break;
		case 0x49:
			SysDebug("CMD49\n");
			break;

		// save register buffer to file
		case 0x4A:
			SysDebug("REGFSAV\n");
			adr += 0x4;
			break;

		// load register buffer from file
		case 0x4B:
			SysDebug("REGFLD\n");
			adr += 0x4;
			break;

		// ?? (screen resolution related?)
		case 0x4C:
			SysDebug("CMD4C\n");
			adr += 0x4;
			break;

		// get current music measure
		case 0x4D:
			SysDebug("BGMMEAS\n");
			adr += 0x2;
			break;

		// play SSG sound effect
		case 0x4E:
			SysDebug("SFXSSG %d\n", SysGetNum(adr));
			DstWrite("SSG %d\n", SysGetNum(adr));
			adr += 0x2;
			break;

		// play FM sound effect
		case 0x4F:
			n1 = SysGetNum(adr);

			SysDebug("SFXFM %d\n", n1);
			DstWrite("FMX %d\n", n1);

			// patch. FMX 4はウェイトを入れる（名言用）
			if(n1 == 4)
			{
				DstWrite("WAT %d\n", Sys.reg[17]*4);
			}

			adr += 0x2;
			break;

		// get BGM status
		case 0x50:
			SysDebug("BGMSTAT\n");
			adr += 0x2;
			break;

		// "AND" value with destination register
		case 0x51:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			SysDebug("ANDI i%d %d\n", n1, n2);

			Sys.reg[n1] &= n2;
			adr += 0x4;
			break;

		// "OR" value with destination register
		case 0x52:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			SysDebug("ORI i%d %d\n", n1, n2);

			Sys.reg[n1] |= n2;
			adr += 0x4;
			break;

		// concatenate source to the destination string
		case 0x53:
			SysDebug("STRCAT\n");
			adr += 0x4;
			break;

		// subroutine call
		case 0x54:
			n1 = SysGetNum(adr);

			if(n1 == 0x4150)
			{
				SysDebug("MAP\n");
				DstWrite("MAP\n");

				if(strcmp(Sys.fname, "9_41.scn") == 0)
				{
					// 自分の部屋へ
					Sys.reg[292] = 23;
				}
				else if(strcmp(Sys.fname, "a_05.scn") == 0)
				{
					// 時計台へ
					Sys.reg[292] = 13;
				}
				else
				{
					// 今いる場所以外に移動。いいかげんな処理
					// 9_40.scnではオオカミに追い回される
					Sys.reg[292]++;
				}

				adr += 0x2;
			}
			else if(n1 == 0x413C)
			{
				// 振動エフェクト
				SysDebug("VIB\n");
				DstWrite("VIB\n");

				adr += 0x2;
			}
			else if(n1 == 0x4110)
			{
				// キャラ消去
				SysDebug("DLC\n");
				DstWrite("DLC\n");

				adr += 0x2;
			}
			else
			{
				SysDebug("CALL %04X\n", n1);
				SysPushStack(adr+2);

				adr = n1;
			}
			break;

		// subroutine return
		case 0x55:
			SysDebug("RET\n");
			adr = SysPopStack();
			break;

		// compare strings
		case 0x56:
			SysDebug("STRCMPR\n");
			adr += 0x4;
			break;

		// copy N bytes from source to destination string
		case 0x57:
			SysDebug("STRNCPY\n");
			adr += 0x6;
			break;

		// append character N from source to the destination string
		case 0x58:
			SysDebug("STRCPYC\n");
			adr += 0x6;
			break;

		// set string to value
		case 0x59:
			SysDebug("STRCPYI\n");
			n1 = SysGetNum(adr+0);

			assert(n1 >= 0x29 && n1 <= 0x31);
			SysSetStr(n1 - 0x29, adr+2);

			adr += 0x4;
			break;

		// clear string
		case 0x5A:
			SysDebug("STRCLR\n");
			n1 = SysGetNum(adr+0);

			assert(n1 >= 0x29 && n1 <= 0x31);
			strcpy(Sys.str[n1 - 0x29], "");

			adr += 0x2;
			break;

		// copy string
		case 0x5B:
			SysDebug("STRCPY\n");
			adr += 0x4;
			break;

		// undefined
		case 0x5C:
			SysDebug("CMD5C\n");
			break;
		case 0x5D:
			SysDebug("CMD5D\n");
			break;

		// ??
		case 0x5E:
			SysDebug("CMD5E\n");
			n1 = SysGetNum(adr+0);

			if(n1 == 0) DstWrite("DRW 0\n");		// 画面黒塗りつぶし？
			if(n1 == 1) DstWrite("DRW 1\n");		// 画面黒塗りつぶし？

			adr += 0xA;
			break;

		// set string to current date/time
		case 0x5F:
			SysDebug("STRTIME\n");
			adr += 0x2;
			break;

		// get file date/time
		case 0x60:
			SysDebug("FILETM\n");
			adr += 0x6;
			break;

		// save XY buffer to file
		case 0x61:
			SysDebug("XYFSAVE\n");
			adr += 0x2;
			break;

		// ?? (writes to I/O port 0A2h and 0A0h)
		case 0x62:
			SysDebug("CMD62\n");
			adr += 0x4;
			break;

		// ?? (GFX related)
		case 0x63:
			SysDebug("CMD63\n");
			adr += 0x10;
			break;

		// ?? (GFX related)
		case 0x64:
			SysDebug("GFX64\n");
			adr += 0x10;
			break;

		// undefined
		case 0x65:
			SysDebug("CMD65\n");
			break;

		case 0x66:
			SysDebug("CMD66\n");
			break;

		// ?? (GFX related)
		case 0x67:
			SysDebug("GFX67\n");
			adr += 0x8;
			break;

		// ?? (GFX related)
		case 0x68:
			SysDebug("GFX68\n");
			adr += 0x4;
			break;

		// ?? (GFX related)
		case 0x69:
			SysDebug("GFX69\n");
			adr += 0x6;
			break;

		// ??
		case 0x6A:
			SysDebug("CMD6A\n");
			adr += 0x8;
			break;

		// ??
		case 0x6B:
			SysDebug("CMD6B\n");
			adr += 0x8;
			break;

		// undefined
		case 0x6C:
			SysDebug("CMD6C\n");
			break;
		case 0x6D:
			SysDebug("CMD6D\n");
			break;

		// get string length
		case 0x6E:
			SysDebug("STRLEN\n");
			adr += 0x4;
			break;

		// undefined
		case 0x6F:
			SysDebug("CMD6F\n");
			break;
		case 0x70:
			SysDebug("CMD70\n");
			break;
		case 0x71:
			SysDebug("CMD71\n");
			break;

		// set script loop counter
		case 0x72:
			SysDebug("LOOPSTI\n");
			Sys.regLoop = SysGetNum(adr);

			adr += 0x2;
			break;

		// get script loop counter
		case 0x73:
			SysDebug("LOOPGTR\n");
			n1 = SysGetNum(adr);

			// pc98 Int0A ディスプレイ関連？
			// vsync単位？のループカウントを１アップ（無限ループする為）
			Sys.reg[n1] = Sys.regLoop++;

			adr += 0x2;
			break;

		// conditional jump based on script loop counter
		case 0x74:
			SysDebug("LOOPJPI\n");
			adr += 0x4;
			break;

		// load custom font character
		case 0x75:
			SysDebug("FONTCHR\n");
			adr += 0x4;
			break;

		// ??
		case 0x76:
			SysDebug("CMD76\n");
			adr += 0x10;
			break;

		// ??
		case 0x77:
			SysDebug("CMD77\n");
			adr += 0x10;
			break;

		// ??
		case 0x78:
			SysDebug("CMD78\n");
			adr += 0x4;
			break;

		// ?? (copies some script data around)
		case 0x79:
			SysDebug("CMD79\n");
			adr += 0x2;
			break;

		// set script loop counter from register
		case 0x7A:
			SysDebug("LOOPSTR\n");
			adr += 0x2;
			break;

		// conditional jump based on script loop counter
		case 0x7B:
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+2);
			r1 = Sys.reg[n1];
			SysDebug("LOOPJPR i%d(%d) %04X\n", n1, r1, n2);

			// pc98 Int0A ディスプレイ関連？
			// ループウェイト無効処理
			Sys.regLoop = r1;

			adr += 0x4;
			break;

		// undefined
		case 0x7C:
			SysDebug("CMD7C\n");
			break;
		case 0x7D:
			SysDebug("CMD7D\n");
			break;
		case 0x7E:
			SysDebug("CMD7E\n");
			break;

		// exit to DOS, return code based on register content
		case 0x7F:
			SysDebug("DOSRETR\n");
			adr += 0x2;
			break;

		// load strings from file
		case 0x80:
			SysDebug("STRFLD\n");
			adr += 0x4;
			break;

		// write strings to file
		case 0x81:
			SysDebug("STRFSAV\n");
			adr += 0x4;
			break;

		// ?? (writes to GVRAM Plane 0/1/2/3)
		case 0x82:
			SysDebug("GFX82\n");
			break;

		// ?? (GFX related)
		case 0x83:
			SysDebug("GFX83\n");
			adr += 0x2;
			break;

		// ?? (some GFX transition effect)
		case 0x84:
			SysDebug("GFX84\n");
			break;

		case 0x85:
			SysDebug("GFX85\n");
			break;

		// ??
		case 0x86:
			SysDebug("GFX86\n");
			adr += 0x2;
			break;

		// ??
		case 0x87:
			SysDebug("GFX87\n");
			adr += 0x14;
			break;

		// ?? (GFX related)
		case 0x88:
			SysDebug("GFX88\n");
			adr += 0x6;
			break;

		// ?? (GFX related)
		case 0x89:
			SysDebug("GFX89\n");
			adr += 0x2;
			break;

		// ?? (GFX related)
		case 0x8A:
			SysDebug("GFX8A\n");
			adr += 0x8;
			break;

		// ?? (GFX related)
		case 0x8B:
			SysDebug("GFX8B\n");
			adr += 0x6;
			break;

		// ?? (GFX related)
		case 0x8C:
			SysDebug("CMD8C\n");
			break;
		case 0x8D:
			SysDebug("CMD8D\n");
			break;
		case 0x8E:
			SysDebug("CMD8E\n");
			break;

		case 0x95:
			SysDebug("CMD95\n");
			adr += 0x10;
			break;

		default:
			SysDebug("UNKNOWN\n");
			break;
		}
	}
}
//---------------------------------------------------------------------------
void SysPrint(u16 adr)
{
	SysDebug("PRINT ");
	DstWrite("MSG ");


	u16 num = SysGetNum(adr);
	u8* pS = &Src.buf[num];
	u8* pD = Sys.printBuf;
	u8* pB = Sys.printBuf;

	bool isCmd = false;

	for(;;)
	{
		assert((pD - pB) < 10000);

		if(*pS == 0x00)
		{
			*pD++ = '\0';

			SysDebug("%s\n", pB);
			DstWrite("%s\n", pB);

			return;
		}

		// wait for key press
		if(*pS == 0x01)
		{
			pS++;

			*pD++ = '\n';
			*pD++ = 'K';
			*pD++ = 'E';
			*pD++ = 'Y';

			isCmd = true;
			continue;
		}

		// text not clear. next line
		if(*pS == 0x02)
		{
			pS++;

			// テキストクリアに変更
//			*pD++ = '\n';
//			*pD++ = 'K';
//			*pD++ = 'E';
//			*pD++ = 'Y';
//			isCmd = true;

			continue;
		}

		// set text colour to xx
		if(*pS == 0x03)
		{
			pS += 2;
			continue;
		}

		// インスタント文字
		if(*pS == 0x04)
		{
			if(isCmd == true)
			{
				*pD++ = '\n';
				*pD++ = 'M';
				*pD++ = 'S';
				*pD++ = 'G';
				*pD++ = ' ';

				isCmd = false;
			}

			if(*(pS+1) == 0x0A)
			{
				*pD++ = 0x90;	// 慎
				*pD++ = 0x54;
				*pD++ = 0x88;	// 一
				*pD++ = 0xEA;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x0B)
			{
				*pD++ = 0x8F;	// 女
				*pD++ = 0x97;
				*pD++ = 0x8E;	// 主
				*pD++ = 0xE5;
				*pD++ = 0x90;	// 人
				*pD++ = 0x6C;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x0C)
			{
				*pD++ = 0x94;	// 美
				*pD++ = 0xFC;
				*pD++ = 0x98;	// 和
				*pD++ = 0x61;
				*pD++ = 0x8E;	// 子
				*pD++ = 0x71;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x0D)
			{
				*pD++ = 0x91;	// 草
				*pD++ = 0x90;
				*pD++ = 0x8E;	// 山
				*pD++ = 0x52;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x0E)
			{
				*pD++ = 0x96;	// 摩
				*pD++ = 0x80;
				*pD++ = 0x96;	// 耶
				*pD++ = 0xEB;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x0F)
			{
				*pD++ = 0x90;	// 雪
				*pD++ = 0xE1;
				*pD++ = 0x8D;	// 菜
				*pD++ = 0xD8;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x10)
			{
				*pD++ = 0x8D;	// 沙
				*pD++ = 0xB9;
				*pD++ = 0x97;	// 里
				*pD++ = 0xA2;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x11)
			{
				*pD++ = 0x90;	// 深
				*pD++ = 0x5B;
				*pD++ = 0x8E;	// 紗
				*pD++ = 0xD1;
				*pD++ = 0x8F;	// 緒
				*pD++ = 0x8F;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x12)
			{
				*pD++ = 0x90;	// 人
				*pD++ = 0x6C;
				*pD++ = 0x8B;	// 魚
				*pD++ = 0x9B;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x13)
			{
				*pD++ = 0x97;	// 由
				*pD++ = 0x52;
				*pD++ = 0x97;	// 羅
				*pD++ = 0x85;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x14)
			{
				*pD++ = 0x88;	// 亜
				*pD++ = 0x9F;
				*pD++ = 0x97;	// 璃
				*pD++ = 0x9E;
				*pD++ = 0x8D;	// 沙
				*pD++ = 0xB9;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x15)
			{
				*pD++ = 0x90;	// 赤
				*pD++ = 0xD4;
				*pD++ = 0x93;	// 頭
				*pD++ = 0xAA;
				*pD++ = 0x8B;	// 巾
				*pD++ = 0xD0;
				*pD++ = 0x81;	// ：
				*pD++ = 0x46;
			}
			else if(*(pS+1) == 0x1E)
			{
				*pD++ = 0x90;	// 慎
				*pD++ = 0x54;
				*pD++ = 0x88;	// 一
				*pD++ = 0xEA;
			}
			else if(*(pS+1) >= 0x29 && *(pS+1) <= 0x31)
			{
				s32 n = *(pS+1) - 0x29;
				s32 i, len;
				len = strlen(Sys.str[n]);

				for(i=0; i<len; i++)
				{
					*pD++ = Sys.str[n][i];
				}
			}
			else
			{
				fprintf(stderr, "Error: SysPrint 0x04 adr=%x\n", num + pD - pB);
				exit(1);
			}

			pS += 2;
			continue;
		}

		// next line
		if(*pS == 0x0D)
		{
			pS++;
			continue;
		}

		// special code
		if(*pS == 0x0F)
		{
			pS++;

			// sets some flag
			if(*pS == 0x00)
			{
				// ignore
				pS += 2;
			}
			else
			{
				pS++;
			}
			continue;
		}

		// space
		if(*pS == 0x20)
		{
			pS++;
			continue;
		}

		// SJIS
		if((*pS>=0x81 && *pS<=0x9f) || (*pS>=0xe0 && *pS<=0xef))
		{
			if(isCmd == true)
			{
				*pD++ = '\n';
				*pD++ = 'M';
				*pD++ = 'S';
				*pD++ = 'G';
				*pD++ = ' ';

				isCmd = false;
			}

			// 全角空白
			if(*pS == 0x81 && *(pS+1) == 0x40)
			{
				pS += 2;

				continue;
			}

			// SJIS外の文字（9_08にて混入）
			if((*pS == 0x85 && *(pS+1) == 0xF7) || (*pS == 0x85 && *(pS+1) == 0xC0))
			{
				// "・"に置換
				*pD++ = 0x81;
				*pD++ = 0x45;
				pS += 2;

				continue;
			}

			// 特殊フォント
			if(*pS == 0xeb || *pS == 0x86)
			{
				*pD++ = '\\';
				*pD++ = SysGetHex2Chr((*pS)  >> 4);
				*pD++ = SysGetHex2Chr((*pS) & 0xf);
				pS++;

				*pD++ = '\\';
				*pD++ = SysGetHex2Chr((*pS)  >> 4);
				*pD++ = SysGetHex2Chr((*pS) & 0xf);
				pS++;

				continue;
			}

			*pD++ = *pS++;
			*pD++ = *pS++;

			continue;
		}

		// 半角(!)
		if(*pS == 0x21)
		{
			if(isCmd == true)
			{
				*pD++ = '\n';
				isCmd = false;
			}

			*pD++ = 0x81;		// ！
			*pD++ = 0x49;

			pS++;
			continue;
		}

		// 半角(?)
		if(*pS == 0x3F)
		{
			if(isCmd == true)
			{
				*pD++ = '\n';
				isCmd = false;
			}

			*pD++ = 0x81;		// ？
			*pD++ = 0x48;

			pS++;
			continue;
		}

		// 半角(p)
		if(*pS == 0x70)
		{
			// "pname" ゲームではただの空白。ミスと思われる
			pS += 5;
			continue;
		}

		// 半角(ｯ)
		if(*pS == 0xAF)
		{
			if(isCmd == true)
			{
				*pD++ = '\n';
				isCmd = false;
			}

			*pD++ = 0x83;		// ッ
			*pD++ = 0x62;

			pS++;
			continue;
		}

		// 半角(ｸ)
		if(*pS == 0xB8)
		{
			if(isCmd == true)
			{
				*pD++ = '\n';
				isCmd = false;
			}

			*pD++ = 0x83;		// ク
			*pD++ = 0x4E;

			pS++;
			continue;
		}

		// 半角(ｸ)
		if(*pS == 0xD7)
		{
			if(isCmd == true)
			{
				*pD++ = '\n';
				isCmd = false;
			}

			*pD++ = 0x83;		// ラ
			*pD++ = 0x89;

			pS++;
			continue;
		}

		*pD++ = '\0';
		fprintf(stderr, "Error: SysPrint adr=%x\n%s\n", num + pD - pB, pB);
		exit(1);
	}
}
//---------------------------------------------------------------------------
u16 SysGetNum(u16 adr)
{
	return (Src.buf[adr]) | (Src.buf[adr+1] << 8);
}
//---------------------------------------------------------------------------
char* SysGetFile(u16 adr)
{
	u16 num = SysGetNum(adr) + 1;

	char* p = (char*)&Src.buf[num];

	while(*p != '\0')
	{
		// ファイル名は全て小文字化します
		if(*p >= 'A' && *p <= 'Z')
		{
			*p += ' ';
		}

		p++;
	}

	return (char*)&Src.buf[num];
}
//---------------------------------------------------------------------------
void SysSetStr(s32 no, u16 adr)
{
	u16 num = SysGetNum(adr);
	u8* pS = &Src.buf[num];
	u8* pD = Sys.str[no];

	while(*pS != '\0')
	{
		// space
		if(*pS == 0x20)
		{
			pS++;

			continue;
		}

		// SJIS
		if((*pS>=0x81 && *pS<=0x9f) || (*pS>=0xe0 && *pS<=0xef))
		{
			// 全角
			if(*pS == 0x81 && *(pS+1) == 0x40)
			{
				pS += 2;

				continue;
			}

			*pD++ = *pS++;
			*pD++ = *pS++;

			continue;
		}
	}

	*pD++ = '\0';
}
//---------------------------------------------------------------------------
void SysPushStack(u16 adr)
{
	assert(Sys.stackCnt < SYS_MAX_STACK_CNT);

	Sys.stackBuf[Sys.stackCnt++] = adr;
}
//---------------------------------------------------------------------------
u16 SysPopStack(void)
{
	assert(Sys.stackCnt != 0);

	return Sys.stackBuf[--Sys.stackCnt];
}
//---------------------------------------------------------------------------
void SysDebug(char* format, ...)
{
	if(Sys.isDebug == false)
	{
		return;
	}

	va_list ap;

	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}
//---------------------------------------------------------------------------
char SysGetHex2Chr(u8 hex)
{
	if(hex <= 9)
	{
		return '0' + hex;
	}

	return 'a' + hex - 10;
}
//---------------------------------------------------------------------------
void OpeInit(char* fname, char* buf)
{
	memset(&Ope, 0x00, sizeof(ST_OPE));

	// manual mode
	if(buf[0] != '\0')
	{
		strncpy(Ope.cmdBuf, buf, OPE_MAX_SEL_CNT);
		return;
	}

	// read OpeTable
	s32 i;

	for(i=0; i<sizeof(OpeTable) / sizeof(ST_OPE_TABLE); i++)
	{
		if(strncmp(fname, OpeTable[i].fname, OPE_MAX_FNAME_CNT) == 0)
		{
			break;
		}
	}
	assert(i < sizeof(OpeTable) / sizeof(ST_OPE_TABLE));


	strncpy(Ope.cmdBuf, OpeTable[i].sel, OPE_MAX_SEL_CNT);
}
//---------------------------------------------------------------------------
u16 OpeGetSel(void)
{
	char c = Ope.cmdBuf[Ope.cmdOrder];
	assert(c != '\0');

	u16 ret;

	if(c >= '0' && c <= '9')
	{
		ret = (u16)(c - '0');
	}
	else
	{
		// 10桁以上 A-Z
		ret = (u16)(c - '7');
	}

//	printf("order:%02d | %d %d %d\n", Ope.cmdOrder, Sys.reg[112], Sys.reg[113], Sys.reg[127]);
	Ope.cmdOrder++;

	return ret;
}
//---------------------------------------------------------------------------
void OpeAddSel(u16 adr)
{
	u16 num = SysGetNum(adr);
	u8* pS = &Src.buf[num];
	u8* pD = Ope.workBuf;
	u8* pB = Ope.workBuf;

//	SysDebug("STR_CHECK\n");
//	DstWrite("STR_CHECK\n");

	for(;;)
	{
		assert((pD - pB) < 10000);

		// end point
		if(*pS == 0x00)
		{
			if(pD - pB != 0)
			{
				*pD = '\0';
				 pD = pB;

				strcpy(Ope.strBuf[Ope.strCnt], pB);
				Ope.strCnt++;
			}

			return;
		}

		// インスタント文字
		if(*pS == 0x04)
		{
			if(*(pS+1) >= 0x29 && *(pS+1) <= 0x31)
			{
				s32 n = *(pS+1) - 0x29;
				s32 i, len;
				len = strlen(Sys.str[n]);

				for(i=0; i<len; i++)
				{
					*pD++ = Sys.str[n][i];
				}
			}
			else
			{
				fprintf(stderr, "Error: OpeAddSel 0x04 adr=%x\n", num + pD - pB);
				exit(1);
			}

			pS += 2;
			continue;
		}


		// next line
		if(*pS == 0x0D)
		{
			pS++;

			// patch. cs13_23
			if((pD - pB) == 0)
			{
				continue;
			}

			*pD = '\0';
			 pD = pB;

			strcpy(Ope.strBuf[Ope.strCnt], pB);
			Ope.strCnt++;

			continue;
		}

		// special code
		if(*pS == 0x0F)
		{
			pS++;

			// sets some flag
			if(*pS == 0x00)
			{
				// ignore
				pS += 2;
			}
			else
			{
				pS++;
			}

			continue;
		}

		// space
		if(*pS == 0x20)
		{
			pS++;

			continue;
		}

		// SJIS
		if((*pS>=0x81 && *pS<=0x9f) || (*pS>=0xe0 && *pS<=0xef))
		{
			// 全角
			if(*pS == 0x81 && *(pS+1) == 0x40)
			{
				pS += 2;

				continue;
			}

			// 特殊フォント
			if(*pS == 0xeb || *pS == 0x86)
			{
				*pD++ = '\\';
				*pD++ = SysGetHex2Chr((*pS)  >> 4);
				*pD++ = SysGetHex2Chr((*pS) & 0xf);
				pS++;

				*pD++ = '\\';
				*pD++ = SysGetHex2Chr((*pS)  >> 4);
				*pD++ = SysGetHex2Chr((*pS) & 0xf);
				pS++;

				continue;
			}

			*pD++ = *pS++;
			*pD++ = *pS++;

			continue;
		}

		*pD++ = '\0';
		fprintf(stderr, "Error: OpeAddStr adr=%x(%x)\n%s\n", num + pD - pB, *pS, pB);
		exit(1);
	}
}
//---------------------------------------------------------------------------
void OpeClrSel(void)
{
	Ope.strCnt = 0;

	memset(&Ope.strBuf, 0x00, sizeof(Ope.strBuf));
}
