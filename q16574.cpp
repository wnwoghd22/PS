#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

typedef long long ll;
const int LEN = 100'001;
int N, M;

bool on[LEN];
ll pre[LEN];

struct SegCount {
	ll t[LEN << 2];
	void update(int l, int r, ll d, int s = 1, int e = N, int i = 1) {
		if (r < s || e < l) return;
		if (l <= s && e <= r) { t[i] += d; return; }
		int m = s + e >> 1;
		update(l, r, d, s, m, i << 1);
		update(l, r, d, m + 1, e, i << 1 | 1);
	}
	ll get(int x, int s = 1, int e = N, int i = 1) {
		if (x < s || e < x) return 0;
		if (s == e) { return t[i]; }
		int m = s + e >> 1;
		return t[i] + get(x, s, m, i << 1) + get(x, m + 1, e, i << 1 | 1);
	}
} count, rotate;

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
} seg;

std::vector<int> graph[LEN];
int ord, in[LEN], out[LEN], idx[LEN];
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
	in[u] = ++ord;
	idx[ord] = u;
	chain[u] = ch;
	if (!chain_top[ch]) chain_top[ch] = u;

	seg.update(in[u], on[u] = 1);
	count.update(ord, ord, size[u]);

	if (heavy[u]) dfs_euler(heavy[u], u);
	for (const int& v : graph[u]) {
		if (v == p || v == heavy[u]) continue;
		++ch;
		dfs_euler(v, u);
	}
	out[u] = ord;
}

int highest_connected_ancestor(int u) {
	// std::cout << "find highest: " << u << '\n';
	int v, l, r, m;
	while (true) {
		v = chain_top[chain[u]];
		// std::cout << v << '\n';
		bool connected = seg.get(in[v], in[u]);
		// std::cout << "chain connected: " << connected << '\n';
		if (!connected) break;
		if (v == 1 || !on[par[v]]) return v;
		u = par[v];
	}

	l = in[chain_top[chain[u]]], r = in[u], v = in[u];
	// std::cout << "parametric: " << chain_top[chain[u]] << ' ' << l << ' ' << u << ' ' << r << '\n';

	while (l <= r) {
		m = l + r >> 1;
		if (seg.get(m, in[u])) {
			v = std::min(v, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return idx[v];
}

int get_count(int u) {
	int v = highest_connected_ancestor(u);
	return count.get(in[v]);
}

void update_count(int u, int v, int d) {
	while (chain[u] ^ chain[v]) {
		int t = chain_top[chain[u]];
		count.update(in[t], in[u], d);
		u = par[t];
	}
	count.update(in[v], in[u], d);
}

void query1(int u) {
	// std::cout << "query1 " << u << '\n';
	pre[u] = rotate.get(in[u]); // save current state
	int v = highest_connected_ancestor(u);
	if (par[v]) pre[u] -= rotate.get(in[par[v]]) - pre[par[v]];
	seg.update(in[u], on[u] = 0);
	// std::cout << "highest: " << v << '\n';
	int d = count.get(in[u]);
	update_count(par[u], par[v], -d);
	// std::cout << "end query1\n";
}

void query2(int u) {
	// std::cout << "query2 " << u << '\n';
	seg.update(in[u], on[u] = 1);
	ll lazy = pre[u] - rotate.get(in[u]);
	int v = highest_connected_ancestor(u);
	if (par[v]) lazy += rotate.get(in[par[v]]) - pre[par[v]];
	rotate.update(in[u], out[u], lazy); // set rotation off
	int d = count.get(in[u]);
	update_count(par[u], par[v], d);
}

int query3(int u, int r) {
	// std::cout << "query3 " << u << '\n';
	int v = highest_connected_ancestor(u);
	// std::cout << v << '\n';
	if (~level[u] & 1) r = -r;
	// if ((level[u] ^ level[v]) & 1) r = -r;

	rotate.update(in[v], out[v], r % 360);

	// std::cout << r << ' ' << count.get(in[v]) << '\n';
	return std::abs(r) * count.get(in[v]);
}

int main() {
	// freopen("input.txt", "r", stdin);
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
	for (int i = 0, q, u, r; i < M; ++i) {
		std::cin >> q >> u;
		if (q == 1) query1(u);
		if (q == 2) query2(u);
		if (q == 3) std::cin >> r, std::cout << query3(u, r) << '\n';
	}

	for (int u = 1; u <= N; ++u) {
		if (!on[u])
			query2(u);
	}

	ll sum = 0;
	for (int u = 1; u <= N; ++u) {
		ll r = rotate.get(in[u]) % 360;
		if (r < 0) r += 360;
		if (~level[u] & 1) r = (360 - r) % 360;
		sum += r;
	}
	std::cout << sum;
}