
/*==============================================================================
 Name        : ch01.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : Compare SM solutions to K&R and the C Answer Book

 See README at the root of this project.  Also krtest comment header.
==============================================================================*/
#include <cstdio>
#include <cassert>
#include <tuple>
#include <iostream>
#include <stdbool.h>

/* C Answer Book Version (a.k.a. "CAB"): blank, tab, and newline count */
std::tuple<int,int,int>  Base_1_8()
{
	int c = 0;
	int nb = 0;
	int nt = 0;
	int nl = 0;

	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

	while ((c = getc(pf)) != EOF) {
		if (c == ' ')
			++nb;
		if (c == '\t')
			++nt;
		if (c == '\n')
			++nl;
	}

	fclose(pf);

        std::cout << nb << " " << nt << " " << nl << "\n";
        return std::make_tuple(nb,nt,nl);
}
/* SM version (note not very different from CAB. */
std::tuple<int,int,int> Test_1_8()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

	int blanks = 0;
	int tabs = 0;
	int newlines = 0;
	int c = 0;

	while ((c = getc(pf)) != EOF) {
		if (c == ' ')
			++blanks;
		else if (c == '\t')
			++tabs;
		else if (c == '\n')
			++newlines;
	}
	fclose(pf);
        std::cout << blanks << " " << tabs << " " << newlines << "\n";
        return std::make_tuple(blanks, tabs, newlines);

}
/*KR version of word count: 1.5.4 pg. 20 2nd ed.*/
std::tuple<int,int,int>  Base_1_11()
{
        const unsigned int IN = 1;
        const unsigned int OUT = 0;

	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

	int c=0;
        int nl = 0;
        int nc = 0;
        int nw = 0;
        int state = OUT;

        while((c = getc(pf)) != EOF) {
                ++nc;
                if(c == '\n')
                        ++nl;

                if(c == ' ' || c == '\n' || c == '\t')
                        state = OUT;
                else if(state == OUT) {
                        state = IN;
                        ++nw;
                }

        }
        
        fclose(pf);
        return std::make_tuple(nl, nw, nc);
}
/*SM version of word count*/
std::tuple<int,int,int> Test_1_11()
{
	FILE *pf = fopen("./parsefiles/kmod.c", "r");
	assert(pf);

	int c = 0;
	int lines = 0;
	int words = 0;
	int chars = 0;
	bool in_word = false;

	while ((c = getc(pf)) != EOF) {
                ++chars;
                if(c == '\n')
                        ++lines;
                
                if(c == ' ' || c == '\n' || c == '\t')
                        in_word = false;
                else if(in_word == false) {
                        in_word = true;
                        ++words;
                }
	}

	fclose(pf);
        return std::make_tuple(lines, words, chars);
}
