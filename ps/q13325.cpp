#include <iostream>

typedef long long ll;

int K;
int W[1 << 21];
int M[1 << 21];
int dfs1(int u, int d = 0) {
	if (d == K) return M[u] = W[u];
	return M[u] = std::max(dfs1(u << 1, d + 1), dfs1(u << 1 | 1, d + 1)) + W[u];
}

int dfs2(int u, int w, int d = 0) {
	if (d == K) return w - M[u];
	return w - M[u] + dfs2(u << 1, M[u] - W[u], d + 1) + dfs2(u << 1 | 1, M[u] - W[u], d + 1);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> K;

	ll ret = 0;
	for (int i = 2; i < 1 << K + 1; ++i) {
		std::cin >> W[i];
		ret += W[i];
	}
	
	dfs1(1);
	ret += dfs2(1, M[1]);
	std::cout << ret;
}