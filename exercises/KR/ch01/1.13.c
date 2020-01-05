/*==============================================================================
 Name        : 1.13.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : histogram of word lengths
==============================================================================*/
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
        const int MAXLEN = 64;

	FILE *pf = fopen("kmod.c", "r");
	assert(pf);

        bool inword = false;
        char buf[MAXLEN];
        char *p = buf;

        while((*p = getc(pf)) != EOF) {
                if(*p >= 'A' && *p <= 'z') {
                        inword = true;
                        ++p;
                }else{
                        if(inword) {
                                *p = '\0';
                                printf("%s : %lu\n", buf, strlen(buf));
                                p = buf;
                        }
                        inword = false;
                }
        }
	fclose(pf);
}
