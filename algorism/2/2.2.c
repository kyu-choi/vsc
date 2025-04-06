#include <stdio.h>
#include <math.h>

typedef long long long_t;

long_t fun(long_t n, long_t m, long_t p) {
    long_t i, j, k, cnt = 0;
    long long time;
    for (i=1; i<=2*n; i+=4)
        for (j=1; j<=2*m; j*=2)
            for (k=4*p; k>=1; k/=2)
                cnt++;

    time = ((n/2)+1) * (log2(2*m) + 1) * (log2(4*p) + 1);
    return (time);
}

int main(void) {    
    long_t n, m, p;
    scanf("%lld %lld %lld", &n, &m, &p);
    printf("%lld", fun(n, m, p));
    return 0;
}