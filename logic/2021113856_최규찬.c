#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int*    binary(int a,int size)
{
    int *res;
    int i;
    i = 0;

    res = (int *)malloc(sizeof(int)*size);
    while ( i < size)
    {
        res[i] = 0;
        i++;
    }
    
    i = 0;
    while ( a > 0)
    {
        res[i] = a % 2;
        i++;
        a /= 2;
    }

    return (res);
}

void    printmax(int n, char alp[], char numarr[])
{
    int idx;
    int i;
    int size;

    int *bin;

    size = pow(2,n);
    bin = (int *)malloc(sizeof(int)*size);
    i = 0;
    while ( i < size)
    {
        bin[i] = 0;
        i++;
    }

    idx = 0;
    printf("F = ");
    while ( numarr[idx] != -1)
    {
        printf("(");
        bin = binary(numarr[idx],size);
        i = 0;
        while ( i < n)
        {
            printf("%c",alp[i]);
            if (bin[n-i-1] == 1)
                printf("\'");
            if (i != n-1)
                printf("+");
            i++;
        }

        printf(")");
        idx++;
    }
}

void    printmin(int n,char alp[],char numarr[])
{
    int idx;
    int i;
    int size;


    int *bin;

    size = pow(2,n);
    bin = (int *)malloc(sizeof(int)*size);
    i = 0;
    while ( i < size)
    {
        bin[i] = 0;
        i++;
    }

    idx = 0;
    printf("F = ");
    while ( numarr[idx] != -1)
    {
        bin = binary(numarr[idx],size);
        i = 0;
        while ( i < n)
        {
            printf("%c",alp[i]);
            if (bin[n-i-1] == 0)
                printf("\'");
            
            i++;
        }

        idx++;

        if (numarr[idx] != -1)
            printf(" + ");
    }
}

int main(void)
{
    int n;
    int i;
    int mode;
    int j;

    char alp[10];
    char numarr[1024];

    printf("변수의 갯수 N을 입력하세요 : ");
    scanf("%d",&n);

    if (n < 1 || n > 10)
    {
        printf("변수갯수 입력이 잘못되었습니다.");
        return (0);
    }

    printf("%d 개의 알파벳을 입력하세요 : ",n);
    i = 0;
    while ( i < n)
    {
        scanf("%s",&alp[i]);
        i++;
    }

    printf("minterm(0) 또는 maxterm(1) 을 선택하세요 : ");
    scanf("%d",&mode);
    if (mode == 1)
    {
        printf("maxterm 번호 목록을 입력하세요 (종료:-1) : ");
    }
    else
    {
        printf("minterm 번호 목록을 입력하세요 (종료:-1) : ");
    }
    i = 0;
    j = 0;
    while (i != -1)
    {
        scanf("%d",&numarr[j]);
        i = numarr[j];
        j++;
    }
    if (mode ==0)
        printmin(n,alp,numarr);
    else
        printmax(n,alp,numarr);

    return (0);
}