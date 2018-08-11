/*==============================================================================
 Name        : vector.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void sine_table_test();

int main()
{
	sine_table_test();
}

void sine_table_test()
{
	const size_t SINE_ARRAY_SIZE = 0xFFFF;
	int compare[SINE_ARRAY_SIZE];

	float sf = 0;
	int res = 0;

	auto v = std::vector<std::pair<int, int>>(SINE_ARRAY_SIZE);

	/* this loop taken from Zhu textbook */
	for (size_t i = 0; i < SINE_ARRAY_SIZE; i++) {
		sf = sin(M_PI * i / 180);
		res = (1 + sf) * 2048;
		if (res == 0x1000)
			res = 0xFFF;

		compare[i] = res;
		v.push_back(std::make_pair(res, res));
	}

	std::sort(v.begin(), v.end(),
		  [](const std::pair<int, int> &p1,
		     const std::pair<int, int> &p2) {
			  return p1.first < p2.first;
		  });

	for (size_t i = 0; i < SINE_ARRAY_SIZE; i++)
		std::binary_search(v.begin(), v.end(),
				   std::make_pair(compare[i], 0),
				   [](const std::pair<int, int> &p1,
				      const std::pair<int, int> &p2) {
					   return p1.first < p2.first;
				   });
}
