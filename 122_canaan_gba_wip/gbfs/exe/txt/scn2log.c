// スクリプトデコーダー PC-98 カナン 約束の地
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
#define SYS_MAX_WINDOW_SIZE				110

#define OPE_MAX_STR_CNT					20
#define OPE_MAX_STR_SIZE				50
#define OPE_MAX_WORK_CNT				10000
#define OPE_MAX_FNAME_CNT				20
#define OPE_MAX_SEL_CNT					200

//---------------------------------------------------------------------------
typedef unsigned char   u8;
typedef char            s8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;
typedef int            s32;

// 入力シナリオ
typedef struct {
	u8*   p;
	s32   size;
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
	{ "cs01_01.scn", "11" },
	{ "cs01_02.scn", "11111" },
	{ "cs01_03.scn", "12122" },
	{ "cs01_04.scn", "1111" },
	{ "cs01_05.scn", "111" },
	{ "cs01_06.scn", "1111" },
	{ "cs01_07.scn", "122221" },
	{ "cs01_08.scn", "11112" },
	{ "cs01_09.scn", "111111121313212122222211123" },
	{ "cs01_10.scn", "1222" },
	{ "cs01_11.scn", "111213222231323232323333333334343434343434" },
	{ "cs01_12.scn", "1112222" },
	{ "cs01_13.scn", "12122223" },
	{ "cs01_14.scn", "1222" },
	{ "cs01_15.scn", "1222" },
	{ "cs01_16.scn", "122222" },
	{ "cs01_17.scn", "22132" },
	{ "cs01_18.scn", "1213222222" },
	{ "cs01_19.scn", "1112222" },
	{ "cs01_20.scn", "11122222" },
	{ "cs01_21.scn", "12122221213132222" },
	{ "cs02_01.scn", "111111111" },
	{ "cs02_02.scn", "1" },
	{ "cs02_03.scn", "1" },
	{ "cs02_04.scn", "1" },
	{ "cs02_05.scn", "1222222" },
	{ "cs02_06.scn", "12222" },
	{ "cs02_07.scn", "1222223131313232323232333333343435353535353535" },
	{ "cs02_08.scn", "122222222" },
	{ "cs02_09.scn", "1112" },
	{ "cs02_10.scn", "111112" },					// ラビィH
	{ "cs02_11.scn", "11" },
	{ "cs02_12.scn", "1111121212212122221313" },
	{ "cs02_13.scn", "1223" },
	{ "cs02_14.scn", "1212132222" },
	{ "cs02_15.scn", "111122222331" },
	{ "cs02_16.scn", "22222" },
	{ "cs02_17.scn", "112222" },
	{ "cs02_18.scn", "123333" },
	{ "cs02_19.scn", "1233333" },
	{ "cs02_20.scn", "1233333" },
	{ "cs02_21.scn", "1233333" },
	{ "cs02_22.scn", "12" },
	{ "cs02_23.scn", "1212121212121212122222222" },
	{ "cs02_24.scn", "12121212222222222" },
	{ "cs03_01.scn", "12222" },
	{ "cs03_02.scn", "122222" },
	{ "cs03_03.scn", "1" },
	{ "cs03_04.scn", "111113131212212121212131322232222222333333" },
	{ "cs03_05.scn", "11121322222222" },
	{ "cs03_06.scn", "112222" },
	{ "cs03_07.scn", "1222" },
	{ "cs03_08.scn", "2" },
	{ "cs03_09.scn", "1122" },
	{ "cs03_10.scn", "121212222232331313232" },
	{ "cs03_11.scn", "11222333" },
	{ "cs03_13.scn", "1222222" },
	{ "cs03_14.scn", "112222222222" },
	{ "cs03_15.scn", "" },
	{ "cs03_16.scn", "" },
	{ "cs04_01.scn", "111" },
	{ "cs04_02.scn", "122" },
	{ "cs04_03.scn", "11" },
	{ "cs04_04.scn", "222" },
	{ "cs04_05.scn", "222222" },
	{ "cs04_06.scn", "12222231313131323232" },
	{ "cs04_07.scn", "12" },
	{ "cs04_08.scn", "111112122222" },
	{ "cs04_09.scn", "122222" },
	{ "cs04_10.scn", "1222" },
	{ "cs04_11.scn", "122222" },
	{ "cs04_12.scn", "122223" },
	{ "cs04_13.scn", "1222" },
	{ "cs04_14.scn", "12233334" },
	{ "cs04_15.scn", "1223334" },
	{ "cs04_16.scn", "1233334" },
	{ "cs04_17.scn", "1222" },
	{ "cs04_18.scn", "1222333333333" },
	{ "cs04_19.scn", "1222223" },
	{ "cs04_20.scn", "1222223" },
	{ "cs04_21.scn", "123334" },
	{ "cs04_22.scn", "12223334" },
	{ "cs04_23.scn", "123334" },
	{ "cs04_24.scn", "111222222" },
	{ "cs04_25.scn", "1222222" },
	{ "cs04_26.scn", "112222" },
	{ "cs04_27.scn", "122" },
	{ "cs04_28.scn", "122" },
	{ "cs05_01.scn", "1222222" },
	{ "cs05_02.scn", "11121322223312" },
	{ "cs05_03.scn", "112223344" },
	{ "cs05_04.scn", "1" },
	{ "cs05_05.scn", "1111" },
	{ "cs05_06.scn", "12223" },
	{ "cs05_07.scn", "1132" },
	{ "cs05_08.scn", "1" },
	{ "cs05_09.scn", "111222222333" },
	{ "cs05_10.scn", "1122" },
	{ "cs05_11.scn", "112222" },
	{ "cs05_12.scn", "121223334" },
	{ "cs05_13.scn", "1222" },						// 鍵入手ポイント
	{ "cs05_14.scn", "1222" },						// 何かいた？
	{ "cs05_15.scn", "1231" },						// Ｂ１Ｆ各部屋の移動分岐
	{ "cs05_16.scn", "12223333334" },				// Ａ－０１号室
	{ "cs05_17.scn", "1233334" },					// Ａ－０２号室
	{ "cs05_18.scn", "123334" },					// Ａ－０３号室
	{ "cs05_19.scn", "12334" },						// Ａ－０４号室（鍵未入手）
	{ "cs05_20.scn", "1122332222222222334" },		// Ａ－０４号室（鍵で開けた）
	{ "cs05_21.scn", "122223322222222222222224" },	// Ａ－０５号室
	{ "cs05_22.scn", "122232" },					// 階段
	{ "cs05_23.scn", "1231" },						// Ｂ２Ｆ各部屋の移動分岐
	{ "cs05_24.scn", "123334" },					// Ｂ－０１号室
	{ "cs05_25.scn", "1234" },						// Ｂ－０２号室
	{ "cs05_26.scn", "13212121212222224" },			// Ｂ－０３号室
	{ "cs05_27.scn", "133322222222222224" },		// Ｂ－０４号室
	{ "cs05_28.scn", "1222222234" },				// Ｂ－０５号室
	{ "cs05_29.scn", "111111121222" },
	{ "cs05_30.scn", "122231313131323232323333333435363636" },
	{ "cs05_31.scn", "1222" },
	{ "cs05_32.scn", "1122" },
	{ "cs05_33.scn", "1122233" },
	{ "cs05_34.scn", "1122" },
	{ "cs05_38.scn", "" },
	{ "cs05_39.scn", "11" },						// 不要ファイル（Ｂ１Ｆ各部屋の移動分岐。05_13より）
	{ "cs05_40.scn", "" },							// ！！！中身はcs05_13.scn！！！鍵入手イベントi96=2042
	{ "cs06_01.scn", "12222222" },
	{ "cs06_02.scn", "1222222" },
	{ "cs06_03.scn", "122333" },
	{ "cs06_04.scn", "122222222" },
	{ "cs06_05.scn", "1112222222231323333" },
	{ "cs06_06.scn", "22221111" },
	{ "cs06_07.scn", "" },
	{ "cs06_08.scn", "1111" },
	{ "cs06_09.scn", "122222" },
	{ "cs07_01.scn", "122223" },
	{ "cs07_02.scn", "122223" },
	{ "cs07_03.scn", "122222223" },
	{ "cs07_04.scn", "122223" },
	{ "cs07_05.scn", "122223" },
	{ "cs07_06.scn", "12222" },
	{ "cs07_07.scn", "123332222233" },
	{ "cs07_08.scn", "11233333" },
	{ "cs07_09.scn", "12121212122222233" },
	{ "cs07_10.scn", "12223333333333" },
	{ "cs07_11.scn", "12223333" },
	{ "cs07_12.scn", "11222222" },
	{ "cs07_13.scn", "121222222222323233" },
	{ "cs07_14.scn", "13212121" },
	{ "cs08_01.scn", "1222222" },
	{ "cs08_02.scn", "12223131313232333333" },
	{ "cs08_03.scn", "12222" },
	{ "cs08_04.scn", "122222" },
	{ "cs08_05.scn", "1111" },
	{ "cs08_06.scn", "" },
	{ "cs08_07.scn", "122222222" },
	{ "cs08_08.scn", "2" },
	{ "cs08_09.scn", "1211223" },
	{ "cs08_10.scn", "1112223" },
	{ "cs08_11.scn", "3" },
	{ "cs08_12.scn", "112" },
	{ "cs08_13.scn", "122222222" },
	{ "cs08_14.scn", "122" },
	{ "cs08_15.scn", "1222222" },
	{ "cs08_16.scn", "122222" },
	{ "cs08_17.scn", "1222" },
	{ "cs08_18.scn", "22231313131313232323233333333343434343434343434" },
	{ "cs08_19.scn", "22222" },
	{ "cs08_20.scn", "1112222222" },
	{ "cs08_21.scn", "111212222333333" },
	{ "cs08_22.scn", "11222222" },
	{ "cs08_23.scn", "122222" },
	{ "cs08_24.scn", "12222" },
	{ "cs08_25.scn", "2223333333" },
	{ "cs08_26.scn", "122233333333" },
	{ "cs08_27.scn", "" },
	{ "cs08_28.scn", "12223" },
	{ "cs08_29.scn", "2" },							// レジーナH 35へ
	{ "cs08_30.scn", "11112222" },
	{ "cs08_31.scn", "" },
	{ "cs08_32.scn", "1222222222" },
	{ "cs08_33.scn", "12222222" },
	{ "cs08_34.scn", "12222" },
	{ "cs08_35.scn", "11111222" },					// 30へ
	{ "cs09_01.scn", "12233333" },
	{ "cs09_02.scn", "12222222222" },
	{ "cs09_03.scn", "1222222" },
	{ "cs09_04.scn", "122222222" },
	{ "cs09_05.scn", "12333333" },
	{ "cs09_06.scn", "11121" },
	{ "cs09_07.scn", "1212121212121222222223333" },
	{ "cs09_08.scn", "123333" },
	{ "cs09_09.scn", "11122222231313131313131323232323232333333343434343434343435353536363636373737373838383839393939393A3A3A" },
	{ "cs09_10.scn", "" },
	{ "cs09_12.scn", "11111" },
	{ "cs09_13.scn", "11111" },
	{ "cs09_14.scn", "221111" },
	{ "cs09_15.scn", "1112222222" },
	{ "cs09_16.scn", "1111" },
	{ "cs09_17.scn", "" },
	{ "cs09_18.scn", "111222223131313132333333" },
	{ "cs09_19.scn", "11111213222" },
	{ "cs09_20.scn", "1111112222" },
	{ "cs09_21.scn", "11222222112" },
	{ "cs09_22.scn", "111" },
	{ "cs09_23.scn", "" },
	{ "cs09_24.scn", "122222" },
	{ "cs09_25.scn", "12222" },
	{ "cs09_26.scn", "2222222" },
	{ "cs09_27.scn", "111" },
	{ "cs10_01.scn", "122222222" },
	{ "cs10_02.scn", "12222333333" },
	{ "cs10_03.scn", "122222" },
	{ "cs10_04.scn", "112222222" },
	{ "cs10_05.scn", "1222" },
	{ "cs10_06.scn", "1212233332333" },
	{ "cs10_07.scn", "1222222" },
	{ "cs10_08.scn", "1111222" },
	{ "cs10_09.scn", "1" },
	{ "cs10_10.scn", "12222" },
	{ "cs10_11.scn", "1222" },
	{ "cs10_12.scn", "122222" },
	{ "cs10_13.scn", "122222" },
	{ "cs10_14.scn", "111122222" },
	{ "cs10_15.scn", "122222" },
	{ "cs11_01.scn", "1122222" },
	{ "cs11_02.scn", "1222" },
	{ "cs11_03.scn", "122222" },
	{ "cs11_04.scn", "122233333" },
	{ "cs11_05.scn", "12222" },
	{ "cs12_01.scn", "12222" },
	{ "cs12_02.scn", "1222333333" },
	{ "cs12_03.scn", "122" },
	{ "cs12_04.scn", "11222" },
	{ "cs12_05.scn", "11111212122222231313132323232323333343435353535363636" },
	{ "cs13_01.scn", "1112132222222222" },
	{ "cs13_02.scn", "132223333333" },
	{ "cs13_03.scn", "132222222313131313131313232323233333333343434343434" },
	{ "cs13_04.scn", "122222" },
	{ "cs13_05.scn", "122222222133333333333333" },
	{ "cs13_06.scn", "2" },							// エルザH
	{ "cs13_07.scn", "11" },
	{ "cs13_08.scn", "" },
	{ "cs13_09.scn", "1111222333444" },
	{ "cs13_10.scn", "" },
	{ "cs13_11.scn", "12222" },
	{ "cs13_12.scn", "1222222222" },
	{ "cs13_13.scn", "1111" },
	{ "cs13_14.scn", "11111" },
	{ "cs13_15.scn", "122222" },
	{ "cs13_16.scn", "122222" },
	{ "cs13_17.scn", "1" },							// ティティH
	{ "cs13_18.scn", "1" },
	{ "cs13_20.scn", "1122222222222" },
	{ "cs13_21.scn", "" },
	{ "cs13_22.scn", "122222223" },
	{ "cs13_23.scn", "122222223" },
	{ "cs13_24.scn", "1222223" },
	{ "cs13_25.scn", "12222222" },
	{ "cs13_26.scn", "2" },							// ルウリィH
	{ "cs13_27.scn", "2" },
	{ "cs13_28.scn", "1" },
	{ "cs13_29.scn", "2" },
	{ "cs13_30.scn", "" },
	{ "cs13_31.scn", "1222223" },
	{ "cs13_32.scn", "122222" },
	{ "cs13_33.scn", "1222222222222" },
	{ "cs13_34.scn", "12222222" },
	{ "cs13_35.scn", "12222" },
	{ "cs13_36.scn", "122223131313131313132323333343434343434" },
	{ "cs13_37.scn", "1" },							// ディライアH
	{ "cs13_38.scn", "111" },
	{ "cs13_39.scn", "" },
	{ "cs13_40.scn", "12222222222" },
	{ "cs13_41.scn", "" },
	{ "cs14_01.scn", "112121212121212222222222" },
	{ "cs14_02.scn", "122222222" },
	{ "cs14_03.scn", "111" },
	{ "cs14_04.scn", "1222" },
	{ "cs14_05.scn", "12222222233" },
	{ "cs14_06.scn", "1222222222222" },
	{ "cs14_07.scn", "1112" },
	{ "cs14_08.scn", "11121322 " },
	{ "cs14_09.scn", "1111" },
	{ "cs14_10.scn", "" },
	{ "cs14_11.scn", "12" },
	{ "cs15_01.scn", "1112122223" },
	{ "cs15_02.scn", "12" },
	{ "cs15_03.scn", "12222222222" },
	{ "cs15_04.scn", "1221" },
	{ "cs15_05.scn", "111112222222233" },
	{ "cs15_06.scn", "1" },
	{ "cs15_07.scn", "122222" },
	{ "cs15_08.scn", "1111" },
	{ "cs15_09.scn", "12334" },
	{ "cs16_01.scn", "11121313222222222 " },
	{ "cs16_02.scn", "1223333" },
	{ "cs16_03.scn", "1112222222222" },
	{ "cs16_04.scn", "11122222" },
	{ "cs16_05.scn", "122222" },
	{ "cs16_06.scn", "111" },
	{ "cs16_07.scn", "112" },
	{ "cs16_08.scn", "12222" },
	{ "cs16_09.scn", "12" },
	{ "cs16_10.scn", "1122222" },
	{ "cs16_11.scn", "121212121222222" },
	{ "cs16_12.scn", "122222222" },
	{ "cs16_13.scn", "122222222" },
	{ "cs16_14.scn", "1" },							// リリーH
	{ "cs16_15.scn", "1112" },
	{ "cs16_16.scn", "1" },							// 分岐あり
	{ "cs16_17.scn", "" },
	{ "cs16_18.scn", "12222" },
	{ "cs16_19.scn", "122222" },
	{ "cs16_20.scn", "1222222" },
	{ "cs17_01.scn", "1222222" },
	{ "cs17_02.scn", "11222222222" },
	{ "cs17_03.scn", "1" },							// イリアH
	{ "cs17_04.scn", "12223333" },
	{ "cs17_05.scn", "122223" },
	{ "cs17_06.scn", "122222" },
	{ "cs17_07.scn", "21212121212122222222232323242424242424252525252526262627271" },
	{ "cs17_08.scn", "122" },
	{ "cs17_09.scn", "11111111111111111212121212131313131313141414141515151515161616" },
	{ "cs17_10.scn", "122222" },
	{ "cs17_11.scn", "1122222" },
	{ "cs17_12.scn", "2" },							// ダイアナH
	{ "cs17_13.scn", "1" },							// 分岐あり。2を選択した場合、14をスキップ15へ
	{ "cs17_14.scn", "1" },							// 分岐あり
	{ "cs17_15.scn", "11122233334" },
	{ "cs17_16.scn", "1112" },						// ローズマリーH
	{ "cs17_17.scn", "112" },
	{ "cs17_18.scn", "1112" },
	{ "cs17_19.scn", "1" },
	{ "cs17_20.scn", "11" },
	{ "cs17_21.scn", "12223" },
	{ "cs17_22.scn", "1" },							// ミーナH
	{ "cs17_23.scn", "1112223" },
	{ "cs17_24.scn", "1111111111" },
	{ "cs17_25.scn", "11114" },
	{ "cs17_26.scn", "11114" },
	{ "cs17_27.scn", "11112223" },
	{ "cs17_28.scn", "122222222" },
	{ "cs17_29.scn", "1222223" },
	{ "cs17_30.scn", "122222222313131313132323232333333" },
	{ "cs17_31.scn", "122223" },
	{ "cs17_32.scn", "12223" },
	{ "cs17_33.scn", "122222" },
	{ "cs17_34.scn", "122" },
	{ "cs17_35.scn", "12222" },
	{ "cs17_36.scn", "111112122233333332" },
	{ "cs17_37.scn", "122222" },
	{ "cs17_38.scn", "111213212121212121212123232222" },
	{ "cs17_39.scn", "21" },
	{ "cs17_40.scn", "11111112222212" },
	{ "cs17_41.scn", "11122222" },
	{ "cs17_42.scn", "1222222231313131313132323232323232323231333333333333333333" },
	{ "cs17_43.scn", "12222223" },
	{ "cs17_44.scn", "12223" },
	{ "cs17_45.scn", "1222" },
	{ "cs17_46.scn", "1122221" },
	{ "cs17_47.scn", "11111" },
	{ "cs17_48.scn", "222222222222222222" },
	{ "cs17_49.scn", "1122223" },
	{ "cs17_50.scn", "11121213132222333" },
	{ "cs18_01.scn", "1222222" },
	{ "cs18_02.scn", "12222" },
	{ "cs18_03.scn", "" },
	{ "cs18_04.scn", "" },
	{ "cs18_05.scn", "1112222313131332323232323233343434" },
	{ "cs18_06.scn", "122222222" },
	{ "cs18_07.scn", "122222" },
	{ "cs18_08.scn", "11131414141515151617171818121223" },
	{ "cs18_09.scn", "11111112222222" },
	{ "cs19_01.scn", "122222233333333" },
	{ "cs19_02.scn", "11222" },
	{ "cs19_03.scn", "122222222" },
	{ "cs19_04.scn", "123333334" },
	{ "cs19_05.scn", "1122223" },
	{ "cs19_06.scn", "122223" },
	{ "cs19_07.scn", "1222223" },
	{ "cs19_08.scn", "122223" },
	{ "cs19_09.scn", "1112222223" },
	{ "cs20_01.scn", "1222223" },
	{ "cs20_02.scn", "122222223" },
	{ "cs20_03.scn", "" },
	{ "cs20_04.scn", "122223" },
	{ "cs20_05.scn", "12333334" },
	{ "cs20_06.scn", "1111121212" },
	{ "cs20_07.scn", "" },
	{ "cs21_01.scn", "122233333" },
	{ "cs21_02.scn", "1222223" },
	{ "cs21_03.scn", "12222223" },
	{ "cs21_04.scn", "111122222333333" },
	{ "cs21_05.scn", "1222222223" },
	{ "cs21_06.scn", "122222222223" },
	{ "cs21_07.scn", "122222222223" },
	{ "cs21_08.scn", "1222222313131323232333333333333343434343535353536363636363636363737373737373838383838" },
	{ "cs21_09.scn", "1222222223" },
	{ "cs21_10.scn", "111" },
	{ "cs21_11.scn", "1223131313131313131323232323232323233333333343434353535353535353636363637373737393939393A3A3A3A3A3B3B38383838" },
	{ "cs21_12.scn", "122222" },
	{ "cs21_13.scn", "122222223" },
	{ "cs21_14.scn", "1223131313333343434353535353232323232323232" },
	{ "cs21_15.scn", "" },
	{ "cs22_01.scn", "1222222" },
	{ "cs22_02.scn", "" },
	{ "cs22_03.scn", "12222" },
	{ "cs22_04.scn", "1122222222222222222" },
	{ "cs22_05.scn", "112222222222" },
	{ "cs22_06.scn", "1111" },
	{ "cs22_07.scn", "1222222222" },
	{ "cs22_08.scn", "122" },
	{ "cs22_09.scn", "12222231313131323232323333333333343434343435" },
	{ "cs22_10.scn", "12214" },						//  1.レオナゼリー
	{ "cs22_11.scn", "" },							//  2.レオナH判定 14へジャンプ
	{ "cs22_12.scn", "1112223334" },				//  6.レオナH
	{ "cs22_13.scn", "1112223" },					//  7.レオナH 20へ
	{ "cs22_14.scn", "12214" },						//  3.ドーラゼリー
	{ "cs22_15.scn", "" },							//  4.ドーラH判定 19へジャンプ
	{ "cs22_16.scn", "111223" },					//  9.ドーラH
	{ "cs22_17.scn", "1112223" },					// 10.ドーラH
	{ "cs22_18.scn", "" },							// 11.ドーラH 21へ
	{ "cs22_19.scn", "1" },							//  5.！！！中身はcs22_11.scn！！！ 12へ
	{ "cs22_20.scn", "1" },							//  8.！！！中身はcs22_15.scn！！！ 16へ
	{ "cs22_21.scn", "" },							// 12.！！！中身はcs22_10.scn！！！ 姉妹合流後
	{ "cs23_01.scn", "122222" },
	{ "cs23_02.scn", "" },
	{ "cs23_03.scn", "" },
	{ "cs23_04.scn", "11" },
	{ "cs23_05.scn", "111" },
	{ "cs23_06.scn", "" },
	{ "cs23_07.scn", "11111212" },
	{ "cs23_08.scn", "122222" },
	{ "cs23_09.scn", "1222222" },
	{ "cs23_10.scn", "12222231313131313131313131313232323232333333343434343435353535353636373737" },
	{ "cs23_11.scn", "12222222" },
	{ "cs23_12.scn", "1111" },
	{ "cs23_13.scn", "1222" },
	{ "cs23_14.scn", "122222" },
	{ "cs24_01.scn", "12222222222" },
	{ "cs24_02.scn", "1222222222" },
	{ "cs24_03.scn", "1222222" },
	{ "cs24_04.scn", "1112132222" },
	{ "cs24_05.scn", "1222" },
	{ "cs24_06.scn", "1222" },
	{ "cs24_07.scn", "1222" },
	{ "cs24_08.scn", "" },
	{ "cs25_01.scn", "122222" },
	{ "cs25_02.scn", "122222" },
	{ "cs25_03.scn", "122222222222" },
	{ "cs25_04.scn", "" },
	{ "cs25_05.scn", "12" },
	{ "cs25_06.scn", "1111111" },
	{ "cs25_07.scn", "1222222222222" },
	{ "cs25_08.scn", "122223131313132323232" },
	{ "cs25_09.scn", "" },
	{ "cs26_01.scn", "1222" },
	{ "cs26_02.scn", "1111121213222" },
	{ "cs26_03.scn", "11122121323333" },
	{ "cs26_04.scn", "12222" },
	{ "cs27_01.scn", "111212132222" },
	{ "cs27_02.scn", "12222" },
	{ "cs28_01.scn", "1222222" },
	{ "cs28_02.scn", "" },							// ラビィH
	{ "cs28_03.scn", "12222222" },
	{ "cs28_04.scn", "1" },							// アンジェラH
	{ "cs28_05.scn", "" },
	{ "cs28_06.scn", "" },
};

