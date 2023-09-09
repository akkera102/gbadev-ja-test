#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

//---------------------------------------------------------------------------
uint32_t tbl[16+16+16+4][128];
uint32_t i = 0;


//---------------------------------------------------------------------------
void spr8x8(int x, int y)
{
	// 8x8
	uint32_t ix, iy;

	for(iy=y; iy<y+8; iy++)
	{
		for(ix=x; ix<x+2; ix++)
		{
			tbl[ix][iy] = i;
			i += 2;
		}
	}
}
//---------------------------------------------------------------------------
void spr64x64(int x, int y)
{
	// 64x64
	uint32_t ix, iy;

	for(iy=y; iy<y+64; iy+=8)
	{
		for(ix=x; ix<x+16; ix+=2)
		{
			spr8x8(ix, iy);
		}
	}
}
//---------------------------------------------------------------------------
void spr16x32(int x, int y)
{
	// 16x32
	uint32_t ix, iy;

	for(iy=y; iy<y+32; iy+=8)
	{
		for(ix=x; ix<x+4; ix+=2)
		{
			spr8x8(ix, iy);
		}
	}
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	spr64x64( 0,  0);
	spr64x64(16,  0);
	spr64x64(32,  0);
	spr16x32(48,  0);
	spr16x32(48, 32);


	spr64x64( 0, 64);
	spr64x64(16, 64);
	spr64x64(32, 64);
	spr16x32(48, 64);
	spr16x32(48, 96);


	uint32_t x, y;

/*
	for(y=0; y<128; y++)
	{
		for(x=0; x<16+16+16+4; x++)
		{
			printf("0x%x, ", tbl[x][y]);
		}
		printf("\n");
	}
*/

	FILE* fp = fopen("spr_table.bin", "wb");

	for(y=0; y<128; y++)
	{
		for(x=0; x<16+16+16+4; x++)
		{
			fwrite(&tbl[x][y], sizeof(uint16_t), 1, fp);
		}
	}

	fclose(fp);


	return 0;
}
