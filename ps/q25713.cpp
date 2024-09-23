#include <iostream>
#include <algorithm>

int map[1001][1001];
int dp[1001][1001];

int main() {
	int N, M, K;
	std::cin >> N >> M >> K;
	while (K--) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		for (int i = a; i <= c; ++i)
			for (int j = b; j <= d; ++j)
				map[i][j]++;
	}
	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j <= M; ++j) {
			dp[i][j] = 2000;
		}
	}
	
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			dp[i][j] = std::max(std::min(dp[i - 1][j], dp[i][j - 1]), map[i][j]);
		}
	}
	std::cout << dp[N][M];
}