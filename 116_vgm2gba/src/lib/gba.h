/*
	$Id: gba.h,v 1.1 2005/12/14 14:22:18 wntrmute Exp $

	Header file for libgba bios affine functions

	Copyright 2003-2005 by Dave Murphy.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
	USA.

	Please report all bugs and problems through the bug tracker at
	"http://sourceforge.net/tracker/?group_id=114505&atid=668551".

	$Log: gba.h,v $
	Revision 1.1  2005/12/14 14:22:18  wntrmute
	added global gba header
	

*/
//---------------------------------------------------------------------------------
#ifndef	_gba_h_
#define	_gba_h_
//---------------------------------------------------------------------------------

#define _DEBUG					1


// gba_types.h
typedef	unsigned char			u8;		/**< Unsigned 8 bit value	*/
typedef	unsigned short int		u16;	/**< Unsigned 16 bit value	*/
typedef	unsigned int			u32;	/**< Unsigned 32 bit value	*/
typedef	signed char				s8;		/**< Signed 8 bit value	*/
typedef	signed short int		s16;	/**< Signed 16 bit value	*/
typedef	signed int				s32;	/**< Signed 32 bit value	*/
typedef	volatile u8				vu8;	/**< volatile Unsigned 8 bit value	*/
typedef	volatile u16			vu16;	/**< volatile Unigned 16 bit value	*/
typedef	volatile u32			vu32;	/**< volatile Unsigned 32 bit value	*/
typedef	volatile s8				vs8;	/**< volatile Signed 8 bit value	*/
typedef	volatile s16			vs16;	/**< volatile Signed 8 bit value	*/
typedef	volatile s32			vs32;	/**< volatile Signed 8 bit value	*/


// gba_base.h
#define	VRAM		0x06000000
#define	IWRAM		0x03000000
#define	EWRAM		0x02000000
#define	EWRAM_END	0x02040000
#define	SRAM		0x0E000000
#define	REG_BASE	0x04000000
#ifndef	NULL
#define	NULL	0
#endif
#if	defined	( __thumb__ )
#define	SystemCall(Number)	 __asm ("SWI	  "#Number"\n" :::  "r0", "r1", "r2", "r3")
#else
#define	SystemCall(Number)	 __asm ("SWI	  "#Number"	<< 16\n" :::"r0", "r1", "r2", "r3")
#endif
#define BIT(number) (1<<(number))
#define IWRAM_CODE	__attribute__((section(".iwram"), long_call))
#define EWRAM_CODE	__attribute__((section(".ewram"), long_call))
#define IWRAM_DATA	__attribute__((section(".iwram")))
#define EWRAM_DATA	__attribute__((section(".ewram")))
#define EWRAM_BSS	__attribute__((section(".sbss")))
#define ALIGN(m)	__attribute__((aligned (m)))


// gba_dma.h
#define REG_DMA0SAD	*(vu32*)(REG_BASE + 0x0b0)
#define REG_DMA0DAD	*(vu32*)(REG_BASE + 0x0b4)
#define REG_DMA0CNT	*(vu32*)(REG_BASE + 0x0b8)
#define REG_DMA1SAD	*(vu32*)(REG_BASE + 0x0bc)
#define REG_DMA1DAD	*(vu32*)(REG_BASE + 0x0c0)
#define REG_DMA1CNT	*(vu32*)(REG_BASE + 0x0c4)
#define REG_DMA2SAD	*(vu32*)(REG_BASE + 0x0c8)
#define REG_DMA2DAD	*(vu32*)(REG_BASE + 0x0cc)
#define REG_DMA2CNT	*(vu32*)(REG_BASE + 0x0d0)
#define REG_DMA3SAD	*(vu32*)(REG_BASE + 0x0d4)
#define REG_DMA3DAD	*(vu32*)(REG_BASE + 0x0d8)
#define REG_DMA3CNT	*(vu32*)(REG_BASE + 0x0dc)
#define DMA_DST_INC		(0<<21)
#define DMA_DST_DEC		(1<<21)
#define DMA_DST_FIXED	(2<<21)
#define DMA_DST_RELOAD	(3<<21)
#define DMA_SRC_INC		(0<<23)
#define DMA_SRC_DEC		(1<<23)
#define DMA_SRC_FIXED	(2<<23)
#define DMA_REPEAT		(1<<25)
#define DMA16			(0<<26)
#define DMA32			(1<<26)
#define	GAMEPAK_DRQ		(1<<27)
#define DMA_IMMEDIATE	(0<<28)
#define DMA_VBLANK		(1<<28)
#define DMA_HBLANK		(2<<28)
#define DMA_SPECIAL		(3<<28)
#define DMA_IRQ			(1<<30)
#define DMA_ENABLE		(1<<31)
#define DMA_Copy(channel, source, dest, mode) {\
	REG_DMA##channel##SAD = (u32)(source);\
	REG_DMA##channel##DAD = (u32)(dest);\
	REG_DMA##channel##CNT = DMA_ENABLE | (mode); \
}

