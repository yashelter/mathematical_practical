#include "work5.c"

int main() {
    
    //printf("%s", res);
    char * res = "";
    int ab = 5;
    oversprintf(&res, "\nThis is %n %Ro %Ro in Roman  really?", &ab, 5, 4);

    FILE *file = fopen("out.txt", "w");
    overfprintf(file, "This is %Ro-%Ro in Roman  really?", 5, 4);
    printf("%s %d\n", res, ab);
    return 0;
}
