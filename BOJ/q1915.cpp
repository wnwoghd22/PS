#include <iostream>
#include <algorithm>

std::string map[1'000];
int dp[1'001][1'001];

int main() {
	int N, M, max = 0;
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> map[i];
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			if (map[i - 1][j - 1] == '1') {
				dp[i][j] = std::min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] }) + 1;
				max = std::max(max, dp[i][j]);
			}
		}
	}
	std::cout << max * max;
}