#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void exchange(int a, int *b)
{
    int i;
    int j;
    int count;
    i = 0;
    while (i < a)
    {
        j = i + 1 ;
        while ( j < a )
        {
            if (b[i] > b[j])
            {
                swap(&b[i],&b[j]);
                count++;
            }
            j++;
        }
        i++;
    }
    i = 0;
    while ( i < a )
    {

        printf("%d",b[i]);
        if (i != a - 1)
        {
            printf(" ");
        }
        i++;
    }
    printf("\n%d",count);
}

int main(void)
{
    int a;
    int i;
    int *b;
    int c;

    i = 0;
    
    scanf("%d",&a);
    b = (int *)malloc(sizeof(int) * a);
    while (i < a)
    {
        scanf("%d",&c);
        b[i] = c;
        i++;
    }

    exchange(a,b);
    return (0);
}