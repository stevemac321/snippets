/*==============================================================================
 Name        : myunordered.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#include <algorithm>
#include <numeric>
#include "unordered_map.hpp"

template <typename T> struct same_hash {
	size_t operator()(const T &x) const
	{
		return 5;
	}
};

int main()
{
	const size_t ARRAY_SIZE = 97;

	stevemac::unordered_map<int, int, -7777> m(ARRAY_SIZE);

	for (size_t i = 0; i < ARRAY_SIZE; i += 2)
		m.insert(std::make_pair(i, i));

	for (size_t i = 0; i < ARRAY_SIZE; i += 2)
		assert(m.find(i)->first == i);

	assert(m.end() == m.find(87));

	size_t accum = 0;
	for (auto p : m)
		accum += p.second;

	size_t accum_raw = 0;
	for (size_t i = 0; i < ARRAY_SIZE; i += 2)
		accum_raw += i;

	assert(accum == accum_raw);

	m.stats();
}

