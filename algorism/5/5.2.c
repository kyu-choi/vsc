#include <stdio.h>
#include <stdlib.h>

int **bi;

int count = 0;

void    bino(int n, int k)
{
    count++;
    if (k==0 || k==n)
        bi[n][k] = 1;
    else if (bi[n][k] == -1)
        bi[n][k] = (bi[n-1][k-1] + bi[n-1][k]) % 10007;    
}


int main(void)
{
    int n;
    int k;
    int i;
    int j;

    scanf("%d",&n);
    scanf("%d",&k);

    bi = (int **)malloc(sizeof(int *) * (n+1));

    i = 0;
    while ( i <= n)
    {
        bi[i] = (int *)malloc(sizeof(int) * (k+1));
        i++;
    }
    i = 0;

    while (i <= n)
    {
        j = 0;
        while ( j <= k)
        {
            bi[i][j] = -1;
            j++;
        }
        i++;
    }


    bino(n,k);

    printf("%d\n",bi[n][k]);
    printf("%d",count);

}