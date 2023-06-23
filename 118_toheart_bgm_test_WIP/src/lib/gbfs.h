#ifndef __GBFS_H__
#define __GBFS_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// ヘッダ（32バイト）
typedef struct {
	char sig[16];				// シグネチャ "PinEightGBFS" + 0x0d + 0x0a + 0x1a + 0x0a
	u32  size;					// アーカイブの大きさ
	u16  dirOff;				// ファイル一覧のオフセット(ROM終端からの相対)
	u16  fileCnt;				// ファイルの登録数
	u8   noUse[8];				// 空き領域
} __PACKED ST_GBFS_HEADER;


// ファイルリスト（32バイト）
typedef struct {
	char fname[24];				// ファイル名
	u32  size;					// サイズ
	u32  dataOff;				// ファイルのオフセット(ROM終端からの相対)
} __PACKED ST_GBFS_LIST;


typedef struct {
	ST_GBFS_HEADER* pHeader;
	ST_GBFS_LIST*   pList;
	u32             pos;
} ST_GBFS;

//---------------------------------------------------------------------------
EWRAM_CODE void  GbfsInit(void);

IWRAM_CODE void* GbfsGetPointer(char* fname);
IWRAM_CODE void* GbfsGetPointer2(u32 cnt);
IWRAM_CODE void* GbfsGetSafePointer(char* fname);
IWRAM_CODE void* GbfsGetSafePointer2(u32 cnt);

EWRAM_CODE char* GbfsGetFileName(void);
EWRAM_CODE u32   GbfsGetFileSize(void);
EWRAM_CODE u32   GbfsGetArcSize(void);
EWRAM_CODE u32   GbfsGetArcCnt(void);


#ifdef __cplusplus
}
#endif
#endif
