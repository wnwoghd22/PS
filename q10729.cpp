#include <iostream>

typedef long long ll;
const int LEN = 1'001'001;
const ll MOD = 1e9 + 7;

ll power(ll a, ll b) {
	if (b == 1) return a;
	ll p = power(a, b >> 1);
	p = (p * p) % MOD;
	if (b & 1) p = p * a % MOD;
	return p;
}

ll N, K, inv, M, l, r, S, dp[LEN];

int main() {
	std::cin >> N >> K >> M;
	l = M, r = M + K;
	inv = power(K + 1, MOD - 2);
	S = dp[M] = 1;
	if (M < N) {
		for (int i = 0; i < N; ++i)
			std::cout << dp[i] << '\n';
		return 0;
	}
	while (r >= N) {
		dp[r - N] = S * inv % MOD;
		S = (S - dp[r--] + MOD) % MOD;
		if (l > N)
			S = (S + dp[--l]) % MOD;
	}
	for (int i = 0; i < N; ++i)
		std::cout << dp[i] << '\n';
}