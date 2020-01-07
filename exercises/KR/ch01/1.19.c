/*==============================================================================
 Name        : 1.19.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : open a file and reverse all lines.
==============================================================================*/
#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char * rev(char * s);

int main()
{
	FILE *pf = fopen("kmod.c", "r");
	assert(pf);
	char *line;
	size_t len = 0;
	ssize_t nread;

	while ((nread = getline(&line, &len, pf)) != -1) {
                printf("%s",rev(line));
	}
	free(line);
	fclose(pf);
}
char * rev(char * s)
{
        assert(s);
        char * r = s;
        while(*r != '\0')
                ++r;
        --r;

        char * l = s;
        while(r > l) {
                char c = *l;
                *l = *r;
                *r = c;
                l++;
                --r;
        }
        return s;
}
