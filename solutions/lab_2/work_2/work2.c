#include <stdio.h>





long double b_pow_d(long double num, unsigned int pow)
{
    if (pow == 1)
    {
        return num;
    }
    if (pow == 0)
    {
        return 1;
    }
    if (pow % 2 == 0)
    {
        long double temp = b_pow_d(num, pow / 2);
        return temp * temp;
    }
    if (pow % 2 == 1)
    {
        long double temp = b_pow_d(num, (pow - 1) / 2);
        return num * temp * temp;
    }
    return 0;
}