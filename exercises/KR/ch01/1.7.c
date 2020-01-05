/*==============================================================================
 Name        : 1.7.c
 Author      : Stephen MacKenzie
 Copyright   : Licensed under GPL version 2 (GPLv2)
 Abstract    : power function, test vs. math.h  (link with -lm)
==============================================================================*/
#include <stdio.h>
#include <math.h>

double power(const double base, const double nth);
int main()
{
        for(double b=1; b < 10; b++)
                for(double n = 1; n < 5; n++)
                        printf("%.2f\t\t  %.2f\n", pow(b,n), power(b,n));
}
double power(const double base, const double nth)
{
        double p=1;
        for(int i=1; i <= nth; i++)
                p = p * base;

        return p;
}
