#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int *arr;
    int size;
}Array;


Array   make(int a)
{
    int i;
    int size;
    int b;
    int *q;
    Array result;

    size = 1;
    
    b = a;
    while ( a != 1)
    {
        if (a % 2 ==0)
        {
            a = a / 2;
        }
        else if (a % 2 == 1)
        {
            a = 3 * a + 1;
        }
        size++;
    }
    q = (int *)malloc(sizeof(int) * (size));
    i = 1;
    q[0] = b;

    while ( i < size)
    {
        if ( b % 2 ==0)
            b = b / 2;
        else if (b % 2 == 1)
            b = 3 * b + 1;
        q[i] = b;
        i++;
    }

    result.arr = q;
    result.size = size;
    return (result);
}

void printarr(Array arr)
{
    int i;
    i = 0;

    while (i < arr.size)
    {
        printf("%d",arr.arr[i]);
        if (arr.arr[i] != 1)
            printf(" ");
        i++;
    }
}

int main(void)
{
    int a;
    int b;
    int size;
    int i;
    int max;
    int maxindex;

    Array *arr;

    scanf("%d %d",&a,&b);
    size = b - a + 1;
    arr = (Array *)malloc(sizeof(Array)*size);


    i = 0;

    while ( i < size )
    {
        arr[i] = make(a+i);
        i++;
    }

    i = 0;
    max = 0;
    while ( i < size)
    {
        if (max <= arr[i].size)
        {
            max = arr[i].size;
            maxindex = i;
        }
            i++;
    }

    printf("%d %d\n",a + maxindex,arr[maxindex].size-1);
    
    printarr(arr[maxindex]);
    return (0);
}