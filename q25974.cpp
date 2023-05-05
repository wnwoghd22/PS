#include <iostream>

typedef long long ll;
const ll MOD = 1e9 + 7;
const int LEN = 1002;

ll N, P;
ll C[LEN][LEN], S[LEN];

ll power(ll x, ll p) {
	if (p == 1) return x;
	ll k = power(x, p >> 1);
	k = k * k % MOD;
	if (p & 1) k = k * x % MOD;
	return k;
}

int main() {
	std::cin >> N >> P;
	for (int i = 0; i <= P + 1; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}
	S[0] = N;
	for (int i = 1, n = (N + 1) * (N + 1) % MOD; i <= P; ++i, n = n * (N + 1) % MOD) {
		S[i] = n - 1;
		for (int j = 0; j < i; ++j) {
			S[i] -= C[i + 1][j] * S[j];
			S[i] = (S[i] + MOD * MOD) % MOD;
		}
		S[i] *= power(i + 1, MOD - 2);
		S[i] %= MOD;
	}
	std::cout << S[P];
}