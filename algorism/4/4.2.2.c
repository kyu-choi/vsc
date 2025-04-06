#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prod() 함수 호출 횟수를 세는 전역 변수
int prod_call_count = 0;

// 표준 곱셈으로 전환하는 임계값 (입력으로 설정됨)
int THRESHOLD;

// 큰 정수를 표현하는 구조체
typedef struct {
    int* digits;  // 자릿수를 저장하는 배열
    int size;     // 자릿수 개수
} LargeInteger;

// 함수 프로토타입
void initLargeInteger(LargeInteger* num, int size);
void freeLargeInteger(LargeInteger* num);
void copyLargeInteger(LargeInteger* dest, const LargeInteger* src);
void div_by_exp(const LargeInteger* num, int exp, LargeInteger* result);
void rem_by_exp(const LargeInteger* num, int exp, LargeInteger* result);
void pow_by_exp(const LargeInteger* num, int exp, LargeInteger* result);
void lmult(const LargeInteger* u, const LargeInteger* v, LargeInteger* result);
void ladd(const LargeInteger* a, const LargeInteger* b, LargeInteger* result);
void prod(const LargeInteger* u, const LargeInteger* v, LargeInteger* r);
void readLargeInteger(LargeInteger* num, const char* str);
void printLargeInteger(const LargeInteger* num);

// 주어진 크기로 큰 정수 초기화
void initLargeInteger(LargeInteger* num, int size) {
    num->size = size;
    if (size > 0) {
        num->digits = (int*)calloc(size, sizeof(int));
    } else {
        num->digits = NULL;
    }
}

// 큰 정수에 할당된 메모리 해제
void freeLargeInteger(LargeInteger* num) {
    if (num->digits != NULL) {
        free(num->digits);
        num->digits = NULL;
    }
    num->size = 0;
}

// 소스 큰 정수를 대상에 복사
void copyLargeInteger(LargeInteger* dest, const LargeInteger* src) {
    freeLargeInteger(dest);
    initLargeInteger(dest, src->size);
    
    for (int i = 0; i < src->size; i++) {
        dest->digits[i] = src->digits[i];
    }
}

// 큰 정수를 10^exp로 나눔 (상위 자릿수 가져오기)
void div_by_exp(const LargeInteger* num, int exp, LargeInteger* result) {
    if (num->size <= exp) {
        // 숫자의 자릿수가 exp보다 적으면 결과는 0
        initLargeInteger(result, 0);
        return;
    }
    
    // 선행 0을 제거한 후의 실제 크기 찾기
    int actualSize = num->size - exp;
    while (actualSize > 0 && num->digits[actualSize + exp - 1] == 0) {
        actualSize--;
    }
    
    if (actualSize <= 0) {
        initLargeInteger(result, 0);
        return;
    }
    
    initLargeInteger(result, actualSize);
    for (int i = 0; i < actualSize; i++) {
        result->digits[i] = num->digits[i + exp];
    }
}

// 10^exp로 나눈 나머지 구하기 (하위 자릿수 가져오기)
void rem_by_exp(const LargeInteger* num, int exp, LargeInteger* result) {
    int resultSize = (num->size < exp) ? num->size : exp;
    
    // 선행 0 건너뛰기
    while (resultSize > 0 && resultSize < num->size && num->digits[resultSize - 1] == 0) {
        resultSize--;
    }
    
    if (resultSize <= 0) {
        initLargeInteger(result, 0);
        return;
    }
    
    initLargeInteger(result, resultSize);
    
    for (int i = 0; i < resultSize; i++) {
        result->digits[i] = num->digits[i];
    }
}

