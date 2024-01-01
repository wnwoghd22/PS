#include "circuit.h"

#include <vector>
#include <cstring>

// #include <iostream>

typedef long long ll;
const int LEN = 100'001;
const ll MOD = 1e9 + 2022;

std::vector<int> graph[LEN];
ll n, _m, C[LEN], l[LEN], S[LEN];
inline ll sum(int l, int r) { return (S[r] - S[l - 1] + MOD) % MOD; }

ll tree[LEN << 2];
bool lz[LEN << 2];

void add(int x, ll d, int s = 1, int e = _m, int i = 1) {
	if (x < s || e < x) return;
	tree[i] = (tree[i] + d) % MOD;
	if (s == e) return;
	int m = s + e >> 1;
	add(x, d, s, m, i << 1);
	add(x, d, m + 1, e, i << 1 | 1);
}
void propagate(int s, int e, int i) {
	if (lz[i]) {
		tree[i] = (sum(s, e) - tree[i] + MOD) % MOD;
		if (s ^ e) {
			lz[i << 1] ^= 1;
			lz[i << 1 | 1] ^= 1;
		}
	}
	lz[i] = 0;
}
void flip(int l, int r, int s = 1, int e = _m, int i = 1) {
	propagate(s, e, i);
	if (r < s || e < l) return;
	if (l <= s && e <= r) {
		lz[i] ^= 1; propagate(s, e, i);
		return;
	}
	int m = s + e >> 1;
	flip(l, r, s, m, i << 1); flip(l, r, m + 1, e, i << 1 | 1);
	tree[i] = (tree[i << 1] + tree[i << 1 | 1]) % MOD;
}

ll dfs1(int u) {
	if (u >= n) return C[u] = 1;
	ll c = 1;
	for (const int& v : graph[u]) {
		l[v] = c;
		c = dfs1(v) * c % MOD;
	}
	return C[u] = c * graph[u].size() % MOD;
}
void dfs2(int u, ll c) {
	if (u >= n) { S[u - n + 1] = c; return; }
	for (int i = graph[u].size() - 1, v; i >= 0; --i) {
		v = graph[u][i];
		dfs2(v, c * l[v] % MOD);
		c = c * C[v] % MOD;
	}
}

void init(int N, int M, std::vector<int> P, std::vector<int> A) {
	n = N, _m = M;
	memset(tree, 0, sizeof tree);
	memset(lz, 0, sizeof lz);
	for (int i = 0; i < LEN; ++i) graph[i].clear();
	for (int i = 1; i < n + _m; ++i) graph[P[i]].push_back(i);
	dfs1(0);
	dfs2(0, 1);
	for (int i = 0; i < _m; ++i) {
		// std::cout << i + n << ' ' << S[i + 1] << '\n';
		if (A[i]) add(i + 1, S[i + 1]);
	}
	for (int i = 1; i <= _m; ++i) 
		S[i] = (S[i] + S[i - 1]) % MOD;
}

int count_ways(int L, int R) {
	int l = L - n + 1;
	int r = R - n + 1;
	flip(l, r);
	return tree[1];
}
