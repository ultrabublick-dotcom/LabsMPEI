#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>

#define BITS 32      // 8, 16, 32 или 64

#if BITS == 8
typedef uint8_t  T;
#define FMT_D "%" PRIu8
#define FMT_X "%" PRIx8
#define FMT_BITS 8
#elif BITS == 16
typedef uint16_t T;
#define FMT_D "%" PRIu16
#define FMT_X "%" PRIx16
#define FMT_BITS 16
#elif BITS == 32
typedef uint32_t T;
#define FMT_D "%" PRIu32
#define FMT_X "%" PRIx32
#define FMT_BITS 32
#elif BITS == 64
typedef uint64_t T;
#define FMT_D "%" PRIu64
#define FMT_X "%" PRIx64
#define FMT_BITS 64
#endif

// Вывод в двоичной системе
void printBinary(T x) {
    T mask = (T)1 << (FMT_BITS - 1);      // старший бит
    for (int i = 0; i < FMT_BITS; i++) {
        putchar((x & mask) ? '1' : '0');
        mask >>= 1;
    }
}

// Основная функция из задания
int process(T x, int p, T* result) {
    if (p < 0 || p >= FMT_BITS) {
        printf("Ошибка: p должно быть в диапазоне [0, %d]\n", FMT_BITS - 1);
        return 0;
    }
    *result = x ^ ~((T)1 << p);   // <-- вся работа тут: одна операция
    return 1;
}

int main() {
    unsigned long long input;
    int p;
    T x, res;

    printf("Введите число x (0..%llu): ", (unsigned long long)~(T)0);
    if (scanf("%llu", &input) != 1) return 1;
    x = (T)input;

    printf("Введите номер бита p (0..%d): ", FMT_BITS - 1);
    if (scanf("%d", &p) != 1) return 1;

    printf("Исходное:   ");
    printBinary(x);
    std::cout << " "<<std::dec << (unsigned)x
        << "  0x" << std::hex << (unsigned)x
        << std::dec << "\n";
    //printf("  " FMT_D "  0x" FMT_X "\n", x, x);

    if (process(x, p, &res)) {
        printf("Результат: ");
        printBinary(res);
        printf("  " FMT_D "  0x" FMT_X "\n", res, res);
    }
    return 0;
}