// 큰 정수에 10^exp 곱하기 (왼쪽으로 이동)
void pow_by_exp(const LargeInteger* num, int exp, LargeInteger* result) {
    if (num->size == 0) {
        initLargeInteger(result, 0);
        return;
    }
    
    // 실제 크기 찾기 (선행 0 무시)
    int actualSize = num->size;
    while (actualSize > 0 && num->digits[actualSize - 1] == 0) {
        actualSize--;
    }
    
    if (actualSize == 0) {
        initLargeInteger(result, 0);
        return;
    }
    
    initLargeInteger(result, actualSize + exp);
    
    // 하위 위치를 0으로 채우기
    for (int i = 0; i < exp; i++) {
        result->digits[i] = 0;
    }
    
    // 원래 자릿수를 상위 위치에 복사
    for (int i = 0; i < actualSize; i++) {
        result->digits[i + exp] = num->digits[i];
    }
}

// 작은 숫자에 대한 표준 곱셈
void lmult(const LargeInteger* u, const LargeInteger* v, LargeInteger* result) {
    if (u->size == 0 || v->size == 0) {
        initLargeInteger(result, 0);
        return;
    }
    
    // 결과를 0으로 초기화
    initLargeInteger(result, u->size + v->size);
    
    // 자릿수별로 곱셈 수행
    for (int i = 0; i < u->size; i++) {
        for (int j = 0; j < v->size; j++) {
            result->digits[i + j] += u->digits[i] * v->digits[j];
        }
    }
    
    // 올림수 처리
    int carry = 0;
    for (int i = 0; i < result->size; i++) {
        result->digits[i] += carry;
        carry = result->digits[i] / 10;
        result->digits[i] %= 10;
    }
    
    // 선행 0 제거
    int actualSize = result->size;
    while (actualSize > 0 && result->digits[actualSize - 1] == 0) {
        actualSize--;
    }
    
    if (actualSize < result->size) {
        int* temp = (int*)realloc(result->digits, actualSize * sizeof(int));
        if (temp != NULL || actualSize == 0) {
            result->digits = temp;
            result->size = actualSize;
        }
    }
}

// 두 큰 정수 더하기
void ladd(const LargeInteger* a, const LargeInteger* b, LargeInteger* result) {
    int maxSize = (a->size > b->size) ? a->size : b->size;
    initLargeInteger(result, maxSize + 1);  // +1은 잠재적 올림수를 위함
    
    int carry = 0;
    for (int i = 0; i < maxSize; i++) {
        int digitA = (i < a->size) ? a->digits[i] : 0;
        int digitB = (i < b->size) ? b->digits[i] : 0;
        
        int sum = digitA + digitB + carry;
        result->digits[i] = sum % 10;
        carry = sum / 10;
    }
    
    if (carry > 0) {
        result->digits[maxSize] = carry;
    } else {
        // 올림수가 없으면 크기 조정
        int* temp = (int*)realloc(result->digits, maxSize * sizeof(int));
        if (temp != NULL || maxSize == 0) {
            result->digits = temp;
            result->size = maxSize;
        }
    }
    
    // 선행 0 제거
    int actualSize = result->size;
    while (actualSize > 0 && result->digits[actualSize - 1] == 0) {
        actualSize--;
    }
    
    if (actualSize == 0) {
        // 결과가 0
        freeLargeInteger(result);
        initLargeInteger(result, 0);
    } else if (actualSize < result->size) {
        int* temp = (int*)realloc(result->digits, actualSize * sizeof(int));
        if (temp != NULL || actualSize == 0) {
            result->digits = temp;
            result->size = actualSize;
        }
    }
}

