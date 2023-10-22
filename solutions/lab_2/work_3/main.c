#include "work3.c"


void print_cell(Cell *c)
{
    printf("\n");
    printf("For file :  %s \n", c->path);
    if (c->stm == all_nums){
        printf("All will be substing");
    }
    if (c->stm == correct)
    {
        printf("Count is : %d\n", c->cnt);
        for (int i = 0; i < c->cnt ; i++)
        {
            printf("At string %d — at position %d\n", c->string_ns[i], c->char_ns[i]);
        }
    }
    printf("\n");
}


int main()
{
    Cell **cells;
    int n = 2;
    statements stm = find_all_patterns(&cells, "a", n, "in.txt", "in2.txt");
    if (stm == correct)
    {
        for (int i = 0; i < n; i++)
        {
            print_cell(cells[i]);
        }
    }
    else{
        printf("Error occured");
    }
    free_Cells(cells, n);
}