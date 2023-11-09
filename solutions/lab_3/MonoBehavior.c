#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
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
} statements;