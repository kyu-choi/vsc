#include <stdio.h>
#include <stdlib.h>


void    bino(int **bi,int n, int k)
{
    int i;
    int j;

    i = 0;
    while (i <= n)
    {
        j = 0;
        while ( j <= k && j <= i)
        {
            if (j == 0 || i == j)
                bi[i][j] = 1;
            else
                bi[i][j] = (bi[i-1][j-1] + bi[i-1][j]) % 10007;
            j++;
        }
        i++;
    }

    printf("%d",bi[n][k]);

}

int main(void)
{
    int n;
    int k;
    int i;
    int j;

    int **bi;

    scanf("%d",&n);
    scanf("%d",&k);

    bi = (int **)malloc(sizeof(int *) * (n+1));

    i = 0;
    while (i <= n)
    {
        bi[i] = (int *)malloc(sizeof(int) * (k+1));
        j = 0;
        while (j <= k)
        {
            bi[i][j] = -1;
            j++;
        }
        i++;
    }

    bino(bi,n,k);

    i = 0;
    while (i < n)
    {
        free(bi[i]);
        i++;
    }
    free(bi);

    return (0);
}