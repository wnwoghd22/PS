#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 250'001;
const ll INF = 1e12;

struct E { int v, c; };
std::vector<E> g[LEN];
ll S[LEN][2];
int C[LEN][2];

ll lambda = 0;
void dfs(int u, int p = 0) {
	ll s = 0, aug_s = 0;
	int cnt = 0, aug_cnt = 0;
	for (const E& e : g[u]) {
		int v = e.v, c = e.c;
		if (v == p) continue;
		dfs(v, u);
		s += S[v][1], cnt += C[v][1];
		ll cur_s = S[v][0] - S[v][1] + c - lambda;
		ll cur_cnt = C[v][0] - C[v][1] + 1;
		if (cur_s > aug_s || cur_s == aug_s && cur_cnt > aug_cnt)
			aug_s = cur_s, aug_cnt = cur_cnt;
	}
	S[u][0] = s, C[u][0] = cnt;
	S[u][1] = s + aug_s, C[u][1] = cnt + aug_cnt;
}

int N, K;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> K;
	for (int i = 1, u, v, c; i < N; ++i) {
		std::cin >> u >> v >> c;
		g[u].push_back({ v, c });
		g[v].push_back({ u, c });
	}
	lambda = -INF;
	dfs(1);
	if (C[1][1] < K) {
		std::cout << "Impossible";
		return 0;
	}
	ll l = -INF, r = INF, ret = -INF;
	while (l <= r) {
		lambda = l + r >> 1;
		dfs(1);
		if (C[1][1] >= K) {
			ret = std::max(ret, lambda);
			l = lambda + 1;
		}
		else r = lambda - 1;
	}
	lambda = ret; dfs(1);
	std::cout << std::max(S[1][0], S[1][1]) + ret * K;
}