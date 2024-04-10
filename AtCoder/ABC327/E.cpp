#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;
typedef long double ld;
const ld TOL = 1e-12;
const int LEN = 5e3 + 1;
const ld INF = 1e17;

struct Edge {
	int u, b, c;
};

ld pow[LEN];

ld x;

struct Score {
	ll p, i;
	ld f(ld x) const { return -pow[i] * x + pow[i] * p; }
	bool operator<(const Score& r) { return f(x) > r.f(x); }
} S[LEN];
ll N, K;

ld f(ld m) {
	x = m;
	std::sort(S, S + N);
	ll P = 0, Q = 0;
	ld result = 0;
	for (int i = 0; i < K; ++i) result += S[i].f(x);
	return result;
}

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

	}
	std::cout << std::fixed;
	std::cout.precision(12);
	std::cout << bs();
}