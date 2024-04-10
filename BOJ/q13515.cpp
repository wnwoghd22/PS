#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>

const int LEN = 100'001;
const int BLACK = 0;
const int WHITE = 1;

int N, M;

struct SegCount {
	int t[LEN << 2];
	void update(int l, int r, int d, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return;
		if (l <= s && e <= r) { t[i] += d; return; }
		int m = s + e >> 1;
		update(l, r, d, s, m, i << 1);
		update(l, r, d, m + 1, e, i << 1 | 1);
	}
	int get(int x, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return 0;
		if (s == e) { return t[i]; }
		int m = s + e >> 1;
		return t[i] + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
	}
} dp[2];

struct SegConnect {
	bool t[LEN << 2];
	void update(int x, bool b, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return;
		if (s == e) { t[i] = b; return; }
		int m = s + e >> 1;
		update(x, b, s, m, i << 1);
		update(x, b, m + 1, e, i << 1 | 1);
		t[i] = t[i << 1] && t[i << 1 | 1];
	}
	bool get(int l, int r, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return 1;
		if (l <= s && e <= r) return t[i];
		int m = s + e >> 1;
		return get(l, r, s, m, i << 1) && get(l, r, m + 1, e, i << 1 | 1);
	}
} seg[2];

/*
 * TODO:
 * finding highest connected ancestor:
 *	1. while check if chain is connected: (log^2 N)
 *		connected:
 *			chain <- chain_top.parent
 *			continue
 *		else:
 *			break
 *	2. parametric search (log^2 N)
 * 
 * if connection changed on node i:
 *	range update from direct parent of i to highest connected ancestor (log^2 N)
 *	connected: range.update(dp[i])
 *	disconneted: range.update(-dp[i])
 */

bool color[LEN];

std::vector<int> graph[LEN];
int ord, order[LEN], index[LEN];
int par[LEN], size[LEN], level[LEN];
int ch, chain[LEN], chain_top[LEN], heavy[LEN];

int dfs(int u, int p = 0) {
	par[u] = p;
	size[u] = 1;
	level[u] = level[p] + 1;
	for (const int& v : graph[u]) {
		if (v == p) continue;
		int sub = dfs(v, u);
		if (!heavy[u] || sub > size[heavy[u]])
			heavy[u] = v;
		size[u] += sub;
	}
	return size[u];
}

void dfs_euler(int u, int p = 0) {
	order[u] = ++ord;
	index[ord] = u;
	chain[u] = ch;
	if (!chain_top[ch]) chain_top[ch] = u;

	// std::cout << u << chain[u] << '\n';
	// std::cout << "update black " << ord << ' ' << size[u] << '\n';
	dp[BLACK].update(ord, ord, size[u]);
	dp[WHITE].update(ord, ord, 1);

	if (heavy[u]) dfs_euler(heavy[u], u);
	for (const int& v : graph[u]) {
		if (v == p || v == heavy[u]) continue;
		++ch;
		dfs_euler(v, u);
	}
}

int highest_connected_ancestor(int u) {
	bool c = color[u];
	int v, l, r, m;
	while (true) {
		v = chain_top[chain[u]];
		bool connected = seg[c].get(order[v], order[u]);
		// std::cout << "chain connected: " << connected << '\n';
		if (!connected) break;
		if (v == 1 || color[par[v]] ^ c) return v;
		u = par[v];
	}

	l = order[chain_top[chain[u]]], r = order[u], v = N;
	// std::cout << "parametric: " << chain_top[chain[u]] << ' ' << l << ' ' << u << ' ' << r << '\n';
	
	while (l <= r) {
		m = l + r >> 1;
		if (seg[c].get(m, order[u])) {
			v = std::min(v, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return index[v];
}

void query(int u, int v, int c, int d) {
	while (chain[u] ^ chain[v]) {
		int t = chain_top[chain[u]];
		dp[c].update(order[t], order[u], d);
		u = par[t];
	}
	dp[c].update(order[v], order[u], d);
}

void switch_color(int u) {
	int c = color[u];
	int d = dp[c].get(order[u]);
	int v = highest_connected_ancestor(u);
	query(par[u], par[v], c, -d);
	seg[c].update(order[u], 0);

	c = color[u] ^= 1;
	seg[c].update(order[u], 1);
	d = dp[c].get(order[u]);
	v = highest_connected_ancestor(u);
	query(par[u], par[v], c, d);
}

int get_count(int u) {
	int v = highest_connected_ancestor(u);
	return dp[color[u]].get(order[v]);
}


int main() {
	freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	memset(seg[BLACK].t, -1, sizeof seg[BLACK].t);
	dfs(1);
	dfs_euler(1);

	std::cin >> M;
	for (int i = 0, q, u; i < M; ++i) {
		std::cin >> q >> u;
		if (q == 1) switch_color(u);
		if (q == 2) std::cout << get_count(u) << '\n';
	}
}