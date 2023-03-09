#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 100'001;
struct Node { ll a1, d; } seg_tree[LEN * 4];
int N, Q;

void update(int l, int r, int a1, int d, int s = 1, int e = N, int i = 1) {
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_tree[i].a1 += (s - l) * d + a1;
		seg_tree[i].d += d;
		return;
	}
	int m = s + e >> 1;
	update(l, r, a1, d, s, m, i << 1);
	update(l, r, a1, d, m + 1, e, i << 1 | 1);
}
ll get(int x, int s = 1, int e = N, int i = 1) {
	if (e < x || x < s) return 0;
	if (s == e) return seg_tree[i].a1;
	int m = s + e >> 1;
	return seg_tree[i].a1 + seg_tree[i].d * (x - s) + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
}

std::vector<int> graph[LEN];
int parent[LEN][16], level[LEN];
int ord, order[LEN], tree_size[LEN], heavy[LEN];
int ch_ord, chain[LEN], chain_size[LEN], chain_top[LEN];

int dfs(int u, int p = 0) {
	parent[u][0] = p;
	for (int i = 1, v = p; v; v = parent[u][i], ++i)
		parent[u][i] = parent[v][i - 1];
	level[u] = level[p] + 1;
	tree_size[u] = 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int sub_size = dfs(v, u);
		if (!heavy[u] || sub_size > tree_size[heavy[u]]) heavy[u] = v;
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

int lca(int u, int v) {
	if (level[u] ^ level[v]) {
		if (level[u] > level[v]) std::swap(u, v);
		for (int i = 15; i >= 0; --i)
			if (level[parent[v][i]] >= level[u])
				v = parent[v][i];
	}
	int l = u;
	if (u ^ v) {
		for (int i = 15; i >= 0; --i) {
			if (parent[u][i] ^ parent[v][i]) {
				u = parent[u][i];
				v = parent[v][i];
			}
			l = parent[u][i];
		}
	}
	return l;
}

void q1(int u, int v) {
	int l = lca(u, v);
	// std::cout << "lca(" << u << ", " << v << "): " << l << '\n';
	ll pivot = level[u] - level[l];
	if (chain[u] ^ chain[v]) {
		while (chain[u] ^ chain[l]) {
			update(order[chain_top[chain[u]]], order[u], pivot - level[chain_top[chain[u]]] + level[l], -1);
			u = parent[chain_top[chain[u]]][0];
		}
		while (chain[v] ^ chain[l]) {
			update(order[chain_top[chain[v]]], order[v], pivot + level[chain_top[chain[v]]] - level[l], 1);
			v = parent[chain_top[chain[v]]][0];
		}
	}

	if (level[u] <= level[v]) update(order[u], order[v], pivot, 1);
	else update(order[v], order[u], pivot, -1);
}
ll q2(int x) { return get(order[x]); }

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (int i = 1, a, b; i < N; ++i) {
		std::cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs(1);
	dfs_euler(1);

	std::cin >> Q;
	for (int i = 0, t, u, v, x; i < Q; ++i) {
		std::cin >> t;
		if (t == 1) {
			std::cin >> u >> v;
			q1(u, v);
		}
		if (t == 2) {
			std::cin >> x;
			std::cout << q2(x) << '\n';
		}
	}
}