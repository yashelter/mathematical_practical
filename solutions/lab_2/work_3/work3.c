#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h> // для length
#include <time.h>

typedef enum
{
    unknow_state,
    correct,
    running_error,
    file_error,

} statements;

bool is_equal_str(char *str1, char *str2, int l)
{
    for (int i = 0; i < l; i++)
    {
        if (str1[i] != str2[i])
        {
            return false;
        }
    }
    return true;
}
void swap_char(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void move_char_left(char *str, int l) // str must be malloc'ed
{
    if (l == 1)
    {
        return;
    }
    for (int i = 0; i < l - 1; i++)
    {
        str[i] = str[i + 1];
    }
}
statements find_pattern(char *pattern, char *buffer, int l, FILE *file)
{
    // пытаемся заполнить buff
    size_t bytes_read = fread(buffer, 1, l, file);
    if (bytes_read != l)
    {
        return file_error;
    }
    // теперь в buff лежит корректная строка = шаблону по длине
    int string_n = 1, char_n = 1;
    for (int i = 0; i < l; i++)
    {
        char_n++;;
        if (buffer[i] == '\n') { string_n++; char_n = 1;}
    }
    if (is_equal_str(pattern, buffer, l)) 
    { 
        printf("Founded at line 1, at index 1\n");
    }
    char_n++;
    int c;

    while (true)
    {
        move_char_left(buffer, l);

        if ((c = fgetc(file)) == EOF) { break; }
        if (c == '\n') {string_n++; char_n = 1;}

        char character = (char)c;
        buffer[l-1] = character;

        //printf("%s - \"%s\" \n\n", pattern, buffer);
        if (is_equal_str(pattern, buffer, l)) 
        { 
            printf("Founded at line %d, at index %d\n", string_n, char_n - l);
        }
        char_n++;
       
    }
    return correct;
}

statements find_all_patterns(char *pattern, int num, ...)
{
    int l = strlen(pattern);
    char *buffer = (char *)malloc(sizeof(char) * (l + 1));
    if (buffer == NULL)
    {
        return running_error;
    }

    va_list args;
    va_start(args, num);

    for (int i = 0; i < num; i++)
    {
        char *path = va_arg(args, char *);
        FILE *file = fopen(path, "r");
        if (file == NULL)
        {
            printf("Error : with file %s\n", path);
            continue;
        }
        printf("<< Opened file at path: %s\n\n", path);
        statements stm = find_pattern(pattern, buffer, l, file);
        if (stm != correct){
            printf("Error : something with input was invalid \n");
        }
        fclose(file);
        printf("\n");
        // printf("Arg %d: %s\n", i, path);
    }

    va_end(args);
    free(buffer);
    return correct;
}
