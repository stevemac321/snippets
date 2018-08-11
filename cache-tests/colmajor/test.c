#include <stdint.h>
#include <stdio.h>

uint64_t grid[8][8] = {{0, 1, 2, 3, 4, 5, 6, 7}, {0, 1, 2, 3, 4, 5, 6, 7},
		       {0, 1, 2, 3, 4, 5, 6, 7}, {0, 1, 2, 3, 4, 5, 6, 7},
		       {0, 1, 2, 3, 4, 5, 6, 7}, {0, 1, 2, 3, 4, 5, 6, 7},
		       {0, 1, 2, 3, 4, 5, 6, 7}, {0, 1, 2, 3, 4, 5, 6, 7}};

int main()
{
	int accum = 0;
#ifdef COLMAJOR
	for (int col = 0; col < 8; col++)
		for (int row = 0; row < 8; row++)
			accum += grid[row][col];
#else
	for (int row = 0; row < 8; row++)
		for (int col = 0; col < 8; col++)
			accum += grid[row][col];

#endif
	return accum - accum;
}

