#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MIN_BUF 200

typedef enum
{
    correct,
    runtime_error,
    invalid_input,
    allocate_error,
    invalid_file,
    end_of,
    not_found
} statements;

double sum(unsigned char *nums, int cnt)
{
    double res = 0.0;
    for (int i = 0; i < cnt; i++)
    {
        res += nums[i];
    }
    return res;
}

double sum_d(unsigned char *nums, int cnt)
{
    return (sum(nums, cnt) / cnt);
}