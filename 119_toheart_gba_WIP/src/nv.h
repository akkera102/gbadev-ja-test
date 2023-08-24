#ifndef __NV_H__
#define __NV_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define NV_MAX_PARSE_CNT				71
#define NV_MAX_FLAG_CNT					0x100
#define NV_MAX_SEL_CNT					12
#define NV_MAX_SCN_CNT					0xa96
#define NV_MAX_STR_CNT					256

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
	NV_ACT_SELECT,
	NV_ACT_END,
};

//---------------------------------------------------------------------------

typedef struct {
	u8   cnt;
	u8   offset;
	u8   msg;
	s8   num;

	s8   item[NV_MAX_SEL_CNT];
	s8   jump[NV_MAX_SEL_CNT];
	u8*  pStr[NV_MAX_SEL_CNT];

	u8*  pSrc;
	u32  srcAdr;

} ST_NV_SEL;


typedef struct {
	// ステータス
	s32  act;
	s32  act2;
	s32  step;
	s32  wait;
	bool isLoop;
	bool isSkip;
	bool isWaitPcm;

	// スクリプト
	u8   scnNo;
	u8   evtNo;
	u8   msgNo;
	u8   maxEvt;
	u8   maxMsg;

	u8*  pCur;
	u32  curAdr;

	u8*  pTxt;
	u8*  pEvt;
	u8*  pMsg;
	u8*  pRet;
	u32  size;

	s8   flag[NV_MAX_FLAG_CNT];

	// メッセージ格納
	char str[NV_MAX_STR_CNT] ALIGN(4);

	// 選択肢
	bool isSel;
	bool isSelOpt;
	bool isSelKey;
	ST_NV_SEL sel;

	// 乱数用
	u32  vblankCnt;

} ST_NV;


//---------------------------------------------------------------------------
EWRAM_CODE void NvInit(void);
EWRAM_CODE void NvExec(void);
EWRAM_CODE void NvExecKey(void);
EWRAM_CODE void NvExecSel(void);
EWRAM_CODE void NvExecRestart(void);

EWRAM_CODE void NvSetEffectBefore(u8 no);
EWRAM_CODE void NvSetEffectAfter(u8 no);
EWRAM_CODE void NvSetEffectTime(u8 num);
EWRAM_CODE void NvSetEffectCal(u8 num);

EWRAM_CODE void NvSetScn(u32 no);
EWRAM_CODE void NvSetEvt(u32 no);
EWRAM_CODE void NvSetMsg(u32 no);
EWRAM_CODE void NvSetNext(void);

EWRAM_CODE void NvSetAct(s32 act);
EWRAM_CODE void NvPushAct(s32 act);
EWRAM_CODE void NvPopAct(void);

EWRAM_CODE void NvSetFlag(u8 no, s8 val);
EWRAM_CODE void NvAddFlag(u8 no, s8 val);
EWRAM_CODE void NvSubFlag(u8 no, s8 val);
EWRAM_CODE s8   NvGetFlag(u8 no);

EWRAM_CODE u16  NvGetChrNo(u16 no);
EWRAM_CODE u8   NvGetVisNo(u8 no);
EWRAM_CODE u8   NvGetCalMonth(u8 num);
EWRAM_CODE u8   NvGetCalDay(u8 num);
EWRAM_CODE u8   NvGetCalWeek(u8 num);
EWRAM_CODE u32  NvGetVblankCnt(void);

EWRAM_CODE bool NvIsSkip(void);
EWRAM_CODE bool NvIsRestart(void);

#ifdef __cplusplus
}
#endif
#endif

