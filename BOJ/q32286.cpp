#include <iostream>

typedef long long ll;
const ll MOD = 1e9 + 7;

ll k, p, q, r, s;
ll S[51];

int main() {
	std::cin >> k >> p >> q >> r >> s >> S[1];
	for (ll i = 2, n = 2; i <= k; ++i, n <<= 1) {
		S[i] = (S[i - 1] * (p + r) % MOD + (n - 1) * (s + q) % MOD + S[1]) % MOD;
	}
	std::cout << S[k];
}