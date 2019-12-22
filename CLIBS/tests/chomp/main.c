#include "../../inc/clib.h"

int main()
{
	{
		char a[] = "hello ";
		size_t n = strlen(a);
		rstrip(a);
		printf("%s old len: %lu new len: %lu\n", a, n, strlen(a));
	}
	{
		char *a = " hello";
		size_t n = strlen(a);
		lstrip(&a);
		printf("%s old len: %lu new len: %lu\n", a, n, strlen(a));
	}
	{
		char a[] = " hello ";
		size_t n = strlen(a);
		char *p = a;
		trim(&p);
		printf("%s old len: %lu new len: %lu\n", p, n, strlen(p));
	}
}