static inline void dmaCopy(const void * source, void * dest, u32 size) {
	DMA_Copy(3, source, dest, DMA16 | size>>1);
}

#define	DMA0COPY( source, dest, mode) DMA_Copy(0,(source),(dest),(mode))
#define	DMA1COPY( source, dest, mode) DMA_Copy(1,(source),(dest),(mode))
#define	DMA2COPY( source, dest, mode) DMA_Copy(2,(source),(dest),(mode))
#define	DMA3COPY( source, dest, mode) DMA_Copy(3,(source),(dest),(mode))


// gba_input.h
#define REG_KEYINPUT	*(vu16*)(REG_BASE + 0x130)  // Key Input
#define REG_KEYCNT		*(vu16*)(REG_BASE + 0x132)  // Key Control
typedef enum KEYPAD_BITS {
	KEY_A		=	(1<<0),	/*!< keypad A button */
	KEY_B		=	(1<<1),	/*!< keypad B button */
	KEY_SELECT	=	(1<<2),	/*!< keypad SELECT button */
	KEY_START	=	(1<<3),	/*!< keypad START button */
	KEY_RIGHT	=	(1<<4),	/*!< dpad RIGHT */
	KEY_LEFT	=	(1<<5),	/*!< dpad LEFT */
	KEY_UP		=	(1<<6),	/*!< dpad UP */
	KEY_DOWN	=	(1<<7),	/*!< dpad DOWN */
	KEY_R		=	(1<<8),	/*!< Right shoulder button */
	KEY_L		=	(1<<9),	/*!< Left shoulder button */

	KEYIRQ_ENABLE	=	(1<<14),	/*!< Enable keypad interrupt */
	KEYIRQ_OR		=	(0<<15),	/*!< interrupt logical OR mode */
	KEYIRQ_AND		=	(1<<15),	/*!< interrupt logical AND mode */
	DPAD 		=	(KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT) /*!< mask all dpad buttons */
} KEYPAD_BITS;


// gba_interrupt.h
#define MAX_INTS	15
#define INT_VECTOR	*(vu32 *)(0x03007ffc)
#define	REG_IME		*(vu16 *)(REG_BASE + 0x208)	// Interrupt Master Enable
#define	REG_IE		*(vu16 *)(REG_BASE + 0x200)	// Interrupt Enable
#define	REG_IF		*(vu16 *)(REG_BASE + 0x202)	// Interrupt Request

typedef enum irqMASKS {
	IRQ_VBLANK	=	(1<<0),		/*!< vertical blank interrupt mask */
	IRQ_HBLANK	=	(1<<1),		/*!< horizontal blank interrupt mask */
	IRQ_VCOUNT	=	(1<<2),		/*!< vcount match interrupt mask */
	IRQ_TIMER0	=	(1<<3),		/*!< timer 0 interrupt mask */
	IRQ_TIMER1	=	(1<<4),		/*!< timer 1 interrupt mask */
	IRQ_TIMER2	=	(1<<5),		/*!< timer 2 interrupt mask */
	IRQ_TIMER3	=	(1<<6),		/*!< timer 3 interrupt mask */
	IRQ_SERIAL	=	(1<<7),		/*!< serial interrupt mask */
	IRQ_DMA0	=	(1<<8),		/*!< DMA 0 interrupt mask */
	IRQ_DMA1	=	(1<<9),		/*!< DMA 1 interrupt mask */
	IRQ_DMA2	=	(1<<10),	/*!< DMA 2 interrupt mask */
	IRQ_DMA3	=	(1<<11),	/*!< DMA 3 interrupt mask */
	IRQ_KEYPAD	=	(1<<12),	/*!< Keypad interrupt mask */
	IRQ_GAMEPAK	=	(1<<13)		/*!< horizontal blank interrupt mask */
} irqMASK;


// gba_sprites.h
typedef struct {
	u16 attr0;
	u16 attr1;
	u16 attr2;
	u16 dummy;
} OBJATTR;

typedef struct {
	u16 attribute[3];
	u16 dummy;
} SpriteEntry;

typedef struct {
	u16 dummy0[3];
	s16 pa;
	u16 dummy1[3];
	s16 pb;
	u16 dummy2[3];
	s16 pc;
	u16 dummy3[3];
	s16 pd;
} OBJAFFINE;

#define	OAM					((OBJATTR *)0x07000000)
#define OBJ_BASE_ADR		((void *)(VRAM + 0x10000))
#define SPRITE_GFX			((u16 *)(VRAM + 0x10000))
#define BITMAP_OBJ_BASE_ADR	((void *)(VRAM + 0x14000))

