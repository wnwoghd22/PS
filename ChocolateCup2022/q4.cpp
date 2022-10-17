#include <iostream>

typedef long long int ll;
const int LEN = 100'001;
const ll MOD = 1'000'000'007;

ll dp[LEN][3];

int main() {
	dp[0][0] = 1;
	for (int i = 1; i < LEN; ++i) {
		if (i & 1) dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % MOD;
		else dp[i][0] = (dp[i - 1][1] * 2 + dp[i - 2][0]) % MOD, dp[i][2] = dp[i - 1][1];
	}
	ll T, N, R, C;

	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> T;
	while (T--) {
		std::cin >> N >> R >> C;
		if (R & 1) std::cout << (dp[C][1] * dp[N - C][0] % MOD + dp[N - C + 1][1] * dp[C - 1][0] % MOD - dp[C - 1][0] * dp[N - C][0] % MOD + MOD) % MOD << '\n';
		else std::cout << (dp[C][2] * dp[N - C + 1][2] * 2) % MOD << '\n';
	}
}