#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int funcount = 0;

void simplemul(char *res, char *a, char *b)
{
    int i;
    int j;
    int pos;

    int a_len;
    int b_len;

    int size;
    int *result;

    a_len = strlen(a);
    b_len = strlen(b);
    size = a_len + b_len;
    result = (int *)calloc(size,sizeof(int));

    i = a_len - 1;
    while ( i >= 0 )
    {
        j = b_len - 1;
        while ( j >=0 )
        {
            result[i + j + 1] += (a[i]-'0')*(b[j] - '0');
            j--;
        }
        i--;
    }

    i = size - 1;
    while ( i > 0)
    {
        result[i-1] += result[i] / 10;
        result[i] = result[i] % 10;
        i--;
    }
    i = 0;
    while (i < size - 1 && result[i] == 0)
        i++;
    pos = 0;
    while (i < size)
    {
        res[pos] = result[i] + '0';
        pos++;
        i++;
    }
    res[pos] = '\0';
    
}

void reverse(char *src)
{
    int i;
    int size;

    char temp;

    i = 0;
    size = strlen(src);
    while ( i < size / 2)
    {
        temp = src[i];
        src[i] = src[size - 1 - i];
        src[size -1 -i] = temp;
        i++;
    }


}

void string_sub(char *res, char *a, char *b)
{
    int i;
    int j;

    int borrow;
    int pos;

    int sub;

    char temp[2002];

    borrow = 0;
    pos = 0;

    i = strlen(a) - 1;
    j = strlen(b) - 1;

    while ( i >=0 )
    {
        sub = a[i] - '0' - borrow;
        if ( j >=0 )
        {
            sub -= b[j] - '0';
            j--;
        }
        if (sub < 0)
        {
            borrow = 1;
            sub += 10;
        }
        else
            borrow = 0;
        temp[pos] = sub + '0';
        i--;
        pos++;
    }

    while ( pos > 1 && temp[pos -1] == '0')
        pos--;

    temp[pos] = '\0';

    reverse(temp);
    strcpy(res,temp);

}

void string_add(char *res, char *a, char *b)
{
    int i;
    int j;
    
    int carry;
    int pos;
    int sum;

    char temp[2002];

    carry = 0;
    pos = 0;

    i = strlen(a) - 1;
    j = strlen(b) - 1;

    while (i >= 0 || j >= 0 || carry)
    {
        sum = carry;
        if ( i >= 0)
        {
            sum += a[i] - '0';
            i--;
        }
        if (j >= 0)
        {
            sum += b[j] - '0';
            j--;
        }
        temp[pos] = sum % 10 + '0';
        carry = sum / 10;
        pos++;

    }
    temp[pos] = '\0';
    reverse(temp);
    strcpy(res,temp);

}

void    prod(char *res, char *a, char *b, int k)
{
    funcount++;

    int i;

    int a_len;
    int b_len;

    int max;
    int half_max;

    long long numa;
    long long numb;

    int zero1;
    int zero2;

    char *a1;
    char *a2;
    char *b1;
    char *b2;

    char *z2;
    char *z0;
    char *z1;
    char *abcd;
    char *temp;
    char *temp1;
    char *temp2;

    char *z2shift;
    char *z1shift;

    a_len = strlen(a);
    b_len = strlen(b);

    if ( a_len <= k && b_len <=k )
    {
        if ( a_len > 18 || b_len > 18)
        {
            simplemul(res,a,b);
        }
        else
        {
        numa = atoll(a);
        numb = atoll(b);
        sprintf(res,"%lld", numa * numb);
        }
        return ;
    }
    if (a_len > b_len)
        max = a_len;
    else
        max = b_len;
    half_max = max / 2;

    a1 = (char *)malloc(sizeof(char)*(half_max + 1));
    a2 = (char *)malloc(sizeof(char)*(half_max + 1));
    b1 = (char *)malloc(sizeof(char)*(half_max + 1));
    b2 = (char *)malloc(sizeof(char)*(half_max + 1));
    
    if ( a_len < half_max)
    {
        a1[0] = '0';
        a1[1] = '\0';
        strcpy(a2,a);
    }
    else
    {
    strncpy(a1,a,a_len - half_max);
    a1[a_len - half_max] = '\0';
    strcpy(a2,a + a_len - half_max);
    }
    if ( b_len < half_max)
    {
        strcpy(b1,"0");
        strcpy(b2,b);
    }
    else
    {
    strncpy(b1,b, b_len - half_max);
    b1[b_len - half_max] = '\0';
    strcpy(b2,b + b_len - half_max);
    }

    z0 = (char *)malloc(sizeof(char) * (2*max+1));
    z2 = (char *)malloc(sizeof(char) * (2*max+1));
    z1 = (char *)malloc(sizeof(char) * (2*max+1));
    abcd = (char *)malloc(sizeof(char) * (2*max+1));
    temp = (char *)malloc(sizeof(char) * (2*max+1));
    temp1 = (char *)malloc(sizeof(char) * (2*max+1));
    temp2 = (char *)malloc(sizeof(char) * (2*max+1));


    prod(z2,a1,b1,k);
    prod(z0,a2,b2,k);

    string_add(temp1,a1,a2);
    string_add(temp2,b1,b2);

    prod(abcd,temp1,temp2,k);

    string_sub(temp,abcd,z2);

    string_sub(z1,temp,z0);

    zero1 = half_max;
    zero2 = 2 * half_max;

    z2shift = (char *)malloc(sizeof(char) * (2*max + zero2+1));
    strcpy(z2shift,z2);

    i = 0;
    while ( i < zero2)
    {
        strcat(z2shift,"0");
        i++;
    }

    z1shift = (char *)malloc(sizeof(char) * (2*max + zero1 + 1));
    strcpy(z1shift,z1);
    i = 0;
    while (i < zero1)
    {
        strcat(z1shift,"0");
        i++;
    }

    string_add(temp2, z2shift, z1shift);
    string_add(res, temp2, z0);



}

int main(void)
{
    int k;
    char a[1001];
    char b[1001];
    char res[2002] = {0};

    scanf("%d",&k);

    scanf("%s",a);
    scanf("%s",b);

    prod(res, a, b, k);

    printf("%d\n",funcount);
    printf("%s",res);

    return (0);
}