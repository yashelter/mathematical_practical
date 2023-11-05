#include "polynom.c"
#include <stdbool.h>
#include <ctype.h>

#define BUFFER 200

char **split(const char *str, const char *delimiters, int *count)
{
    int token_count = 0;
    char **tokens = NULL;

    const char *start = str;
    const char *end = str;

    while (*end != '\0')
    {
        if (strchr(delimiters, *end) != NULL)
        {
            // Найден разделитель, выделяем строку и копируем часть
            int token_length = end - start;
            char *token = (char *)malloc(token_length + 1);
            if (token == NULL)
            {
                // Ошибка выделения памяти
                for (int i = 0; i < token_count; i++)
                {
                    free(tokens[i]);
                }
                free(tokens);
                return NULL;
            }
            strncpy(token, start, token_length);
            token[token_length] = '\0';

            // Добавляем строку к массиву строк
            token_count++;
            char **temp = (char **)realloc(tokens, sizeof(char *) * token_count);
            if (temp == NULL)
            {
                // Ошибка выделения памяти
                free(token);
                for (int i = 0; i < token_count - 1; i++)
                {
                    free(tokens[i]);
                }
                free(tokens);
                return NULL;
            }
            tokens = temp;
            tokens[token_count - 1] = token;

            // Продвигаем указатель `start`
            start = end + 1;
        }
        end++;
    }

    // Добавляем оставшуюся часть строки (последний токен)
    int token_length = end - start;
    char *token = (char *)malloc(token_length + 1);
    if (token == NULL)
    {
        // Ошибка выделения памяти
        for (int i = 0; i < token_count; i++)
        {
            free(tokens[i]);
        }
        free(tokens);
        return NULL;
    }
    strncpy(token, start, token_length);
    token[token_length] = '\0';

    token_count++;
    char **temp = (char **)realloc(tokens, sizeof(char *) * token_count);
    if (temp == NULL)
    {
        // Ошибка выделения памяти
        free(token);
        for (int i = 0; i < token_count - 1; i++)
        {
            free(tokens[i]);
        }
        free(tokens);
        return NULL;
    }
    tokens = temp;
    tokens[token_count - 1] = token;

    *count = token_count;
    return tokens;
}

statements get_file(char *path, FILE **result)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        return invalid_file;
    }
    *result = f;
    return correct;
}

statements parse_command(FILE *file, char **line)
{
    char *string = (char *)malloc(sizeof(char) * BUFFER);
    int buf = BUFFER;
    int cnt = 0;

    char ch;
    bool comment = false;
    bool bigcomment = false;

    while ((ch = fgetc(file)) != EOF && ch != ';')
    {
        if (buf - 1 <= cnt)
        {
            char *new_string = (char *)realloc(string, sizeof(char) * buf * 2);
            if (new_string == NULL)
            {
                free(string);
                return allocate_error;
            }
            buf *= 2;
        }
        if (!bigcomment && ch == '%')
        {
            comment = true;
        }
        if (!comment && ch == '[')
        {
            bigcomment = true;
        }
        if (ch != '\n' && ch != ' ' && !comment && !bigcomment)
        {
            string[cnt] = ch;
            // printf("%c\n", ch);
            cnt++;
        }

        if (ch == '\n' && comment)
        {
            comment = false;
        }
        if (bigcomment && ch == ']')
        {
            bigcomment = false;
        }
    }
    string[cnt] = '\0';
    *line = string;
    return correct;
}
int to_int(char c) { return c - '0'; }

statements pre_build_polynom(char *line, int *pos, Polynom **result)
{
    Polynom *ptr;
    int leng = strlen(line);
    int koef = -1;
    int i = *pos;

    int znak = 1;
    if (line[i] == '+' || line[i] == '-')
    {
        znak = line[i] == '-' ? -1 : 1;
        i++;
    }

    while (i < leng && isdigit(line[i]) != 0)
    {
        if (koef == -1)
        {
            koef = 0;
        }
        koef *= 10;
        koef += to_int(line[i]);
        i++;
    }
    if (koef == -1)
    {
        koef = 1;
    }

    koef *= znak;
    if (i >= leng || line[i] != 'x')
    {
        statements stm = create_polynom(&ptr);
        if (stm != correct)
        {
            return stm;
        }
        stm = add_koefficient(ptr, koef);
        if (stm != correct)
        {
            delete_polynom(ptr);
            return stm;
        }
        *result = ptr;
        *pos = i;
        return correct;
    }
    i++;

    if (i >= leng || line[i] != '^')
    {
        statements stm = create_polynom(&ptr);
        if (stm != correct)
        {
            return stm;
        }
        stm = add_koefficient(ptr, koef);
        if (stm != correct)
        {
            delete_polynom(ptr);
            return stm;
        }
        stm = add_koefficient(ptr, 0);
        if (stm != correct)
        {
            delete_polynom(ptr);
            return stm;
        }
        *result = ptr;
        *pos = i;
        return correct;
    }
    i++;
    statements stm = create_polynom(&ptr);
    if (stm != correct)
    {
        return stm;
    }

    int power = -1;
    while (i < leng && isdigit(line[i]) != 0)
    {
        if (power == -1)
        {
            power += 1;
        }
        power *= 10;
        power += to_int(line[i]);
        i++;
    }
    stm = add_koefficient(ptr, koef);
    if (stm != correct)
    {
        delete_polynom(ptr);
        return stm;
    }
    // printf("%d \n", power);
    while (power > 0)
    {
        power--;
        stm = add_koefficient(ptr, 0);
        if (stm != correct)
        {
            return stm;
        }
    }
    // print_polynom(ptr);
    *result = ptr;
    *pos = i;
    return correct;
}

