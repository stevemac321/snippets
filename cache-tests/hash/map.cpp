/*==============================================================================
 Name        : map.cpp
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
==============================================================================*/
#include <map>
#include <utility>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void sine_table_test();

int main()
{
	sine_table_test();
}
/*-----------------------------------------------------------------------------
Test functions and data
-----------------------------------------------------------------------------*/

void sine_table_test()
{
        const size_t SINE_ARRAY_SIZE=0xFFFF;
	int compare[SINE_ARRAY_SIZE];

	float sf = 0;
	int res = 0;

	auto m = std::map<int, int>();

	/* this loop taken from Zhu textbook */
	for (size_t i = 0; i < SINE_ARRAY_SIZE; i++) {
		sf = sin(M_PI * i / 180);
		res = (1 + sf) * 2048;
		if (res == 0x1000)
			res = 0xFFF;

		compare[i] = res;
		m.insert(std::make_pair(res, res));
	}

	for (size_t i = 0; i < SINE_ARRAY_SIZE; i++) {
		m.find(compare[i]);
	}

}
