#include <iostream>

const int MOD = 1e9 + 7;
int N, dp[2][6];

int main() {
	std::cin >> N;
	dp[0][2] = dp[0][4] = 1;
	for (int i = 0; i < N - 1; ++i) {
		for (int j = 0; j < 6; ++j) dp[~i & 1][j] = 0;
		for (int j = 0; j < 3; ++j) {
			dp[~i & 1][(j + 5) % 3] += dp[i & 1][j];
			dp[~i & 1][(j + 1) % 3 + 3] += dp[i & 1][j];
			dp[~i & 1][(j + 5) % 3] %= MOD;
			dp[~i & 1][(j + 1) % 3 + 3] %= MOD;

			dp[~i & 1][(j + 5) % 3] += dp[i & 1][j + 3];
			dp[~i & 1][(j + 1) % 3 + 3] += dp[i & 1][j + 3];
			dp[~i & 1][(j + 5) % 3] %= MOD;
			dp[~i & 1][(j + 1) % 3 + 3] %= MOD;
		}
	}

	std::cout << dp[(N - 1) & 1][0];
}