#include <iostream>
#include <cstring>

const int LEN = 3000;

int N, M, K, L;
int G[LEN], Y[LEN], X[LEN];
int dp[2][LEN];

int main() {
	std::cin >> N >> M >> K;
	for (int i = 0; i < K; ++i) std::cin >> G[i] >> Y[i];
	std::cin >> L;
	for (int i = 0, x; i < L; ++i) std::cin >> x, X[x] = 1;
	
	dp[1][M] = 1;
	for (int i = 0; i < K; ++i) {
		memset(dp[i & 1], 0, sizeof dp[i & 1]);
		for (int c = 0; c < N; ++c) {
			if (!X[c] && dp[~i & 1][c]) {
				dp[i & 1][(c + G[i]) % N] = 1;
				dp[i & 1][(c + Y[i]) % N] = 1;
			}
		}
	}
	std::cout << (dp[~K & 1][0] ? "utopia" : "dystopia");
}