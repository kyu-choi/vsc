#include <stdio.h>

int main(int argc, char **argv)
{
    int i;

    printf("%d\n", argc);
    i = 1;
    while ( i < argc)
    {
        printf("%s\n", argv[i]);
        i++;
    }
    return (0);
}