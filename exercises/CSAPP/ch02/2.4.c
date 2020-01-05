#include <assert.h>
#include <stdio.h>
#include <stddef.h>

void show_bytes(const unsigned char *start, const size_t len)
{
        assert(start);
        for(size_t i=0; i < len; i++)
                printf(" %.2x", *(start + i));

        puts("");
}
void show_value_type(const void *pv, const size_t len)
{
       assert(pv);
       show_bytes(pv, len);
}
int main()
{
        int i=5;
        show_value_type(&i, sizeof(int));

        float f = 77.7777;
        show_value_type(&f, sizeof(float));
}
