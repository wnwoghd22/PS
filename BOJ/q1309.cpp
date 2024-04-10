#include <iostream>

const int LEN = 1e5 + 1;
const int MOD = 9901;

int N, dp[LEN][3];

int main() {
	std::cin >> N;
	dp[0][0] = 1;
	for (int i = 1; i <= N; ++i) {
		dp[i][0] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][2]) % MOD;
		dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % MOD;
		dp[i][2] = (dp[i - 1][0] + dp[i - 1][1]) % MOD;
	}
	std::cout << (dp[N][0] + dp[N][1] + dp[N][2]) % MOD;
}