/**************************************/
#include "AsmMacros.h"
/**************************************/
#include "ulc_Specs.h"
/**************************************/

ASM_DATA_GLOBAL(ulc_State)
ASM_DATA_BEG   (ulc_State, ASM_SECTION_EWRAM_BSS;ASM_ALIGN(4))

ulc_State:
	.byte  0 @ [00h]  RdBufIdx
	.byte  0 @ [01h]  nBufProc
	.hword 0 @ [02h]  LastSubBlockSize
	.word  0 @ [04h]  WrBufIdx | Pause<<1 | nBlkRem<<2
	.word  0 @ [08h] &SoundFile
	.word  0 @ [0Ch] &NextData

ASM_DATA_END(ulc_State)

/**************************************/

ASM_DATA_GLOBAL(ulc_OutputBuffer)
ASM_DATA_BEG   (ulc_OutputBuffer, ASM_SECTION_EWRAM_BSS;ASM_ALIGN(4))

ulc_OutputBuffer:
	.space (0x01 * ULC_MAX_BLOCK_SIZE*(2-ULC_SINGLE_BUFFER)) * (1+ULC_STEREO_SUPPORT)

ASM_DATA_END(ulc_OutputBuffer)

/**************************************/
//! EOF
/**************************************/
