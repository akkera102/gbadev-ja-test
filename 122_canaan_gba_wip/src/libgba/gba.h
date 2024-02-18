#ifndef	_GBA_H_
#define	_GBA_H_

//---------------------------------------------------------------------------
#define _DEBUG					0


//---------------------------------------------------------------------------
#include <gba_affine.h>
#include <gba_compression.h>
#include <gba_console.h>
#include <gba_dma.h>
#include <gba_input.h>
#include <gba_interrupt.h>
#include <gba_multiboot.h>
#include <gba_sio.h>
#include <gba_sound.h>
#include <gba_sprites.h>
#include <gba_systemcalls.h>
#include <gba_timers.h>
#include <gba_video.h>


// fixed, added
//---------------------------------------------------------------------------
// Reg
#define REG_IRQ_WAITFLAGS		*(volatile u16*)0x3007FF8
#define REG_WSCNT				*(volatile u16*)0x4000204


//---------------------------------------------------------------------------
// Key
#define KEY_NONE				0x0000
#define STAT_MASK				0x00ff


//---------------------------------------------------------------------------
// SetMode
#define OBJ_2D_MAP				0x0


//---------------------------------------------------------------------------
// Timer
#define TIMER_FREQ_PER_1		0
#define TIMER_FREQ_PER_64		1
#define TIMER_FREQ_PER_256		2
#define TIMER_FREQ_PER_1024		3
#define TIMER_CASCADE			(1<<2)


//---------------------------------------------------------------------------
// Mosaic
#define MOSAIC_BG_H(x)			((x)<<0)
#define MOSAIC_BG_V(x)			((x)<<4)
#define MOSAIC_OBJ_H(x)			((x)<<8)
#define MOSAIC_OBJ_V(x)			((x)<<12)


//---------------------------------------------------------------------------
// Window
#define WIN_RIGHT(x)			((x)<<0)		// REG_WIN0H, WIN1H
#define WIN_LEFT(x)				((x)<<8)

#define WIN_DOWN(x)				((x)<<0)		// REG_WIN0V, WIN1V
#define WIN_TOP(x)				((x)<<8)

#define WIN_0_BG0				(1<<0)			// REG_WININ, WINOUT
#define WIN_0_BG1				(1<<1)
#define WIN_0_BG2				(1<<2)
#define WIN_0_BG3				(1<<3)
#define WIN_0_OBJ				(1<<4)
#define WIN_0_SPE				(1<<5)
#define WIN_1_BG0				(1<<8)
#define WIN_1_BG1				(1<<9)
#define WIN_1_BG2				(1<<10)
#define WIN_1_BG3				(1<<11)
#define WIN_1_OBJ				(1<<12)
#define WIN_1_SPE				(1<<13)


//---------------------------------------------------------------------------
// Blend
#define BLEND_TOP_BG0			(1<<0)			// REG_BLDCNT
#define BLEND_TOP_BG1			(1<<1)
#define BLEND_TOP_BG2			(1<<2)
#define BLEND_TOP_BG3			(1<<3)
#define BLEND_TOP_OBJ			(1<<4)
#define BLEND_TOP_BD			(1<<5)
#define BLEND_LOW_BG0			(1<<8)
#define BLEND_LOW_BG1			(1<<9)
#define BLEND_LOW_BG2			(1<<10)
#define BLEND_LOW_BG3			(1<<11)
#define BLEND_LOW_OBJ			(1<<12)
#define BLEND_LOW_BD			(1<<13)
                     
#define BLEND_MODE_OFF			(0<<6)			// REG_BLDALPHA
#define BLEND_MODE_ALPHA		(1<<6)
#define BLEND_MODE_LIGHT		(2<<6)
#define BLEND_MODE_DARK			(3<<6)
#define BLEND_LOW(n)			((n)<<0)
#define BLEND_HIGH(n)			((n)<<8)
#define BLEND_LEVEL(n)			(BLEND_LOW(n) | BLEND_HIGH(n))
#define BLEND_BALANCE(n)		(BLEND_LOW(n) | BLEND_HIGH(16-n))

#define BLEND_DEPTH(n)			((n)<<0)		// REG_BLDY

//---------------------------------------------------------------------------
// Sprite
#define SP_PAL(pal)				((pal) << 12)
#define SP_NOFLIP				((0x4000))
#define SP_HFLIP				((0x1000) | (0x4000))
#define SP_VFLIP				((0x2000) | (0x4000))
#define SP_HVFLIP				(SP_HFLIP | SP_VFLIP)


//---------------------------------------------------------------------------
// Bios
#define CPUSET_SRC_FIX		(1<<24)
#define CPUSET_16BIT		(0<<26)
#define CPUSET_32BIT		(1<<26)


//---------------------------------------------------------------------------
// mGBA debug
#define REG_DEBUG_ENABLE  *(volatile u16*) 0x4FFF780
#define REG_DEBUG_FLAGS   *(volatile u16*) 0x4FFF700
#define REG_DEBUG_STR      (char*) 0x4FFF600


//---------------------------------------------------------------------------
// Etc
#if _DEBUG
#define TRACE					_Printf
#define _ASSERT(x)				if(!(x)) SystemError("[Assert] %s(%d): "#x"\n", __FILE__, __LINE__)
#else
#define TRACE(...)				((void)0)
#define _ASSERT(x)				((void)0)
#endif

#define __PACKED				__attribute__((__packed__))
#define HIBYTE(x)				((u8)(((x) >> 8) & 0xff))
#define LOBYTE(x)				((u8)((x) & 0xff))
#define MAKEWORD(l, h)			(((l) & 0xff) | (((h) << 8) & 0xff00))

#define ROM_CODE				__attribute__((section (".text"),long_call))
#define ROM_DATA				__attribute__((section (".roda")))

#define SCREEN_CX				240
#define SCREEN_CY				160


#include "common.h"


//---------------------------------------------------------------------------
#endif
