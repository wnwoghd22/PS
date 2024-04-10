#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>

typedef long long ll;
const int LEN = 100'001;

int N, M, Q, S[LEN], E[LEN];
struct SegTree {
	ll tree[LEN * 4];
	ll lazy[LEN * 4];
	void propagate(int s, int e, int i) {
		if (lazy[i]) {
			tree[i] += lazy[i] * (e - s + 1);
			if (s ^ e) {
				lazy[i << 1] += lazy[i];
				lazy[i << 1 | 1] += lazy[i];
			}
			lazy[i] = 0;
		}
	}
	void update(int l, int r, ll d, int s = 1, int e = N, int i = 1) {
		propagate(s, e, i);
		if (e < l || r < s) return;
		if (l <= s && e <= r) {
			tree[i] += d * (e - s + 1);
			if (s ^ e) {
				lazy[i << 1] += d;
				lazy[i << 1 | 1] += d;
			}
			return;
		}
		int m = s + e >> 1;
		update(l, r, d, s, m, i << 1);
		update(l, r, d, m + 1, e, i << 1 | 1);
		tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	ll get(int l, int r, int s = 1, int e = N, int i = 1) {
		propagate(s, e, i);
		if (e < l || r < s) return 0;
		if (l <= s && e <= r) return tree[i];
		int m = s + e >> 1;
		return get(l, r, s, m, i << 1) + get(l, r, m + 1, e, i << 1 | 1);
	}
} w_edge, w_vert;

std::vector<int> graph[LEN];
int level[LEN], size[LEN], parent[LEN];
int ord, order[LEN], heavy[LEN];
int ch_ord, chain[LEN], chain_size[LEN], chain_top[LEN];

int dfs(int u, int p = 0) {
	parent[u] = p;
	level[u] = level[p] + 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int sub_size = dfs(v, u);
		if (!heavy[u] || sub_size > size[heavy[u]])
			heavy[u] = v;
		size[u] += sub_size;
	}
	return size[u] += 1;
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

void update(int u, int v) {
	while (chain[u] ^ chain[v]) {
		if (level[chain_top[chain[u]]] > level[chain_top[chain[v]]]) std::swap(u, v);
		w_vert.update(order[chain_top[chain[v]]], order[v], 1);
		w_edge.update(order[chain_top[chain[v]]], order[v], 1);
		v = parent[chain_top[chain[v]]];
	}
	if (level[u] > level[v]) std::swap(u, v);
	if (u ^ v) w_edge.update(order[heavy[u]], order[v], 1);
	w_vert.update(order[u], order[v], 1);
}
ll get(int u, int v) {
	ll sum = 0;
	while (chain[u] ^ chain[v]) {
		if (level[chain_top[chain[u]]] > level[chain_top[chain[v]]]) std::swap(u, v);
		sum += w_vert.get(order[chain_top[chain[v]]], order[v]);
		sum -= w_edge.get(order[chain_top[chain[v]]], order[v]);
		v = parent[chain_top[chain[v]]];
	}
	if (level[u] > level[v]) std::swap(u, v);
	sum += w_vert.get(order[u], order[v]);
	if (u ^ v) sum -= w_edge.get(order[heavy[u]], order[v]); // IMPORTANT!
	return sum;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);
	std::cin >> N >> M >> Q;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	dfs(1);
	dfs_euler(1);
	for (int i = 1; i <= M; ++i) std::cin >> S[i] >> E[i];
	for (int i = 0, q, x, y, k; i < Q; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> x >> y;
			update(x, y);
		}
		if (q == 2) {
			std::cin >> k;
			std::cout << get(S[k], E[k]) << '\n';
		}
	}
}