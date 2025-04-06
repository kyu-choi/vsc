#include <stdio.h>
#include <stdlib.h>

void swap(int *a,int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sortarr(int n,int *a)
{
    int i;
    int j;
    i = 0;
    while (i < n)
    {
        j = i + 1;
        while (j < n)
        {
            if (a[i]>a[j])
            {
                swap(&a[i],&a[j]);
            }
            j++;
        }
        i++;
    }
}

void bisearch(int a,int *p,int s)
{
    int low;
    int high;
    int mid;

    low = 0;
    high = a - 1;


    while (low <= high )
    {
        mid = (low + high) / 2;
        if ( p[mid] == s)
        {   printf("%d is in %d\n",s,mid+1);
            return ;
        }
        else if (mid < s)
        {
            high = mid - 1;

        }
        else if (mid > s)
        {
            low = mid + 1;
        }

    }
    printf("%d is not in S\n",s);


}

int main(void)
{
    int a;
    int b;

    int max;

    int i;
    int n;
    int *p;
    int *q;

    scanf("%d",&a);
    scanf("%d",&b);

    p = (int *)malloc(sizeof(int) * a);
    q = (int *)malloc(sizeof(int) * b);
    i = 0;
    while (i < a)
    {
        scanf("%d",&n);
        p[i] = n;
        i++;    
    }
    i = 0;
    while ( i < b)
    {
        scanf("%d",&n);
        q[i] = n;
        i++;
    }

    sortarr(a,p);

    i = 0;
    while ( i < b)
    {
        bisearch(a,p,q[i]);
        i++;
    }
    
    return (0);

}