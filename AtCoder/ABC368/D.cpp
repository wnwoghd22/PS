#include <iostream>
#include <vector>

const int LEN = 2e5 + 1;

int N, K, x;
bool V[LEN];
std::vector<int> g[LEN];

int dfs(int u, int p = -1) {
	int ret = 0;
	for (const int& v : g[u]) {
		if (v == p) continue;
		ret += dfs(v, u);
	}
	if (ret > 0) return ret + 1;
	return V[u];
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> K;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 0; i < K; ++i) {
		std::cin >> x;
		V[x] = 1;
	}
	std::cout << dfs(x);
}