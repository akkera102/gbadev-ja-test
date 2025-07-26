/**************************************/
#include "AsmMacros.h"
/**************************************/
#include "ulc_Specs.h"
/**************************************/

@ r0: &SoundFile

ASM_FUNC_GLOBAL(ulc_StartPlayer)
ASM_FUNC_BEG   (ulc_StartPlayer, ASM_MODE_THUMB;ASM_SECTION_TEXT)

ulc_StartPlayer:
	MOV	r3, lr
	PUSH	{r3,r4}
	LDR	r2, [r0, #0x00] @ File.Magic -> r2
	LDRH	r4, [r0, #0x04] @ File.BlockSize -> r4
	LDR	r3, =ULC_FILE_MAGIC
0:	CMP	r2, r3                             @ Signature mismatch?
	BNE	.LInit_Exit_Fail
	LDRH	r2, [r0, #0x10]                    @ File.nChan -> r2
	LSR	r3, r4, #ULC_MAX_BLOCK_SIZE_LOG2+1 @ Incompatible block size?
	BNE	.LInit_Exit_Fail
#if ULC_STEREO_SUPPORT
	SUB	r1, r2, #0x01                      @ Incompatible number of channels?
	MOV	ip, r1                             @ [IsStereo -> ip]
	CMP	r1, #0x02-1
	BHI	.LInit_Exit_Fail
#else
	CMP	r2, #0x01
	BNE	.LInit_Exit_Fail
#endif
	LDR	r3, [r0, #0x08]                @ State.nBlkRem = File.nBlocks-1 -> r3
	LDR	r1, =ulc_State
	LSL	r3, #0x02                      @ WrBufIdx=0 | Pause=0
	MOV	r2, #0x00
	STMIA	r1!, {r2,r3}                   @ RdBufIdx = 0,nBufProc = 0,LastSubBlockSize = 0, store WrBufIdx|nBlkRem<<1
	LDR	r2, [r0, #0x14]                @ File.StreamOffs -> r2
	ADD	r2, r0                         @ State.SoundFile = File, State.NextData = File + StreamOffs
	STMIA	r1!, {r0,r2}
#if ULC_STEREO_SUPPORT
	ADD	r4, r4                         @ IsStereo | BlockSize<<1 -> r4
	ADD	r4, ip
#endif
1:	LDR	r1, [r0, #0x0C]                @ Period = Ceil[HW_RATE / RateHz] -> r0
	MOV	r0, #0x01
	LSL	r0, #0x18
	SUB	r0, #0x01
	BL	__aeabi_uidiv
	@ADD	r0, #0x01                      @ <- Account for this later

.LInit_ClearBuffers:
	PUSH	{r0}
	LDR	r0, =ulc_OutputBuffer
	MOV	r1, #0x00
	LDR	r2, =0x01 * (ULC_MAX_BLOCK_SIZE*(2-ULC_SINGLE_BUFFER)) * (1+ULC_STEREO_SUPPORT)
	BL	memset
	LDR	r0, =ulc_LappingBuffer
	MOV	r1, #0x00
	LDR	r2, =0x04 * (ULC_MAX_BLOCK_SIZE/2) * (1+ULC_STEREO_SUPPORT)
	BL	memset
	POP	{r0}

.LInit_SetupHardware:
#if !ULC_USER_HWSETUP
	LDR	r1, =0x04000080    @ &SOUNDCNT -> r1
# if ULC_STEREO_SUPPORT
	LSR	r4, #0x01          @ IsStereo? (and restore BlockSize -> r4)
	BCS	2f
1:	LDR	r2, =0x0B04        @ FIFOA 100%,             FIFOA -> L, FIFOA -> R, FIFOA reset
	B	3f
2:	LDR	r2, =0x9A0C        @ FIFOB 100%, FIFOB 100%, FIFOA -> L, FIFOB -> R, FIFOA reset, FIFOB reset
# else
	LDR	r2, =0x0B04        @ FIFOA 100%,             FIFOA -> L, FIFOA -> R, FIFOA reset
# endif
3:	STR	r1, [r1, #0x04]    @ Master enable for audio (Bit7)
	STRH	r2, [r1, #0x02]    @ Store DMA audio control
# if ULC_STEREO_SUPPORT
	MOV	ip, r2             @ Save DMA audio control -> ip
# endif
1:	ADD	r1, #0x0100-0x80   @ &TM0 -> r1
	MOV	r2, #0x81          @ TM0 = ENABLE, Period = HW_RATE / RateHz
	LSL	r2, #0x10          @ [C=0]
	STRH	r2, [r1, #0x02]    @ [TM0CNT = 0, safety]
	SBC	r2, r0             @ [this completes the ceiling division by adding 1 to the off-by-one result]
	STR	r2, [r1, #0x00]    @ Start FIFO timer
2:	SUB	r1, #0x0100 - 0xBC @ &DMA1 -> r1
	LDR	r0, =ulc_OutputBuffer
	MOV	r2, #0xBC-0xA0     @ DMA1.Dst = &FIFOA -> r2
	SUB	r2, r1, r2
	MOV	r3, #0xB6          @ DMA1.Cnt = DST_INC, SRC_INC, REPT, WORDS, SOUNDFIFO, ENABLE
	LSL	r3, #0x18
	STRH	r3, [r1, #0x0A]    @ [CNT_H=0, safety]
	STMIA	r1!, {r0,r2,r3}
# if ULC_STEREO_SUPPORT
	MOV	r4, ip             @ Stereo has DMA bit 15 set
	LSR	r4, #0x0F
	BEQ	1f
0:	LSL	r4, #ULC_MAX_BLOCK_SIZE_LOG2+1
	ADD	r2, #0x04          @ DMA2.Dst = &FIFOB -> r2
	ADD	r0, r4             @ Advance source to the right-channel buffer
	STRH	r3, [r1, #0x0A]
	STMIA	r1!, {r0,r2,r3}
1:
# endif
#endif

.LInit_Exit_Okay:
	MOV	r0, #0x00 @ Return TRUE
	POP	{r3,r4}
	BX	r3

.LInit_Exit_Fail:
	MOV	r0, #0x00 @ Return FALSE
	POP	{r3,r4}
	BX	r3

ASM_FUNC_END(ulc_StartPlayer)

/**************************************/
//! EOF
/**************************************/
