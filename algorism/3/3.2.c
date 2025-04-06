#include <stdio.h>
#include <stdlib.h>

int count = 0;

void merge2(int *S, int low, int mid, int high) 
{
    count++;
    int i = low, j = mid + 1, k = 0;
    int size = high - low + 1;
    int *U = (int *)malloc(size * sizeof(int));
    
    while (i <= mid && j <= high)
        U[k++] = (S[i] < S[j]) ? S[i++] : S[j++];
    
    if (i > mid) {
        // S[j] 부터 S[high]까지를 U[k] 부터 U[high]로 이동
        while (j <= high)
            U[k++] = S[j++];
    }
    else {
        // S[i] 부터 S[mid]까지를 U[k] 부터 U[high]로 이동
        while (i <= mid)
            U[k++] = S[i++];
    }
    
    // U[0] 부터 U[high-low+1]까지를 S[low] 부터 S[high]로 이동
    for (int t = low; t <= high; t++)
        S[t] = U[t - low];
        
    free(U);  // 동적 할당된 메모리 해제
}
void mergesort2(int *S, int low, int high)
 {
    if (low < high) 
    {
        int mid = (low + high) / 2;
        mergesort2(S, low, mid);
        mergesort2(S, mid + 1, high);
        merge2(S, low, mid, high);
    }
}

int main(void)
{
    int a;
    int i;

    int *p;

    scanf("%d",&a);
    a++;
    p = (int *)malloc(sizeof(int)*a);
    
    i = 1;
    while (i < a)
    {
        scanf("%d",&p[i]);
        i++;
    }

    mergesort2(p,1,a-1);
    i = 1;
    while(i < a)
    {
        printf("%d",p[i]);
        if ( i!=a-1)
            printf(" ");
        else
            printf("\n");
        i++;
    }
    printf("%d",count);

    return (0);

}