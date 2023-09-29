#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>

const long double MIN_EPSILON_VAL = 0.00001,
                  MAX_EPSILON_VAL = 1.0;

const unsigned long long MAX_LL_VAL = 1e18, MAX_DIG_LL = 18;

// check fractional number to correctivility
enum epsilon_checkmark
{
    epsilon_correct,
    epsilon_not_digit,
    epsilon_overflow,
    epsilon_underflow
};

enum epsilon_checkmark check_epsilon(const long double epsilon)
{
    if (epsilon < MIN_EPSILON_VAL) { return epsilon_underflow; }
    if (epsilon >= MAX_EPSILON_VAL) { return epsilon_overflow; }
    return epsilon_correct;
}


enum epsilon_checkmark is_correct(const char *str_number, long double *resulting_number)
{
    char *endptr;
    *resulting_number = strtold(str_number, &endptr);

    if (*str_number != '\0' && *endptr == '\0') { return check_epsilon(*resulting_number); }

    resulting_number = NULL;
    return epsilon_not_digit;

}

// check flags to correctivitily

enum flag_chemark
{
    flag_non_flag,
    flag_not_servicing,
    flag_correct
};

enum flag_chemark check_flag(int argc, char* argv[], char *flag)
{
    if (argc < 2) {return flag_non_flag;}
    if (strlen(argv[1]) != 2 || (argv[1][0] != '-' && argv[1][0] != '/')) {return flag_non_flag; }
    if (argv[1][1] != 'q' && argv[1][1] != 'm' && argv[1][1] != 't') { return flag_not_servicing; }
    *flag = argv[1][1];
    return flag_correct;
}


// check ll numbers and get
enum digit_status
{
    digit_status_correct,
    digit_status_overflow,
    digit_status_non_digit,
    digit_status_fractional,
    digit_status_under_zero,
    digit_status_zero
};

enum digit_status char_to_ll(char* number, unsigned long long * result)
{
    int number_size = strlen(number);
    if (number_size > MAX_DIG_LL) { return digit_status_overflow; }

    *result = 0;
    if (number[0] == '-') { return digit_status_under_zero; }

    for (int i = 0; i < number_size; i++)
    {
        if (number[i] == '.' || number[i] == ',' )
        {
            return digit_status_fractional;
        }
        if (isalpha(number[i]) || !isalnum(number[i]))
        {
            return digit_status_non_digit;
        }
        *result = (*result * 10) + (unsigned long long) (number[i] - '0');
    }
    if (*result == 0) {return digit_status_zero; }
    return digit_status_correct;
}

enum digit_status get_ll_numbers(int argc, char* argv[], unsigned long long * num1, unsigned long long * num2)
{  
    enum digit_status state1 = char_to_ll(argv[2], num1);
    enum digit_status state2 = char_to_ll(argv[3], num2);
    if (state1 != digit_status_correct) { return state1;}
    if (state2 != digit_status_correct) { return state2;}
    return digit_status_correct;
}

// check input to correctivitily

enum input_checkmark
{
    input_correct,
    input_invalid_epsilon,
    input_invalid_flag,
    input_invalid_cnt_param,
    input_invalid_input,
    invalid_param
};

enum input_checkmark check_input_validate_n_run(int argc, char* argv[], char *flag)
{
    if (argc <= 2) { return input_invalid_input; }
    enum flag_chemark flag_checkpoint = check_flag(argc, argv, flag);
     
    switch (flag_checkpoint)
    {
        case flag_non_flag:
            return input_invalid_cnt_param;
            break;
        case flag_not_servicing:
            return input_invalid_flag;
            break;
        case flag_correct:
            break;
        default:
            return input_invalid_input;
    }
    
    switch (*flag)
    {
    case 'q':
        if (argc != 6)
        {
            printf("For this flag needed more numbers");
            return input_invalid_cnt_param;
        }
        // checker for numbers
        return input_correct;
        break;
    case 'm':
        if (argc != 4)
        {
            printf("For this flag needed more numbers");
            return input_invalid_cnt_param;
        }
        unsigned long long num1, num2;
        enum digit_status nums_state = get_ll_numbers(argc, argv, &num1, &num2);
        if (nums_state != digit_status_correct) // there can check all situations
        {
            printf("Error: Check input paramers, something wrong");
            return input_invalid_input;
        }
        //check_for_separable(num1, num2);
        return input_correct;
        break;
    case 't':
    if (argc != 6)
        {
            printf("For this flag needed more numbers");
            return input_invalid_cnt_param;
        }
        // checker for numbers
        return input_correct;
        break;
        break;
    default:
        break;
    }
    
}