enum SPRITE_SHAPES {
	SQUARE,
	WIDE,
	TALL
};
#define OBJ_SHAPE(m)		((m)<<14)


// Sprite Attribute 0
#define OBJ_Y(m)			((m)&0x00ff)
#define OBJ_ROT_SCALE_ON	(1<<8)
#define OBJ_DISABLE			(1<<9)
#define OBJ_DOUBLE			(1<<9)
#define OBJ_MODE(m)			((m)<<10)
#define OBJ_MOSAIC			(1<<12)
#define	OBJ_256_COLOR		(1<<13)
#define	OBJ_16_COLOR		(0<<13)

#define ATTR0_MOSAIC			(1<<12)
#define ATTR0_COLOR_256			(1<<13)
#define ATTR0_COLOR_16			(0<<13)
#define ATTR0_NORMAL			(0<<8)
#define ATTR0_ROTSCALE			(1<<8)
#define ATTR0_DISABLED			(2<<8)
#define ATTR0_ROTSCALE_DOUBLE	(3<<8)

#define ATTR0_SQUARE	OBJ_SHAPE(SQUARE)
#define ATTR0_WIDE		OBJ_SHAPE(WIDE)
#define ATTR0_TALL		OBJ_SHAPE(TALL)
// Sprite Attribute 1
#define OBJ_X(m)			((m)&0x01ff)
#define OBJ_ROT_SCALE(m)	((m)<<9)
#define OBJ_HFLIP			(1<<12)
#define OBJ_VFLIP			(1<<13)

#define ATTR1_ROTDATA(n)      ((n)<<9)  // note: overlaps with flip flags
#define ATTR1_FLIP_X          (1<<12)
#define ATTR1_FLIP_Y          (1<<13)
#define ATTR1_SIZE_8          (0<<14)
#define ATTR1_SIZE_16         (1<<14)
#define ATTR1_SIZE_32         (2<<14)
#define ATTR1_SIZE_64         (3<<14)

#define OBJ_SIZE(m)		((m)<<14)

// Sprite Attribute 2
#define OBJ_CHAR(m)		((m)&0x03ff)
#define OBJ_PRIORITY(m)	((m)<<10)
#define OBJ_PALETTE(m)	((m)<<12)

#define ATTR2_PRIORITY(n)     ((n)<<10)
#define ATTR2_PALETTE(n)      ((n)<<12)

#define OBJ_TRANSLUCENT	OBJ_MODE(1)
#define OBJ_OBJWINDOW	OBJ_MODE(2)
#define OBJ_SQUARE		OBJ_SHAPE(0)
#define OBJ_WIDE		OBJ_SHAPE(1)
#define OBJ_TALL		OBJ_SHAPE(2)

enum SPRITE_SIZECODE {
		Sprite_8x8,
		Sprite_16x16,
		Sprite_32x32,
		Sprite_64x64,
		Sprite_16x8,
		Sprite_32x8,
		Sprite_32x16,
		Sprite_64x32,
		Sprite_8x16,
		Sprite_8x32,
		Sprite_16x32,
		Sprite_32x64
};


// gba_systemcalls.h
typedef enum RESTART_FLAG {
	ROM_RESTART,	/*!< Restart from RAM entry point. */
	RAM_RESTART		/*!< restart from ROM entry point */
} RESTART_FLAG;

enum RESET_FLAG {
	RESET_EWRAM		=	(1<<0),	/*!< Clear 256K on-board WRAM			*/
	RESET_IWRAM		=	(1<<1),	/*!< Clear 32K in-chip WRAM				*/
	RESET_PALETTE	=	(1<<2),	/*!< Clear Palette						*/
	RESET_VRAM		=	(1<<3),	/*!< Clear VRAM							*/
	RESET_OAM		=	(1<<4),	/*!< Clear OAM							*/
	RESET_SIO		=	(1<<5),	/*!< Switches to general purpose mode	*/
	RESET_SOUND		=	(1<<6),	/*!< Reset Sound registers				*/
	RESET_OTHER		=	(1<<7)	/*!< all other registers				*/
};

static inline void Halt()	{ SystemCall(2); }
static inline void Stop()	{ SystemCall(3); }
static inline u32 BiosCheckSum()
{
	register u32 result;
	#if	defined	( __thumb__ )
		__asm ("SWI	0x0d\nmov %0,r0\n" :  "=r"(result) :: "r1", "r2", "r3");
	#else
		__asm ("SWI	0x0d<<16\nmov %0,r0\n" : "=r"(result) :: "r1", "r2", "r3");
	#endif
	return result;
}

static inline void VBlankIntrWait()	{ SystemCall(5); }


