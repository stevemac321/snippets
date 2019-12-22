#pragma once

void readfile(const char *fname, void (*func)(const char *, char **),
	      char **save);
void rstrip(char *line);
void lstrip(char **pline);
void trim(char **pline);
void paren_strip(char **pline);
void chop_period(char *line);
void rem_newline(char *);
void tokenize_verse(const char *, char bufbook[32], char bufchap[32],
		    char bufverse[32]);
