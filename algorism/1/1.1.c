#include <stdio.h>
#include <stdlib.h>

void findindex(int a, int *b, int p)
{
    int index;
    int i;
    index = 1;
    i = 0;
    while (i < p)
    {
        if (b[i] == a)
        {
            printf("%d is in %d.\n",a,i + 1);
            return;
        }
        i++;
    }
    printf("%d is not in S.\n",a);
}

int main(void)
{

    int p;
    int q;
    int i;
    
    scanf("%d %d",&p,&q);
    

    int *a;
    int *b;
    
    a = (int *)malloc(sizeof(int) * p);
    b = (int *)malloc(sizeof(int) * q);
    i = 0;
    
    while (i < p)
    {
        scanf("%d",&a[i]);
        i++;
    }

    i = 0;

    while (i < q)
    {
        scanf("%d",&b[i]);
        i++;
    }

    i = 0;
    while (i < q)
    {
        findindex(b[i],a,p);
        i++;
    }
    return (0);
}