#include <iostream>
#include <vector>
#include <algorithm>

typedef long double ld;
const ld TOL = 1e-12;
const int LEN = 2e5 + 1;
const ld INF = 1e17;

struct Edge {
	int u, b, c;
};

int N, M;
std::vector<Edge> g[LEN];
ld dp[LEN];

ld f(ld x) {
	dp[1] = 0;
	for (int i = 2; i <= N; ++i) dp[i] = -INF;
	for (int v = 2; v <= N; ++v) {
		for (const Edge& e : g[v]) {
			ld val = e.b - x * e.c;
			dp[v] = std::max(dp[v], dp[e.u] + val);
		}
	}
	return dp[N];
}

ld bs() {
	ld l = -INF, r = INF, m;
	ld result = -INF;
	while (r - l > TOL) {
		m = (l + r) / 2;
		if (f(m) > -TOL) {
			result = std::max(result, m);
			l = m + TOL;
		}
		else r = m - TOL;
	}
	return result;
}

int main() {
	std::cin >> N >> M;
	for (int i = 0, u, v, b, c; i < M; ++i) {
		std::cin >> u >> v >> b >> c;
		g[v].push_back({ u, b, c });
	}
	std::cout << std::fixed;
	std::cout.precision(12);
	std::cout << bs();
}