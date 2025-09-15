#include <iostream>
#include <cstring>

const int LEN = 101;

int N, M, g[LEN][LEN], dp[LEN][LEN];
int f(int u, int i) {
	if (u == i) return dp[i][i] = 1;
	int& ret = dp[u][i];
	if (~ret) return ret;
	ret = 0;
	for (int j = 1; j < N; ++j) {
		if (g[u][j])
			ret += g[u][j] * f(j, i);
	}
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0, x, y, k; i < M; ++i) {
		std::cin >> x >> y >> k;
		g[x][0]++;
		g[x][y] = k;
	}
	memset(dp, -1, sizeof dp);
	for (int i = 1; i <= N; ++i) {
		if (!g[i][0]) {
			f(N, i);
			std::cout << i << ' ' << dp[N][i] << '\n';
		}
	}
}