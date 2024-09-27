#include <iostream>
#include <algorithm>

// TODO: fix dp
// need two maps: left to right, and top to down.
// dp[i][j] = min(dp[i-1][j]+U[i][j], dp[i][j-1]+R[i][j])

int R[1001][1001];
int U[1001][1001];
int dp[1001][1001];

int main() {
	int N, M, K;
	std::cin >> N >> M >> K;
	while (K--) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		for (int i = a; i <= c; ++i) R[i][b]++;
		for (int j = b; j <= d; ++j) U[a][j]++;
	}
	for (int i = 1; i <= N; ++i) dp[i][1] = dp[i - 1][1] + U[i][1];
	for (int j = 1; j <= M; ++j) dp[1][j] = dp[1][j - 1] + R[1][j];

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j)
			std::cout << R[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << '\n';

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j)
			std::cout << U[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << '\n';

	for (int i = 2; i <= N; ++i)
		for (int j = 2; j <= M; ++j)
			dp[i][j] = std::min(dp[i][j - 1] + R[i][j], dp[i - 1][j] + U[i][j]);

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j)
			std::cout << dp[i][j] << ' ';
		std::cout << '\n';
	}
	std::cout << '\n';

	std::cout << dp[N][M];
}