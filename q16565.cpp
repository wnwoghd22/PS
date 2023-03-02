#include <iostream>

const int MOD = 10'007;
int N, result, dp[53][53];

int main() {
	for (int i = 0, j; i < 53; ++i)
		for (dp[i][0] = j = 1; j <= i; ++j)
			dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;

	std::cin >> N;
	for (int i = 1, j = 1; i <= N >> 2; ++i, j *= -1) {
		result += j * dp[13][i] * dp[52 - (i << 2)][N - (i << 2)];
		result = (result + MOD) % MOD;
	}
	std::cout << result;
}