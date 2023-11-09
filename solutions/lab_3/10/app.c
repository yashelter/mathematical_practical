#include "../MonoBehavior.c"


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