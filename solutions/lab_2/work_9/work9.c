#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> // для length
#include <time.h>
#include <ctype.h>

#define ll long long 

typedef enum
{
    memory_error,
    correct,
    runtime_error,
} statements;


#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

bool has_finite_representation(double num, int base) {
    ll denominator = 1, it = 0;
    while (num != (int)num) {
        if (num > 1e9+7 || denominator >= 1e18 || it > 1e8) return false;
        num *= base;
        denominator *= base;
        it++;
    }

    for (int i = 2; i <= denominator && i <= base; i++) {
        while (base % i == 0) 
        {
            base /= i;
            while (denominator % i == 0) denominator /= i;
        }
    }

    return denominator == 1;
}

void check_representation(int base, int num, ...) {
    va_list numbers;
    va_start(numbers, num);

    for (int i = 0; i < num; i++) {
        double num = va_arg(numbers, double);
        printf("Representation %.5lf in base %d: %s\n", num, base, has_finite_representation(num, base) ? "Finite" : "Infinite");
    }

    va_end(numbers);
}