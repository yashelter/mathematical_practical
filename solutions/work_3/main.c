#include "work3.h"

int main(int argc, char* argv[])
{
    char flag;
    enum input_checkmark input_state = check_input_validate_n_run(argc, argv, &flag);
    printf("Debud: argc %d\n", argc);

    switch (input_state)
    {
    case input_correct:
        printf("All good\n");
        break;
    case input_invalid_input:
        printf("Error: Invalid Input, please check it\n");
        break;
    case input_invalid_flag:
        printf("Error: Invalid <Flag>, please check it\n");
        break;
    case input_invalid_cnt_param:
        printf("Error: Invalid <count> of params for your flag, please check it\n");
        break;
    case invalid_param:
        printf("Error: One of params not in limits, please check it\n");
        break;
    default:
        break;
    }
 printf("done\n");

}