// 카라추바 알고리즘을 사용한 재귀적 곱셈
void prod(const LargeInteger* u, const LargeInteger* v, LargeInteger* r) {
    // 호출 카운터 증가
    prod_call_count++;
    
    LargeInteger x, y, w, z;
    LargeInteger t1, t2, t3, t4, t5, t6, t7, t8;
    
    // 모든 임시 변수 초기화
    initLargeInteger(&x, 0);
    initLargeInteger(&y, 0);
    initLargeInteger(&w, 0);
    initLargeInteger(&z, 0);
    initLargeInteger(&t1, 0);
    initLargeInteger(&t2, 0);
    initLargeInteger(&t3, 0);
    initLargeInteger(&t4, 0);
    initLargeInteger(&t5, 0);
    initLargeInteger(&t6, 0);
    initLargeInteger(&t7, 0);
    initLargeInteger(&t8, 0);
    
    int n = (u->size > v->size) ? u->size : v->size;
    
    if (u->size == 0 || v->size == 0) {
        initLargeInteger(r, 0);
    } else if (n <= THRESHOLD) {
        lmult(u, v, r);
    } else {
        int m = n / 2;
        
        // u를 x와 y로 분할
        div_by_exp(u, m, &x);  // x = u / 10^m
        rem_by_exp(u, m, &y);  // y = u % 10^m
        
        // v를 w와 z로 분할
        div_by_exp(v, m, &w);  // w = v / 10^m
        rem_by_exp(v, m, &z);  // z = v % 10^m
        
        // t2 <- prod(x,w) * 10^(2*m)
        prod(&x, &w, &t1);      // t1 = x * w
        pow_by_exp(&t1, 2 * m, &t2);  // t2 = t1 * 10^(2*m)
        
        // t6 <- (prod(x,z) + prod(w,y)) * 10^m
        prod(&x, &z, &t3);      // t3 = x * z
        prod(&w, &y, &t4);      // t4 = w * y
        ladd(&t3, &t4, &t5);    // t5 = t3 + t4
        pow_by_exp(&t5, m, &t6);// t6 = t5 * 10^m
        
        // r <- t2 + t6 + prod(y, z)
        prod(&y, &z, &t7);      // t7 = y * z
        ladd(&t2, &t6, &t8);    // t8 = t2 + t6
        ladd(&t8, &t7, r);      // r = t8 + t7
    }
    
    // 모든 임시 변수 메모리 해제
    freeLargeInteger(&x);
    freeLargeInteger(&y);
    freeLargeInteger(&w);
    freeLargeInteger(&z);
    freeLargeInteger(&t1);
    freeLargeInteger(&t2);
    freeLargeInteger(&t3);
    freeLargeInteger(&t4);
    freeLargeInteger(&t5);
    freeLargeInteger(&t6);
    freeLargeInteger(&t7);
    freeLargeInteger(&t8);
}

// 문자열에서 큰 정수 읽기
void readLargeInteger(LargeInteger* num, const char* str) {
    int len = strlen(str);
    initLargeInteger(num, len);
    
    for (int i = 0; i < len; i++) {
        num->digits[len - 1 - i] = str[i] - '0';
    }
    
    // 선행 0 제거
    int actualSize = num->size;
    while (actualSize > 0 && num->digits[actualSize - 1] == 0) {
        actualSize--;
    }
    
    if (actualSize == 0) {
        // 숫자가 0
        freeLargeInteger(num);
        initLargeInteger(num, 0);
    } else if (actualSize < num->size) {
        int* temp = (int*)realloc(num->digits, actualSize * sizeof(int));
        if (temp != NULL || actualSize == 0) {
            num->digits = temp;
            num->size = actualSize;
        }
    }
}

// 큰 정수 출력
void printLargeInteger(const LargeInteger* num) {
    if (num->size == 0) {
        printf("0");
        return;
    }
    
    for (int i = num->size - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
}

int main() {
    char buffer[1000001];
    LargeInteger A, B, C;
    
    // 큰 정수 초기화
    initLargeInteger(&A, 0);
    initLargeInteger(&B, 0);
    initLargeInteger(&C, 0);
    
    // 임계값 읽기
    scanf("%d", &THRESHOLD);
    
    // 정수 A와 B 읽기
    scanf("%s", buffer);
    readLargeInteger(&A, buffer);
    
    scanf("%s", buffer);
    readLargeInteger(&B, buffer);
    
    // 곱셈 전 호출 카운터 초기화
    prod_call_count = 0;
    
    // 곱셈 수행
    prod(&A, &B, &C);
    
    // prod() 호출 횟수 출력
    printf("%d\n", prod_call_count);
    
    // 곱셈 결과 출력
    printLargeInteger(&C);
    printf("\n");
    
    // 메모리 해제
    freeLargeInteger(&A);
    freeLargeInteger(&B);
    freeLargeInteger(&C);
    
    return 0;
}