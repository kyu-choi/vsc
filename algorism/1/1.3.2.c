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
    int count;

    i = 0;
    count = 0;
    while ( i < n)
    {
        j = i + 1;
        while ( j < n )
        {
            if (p[i] > p[j])
            {
                swap(&p[i],&p[j]);
                count++;
            }
            j++;
        }
        i++;
    }
    i = 0;
    while ( i < n )
    {
        printf("%d",p[i]);
        if (i != (n - 1))
            printf(" ");
        else
            printf("\n");
        i++;
    }

    printf("%d",count);
}


int main(void)
{
    int a;
    int i;
    int n;

    int *p;

    scanf("%d",&a);

    p = (int *)malloc(sizeof(int)*a);
    i = 0;
    while ( i < a)
    {
        scanf("%d",&n);
        p[i] = n;
        i++;
    }

    exsort(a,p);

    return (0);


}
