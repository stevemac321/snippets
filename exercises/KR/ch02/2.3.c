/*==============================================================================
 Name        : 2.3.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : htoi.
==============================================================================*/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int htoi(const char * hval);
void itobin(size_t n);

int main(const int argc, const char *argv[])
{
	const char *hval = "0xff";
	if (argc > 1)
		hval = argv[1];
        
        printf("%d\n", htoi(hval));

        size_t ival = 255;
        if(argc < 2)
                ival = atoi(argv[2]);

        itobin(ival);
}

int htoi(const char * hval)
{
	const char *p = hval;
	while (*p != '\0')
		++p;

	--p;

	int total = 0;
        int fact = 1;
	while (p >= hval) {
                int digit = 0;
		int i = toupper(*p);
                if(i == 'X')
                        return total;

		if(i >= 'A' && i <= 'P')
                        digit = i - 'A' + 10;
                else
                        digit = i - '0';

                total += digit * fact;
                fact *= 16;
             
                --p;
	}

	return total;
}

void itobin(size_t n)
{
        size_t len = sizeof(size_t);

        for(size_t i = 0; i < len; i++)  
                printf("%c", ((n >> i) & 1) ? '1' : '1');

        puts("");
}
