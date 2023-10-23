#include "functions.c"
#define MAX_L 1000

char **split_perc(char*str, int *point)
{
    *point = -1;
    int l = strlen(str);
    int i = 0;

    for (; i < l - 1; i++) 
    { 
        if (str[i] == '%' && str[i+1] != '%'){break;}
        else if (str[i] == '%' ) { i++;}
    }

    if (str[i] == '%' && str[i+1] != ' ') {*point = i;}
    else
    {
        return NULL;
    }

    int pos_end = i+1;
    while (pos_end < l && str[pos_end] != ' ') {pos_end++;};

    //here
    char *s1 = (char*) malloc(sizeof(char) * (i + 1));
    if (s1 == NULL) {return NULL;}

    char *s2 = (char*) malloc(sizeof(char) * (pos_end - i + 1));
    if (s2 == NULL) {free(s1); return NULL;}

    char *s3 = (char*) malloc(sizeof(char) * (l - pos_end + 1));
    if (s3 == NULL) {free(s1); free(s2); return NULL;}

    for (int j = 0; j < i; j++) 
    {
        s1[j] = str[j];
    }
    s1[i] = '\0';

    int k = 0;
    for (int j = i; j < pos_end; j++) {
        s2[k] = str[j];
        k++;
    }
    s2[k] = '\0'; // Завершите вторую подстроку нулевым символом

    // Выделение третьей подстроки (после пробела)
    int m = 0;
    for (int j = pos_end; j < l; j++) {
        s3[m] = str[j];
        m++;
    }
    s3[m] = '\0'; // Завершите третью подстроку нулевым символом

    // Выделяем память для массива указателей
    char **res = (char**) malloc(sizeof(char *) * 3);
    if (res == NULL) {
        free(s1);
        free(s2);
        free(s3);
        return NULL;
    }

    res[0] = s1;
    res[1] = s2;
    res[2] = s3;

    return res;

}

statements try_execute(char *format, va_list *ptr, char **res)
{
    if (strcmp(format, "%Ro") == 0)
    {
        int num = va_arg(*ptr, int);
        statements stm = to_roman(num, res);
        return stm;
    }
    if (strcmp(format, "%Zr") == 0)
    {
        unsigned int num = va_arg(*ptr, unsigned int);
        statements stm = zeckendorf_look(num, res);
        return stm;
        
    }
    if (strcmp(format, "%Cv") == 0)
    {
        int num = va_arg(*ptr, int);
        int base = va_arg(*ptr, int);
        statements stm = _10th_to_cc(num, base, res, false);
        return stm;
    }
    if (strcmp(format, "%CV") == 0)
    {
        int num = va_arg(*ptr, int);
        int base = va_arg(*ptr, int);
        statements stm = _10th_to_cc(num, base, res, true);
        return stm;
    }
    if (strcmp(format, "%to") == 0 || strcmp(format, "%TO") == 0 )
    {
        char* str = va_arg(*ptr, char*);
        int base = va_arg(*ptr, int);
        long long _res;
        statements stm = cc_to_10th(str, base, &_res, strcmp(format, "%TO") == 0);
        if (stm != correct) { return stm; }
        
        int buffer_size = snprintf(NULL, 0, "%lld", _res);
        char *temp = (char *)malloc(buffer_size + 1);

        if (str == NULL) {
            return memory_error;
        }

        snprintf(temp, buffer_size + 1, "%lld", _res);
        *res = temp;
        return correct;
    }
    if (strcmp(format, "%mi") == 0)
    {
        int num = va_arg(*ptr, int);
        statements stm = print_memory_dump(&num, sizeof(int), res);
        return stm;
    }
    if (strcmp(format, "%mu") == 0)
    {
        unsigned int num = va_arg(*ptr, unsigned int);
        statements stm = print_memory_dump(&num, sizeof(unsigned int), res);
        return stm;
    }
    if (strcmp(format, "%md") == 0)
    {
        double num = va_arg(*ptr, double);
        statements stm = print_memory_dump(&num, sizeof(double), res);
        return stm;
    }
    if (strcmp(format, "%mf") == 0)
    {
        float num = va_arg(*ptr, double);
        statements stm = print_memory_dump(&num, sizeof(float), res);
        return stm;
    }
    return nah_executed;
    
}

int oversprintf(char** str, char* format, ...) 
{
    va_list ptr;
    va_start(ptr, format);

    char buffer_s[MAX_L];
    char *buffer = buffer_s;

    int written = 0;
    int pos;

    char* right = NULL;
    char ** res = split_perc(format, &pos);
    
    while (pos != -1 && res != NULL && written < MAX_L)
    {
        char *left = res[0], *mid = res[1];
        right = res[2];

        char *result = NULL;
        written = vsnprintf(buffer + written, MAX_L - written, left, ptr) + written;
        
        if (strlen(mid) > 0) 
        {
            statements printed = try_execute(mid, &ptr, &result);
            if (printed == correct){
                written += vsnprintf(buffer + written, MAX_L - written, result, ptr);
                free(result);
            }
            else{
                 written += vsnprintf(buffer + written, MAX_L - written, mid, ptr);
            }          
        }
        if (res[0] != NULL) {free(res[0]);}
        if (res[1] != NULL) {free(res[1]);}

        if (strlen(right) > 0)
        {
            char **new_res = split_perc(right, &pos);
            if (res[2] != NULL) {free(res[2]);}
            free(res);
            res = NULL;
            right = NULL;

            res = new_res;
        }
        else
        {
            break;
        }
    }
    va_end(ptr);

    *str = (char *) malloc(sizeof(char) * (written + 1));

    for (int i = 0; i < written; i++)
    {
        (*str)[i] = buffer[i];
    }
    
    //vsnprintf(*str, MAX_L, buffer, NULL);   
    return 0;
}