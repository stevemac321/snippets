/*==============================================================================
 Name        : KR.1.9.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
Abstract     : Remove duplicate spaces.
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
	FILE *pf = fopen("test.txt", "r");
	assert(pf);
        int c = 0;
        int last='a';
        while((c = getc(pf)) != EOF) {
                if(c != ' ' || last != ' ')
                        putc(c, stdout);

                last = c;
        }

        fclose(pf);
}
