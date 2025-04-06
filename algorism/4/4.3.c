#include <stdio.h>

#define MOD 10007

typedef struct
{
    long long a;
    long long b;
    long long c;
    long long d;
} Matrix;

Matrix matmul(Matrix m1, Matrix m2)
{
    Matrix res;

    res.a = (m1.a*m2.a + m1.b*m2.c)%MOD;
    res.b = (m1.a*m2.b + m1.b*m2.d)%MOD;
    res.c = (m1.c*m2.a + m1.d*m2.c)%MOD;
    res.d = (m1.c*m2.b + m1.d*m2.d)%MOD;
    return (res);
}

Matrix matrixpower(Matrix base, long long n)
{
    if (n == 1)
        return (base);

    Matrix half;
    Matrix temp;
    half = matrixpower(base,n/2);

    if (n%2 ==0)
    {
        return (matmul(half,half));
    }
    else
    {
        temp = matmul(half,half);
        return matmul(temp,base);
    }


}


long long fibonacci(long long n)
{
    if (n <= 0)
        return (0);
    if (n == 1)
        return (1);
    
    Matrix base = {1,1,1,0};

    Matrix result = matrixpower(base, n-1);

    return result.a;
}

int main(void)
{
    long long n;
    long long fibo;
    int i;
    
    char input[100];
    scanf("%s",input);
    i = 0;
    n = 0;
    while ( input[i] !='\0')
    {
        n = (n*10 + (input[i]-'0')) % (2 * (MOD+1));
        i++;
    }

    fibo = fibonacci(n);

    printf("%lld",fibo);

    return (0);
    
}