#include <iostream>
#include <algorithm>

typedef long long ll;

ll T, N, K;

bool is_prime(ll x) {
	if (x <= 1) return 0;
	for (ll p = 2; p * p <= x; ++p) {
		if (x % p == 0) return 0;
	}
	return 1;
}

int main() {
	std::cin >> T;
	while (T--) {
		std::cin >> N;
		for (K = N; !is_prime(K); ++K);
		std::cout << K << '\n';
	}
}