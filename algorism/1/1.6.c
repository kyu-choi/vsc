#include <stdio.h>

int count = 0;

int fibo(int n)
{
    if (n ==0)
    {
        count++;
        return 0;
    }
        else if (n==1)
    {
        count++;
        return (1);
    }
    count++;

    return ((fibo(n-1) + fibo(n-2)) % 1000000);
}

int main(void)
{
    int a;
    int b;
    
    
    scanf("%d",&a);

    b = fibo(a);
    printf("%d\n%d\n",b,count);
    
    return (0);

}