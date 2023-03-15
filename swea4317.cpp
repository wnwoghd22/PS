#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>

int H, W;
int dp[25][10][1 << 10];
int A[25][10];

int dfs(int i, int j, int bit) {
	if (i >= W) return 0;
	int& ref = dp[i][j][bit];
	if (~ref) return ref;
	ref = 0;

	if (A[i][j]) {
		ref = std::max(ref, dfs(i + (j + 1) / H, (j + 1) % H, 1023 & (bit << 1 | 1)));
	}
	else {
		if (j < H - 1 && !A[i][j + 1] && !(bit & 3 << (H - 2))) {
			ref = std::max(ref, dfs(i + (j + 2) / H, (j + 2) % H, 1023 & (bit << 2 | 3)) + 1);
		}
		ref = std::max(ref, dfs(i + (j + 1) / H, (j + 1) % H, 1023 & (bit << 1)));
	}

	return ref;
}

int solve() {
	memset(dp, -1, sizeof dp);
	std::cin >> H >> W;
	for (int i = 0; i < H; ++i)
		for (int j = 0; j < W; ++j)
			std::cin >> A[j][i];

	/*std::cout << '\n' << H << ' ' << W << '\n';
	for (int i = 0; i < W; ++i) {
		for (int j = 0; j < H; ++j)
			std::cout << A[i][j];
		std::cout << '\n';
	}*/

	int bit = 0;
	for (int i = 0; i < H; ++i) bit = bit << 1 | A[0][i];

	return dfs(1, 0, bit);
}

int main() {
	freopen("input.txt", "r", stdin);
	int t, T;
	std::cin >> T;
	for (t = 1; t <= T; ++t) {
		std::cout << '#' << t << ' ' << solve() << '\n';
	}
}