// gba_timers.h
#define REG_TM0CNT		*(vu32*)(REG_BASE + 0x100)
#define REG_TM0CNT_L	*(vu16*)(REG_BASE + 0x100)
#define REG_TM0CNT_H	*(vu16*)(REG_BASE + 0x102)
#define REG_TM1CNT		*(vu32*)(REG_BASE + 0x104)
#define REG_TM1CNT_L	*(vu16*)(REG_BASE + 0x104)
#define REG_TM1CNT_H	*(vu16*)(REG_BASE + 0x106)
#define REG_TM2CNT		*(vu32*)(REG_BASE + 0x108)
#define REG_TM2CNT_L	*(vu16*)(REG_BASE + 0x108)
#define REG_TM2CNT_H	*(vu16*)(REG_BASE + 0x10a)
#define REG_TM3CNT		*(vu32*)(REG_BASE + 0x10c)
#define REG_TM3CNT_L	*(vu16*)(REG_BASE + 0x10c)
#define REG_TM3CNT_H	*(vu16*)(REG_BASE + 0x10e)
#define	TIMER_COUNT	BIT(2)
#define	TIMER_IRQ	BIT(6)
#define	TIMER_START	BIT(7)


// gba_video.h
#define BG_COLORS		((u16 *)0x05000000)	// Background color table
#define BG_PALETTE		((u16 *)0x05000000)	// Background color table
#define	OBJ_COLORS		((u16 *)0x05000200)	// Sprite color table
#define	SPRITE_PALETTE	((u16 *)0x05000200)	// Sprite color table
#define	REG_DISPCNT		*((vu16 *)(REG_BASE + 0x00))

typedef enum LCDC_BITS {
	MODE_0	=	0,	/*!< BG Mode 0 */
	MODE_1	=	1,	/*!< BG Mode 1 */
	MODE_2	=	2,	/*!< BG Mode 2 */
	MODE_3	=	3,	/*!< BG Mode 3 */
	MODE_4	=	4,	/*!< BG Mode 4 */
	MODE_5	=	5,	/*!< BG Mode 5 */

	BACKBUFFER	=	BIT(4),		/*!< buffer display select			*/
	OBJ_1D_MAP	=	BIT(6),		/*!< sprite 1 dimensional mapping	*/
	LCDC_OFF	=	BIT(7),		/*!< LCDC OFF						*/
	BG0_ON		=	BIT(8),		/*!< enable background 0			*/
	BG1_ON		=	BIT(9),		/*!< enable background 1			*/
	BG2_ON		=	BIT(10),	/*!< enable background 2			*/
	BG3_ON		=	BIT(11),	/*!< enable background 3			*/
	OBJ_ON		=	BIT(12),	/*!< enable sprites					*/
	WIN0_ON		=	BIT(13),	/*!< enable window 0				*/
	WIN1_ON		=	BIT(14),	/*!< enable window 1				*/
	OBJ_WIN_ON	=	BIT(15),	/*!< enable obj window				*/

	BG0_ENABLE		=	BG0_ON,		/*!< enable background 0	*/
	BG1_ENABLE		=	BG1_ON, 	/*!< enable background 1	*/
	BG2_ENABLE		=	BG2_ON, 	/*!< enable background 2	*/
	BG3_ENABLE		=	BG3_ON,		/*!< enable background 3	*/
	OBJ_ENABLE		=	OBJ_ON, 	/*!< enable sprites			*/
	WIN0_ENABLE		=	WIN0_ON,	/*!< enable window 0		*/
	WIN1_ENABLE		=	WIN1_ON,	/*!< enable window 1		*/
	OBJ_WIN_ENABLE	=	BG0_ON, 	/*!< enable obj window		*/

	BG_ALL_ON		=	BG0_ON | BG1_ON | BG2_ON | BG3_ON, 	    /*!< All Backgrounds on.		*/
	BG_ALL_ENABLE	=	BG0_ON | BG1_ON | BG2_ON | BG3_ON	    /*!< All Backgrounds enabled.	*/

} LCDC_BITS;

#define	REG_DISPSTAT	*((vu16 *)(REG_BASE + 0x04))

enum LCDC_IRQ {
	LCDC_VBL_FLAG	=	(1<<0),
	LCDC_HBL_FLAG	=	(1<<1),
	LCDC_VCNT_FLAG	=	(1<<2),
	LCDC_VBL		=	(1<<3),
	LCDC_HBL		=	(1<<4),
	LCDC_VCNT		=	(1<<5)
};

static inline u32 VCOUNT( int m) { return m<<8; }
#define	REG_VCOUNT		*((vu16 *)(REG_BASE + 0x06))
#define BGCTRL		((vu16 *)(REG_BASE + 0x08))
#define REG_BG0CNT	*((vu16 *)(REG_BASE + 0x08))
#define REG_BG1CNT	*((vu16 *)(REG_BASE + 0x0a))
#define REG_BG2CNT	*((vu16 *)(REG_BASE + 0x0c))
#define REG_BG3CNT	*((vu16 *)(REG_BASE + 0x0e))

