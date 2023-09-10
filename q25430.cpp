#include <iostream>
#include <algorithm>

typedef long long ll;
const ll INF = 1e13;
const int NLEN = 50'001;
const int MLEN = 100'000;

struct Edge {
	int u, v, w;
	bool operator<(const Edge& r) const { return w < r.w; }
} edges[MLEN];

int N, M,S, E;
ll dp[2][NLEN];

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < M; ++i) std::cin >> edges[i].u >> edges[i].v >> edges[i].w;
	std::cin >> S >> E;

	for (int i = 1; i <= N; ++i) dp[0][i] = dp[1][i] = INF;
	dp[0][S] = dp[1][S] = 0;

	std::sort(edges, edges + M);

	for (int u, v, w, s, m, e = 0; e < M; ++e) {
		for (s = e; e < M; ++e) {
			u = edges[e].u, v = edges[e].v, w = edges[e].w;
			dp[1][u] = std::min(dp[1][u], dp[0][v] + w);
			dp[1][v] = std::min(dp[1][v], dp[0][u] + w);
			if (e == M - 1 || edges[e + 1].w != edges[e].w) break;
		}
		for (m = s; m <= e; ++m) {
			u = edges[m].u, v = edges[m].v, w = edges[m].w;
			dp[0][u] = std::min(dp[0][u], dp[1][u]); dp[1][u] = INF;
			dp[0][v] = std::min(dp[0][v], dp[1][v]); dp[1][v] = INF;
		}
	}

	if (dp[0][E] == INF) std::cout << "DIGESTA";
	else std::cout << dp[0][E];
}