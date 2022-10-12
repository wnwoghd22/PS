#include <iostream>

int N;
int dp[17][17][3];
int map[17][17];

int F() {
	dp[1][2][0] = 1;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (map[i][j]) continue;

			dp[i][j][0] += dp[i][j - 1][0] + dp[i][j - 1][2];
			dp[i][j][1] += dp[i - 1][j][1] + dp[i - 1][j][2];

			if (map[i - 1][j] || map[i][j - 1]) continue;

			dp[i][j][2] += dp[i - 1][j - 1][0] + dp[i - 1][j - 1][1] + dp[i - 1][j - 1][2];
		}
	}
	return dp[N][N][0] + dp[N][N][1] + dp[N][N][2];
}

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			std::cin >> map[i][j];

	std::cout << F();
}