typedef struct {
	vu16 x;
	vu16 y;
} bg_scroll;

#define BG_OFFSET ((bg_scroll *)(REG_BASE + 0x10))
#define	REG_BG0HOFS		*((vu16 *)(REG_BASE + 0x10))	// BG 0 H Offset
#define	REG_BG0VOFS		*((vu16 *)(REG_BASE + 0x12))	// BG 0 V Offset
#define	REG_BG1HOFS		*((vu16 *)(REG_BASE + 0x14))	// BG 1 H Offset
#define	REG_BG1VOFS		*((vu16 *)(REG_BASE + 0x16))	// BG 1 V Offset
#define	REG_BG2HOFS		*((vu16 *)(REG_BASE + 0x18))	// BG 2 H Offset
#define	REG_BG2VOFS		*((vu16 *)(REG_BASE + 0x1a))	// BG 2 V Offset
#define	REG_BG3HOFS		*((vu16 *)(REG_BASE + 0x1c))	// BG 3 H Offset
#define	REG_BG3VOFS		*((vu16 *)(REG_BASE + 0x1e))	// BG 3 V Offset
#define	REG_BG2PA	*((vu16 *)(REG_BASE + 0x20))
#define	REG_BG2PB	*((vu16 *)(REG_BASE + 0x22))
#define	REG_BG2PC	*((vu16 *)(REG_BASE + 0x24))
#define	REG_BG2PD	*((vu16 *)(REG_BASE + 0x26))
#define	REG_BG2X	*((vu32 *)(REG_BASE + 0x28))
#define	REG_BG2Y	*((vu32 *)(REG_BASE + 0x2c))
#define	REG_BG3PA	*((vu16 *)(REG_BASE + 0x30))
#define	REG_BG3PB	*((vu16 *)(REG_BASE + 0x32))
#define	REG_BG3PC	*((vu16 *)(REG_BASE + 0x34))
#define	REG_BG3PD	*((vu16 *)(REG_BASE + 0x36))
#define	REG_BG3X	*((vu32 *)(REG_BASE + 0x38))
#define	REG_BG3Y	*((vu32 *)(REG_BASE + 0x3c))
#define BG_SIZE(m)		((m<<14))

enum BG_CTRL_BITS {
	BG_MOSAIC		=	BIT(6),		/*!< enable background mosaic			*/
	BG_16_COLOR		=	(0<<7),		/*!< background uses 16 color tiles		*/
	BG_256_COLOR	=	BIT(7),		/*!< background uses 256 color tiles	*/
	BG_WRAP			=	BIT(13),	/*!< background wraps when scrolling	*/
	BG_SIZE_0		=	BG_SIZE(0),	/*!< Map Size 256x256	*/
	BG_SIZE_1		=	BG_SIZE(1),	/*!< Map Size 512x256	*/
	BG_SIZE_2		=	BG_SIZE(2),	/*!< Map Size 256x512	*/
	BG_SIZE_3		=	BG_SIZE(3),	/*!< Map Size 512x512	*/
};

#define	CHAR_BASE(m)		((m) << 2)
#define BG_TILE_BASE(m)		((m) << 2)
#define CHAR_BASE_ADR(m)	((void *)(VRAM + ((m) << 14)))
#define CHAR_BASE_BLOCK(m)	((void *)(VRAM + ((m) << 14)))
#define MAP_BASE_ADR(m)		((void *)(VRAM + ((m) << 11)))
#define SCREEN_BASE_BLOCK(m)((void *)(VRAM + ((m) << 11)))
#define SCREEN_BASE(m)		((m) << 8)
#define BG_MAP_BASE(m)		((m) << 8)

#define	TILE_BASE(m)		((m) << 2)
#define TILE_BASE_ADR(m)	((void *)(VRAM + ((m) << 14)))

#define MAP_BASE_ADR(m)		((void *)(VRAM + ((m) << 11)))
#define MAP_BASE(m)			((m) << 8)

#define BG_PRIORITY(m)		((m))
#define CHAR_PALETTE(m)		((m)<<12)

#define PATRAM4(x, tn) ((u32 *)(VRAM | (((x) << 14) + ((tn) << 5)) ))
#define PATRAM8(x, tn) ((u32 *)(VRAM | (((x) << 14) + ((tn) << 6)) ))
#define SPR_VRAM(tn) ((u32 *)(VRAM | 0x10000 | ((tn) << 5)))

typedef u16 NAMETABLE[32][32];
#define MAP ((NAMETABLE *)0x06000000)

#define BG_WID_32 BG_SIZE_0
#define BG_WID_64 BG_SIZE_1
#define BG_HT_32  BG_SIZE_0
#define BG_HT_64  BG_SIZE_2

#define ROTBG_SIZE_16  BG_SIZE_0
#define ROTBG_SIZE_32  BG_SIZE_1
#define ROTBG_SIZE_64  BG_SIZE_2
#define ROTBG_SIZE_128 BG_SIZE_3

