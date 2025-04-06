#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int funcount = 0;

void simplemul(char *res, char *a, char *b)
{
    int i, j, pos;
    int a_len, b_len, size;
    int *result;

    a_len = strlen(a);
    b_len = strlen(b);
    size = a_len + b_len;
    result = (int *)calloc(size, sizeof(int));  // calloc 사용하여 0으로 초기화

    for (i = a_len - 1; i >= 0; i--) {
        for (j = b_len - 1; j >= 0; j--) {
            result[i + j + 1] += (a[i]-'0')*(b[j]-'0');
        }
    }
    for (i = size - 1; i > 0; i--) {
        result[i-1] += result[i] / 10;
        result[i] %= 10;
    }
    i = 0;
    while (i < size - 1 && result[i] == 0)
        i++;
    pos = 0;
    while (i < size) {
        res[pos++] = result[i++] + '0';
    }
    res[pos] = '\0';
    free(result);
}

void reverse(char *src)
{
    int i, size;
    char temp;
    size = strlen(src);
    for (i = 0; i < size / 2; i++) {
        temp = src[i];
        src[i] = src[size - 1 - i];
        src[size - 1 - i] = temp;
    }
}

void string_sub(char *res, char *a, char *b)
{
    int i, j, borrow = 0, pos = 0, sub;
    char temp[2002];

    i = strlen(a) - 1;
    j = strlen(b) - 1;
    while (i >= 0) {
        sub = a[i] - '0' - borrow;
        if (j >= 0) {
            sub -= b[j] - '0';
            j--;
        }
        if (sub < 0) {
            borrow = 1;
            sub += 10;
        } else {
            borrow = 0;
        }
        temp[pos++] = sub + '0';
        i--;
    }
    while (pos > 1 && temp[pos - 1] == '0')
        pos--;
    temp[pos] = '\0';
    reverse(temp);
    strcpy(res, temp);
}

void string_add(char *res, char *a, char *b)
{
    int i, j, carry = 0, pos = 0, sum;
    char temp[2002];

    i = strlen(a) - 1;
    j = strlen(b) - 1;
    while (i >= 0 || j >= 0 || carry) {
        sum = carry;
        if (i >= 0)
            sum += a[i--] - '0';
        if (j >= 0)
            sum += b[j--] - '0';
        temp[pos++] = (sum % 10) + '0';
        carry = sum / 10;
    }
    temp[pos] = '\0';
    reverse(temp);
    strcpy(res, temp);
}

void prod(char *res, char *a, char *b, int k)
{
    funcount++;
    int i;
    int a_len = strlen(a);
    int b_len = strlen(b);
    int max, half_max;
    long long numa, numb;

    char *a1, *a2, *b1, *b2;
    char *z2, *z0, *z1, *abcd, *temp, *temp1, *temp2;
    char *z2shift, *z1shift;

    if (a_len <= k || b_len <= k) {
        if (a_len > 18 || b_len > 18) {
            simplemul(res, a, b);
        } else {
            numa = atoll(a);
            numb = atoll(b);
            sprintf(res, "%lld", numa * numb);
        }
        return;
    }

    max = (a_len > b_len) ? a_len : b_len;
    half_max = max / 2;

    a1 = (char *)malloc(sizeof(char) * (half_max + 1));
    a2 = (char *)malloc(sizeof(char) * (half_max + 1));
    b1 = (char *)malloc(sizeof(char) * (half_max + 1));
    b2 = (char *)malloc(sizeof(char) * (half_max + 1));
    
    if (a_len < half_max) {
        strcpy(a1, "0");
        strcpy(a2, a);
    } else {
        strncpy(a1, a, a_len - half_max);
        a1[a_len - half_max] = '\0';
        strcpy(a2, a + a_len - half_max);
    }
    if (b_len < half_max) {
        strcpy(b1, "0");
        strcpy(b2, b);
    } else {
        strncpy(b1, b, b_len - half_max);
        b1[b_len - half_max] = '\0';
        strcpy(b2, b + b_len - half_max);
    }

    z0 = (char *)malloc(sizeof(char) * (2 * max + 1));
    z2 = (char *)malloc(sizeof(char) * (2 * max + 1));
    z1 = (char *)malloc(sizeof(char) * (2 * max + 1));
    abcd = (char *)malloc(sizeof(char) * (2 * max + 1));
    temp = (char *)malloc(sizeof(char) * (2 * max + 1));
    temp1 = (char *)malloc(sizeof(char) * (2 * max + 1));
    temp2 = (char *)malloc(sizeof(char) * (2 * max + 1));

    prod(z2, a1, b1, k);
    prod(z0, a2, b2, k);

    string_add(temp1, a1, a2);
    string_add(temp2, b1, b2);
    prod(abcd, temp1, temp2, k);

    string_sub(temp, abcd, z2);
    string_sub(z1, temp, z0);

    int zero1 = half_max;
    int zero2 = 2 * half_max;

    z2shift = (char *)malloc(sizeof(char) * (2 * max + zero2 + 1));
    strcpy(z2shift, z2);
    for (i = 0; i < zero2; i++)
        strcat(z2shift, "0");

    z1shift = (char *)malloc(sizeof(char) * (2 * max + zero1 + 1));
    strcpy(z1shift, z1);
    for (i = 0; i < zero1; i++)
        strcat(z1shift, "0");

    string_add(temp2, z2shift, z1shift);
    string_add(res, temp2, z0);

    free(a1); free(a2); free(b1); free(b2);
    free(z0); free(z1); free(z2); free(abcd);
    free(temp); free(temp1); free(temp2);
    free(z2shift); free(z1shift);
}

int main(void)
{
    int k;
    char a[1001], b[1001];
    char res[2002] = {0};

    scanf("%d", &k);
    scanf("%s", a);
    scanf("%s", b);

    prod(res, a, b, k);

    printf("%d\n", funcount);
    printf("%s", res);

    return 0;
}
