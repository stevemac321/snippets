#include <stdio.h>
#include <ctype.h>

void changestr(char ** p)
{
        char * i = *p;
        while(isspace(*i))
                ++i;

        *p = i;
}
int main()
{
        char * p = " hello";
        changestr(&p);
        puts(p);
}