#define TEXTBG_SIZE_256x256    BG_SIZE_0
#define TEXTBG_SIZE_512x256    BG_SIZE_1
#define TEXTBG_SIZE_256x512    BG_SIZE_2
#define TEXTBG_SIZE_512x512    BG_SIZE_3

#define ROTBG_SIZE_128x128    BG_SIZE_0
#define ROTBG_SIZE_256x256    BG_SIZE_1
#define ROTBG_SIZE_512x512    BG_SIZE_2
#define ROTBG_SIZE_1024x1024  BG_SIZE_3

typedef u16 MODE3_LINE[240];
typedef u16 MODE5_LINE[160];

#define MODE3_FB ((MODE3_LINE *)0x06000000)
#define MODE5_FB ((MODE5_LINE *)0x06000000)
#define MODE5_BB ((MODE5_LINE *)0x0600A000)

#define	REG_WIN0H	*((vu16 *)(REG_BASE + 0x40))
#define	REG_WIN1H	*((vu16 *)(REG_BASE + 0x42))
#define	REG_WIN0V	*((vu16 *)(REG_BASE + 0x44))
#define	REG_WIN1V	*((vu16 *)(REG_BASE + 0x46))
#define	REG_WININ	*((vu16 *)(REG_BASE + 0x48))
#define	REG_WINOUT	*((vu16 *)(REG_BASE + 0x4A))

#define	REG_MOSAIC	*(vu16 *)(REG_BASE + 0x4c)

#define	REG_BLDCNT		*((vu16 *)(REG_BASE + 0x50))
#define	REG_BLDALPHA	*((vu16 *)(REG_BASE + 0x52))
#define	REG_BLDY		*((vu16 *)(REG_BASE + 0x54))

static inline void SetMode(int mode)	{REG_DISPCNT = mode;}

#define RGB5(r,g,b)	((r)|((g)<<5)|((b)<<10))
#define RGB8(r,g,b)	( (((b)>>3)<<10) | (((g)>>3)<<5) | ((r)>>3) )

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160


// gba_sound.h
#define SND1_R_ENABLE	(1<<8)		// Enable left & right speakers for each sound channel
#define SND1_L_ENABLE	(1<<12)
#define SND2_R_ENABLE	(1<<9)
#define SND2_L_ENABLE	(1<<13)
#define SND3_R_ENABLE	(1<<10)
#define SND3_L_ENABLE	(1<<14)
#define SND4_R_ENABLE	(1<<11)
#define SND4_L_ENABLE	(1<<15)

#define SNDA_VOL_50     (0<<2)
#define SNDA_VOL_100    (1<<2)
#define SNDB_VOL_50     (0<<3)
#define SNDB_VOL_100    (1<<3)
#define SNDA_R_ENABLE   (1<<8)
#define SNDA_L_ENABLE   (1<<9)
#define SNDA_RESET_FIFO (1<<11)
#define SNDB_R_ENABLE   (1<<12)
#define SNDB_L_ENABLE   (1<<13)
#define SNDB_RESET_FIFO (1<<15)


#define	REG_SOUNDCNT_L	(*((u16 volatile *) (REG_BASE + 0x080)))
#define	REG_SOUNDCNT_H	(*((u16 volatile *) (REG_BASE + 0x082)))
#define	REG_SOUNDCNT_X	(*((u16 volatile *) (REG_BASE + 0x084)))


#define	REG_SOUND1CNT_L	(*((u16 volatile *) (REG_BASE + 0x060)))
#define	REG_SOUND1CNT_H	(*((u16 volatile *) (REG_BASE + 0x062)))
#define	REG_SOUND1CNT_X	(*((u16 volatile *) (REG_BASE + 0x064)))

#define	REG_SOUND2CNT_L	(*((u16 volatile *) (REG_BASE + 0x068)))
#define	REG_SOUND2CNT_H	(*((u16 volatile *) (REG_BASE + 0x06C)))

#define	REG_SOUND3CNT_L	(*((u16 volatile *) (REG_BASE + 0x070)))
#define	REG_SOUND3CNT_H	(*((u16 volatile *) (REG_BASE + 0x072)))
#define	REG_SOUND3CNT_X	(*((u16 volatile *) (REG_BASE + 0x074)))

#define	REG_SOUND4CNT_L	(*((u16 volatile *) (REG_BASE + 0x078)))
#define	REG_SOUND4CNT_H	(*((u16 volatile *) (REG_BASE + 0x07C)))

#define	REG_SOUNDBIAS	(*((u16 volatile *) (REG_BASE + 0x088)))

#define	REG_FIFO_A		(*((u32 volatile *) (REG_BASE + 0x0A0)))
#define	REG_FIFO_B		(*((u32 volatile *) (REG_BASE + 0x0A4)))

