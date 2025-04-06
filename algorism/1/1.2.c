#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a;
    int b;
    int sum;

    int i;
    i = 0;
    b = 0;
    sum = 0;
    scanf("%d",&a);
    while (i < a)
    {
        scanf("%d",&b);
        sum = sum + b;
        i++;
    }
    printf("%d",sum);
    return (0);
}