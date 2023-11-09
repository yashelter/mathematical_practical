#include "String.c"


int main() {
    String *p = NULL;
    create_string("1234", &p);
    printf("%s \n", p->value);
    delete_string(p);
    return 0;
}