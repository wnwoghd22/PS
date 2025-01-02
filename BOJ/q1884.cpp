#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int N_LEN = 101;
const int M_LEN = 10001;
const int INF = 1e9 + 7;

struct E {
	int u, c, d;
	bool operator<(const E& r) const {
		return d == r.d ? c > r.c : d > r.d;
	}
};

int T, N, M, K, dp[N_LEN][M_LEN];

std::vector<E> graph[N_LEN];
std::priority_queue<E> pq;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> M >> N >> K;
	// while (pq.size()) pq.pop();
	for (int i = 1; i <= N; ++i) {
		// graph[i].clear();
		for (int j = 0; j <= M; ++j) dp[i][j] = INF;
	}
	for (int i = 0, u, v, c, d; i < K; ++i) {
		std::cin >> u >> v >> d >> c;
		graph[u].push_back({ v, c, d });
	}
	for (int i = 1; i <= N; ++i) std::sort(graph[i].begin(), graph[i].end());
	for (int i = 0; i <= M; ++i) dp[1][i] = 0;
	pq.push({ 1, 0, 0 });
	while (pq.size()) {
		int u = pq.top().u;
		int m = pq.top().c;
		int dist = pq.top().d;
		pq.pop();
		// std::cout << "pop: " << u << ' ' << m << ' ' << dist << '\n';
		if (u == N) continue;
		if (dist > dp[u][m]) continue;
		for (int i = graph[u].size() - 1; i >= 0; --i) {
			const E& e = graph[u][i];
			int v = e.u, c = m + e.c, d = dist + e.d;
			// std::cout << v << ' ' << c << ' ' << d << '\n';
			if (c > M) continue;
			if (dp[v][c] > d) {
				dp[v][c] = d;
				for (int k = c + 1; k <= M; ++k) {
					if (dp[v][k] < d) break;
					dp[v][k] = d;
				}
				// std::cout << "push: " << v << ' ' << m + c << ' ' << dist + d << '\n';
				pq.push({ v, c, d });
			}
		}
	}
	int result = INF;
	for (int c = 0; c <= M; ++c)
		if (dp[N][c] < result)
			result = dp[N][c];

	if (result == INF) std::cout << "-1";
	else std::cout << result;
}