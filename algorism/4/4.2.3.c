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
    result = (int *)calloc(size, sizeof(int));

    i = a_len - 1;
    while (i >= 0)
    {
        j = b_len - 1;
        while (j >= 0)
        {
            result[i + j + 1] += (a[i] - '0') * (b[j] - '0');
            j--;
        }
        i--;
    }

    i = size - 1;
    while (i > 0)
    {
        result[i - 1] += result[i] / 10;
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
    free(result);
}

void reverse(char *src)
{
    int i;
    int size;

    char temp;

    i = 0;
    size = strlen(src);
    while (i < size / 2)
    {
        temp = src[i];
        src[i] = src[size - 1 - i];
        src[size - 1 - i] = temp;
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

    while (i >= 0)
    {
        sub = a[i] - '0' - borrow;
        if (j >= 0)
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

    while (pos > 1 && temp[pos - 1] == '0')
        pos--;

    temp[pos] = '\0';

    reverse(temp);
    strcpy(res, temp);
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
        if (i >= 0)
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
    strcpy(res, temp);
}

// k가 분할 정복의 임계값
void prod(char *res, char *a, char *b, int k)
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

    // 문자열 길이가 k 이하이면 단순 곱셈 수행
    if (a_len <= k || b_len <= k)
    {
        if (a_len > 18 || b_len > 18)
        {
            simplemul(res, a, b);
        }
        else
        {
            numa = atoll(a);
            numb = atoll(b);
            sprintf(res, "%lld", numa * numb);
        }
        return;
    }

    // 두 입력 중 더 긴 길이 선택
    max = (a_len > b_len) ? a_len : b_len;
    half_max = max / 2;

    // 메모리 할당
    a1 = (char *)malloc(sizeof(char) * (max + 1));
    a2 = (char *)malloc(sizeof(char) * (max + 1));
    b1 = (char *)malloc(sizeof(char) * (max + 1));
    b2 = (char *)malloc(sizeof(char) * (max + 1));

    // a를 a1과 a2로 분할
    if (a_len <= half_max)
    {
        strcpy(a1, "0");
        strcpy(a2, a);
    }
    else
    {
        strncpy(a1, a, a_len - half_max);
        a1[a_len - half_max] = '\0';
        strcpy(a2, a + a_len - half_max);
    }

    // b를 b1과 b2로 분할
    if (b_len <= half_max)
    {
        strcpy(b1, "0");
        strcpy(b2, b);
    }
    else
    {
        strncpy(b1, b, b_len - half_max);
        b1[b_len - half_max] = '\0';
        strcpy(b2, b + b_len - half_max);
    }

    // 필요한 메모리 할당
    z0 = (char *)malloc(sizeof(char) * (2 * max + 1));
    z2 = (char *)malloc(sizeof(char) * (2 * max + 1));
    z1 = (char *)malloc(sizeof(char) * (2 * max + 1));
    abcd = (char *)malloc(sizeof(char) * (2 * max + 1));
    temp = (char *)malloc(sizeof(char) * (2 * max + 1));
    temp1 = (char *)malloc(sizeof(char) * (2 * max + 1));
    temp2 = (char *)malloc(sizeof(char) * (2 * max + 1));

    // 재귀적으로 곱셈 계산
    prod(z2, a1, b1, k);  // z2 = a1 * b1
    prod(z0, a2, b2, k);  // z0 = a2 * b2

    string_add(temp1, a1, a2);  // temp1 = a1 + a2
    string_add(temp2, b1, b2);  // temp2 = b1 + b2

    prod(abcd, temp1, temp2, k);  // abcd = (a1 + a2) * (b1 + b2)

    string_sub(temp, abcd, z2);  // temp = abcd - z2
    string_sub(z1, temp, z0);    // z1 = temp - z0 = (a1 + a2) * (b1 + b2) - a1*b1 - a2*b2 = a1*b2 + a2*b1

    zero1 = half_max;
    zero2 = 2 * half_max;

    // z2에 10^(2*half_max) 곱하기
    z2shift = (char *)malloc(sizeof(char) * (2 * max + zero2 + 1));
    strcpy(z2shift, z2);
    i = 0;
    while (i < zero2)
    {
        strcat(z2shift, "0");
        i++;
    }

    // z1에 10^half_max 곱하기
    z1shift = (char *)malloc(sizeof(char) * (2 * max + zero1 + 1));
    strcpy(z1shift, z1);
    i = 0;
    while (i < zero1)
    {
        strcat(z1shift, "0");
        i++;
    }

    // 최종 결과 계산: res = z2 * 10^(2*m) + z1 * 10^m + z0
    string_add(temp2, z2shift, z1shift);
    string_add(res, temp2, z0);

    // 메모리 해제
    free(a1);
    free(a2);
    free(b1);
    free(b2);
    free(z0);
    free(z2);
    free(z1);
    free(abcd);
    free(temp);
    free(temp1);
    free(temp2);
    free(z2shift);
    free(z1shift);
}

int main(void)
{
    int k;
    char a[1001];
    char b[1001];
    char res[2002] = {0};

    // 입력 받기
    scanf("%d", &k);
    scanf("%s", a);
    scanf("%s", b);

    // 함수 호출 횟수 초기화
    funcount = 0;
    
    // 곱셈 수행
    prod(res, a, b, k);

    // 결과 출력
    printf("%d\n", funcount);
    printf("%s\n", res);

    return (0);
}