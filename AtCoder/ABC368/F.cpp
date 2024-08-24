#include <iostream>

const int LEN = 1e5 + 1;
int N, A, sieve[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 2; i < LEN; ++i) {
		if (sieve[i]) continue;
		for (int j = i; j < LEN; j += i) {
			sieve[j] = i;
		}
	}
	int R = 0;
	while (N--) {
		std::cin >> A;
		int P = 0;
		while (A > 1) {
			A /= sieve[A];
			++P;
		}
		R ^= P;
	}
	std::cout << (R ? "Anna" : "Bruno");
}