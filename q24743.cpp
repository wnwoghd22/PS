#include <iostream>

unsigned int N, b0, b1, A;
char S[16];

int to_bit(const char* s) {
	unsigned n, ret = 0;
	for (int i = -1, j = 3; j >= 0; --j) {
		++i;
		for (n = 0; s[i] && s[i] != '.'; ++i) 
			n = n * 10 + s[i] - '0';
		ret |= n << (8 * j);
	}
	return ret;
}

int main() {
	std::cin >> N;
	b0 = b1 = -1;
	for (int i = 0; i < N; ++i) {
		std::cin >> S;
		A = to_bit(S);

		// printf("%x\n", A);

		b0 &= ~A;
		b1 &= A;
	}

	unsigned int bit = ~(b0 | b1);

	if (!bit || bit & 1 << 31) std::cout << 32;
	else {
		for (int i = 30; i >= 0; --i) {
			if (bit & 1 << i) {
				std::cout << 31 - i;
				break;
			}
		}
	}
}