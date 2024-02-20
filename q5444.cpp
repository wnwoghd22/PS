#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 1e5;
int T,N, M, S, dp[2][LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) {
		std::cin >> N >> M;
		memset(dp, -1, sizeof dp);
		dp[0][0] = 0;
		for (int i = 1; i <= N; ++i) {
			std::cin >> S;
			memcpy(dp[i & 1], dp[~i & 1], sizeof dp[i & 1]);
			for (int j = 0, k; j < M; ++j) {
				if (~dp[~i & 1][j]) {
					int& cur = dp[i & 1][(j + S) % M];
					cur = std::max(cur, dp[~i & 1][j] + 1);
				}
			}
		}
		std::cout << dp[N & 1][0] << '\n';
	}
}