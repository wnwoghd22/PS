#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

const int LEN = 51;
const int MAX = 500'001;

int N, h[LEN], dp[LEN][MAX];

int main() {
	freopen("input.txt", "r", stdin);
	memset(dp, -1, sizeof dp);
	dp[0][0] = 0;
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> h[i];
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < MAX; ++j) {
			dp[i][j] = dp[i - 1][j];
			if (j >= h[i] && ~dp[i - 1][j - h[i]])
				dp[i][j] = std::max(dp[i][j], dp[i - 1][j - h[i]] + h[i]);
			if (j <= h[i] && ~dp[i - 1][h[i] - j])
				dp[i][j] = std::max(dp[i][j], dp[i - 1][h[i] - j] + j);
			if (j + h[i] <= MAX && ~dp[i - 1][j + h[i]])
				dp[i][j] = std::max(dp[i][j], dp[i - 1][h[i] + j]);
		}
	}
	std::cout << (dp[N][0] ? dp[N][0] : -1);
}