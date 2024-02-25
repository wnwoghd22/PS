#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 3e5 + 1;
const ll MOD = 1e9 + 7;

int N;
std::vector<int> g[LEN];
int ord, in[LEN], out[LEN], lv[LEN], o[LEN];
void dfs(int u) {
	in[u] = ++ord;
	o[ord] = u;
	for (const int& v : g[u]) {
		lv[v] = lv[u] + 2;
		dfs(v);
	}
	out[u] = ord;
}

ll X[LEN << 2], K[LEN << 2];
void update(int v, int x, int k, int s = 1, int e = N, int i = 1) {
	int l = in[v], r = out[v];
	if (r < s || e < l) return;
	if (l <= s && e <= r) {
		X[i] = (X[i] + x) % MOD;
		K[i] = (K[i] + k * (lv[o[s]] - lv[v])) % MOD;
		return;
	}
	int m = s + e >> 1;
	update(v, x, k, s, m, i << 1);
	update(v, x, k, m + 1, e, i << 1 | 1);
}

ll query(int v, int s = 1, int e = N, int i = 1) {
	if (o[v] < s || e < o[v]) return 0;
	
	ll ret = ((X[i] - (lv[o[s]] - lv[v]) * K[i] % MOD) + MOD) % MOD;
	
	if (s ^ e) {
		int m = s + e >> 1;
		ret += query(v, s, m, i << 1);
		ret += query(v, m + 1, e, i << 1 | 1);
	}
	return ret % MOD;
}

int main() {

}