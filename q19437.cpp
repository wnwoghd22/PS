#include <iostream>
#include <cstring>
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

int T, N, M;
std::vector<int> g[LEN];
int idx, cc, ord[LEN], H[LEN], c[LEN], par[LEN];
ll W[LEN], Wg[LEN], P[LEN], Hs[LEN], Hp[LEN];

int dfs(int u, int p, int h) {
	par[u] = p;
	c[u] = ord[u] = ++idx;
	H[u] = h;
	Wg[h] = (Wg[h] * W[u]) % MOD;
	Hs[u] = 0; Hp[u] = W[u];
	P[ord[u]] = P[ord[u] - 1] * W[u] % MOD;
	for (const int& v : g[u]) {
		if (v == p) continue;
		if (ord[v]) c[u] = std::min(c[u], c[v]);
		else {
			int nxt = dfs(v, u, h);
			if (nxt >= ord[u]) { // cycle detected, articulation
				ll sub = P[idx] * pow(P[ord[v] - 1], MOD - 2) % MOD;
				Hs[u] = (Hs[u] + sub) % MOD;
				Hp[u] = (Hp[u] * sub) % MOD;
			}
			c[u] = std::min(c[u], nxt);
		}
	}
	return c[u];
}

ll solve() {
	idx = cc = 0; P[0] = 1;
	memset(ord, 0, sizeof ord);
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		g[i].clear();
		std::cin >> W[i];
	}
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	ll S = 0;
	for (int i = 1; i <= N; ++i) {
		if (!ord[i]) {
			Wg[++cc] = 1;
			dfs(i, 0, cc);
			S = (S + Wg[cc]) % MOD;
		}
	}

	ll ret = 0;
	for (ll i = 1, z, num; i <= N; ++i) {
		num = Wg[H[i]];
		z = (S - num + num * pow(Hp[i], MOD - 2) - !par[i] + Hs[i] + MOD) % MOD;
		ret = (ret + i * z) % MOD;
	}
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}