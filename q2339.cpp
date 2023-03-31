#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

typedef long long int ll;
enum Dir {
	HORIZONTAL,
	VERTICAL,
};
int N, map[20][20];
ll dp[20][20][20][20][2];

ll divide(int l, int r, int u, int d, int dir) {
	if (l + 1 >= r && u + 1 >= d) { // base case
		int result = 0;
		for (int i = u; i <= d; ++i) {
			for (int j = l; j <= r; ++j) {
				if (map[i][j] == 1) return dp[l][r][u][d][0] = dp[l][r][u][d][1] = 0;
				if (map[i][j] == 2) result += 1;
			}
		}
		return dp[l][r][u][d][0] = dp[l][r][u][d][1] = result == 1;
	}
	ll& ref = dp[l][r][u][d][dir];
	if (~ref) return ref;
	ref = 0;

	if (dir == HORIZONTAL) { // cut horizontal
		for (int i = u + 1; i < d; ++i) {
			bool jewel = 0, obstacle = 0;
			for (int j = l; j <= r; ++j) {
				if (map[i][j] == 1) obstacle = 1;
				if (map[i][j] == 2) jewel = 1;
			}
			if (!jewel && obstacle)
				ref += divide(l, r, u, i - 1, VERTICAL) * divide(l, r, i + 1, d, VERTICAL);
		}
	}
	if (dir == VERTICAL) { // cut vertical
		for (int i = l + 1; i < r; ++i) {
			bool jewel = 0, obstacle = 0;
			for (int j = u; j <= d; ++j) {
				if (map[j][i] == 1) obstacle = 1;
				if (map[j][i] == 2) jewel = 1;
			}
			if (!jewel && obstacle)
				ref += divide(l, i - 1, u, d, HORIZONTAL) * divide(i + 1, r, u, d, HORIZONTAL);
		}
	}

	int total_jewel = 0, total_obstacle = 0;
	for (int i = l; i <= r; ++i) {
		for (int j = u; j <= d; ++j) {
			if (map[j][i] == 1) total_obstacle += 1;
			if (map[j][i] == 2) total_jewel += 1;
		}
	}
	if (!total_obstacle)
		return dp[l][r][u][d][0] = dp[l][r][u][d][1] = total_jewel == 1;
	// std::cout << l << ' ' << r << ' ' << u << ' ' << d << ' ' << dir << ' ' << total_jewel << ' ' << total_obstacle << ' ' << ref << '\n';
	return ref;
}

int main() {
	freopen("input.txt", "r", stdin);
	memset(dp, -1, sizeof dp);
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> map[i][j];
	ll result = divide(0, N - 1, 0, N - 1, HORIZONTAL) + divide(0, N - 1, 0, N - 1, VERTICAL);
	std::cout << (result ? result : -1);
}