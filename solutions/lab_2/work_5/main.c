#include "work5.c"


int main() {
    
    //printf("%s", res);
    char * res = "";
    oversprintf(&res, "This is %mf in Roman %Ro really? %d", 151561.15151, 512, 1);
    printf("\n%s\n", res);
    return 0;
}
