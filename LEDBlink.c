#include "precompile.h"
#include "array.h"
#include "functor.h"
#include "specializations.h"
#include "static_tree.h"
#include "heap.h"
#include "algo.h"
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

#ifndef NL
#define NL printf("\n")
#endif
// test data
// array interface tests
static int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3};
static int grid[3][3] = {{44, 77, 11}, {2, 100, 77}, {0, 33, 9}};
static const char *strs[] = {"zero", "one", "two", "three", "four"};
static student recs[] = {{"Joe", 2.0},   {"Mary", 4.0},  {"Larry", 3.5},
			 {"Moe", 3.0},   {"Harry", 3.5}, {"Mary", 2.0},
			 {"Jill", 4.0},  {"Jerry", 2.9}, {"Mike", 3.5},
			 {"Harry", 3.0}, {"Abel", 3.5},  {"Abel", 2.0}};

// test helper
void print_int_array(int *arr, const size_t count);

// test functions
void raw_int_array_test();
void raw_grid_array_test();
void raw_string_array_test();
void raw_record_array_test();
void array_test();
void search_test();
void tree_test();
void heap_test();
void tree_find_delete_test();

void Delay()
{
	int i;
	for (i = 0; i < 1000000; i++)
		;
}

int main()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	printf("hello semihosting %d\n", 11);
	Heap_Init();
	#if 0
	raw_int_array_test();
	raw_grid_array_test();
	raw_string_array_test();
	raw_record_array_test();
	array_test();
	#endif
	search_test();
	tree_test();
	tree_find_delete_test();
	heap_test();
	
	for (;;) {
		printf("hello semihosting %d\n", 11);
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_SET);
		Delay();
		GPIO_WriteBit(GPIOA, GPIO_Pin_5, Bit_RESET);
		Delay();
	}
}
void PrintByte(char c)
{
  USART_SendData(USART2, c);
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
          ; /* do nothing until RESET state*/
}

size_t __write(int handle, const unsigned char* data, size_t byteCount)
{
    size_t nChars = 0;

    // handle == -1 means "flush all streams". Not implemented here.
    if (handle == -1 || byteCount == 0)
        return 0;

    // 1 - stdout; 2 - stderr. 
    if (handle != 1 && handle != 2)
        return -1;

    while (byteCount-- > 0) {
        char ch = (char)(*data);
        PrintByte(ch);
        if (ch == '\n') {
            PrintByte('\r');
        }
       ++data;
       ++nChars;
    }
    return nChars;

} // __write
/*-----------------------------------------------------------------------------
Test functions and data
-----------------------------------------------------------------------------*/
void raw_int_array_test()
{
	printf("\n%s\n", __func__);
	gensort(arr, _countof(arr), sizeof(int), int_less, int_swap);
	print_int_array(arr, _countof(arr));
	visit(arr, _countof(arr), sizeof(int), print_int);
	NL;
	transform(arr, _countof(arr), sizeof(int), arr, double_int);
	print_int_array(arr, _countof(arr));
	modify(arr, _countof(arr), sizeof(int), rand_int);
	print_int_array(arr, _countof(arr));
	gensort(arr, _countof(arr), sizeof(int), int_less, int_swap);
	print_int_array(arr, _countof(arr));
}
void raw_grid_array_test()
{
	printf("\n%s\n", __func__);
	gensort(grid, _gridcountof(grid), sizeof(int), int_less, int_swap);
	print_int_array(grid, _gridcountof(grid));
}
void raw_string_array_test()
{
	printf("\n%s\n", __func__);
	gensort(strs, _countof(strs), sizeof(const char *), str_less, str_swap);
	visit(strs, _countof(strs), sizeof(const char *), print_str);
}
void raw_record_array_test()
{
	printf("\n%s\n", __func__);
	gensort(recs, _countof(recs), sizeof(student), record_gpaless,
		record_swap);
	visit(recs, _countof(recs), sizeof(student), print_student);
}
void array_test()
{
	printf("\n%s\n", __func__);
	array *pai = array_alloc(a, _countof(a), sizeof(int));
	array_modify(pai, rand_int);
	array_print(pai, print_int);
	array_sort(pai, int_less, int_swap);
	array_print(pai, print_int);

	array *pas = array_alloc(strs, _countof(strs), sizeof(const char *));
	array_print(pas, print_str);
	array_sort(pas, int_less, int_swap);
	array_print(pas, print_str);

	array *par = array_alloc(recs, _countof(recs), sizeof(student));
	array_sort(par, record_gpaless, record_swap);
	array_print(par, print_student);

	student s = {"Johnny Yuma", 1.5};
	student *p = array_at(par, 3);
	*p = s;
	array_print(par, print_student);

	array_free(pai);
	array_free(pas);
	array_free(par);

	array *pag = array_alloc(grid, _gridcountof(grid), sizeof(int));
	array_sort(pag, int_less, int_swap);
	array_print(pag, print_int);	Heap_Init();
	raw_int_array_test();
	raw_grid_array_test();
	raw_string_array_test();
	raw_record_array_test();
	array_test();
	search_test();
	tree_test();
	tree_find_delete_test();
	heap_test();
	array_free(pag);

	pas = array_alloc(strs, _countof(strs), sizeof(const char *));
	array_print(pas, print_str);
	array_free(pas);
}

