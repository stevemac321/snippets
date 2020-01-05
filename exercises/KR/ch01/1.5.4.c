/*==============================================================================
 Name        : 1.5.4.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : count lines, words, characters. (behave line wc -l)
==============================================================================*/
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
	FILE *pf = fopen("test.txt", "r");
	assert(pf);

	int c = 0;
	int lines = 0;
	int words = 0;
	int chars = 0;
	bool INWORD = false;

	while ((c = getc(pf)) != EOF) {
		switch (c) {
		case '\n':
			++lines;
		case ' ':
		case '\t': /*first two cases fall thru to here*/

			if (INWORD == true)
				++words;

			INWORD = false;
			++chars;
			break;

		default:
			INWORD = true;
			++chars;
			break;
		}
	}

	fclose(pf);
	printf("lines: %d words: %d  chars: %d\n", lines, words, chars);
}
