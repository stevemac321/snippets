/*==============================================================================
 Name        : 1.5.3.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : count lines
==============================================================================*/
#include <assert.h>
#include <stdio.h>

int main()
{
	FILE *pf = fopen("test.txt", "r");
	assert(pf);

	int c = 0;
	int count = 0;

	while ((c = getc(pf)) != EOF) {
		if (c == '\n')
			++count;
	}

	fclose(pf);
        printf("lines: %d\n", count);
}
