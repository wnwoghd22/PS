#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

bool dp[750][750][750][4];
int R, C, result;

int main() {
	scanf("%d %d", &R, &C);

	for (int r = 0; r < R; ++r) {
		for (int e, c = 0; c < C; ++c) {
			scanf("%1d", &e);
			dp[0][r][c][0] = dp[0][r][c][1] = dp[0][r][c][2] = dp[0][r][c][3] = e;
			if (e) result = 1;
		}
	}

	for (int i = 1; i <= std::min(R, C) / 2; ++i) {
		for (int r = i; r < R - i; ++r) {
			for (int c = i; c < C - i; ++c) {
				if (dp[i - 1][r - 1][c][0] && dp[i - 1][r][c - 1][0]) dp[i][r][c][0] = 1;
				if (dp[i - 1][r - 1][c][1] && dp[i - 1][r][c + 1][1]) dp[i][r][c][1] = 1;
				if (dp[i - 1][r + 1][c][2] && dp[i - 1][r][c - 1][2]) dp[i][r][c][2] = 1;
				if (dp[i - 1][r + 1][c][3] && dp[i - 1][r][c + 1][3]) dp[i][r][c][3] = 1;

				if (dp[i][r][c][0] && dp[i][r][c][1] && dp[i][r][c][2] && dp[i][r][c][3]) result = i + 1;
			}
		}
	}
	std::cout << result;
}