void search_test()
{
	printf("\n%s\n", __func__);
	gensort(arr, _countof(arr), sizeof(int), int_less, int_swap);
	int x = 888;
	assert(NULL == gensearch(arr, &x, 0, _countof(arr)-1, sizeof(int), 
								int_cmp));

	for(int i=0; i < _countof(arr); i++) {
		int val = arr[i];
		int * p = gensearch(arr, &val, 0, _countof(arr)-1, sizeof(int), 
								      int_cmp);
		assert(p && *p == val);
		printf("%d ", *p); 
	}
	NL;
}

void tree_test()
{
	printf("\n%s\n", __func__);
	int t2[30];
	modify(t2, _countof(t2), sizeof(int), rand_int);
	treeptr pt = tree_alloc(int_cmp, true);
	if(pt) {
		for(size_t i=0; i < _countof(t2); i++)
			tree_add(pt, &t2[i]);

		tree_visit(pt, in, print_int);
		tree_free(pt);
		NL;
	}
	
	
	modify(t2, _countof(t2), sizeof(int), rand_int);
	pt = tree_alloc(int_cmp, false);
	assert(pt);
	for(size_t i=0; i < _countof(t2); i++)
		tree_add(pt, &t2[i]);

	tree_visit(pt, in, print_int);
	tree_free(pt);
	NL;
}
void tree_find_delete_test()
{
	printf("\n%s\n", __func__);
	int easy[] = {6, 3, 44, 1, 30};
	treeptr pt = tree_alloc(int_cmp, false);
	assert(pt);
	for(size_t i = 0; i < _countof(easy); i++)
		tree_add(pt, &easy[i]);
	
	tree_visit(pt, in, print_int);
	int val = 44;
	int* f = tree_find(pt, &val);
	assert(f);
	printf("should have fount it: %d\n", *f);
	tree_delete_node(pt, f);
	tree_visit(pt, in, print_int);
	
	f = tree_find(pt, &val);
	assert(f == NULL);
	tree_visit(pt, in, print_int);
	tree_free(pt);
}
void heap_test()
{
	printf("\n%s\n", __func__);
	const int alloc_count = 10;
	int* dyna = Heap_Malloc(sizeof(*dyna) * alloc_count);
	assert(dyna);
	modify(dyna, alloc_count, sizeof(int), rand_int);
	print_int_array(dyna, alloc_count);
	Heap_Free(dyna);
}

// often used print integer array
void print_int_array(int *arr, const size_t count)
{
	for (int *p = arr; p < arr + count; p++) 
		printf("%d ", *(int *)p);

	printf("\n");
}
#pragma GCC diagnostic pop