/*==============================================================================
 Name        : 1.23.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : remove comments, C-style and now cpp style
==============================================================================*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int SLASH = '/';
const int AST = '*';
const int NL = '\n';

void slash_found(const int c, FILE * pf);
void in_double_slash(FILE * pf);
void in_asterisk(FILE * pf);

int main()
{
	FILE *pf = fopen("kmod.c", "r");
	assert(pf);

	int c = 0;

	while ((c = getc(pf)) != EOF) {
		if (c == SLASH) 
                        slash_found(c, pf);                        
		else
			putc(c, stdout);
	}
	fclose(pf);
}
void slash_found(const int c, FILE *pf)
{
        int after  = getc(pf);
        if(after == SLASH)
                in_double_slash(pf);
        else if(after == AST)
                in_asterisk(pf);
        else {
                putc(c, stdout);
                putc(after, stdout);
        }
}
void in_double_slash(FILE * pf)
{
        int c = getc(pf);
        while(c != EOF && c != NL)
                c = getc(pf);
}
void in_asterisk(FILE * pf)
{
        int next = getc(pf);
        while(next != EOF) {
                next = getc(pf);
                if(next == AST) {
                        next = getc(pf);
                        if(next == SLASH) {
                                next = getc(pf);
                                if(next == NL)
                                        putc(NL, stdout);

                                break;
                        }
                }
        }
}
