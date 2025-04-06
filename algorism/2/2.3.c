#include <stdio.h>

typedef long long long_t;

long_t fun(long_t n) {
    if (n == 0)
        return 1;
    else
        return fun(n/2) + fun(n/2) + fun(n/2) + fun(n/2);
}

int main() {
    long_t n;
    scanf("%lld", &n);
    printf("%lld", fun(n));
    return 0;
}