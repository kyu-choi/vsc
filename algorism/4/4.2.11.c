#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int *num;
    int size;
} Largeint;

int K;
int funcount = 0;

void    carry(Largeint *src);
void    delzero(Largeint *stc);


void    lmul(Largeint *res, Largeint *s1,Largeint *s2)
{
    int i;
    int j;

    res->num = (int *)calloc(s1->size + s2->size,sizeof(int));
    res->size = s1->size + s2->size ;

    i = 0;
    while (i < s1->size)
    {
        j = 0;
        while ( j < s2->size)
        {
            res->num[i + j] += s1->num[i] * s2->num[j];
            j++;
        }
        i++;
    }
    carry(res);

}

void    carry(Largeint *src)
{
    int cary;
    int i;
    
    cary = 0;
    i = 0;
    while ( i < src->size)
    {
        src->num[i] += cary;
        cary = src->num[i] / 10;
        src->num[i] %= 10;
        i++;
    }
    if (cary > 0)
    {
        src->num = (int *)realloc(src->num, (src->size + 1) * sizeof(int));
        src->num[src->size++] = cary;
    }

}

void    ladd(Largeint *res, Largeint *s1,Largeint *s2)
{
    int size;
    int i;
    if (s1->size > s2-> size)
        size = s1->size;
    else
        size = s2->size;
    res->num = (int *)calloc(size,sizeof(int));
    res->size = size;

    i = 0;
    while ( i < size)
    {
        if ( i < s1->size)
            res->num[i] += s1->num[i];
        if ( i < s2->size)
            res->num[i] += s2->num[i];
        i++;
    }

    carry(res);

}

void    poww(Largeint *det, int n, Largeint *src)
{
    det->num = (int *)calloc(src->size + n,sizeof(int));
    det->size = src->size + n;
    memcpy(det->num + n,src->num,src->size * sizeof(int));
}


void    remnum(Largeint *det, Largeint *src, int n)
{
    int m;

    if ( src->size == 0)
    {
        det->size = 0;
        det->num = NULL;
    }
    else
    {
        if (n < src->size)
            m = n;
        else
            m = src->size;
        det->size = m;
        det->num = (int *)malloc(sizeof(int)*m);
        memcpy(det->num,src->num,sizeof(int)*m);;
        delzero(det);
    }
}

void    divnum(Largeint *dst, Largeint *src, int n)
{
    int m;

    if (src->size ==0)
    {
        dst->num = NULL;
        dst->size = 0;
    }
    else
    {
        if ( n < src->size)
            m = src->size - n;
        else
            m = 0;
        dst->num = (int *)malloc(sizeof(int)*m);
        dst->size = m;
        if ( m > 0)
        {
            memcpy(dst->num,src->num + n , m * sizeof(int));
        }        
        delzero(dst);
    }
}

void    prod(Largeint *res,Largeint *a,Largeint *b)
{
    funcount++;

    int max;
    int half;

    Largeint a1,a2,b1,b2;
    Largeint M1,M2,M3,M4,M5,M6,M7,M8;

    if (a->size > b->size)
        max = a->size;
    else
        max = b->size;
    if (max < K)
        lmul(res,a,b);
    else
    {
        half = max / 2;
        divnum(&a1,a,half);
        remnum(&a2,a,half);
        divnum(&b1,b,half);
        remnum(&b2,b,half);
    

        prod(&M1,&a1,&b1);
    
        poww(&M2,2 * half, &M1);

        prod(&M3,&a1,&b2);
        prod(&M4,&b1,&a2);

        ladd(&M5,&M3,&M4);

        poww(&M6,half,&M5);

        prod(&M7,&a2,&b2);

        ladd(&M8,&M2,&M6);

        ladd(res,&M7,&M8);
    }





}

void    delzero(Largeint *stc)
{
    while (stc->size>0 && stc->num[stc->size - 1] ==0 )
        stc->size--;
}

void    makestc(char *input,Largeint *stc)
{
    int len;
    int i;

    len = strlen(input);
    stc->size = len;
    stc->num = (int *)malloc(sizeof(int)*len);
    i = 0;
    while ( i < len)
    {
        stc->num[i] = input[len-1-i] - '0';
        i++;
    }

    delzero(stc);

}


void largetostring(Largeint *src, char *det)
{
    int idx = 0;
    int i;
    i = src->size -1;
    while (i >=0)
    {
        det[idx++] = src->num[i] + '0';
        i--;
    }
    det[idx] = '\0';
}

int main(void)
{
    char input_a[1001];
    char input_b[1001];
    char resstring[2000];

    Largeint a;
    Largeint b;
    Largeint res;

    scanf("%d",&K);
    scanf("%s %s",input_a,input_b);

    makestc(input_a,&a);
    makestc(input_b,&b);

    prod(&res,&a,&b);

    largetostring(&res,resstring);

    printf("%d\n",funcount);
    printf("%s",resstring);

    return (0);
}