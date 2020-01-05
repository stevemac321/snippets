/*==============================================================================
 Name        : KR.1.12.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
Abstract     : Print a programs input one word at a time.
==============================================================================*/
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
	FILE *pf = fopen("../template.c", "r");
	assert(pf);
	int c = 0;
	bool inword = false;

	while ((c = getc(pf)) != EOF) {
		if (c != ' ' && c != '\t' && c != '\n') {
			inword = true;
			putc(c, stdout);
		} else if (inword == true) {
			putc('\n', stdout);
			inword = false;
		}
	}
	fclose(pf);
}
