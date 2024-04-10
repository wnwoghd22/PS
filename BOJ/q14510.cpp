#include <iostream>
#include <algorithm>
#include <cstring>

typedef long long ll;
const int LEN = 1e5;

int N, M, K, W, S[LEN * 2 + 1];
int p[LEN * 2 + 1];
int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int join(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return 0;
	if (p[a] < p[b]) p[a] += p[b], p[b] = a;
	else p[b] += p[a], p[a] = b;
	return 1;
}

ll cost;
struct Edge {
	int u, v, f, c;
	ll w;
	bool operator<(const Edge& r) const { return w == r.w ? f < r.f : w < r.w; }
} edges[LEN * 5];

int mst(ll m) {
	int ret = 0;
	int cnt = cost = 0;
	for (int i = 0; i < M; ++i) edges[i].w = edges[i].c + edges[i].f * m;
	std::sort(edges, edges + M);
	memset(p, -1, sizeof p);
	for (int i = 0; i < M; ++i) {
		if (join(edges[i].u, edges[i].v)) {
			++ret;
			cnt += edges[i].f;
			cost += edges[i].w;
		}
	}
	if (ret < N - 1) return -1;
	return cnt;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> K >> W;
	for (int i = 0, s; i < K; ++i) {
		std::cin >> s;
		S[s] = 1;
	}
	for (int i = 0; i < M; ++i) {
		std::cin >> edges[i].u >> edges[i].v >> edges[i].c;
		edges[i].f = S[edges[i].u] ^ S[edges[i].v];
	}
	if (!~mst(0)) { std::cout << -1; return 0; }
	ll l = -LEN, r = LEN, m, ret = -1;
	if (mst(l) < W || mst(r) > W) { std::cout << -1; return 0; }
	while (l <= r) {
		m = l + r >> 1;
		if (mst(m) <= W) {
			ret = std::max(ret, cost - m * W);
			r = m - 1;
		}
		else l = m + 1;
	}
	std::cout << ret;
}