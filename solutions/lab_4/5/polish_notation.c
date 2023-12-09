#include "stack.c"

bool ending_symb(char s)
{
    return (s == '+' || s == '-' || s == '%' || s == '/' || s == '^' || s == '*' || s == '(' || s == ')');
}

char *scan_lexema(FILE *file, char *ending)
{
    *ending = '\0';

    char *string;
    int buf = 128;
    int lent = 0;

    char symb;
    if (ending_symb((symb = getc(file))))
    {
        *ending = symb;
        return NULL;
    }

    ungetc(symb, file);
    string = (char *)malloc(sizeof(char) * buf);

    if (string == NULL)
    {
        return NULL;
    }

    while ((symb = getc(file)) != EOF && !ending_symb(symb))
    {
        if (symb == '\n' || symb == ' ')
        {
            continue;
        }
        if (lent + 1 > buf)
        {
            buf *= 2;
            char *temp = (char *)realloc(string, sizeof(char) * buf);
            if (temp == NULL)
            {
                free(string);
                return NULL;
            }
            string = temp;
        }
        string[lent++] = symb;
    }

    ungetc(symb, file);

    if (lent == 0)
    {
        free(string);
        return NULL;
    }
    if (lent != buf)
    {
        char *temp = (char *)realloc(string, sizeof(char) * (lent + 1));
        if (temp == NULL)
        {
            free(string);
            return NULL;
        }
        string = temp;
    }

    string[lent] = '\0';
    *ending = ' ';

    return string;
}

bool is_number(const char *s)
{
    int l = strlen(s);
    for (int i = 0; i < l; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

statements solve(FILE *in)
{
    Stack *stack = create_stack();

    if (stack == NULL)
    {
        return allocate_error;
    }
    char *lexema = NULL;
    char op;

    while ((lexema = scan_lexema(in, &op)) != NULL || op != '\0')
    {
        //printf("%s\n", lexema);
        if (lexema == NULL)
        {
            if (op == ')')
            {
                Node *nd;
                while ((nd = stack_pop(stack)) != NULL && nd->symb != '(')
                {
                    if (nd->symb != ' ')
                    {
                        printf("%c ", nd->symb);
                    }
                    else
                    {
                        printf("%d ", nd->val);
                    }
                }
            }
            else if (op == '^')
            {
            }
            else
            {
                Node *nd = create_node(0, op);
                if(nd == NULL)
                {
                    //
                    return allocate_error;
                }
                push_back(stack, nd);
            }
        }
        else{
            Node *nd = create_node(atoi(lexema), ' ');
            push_back(stack, nd);
        }
    }
    return correct;
    /*
    Читаем очередной символ.
    Если символ является числом или постфиксной функцией (например, ! — факториал), добавляем его к выходной строке.
    Если символ является префиксной функцией (например, sin — синус), помещаем его в стек.
    Если символ является открывающей скобкой, помещаем его в стек.
    Если символ является закрывающей скобкой:
    До тех пор, пока верхним элементом стека не станет открывающая скобка, выталкиваем элементы из стека в выходную строку. При этом открывающая скобка удаляется из стека, но в выходную строку не добавляется. Если стек закончился раньше, чем мы встретили открывающую скобку, это означает, что в выражении либо неверно поставлен разделитель, либо не согласованы скобки.
    Если существуют разные виды скобок, появление непарной скобки также свидетельствует об ошибке. Если какие-то скобки одновременно являются функциями (например, [x] — целая часть), добавляем к выходной строке символ этой функции.
*/
}