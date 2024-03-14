#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 2e5 + 1;
const ll MOD = 1e9 + 7;

ll pow(ll a, ll b) {
	ll ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return ret;
}

std::vector<int> g[LEN];
int idx, ord[LEN], H[LEN], t[LEN], c[LEN];
ll W[LEN], P[LEN], Hs[LEN], Hp[LEN];

int dfs(int u, int p = 0, int h = idx) {
	c[u] = ord[u] = ++idx;
	H[u] = h;
	P[ord[u]] = P[ord[p]] * W[u] % MOD;
	Hp[u] = W[u];
	for (const int& v : g[u]) {
		if (v == p) continue;
		if (c[v]) c[u] = std::min(c[u], c[v]);
		else {
			int nxt = dfs(v, u, h);
			if (nxt >= ord[u]) { // cycle detected, articulation
				ll sub = P[idx] * pow(P[ord[u]], MOD - 2) % MOD;
				Hs[u] = (Hs[u] + sub) % MOD;
				Hp[u] = (Hp[u] * sub) % MOD;
			}
		}
	}
	return c[u];
}