//---------------------------------------------------------------------------
ST_SRC Src;
ST_DST Dst;
ST_SYS Sys;
ST_OPE Ope;


//---------------------------------------------------------------------------
void  SrcInit(char* fname);
void  SrcFree(void);

void  DstInit(char* fname);
void  DstWrite(char* format, ...);
void  DstFree(void);

void  SysInit(char* fname);
void  SysExec(void);
u16   SysGetNum(u16 adr);
char* SysGetFile(u16 adr);
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

	SrcFree();
	DstFree();

	return 0;
}
//---------------------------------------------------------------------------
void SrcInit(char* fname)
{
	// get file size
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "Error: open src\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Src.size = ftell(fp);

	// read file
	Src.p = calloc(Src.size, sizeof(u8));

	if(Src.p == NULL)
	{
		fprintf(stderr, "Error: calloc src\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Src.p, 1, Src.size, fp);
	fclose(fp);
}
//---------------------------------------------------------------------------
void SrcFree(void)
{
	free(Src.p);
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
}
//---------------------------------------------------------------------------
void SysExec(void)
{
	//
	// 例外処理
	//

	if(strcmp(Sys.fname, "cs05_40.scn") == 0)
	{
		// 鍵入手フラグ
		Sys.reg[96]  = 2042;
		Sys.reg[176] = 1;
	}

	if(strcmp(Sys.fname, "cs22_19.scn") == 0)
	{
		// 姉妹救出後フラグ
		Sys.reg[177] = 28;
	}

	if(strcmp(Sys.fname, "cs22_20.scn") == 0)
	{
		// 姉妹救出後フラグ
		Sys.reg[177] = 12;
	}

	if(strcmp(Sys.fname, "cs22_21.scn") == 0)
	{
		// 姉妹合流後フラグ
		Sys.reg[177] = 32;
	}


	u16 n1, n2, n3;
	u16 r1, r2;
	u16 w8, w9;

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
			n1 = SysGetNum(adr+0);
			n2 = SysGetNum(adr+6);
			n3 = SysGetNum(adr+8);

			if(n1 == 8)
			{
				w8 = n2 * n3;
			}
			else if(n1 == 9)
			{
				w9 = n2 * n3;
			}
			else
			{
				assert(0 && "TBOPEN");
			}

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
			SysDebug("PALBW %d %d\n", SysGetNum(adr), SysGetNum(adr+2));
			adr += 0x4;
			break;

		// palette fade: out/in
		case 0x08:
			SysDebug("PALFADE %d %d\n", SysGetNum(adr), SysGetNum(adr+2));
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
			if(strcmp(Sys.fname, "cs03_08.scn") == 0 && adr == 0x1032)
			{
				// 例外処理 ニースH 選択肢ウィンドウ
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "cs08_08.scn") == 0 && adr == 0x29d)
			{
				// 例外処理 ローズマリーH 選択肢ウィンドウ
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "cs21_11.scn") == 0 && adr == 0x6f3)
			{
				// 例外処理 ビィ 選択肢ウィンドウ
				OpeAddSel(adr+2);
			}
			else if(strcmp(Sys.fname, "cs23_02.scn") == 0 && SysGetNum(adr) == 8)
			{
				// 例外処理 ファー撃たれた後の仲間 テキストウィンドウ
				SysPrint(adr+2);
			}
			else if(SysGetNum(adr) == 8 && w8 < SYS_MAX_WINDOW_SIZE)
			{
				OpeAddSel(adr+2);
			}
			else if(SysGetNum(adr) == 9 && w9 < SYS_MAX_WINDOW_SIZE)
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
			DstWrite("BPL %d\n", Sys.reg[575]);
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
			DstWrite("LDS %d %d\n", Sys.reg[185], Sys.reg[186]);
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

			adr += 0x2;
			break;

		// ??
		case 0x22:
			SysDebug("GFX22\n");
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

		// print register as text (canaan no use)
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

		// "AND" source with destination register (canaan no use)
		case 0x38:
			SysDebug("ANDR\n");
			adr += 0x4;
			break;

		// "OR" source with destination register (canaan no use)
		case 0x39:
			SysDebug("ORR\n");
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

		// get current music measure (canaan no use)
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
			SysDebug("SFXFM %d\n", SysGetNum(adr));
			DstWrite("FMX %d\n", SysGetNum(adr));
			adr += 0x2;
			break;

		// get BGM status (canaan no use)
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
			SysDebug("CALL %04X\n", n1);

			SysPushStack(adr+2);
			adr = n1;
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
			adr += 0x4;
			break;

		// clear string
		case 0x5A:
			SysDebug("STRCLR\n");
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

		// conditional jump based on script loop counter (canaan no use)
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

		// set script loop counter from register (canaan no use)
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
	u8* pS = &Src.p[num];
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
			*pD++ = '\n';
			*pD++ = 'K';
			*pD++ = 'E';
			*pD++ = 'Y';

			isCmd = true;
			continue;
		}

		// set text colour to xx
		if(*pS == 0x03)
		{
			pS += 2;
			continue;
		}

		// 主人公の名前
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

			if(*(pS+1) == 0x00 || *(pS+1) == 0x14)
			{
				*pD++ = 0x83;	// カ
				*pD++ = 0x4A;
				*pD++ = 0x83;	// イ
				*pD++ = 0x43;
				*pD++ = 0x83;	// ト
				*pD++ = 0x67;
			}
			else if(*(pS+1) == 0x01)
			{
				*pD++ = 0x83;	// ウ
				*pD++ = 0x45;
				*pD++ = 0x83;	// ル
				*pD++ = 0x8B;
				*pD++ = 0x83;	// フ
				*pD++ = 0x74;
				*pD++ = 0x83;	// ィ
				*pD++ = 0x42;
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

			// フォアナイン特殊フォント
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

		fprintf(stderr, "Error: SysPrint adr=%x\n", num + pD - pB);
		exit(1);
	}
}
//---------------------------------------------------------------------------
u16 SysGetNum(u16 adr)
{
	return (Src.p[adr]) | (Src.p[adr+1] << 8);
}
//---------------------------------------------------------------------------
char* SysGetFile(u16 adr)
{
	u16 num = SysGetNum(adr) + 1;

	char* p = (char*)&Src.p[num];

	while(*p != '\0')
	{
		// ファイル名は全て小文字化します
		if(*p >= 'A' && *p <= 'Z')
		{
			*p += ' ';
		}

		p++;
	}

	return (char*)&Src.p[num];
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
	u8* pS = &Src.p[num];
	u8* pD = Ope.workBuf;
	u8* pB = Ope.workBuf;

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

		// 主人公の名前
		if(*pS == 0x04)
		{
			if(*(pS+1) == 0x14)
			{
				*pD++ = 0x83;	// カ
				*pD++ = 0x4A;
				*pD++ = 0x83;	// イ
				*pD++ = 0x43;
				*pD++ = 0x83;	// ト
				*pD++ = 0x67;
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

		// space
		if(*pS == 0x20)
		{
			pS++;

			continue;
		}

		// SJIS
		if((*pS>=0x81 && *pS<=0x9f) || (*pS>=0xe0 && *pS<=0xef))
		{
			// フォアナイン特殊フォント
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

		fprintf(stderr, "Error: OpeAddStr adr=%x(%x)\n", num + pD - pB, *pS);
		exit(1);
	}
}
//---------------------------------------------------------------------------
void OpeClrSel(void)
{
	Ope.strCnt = 0;

	memset(&Ope.strBuf, 0x00, sizeof(Ope.strBuf));
}
