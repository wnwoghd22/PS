#include <iostream>
#include <algorithm>
#include <vector>

const int LEN = 3e5 + 1;

std::vector<int> g[LEN];
int N, sz[LEN];

int dfs(int u, int p = 0) {
	sz[u] = 1;
	for (const int& v : g[u]) {
		if (v == p) continue;
		sz[u] += dfs(v, u);
	}
	return sz[u];
}

int main() {
	std::cin >> N;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1);
	int min = 1e9;
	for (const int& v : g[1])
		min = std::min(min, sz[1] - sz[v]);
	std::cout << min;
}