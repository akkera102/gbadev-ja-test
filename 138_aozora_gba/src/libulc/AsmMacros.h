/**************************************/
#pragma once
/**************************************/

//! Global helpers
#define ASM_ALIGN(x)               .balign x;
#define ASM_WEAK(...)              .weak __VA_ARGS__;
#define ASM_WEAKREF(Alias, Target) .weakref Alias, Target;

/**************************************/

//! Section definitions
#define ASM_SECTION_DATA   .section .data;
#define ASM_SECTION_RODATA .section .rodata;
#define ASM_SECTION_TEXT   .section .text;
#define ASM_SECTION_IWRAM  .section .iwram, "awx", %progbits;
#ifdef ASM_BSS_IS_EWRAM
# define ASM_SECTION_IWRAM_BSS .section .sbss, "aw", %nobits;
# define ASM_SECTION_EWRAM_BSS .section .bss,  "aw", %nobtis;
#else
# define ASM_SECTION_IWRAM_BSS .section .bss,  "aw", %nobits;
# define ASM_SECTION_EWRAM_BSS .section .sbss, "aw", %nobtis;
#endif

/**************************************/

//! Function helpers
#define ASM_MODE_ARM   .balign 4; .arm;
#define ASM_MODE_THUMB .balign 2; .thumb_func;

//! Function global macro
#define ASM_FUNC_GLOBAL(...) \
	.global __VA_ARGS__

//! Function begin macro
//! Usually pass a section in varg
#define ASM_FUNC_BEG(Name, Args) \
	Args;                    \
	.type Name, %function

//! Function end macro
#define ASM_FUNC_END(Name) \
	.size Name, . - Name

/**************************************/

//! Data global macro
#define ASM_DATA_GLOBAL(...) \
	.global __VA_ARGS__

//! Data begin macro
//! Usually pass a section in varg
#define ASM_DATA_BEG(Name, Args) \
	Args;                    \
	.type Name, %object

//! Data end macro
#define ASM_DATA_END(Name) \
	.size Name, . - Name

/**************************************/
//! EOF
/**************************************/
