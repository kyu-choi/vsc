#include <stdio.h>

void hanoi(int n, char src, char via, char dst) {
   
    if (n == 1) {
        printf("%c -> %c\n", src, dst);
    }
    else {
        hanoi(n-1, src, dst, via);
        hanoi(1, src, via, dst);
        hanoi(n-1, via, src, dst);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    return 0;
}