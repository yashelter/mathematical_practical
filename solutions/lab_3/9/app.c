#include "Node.c"

String *get_line(FILE *file, char *delimeters, statements *state)
{
    String *s;
    statements stm = create_string("", &s);
    if (stm != correct)
    {
        *state = stm;
        return NULL;
    }
    char symb;

    while (((symb = fgetc(file)) != EOF) && (strchr(delimeters, symb) == NULL))
    {
        stm = string_add_char(symb, s);
        // printf("%c, ", symb);
        if (stm != correct)
        {
            *state = stm;
            return NULL;
        }
    }
    *state = correct;
    if (symb == EOF)
    {
        *state = end_of;
    }
    return s;
}

statements validate(int argc, char *argv[], char **sep)
{
    if (argc < 3)
    {
        return invalid_input;
    }
    char *answ = (char *)malloc(sizeof(char) * (argc - 1));
    answ[argc - 2] = '\0';
    if (answ == NULL)
    {
        return allocate_error;
    }
    for (int i = 2; i < argc; i++)
    {
        if (strlen(argv[i]) != 1)
        {
            free(answ);
            return invalid_input;
        }
        answ[i - 2] = argv[i][0];
    }
    *sep = answ;
    return correct;
}



statements run(int argc, char *argv[])
{
    char *separators = NULL;
    statements stm = validate(argc, argv, &separators);
    if (stm != correct)
    {
        return stm;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        free(separators);
        return invalid_file;
    }
    Node *root = create_node("_root_", &stm);
    if (stm != correct)
    {
        free(separators);
        return invalid_file;
    }
    statements state = correct;
    while (state != end_of)
    {
        String *s = get_line(file, separators, &state);
        if (stm != correct && stm != end_of)
        {
            free(separators);
            delete_node(&root);
            return stm;
        }

        Node *addable = create_node_s(s, &stm);
        if (stm != correct)
        {
            free(separators);
            delete_node(&root);
            return stm;
        }
        stm = add_node(root, addable);
        if (stm != correct)
        {
            free(separators);
            delete_node(&root);
            return stm;
        }
    }
    print_nodes(root, 0);
    printf("Success\n");
    String *s;
    //create_string("work", &s);

    //Node *search;

    //find_node(root, s, &search);
    //print_node(search);

    backup_nodes(root);
}