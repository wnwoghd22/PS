#include <iostream>

typedef long long ll;
const ll MOD = 1e9 + 7;
const int F = 5;
const int B = 11;
ll n, m, dp[20][2][22][22]; // n, floor, max len, current len

int main() {
	std::cin >> n >> m;
	dp[0][0][1][1] = F;
	dp[0][1][1][1] = B;
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int k = 1; k <= m; ++k) {
				// F -> B
				dp[i + 1][1][j + (k >= j)][k + 1] += dp[i][0][j][k] * B % MOD;
				dp[i + 1][1][j + (k >= j)][k + 1] %= MOD;
				
				// F -> F
				dp[i + 1][0][j][1] += dp[i][0][j][k] * F % MOD;
				dp[i + 1][0][j][1] %= MOD;
			}
		}
		for (int j = 1; j <= m; ++j) {
			for (int k = 1; k <= m; ++k) {
				// B -> F
				dp[i + 1][0][j + (k >= j)][k + 1] += dp[i][1][j][k] * F % MOD;
				dp[i + 1][0][j + (k >= j)][k + 1] %= MOD;

				// B -> B
				dp[i + 1][1][j][1] += dp[i][1][j][k] * B % MOD;
				dp[i + 1][1][j][1] %= MOD;
			}
		}
	}
	ll result = 0;
	for (int i = 0; i < 2; ++i)
		for (int j = 1; j <= m; ++j)
			result += dp[n - 1][i][m][j], result %= MOD;
	std::cout << result;
}