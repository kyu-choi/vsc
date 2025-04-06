#include <stdio.h>
#include <stdlib.h>
void    swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;

}

void exsort(int n,int *p)
{
    int i;
    int j;

    i = 0;
    while ( i < n)
    {
        j = i + 1;
        while ( j < n )
        {
            if (p[i] > p[j])
                swap(&p[i],&p[j]);
            j++;
        }
        i++;
    }
}

void    bisearch(int a,int b,int *p)
{
    int i;
    i = 0;
    while ( i < a)
    {
        if ( b == p[i])
        {
            printf("%d is in %d.\n",b,i + 1);
            return ;
        }
        i++;
    }
    printf("%d is not in S.\n",b);
}

int main(void)
{
    int a;
    int b;
    int i;
    int n;

    int *p;
    int *q;

    scanf("%d",&a);
    scanf("%d",&b);


    p = (int *)malloc(sizeof(int)*a);
    i = 0;
    while ( i < a)
    {
        scanf("%d",&n);
        p[i] = n;
        i++;
    }

    q = (int *)malloc(sizeof(int)*b);
    i = 0;
    while ( i < b)
    {
        scanf("%d",&n);
        q[i] = n;
        i++;
    }

    exsort(a,p);
    i = 0;
    while ( i < b)
    {
        bisearch(a,q[i],p);
        i++;
    }
    



    return (0);
}