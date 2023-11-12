#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 250'001;

std::vector<int> g[LEN];
int N, A[LEN];
int colors[LEN];
int sub_cnt[LEN], excl[LEN];
bool sub[LEN], sup[LEN] = { 1, };

bool dfs_sub(int u, int p = 0) {
	int l = ++colors[A[u]];
	int cur = l;
	sub[u] = 1;
	for (const int& v : g[u]) {
		if (v == p) continue;
		sub[u] &= dfs_sub(v, u);
		excl[v] = colors[A[u]] - cur;
		cur = colors[A[u]];
	}
	for (int i = 0, sub_l = 1; i < g[u].size(); ++i) {
		if (g[u][i] == p) continue;
		sup[g[u][i]] &= sub_l;
		sub_l &= sub[g[u][i]];
	}
	for (int i = g[u].size() - 1, sub_r = 1; i >= 0; --i) {
		if (g[u][i] == p) continue;
		sup[g[u][i]] &= sub_r;
		sub_r &= sub[g[u][i]];
	}

	return sub[u] &= !(sub_cnt[u] = colors[A[u]] - l);
}
void dfs_sup(int u, int p = 0) {
	sup[u] &= sup[p] & !(sub_cnt[p] - excl[u]) & !(colors[A[u]] - sub_cnt[u] - 1);
	for (const int& v : g[u]) {
		if (v == p) continue;
		dfs_sup(v, u);
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i], sup[i] = 1;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs_sub(1);
	dfs_sup(1);
	ll ans0 = 0, ans1 = 0, ans2 = 0;
	for (ll i = 1; i <= N; ++i) {
		// std::cout << sub[i] << ' ' << sup[i] << ' ' << sub_cnt[i] << '\n';
		if (sub[i] && sup[i]) {
			ans0++;
			ans1 += i;
			ans2 += i * i;
		}
	}
	std::cout << ans0 << '\n' << ans1 << '\n' << ans2;
}