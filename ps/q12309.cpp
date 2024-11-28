#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;
const ll INF = 1e17;
const int LEN = 100'001;
int T, N, K, X[LEN];
ll S[LEN];
std::vector<int> g[LEN];

int f(int u, ll k, int p = -1) {
	if ((S[u] = X[u]) > k) return K + 1;
	int ret = 0;
	std::priority_queue<int> pq;
	for (const int& v : g[u]) {
		if (v == p) continue;
		ret += f(v, k, u);
		S[u] += S[v];
		pq.push(S[v]);
	}
	while (pq.size() && S[u] > k) {
		S[u] -= pq.top(); pq.pop();
		ret++;
	}
	return ret;
}

ll solve() {
	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i) std::cin >> X[i], g[i].clear();
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	ll l = 0, r = INF, m, ret = r;
	while (l <= r) {
		m = l + r >> 1;
		if (f(1, m) <= K) {
			ret = std::min(ret, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> T;
	while (T--) std::cout << solve() << '\n';
}