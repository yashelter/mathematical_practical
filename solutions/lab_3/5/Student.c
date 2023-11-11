/*
Через аргументы
командной строки программе на вход подаётся путь к файлу, содержащему записи о
студентах. При старте программа считывает поданный файл в динамический массив
структур типа Student. В программе должен быть реализован поиск всех студентов по
*/

#include "../4/String.c"

typedef struct
{
    unsigned int id;

    String *name;
    String *s_name;
    String *group;

    unsigned char *mas;
    int m_size;
} Student;

Student *create_student(int id, String *name, String *s_name, String *group, unsigned char *mas, int l,  statements *stm)
{
    Student *st = (Student *)malloc(sizeof(Student));
    if (st == NULL)
    {
        *stm = allocate_error;
        return NULL;
    }
    st->id = id;
    st->name = name;
    st->group = group;
    st->mas = mas;
    st->m_size = l;
    return st;
}

int compare_by_id(const void *a, const void *b)
{
    const Student *_a = (const Student *)a;
    const Student *_b = (const Student *)b;

    return  _a->id - _b->id;
}

int compare_by_name(const void *a, const void *b)
{
    const Student *_a = (const Student *)a;
    const Student *_b = (const Student *)b;

    return  compare_strings(_a->name, _b->name);
}

int compare_by_sname(const void *a, const void *b)
{
    const Student *_a = (const Student *)a;
    const Student *_b = (const Student *)b;

    return  compare_strings(_a->s_name, _b->s_name);
}

int compare_by_group(const void *a, const void *b)
{
    const Student *_a = (const Student *)a;
    const Student *_b = (const Student *)b;

    return  compare_strings(_a->group, _b->group);
}

Student *find_student_by_id(Student **stds)
{

}


void sort_students(Student **stds, int size, int (*func)(const void *, const void *))
{   
    qsort(stds, size, sizeof(Student *), func);
}

double calulate_mid(Student **stds, int size){
    double res = 0;
    for (int i = 0; i < size; i++)
    {
        res = res + (sum_d((stds[i])->mas, (stds[i])->m_size));
    }
    return res;
}