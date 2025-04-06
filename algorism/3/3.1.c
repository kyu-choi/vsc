#include <stdio.h>
#include <stdlib.h>

int count = 0;

int a;
int b;
int i;

int *p;
int *q;

void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sortarr(int *p,int n)
{
    int i;
    int j;

    i = 1;
    while (i < n)
    {
        j = i+1;
        while ( j < n)
        {
            if(p[i]>p[j])
                swap(&p[i],&p[j]);
            j++;
        }
        i++;
    }

}

int binsearch2(int n,int low, int high)
{
    int mid;

    count++;


    if (low > high)
        return 0;
    else
    {
        mid = (low + high) / 2;
        if (n == p[mid])
            return mid;
        else if (n < p[mid])
            return binsearch2(n,low,mid - 1);
        else
            return binsearch2(n,mid + 1, high);
    }
}

int main(void)
{
   

    scanf("%d %d",&a,&b);
    a = a+1;

    p = (int *)malloc(sizeof(int)*a);
    q = (int *)malloc(sizeof(int)*b);

    i = 1;
    while (i < a)
    {
        scanf("%d",&p[i]);
        i++;
    }
    i = 0;
    while (i < b)
    {
        scanf("%d",&q[i]);
        i++;
    }

    sortarr(p,a);
    i = 0;
/*
    while ( i < a)
    {
        printf("%d\n",p[i]);
        i++;
    }
    i = 0;
    while ( i < b)
    {
        printf("%d\n",q[i]);
        i++;
    }
*/


    while ( i < b)
    {
        count = 0;
        printf("%d %d\n",count,binsearch2(q[i],1,a-1));
        i++;
    }


    
    return (0);
}
