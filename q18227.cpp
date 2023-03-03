#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long int ll;
const int LEN = 200'001;
struct Node {
	ll a1, d;
} seg_tree[LEN * 4];
int N, C, Q, x, y;

void update(int l, int r, int a, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_tree[i].a1 += s - l + a;
		++seg_tree[i].d;
		return;
	}
	int m = s + e >> 1;
	update(l, r, a, s, m, i << 1);
	update(l, r, a, m + 1, e, i << 1 | 1);
}

ll get_sum(int x, int s = 1, int e = N, int i = 1) {
	if (e < x || x < s) return 0;
	if (s == e) return seg_tree[i].a1;
	int m = s + e >> 1;
	return seg_tree[i].a1 + seg_tree[i].d * (x - s) + get_sum(x, s, m, i << 1) + get_sum(x, m + 1, e, i << 1 | 1);
}

std::vector<int> graph[LEN];
int parent[LEN], level[LEN], tree_size[LEN];
int ord, order[LEN], heavy[LEN];
int ch_ord, chain[LEN], chain_size[LEN], chain_top[LEN];

int dfs(int u, int p = 0) {
	parent[u] = p;
	level[u] = level[p] + 1;
	tree_size[u] = 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int sub_size = dfs(v, u);
		if (!heavy[u] || sub_size > tree_size[heavy[u]])
			heavy[u] = v;
		tree_size[u] += sub_size;
	}
	return tree_size[u];
}

void dfs_euler(int u, int p = 0) {
	order[u] = ++ord;
	chain[u] = ch_ord;
	if (!chain_size[chain[u]]) chain_top[chain[u]] = u;
	++chain_size[chain[u]];

	if (heavy[u]) dfs_euler(heavy[u], u);
	for (const int& v : graph[u]) {
		if (v == p || v == heavy[u]) continue;
		++ch_ord;
		dfs_euler(v, u);
	}
}

void q1(int a) {
	while (chain[C] ^ chain[a]) {
		int top = chain_top[chain[a]];
		update(order[top], order[a], level[top]);
		a = parent[top];
	}
	update(order[C], order[a], level[C]);
}
ll q2(int a) { return get_sum(order[a]); }

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N >> C;
	for (int i = 1; i < N; ++i) {
		std::cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	dfs(C);
	dfs_euler(C);

	std::cin >> Q;
	while (Q--) {
		std::cin >> x >> y;
		if (x == 1) q1(y);
		else if (x == 2) std::cout << q2(y) << '\n';
	}
}