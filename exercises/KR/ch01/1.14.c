/*==============================================================================
 Name        : 1.5.6.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : count stuff
==============================================================================*/
#include <assert.h>
#include <stdio.h>
#include <string.h>

void print_table(const int *table, const int SZ);

int main()
{
	FILE *pf = fopen("kmod.c", "r");
	assert(pf);

	const unsigned int SZ = 128;
	int table[SZ];

	for (int i = 0; i < SZ; i++)
		table[i] = 0;

	int c = 0;

	while ((c = getc(pf)) != EOF)
		table[c]++;

	fclose(pf);
	print_table(table, SZ);
}
void print_table(const int *table, const int SZ)
{
	const char *fmt = "%s occured %d times\n";
	char buf[8] = {'\0'};

	const int SPC = 32;
	const int TAB = 9;
	const int NL = 10;
	int digits = 0;

	for (int i = 0; i < SZ; i++)
		if (table[i] > 0) {
			switch (i) {
			case NL:
				strcpy(buf, "NL");
				break;
			case SPC:
				strcpy(buf, "SPC");
				break;
			case TAB:
				strcpy(buf, "TAB");
				break;
			default:
				if (i >= '0' && i <= '9')
					++digits;
			}

			if (i == NL || i == SPC || i == TAB)
				printf(fmt, buf, table[i]);
			else
				printf("%c occured %d times\n", i, table[i]);
		}
	puts("----------------------------------------------------------------------");
	printf("Newlines=%d spaces=%d tabs=%d digits=%d\n", table[NL],
	       table[SPC], table[TAB], digits);
}
