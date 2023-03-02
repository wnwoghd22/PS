#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int LEN = 201;
const int INF = 1e9;
struct Edge { int v, l; };
struct Info {
	int u, d;
	bool operator<(const Info& r) const { return d > r.d; }
};
std::vector<Edge> graph[LEN];
int N, M, S, E, L, max_dist[LEN][LEN], min_dist[LEN][LEN], dist[LEN], visited[LEN];

double dijkstra(int s) {
	std::priority_queue<Info> pq;
	memset(visited, 0, sizeof visited);
	for (int i = 1; i <= N; ++i) dist[i] = INF;
	double result = 0;
	dist[s] = 0;
	pq.push({ s, 0 });
	while (pq.size()) {
		auto [u, d] = pq.top(); pq.pop();
		// std::cout << "dijkstra u: " << u << ", dist: " << d << '\n';
		if (d > dist[u]) continue;
		visited[u] = 1;
		result = std::max(result, (double)d);
		for (const auto& [v, l] : graph[u]) {
			if (u == v) {
				result = std::max(result, d + (double)max_dist[u][u] / 2);
				continue;
			}
			dist[v] = std::min(dist[v], d + l);

			if (visited[v]) {
				result = std::max(result, ((double)max_dist[u][v] + dist[v] + dist[u]) / 2);
				continue;
			}
			pq.push({ v, d + l });
		}
	}
	return result;
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin.tie(0)->sync_with_stdio(0);

	std::cin >> N >> M;
	while (M--) {
		std::cin >> S >> E >> L;
		if (!min_dist[S][E] || L < min_dist[S][E]) min_dist[S][E] = min_dist[E][S] = L;
		if (L > max_dist[S][E]) max_dist[S][E] = max_dist[E][S] = L;
	}
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j)
			if (min_dist[i][j]) graph[i].push_back({ j, min_dist[i][j] });

	double min = 1e9;
	std::cout << std::fixed;
	std::cout.precision(1);
	for (int u = 1; u <= N; ++u) min = std::min(min, dijkstra(u));
	std::cout << min;
}