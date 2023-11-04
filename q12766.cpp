#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long ll;
const int LEN = 5001;
const ll INF = 1e17;

int N, b, s, r;
ll dist[2][LEN], A[LEN], S[LEN], dp[LEN][LEN];

ll c(int g, ll i, ll j) { return dp[g - 1][i - 1] + (j - i) * (S[j] - S[i - 1]); }
void f(int g, int s, int e, int l, int r) {
	if (s > e) return;
	int m = s + e >> 1;
	int opt = l;
	for (int i = opt; i <= std::min(m, r); ++i)
		if (c(g, i, m) < c(g, opt, m)) opt = i;
	dp[g][m] = c(g, opt, m);

	f(g, s, m - 1, l, opt);
	f(g, m + 1, e, opt, r);
}

struct Edge { int v, l; };
std::vector<Edge> g[2][LEN];
struct I {
	int u; ll d;
	bool operator<(const I& r) const { return d > r.d; }
};
std::priority_queue<I> pq;

int main() {
	std::cin >> N >> b >> s >> r;
	for (int i = 0, u, v, l; i < r; ++i) {
		std::cin >> u >> v >> l;
		g[0][u].push_back({ v, l });
		g[1][v].push_back({ u, l });
	}
	for (int k = 0; k <= 1; ++k) {
		for (int i = 1; i <= N; ++i) dist[k][i] = INF;
		dist[k][b + 1] = 0; pq.push({ b + 1, 0 });
		while (pq.size()) {
			int u = pq.top().u, d = pq.top().d; pq.pop();
			if (dist[k][u] < d) continue;
			for (const Edge& e : g[k][u]) {
				if (d + e.l < dist[k][e.v]) {
					dist[k][e.v] = d + e.l;
					pq.push({ e.v, d + e.l });
				}
			}
		}
	}
	for (int i = 1; i <= b; ++i) A[i] = dist[0][i] + dist[1][i];
	std::sort(A, A + b + 1);
	for (int i = 1; i <= b; ++i) S[i] = A[i] + S[i - 1];
	for (int i = 1; i <= b; ++i) {
		std::cout << A[i] << ' ' << S[i] << '\n';
	}
	for (int i = 1; i <= b; ++i) dp[0][i] = S[i] * (i - 1);
	for (int i = 1; i < s; ++i) f(i, 1, b, 1, b);
	std::cout << dp[s - 1][b];
}