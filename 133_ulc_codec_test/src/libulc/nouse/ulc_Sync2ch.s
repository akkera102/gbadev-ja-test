/**************************************/
#include "AsmMacros.h"
/**************************************/
#include "ulc_Specs.h"
/**************************************/
#if (!ULC_SINGLE_BUFFER && ULC_STEREO_SUPPORT)
/**************************************/

ASM_FUNC_GLOBAL(ulc_Sync2ch)
ASM_FUNC_BEG   (ulc_Sync2ch, ASM_MODE_THUMB;ASM_SECTION_IWRAM)

ulc_Sync2ch:
	LDR	r0, =ulc_State
	LDR	r1, [r0, #0x08] @ Ensure SoundFile != NULL
	CMP	r1, #0x00
	BEQ	3f
1:	LDRB	r2, [r0, #0x00] @ RdBufIdx ^= 1 -> r3?
	MOV	r3, #0x01
	EOR	r3, r2
	BNE	2f
1:	LSL	r2, #0x1A       @ &REG_BASE -> r1
	ADD	r2, #0xC4       @ &DMA1CNT -> r1
	MOV	r3, #0xB6       @ Ctrl = DST_INC, SRC_INC, REPT, WORDS, SOUNDFIFO, ENABLE -> r3
	LSL	r3, #0x18
	STRH	r3, [r2, #0x02] @ DMA1CNT_H = 0
	STR	r3, [r2, #0x00] @ DMA1CNT = Ctrl
	STRH	r3, [r2, #0x0E] @ DMA2CNT_H = 0
	STR	r3, [r2, #0x0C] @ DMA2CNT = Ctrl
2:	LDRB	r1, [r0, #0x01] @ nBufProc++
	STRB	r3, [r0, #0x00]
	ADD	r1, #0x01
	STRB	r1, [r0, #0x01]
3:	BX	lr

ASM_FUNC_END(ulc_Sync2ch)

/**************************************/
#endif
/**************************************/
//! EOF
/**************************************/
