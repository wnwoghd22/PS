#include <iostream>

typedef long long int ll;
const int LEN = 1'000'001;
ll sieve[LEN], phi[LEN], S[LEN];

int main() {
	for (ll i = 1; i < LEN; ++i) phi[i] = i;
	for (ll p = 2; p < LEN; ++p) {
		if (sieve[p]) continue;
		phi[p] /= p; phi[p] *= (p - 1);
		for (ll i = p * 2; i < LEN; i += p) {
			sieve[i] = true;
			phi[i] /= p; phi[i] *= (p - 1);
		}
	}
	for (ll i = 1; i < LEN; ++i) S[i] = S[i - 1] + phi[i];
	int t, T;
	std::cin >> T;
	for (t = 1; t <= T; ++t) {
		int a, b;
		std::cin >> a >> b;
		std::cout << '#' << t << ' ' << S[b] - S[a - 1] << '\n';
	}
}