// Sogna WIN2TXT (Windows Viper GTS)
// Copyright (C) 2024 Notequalsoft. Arranged by akkera102. GPL2 License.

// gcc win2txt_debug.c -o win2txt_debug

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

//---------------------------------------------------------------------------
typedef unsigned char			 u8;
typedef char					 s8;
typedef unsigned short			u16;
typedef short					s16;
typedef unsigned int			u32;
typedef int						s32;

typedef struct {
	u8* p;
	s32 size;
	s32 pos;

} ST_BIT;

//---------------------------------------------------------------------------
ST_BIT Bit;


//---------------------------------------------------------------------------
void  BitCalloc(char* fname);
void  BitFree(void);
u8    BitCur8(void);
u8    BitGet8(void);
u16   BitGet16(void);
char* BitGetStr(void);

void WinWrite(FILE* fp);
//---------------------------------------------------------------------------
void BitCalloc(char* fname)
{
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't find file \"%s\"\n", fname);

		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Bit.size = ftell(fp);

	Bit.p = (u8*)calloc(Bit.size, sizeof(u8));

	if(Bit.p == NULL)
	{
		fprintf(stderr, "calloc datSize error\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Bit.p, 1, Bit.size, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void BitFree(void)
{
	free(Bit.p);

	Bit.p = NULL;
}
//---------------------------------------------------------------------------
u8 BitCur8(void)
{
	assert(Bit.pos < Bit.size);

	return Bit.p[Bit.pos];
}
//---------------------------------------------------------------------------
u8 BitGet8(void)
{
	assert(Bit.pos < Bit.size);

	return Bit.p[Bit.pos++];
}
//---------------------------------------------------------------------------
u16 BitGet16(void)
{
	u16 b1 = BitGet8();
	u16 b2 = BitGet8() << 8;

	return b2 | b1;
}
//---------------------------------------------------------------------------
char* BitGetStr(void)
{
	char* pRet = Bit.p + Bit.pos;

	while(Bit.p[Bit.pos++] != '\0')
	{
		// EMPTY
	}

	return pRet;
}
//---------------------------------------------------------------------------
void WinWrite(FILE* fp)
{
	u16 a, b, c, d, e, f, g, h, i;
	u8 op;
	char* s;

	while(Bit.pos < Bit.size)
	{
		fprintf(fp, "0x%04X: ", Bit.pos);
		op = BitGet8();

		switch(op)
		{
		case 0x00:
			// NONE
			fprintf(fp, "STOP\n");
			break;

		case 0x01:
			a = BitGet16();		// LEFT
			b = BitGet16();		// TOP
			fprintf(fp, "SET_VIEWPORT_POS %d %d\n", a, b);
			break;

		case 0x02:
			a = BitGet16();		// WIDTH
			b = BitGet16();		// HEIGHT
			fprintf(fp, "SET_VIEWPORT_SIZE %d %d\n", a, b);
			break;

		case 0x03:
			a = BitGet8();		// IMAGE
			s = BitGetStr();	// FILE
			fprintf(fp, "LOAD_ANM %d %s\n", a, s);
			break;

		case 0x04:
			a = BitGet8();		// IMAGE
			fprintf(fp, "UNLOAD_ANM %d\n", a);
			break;

		case 0x05:
			a = BitGet8();		// COLOR
			b = BitGet16();		// CYCLES
			fprintf(fp, "FADE_IN_GRAYSCALE %d %d\n", a, b);
			break;

		case 0x06:
			a = BitGet8();		// COLOR
			b = BitGet16();		// CYCLES
			fprintf(fp, "FADE_OUT_GRAYSCALE %d %d\n", a, b);
			break;

		case 0x07:
			a = BitGet8();		// IMAGE
			fprintf(fp, "SET_PALETTE_FROM_ANM %d\n", a);
			break;

		case 0x08:
			// NONE
			fprintf(fp, "FORCE_FINISH_FADE_IN\n");
			break;

		case 0x09:
			// NONE
			fprintf(fp, "FORCE_FINISH_FADE_OUT\n");
			break;

		case 0x0A:
			a = BitGet8();		// BUFFER
			b = BitGet16();		// LEFT
			c = BitGet16();		// TOP
			d = BitGet8();		// FLAGS1			X2
			e = BitGet8();		// FLAGS2			X2
			f = BitGet8();		// IMAGE
			g = BitGet8();		// MASK_COLOR		X2
			fprintf(fp, "SET_BUFFER_PROPERTIES %d %d %d 0x%02X 0x%02X %d 0x%02X", a, b, c, d, e, f, g);

			// FRAMES
			while(BitCur8() != 0x00)
			{
				a = BitGet8();
				b = BitGet8();

				fprintf(fp, " %d:%d", a, b);
			}
			fprintf(fp, "\n");

			// 0x00 skip
			BitGet8();

			break;

		case 0x0B:
			a = BitGet8();		// BUFFER
			fprintf(fp, "RESET_BUFFER_FLAGS %d\n", a);
			break;

		case 0x0C:
			a = BitGet8();		// BUFFER
			fprintf(fp, "WAIT_FOR_BUFFER %d\n", a);
			break;

		case 0x0D:
			// NONE
			fprintf(fp, "RESET_ALL_BUFFER_FLAGS\n");
			break;

		case 0x0E:
			// NONE
			fprintf(fp, "WAIT_FOR_INPUT\n");
			break;

		case 0x0F:
			// NONE
			fprintf(fp, "WAIT_FOR_INPUT2\n");
			break;

		case 0x10:
			a = BitGet8();		// BUFFER
			fprintf(fp, "CLEAR_IMAGE_PROPERTIES %d\n", a);
			break;

		case 0x11:
			// NONE
			fprintf(fp, "UNKNOWN_11\n");
			break;

		case 0x12:
			a = BitGet8();		// IMAGE
			b = BitGet8();		// OFFSET
			c = BitGet8();		// BUFFER
			d = BitGet16();		// LEFT
			e = BitGet16();		// TOP
			fprintf(fp, "SET_IMAGE_PROPERTIES %d %d %d %d %d\n", a, b, c, d, e);
			break;

		case 0x13:
			a = BitGet16();		// HUNDREDTH_SECONDS
			fprintf(fp, "SLEEP %d\n", a);
			break;

		case 0x14:
			a = BitGet16();		// ADR
			fprintf(fp, "JUMP 0x%04X\n", a);
			break;

		case 0x15:
			a = BitGet16();		// ADR
			fprintf(fp, "ON_INPUT_JUMP 0x%04X\n", a);
			break;

		case 0x16:
			a = BitGet16();		// ADR
			fprintf(fp, "ON_ESCAPE_JUMP 0x%04X\n", a);
			break;

		case 0x17:
			a = BitGet8();		// BUFFER
			b = BitGet16();		// START_X
			c = BitGet16();		// END_X
			d = BitGet16();		// VISIBLE_WIDTH
			e = BitGet16();		// START_Y
			f = BitGet16();		// END_Y
			g = BitGet16();		// VISIBLE_HEIGHT
			h = BitGet16();		// CYCLES
			fprintf(fp, "SCROLL_VIEWPORT %d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h);
			break;

		case 0x18:
			a = BitGet8();		// BUFFER
			fprintf(fp, "WAIT_FOR_SCROLL %d\n", a);
			break;

		case 0x19:
			a = BitGet8();		// LOOP
			b = BitGet8();		// STEAM
			fprintf(fp, "PLAY_MIDI %d %d\n", a, b);
			break;

		case 0x1A:
			// NONE
			fprintf(fp, "STOP_MIDI\n");
			break;

		case 0x1B:
			a = BitGet8();		// STREAM
			s = BitGetStr();	// FILE
			fprintf(fp, "LOAD_MIDI %d %s\n", a, s);
			break;

		case 0x1C:
			// NONE
			fprintf(fp, "UNKNOWN_1C\n");
			break;

		case 0x1D:
			a = BitGet8();		// STREAM
			s = BitGetStr();	// FILE
			fprintf(fp, "PLAY_PCM %d %s\n", a, s);
			break;

		case 0x1E:
			// NONE
			fprintf(fp, "STOP_PCM\n");
			break;

		case 0x1F:
			// NONE
			fprintf(fp, "STOP_PCM_ON_NEXT_REFRESH\n");
			break;

		case 0x20:
			a = BitGet16();		// LEFT
			b = BitGet16();		// TOP
			c = BitGet8();		// CHARS
			d = BitGet8();		// LINES
			fprintf(fp, "SET_TEXT_AREA %d %d %d %d\n", a, b, c, d);
			break;

		case 0x21:
			s = BitGetStr();	// TEXT
			fprintf(fp, "DISPLAY_TEXT %s\n", s);
			break;

		case 0x22:
			a = BitGet8();		// PIXELS
			fprintf(fp, "SET_TEXT_INDENT %d\n", a);
			break;

		case 0x23:
			a = BitGet8();		// HEIGHT
			fprintf(fp, "SET_FONT_SIZE %d\n", a);
			break;

		case 0x24:
			a = BitGet8();		// TOKEN
			s = BitGetStr();	// TEXT
			fprintf(fp, "SET_TEXT_TOKEN %d %s\n", a, s);
			break;

		case 0x25:
			a = BitGet16();		// ADR
			fprintf(fp, "CALL 0x%04X\n", a);
			break;

		case 0x26:
			// NONE
			fprintf(fp, "RETURN\n");
			break;

		case 0x27:
			a = BitGet8();		// VALUE
			fprintf(fp, "SET_FULL_SCREEN_MODE %d\n", a);
			break;

		case 0x28:
			a = BitGet8();		// EFFECT
			b = BitGet16();		// CYCLES
			c = BitGet8();		// COLORS
			fprintf(fp, "MODIFY_PALETTE_WITH_EFFECT %d %d %d", a, b, c);

			// PALETTE
			for(i=0; i<c; i++)
			{
				d = BitGet8();	// INDEX
				e = BitGet8();	// BLUE
				f = BitGet8();	// GREEN
				g = BitGet8();	// RED

				fprintf(fp, " %d:%d.%d.%d", d, e, f, g);
			}

			fprintf(fp, "\n");
			break;

		case 0x29:
			a = BitGet16();		// ADR
			fprintf(fp, "ENABLE_EXIT_MENU 0x%04X\n", a);
			break;

		case 0x2A:
			// NONE
			fprintf(fp, "DISABLE_EXIT_MENU\n");
			break;

		case 0x2B:
			a = BitGet16();		// ADR
			fprintf(fp, "ENABLE_LOAD_MENU 0x%04X\n", a);
			break;

		case 0x2C:
			// NONE
			fprintf(fp, "DISABLE_LOAD_MENU\n");
			break;

		case 0x2D:
			// NONE
			fprintf(fp, "CLEAR_ON_JUMPS\n");
			break;

		case 0x2E:
			a = BitGet8();		// REG
			b = BitGet16();		// VAL
			c = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_REGISTER_EQUAL %d %d 0x%04X\n", a, b, c);
			break;

		case 0x2F:
			a = BitGet8();		// REG
			b = BitGet16();		// VAL
			c = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_REGISTER_NOT_EQUAL %d %d 0x%04X\n", a, b, c);
			break;

		case 0x30:
			a = BitGet8();		// REG
			b = BitGet16();		// VAL
			c = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_REGISTER_LESS_THAN_OR_EQUAL %d %d 0x%04X\n", a, b, c);
			break;

		case 0x31:
			a = BitGet8();		// REG
			b = BitGet16();		// VAL
			c = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_REGISTER_GREATER_THAN_OR_EQUAL %d %d 0x%04X\n", a, b, c);
			break;

		case 0x32:
			a = BitGet8();		// REG
			fprintf(fp, "READ %d\n", a);
			break;

		case 0x33:
			a = BitGet16();		// VAL
			b = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_LAST_READ_NOT_EQUAL %d 0x%04X\n", a, b);
			break;

		case 0x34:
			a = BitGet8();		// REG
			b = BitGet16();		// VAL
			fprintf(fp, "WRITE %d %d\n", a, b);
			break;

		case 0x35:
			a = BitGet8();		// REG
			fprintf(fp, "INC %d\n", a);
			break;

		case 0x36:
			a = BitGet8();		// REG
			fprintf(fp, "DEC %d\n", a);
			break;

		case 0x37:
			a = BitGet8();		// REG
			b = BitGet16();		// VAL
			fprintf(fp, "ADD %d %d\n", a, b);
			break;

		case 0x38:
			a = BitGet8();		// REG
			b = BitGet16();		// VAL
			fprintf(fp, "OR %d %d\n", a, b);
			break;

		case 0x39:
			a = BitGet8();		// REG
			b = BitGet16();		// VAL
			fprintf(fp, "AND %d %d\n", a, b);
			break;

		case 0x3A:
			a = BitGet16();		// CYCLES
			fprintf(fp, "FADE_OUT_PALETTE %d\n", a);
			break;

		case 0x3B:
			// NONE
			fprintf(fp, "LOAD_STATE\n");
			break;

		case 0x3C:
			// NONE
			fprintf(fp, "SAVE_STATE\n");
			break;

		case 0x3D:
			a = BitGet16();		// LEFT
			b = BitGet16();		// TOP
			c = BitGet16();		// WIDTH
			d = BitGet16();		// HEIGHT
			fprintf(fp, "PAINT_BLACK_RECT %d %d %d %d\n", a, b, c, d);
			break;

		case 0x3E:
			a = BitGet8();		// REG
			b = BitGet16();		// LEFT
			c = BitGet16();		// TOP
			d = BitGet8();		// CHARS
			e = BitGet8();		// CHOICES
			fprintf(fp, "DISPLAY_HOT_ZONE_TEXT %d %d %d %d %d", a, b, c, d, e);

			// TEXT
			for(i=0; i<e; i++)
			{
				s = BitGetStr();

				fprintf(fp, " %s", s);
			}

			fprintf(fp, "\n");
			break;

		case 0x3F:
			a = BitGet8();		// TYPE
			fprintf(fp, "SET_HOT_ZONE_SEPERATOR %d\n", a);
			break;


		case 0x40:
			a = BitGet8();		// ENABLE
			fprintf(fp, "SET_SAVE_MENU_ENABLED %d\n", a);
			break;

		case 0x41:
			a = BitGet8();		// COLORS
			fprintf(fp, "MODIFY_PALETTE %d", a);

			// PALETTE
			for(i=0; i<a; i++)
			{
				b = BitGet8();	// INDEX
				c = BitGet8();	// BLUE
				d = BitGet8();	// GREEN
				e = BitGet8();	// RED

				fprintf(fp, " %d:%d.%d.%d", b, c, d, e);
			}

			fprintf(fp, "\n");
			break;

		case 0x42:
			// NONE
			fprintf(fp, "WAIT_FOR_INPUT_OR_PCM\n");
			break;

		case 0x43:
			a = BitGet16();		// REG
			fprintf(fp, "SET_THREAD_SYNC_FREQ %d\n", a);
			break;

		case 0x44:
			// NONE
			fprintf(fp, "WAIT_FOR_DPAD_INPUT\n");
			break;

		case 0x45:
			a = BitGet8();		// REG
			fprintf(fp, "WRITE_DPAD_DIR %d\n", a);
			break;

		case 0x46:
			// NONE
			fprintf(fp, "WAIT_FOR_DPAD_RELEASE\n");
			break;

		case 0x47:
			a = BitGet8();		// BYTE
			fprintf(fp, "RESET_SYSTEM_STATE %d\n", a);
			break;

		case 0x48:
			a = BitGet16();		// VAL
			b = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_LAST_READ_AND_VALUE_EQUALS_ZERO %d 0x%04X\n", a, b);
			break;

		case 0x49:
			a = BitGet8();		// BUF
			b = BitGet8();		// OFFSET
			c = BitGet8();		// REG
			fprintf(fp, "WRITE_BUFFER_PROP_VALUE %d %d %d\n", a, b, c);
			break;

		case 0x4A:
			s = BitGetStr();	// FILE
			fprintf(fp, "LOAD_WIN %s\n", s);
			break;

		case 0x4B:
			a = BitGet16();		// LEFT
			b = BitGet16();		// TOP
			fprintf(fp, "SET_CARET_POS %d %d\n", a, b);
			break;

		case 0x4C:
			a = BitGet16();		// START_X
			b = BitGet16();		// END_X
			c = BitGet16();		// START_Y
			d = BitGet16();		// END_Y
			fprintf(fp, "MODIFY_SCROLL_PROPERTIES %d %d %d %d\n", a, b, c, d);
			break;

		case 0x4D:
			// NONE
			fprintf(fp, "DISABLE_ANIM_PAUSE\n");
			break;

		case 0x4E:
			// NONE
			fprintf(fp, "ENABLE_ANIM_PAUSE\n");
			break;

		case 0x4F:
			a = BitGet8();		// IMAGE
			fprintf(fp, "WAIT_FOR_BUFFER_WITH_SYNC %d\n", a);
			break;

		case 0x50:
			a = BitGet8();		// RED
			b = BitGet8();		// GREEN
			c = BitGet8();		// BLUE
			d = BitGet16();		// CYCLES
			fprintf(fp, "FADE_IN_RGB %d %d %d %d\n", a, b, c, d);
			break;

		case 0x51:
			a = BitGet8();		// RED
			b = BitGet8();		// GREEN
			c = BitGet8();		// BLUE
			d = BitGet16();		// CYCLES
			fprintf(fp, "FADE_OUT_RGB %d %d %d %d\n", a, b, c, d);
			break;

		case 0x52:
			a = BitGet8();		// VAL
			fprintf(fp, "SET_SHIMMER %d\n", a);
			break;

		case 0x53:
			a = BitGet16();		// ADR
			fprintf(fp, "ENABLE_REPEAT_MENU 0x%04X\n", a);
			break;

		case 0x54:
			// NONE
			fprintf(fp, "DISABLE_REPEAT_MENU\n");
			break;

		case 0x55:
			a = BitGet8();		// TO
			b = BitGet8();		// FROM
			fprintf(fp, "SET_VISIBLE_PALETTE_RANGE %d %d\n", a, b);
			break;

		case 0x56:
			s = BitGetStr();	// REGKEY
			fprintf(fp, "LOAD_ADVANCED_STATE %s\n", s);
			break;

		case 0x57:
			s = BitGetStr();	// REGKEY
			fprintf(fp, "SAVE_ADVANCED_STATE %s\n", s);
			break;

		case 0x58:
			a = BitGet8();		// TO
			b = BitGet8();		// FROM
			fprintf(fp, "COPY %d %d\n", a, b);
			break;

		case 0x59:
			a = BitGet16();		// BUFFER
			b = BitGet16();		// START
			c = BitGet16();		// END
			d = BitGet16();		// DELTA_X
			e = BitGet16();		// DELTA_Y
			f = BitGet16();		// DIVISOR
			fprintf(fp, "SCROLL_MAP %d %d %d %d %d %d\n", a, b, c, d, e, f);
			break;

		case 0x5A:
			a = BitGet8();		// BUFFER
			fprintf(fp, "WAIT_FOR_MAP %d\n", a);
			break;

		case 0x5B:
			a = BitGet8();		// INDEX
			b = BitGet8();		// COUNT
			fprintf(fp, "DEFINE_MAP_PATH %d %d", a, b);

			// ARRAY
			for(i=0; i<b; i++)
			{
				c = BitGet8();
				d = BitGet8();

				fprintf(fp, " %d.%d", c, d);
			}

			fprintf(fp, "\n");
			break;

		case 0x5C:
			a = BitGet8();		// BUF
			fprintf(fp, "FORCE_FINISH_SCROLL %d\n", a);
			break;

		case 0x5D:
			a = BitGet8();		// VOL
			fprintf(fp, "SET_MIDI_VOLUME %d\n", a);
			break;

		case 0x5E:
			a = BitGet16();		// CYCLES
			fprintf(fp, "FADE_OUT_MIDI %d\n", a);
			break;

		case 0x5F:
			// NONE
			fprintf(fp, "NOP\n");
			break;

		case 0x60:
			a = BitGet8();		// VOL
			b = BitGet16();		// CYCLES
			fprintf(fp, "FADE_MIDI %d %d\n", a, b);
			break;

		case 0x61:
			a = BitGet8();		// BUF
			b = BitGet16();		// LEFT
			c = BitGet16();		// TOP
			d = BitGet16();		// WIDTH
			e = BitGet16();		// HEIGHT
			fprintf(fp, "SET_ADVANCED_IMAGE_PROPS %d %d %d %d %d\n", a, b, c, d, e);
			break;

		case 0x62:
			a = BitGet8();		// VAL
			fprintf(fp, "SET_DIALOG_MODE %d\n", a);
			break;

		case 0x63:
			a = BitGet8();		// STREAM
			fprintf(fp, "SET_MAX_ENABLED_PCM_STREAM %d\n", a);
			break;

		case 0x64:
			a = BitGet8();		// COLORS
			fprintf(fp, "PALETTE_SHIFT %d", a);

			// ARRAY
			for(i=0; i<a; i++)
			{
				b = BitGet8();	// INDEX
				c = BitGet8();	// BLUE
				d = BitGet8();	// GREEN
				e = BitGet8();	// RED

				fprintf(fp, " %d:%d.%d.%d", b, c, d, e);
			}

			fprintf(fp, "\n");
			break;

		case 0x65:
			a = BitGet8();		// STREAM
			fprintf(fp, "ENABLE_MAX_CD_AUDIO_STREAM %d\n", a);
			break;

		case 0x66:
			a = BitGet8();		// BUF
			fprintf(fp, "SET_BUFFER_MOUSE_MOVED_VALUE %d\n", a);
			break;

		case 0x67:
			// NONE
			fprintf(fp, "ENABLE_LANGUAGE_MENU\n");
			break;

		case 0x68:
			a = BitGet16();		// LINE
			fprintf(fp, "DISPLAY_TEXT_FROM_FILE %d\n", a);
			break;

		case 0x69:
			a = BitGet8();		// REG
			b = BitGet16();		// LEFT
			c = BitGet16();		// TOP
			d = BitGet8();		// CHOICE
			fprintf(fp, "DISPLAY_HOT_ZONE_TEXT_FROM_FILE %d %d %d %d", a, b, c, d);

			// LINES
			for(i=0; i<d; i++)
			{
				s = BitGetStr();

				fprintf(fp, " %s", s);
			}

			fprintf(fp, "\n");
			break;

		case 0x6A:
			a = BitGet8();		// REG
			b = BitGet16();		// MOD
			fprintf(fp, "WRITE_RANDOM %d %d\n", a, b);
			break;

		case 0x6B:
			a = BitGet8();		// STREAM
			b = BitGet16();		// TENTH_SECONDS
			s = BitGetStr();	// FILE
			fprintf(fp, "LOAD_PCM_WITH_DELAY %d %d %s\n", a, b, s);
			break;

		case 0x6C:
			a = BitGet8();		// INFINITE
			fprintf(fp, "REPEAT_PCM %d\n", a);
			break;

		case 0x6D:
			a = BitGet8();		// BUF
			b = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_BUFFER_FLAGS_NOT_ZERO %d 0x%04X\n", a, b);
			break;

		case 0x6E:
			a = BitGet8();		// REG
			b = BitGet8();		// BUF
			fprintf(fp, "READ_BUFFER_FLAGS %d %d\n", a, b);
			break;

		case 0x6F:
			a = BitGet8();		// REG
			b = BitGet8();		// BUF
			c = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_REGISTER1_EQUALS_REGISTER2 %d %d 0x%04X\n", a, b, c);
			break;

		case 0x70:
			a = BitGet8();		// REG1
			b = BitGet8();		// REG2
			c = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_REGISTER1_NOT_EQUAL_REGISTER2 %d %d 0x%04X\n", a, b, c);
			break;

		case 0x71:
			a = BitGet8();		// REG1
			b = BitGet8();		// REG2
			c = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_REGISTER1_LESS_THAN_OR_EQUAL_REGISTER2 %d %d 0x%04X\n", a, b, c);
			break;

		case 0x72:
			a = BitGet8();		// REG1
			b = BitGet8();		// REG2
			c = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_REGISTER1_GREATER_THAN_OR_EQUAL_REGISTER2 %d %d 0x%04X\n", a, b, c);
			break;

		case 0x73:
			s = BitGetStr();	// TEXT
			fprintf(fp, "DISPLAY_FREE_FLOATING_TEXT %s\n", s);
			break;

		case 0x74:
			a = BitGet8();		// RED
			b = BitGet8();		// GREEN
			c = BitGet8();		// BLUE
			fprintf(fp, "SET_FREE_FLOATING_TEXT_COLOR %d %d %d\n", a, b, c);
			break;

		case 0x75:
			a = BitGet16();		// LEFT
			b = BitGet16();		// TOP
			fprintf(fp, "SET_FREE_FLOATING_TEXT_POSITION %d %d\n", a, b);
			break;

		case 0x76:
			// NONE
			fprintf(fp, "SHOW_NAME_ENTRY_DIALOG\n");
			break;

		case 0x77:
			// NONE
			fprintf(fp, "UNKNOWN_77\n");
			break;

		case 0x78:
			a = BitGet8();		// DISABLE
			fprintf(fp, "SET_PCM_SKIPPING_MODE %d\n", a);
			break;

		case 0x79:
			a = BitGet8();		// REG
			fprintf(fp, "SET_CHARACTER_FACING_FROM_REGISTER %d\n", a);
			break;

		case 0x7A:
			a = BitGet16();		// VAL
			b = BitGet16();		// ADR
			fprintf(fp, "JUMP_IF_LAST_READ_AND_VALUE_NOT_EQUAL_ZERO %d 0x%04X\n", a, b);
			break;

		case 0x7B:
			a = BitGet16();		// LEFT
			b = BitGet16();		// TOP
			s = BitGetStr();	// FILE
			fprintf(fp, "DRAW_BMP %d %d %s\n", a, b, s);
			break;

		default:
			fprintf(fp, "error op=%02X pos=%X \n", op, Bit.pos);
			goto End;
		}
	}

End:
	fclose(fp);
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("win2txt [WIN File]\n");

		exit(0);
	}

	printf("win2txt... %s\n", argv[1]);

	BitCalloc(argv[1]);


	char rname[30];
	strncpy(rname, argv[1], 20);

	char* p = strchr(rname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	p[0] = '.';
	p[1] = 't';
	p[2] = 'x';
	p[3] = 't';
	p[4] = '\0';

	FILE* fp = fopen(rname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open WAV file\n");

		exit(1);
	}

	WinWrite(fp);


	BitFree();

	return 0;
}
