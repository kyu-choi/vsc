#include <stdio.h>
#include <stdlib.h>

int count = 0;

int *S;
void quicksort(int low, int high);
void swap(int* a, int* b);
void partition(int low, int high, int* pivotpoint); 

void swap(int* a, int* b) 
{
    count++;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void partition(int low, int high, int* pivotpoint) 
{
    int pivotitem = S[low];
    int j = low;
    for (int i = low + 1; i <= high; i++) 
    {
        if (S[i] < pivotitem) 
        {
            j++;
            swap(&S[i], &S[j]);
        }
    }
    *pivotpoint = j;
    swap(&S[low], &S[*pivotpoint]);
}
void quicksort(int low, int high) 
{
    int pivotpoint;
    if (low < high) 
    {
        partition(low, high, &pivotpoint);
        quicksort(low, pivotpoint - 1);
        quicksort(pivotpoint + 1, high);
    }
}



int main(void)
{
    int a;
    int i;

    scanf("%d",&a);
    S = (int *)malloc(sizeof(int)*a);
    i = 0;
    while ( i < a )
    {
        scanf("%d",&S[i]);
        i++;
    }

    quicksort(0,a-1);
    i = 0;
    while (i < a)
    {
        printf("%d",S[i]);
        if ( i != a-1)
            printf(" ");
        else
            printf("\n");
        i++;
    }
    printf("%d\n",count);

    return (0);
}