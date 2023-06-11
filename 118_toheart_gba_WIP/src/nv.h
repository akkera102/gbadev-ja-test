#ifndef __NV_H__
#define __NV_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define NV_MAX_FLAG_CNT					256
#define NV_MAX_PARSE_CNT				70
#define NV_MAX_FLAG_END_CNT				17
#define NV_MAX_SELECT_CNT				10
#define NV_MAX_SCN_CNT					197

#define NV_FLAG_EVENT_DONE				0xa6
#define NV_FLAG_IDOU					0xaf
#define NV_FLAG_DAY						0xab
#define NV_FLAG_WEEK					0xad
#define NV_FLAG_TIME					0xae
#define NV_FLAG_VSELECT_MSG				0xb1
#define NV_FLAG_VSELECT_OFF				0xbd
#define NV_FLAG_AKARI					0x01
#define NV_FLAG_A_SCN1					0xf0
#define NV_FLAG_A_SCN2					0xf1
#define NV_FLAG_A_BLK					0xf2
#define NV_FLAG_B_SCN1					0xf4
#define NV_FLAG_B_SCN2					0xf5
#define NV_FLAG_B_BLK					0xf6


enum {
	NV_ACT_PARSE,
	NV_ACT_KEY,
	NV_ACT_RESTART,
	NV_ACT_END,
};

//---------------------------------------------------------------------------

typedef struct {
	// 状態
	s32  act;
	s32  step;
	s32  wait;
	bool isLoop;
	bool isSkip;

	// スクリプトカーソル
	char* pCur;
	char* pRet;
	u32   curAdr;
	u8    scnNo;
	u8    evtNo;
	u8    msgNo;

	// スクリプトファイル
	u8*   pScn;
	u8    evtMax;
	u8    msgMax;

	// ゲーム関連
	s8    flag[NV_MAX_FLAG_CNT];

} ST_NV;


//---------------------------------------------------------------------------
EWRAM_CODE void NvInit(void);
EWRAM_CODE void NvExec(void);
EWRAM_CODE void NvExecKey(void);
EWRAM_CODE void NvExecRestart(void);


EWRAM_CODE void NvSetScn(u16 no);
EWRAM_CODE void NvSetEvt(u16 no);
EWRAM_CODE void NvSetMsg(u16 no);
EWRAM_CODE void NvSetEffectBefore(u8 no);
EWRAM_CODE void NvSetEffectAfter(u8 no);
EWRAM_CODE void NvSetNext(void);
EWRAM_CODE void NvSetAct(s32 act);

EWRAM_CODE void NvSetFlag(u8 no, s8 val);
EWRAM_CODE void NvAddFlag(u8 no, s8 val);
EWRAM_CODE s8   NvGetFlag(u8 no);

EWRAM_CODE void NvAddCur(u8 offset);
EWRAM_CODE void NvNextLine(void);
EWRAM_CODE void NvPrevLine(void);

EWRAM_CODE u16  NvGetChrNo(u16 no);

EWRAM_CODE bool NvIsSkip(void);
EWRAM_CODE bool NvIsRestart(void);

#ifdef __cplusplus
}
#endif
#endif

