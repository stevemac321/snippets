/*==============================================================================
 Name        : KR.1.8.c 
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
Abstract     : Write a program to count blanks, tabs, and newlines.
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

        int blanks=0;
        int tabs = 0;
        int newlines=0;
        int c = 0;

        while((c = getc(pf)) != EOF) {
                if(c == ' ')
                        ++blanks;
                else if(c == '\t')
                        ++tabs;
                else if(c == '\n')
                        ++newlines;
        }

        printf("Blanks: %d, Tabs: %d, Newlines: %d\n", blanks, tabs, newlines);
	fclose(pf);
}
