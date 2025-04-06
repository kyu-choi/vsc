#include <stdio.h>

typedef long long long_t;

long_t fun(long_t n) {
    long_t i, j, cnt = 0;
    long long time;
    for (i=1; i<=4*n; i+=2)
        for (j=n; j>=1; j--)
            cnt++;


    time = 2* n * n;
    return (time);

}

int main(void) {
    long_t n;
    scanf("%lld", &n);
    printf("%lld", fun(n));
    return 0;
}