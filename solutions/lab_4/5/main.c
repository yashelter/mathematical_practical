#include "stack.c"
#include "polish_notation.c"

int main()
{
    int l = 0;
    char *ans;
    solve("2*(2^2+1*3+4)", &ans, &l);
    printf("%s\n%d", ans, l);
    free(ans);
    /*
        for (int i = 0; i < l; i++)
        {
            free(ans[i]);
        }
        free(ans);*/
}