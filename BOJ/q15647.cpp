#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 300'001;

struct Edge { int v, w; };

std::vector<Edge> g[LEN];
int N, sz[LEN], w[LEN];
ll sum[LEN], ans[LEN];

void dfs(int u, int p = -1) {
	sz[u] = 1;
	for (const Edge& e : g[u]) {
		if (e.v == p) continue;
		w[e.v] = e.w;
		dfs(e.v, u);
		sz[u] += sz[e.v];
		sum[u] += sum[e.v] + sz[e.v] * e.w;
	}
}

void solve(int u, int p = -1, ll ret = 0) {
	ans[u] = ret + sum[u] + (N - sz[u]) * w[u];
	for (const Edge& e : g[u]) {
		if (e.v == p) continue;
		solve(e.v, u, ans[u] - sum[e.v] - sz[e.v] * e.w);
	}
}


int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1, u, v, w; i < N; ++i)	{
		std::cin >> u >> v >> w;
		g[u].push_back({ v, w });
		g[v].push_back({ u, w });
	}
	dfs(1);
	solve(1);
	for (int i = 1; i <= N; ++i) std::cout << ans[i] << '\n';
}