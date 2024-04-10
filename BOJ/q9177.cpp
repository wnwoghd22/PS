#include <iostream>
#include <algorithm>
#include <cstring>

const int LEN = 201;

int T, N, M, K;
char A[LEN], B[LEN], C[LEN * 2];
bool dp[LEN * 2][LEN];

bool solve() {
	memset(dp, 0, sizeof dp);
	std::cin >> A >> B >> C;

	N = strlen(C);
	M = strlen(A);
	K = strlen(B);

	dp[0][0] = 1;
	for (int i = 1; i <= N; ++i) {
		// std::cout << "dp " << i << ' ';
		for (int m = 0, k; m <= std::min(i - 1, M); ++m) {
			if (dp[i - 1][m]) {
				k = i - 1 - m;
				// std::cout << m << ' ';
				if (k >= K) continue;
				if (A[m] == C[i - 1]) dp[i][m + 1] = 1;
				if (B[k] == C[i - 1]) dp[i][m] = 1;
			}
		}
		// std::cout << '\n';
	}
	for (int i = 0; i <= M; ++i) if (dp[N][i]) return 1;
	return 0;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	for (int t = 1; t <= T; ++t) {
		std::cout << "Data set " << t << ": " << (solve() ? "yes" : "no") << '\n';
		/*for (int i = 0; i <= N; ++i) {
			for (int j = 0; j <= M; ++j) std::cout << dp[i][j] << ' ';
			std::cout << '\n';
		}*/
	}
}