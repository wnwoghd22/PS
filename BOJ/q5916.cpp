#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 100'001;
int N, M, seg_tree[LEN * 4];
void update(int l, int r, int d, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) { seg_tree[i] += d; return; }
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1), update(l, r, d, m + 1, e, i << 1 | 1);
}
int get(int x, int s = 1, int e = N, int i = 1) {
	if (e < x || x < s) return 0;
	if (s == e) return seg_tree[i];
	int m = s + e >> 1;
	return seg_tree[i] + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
}

std::vector<int> graph[LEN];
int level[LEN], parent[LEN], size[LEN];
int ord, order[LEN], heavy[LEN];
int ch_ord, chain[LEN], chain_size[LEN], chain_top[LEN];
int dfs(int u, int p = 0) {
	parent[u] = p;
	level[u] = level[p] + 1;
	size[u] = 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int sub_size = dfs(v, u);
		if (!heavy[u] || sub_size > size[heavy[u]]) heavy[u] = v;
		size[u] += sub_size;
	}
	return size[u];
}
void dfs_euler(int u, int p = 0) {
	order[u] = ++ord;
	chain[u] = ch_ord;
	if (!chain_size[chain[u]]++) 
		chain_top[chain[u]] = u;
	if (heavy[u]) dfs_euler(heavy[u], u);
	for (const int& v : graph[u]) {
		if (v == p || v == heavy[u]) continue;
		++ch_ord;
		dfs_euler(v, u);
	}
}

void update(int u, int v) {
	while (chain[u] ^ chain[v]) {
		if (level[chain_top[chain[u]]] > level[chain_top[chain[v]]]) std::swap(u, v);
		update(order[chain_top[chain[v]]], order[v], 1);
		v = parent[chain_top[chain[v]]];
	}
	if (level[u] > level[v]) std::swap(u, v);
	if (u ^ v) update(order[heavy[u]], order[v], 1);
}
int query(int u, int v) { return get(level[u] > level[v] ? order[u] : order[v]); }
char q;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1);
	dfs_euler(1);
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> q >> u >> v;
		if (q == 'P') update(u, v);
		if (q == 'Q') std::cout << query(u, v) << '\n';
	}
}