#define	WAVE_RAM	((u16 volatile *)	(REG_BASE + 0x090))

#define	SOUND3_STEP32		(0<<5)	// Use two banks of 32 steps each
#define SOUND3_STEP64		(1<<5)	// Use one bank of 64 steps
#define SOUND3_SETBANK(n)	(n<<6)	// Bank to play 0 or 1 (non set bank is written to)
#define SOUND3_PLAY			(1<<7)	// Output sound
#define SOUND3_STOP			(0<<7)	// Stop sound output

//---------------------------------------------------------------------------------
// pin8 compatible sound macros 
//---------------------------------------------------------------------------------

/*---------------------------------------------------------------------------------
	DMG Sound Control (0x04000080)
fedcba9876543210
|||||||| ||| |||
|||||||| ||| +++- DMG left volume
|||||||| +++----- DMG right volume
|||||||+--------- Enable sqr1 on left
||||||+---------- Enable sqr2 on left
|||||+----------- Enable triangle on left
||||+------------ Enable noise on left
|||+------------- Enable sqr1 on right
||+-------------- Enable sqr2 on right
|+--------------- Enable triangle on right
+---------------- 
---------------------------------------------------------------------------------*/
#define DMGSNDCTRL         (*(volatile u16 *)0x04000080)
#define DMGSNDCTRL_LVOL(x) (x)
#define DMGSNDCTRL_RVOL(x) ((x) << 4)
#define DMGSNDCTRL_LSQR1   0x0100
#define DMGSNDCTRL_LSQR2   0x0200
#define DMGSNDCTRL_LTRI    0x0400
#define DMGSNDCTRL_LNOISE  0x0800
#define DMGSNDCTRL_RSQR1   0x1000
#define DMGSNDCTRL_RSQR2   0x2000
#define DMGSNDCTRL_RTRI    0x4000
#define DMGSNDCTRL_RNOISE  0x8000

/*---------------------------------------------------------------------------------
	Direct Sound Control (0x04000082)
-----------------------------------------------------------------------------------
fedcba9876543210
||||||||    ||||
||||||||    ||++- DMG sound output volume
||||||||    ||    (00: 25%; 01: 50%; 10: 100%)
||||||||    |+--- DSound A output volume (0: 50%; 1: 100%)
||||||||    +---- DSound B output volume (0: 50%; 1: 100%)
|||||||+--------- Enable DSound A on right
||||||+---------- Enable DSound A on left
|||||+----------- DSound A sample timer (0 or 1)
||||+------------ DSound A FIFO reset
|||+------------- Enable DSound B on right
||+-------------- Enable DSound B on left
|+--------------- DSound B sample timer (0 or 1)
+---------------- DSound B FIFO reset
---------------------------------------------------------------------------------*/
#define DSOUNDCTRL           (*(volatile u16 *)0x04000082)
#define DSOUNDCTRL_DMG25     0x0000
#define DSOUNDCTRL_DMG50     0x0001
#define DSOUNDCTRL_DMG100    0x0002
#define DSOUNDCTRL_A50       0x0000
#define DSOUNDCTRL_A100      0x0004
#define DSOUNDCTRL_B50       0x0000
#define DSOUNDCTRL_B100      0x0008
#define DSOUNDCTRL_AR        0x0100
#define DSOUNDCTRL_AL        0x0200
#define DSOUNDCTRL_ATIMER(x) ((x) << 10)
#define DSOUNDCTRL_ARESET    0x0800
#define DSOUNDCTRL_BR        0x1000
#define DSOUNDCTRL_BL        0x2000
#define DSOUNDCTRL_BTIMER(x) ((x) << 14)
#define DSOUNDCTRL_BRESET    0x8000

/*---------------------------------------------------------------------------------
 Sound Status (0x04000084)
-----------------------------------------------------------------------------------
Note that unlike NES's $4014, bits 0 to 3 of this register are
read-only.  They do not enable sound.

fedcba9876543210
        |   ||||
        |   |||+- Square 1 playing
        |   ||+-- Square 2 playing
        |   |+--- Triangle playing
        |   +---- Noise playing
        +-------- 0: save 10% battery power by turning off ALL sound;
                  1: play sound
---------------------------------------------------------------------------------*/
#define SNDSTAT        (*(volatile u16*)0x04000084)
#define SNDSTAT_SQR1   0x0001
#define SNDSTAT_SQR2   0x0002
#define SNDSTAT_TRI    0x0004
#define SNDSTAT_NOISE  0x0008
#define SNDSTAT_ENABLE 0x0080

