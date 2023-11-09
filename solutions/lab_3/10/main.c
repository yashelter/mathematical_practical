#include "MultiNode.c"

statements process_line(char *line)
{
    int size = strlen(line);
    Node *root;

    String *s;
    statements stm = create_string("root", &s);

    if (stm != correct)
    {
        return stm;
    }
    stm = create_node(s, &root);

    if (stm != correct)
    {
        return stm;
    }
    char symbol;
    int i = 0;

    s = NULL;

    stm = create_string("", &s);
    if (stm != correct)
    {
        return stm;
    }

    while (i < size)
    {
        symbol = line[i];
        Node *nd = NULL;
        if (symbol == ' ') {i++;continue;}
        if (s->length > 0 && (symbol == '(' || symbol == ',' || symbol == ')' || i == size - 1))
        {
            //print_string(s);
            stm = create_node(s, &nd);
            if (stm != correct)
            {
                return stm;
            }
            add_child(root, nd);
            //printf("\n");
            stm = create_string("", &s);
            if (stm != correct)
            {
                return stm;
            }
        }
        else if (symbol != ')' && symbol != ',')
        {
            String *temp;
            char *lk = (char *)malloc(sizeof(char) * 2);
            if (lk == NULL)
            {
                return allocate_error;
            }
            sprintf(lk, "%c", symbol);

            stm = create_string(lk, &temp);
            free(lk);
            if (stm != correct)
            {
                return stm;
            }
            stm = _s_concat_string(s, temp);
            // print_string(s);
        }

        if (symbol == '(')
        {
            root = nd;
        }
        else if (symbol == ')')
        {
            root = root->master;
        }
        i++;
    }
    print_nodes(root, 0);
    delete_nodes(root);
    delete_string(s);
}

int main()
{
    // если в скобках 1 элемент (чего вообще быть не должно), то надо поставить после него запятую
    char *input = "A (B (E (G, T (W, Z), R (W, Z)), F (L, M)), C)";
    process_line(input);
}