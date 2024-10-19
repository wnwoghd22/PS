#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 250'001;

char cmd;
int N, M, seg_tree[LEN * 4];
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
	int result = 0;
	while (chain[u] ^ chain[v]) {
		if (level[chain_top[chain[u]]] > level[chain_top[chain[v]]]) std::swap(u, v);
		result += get_sum(node_order[chain_top[chain[v]]], node_order[v]);
		v = parent[chain_top[chain[v]]];
	}
	if (level[u] > level[v]) std::swap(u, v);
	return result + get_sum(node_order[u], node_order[v]);
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1);
	dfs_euler(1);

	std::cin >> M;
	for (int i = 1, u, v; i < N + M; ++i) {
		std::cin >> cmd;
		if (cmd == 'A') {
			std::cin >> u >> v;
			update_node(v, 1);
		}
		if (cmd == 'W') {
			std::cin >> v;
			std::cout << level[v] - query(1, v) - 1 << '\n';
		}
	}
}