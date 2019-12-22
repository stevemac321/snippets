#include "../../inc/clib.h"

void pline(const char *line);

int main()
{
        readfile("catechism.txt", pline);
}

void pline(const char *line)
{
        assert(line);
        char * dup = strdup(line);
        puts(dup);
        free(dup);
}
