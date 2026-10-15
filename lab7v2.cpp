#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <iostream>

#define BITS 8     // 8, 16, 32 или 64

#if BITS == 8
typedef uint8_t  T;
#define FMT_BITS 8
#elif BITS == 16
typedef uint16_t T;
#define FMT_BITS 16
#elif BITS == 32
typedef uint32_t T;
#define FMT_BITS 32
#elif BITS == 64
typedef uint64_t T;
#define FMT_BITS 64
#endif

void printbin(T);
T process(T, int, int);

int main() {
	unsigned long long in;
	unsigned long long ubound = pow(2, FMT_BITS) - 1;
	T x, res;
	int p, n;
	
	std::cout << "enter the number? it MUST be between 0 and " << ubound <<": ";
	std::cin >> in;
	if (in > ubound) {
		for (;;) {
			std::cout << "it MUST be between 0 and " << ubound << ": ";
			std::cin >> p;
			if (in <= ubound)
				break;
		}
	}
	x = (T)in;
	std::cout << "your number in binary: \n";
	printbin(x);
	std::cout << "enter the position p it must be between 0 and " << FMT_BITS - 1 << ": ";
	std::cin >> p;
	if (p < 0 || p >= FMT_BITS) {
		for (;;) {
			std::cout << "it MUST be between 0 and " << FMT_BITS - 1 << ": ";
			std::cin >> p;
			if (p >= 0 && p < FMT_BITS)
				break;
		}
	}
	std::cout << "enter the number n it must be between 0 and " << p << ": ";
	std::cin >> n;
	if (n < 0 || n > p) {
		for (;;) {
			std::cout << "it MUST be between 0 and " << p << ": ";
			std::cin >> n;
			if (n >= 0 && n <= p)
				break;
		}
	}
	res = process(x, n, p);
	std::cout << "original input: \n";
	std::cout << std::dec << (unsigned)x << " 0x" << std::hex << (unsigned)x << " ";
	printbin(x);
	std::cout << "result: \n";
	std::cout << std::dec << (unsigned)res << " 0x" << std::hex << (unsigned)res << " ";
	printbin(res);

	
	return 0;
}

void printbin(T x) {
	T mask = T(1) << (FMT_BITS - 1);
	for (int i = 0; i < FMT_BITS; i++) {
		std::cout << ((x & mask) ? '1' : '0');
		mask >>= 1;
	}
	std::cout << '\n';
}

T process(T x, int n, int p) {
	T ones = ((T)1 << n) - 1;      
	T mask = ones << (p - n);      
	return (x & ~mask);
}