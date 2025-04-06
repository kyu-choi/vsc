#include <stdio.h>

int main(void)
{
    int a;
    scanf("%d",&a);

    printf("%d\n",a);
    
    while ( a != 1)
    {
        if ( a % 2 ==0 )
            a = a / 2;
        else if ( a % 2 == 1 )
            a = 3*a + 1;
        printf("%d\n",a);
    }
    return (0);
}