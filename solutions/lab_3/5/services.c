#include "Student.c"

Student **update_data(FILE *file, int *n)
{
    statements stm;
    size_t buf = 32, realn = 0;

    Student **mas = (Student **)malloc(sizeof(Student *) * buf);
    if (mas == NULL)
    {
        return NULL;
    }
    Student *curr;
    while ((curr = read_student(file, &stm)) != NULL)
    {
        fprintf(stdout, "Name is %s, Surname is %s, %s, %d\n", curr->name->value, curr->s_name->value, curr->group->value, curr->mas[4]);
        if (buf > realn + 1)
        {
            buf *= 2;
            Student **temp = (Student **)realloc(mas, sizeof(Student *) * buf);
            if (temp == NULL)
            {
                free(mas);
                return NULL;
            }
            mas = temp;
        }
        mas[realn++] = curr;
    }
    Student **temp = (Student **)realloc(mas, sizeof(Student *) * realn);
    if (temp == NULL)
    {
        free(mas);
        return NULL;
    }
    mas = temp;

    *n = realn;
    return mas;
}

void skippy_empty()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void print_usage()
{
    printf(">>> <s> Sort students by ..\n");
    printf(">>> <f> Find students by ..\n");
    printf(">>> <t> Print good students\n");
    printf(">>> <q> Exit from menu\n\n\n");
}

statements run(char *path)
{
    FILE *data = NULL;
    data = fopen(path, "r");
    if (data == NULL)
    {
        return invalid_file;
    }
    int n;
    Student **students = update_data(data, &n);
    fclose(data);

    if (students == NULL)
    {
        return runtime_error;
    }

    print_usage();

    while (true)
    {
        printf("-: ");
        char input;
        scanf("%c", &input);

        skippy_empty();
        if (input == 's')
        {
            printf("Select sort parameter\n");
            printf(">>> <i> by id\n");
            printf(">>> <g> by group\n");
            printf(">>> <n> by name\n");
            printf(">>> <s> by surname\n\n");
            printf("-: ");
            scanf("%c", &input);
            CompareFunction ptr; 
            if (input == 'i')
            {
                ptr = compare_by_id;
            }
            if (input == 'g')
            {
                ptr = compare_by_group;
            }
             if (input == 'n')
            {
                ptr = compare_by_name;
            }
             if (input == 's')
            {
                ptr = compare_by_sname;
            }
            sort_students(students, n, ptr);
        }
        if (input == 't')
        {
            printf("Enter out file path\n");
            printf("-: ");

            char path[1024] = "";

            scanf("%s", path);
            FILE * out = NULL;

            out = fopen(path, "w");

            if (out == NULL)
            {
                printf("Invalid file\n");
                continue;
            }
            int new_cnt = n;
            Student ** good = get_better_mid_students(students, &new_cnt);
            if (good == NULL)
            {
                fclose(out);
                printf("Something wrong of Not founded\n");
                continue;
            }
            printf("%d\n", good[0]->id);
            for (int i = 0; i < new_cnt; i++)
            {
                print_student(good[i], out);
            }

            fclose(out);
            free(good);
        }

        if (input == 'q')
        {
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        delete_student(students[i]);
    }
    free(students);
    
}