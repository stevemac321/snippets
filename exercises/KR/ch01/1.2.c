#include <stdio.h>

int main()
{
        const float LOWER = 0;
	const float UPPER = 300.00;
	const float STEP = 20.00;

	for (float fahr = LOWER; fahr <= UPPER; fahr += STEP)
		printf("%3.0f %6.1f\n", fahr, ((5.0 / 9.0) * (fahr - 32.0)));
}
