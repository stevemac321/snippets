/*==============================================================================
 Name        : unordered.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#include <unordered_map>
#include <utility>
#include <cstdio>

template <typename T> struct same_hash {
	size_t operator()(const T &x) const
	{
		return 5;
	}
};

void test();

int main()
{
	test();
}

void test()
{
        const size_t ARRAY_SIZE=0xFFFF;

#ifdef STRESS
	auto m = std::unordered_map<int, int, same_hash<int>>();
#else
	auto m = std::unordered_map<int, int>();
#endif

	/* this loop taken from Zhu textbook */
	for (size_t i = 0; i < ARRAY_SIZE; i++) 
		m.insert(std::make_pair(i, i));
	

	for (size_t i = 0; i < ARRAY_SIZE; i++) 
		m.find(i);
        
        printf("buckets: %zu\n", m.bucket_count());
        printf("load factor: %f\n", m.load_factor());
}

