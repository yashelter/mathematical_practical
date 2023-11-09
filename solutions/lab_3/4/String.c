#include "../MonoBehavior.c"

typedef struct
{
    char *value;
    int length;
    int _buffer;
} String;

int max(int a, int b) { return a > b ? a : b; }

int lexicographic_compare(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (*a != *b)
        {
            return (unsigned char)*a - (unsigned char)*b;
        }
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

void copy_chars(char *to, char *from, int start, int l)
{
    for (int i = start, j = 0; i < l; i++)
    {
        to[i] = from[j];
        j++;
    }
    to[l] = '\0';
}


statements create_string(char *input, String **resulting)
{
    String *s = (String *)malloc(sizeof(String));
    if (s == NULL)
    {
        return allocate_error;
    }
    int l = strlen(input), size = max(MIN_BUF, l + 1);

    char *val = (char *)malloc(sizeof(char) * size);
    if (val == NULL)
    {
        free(s);
        return allocate_error;
    }
    copy_chars(val, input, 0, l);
    s->length = l;
    s->value = val;
    s->_buffer = size;
    *resulting = s;
    return correct;
}

statements delete_string(String *s)
{
    if (s == NULL)
    {
        return invalid_input;
    }
    if (s->value != NULL)
    {
        free(s->value);
    }
    free(s);
    return correct;
}

statements clear_string(String *s)
{
    statements stm;
    stm = delete_string(s);
    if (stm != correct)
    {
        return stm;
    }
    stm = create_string("", &s);
    return stm;
}

// copies string to created obj
statements string_copy_to(String *to, String *from)
{
    if (to == NULL || from == NULL || from->value == NULL)
    {
        return invalid_input;
    }
    char *temp = (char *)malloc(sizeof(char) * (from->_buffer));
    if (to->value == NULL)
    {
        return allocate_error;
    }
    copy_chars(temp, from->value, 0, from->length);
    if (to->value != NULL)
    {
        free(to->value);
    }
    to->value = temp;
    to->length = from->length;
    to->_buffer = from->_buffer;
    return correct;
}

// getting copy of string
statements string_copy(String *from, String **result)
{
    if (from == NULL || from->value == NULL)
    {
        return invalid_input;
    }
    if (*result != NULL)
    {
        free(*result);
    }
    *result = NULL;
    create_string(from->value, result);
    
    return correct;
}


// copies from second paramenters value to first, with saving that was
statements concat_string(String *left, String *right)
{
    if (left == NULL || right == NULL) { return invalid_input; }
    if (left->length + right->length <= left->_buffer)
    {
        left->_buffer = left->_buffer + right->_buffer + 1;
        char *temp = (char *) realloc(left->value, sizeof(char) * left->_buffer);
        if (temp == NULL) {free(left->value); left->value = NULL; return allocate_error; }
        left->value = temp;
    }
    copy_chars(left->value, right->value, left->length, left->length + right->length);
    left->length = left->length + right->length;
    return correct;
}   

// from usual concat deletes right
statements _s_concat_string(String *left, String *right)
{
    statements stm = concat_string(left, right);
    if (stm != correct) {return stm;}
    delete_string(right);
    return correct;
}

int compare_strings(String *a, String *b)
{
    if (a == NULL || b == NULL)
    {
        return 0;
    }
    return lexicographic_compare(a->value, b->value);
}

void print_string(String *s)
{
    for (int i = 0; i < s->length; i++)
    {
        printf("%c", (s->value)[i]);
    }
    //printf(" ");
    //printf("\n"); // debug
}