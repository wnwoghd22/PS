#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;
const int LEN = 100'001;

int N;

struct Node {
	ll lm, rm, sum, max;
	bool lazy;	// for lazy
	ll val;	// for lazy
	Node operator+(const Node& r) const {
		return {
			std::max(lm, sum + r.rm),
			std::max(rm + r.sum, r.rm),
			sum + r.sum,
			std::max({ max, r.max, rm + r.lm })
		};
	}
	Node operator~() const { return { rm, lm, sum, max, lazy, val }; }
} seg_tree[LEN * 4];

void propagate(int s, int e, int i) {
	if (seg_tree[i].lazy) {
		seg_tree[i].sum = seg_tree[i].val * (e - s + 1);
		seg_tree[i].lm = seg_tree[i].rm = seg_tree[i].max = std::max(seg_tree[i].sum, 0ll);
		if (s ^ e) {
			for (int j = 0; j < 2; ++j) {
				seg_tree[i << 1 | j].lazy = 1;
				seg_tree[i << 1 | j].val = seg_tree[i].val;
			}
		}
		seg_tree[i].lazy = 0;
	}
}

void update(int l, int r, ll d, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s) return;
	if (l <= s && e <= r) {
		seg_tree[i].sum = d * (e - s + 1);
		if (s ^ e) {
			for (int j = 0; j < 2; ++j) {
				seg_tree[i << 1 | j].lazy = 1;
				seg_tree[i << 1 | j].val = d;
			}
		}
		return;
	}
	int m = s + e >> 1;
	update(l, r, d, s, m, i << 1);
	update(l, r, d, m + 1, e, i << 1 | 1);
	seg_tree[i] = seg_tree[i << 1] + seg_tree[i << 1 | 1];
}

Node get(int l, int r, int s = 1, int e = N, int i = 1) {
	propagate(s, e, i);
	if (e < l || r < s) return { 0, 0, 0, 0 };
	if (l <= s && e <= r) return seg_tree[i];
	int m = s + e >> 1;
	return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
}

std::vector<int> graph[LEN];
int parent[LEN][20], level[LEN], size[LEN];
int ord, order[LEN], heavy[LEN];
int ch_ord, chain[LEN], chain_size[LEN], chain_top[LEN];

int dfs(int u, int p = 0) {
	level[u] = level[p] + 1;
	parent[u][0] = p;
	for (int i = 1, v = p; v; v = parent[u][i++])
		parent[u][i] = parent[v][i - 1];
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int sub_size = dfs(v, u);
		if (!heavy[u] || sub_size > size[heavy[u]]) heavy[u] = v;
		size[u] += sub_size;
	}
	return ++size[u];
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

int lca(int u, int v) {
	if (level[u] ^ level[v]) {
		if (level[u] > level[v]) std::swap(u, v);
		for (int i = 19; i >= 0; --i)
			if (level[parent[v][i]] >= level[u])
				v = parent[v][i];
	}
	int l = u;
	if (u ^ v) {
		for (int i = 19; i >= 0; --i) {
			if (parent[u][i] ^ parent[v][i]) {
				u = parent[u][i];
				v = parent[v][i];
			}
			l = parent[u][i];
		}
	}
	return l;
}

ll query1(int u, int v) {
	if (order[u] > order[v]) std::swap(u, v);
	int l = lca(u, v);
	Node total = { 0, 0, 0, 0 };
	Node nu = { 0, 0, 0, 0 };
	Node nv = { 0, 0, 0, 0 };
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

ll query2(int u, int v) {

}