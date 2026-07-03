/**************************************/
#include "AsmMacros.h"
/**************************************/
#include "ulc_Specs.h"
/**************************************/

ASM_FUNC_GLOBAL(ulc_StopPlayer)
ASM_FUNC_BEG   (ulc_StopPlayer, ASM_MODE_THUMB;ASM_SECTION_TEXT)

ulc_StopPlayer:
	LDR	r1, =ulc_State
	MOV	r0, #0x00
	STR	r0, [r1, #0x08]        @ SoundFile = NULL
#if !ULC_USER_HWSETUP
# if ULC_STEREO_SUPPORT
	LDR	r1, [r1, #0x08]        @ &File -> r1
	LDRH	r1, [r1, #0x10]        @ File.nChan -> r1
	CMP	r1, #0x01              @ nChan == 1?
# endif
0:	LDR	r2, =0x04000080
	STRH	r2, [r2, #0x82-0x80]   @ Disable DMA audio
	STR	r0, [r2, #0xC4-0x80]   @ Disable DMA1
# if ULC_STEREO_SUPPORT
	BLS	0f
	STR	r0, [r2, #0xD0-0x80]   @ Disable DMA2 (with nChan > 1)
# endif
0:	ADD	r2, #0x0100-0x80
	STRH	r0, [r2, #0x02]        @ Disable TM0
#endif
0:	@MOV	r0, #0x00              @ Return 0 for compatibility with ulc_UpdatePlayer()
	BX	lr

ASM_FUNC_END(ulc_StopPlayer)

/**************************************/
//! EOF
/**************************************/
