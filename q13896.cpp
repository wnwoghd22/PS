#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>

const int LEN = 100'001;
std::vector<int> graph[LEN];

int T, N, Q, R;
int level[LEN];
int parent[LEN][21];
int size[LEN];

int dfs(int u, int p = 0) {
	level[u] = level[p] + 1;
	parent[u][0] = p;
	size[u] = 1;
	for (int i = 1, v = p; v; v = parent[u][i++])
		parent[u][i] = parent[v][i - 1];
	for (const int& v : graph[u]) {
		if (v == p) continue;
		size[u] += dfs(v, u);
	}
	return size[u];
}
int find_ancestor(int u, int l) { // find ancestor of level l of u 
	int v = u;
	for (int i = 20; i >= 0; --i)
		if (level[parent[v][i]] >= l)
			v = parent[v][i];
	return v;
}
int lca(int u, int v) {
	if (level[u] ^ level[v]) {
		if (level[u] > level[v]) std::swap(u, v);
		for (int i = 20; i >= 0; --i)
			if (level[parent[v][i]] >= level[u])
				v = parent[v][i];
	}
	int l = u;
	if (u ^ v) {
		for (int i = 20; i >= 0; --i) {
			if (parent[u][i] ^ parent[v][i]) {
				u = parent[u][i];
				v = parent[v][i];
			}
			l = parent[u][i];
		}
	}
	return l;
}

void solve() {
	for (std::vector<int>& v : graph) v.clear();
	memset(parent, 0, sizeof parent);
	std::cin >> N >> Q >> R;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1);
	for (int i = 0, s, u; i < Q; ++i) {
		std::cin >> s >> u;
		if (s) {
			if (u == R) std::cout << N << '\n';
			else {
				int l = lca(u, R);
				if (l == u) {
					int p = find_ancestor(R, level[u] + 1);
					std::cout << N - size[p] << '\n';
				}
				else std::cout << size[u] << '\n';

			}
		}
		else R = u;
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	for (int t = 1; t <= T; ++t) {
		std::cout << "Case #" << t << ":\n";
		solve();
	}
}