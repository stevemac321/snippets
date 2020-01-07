/*==============================================================================
 Name        : 1.18.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : remove trailing newline and whitespace
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
	FILE *pf = fopen("kmod.c", "r");
	assert(pf);
	char *line;
	size_t len = 0;
	ssize_t nread;

	while ((nread = getline(&line, &len, pf)) != -1) {
                char *p = line + strlen(line) -1;
                while((*p == '\n' || *p == '\t' || *p == ' ') && p >= line)
                        *p-- = '\0';

                printf("%s", line);
	}
	free(line);
	fclose(pf);
}
