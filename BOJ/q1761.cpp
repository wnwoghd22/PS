#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 40'001;
int N, M, u, v, w, seg_tree[LEN * 4];
void update(int n, int d, int s = 1, int e = N, int i = 1) {
	if (n < s || e < n) return;
	if (s == e) {
		seg_tree[i] = d;
		return;
	}
	int m = s + e >> 1;
	update(n, d, s, m, i << 1), update(n, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}
int get_sum(int l, int r, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return seg_tree[i];
	int m = s + e >> 1;
	return get_sum(l, r, s, m, i << 1) + get_sum(l, r, m + 1, e, i << 1 | 1);
}

struct Edge { int v, w; };
std::vector<Edge> graph[LEN];
int tree_size[LEN], parent[LEN], level[LEN];
int ord, order[LEN], heavy[LEN], heavy_w[LEN];
int chain_num, chain[LEN], chain_top[LEN], chain_size[LEN];

int dfs(int u, int p = 0) {
	tree_size[u] = 1;
	parent[u] = p;
	level[u] = level[p] + 1;
	for (const Edge& e : graph[u]) {
		if (e.v == p) continue;
		int sub_size = dfs(e.v, u);
		if (!heavy[u] || sub_size > tree_size[heavy[u]]) heavy[u] = e.v, heavy_w[u] = e.w;
		tree_size[u] += sub_size;
	}
	return tree_size[u];
}

void dfs_euler(int u, int p = 0, int w = 0) {
	order[u] = ++ord;
	update(order[u], w);
	chain[u] = chain_num;
	if (!chain_size[chain[u]]) chain_top[chain[u]] = u;
	++chain_size[chain[u]];

	if (heavy[u]) dfs_euler(heavy[u], u, heavy_w[u]);
	for (const Edge& e : graph[u]) {
		if (e.v == p || e.v == heavy[u]) continue;
		++chain_num;
		dfs_euler(e.v, u, e.w);
	}
}

int query(int u, int v) {
	if (u == v) return 0;
	int result = 0;
	while (chain[u] ^ chain[v]) {
		if (level[chain_top[chain[u]]] > level[chain_top[chain[v]]]) std::swap(u, v);
		result += get_sum(order[chain_top[chain[v]]], order[v]);
		v = parent[chain_top[chain[v]]];
	}
	if (level[u] > level[v]) std::swap(u, v);
	result += get_sum(order[heavy[u]], order[v]);
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1; i < N; ++i) {
		std::cin >> u >> v >> w;
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}
	dfs(1);
	dfs_euler(1);

	std::cin >> M;
	while (M--) {
		std::cin >> u >> v;
		std::cout << query(u, v) << '\n';
	}
}