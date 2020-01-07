/*==============================================================================
 Name        : 1.24.c
 Author      : Stephen MacKenzie
 CopyrighT   : Licensed under GPL version 2 (GPLv2)
 Abstract    : syntax checker, parens, brackets, braces, single-double quotes,
==============================================================================*/
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

struct stacks {
	unsigned int parens;
	unsigned int brackets;
	unsigned int braces;
};
enum { OPAREN = '(',
       CPAREN = ')',
       OBRACKET = '[',
       CBRACKET = ']',
       OBRACE = '{',
       CBRACE = '}',
       QUOTE = '\'',
       DQUOTE = '\"',
       SLASH = '/',
       ESC = '\\',
       AST = '*' };

void push_pop(const int c, struct stacks *ps);
void eat_comment(FILE *pf);
void eat_quote(const int q, FILE *pf);
void report(const struct stacks *ps);

int main()
{
	FILE *pf = fopen("kmod.c", "r");
	assert(pf);

	struct stacks s = {0, 0, 0};
	int c = 0;

	while ((c = getc(pf)) != EOF) {
		if (c == SLASH) {
			if ((c = getc(pf)) == AST)
				eat_comment(pf);
			else
				push_pop(c, &s);
		} else if (c == QUOTE || c == DQUOTE)
			eat_quote(c, pf);
		else
			push_pop(c, &s);
	}
	fclose(pf);
	report(&s);
}
void push_pop(const int c, struct stacks *ps)
{
	assert(ps);
	switch (c) {
	case OPAREN:
		++ps->parens;
		break;
	case CPAREN:
		--ps->parens;
		break;
	case OBRACKET:
		++ps->brackets;
		break;
	case CBRACKET:
		--ps->brackets;
		break;
	case OBRACE:
		++(ps->braces);
		break;
	case CBRACE:
		--(ps->braces);
		break;
	default:
		break;
	}
}
void eat_comment(FILE *pf)
{
	assert(pf);
	int prev = getc(pf);
	int cur = getc(pf);
	while (prev != AST || cur != SLASH) {
		prev = cur;
		cur = getc(pf);
	}
}
void eat_quote(const int q, FILE *pf)
{
	assert(pf);
	int next = 0;
	while ((next = getc(pf)) != q)
		if (next == ESC)
			getc(pf);
}
void report(const struct stacks *ps)
{
	assert(ps);
        puts("----All stacks should be empty (0)--------------------");
	printf("parens:%d brackets:%d braces:%d\n", ps->parens, ps->brackets,
	       ps->braces);
        puts("---- If any non-zero, there is an unbalance error-----");
}
