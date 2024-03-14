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
int idx, ord[LEN], H[LEN], t[LEN], c[LEN], is_root[LEN];
ll W[LEN], P[LEN], Hs[LEN], Hp[LEN];

int dfs(int u, int p = 0, int h = idx) {
	is_root[u] = !p;
	c[u] = ord[u] = ++idx;
	H[u] = h;
	P[ord[u]] = P[ord[p]] * W[u] % MOD;
	Hp[u] = W[u];
	ll den = pow(P[ord[u]], MOD - 2) % MOD;
	for (const int& v : g[u]) {
		if (v == p) continue;
		if (c[v]) c[u] = std::min(c[u], c[v]);
		else {
			int nxt = dfs(v, u, h);
			if (nxt >= ord[u]) { // cycle detected, articulation
				ll sub = P[idx] * den % MOD;
				Hs[u] = (Hs[u] + sub) % MOD;
				Hp[u] = (Hp[u] * sub) % MOD;
			}
		}
	}
	return c[u];
}

ll solve() {
	idx = 0; P[0] = 1;
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
			dfs(i);
			t[H[i]] = idx;
			S = (S + P[idx]);
		}
	}

	ll ret = 0;
	for (ll i = 1, z, num; i <= N; ++i) {
		num = P[ord[t[H[i]]]];
		z = (S - num + num * pow(Hp[ord[i]], MOD - 2) - is_root[i] + Hs[ord[i]] + MOD) % MOD;
		ret = (ret + i * z) % MOD;
	}
	return ret;
}

int main() {
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';	
}