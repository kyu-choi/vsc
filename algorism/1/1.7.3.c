#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a;
    int i;

    int *p;

    scanf("%d",&a);

    p = (int *)malloc(sizeof(int)*(a+1));

    p[0] = 0;
    p[1] = 1;

    i = 2;

    while ( i < a+1)
    {
        p[i] = (p[i - 1] + p[i - 2]) % 1000000;
        if ( i ==a)
        {
            break;
        }
        i++;
    }

    printf("%d\n",p[a]);
    
    
    return (0);
}