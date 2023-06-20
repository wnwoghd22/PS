#include <iostream>

const int LEN = 1'000'001;
bool sieve[LEN];

int main() {
	sieve[1] = 1;
	for (int i = 2; i < LEN; ++i) {
		if (sieve[i]) continue;
		for (int j = i << 1; j < LEN; j += i) sieve[j] = 1;
	}
	int T, N, C;
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		C = 0;
		for (int i = 2; i <= N >> 1; ++i) {
			if (!sieve[i] && !sieve[N - i])
				++C;
		}
		std::cout << C << '\n';
	}
}