#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	FILE* fp = fopen("tbl_effpal.bin", "wb");
	float x, y, d, t;

	for(y=0; y<32; y++)
	{
		d = (y+0.99) / 32;
		t = 0;

		for(x=0; x<32; x++)
		{
			t += d;

			printf("%02d ", (int)t);

			uint8_t w = (unsigned char)t;
			fwrite(&w, sizeof(uint8_t), 1, fp);
		}

		printf("\n");
	}

	fclose(fp);

	return 0;
}
