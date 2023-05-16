#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long ll;
typedef long double ld;

const ld ERR = 1e-7;
const ll INF = 1e17;
const int LEN = 100'001;

struct Line {
	ll a, b;
	ld x;
	Line() : a(0), b(0), x(-INF) {}
	Line(ll a, ll b, ld x) : a(a), b(b), x(x) {}
	ld operator&(const Line& r) { return (ld)(r.b - b) / (a - r.a); } // get pos X of intersect of l and r
} hull[LEN];
int ptr = 1;
ll N, dist[LEN], V[LEN], S[LEN], dp[LEN];

int binary_search(const Line& line) {
	int l = 1, r = ptr, m;
	while (l < r) {
		m = l + r >> 1;
		if ((hull[m] & line) < hull[m].x) r = m;
		else l = m + 1;
	}
	return r;
}
int binary_search(int x) {
	int l = 0, r = ptr - 1, m;
	while (l < r) {
		m = l + r + 1 >> 1;
		if (hull[m].x < x) l = m;
		else r = m - 1;
	}
	return r;
}
ll f(ll x) {
	int p = binary_search(x);
	return hull[p].a * x + hull[p].b;
}

struct Edge { ll v, w; };
std::vector<Edge> graph[LEN];

void dfs(int u, int p = 0, ll d = 0) {
	int pp = ptr, idx;
	Line pl, cur;
	if (p) {
		dp[u] = f(V[u]) + d * V[u] + S[u];
		cur = Line(-d, dp[u], -INF);
		idx = binary_search(cur);
		pl = hull[idx];
		cur.x = cur & hull[idx - 1];
		hull[idx] = cur;
		ptr = idx + 1;
	}
	for (const Edge& e : graph[u]) {
		if (e.v == p) continue;
		dfs(e.v, u, d + e.w);
	}
	if (p) {
		hull[idx] = pl;
		ptr = pp;
	}
}

int main() {
	std::cin >> N;
	for (int i = 1, u, v, w; i < N; ++i) {
		std::cin >> u >> v >> w;
		graph[u].push_back({ v, w });
		graph[v].push_back({ u, w });
	}
	for (int i = 2; i <= N; ++i) std::cin >> S[i] >> V[i];

	dfs(1);
	for (int i = 2; i <= N; ++i) std::cout << dp[i] << ' ';
}