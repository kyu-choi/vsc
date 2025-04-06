#include <stdio.h>

int main(void)
{

    int n;
    int k;
    int i;
    int j;
    int temp;

    int bn[100];
 

    scanf("%d %d",&n,&k);

    i = 1;
    j = 0;
    

    bn[0] = 1;
    bn[1] = 1;

    while ( i <= n)
    {
        j = 1;
        while ( j <= k)
        {
            temp = bn[j];
            bn[j] = bn[j - 1] + bn[j];
            j++;            
        }
        i++;
    }
    i = 0;
    while ( i <= k )
    {
        printf("%d\t",bn[i]);
        i++;
    }

}