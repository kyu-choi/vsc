#include <stdio.h>
#include <stdlib.h>

void    mulmat(int a,int **p,int **q,int **r)
{
    int i;
    int j;
    int k;
    i = 0;
    while ( i < a)
    {
        j = 0;
        while ( j < a)
        {
            k = 0;
            while (k < a)
            {
                r[i][j] += p[i][k] * q[k][j];
                k++;
            }
            j++;
        }
        i++;
    }
    i = 0;
    while ( i < a)
    {
        j = 0;
        while (j < a)
        {
            printf("%d",r[i][j]);
            if (j != a - 1)
                printf(" ");
            else
                printf("\n");
            j++;
        }
        i++;
    }
}


int main(void)
{
    int a;
    int **p;
    int **q;
    int **r;
    int n;
    int i;
    int j;

    scanf("%d",&a);
    i = 0;
    p = (int **)malloc(sizeof(int *)*a);
    while (i < a)
    {
        p[i] = (int *)malloc(sizeof(int) * a);
        i++;
    }
    q = (int **)malloc(sizeof(int *)*a);
    i = 0;
    while (i < a)
    {
        q[i] = (int *)malloc(sizeof(int) * a);
        i++;
    }

    r = (int **)malloc(sizeof(int *)*a);
    i = 0;
    while (i < a)
    {
        r[i] = (int *)malloc(sizeof(int) * a);
        i++;
    }

    i = 0;
    while (i < a)
    {
        j = 0;
        while (j < a)
        {
            p[i][j] = 0;
            q[i][j] = 0;
            r[i][j] = 0;
            j++;
        }
        i++;
    }


    i = 0;
    while ( i < a)
    {
        j = 0;
        while (j < a)
        {
            scanf("%d",&n);
            p[i][j] = n;
            j++;
        }
        i++;
    }
    i = 0;
    while ( i < a)
    {
        j = 0;
        while (j < a)
        {
            scanf("%d",&n);
            q[i][j] = n;
            j++;
        }
        i++;
    }

    mulmat(a,p,q,r);
    return (0);

}