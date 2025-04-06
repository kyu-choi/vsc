#include <stdio.h>
#include <stdlib.h>

int **q;
int **p;

void    matcpy(int **q,int **p,int n)
{
    int i;
    int j;
    i = 0;
    while ( i < n)
    {
        j = 0;
        while(j < n)
        {
            q[i][j]=p[i][j];
            j++;
        }
        i++;
    }
}

void    matmul(int **a,int **b,int **q,int n)
{
    int i;
    int j;
    int k;

    int val;

    int **temp;
    temp = (int **)malloc(sizeof(int *)*n);
    i = 0;
    while ( i < n)
    {
        temp[i] = (int *)malloc(sizeof(int)*n);
        i++; 
    }

    i = 0;
    while ( i < n)
    {
        j = 0;
        while (j < n)
        {
            val = 0;
            k = 0;
            while (k < n)
            {
                val = (val+a[i][k]*b[k][j]) % 1000;
                k++;
            }
            temp[i][j] = val;
            j++;
        }
        i++;
    }

    i = 0;
    while ( i < n)
    {
        j = 0;
        while ( j < n)
        {
            q[i][j] = temp[i][j];
            j++;
        }
        i++;
    }

}

void    matpow(int **p, int **q, int a, int b)
{
    int i;
    int j;

    int **temp;

    i = 0;
    j = 0;
    if (b==0)
    {
        while ( i < a)
        {
            p[i][j] = 1;
            i++;
            j++;
        }
        return;
    }
    else if (b==1)
    {    
        matcpy(q,p,a);
        return;
    }
   
    temp = (int **)malloc(sizeof(int *)*a);
    i = 0;
    while ( i < a)
    {
        temp[i] = (int *)malloc(sizeof(int)*a);
        i++;
    }

    matpow(p,temp,a,b/2);
    matmul(temp,temp,q,a);
    if (b%2 ==1 )
    {
        matcpy(temp,q,a);
        matmul(temp,p,q,a);
    }


}



int main(void)
{
    int a;
    int b;
    int i;
    int j;



    scanf("%d",&a);
    p = (int **)malloc(sizeof(int *)*a);
    q = (int **)malloc(sizeof(int *)*a);

    scanf("%d",&b);

    i = 0;
    while( i < a)
    {
        p[i] = (int *)malloc(sizeof(int)*a);
        j = 0;
        while (j < a)
        {
            scanf("%d",&p[i][j]);
            j++;
        }
        i++;
    }
    i = 0;
    j = 0;
    while( i < a)
    {
        j = 0;
        q[i] = (int *)malloc(sizeof(int)*a);
        while ( j < a)
        {
            q[i][j] = 0;
            j++;
        }
        i++;
    }

    matpow(p,q,a,b);

    i = 0;
    while ( i < a)
    {
        j = 0;
        while ( j < a)
        {
            printf("%d",q[i][j]);
            if (j != a - 1)
                printf(" ");
            else
                printf("\n");
            j++;
        }
        i++;
    }

    return (0);
}