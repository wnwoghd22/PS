#include <iostream>
#include <algorithm>

const int INF = 1e9;
const int LEN = 1000;
int N, A[LEN];
int dp[LEN][3];
int max[LEN][3][3];

int solve() {
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < 3; ++j)
				dp[i][j] = INF, max[i][j][0] = max[i][j][1] = max[i][j][2] = 0;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	if (N == 1) return A[0];
	if (N == 2) return A[0] + A[1];
	dp[0][0] = max[0][0][0] = A[0];
	dp[1][1] = max[1][1][1] = A[1];
	dp[2][2] = max[2][2][2] = A[2];
	dp[1][1] += dp[0][0];
	for (int i = 2; i < N; ++i) {
		
	}
}