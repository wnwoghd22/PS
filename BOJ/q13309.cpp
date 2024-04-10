#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 200'001;

int N, Q, a, b, c, d;
std::vector<int> children[LEN];
int parent[LEN], tree_size[LEN], level[LEN];
int ord, order[LEN], heavy[LEN];
int chain_num, chain[LEN], chain_size[LEN], chain_top[LEN];

int dfs(int u, int p = 0) { // root is always 1
	level[u] = level[p] + 1;
	tree_size[u] = 1;
	for (const int& v : children[u]) {
		if (v == p) continue;
		int sub_size = dfs(v, u);
		if (!heavy[u] || sub_size > tree_size[heavy[u]]) heavy[u] = v;
		tree_size[u] += sub_size;
	}
	return tree_size[u];
}

void dfs_euler(int u, int p = 0) {
	order[u] = ++ord;
	chain[u] = chain_num;
	if (!chain_size[chain[u]]) chain_top[chain[u]] = u;
	++chain_size[chain[u]];

	if (heavy[u]) dfs_euler(heavy[u], u);

	for (const int& v : children[u]) {
		if (v == p || v == heavy[u]) continue;
		++chain_num;
		dfs_euler(v, u);
	}
}

bool seg_tree[LEN * 4];
void update(int n, bool b, int s = 1, int e = N, int i = 1) {
	if (n < s || e < n) return;
	if (s == e) {
		seg_tree[i] = b;
		return;
	}
	int m = s + e >> 1;
	update(n, b, s, m, i << 1), update(n, b, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] & seg_tree[i << 1 | 1];
}

bool is_conneted(int l, int r, int s = 1, int e = N, int i = 1) {
	if (r < s || e < l) return 1;
	if (l <= s && e <= r) return seg_tree[i];
	int m = s + e >> 1;
	return is_conneted(l, r, s, m, i << 1) & is_conneted(l, r, m + 1, e, i << 1 | 1);
}

bool find(int u, int v) {
	if (u == v) return true;
	while (chain[u] ^ chain[v]) {
		if (level[chain_top[chain[u]]] > level[chain_top[chain[v]]]) std::swap(u, v);
		if (!is_conneted(order[chain_top[chain[v]]], order[v])) return false;
		v = parent[chain_top[chain[v]]];
	}
	if (level[u] > level[v]) std::swap(u, v);
	return is_conneted(order[heavy[u]], order[v]);
}

bool find_and_delete(int b, int c) {
	bool result = find(b, c);
	update(order[result ? b : c], 0);
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N >> Q;
	for (int i = 2; i <= N; ++i) {
		std::cin >> a;
		children[a].push_back(i);
		parent[i] = a;
	}
	dfs(1);
	dfs_euler(1);

	for (int i = 0; i < N * 4; ++i) seg_tree[i] = 1;
	while (Q--) {
		std::cin >> b >> c >> d;
		if (d == 0) std::cout << (find(b, c) ? "YES\n" : "NO\n");
		if (d == 1) std::cout << (find_and_delete(b, c) ? "YES\n" : "NO\n");
	}
}