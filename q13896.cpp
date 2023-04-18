#include <iostream>
#include <vector>

const int LEN = 100'001;
std::vector<int> graph[LEN];

int T, N, Q, R;
int level[LEN];
int parent[LEN][21];
int size[LEN];

int dfs(int u, int p = 0) {
	level[u] = level[p] + 1;
	parent[u][0] = p;
	for (int i = 1, v = p; v; v = parent[v][i++])
		parent[u][i] = parent[v][i - 1];
	for (const int& v : graph[u]) {
		if (v == p) continue;
		size[u] += dfs(v, u);
	}
	return ++size[u];
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
	for (int i = 0, s, u; i < Q; ++i) {
		std::cin >> s >> u;
		if (s) {
			if (u == R) std::cout << N << '\n';
			else {
				int l = lca(u, R);
				if (l == R) std::cout << size[u] << '\n';
				// TODO: complete casework
			}
		}
		else R = u;
	}
}

int main() {
	std::cin >> T;
	while (T--) solve();
}