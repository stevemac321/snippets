#include <precompile.h>
#include <clib.h>

void readfile(const char *fname, void (*func)(const char *, char **),
	      char **save)
{
	assert(fname && func && save && *save);
	FILE *pf = fopen(fname, "r");
	assert(pf);
	char *line;
	size_t len = 0;
	ssize_t nread;

	while ((nread = getline(&line, &len, pf)) != -1) {
		func(line, save);
	}
	free(line);
	fclose(pf);
}
/**/
void rstrip(char *line)
{
	assert(line);
	char *p = line;
	while (*p != '\0')
		++p;

	while (p > line && isspace(*(p - 1)))
		--p;

	*p = '\0';
}
void lstrip(char **pline)
{
	assert(pline && *pline);
	char *p = *pline;
	while (*p != '\0' && isspace(*p))
		++p;

	*pline = p;
}
void trim(char **pline)
{
	assert(pline && *pline);
	rstrip(*pline);
	lstrip(pline);
}
void paren_strip(char **pline)
{
	assert(pline && *pline);
	trim(pline);
	char *p = *pline + strlen(*pline) - 1;
	assert(*p == ')');
	*p = '\0';
	p = *pline;
	assert(*p == '(');
	++p;
	*pline = p;
}
void chop_period(char *line)
{
	assert(line);
	char *p = line;
	while (*p != '\0')
		++p;
	--p;

	if (*p == '.')
		*p = '\0';
}
void rem_newline(char *line)
{
	assert(line);
	char *p = line + strlen(line) - 1;
	while (!isalnum(*p) && p > line) {
		*p = '\0';
		--p;
	}
}

void tokenize_verse(const char *verse, char *bufbook, char *bufchap,
		    char *bufverse)
{
	assert(verse);
	char *dup = strdup(verse);

	char *p = dup;
	while (*p != ':' && *p != '\0')
		++p;

	if (*p != ':')
		strcpy(bufverse, "");
	else
		strcpy(bufverse, p + 1);

	*p = '\0';
	--p;

	assert(isdigit(*p));

	while (isdigit(*(p - 1)))
		--p;


	if (!isspace(*(p - 1)) && *(p - 1) != '.')
		puts(verse);

	assert(isspace(*(p - 1)) || *(p - 1) == '.');

	strcpy(bufchap, p);
	*(p - 1) = '\0';

	strcpy(bufbook, dup);
	free(dup);
}
