/*==============================================================================
 Name        : test-1.6.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : count stuff
==============================================================================*/
#include <assert.h>
#include <stdio.h>

int main()
{
	const int SPC = 32;
	const int TAB = 9;
	const int NL = 10;

	FILE *pf = fopen("kmod.c", "r");
	assert(pf);

	int newlines = 0;
	int spaces = 0;
	int tabs = 0;
	int digits = 0;

	int c = 0;

	while ((c = getc(pf)) != EOF)
		switch (c) {
		case NL:
			++newlines;
			break;
		case SPC:
			++spaces;
			break;
		case TAB:
			++tabs;
			break;
		default:
			if (c >= '0' && c <= '9')
				++digits;
			break;
		}

	fclose(pf);

	printf("Newlines=%d spaces=%d tabs=%d digits=%d\n", newlines, spaces,
	       tabs, digits);
}
