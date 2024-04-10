#include <iostream>

const int LEN = 318138;

bool sieve[LEN];
int T, N, A[3001];

int main() {
	for (int i = 2, j = 0, k = 0; i < LEN; ++i) {
		if (sieve[i]) continue;
		if (!sieve[++k]) A[j++] = i;
		for (int p = i * 2; p < LEN; p += i)
			sieve[p] = 1;
	}
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		std::cout << A[N] << '\n';
	}
}