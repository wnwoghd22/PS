#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 1e5 + 1;

std::vector<int> g[LEN];

int N, C[LEN];
ll S[LEN], total, SD[LEN], F[LEN];

void dfs_pre(int u, int p = 0) {
	S[u] = C[u];
	for (const int& v : g[u]) {
		if (v == p) continue;
		dfs_pre(v, u);
		S[u] += S[v];
		SD[u] += SD[v];
	}
	SD[u] += S[u] - C[u];
}

ll dfs(int u, ll f, int p = 0) {
	F[u] = f;
	ll ret = F[u];

	// std::cout << "f: " << u << ' ' << f << '\n';

	for (const int& v : g[u]) {
		if (v == p) continue;
		ll nxt = f + total - 2 * S[v];
		ret = std::min(ret, dfs(v, nxt, u));
	}
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for (int i = 1; i <= N; ++i) std::cin >> C[i];
	dfs_pre(1);
	total = S[1];
	
	std::cout << dfs(1, SD[1]);
}