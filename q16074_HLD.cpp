#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

const int LEN = 250'001;

int N, M, Q, h[500][500];
int p[LEN];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
bool join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return false;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return true;
}

int seg_tree[LEN << 2];
void update(int n, int d, int s = 1, int e = N * M, int i = 1) {
	if (n < s || e < n) return;
	if (s == e) {
		seg_tree[i] = d;
		return;
	}
	int m = s + e >> 1;
	update(n, d, s, m, i << 1), update(n, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = std::max(seg_tree[i << 1], seg_tree[i << 1 | 1]);
}
int get_max(int l, int r, int s = 1, int e = N * M, int i = 1) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return seg_tree[i];
	int m = s + e >> 1;
	return std::max(get_max(l, r, s, m, i << 1), get_max(l, r, m + 1, e, i << 1 | 1));
}

std::vector<int> graph[LEN];
int tree_size[LEN], level[LEN], parent[LEN], heavy[LEN];
int order, node_order[LEN];
int chain_num, chain[LEN], chain_size[LEN], chain_top[LEN];
int dfs(int u, int p = 0) {
	tree_size[u] = 1;
	parent[u] = p;
	level[u] = level[p] + 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int sub_size = dfs(v, u);
		if (!heavy[u] || sub_size > tree_size[heavy[u]]) heavy[u] = v;
		tree_size[u] += sub_size;
	}
	return tree_size[u];
}
void dfs_euler(int u, int p = 0) {
	node_order[u] = ++order;
	chain[u] = chain_num;
	if (!chain_size[chain[u]]) chain_top[chain[u]] = u;
	++chain_size[chain[u]];

	if (heavy[u]) dfs_euler(heavy[u], u);

	for (const int& v : graph[u]) {
		if (v == p || v == heavy[u]) continue;
		++chain_num;
		dfs_euler(v, u);
	}
}

void update_node(int i, int d) { update(node_order[i], d); }
int query(int u, int v) {
	int result = -1;
	while (chain[u] ^ chain[v]) {
		if (level[chain_top[chain[u]]] > level[chain_top[chain[v]]]) std::swap(u, v);
		result = std::max(result, get_max(node_order[chain_top[chain[v]]], node_order[v]));
		v = parent[chain_top[chain[v]]];
	}
	if (level[u] > level[v]) std::swap(u, v);
	return std::max(result, get_max(node_order[u], node_order[v]));
}

struct Edge {
	int a, b, c;
	bool operator<(const Edge& r) const { return c < r.c; }
} edges[LEN << 1];
int ep;

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> M >> N >> Q;
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cin >> h[i][j];
			if (i > 0) edges[ep++] = { i * N + j, (i - 1) * N + j, std::max(h[i][j], h[i - 1][j]) };
			if (j > 0) edges[ep++] = { i * N + j, i * N + j - 1, std::max(h[i][j], h[i][j - 1]) };

		}
	}
	std::sort(edges, edges + ep);

	memset(p, -1, sizeof p);
	for (int i = 0; i < ep; ++i) {
		int u = edges[i].a + 1, v = edges[i].b + 1;
		if (join(u, v)) {
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
	}
	dfs(1);
	dfs_euler(1);
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
			update_node(i * N + j + 1, h[i][j]);

	for (int i = 0, x1, y1, x2, y2; i < Q; ++i) {
		std::cin >> x1 >> y1 >> x2 >> y2;
		std::cout << query(--x1 * N + y1, --x2 * N + y2) << '\n';
	}
}