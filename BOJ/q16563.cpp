#include <iostream>

const int LEN = 5e6 + 1;
int N, K, s[LEN], sp, f[30];

int main() {
	for (int i = 2; i < LEN; ++i) {
		if (s[i]) continue;
		for (int j = i; j < LEN; j += i)
			s[j] = i;
	}
	std::cin >> N;
	while (N--) {
		sp = 0;
		std::cin >> K;
		while (K > 1) {
			f[sp++] = s[K];
			K /= s[K];
		}
		for (int i = sp - 1; i >= 0; --i) std::cout << f[i] << ' ';
		std::cout << '\n';
	}
}