/*==============================================================================
 Name        : fastkey.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#include <cassert>
#include "fastkey.hpp"

template <typename T> struct same_hash {
	size_t operator()(const T &x) const
	{
		return 5;
	}
};

int main()
{
	const int ARRAY_SIZE = 0xFFFF;
#ifdef STRESS
        stevemac::fastkey<int, int, -7777, same_hash<int>> m(ARRAY_SIZE);
#else
	stevemac::fastkey<int, int, -7777> m(ARRAY_SIZE);
#endif
	for (int i = 0; i < ARRAY_SIZE; i++)
		assert(m.insert(i, i));

	for (int i = 0; i < ARRAY_SIZE; i++) {
		assert(m.find(i));
	}
}

