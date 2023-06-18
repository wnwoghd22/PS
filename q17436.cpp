#include <iostream>

typedef long long ll;

int N, p[10];
ll M, K;

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> p[i];

	for (int i = 1; i < 1 << N; ++i) {
		ll den = 1, s = 0;
		for (int j = 0; j < N; ++j) {
			if (i & (1 << j))
				den *= p[j], ++s;
		}
		if (s & 1) K += M / den;
		else K -= M / den;
	}
	std::cout << K;
}