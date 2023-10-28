#include "work3.c"

int main(int argc, char*argv[])
{
    FILE *file;
    statements stm = validate_params(argc, argv, &file);
    if(stm != correct){
        print_err(stm);
        return 0;
    }
    
    int buf = 2, cnt = 0;

    Employee *employers = (Employee *) malloc(sizeof(Employee) * buf);
    if (employers == NULL)
    {
        fclose(file);
        print_err(memory_error);
        return 0;
    }

    Employee new_emp;
    while (scan_eployee(file, &new_emp) == correct)
    {
        printf("Cотрудник %d %s %s %lf\n", new_emp.id, new_emp.name, new_emp.sur_name, new_emp.money);
        if (buf <= cnt){
            buf *= 2;
            Employee *new_employers = (Employee *) realloc(employers, sizeof(Employee) * buf);

            if (new_employers == NULL)
            {
                free(employers);
                fclose(file);
                print_err(memory_error);
                return 0;
            }
            employers = new_employers;
        }
        employers[cnt] = new_emp;
    }
    

    // Закрываем файл
    fclose(file);

}