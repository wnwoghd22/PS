#include <iostream>
#include <algorithm>

const int LEN = 1002;
const int INF = 1e9;
int map[LEN][LEN];
int dp[LEN][LEN][2];
int N, M;

int F() {
	for (int i = 0; i < LEN; ++i)
		for (int j = 0; j < LEN; ++j)
			dp[i][j][0] = dp[i][j][1] = -INF;

	dp[1][0][0] = 0;
	for (int i = 1; i <= M; ++i) dp[1][i][0] = dp[1][i - 1][0] + map[1][i];

	for (int i = 2; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) dp[i][j][0] = std::max({ dp[i - 1][j][0], dp[i - 1][j][1], dp[i][j - 1][0] }) + map[i][j];
		for (int j = M; j >= 1; --j) dp[i][j][1] = std::max({ dp[i - 1][j][0], dp[i - 1][j][1], dp[i][j + 1][1] }) + map[i][j];
	}
	return dp[N][M][0];
}

int main() {
	std::cin >> N >> M;

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			std::cin >> map[i][j];

	std::cout << F();
}