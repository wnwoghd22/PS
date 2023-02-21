#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 100'001;
struct Edge { int u, v, w, i, o; } edges[LEN]; // u -> v with weigt w, index of edge, order of edge by euler tour
std::vector<Edge> graph[LEN];
int level[LEN], parent[LEN];
int tree_size[LEN], heavy[LEN], node_i[LEN]; // size of subtree, index of heavy-node, order of edge connected with parent node
int ch_ord, chain[LEN], chain_top[LEN], chain_size[LEN]; // order of chain, each index of chain of node, index of node of top of chain, size of chain
int e_ord, edge_i[LEN]; // order of edges according to euler tour
int N, M, seg_max[LEN * 4];

void update(int n, int d, int s = 1, int e = N - 1, int i = 1) {
	if (n < s || e < n) return;
	if (s == e) {
		seg_max[i] = d;
		return;
	}

	int m = s + e >> 1;
	update(n, d, s, m, i << 1), update(n, d, m + 1, e, i << 1 | 1);
	seg_max[i] = std::max(seg_max[i << 1], seg_max[i << 1 | 1]);
}

int get_max(int l, int r, int s = 1, int e = N - 1, int i = 1) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return seg_max[i];

	int m = s + e >> 1;
	return std::max(get_max(l, r, s, m, i << 1), get_max(l, r, m + 1, e, i << 1 | 1));
}

int dfs(const int u, const int p = 0, const int i = -1) {
	tree_size[u] = 1;
	parent[u] = p;
	level[u] = level[p] + 1;
	node_i[u] = i;

	for (const Edge& e : graph[u]) {
		int v = e.v;
		if (v == p) continue;
		int s = dfs(v, u, e.i);
		if (!heavy[u] || s > tree_size[heavy[u]])
			heavy[u] = v;
		tree_size[u] += s;
	}
	return tree_size[u];
}

void dfs_euler(const int u, const int p = 0, const int i = 0) {
	chain[u] = ch_ord;
	if (i) edges[i].o = ++e_ord, edge_i[u] = e_ord;
	if (!chain_size[chain[u]]) chain_top[chain[u]] = u;
	++chain_size[chain[u]];

	if (heavy[u]) dfs_euler(heavy[u], u, node_i[heavy[u]]);

	for (const Edge& e : graph[u]) {
		int v = e.v;
		if (v == p || v == heavy[u]) continue;
		++ch_ord;
		dfs_euler(v, u, e.i);
	}
}

void update_edge(int i, int d) { update(edges[i].o, d); }
int query(int u, int v) {
	int result = 0;
	while (chain[u] ^ chain[v]) {
		// std::cout << u << ' ' << v << '\n';
		if (level[chain_top[chain[u]]] > level[chain_top[chain[v]]]) std::swap(u, v);
		// std::cout << "v->top: " << v << "->" << chain_top[chain[v]] << '\n';
		result = std::max(result, get_max(edge_i[chain_top[chain[v]]], edge_i[v]));
		// std::cout << v << ' ' << result << '\n';
		v = parent[chain_top[chain[v]]];
	}
	if (level[u] > level[v]) std::swap(u, v);
	// std::cout << "u, v: " << u << ' ' << v << '\n';
	// std::cout << u << ' ' << v << ' ' << edge_i[u] << ' ' << edge_i[v] << '\n';
	return std::max(result, get_max(edge_i[heavy[u]], edge_i[v]));
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1, u, v, w; i < N; ++i) {
		std::cin >> u >> v >> w;
		edges[i] = { u, v, w, i };
		graph[u].push_back({ u, v, w, i });
		graph[v].push_back({ v, u, w, i });
	}
	dfs(1);
	dfs_euler(1);
	for (const Edge& e : edges) update_edge(e.i, e.w);

	// for (int i = 1; i < N; ++i) std::cout << edge_order[i] << ' ';  std::cout << '\n';
	// for (int i = 1; i <= N; ++i) std::cout << i << ' ' << chain[i] << ' ' << chain_top[chain[i]] << ' ' << parent[i] << '\n';

	std::cin >> M;
	while (M--) {
		int q;
		std::cin >> q;
		if (q == 1) {
			int i, c;
			std::cin >> i >> c;
			update_edge(i, c);
		}
		if (q == 2) {
			int u, v;
			std::cin >> u >> v;
			std::cout << query(u, v) << '\n';
		}
	}
}