statements get_zero(Polynom **p)
{
    statements stm = create_polynom(p);
    if (stm != correct)
    {
        return stm;
    }
    stm = add_koefficient(*p, 0);
    if (stm != correct)
    {
        delete_polynom(*p);
    }
    return stm;
}

void free_mas(char **input, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (input[i] != NULL)
        {
            free(input[i]);
        }
    }
    free(input);
}

statements build_polynom(char *input, int n, Polynom **a)
{
    // printf("%s\n", input[0]);
    int l = 0;
    Polynom *p = NULL, *current = NULL, *temper = NULL;
    statements stm = get_zero(&current);
    if (stm != correct)
    {
        return runtime_error;
    }
    int in_s = strlen(input);

    while (l < in_s)
    {
        stm = pre_build_polynom(input, &l, &p);
        if (stm != correct)
        {
            delete_polynom(p);
            delete_polynom(current);
            return stm;
        }
        stm = summation_polynoms(current, p, &temper);
        if (stm != correct)
        {
            delete_polynom(p);
            delete_polynom(current);
            delete_polynom(temper);
            return stm;
        }
        delete_polynom(current);
        current = temper; 
    }
    *a = current;
    //print_polynom(current);
    return correct;
}
statements run_command(char *line, Polynom **results)
{
    int size = strlen(line);

    if (strncmp(line, "Mult(", 5) != 0 && strncmp(line, "Mod(", 4) != 0 &&
        strncmp(line, "Div(", 4) != 0 && strncmp(line, "Add(", 4) != 0 &&
        strncmp(line, "Sub(", 4) != 0 && strncmp(line, "Diff(", 5) != 0 &&
        strncmp(line, "Cmps(", 5) != 0 && strncmp(line, "Eval(", 5) != 0)
    {
        return invalid_input;
    }
    // example "Mult(x^2+3x-1,2x+x^3)";

    char *delimiter = "()";

    int count;
    char **tokens = split(line, delimiter, &count);

    if (tokens == NULL)
    {
        return runtime_error;
    }

    if (!(count > 1 && tokens[1] != NULL && strlen(tokens[1]) > 0))
    {
        for (int i = 0; i < count; i++)
        {
            if (tokens[i] != NULL)
            {
                free(tokens[i]);
            }
        }
        free(tokens);
        return runtime_error;
    }
    char *polys = tokens[1];

    // printf("%s\n", polys);

    int n;
    char **input = split(polys, ",", &n);

    for (int i = 0; i < count; i++)
    {
        if (tokens[i] != NULL)
        {
            free(tokens[i]);
        }
    }
    free(tokens);

    if (strncmp(line, "Mult(", 5) == 0 && n > 0)
    {
        // printf("%s.%s\n", input[0], input[1]);
        Polynom *pol1, *pol2;
        build_polynom(input[0], n, &pol1);
        
        if (n == 2){
            build_polynom(input[1], n, &pol2);
        }
        else{
            pol2 = *results;
        }
        multiply_polynoms(pol1, pol2, results);
        print_polynom(*results);
        // example "Mult(x^2+3x-1,2x+x^3)";
    }
    if (strncmp(line, "Add(", 4) == 0 && n > 0)
    {
        // printf("%s.%s\n", input[0], input[1]);
        Polynom *pol1, *pol2;
        build_polynom(input[0], n, &pol1);
        
        if (n == 2){
            build_polynom(input[1], n, &pol2);
        }
        else{
            pol2 = *results;
        }
        summation_polynoms(pol1, pol2, results);
        print_polynom(*results);
        // example "Mult(x^2+3x-1,2x+x^3)";
    }
    if (strncmp(line, "Add(", 4) == 0 && n > 0)
    {
        // printf("%s.%s\n", input[0], input[1]);
        Polynom *pol1, *pol2;
        build_polynom(input[0], n, &pol1);
        
        if (n == 2){
            build_polynom(input[1], n, &pol2);
        }
        else{
            pol2 = *results;
        }
        summation_polynoms(pol1, pol2, results);
        print_polynom(*results);
        // example "Mult(x^2+3x-1,2x+x^3)";
    }
    free_mas(input, n);
}

int run()
{
    FILE *file;

    statements stm = get_file("input.txt", &file);

    // printf("uwu\n");

    char *command;
    stm = parse_command(file, &command);
    Polynom *p;
    run_command(command, &p);

    free(command);
}