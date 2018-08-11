/*==============================================================================
 Name        : myunordered.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#include "unordered_map.hpp"

template <typename T> struct same_hash {
	size_t operator()(const T &x) const
	{
		return 5;
	}
};

int main()
{
	const size_t ARRAY_SIZE = 0xFFFF;

#ifdef STRESS
	stevemac::unordered_map<int, int, -7777, same_hash<int>>
		m(ARRAY_SIZE);
#else
	stevemac::unordered_map<int, int, -7777> m(ARRAY_SIZE);
#endif
	for (size_t i = 0; i < ARRAY_SIZE; i++) 
		m.insert(std::make_pair(i, i));

	for (size_t i = 0; i < ARRAY_SIZE; i++) 
		m.find(i);

        m.stats();
}

