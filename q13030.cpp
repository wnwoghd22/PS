#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 3e5 + 1;
const ll MOD = 1e9 + 7;

int N, Q;
std::vector<int> g[LEN];
int ord, in[LEN], out[LEN], lv[LEN], o[LEN];
void dfs(int u) {
	in[u] = ++ord;
	o[ord] = u;
	for (const int& v : g[u]) {
		lv[v] = lv[u] + 1;
		dfs(v);
	}
	out[u] = ord;
}

ll X[LEN << 2], K[LEN << 2];
void update(int v, ll x, ll k, int s = 1, int e = N, int i = 1) {
	int l = in[v], r = out[v];
	if (r < s || e < l) return;
	if (l <= s && e <= r) {
		X[i] = ((X[i] + x - k * (lv[o[s]] - lv[v])) % MOD + MOD) % MOD;
		K[i] = (K[i] + k) % MOD;
		return;
	}
	int m = s + e >> 1;
	update(v, x, k, s, m, i << 1);
	update(v, x, k, m + 1, e, i << 1 | 1);
}

ll query(int v, int s = 1, int e = N, int i = 1) {
	if (in[v] < s || e < in[v]) return 0;
	
	ll ret = ((X[i] - (lv[v] - lv[o[s]]) * K[i]) % MOD + MOD) % MOD;
	
	if (s ^ e) {
		int m = s + e >> 1;
		ret += query(v, s, m, i << 1);
		ret += query(v, m + 1, e, i << 1 | 1);
	}
	return ret % MOD;
}

int main() {
	std::cin >> N >> Q;
	for (int i = 2, p; i <= N; ++i) {
		std::cin >> p;
		g[p].push_back(i);
	}
	dfs(1);
	for (int i = 0, q, v, x, k; i < Q; ++i) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> v >> x >> k;
			update(v, x, k);
		}
		if (q == 2) {
			std::cin >> v;
			std::cout << query(v) << '\n';
		}
	}
}