/*---------------------------------------------------------------------------------
	Sound Bias: will not be documented.
-----------------------------------------------------------------------------------
fedcba9876543210
||    ||||||||||
||    ++++++++++- PWM bias
++--------------- Amplitude resolution
                  00: 9-bit at 32768 Hz
                  01: 8-bit at 65536 Hz (most common)
                  10: 7-bit at 131072 Hz
                  11: 6-bit at 262144 Hz

Do NOT use SNDBIAS directly.  To set the resolution, use
  SETSNDRES(1);
---------------------------------------------------------------------------------*/
#define SNDBIAS      (*(volatile u16 *)0x04000088)
#define SETSNDRES(x) SNDBIAS = (SNDBIAS & 0x3fff) | (x << 14)

#define DSOUND_FIFOA (*(volatile u32 *)0x040000a0)
#define DSOUND_FIFOB (*(volatile u32 *)0x040000a4)


/*---------------------------------------------------------------------------------
 Square 1 Sweep Register
---------------------------------------------------------------------------------

fedcba9876543210
         |||||||
         ||||+++- Sweep shifts (1 fastest; 7 slowest)
         |||+---- 0: Sweep up; 1: Sweep down

Write 0x0040 into this register to disable sweep.
---------------------------------------------------------------------------------*/
#define SQR1SWEEP   (*(volatile u16 *)0x04000060)
#define SQR1SWEEP_OFF 0x0008


/*---------------------------------------------------------------------------------
   Square 1 Control Register
   Square 2 Control Register
-----------------------------------------------------------------------------------
fedcba9876543210
||||||||||||||||
||||||||||++++++- Sound length (1 longest; 63: shortest)
||||||||++------- Duty cycle (00: 1/8; 01: 1/4; 10: 1/2; 11: 3/4)
|||||+++--------- Envelope step time (0: off; 1 fastest; 7 slowest)
||||+------------ Envelope direction (0: decrease; 1: increase)
++++------------- Volume
---------------------------------------------------------------------------------*/
#define SQR1CTRL    (*(volatile u16 *)0x04000062)
#define SQR2CTRL    (*(volatile u16 *)0x04000068)
#define SQR_DUTY(n) ((n) << 6)
#define SQR_VOL(n)  ((n) << 12)

/*---------------------------------------------------------------------------------
   Square 1 Frequency
   Square 2 Frequency
   Triangle Channel Frequency (0x04000074)
-----------------------------------------------------------------------------------
fedcba9876543210
||   |||||||||||
||   +++++++++++- frequency (131072 Hz/(2048-x)) (halved for tri channel)
|+--------------- 0: hold note; 1: use length
+---------------- 1: Reset channel
---------------------------------------------------------------------------------*/
#define SQR1FREQ      (*(volatile u16 *)0x04000064)
#define SQR2FREQ      (*(volatile u16 *)0x0400006c)
#define TRIFREQ       (*(volatile u16 *)0x04000074)
#define TRIFREQ_HOLD  0x0000
#define TRIFREQ_TIMED 0x4000
#define TRIFREQ_RESET 0x8000


/*---------------------------------------------------------------------------------
	Triangle Channel Control Register
-----------------------------------------------------------------------------------
fedcba9876543210
        |||
        ||+------ Bank mode (0: 2 banks of 32; 1: 1 bank of 64)
        |+------- Play this bank (and write other bank)
        +-------- Enable triangle channel
---------------------------------------------------------------------------------*/
#define TRICTRL         (*(volatile u16 *)0x04000070)
#define TRICTRL_2X32    0x0000
#define TRICTRL_1X64    0x0020
#define TRICTRL_BANK(x) ((x) << 6)
#define TRICTRL_ENABLE  0x0080

/*---------------------------------------------------------------------------------
	Triangle Channel Length/Volume (0x04000072)
-----------------------------------------------------------------------------------

fedcba9876543210
|||     ||||||||
|||     ++++++++- Length ((256-x)/256 seconds)
+++-------------- Volume (000: mute; 001: 100%; 010: 50%;
                          011: 25%; 100: 75%)
---------------------------------------------------------------------------------*/
#define TRILENVOL        (*(volatile u16 *)0x04000072)
#define TRILENVOL_LEN(x) (256 - (x))
#define TRILENVOL_MUTE   0x0000
#define TRILENVOL_25     0x6000
#define TRILENVOL_50     0x4000
#define TRILENVOL_75     0x8000
#define TRILENVOL_100    0x2000

#define TRIWAVERAM ((volatile u32 *)0x04000090)


// C³•ªA’Ç‰Á•ª
//---------------------------------------------------------------------------
// Reg
#define REG_IRQ_WAITFLAGS		*(volatile u16*)0x3007FF8
#define REG_WSCNT				*(volatile u16*)0x4000204


//---------------------------------------------------------------------------
// KeyMask
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

typedef enum { FALSE, TRUE } bool;


#include "common.h"
#include "div.h"
#include "sys.arm.h"
#include "gbfs.h"

//---------------------------------------------------------------------------------
#endif //_gba_h
//---------------------------------------------------------------------------------
