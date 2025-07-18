// メッセージ命令を変更
// gcc scn_msg.c -s -o scn_msg

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <assert.h>

//---------------------------------------------------------------------------
#define SCN_MAX_CX				17
#define SCN_MAX_CY				6

typedef unsigned char   u8;
typedef char            s8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;
typedef int            s32;


typedef struct {
	u8*   pSrc;
	u8*   pAdr;
	u8*   pCmd;
	s32   fsize;
	s32   pos;
	FILE* fp;

	s32   x;
	s32   y;

} ST_SCN;

//---------------------------------------------------------------------------
ST_SCN Scn;


//---------------------------------------------------------------------------
void  ScnInit(char* fname);
void  ScnInitSrc(char* fname);
void  ScnInitDst(char* fname);
void  ScnFree(void);
void  ScnExec(void);

u8    ScnCurChr(void);
char* ScnCurStr(void);
s32   ScnCurNum(void);

void  ScnWriteStr(void);
void  ScnWriteStr2(s32 cnt);
void  ScnWriteMsg(void);
void  ScnWriteMsgSub(void);

bool  ScnIsMsgFull(void);
bool  ScnIsMsgFront(u16 code);
bool  ScnIsMsgBack(u16 code);

//---------------------------------------------------------------------------
void ScnInit(char* fname)
{
	ScnInitSrc(fname);
	ScnInitDst(fname);
}
//---------------------------------------------------------------------------
void ScnInitSrc(char* fname)
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
void ScnInitDst(char* fname)
{
	char dname[30];

	strncpy(dname, fname, 20);
	char* p = strchr(dname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	p[0] = '.';
	p[1] = 's';
	p[2] = '0';
	p[3] = '2';
	p[4] = '\0';

	Scn.fp = fopen(dname, "wb");

	if(Scn.fp == NULL)
	{
		fprintf(stderr, "couldn't open fille\n");

		exit(1);
	}
}
//---------------------------------------------------------------------------
void ScnFree(void)
{
	free(Scn.pSrc);
	Scn.pSrc = NULL;

	fclose(Scn.fp);
}
//---------------------------------------------------------------------------
void ScnExec(void)
{
	// 選択肢スキップ
	s32 sel = ScnCurNum();
	ScnWriteStr();

	if(sel != 0)
	{
		// 選択肢とアドレススキップ
		ScnWriteStr2(sel * 2);
	}

	// 各行はアドレス、命令、可変オプション
	while(Scn.pos < Scn.fsize)
	{
		Scn.pAdr = ScnCurStr();
		ScnWriteStr();

		Scn.pCmd = ScnCurStr();
		ScnWriteStr();

//		printf("%s %s\n", Scn.pAdr, Scn.pCmd);

		switch(Scn.pCmd[0])
		{
		case '!':
			switch(Scn.pCmd[1])
			{
			// 背景
			case 'g':
				ScnWriteStr2(1);
				break;

			// 音楽再生
			case 'b':
				ScnWriteStr2(1);
				break;

			// 効果音再生
			case 'e':
				ScnWriteStr2(1);
				break;

			// 立ち絵
			case 'x':
				ScnWriteStr2(2);
				break;

			// スクリプトジャンプ（条件判定あり）
			case 'j':
				ScnWriteStr2(1);
				break;

			// タイトル
			case 't':
				ScnWriteStr2(1);
				break;

			// テキストコマンドから既読コマンドに意味付けを変更
			case 's':
				ScnWriteStr2(2);
				// '_?'コマンドを付与して既読コマンドと分離
				ScnWriteMsg();
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
				ScnWriteStr2(1);
				break;

			// RET, ELSE, ENDIF
			case 'r':
			case 'l':
			case 'n':
				// EMPTY
				break;

			// 条件式（!jスクリプトジャンプと連動）
			case 'i':
				ScnWriteStr2(3);
				break;

			// エフェクト
			case 'W':
				ScnWriteStr2(1);
				break;

			// ウェイト
			case 't':
				ScnWriteStr2(1);
				break;

			default:
				goto Err;
			}
			break;

		// 選択肢
		case ';':
			assert(Scn.pCmd[1] == ';');
			break;

		// 代入か加算
		case '[':
			assert(Scn.pCmd[1] == ']');
			ScnWriteStr2(3);
			break;

		default:
			goto Err;
		}
	}

	return;

Err:

	fprintf(stderr, "parse error %04X %s %s\n", Scn.pos, Scn.pAdr, Scn.pCmd);
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
void ScnWriteStr(void)
{
	u8 c;

	do {
		c = ScnCurChr();
		fputc(c, Scn.fp);

	} while(c != '\0');
}
//---------------------------------------------------------------------------
void ScnWriteStr2(s32 cnt)
{
	s32 i;

	for(i=0; i<cnt; i++)
	{
		ScnWriteStr();
	}
}
//---------------------------------------------------------------------------
void ScnWriteMsg(void)
{
	while(Scn.pSrc[Scn.pos] != '\0')
	{
		ScnWriteMsgSub();
	}

	// skip '\0'
	Scn.pos++;
}
//---------------------------------------------------------------------------
void ScnWriteMsgSub(void)
{
	u16 buf[256];

	s32 cnt = 0;
	u8 c1, c2;
	u16 code;

//	printf("--%d %d\n", Scn.x, Scn.y);

	for(;;)
	{
		assert(Scn.y < SCN_MAX_CY);
		assert(cnt < 256);

		if(Scn.pSrc[Scn.pos] == '\0')
		{
			if(cnt == 0)
			{
				return;
			}

			// _m 文字列のみ
			c1 = '_';
			c2 = 'm';

			goto Write;
		}

		c1 = ScnCurChr();
		c2 = ScnCurChr();
		code = (c2 << 8) | c1;

//		printf("%d %d %04X %c%c\n", Scn.x, Scn.y, code, c1, c2);

		switch(code)
		{
		// _r 改ページ
		case 0x725F:
			Scn.x = 0;
			Scn.y = 0;
			goto Write;

		// _b 指アイコン＋メッセージ退避せずエフェクト
		case 0x625F:
			// tに変更。tはGBA仕様でメッセージ退避させない
			c2 = 't';
			// no break

		// _t 指アイコン
		case 0x745F:
			assert(cnt != 0);

			goto Write;

		// _n 改行
		case 0x6E5F:
			if(Scn.x == 0 && cnt == 0)
			{
				return;
			}
			Scn.x = 0;
			Scn.y++;
			goto Write;

		// _w 謎
		case 0x775F:
			// 正規表現で消去済
			assert(0 && "_w");
			break;

		// _s 謎
		case 0x735F:
			// 正規表現で消去済
			assert(0 && "_s");
			return;

		// SJIS
		default:
			if(Scn.x == 0 && cnt != 0 && ScnIsMsgFront(code) == true)
			{
				// 行頭
				buf[cnt+0] = buf[cnt-1];
				buf[cnt-1] = 0x4081;
				buf[cnt+1] = code;

				Scn.x = 2;
				cnt += 2;
			}
			else if(Scn.x == (SCN_MAX_CX-1) && ScnIsMsgBack(code) == true)
			{
				// 行末
				buf[cnt+0] = 0x4081;
				buf[cnt+1] = code;

				Scn.y++;
				Scn.x = 1;
				cnt += 2;
			}
			else
			{
				// 通常
				buf[cnt] = code;

				Scn.x++;
				cnt++;

				if(Scn.x >= SCN_MAX_CX)
				{
					Scn.x = 0;
					Scn.y++;
				}
			}
			break;
		}
	}

Write:

	assert(cnt < 256);
	buf[cnt] = '\0';

	// メッセージが画面に入るか先読みします
	bool isFull = ScnIsMsgFull();

//	printf("%c is:%d x:%2d y:%2d %s\n", c2, isFull, Scn.x, Scn.y, buf);

	if(isFull == true)
	{
		c2 = 'r';

		Scn.x = 0;
		Scn.y = 0;
	}

	char tmp[512];
	sprintf(tmp, "%s %c%c %s", Scn.pAdr, c1, c2, buf);

	// +1をして'\0'含めます
	s32 len = strlen(tmp)+1;

	// 区切り位置を決め打ち
	tmp[4] = '\0';
	tmp[7] = '\0';

	fwrite(tmp, len, 1, Scn.fp);
}
//---------------------------------------------------------------------------
bool ScnIsMsgFull(void)
{
	s32 x = Scn.x;
	s32 y = Scn.y;
	u8* p = Scn.pSrc + Scn.pos;

	s32 cnt = 0;
	u16 code;

	for(;;)
	{
		if(x >= SCN_MAX_CX)
		{
			x = 0;
			y++;
		}

		if(y >= SCN_MAX_CY)
		{
			return true;
		}

		if(*p == '\0')
		{
			return false;
		}

		code  = *p++;
		code += *p++ << 8;

		switch(code)
		{
		// _r 改ページ
		case 0x725F:
			return false;

		// _b 指アイコン＋メッセージ退避せずエフェクト
		// _t 指アイコン
		case 0x625F:
		case 0x745F:
			if(cnt != 0)
			{
				return false;
			}
			// 次へ
			break;

		// _n 改行
		case 0x6E5F:
			if(x != 0 && cnt == 0)
			{
				x = 0;
				y++;
			}
			break;

		// _w 謎
		case 0x775F:
			// 正規表現で消去済
			assert(0 && "_w");
			return false;

		// _s 謎
		case 0x735F:
			// 正規表現で消去済
			assert(0 && "_s");
			return false;

		// SJIS
		default:
			if(x == 0 && cnt != 0 && ScnIsMsgFront(code) == true)
			{
				// 行頭
				x = 2;
				cnt += 2;

				continue;
			}
			else if(x == (SCN_MAX_CX-1) && ScnIsMsgBack(code) == true)
			{
				// 行末
				y++;
				x = 1;
				cnt += 2;

				continue;
			}
			else
			{
				// 通常
				x++;
				cnt++;
			}
			break;
		}
	}
}
//---------------------------------------------------------------------------
bool ScnIsMsgFront(u16 code)
{
	switch(code)
	{
	case 0xE182:	// ゃ
	case 0xE382:	// ゅ
	case 0xE582:	// ょ
	case 0xC182:	// っ
	case 0x4281:	// 。
	case 0x4181:	// 、
	case 0x4581:	// ・
	case 0x6381:	// …
	case 0x8481:	// ＞
	case 0x7881:	// 』
	case 0x7681:	// 」
	case 0x6A81:	// ）
	case 0x6E81:	// ］
	case 0x4881:	// ？
	case 0x4981:	// ！
	case 0x7C81:	// －
	case 0x5B81:	// ー
	case 0x8383:	// ャ
	case 0x8583:	// ュ
	case 0x8783:	// ョ
	case 0x6283:	// ッ
	case 0x9683:	// ヶ
	case 0x9F82:	// ぁ
	case 0xA182:	// ぃ
	case 0xA382:	// ぅ
	case 0xA582:	// ぇ
	case 0xA782:	// ぉ
	case 0x4083:	// ァ
	case 0x4283:	// ィ
	case 0x4483:	// ゥ
	case 0x4683:	// ェ
	case 0x4883:	// ォ
	case 0x4481:	// ．
	case 0x6081:	// ～
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------
bool ScnIsMsgBack(u16 code)
{
	switch(code)
	{
	case 0x8381:	// ＜
	case 0x7781:	// 『
	case 0x7581:	// 「
	case 0x6D81:	// ［
	case 0x6981:	// （
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "scn_msg [filename]\n");
		exit(1);
	}

	printf("scn_msg... %s\n", argv[1]);

	ScnInit(argv[1]);
	ScnExec();
	ScnFree();

	return 0;
}
