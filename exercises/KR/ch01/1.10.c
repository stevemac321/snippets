/*==============================================================================
 Name        : KR.1.10.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
Abstract     : Replace \t \b and \ with visible marker
==============================================================================*/
#define _GNU_SOURCE
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
	while ((c = getc(pf)) != EOF) {
                if(c == '\t')
                        printf("\\t");
                else if(c == '\\')
                        printf("\\\\");
                else
                        putc(c, stdout);
	}

	fclose(pf);
}
